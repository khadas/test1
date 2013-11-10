/*
 * Copyright (c) 2013 Google, Inc
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/state.h>
#include <asm/unaligned.h>
#include <linux/crc8.h>

/* TPM NVRAM location indices. */
#define FIRMWARE_NV_INDEX		0x1007
#define KERNEL_NV_INDEX			0x1008

#define NV_DATA_PUBLIC_PERMISSIONS_OFFSET	60

/* Kernel TPM space - KERNEL_NV_INDEX, locked with physical presence */
#define ROLLBACK_SPACE_KERNEL_VERSION	2
#define ROLLBACK_SPACE_KERNEL_UID	0x4752574C  /* 'GRWL' */

struct rollback_space_kernel {
	/* Struct version, for backwards compatibility */
	uint8_t struct_version;
	/* Unique ID to detect space redefinition */
	uint32_t uid;
	/* Kernel versions */
	uint32_t kernel_versions;
	/* Reserved for future expansion */
	uint8_t reserved[3];
	/* Checksum (v2 and later only) */
	uint8_t crc8;
} __packed rollback_space_kernel;

/*
 * These numbers derive from adding the sizes of command fields as shown in
 * the TPM commands manual.
 */
#define TPM_REQUEST_HEADER_LENGTH	10
#define TPM_RESPONSE_HEADER_LENGTH	10

/* These are the different non-volatile spaces that we emulate */
enum {
	NV_GLOBAL_LOCK,
	NV_SEQ_FIRMWARE,
	NV_SEQ_KERNEL,
	NV_SEQ_COUNT,
};

/* Size of each non-volatile space */
#define NV_DATA_SIZE		0x20

/*
 * Information about our TPM emulation. This is preserved in the sandbox
 * state file if enabled.
 */
static struct tpm_state {
	uint8_t nvdata[NV_SEQ_COUNT][NV_DATA_SIZE];
} state;

/**
 * sandbox_tpm_read_state() - read the sandbox EC state from the state file
 *
 * If data is available, then blob and node will provide access to it. If
 * not this function sets up an empty TPM.
 *
 * @blob: Pointer to device tree blob, or NULL if no data to read
 * @node: Node offset to read from
 */
static int sandbox_tpm_read_state(const void *blob, int node)
{
	const char *prop;
	int len;
	int i;

	if (!blob)
		return 0;

	for (i = 0; i < NV_SEQ_COUNT; i++) {
		char prop_name[20];

		sprintf(prop_name, "nvdata%d", i);
		prop = fdt_getprop(blob, node, prop_name, &len);
		if (prop && len == NV_DATA_SIZE)
			memcpy(state.nvdata[i], prop, NV_DATA_SIZE);
	}

	return 0;
}

/**
 * cros_ec_write_state() - Write out our state to the state file
 *
 * The caller will ensure that there is a node ready for the state. The node
 * may already contain the old state, in which case it is overridden.
 *
 * @blob: Device tree blob holding state
 * @node: Node to write our state into
 */
static int sandbox_tpm_write_state(void *blob, int node)
{
	int i;

	/*
	 * We are guaranteed enough space to write basic properties.
	 * We could use fdt_add_subnode() to put each set of data in its
	 * own node - perhaps useful if we add access informaiton to each.
	 */
	for (i = 0; i < NV_SEQ_COUNT; i++) {
		char prop_name[20];

		sprintf(prop_name, "nvdata%d", i);
		fdt_setprop(blob, node, prop_name, state.nvdata[i],
			    NV_DATA_SIZE);
	}

	return 0;
}

SANDBOX_STATE_IO(sandbox_tpm, "google,sandbox-tpm", sandbox_tpm_read_state,
		 sandbox_tpm_write_state);

static int index_to_seq(uint32_t index)
{
	switch (index) {
	case FIRMWARE_NV_INDEX:
		return NV_SEQ_FIRMWARE;
	case KERNEL_NV_INDEX:
		return NV_SEQ_KERNEL;
	case 0:
		return NV_GLOBAL_LOCK;
	}

	printf("Invalid nv index %#x\n", index);
	return -1;
}

int tis_sendrecv(const u8 *sendbuf, size_t send_size,
		 u8 *recvbuf, size_t *recv_len)
{
	struct tpm_state *tpm = &state;
	uint32_t code, index, length, type;
	uint8_t *data;
	int seq;

	code = get_unaligned_be32(sendbuf + sizeof(uint16_t) +
				  sizeof(uint32_t));
	printf("tpm: %zd bytes, recv_len %zd, cmd = %x\n", send_size,
	       *recv_len, code);
	print_buffer(0, sendbuf, 1, send_size, 0);
	switch (code) {
	case 0x65: /* get flags */
		type = get_unaligned_be32(sendbuf + 14);
		switch (type) {
		case 4:
			index = get_unaligned_be32(sendbuf + 18);
			printf("Get flags index %#02x\n", index);
			*recv_len = 22;
			memset(recvbuf, '\0', *recv_len);
			put_unaligned_be32(22, recvbuf +
					   TPM_RESPONSE_HEADER_LENGTH);
			data = recvbuf + TPM_RESPONSE_HEADER_LENGTH +
					sizeof(uint32_t);
			switch (index) {
			case FIRMWARE_NV_INDEX:
				break;
			case KERNEL_NV_INDEX:
				/* TPM_NV_PER_PPWRITE */
				put_unaligned_be32(1, data +
					NV_DATA_PUBLIC_PERMISSIONS_OFFSET);
				break;
			}
			break;
		case 0x11: /* TPM_CAP_NV_INDEX */
			index = get_unaligned_be32(sendbuf + 18);
			printf("Get cap nv index %#02x\n", index);
			put_unaligned_be32(22, recvbuf +
					   TPM_RESPONSE_HEADER_LENGTH);
			break;
		default:
			printf("   ** Unknown 0x65 command type %#02x\n",
			       type);
			return -1;
		}
		break;
	case 0xcd: /* nvwrite */
		index = get_unaligned_be32(sendbuf + 10);
		length = get_unaligned_be32(sendbuf + 18);
		seq = index_to_seq(index);
		if (seq < 0)
			return -1;
		printf("tpm: nvwrite index=%#02x, len=%#02x\n", index, length);
		memcpy(&tpm->nvdata[seq],
		       recvbuf + TPM_RESPONSE_HEADER_LENGTH + sizeof(uint32_t),
		       length);
		*recv_len = 12;
		memset(recvbuf, '\0', *recv_len);
		break;
	case 0xcf: /* nvread */
		index = get_unaligned_be32(sendbuf + 10);
		length = get_unaligned_be32(sendbuf + 18);
		seq = index_to_seq(index);
		if (seq < 0)
			return -1;
		printf("tpm: nvread index=%#02x, len=%#02x\n", index, length);
		*recv_len = TPM_RESPONSE_HEADER_LENGTH + sizeof(uint32_t) +
					length;
		memset(recvbuf, '\0', *recv_len);
		put_unaligned_be32(length, recvbuf +
				   TPM_RESPONSE_HEADER_LENGTH);
		if (seq == NV_SEQ_KERNEL) {
			struct rollback_space_kernel rsk;

			data = recvbuf + TPM_RESPONSE_HEADER_LENGTH +
					sizeof(uint32_t);
			rsk.struct_version = 2;
			rsk.uid = ROLLBACK_SPACE_KERNEL_UID;
			rsk.kernel_versions = 0;
			rsk.crc8 = crc8((unsigned char *)&rsk,
					offsetof(struct rollback_space_kernel,
						 crc8));
			memcpy(data, &rsk, sizeof(rsk));
		} else {
			memcpy(recvbuf + TPM_RESPONSE_HEADER_LENGTH +
			       sizeof(uint32_t), &tpm->nvdata[seq], length);
		}
		break;
	case 0x14: /* tpm extend */
	case 0x15: /* pcr read */
	case 0x5d: /* force clear */
	case 0x6f: /* physical enable */
	case 0x72: /* physical set deactivated */
	case 0x99: /* startup */
	case 0x4000000a:  /* assert physical presence */
		*recv_len = 12;
		memset(recvbuf, '\0', *recv_len);
		break;
	default:
		printf("Unknown tpm command %02x\n", code);
		return -1;
	}

	return 0;
}

int tis_open(void)
{
	printf("%s\n", __func__);
	return 0;
}

int tis_close(void)
{
	printf("%s\n", __func__);
	return 0;
}

int tis_init(void)
{
	printf("%s\n", __func__);
	return 0;
}
