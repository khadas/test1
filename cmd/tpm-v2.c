// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2018 Bootlin
 * Author: Miquel Raynal <miquel.raynal@bootlin.com>
 */

#include <common.h>
#include <dm.h>
#include <log.h>
#include <mapmem.h>
#include <tpm-common.h>
#include <tpm-v2.h>
#include "tpm-user-utils.h"

static int do_tpm2_startup(cmd_tbl_t *cmdtp, int flag, int argc,
			   char * const argv[])
{
	enum tpm2_startup_types mode;

	if (argc != 2)
		return CMD_RET_USAGE;

	if (!strcasecmp("TPM2_SU_CLEAR", argv[1])) {
		mode = TPM2_SU_CLEAR;
	} else if (!strcasecmp("TPM2_SU_STATE", argv[1])) {
		mode = TPM2_SU_STATE;
	} else {
		printf("Couldn't recognize mode string: %s\n", argv[1]);
		return CMD_RET_FAILURE;
	}

	return report_return_code(tpm2_startup(mode));
}

static int do_tpm2_self_test(cmd_tbl_t *cmdtp, int flag, int argc,
			     char * const argv[])
{
	enum tpm2_yes_no full_test;

	if (argc != 2)
		return CMD_RET_USAGE;

	if (!strcasecmp("full", argv[1])) {
		full_test = TPMI_YES;
	} else if (!strcasecmp("continue", argv[1])) {
		full_test = TPMI_NO;
	} else {
		printf("Couldn't recognize test mode: %s\n", argv[1]);
		return CMD_RET_FAILURE;
	}

	return report_return_code(tpm2_self_test(full_test));
}

static int do_tpm2_clear(cmd_tbl_t *cmdtp, int flag, int argc,
			 char * const argv[])
{
	u32 handle = 0;
	const char *pw = (argc < 3) ? NULL : argv[2];
	const ssize_t pw_sz = pw ? strlen(pw) : 0;

	if (argc < 2 || argc > 3)
		return CMD_RET_USAGE;

	if (pw_sz > TPM2_DIGEST_LEN)
		return -EINVAL;

	if (!strcasecmp("TPM2_RH_LOCKOUT", argv[1]))
		handle = TPM2_RH_LOCKOUT;
	else if (!strcasecmp("TPM2_RH_PLATFORM", argv[1]))
		handle = TPM2_RH_PLATFORM;
	else
		return CMD_RET_USAGE;

	return report_return_code(tpm2_clear(handle, pw, pw_sz));
}

static int do_tpm2_pcr_extend(cmd_tbl_t *cmdtp, int flag, int argc,
			      char * const argv[])
{
	struct udevice *dev;
	struct tpm_chip_priv *priv;
	u32 index = simple_strtoul(argv[1], NULL, 0);
	void *digest = map_sysmem(simple_strtoul(argv[2], NULL, 0), 0);
	int ret;
	u32 rc;

	if (argc != 3)
		return CMD_RET_USAGE;

	ret = uclass_first_device_err(UCLASS_TPM, &dev);
	if (ret)
		return ret;

	priv = dev_get_uclass_priv(dev);
	if (!priv)
		return -EINVAL;

	if (index >= priv->pcr_count)
		return -EINVAL;

	rc = tpm2_pcr_extend(index, digest);

	unmap_sysmem(digest);

	return report_return_code(rc);
}

static int do_tpm_pcr_read(cmd_tbl_t *cmdtp, int flag, int argc,
			   char * const argv[])
{
	struct udevice *dev;
	struct tpm_chip_priv *priv;
	u32 index, rc;
	unsigned int updates;
	void *data;
	int ret;

	if (argc != 3)
		return CMD_RET_USAGE;

	ret = uclass_first_device_err(UCLASS_TPM, &dev);
	if (ret)
		return ret;

	priv = dev_get_uclass_priv(dev);
	if (!priv)
		return -EINVAL;

	index = simple_strtoul(argv[1], NULL, 0);
	if (index >= priv->pcr_count)
		return -EINVAL;

	data = map_sysmem(simple_strtoul(argv[2], NULL, 0), 0);

	rc = tpm2_pcr_read(index, priv->pcr_select_min, data, &updates);
	if (!rc) {
		printf("PCR #%u content (%d known updates):\n", index, updates);
		print_byte_string(data, TPM2_DIGEST_LEN);
	}

	unmap_sysmem(data);

	return report_return_code(rc);
}

static cmd_tbl_t tpm2_commands[] = {
	U_BOOT_CMD_MKENT(info, 0, 1, do_tpm_info, "", ""),
	U_BOOT_CMD_MKENT(init, 0, 1, do_tpm_init, "", ""),
	U_BOOT_CMD_MKENT(startup, 0, 1, do_tpm2_startup, "", ""),
	U_BOOT_CMD_MKENT(self_test, 0, 1, do_tpm2_self_test, "", ""),
	U_BOOT_CMD_MKENT(clear, 0, 1, do_tpm2_clear, "", ""),
	U_BOOT_CMD_MKENT(pcr_extend, 0, 1, do_tpm2_pcr_extend, "", ""),
	U_BOOT_CMD_MKENT(pcr_read, 0, 1, do_tpm_pcr_read, "", ""),
};

cmd_tbl_t *get_tpm_commands(unsigned int *size)
{
	*size = ARRAY_SIZE(tpm2_commands);

	return tpm2_commands;
}

U_BOOT_CMD(tpm, CONFIG_SYS_MAXARGS, 1, do_tpm, "Issue a TPMv2.x command",
"<command> [<arguments>]\n"
"\n"
"info\n"
"    Show information about the TPM.\n"
"init\n"
"    Initialize the software stack. Always the first command to issue.\n"
"startup <mode>\n"
"    Issue a TPM2_Startup command.\n"
"    <mode> is one of:\n"
"        * TPM2_SU_CLEAR (reset state)\n"
"        * TPM2_SU_STATE (preserved state)\n"
"self_test <type>\n"
"    Test the TPM capabilities.\n"
"    <type> is one of:\n"
"        * full (perform all tests)\n"
"        * continue (only check untested tests)\n"
"clear <hierarchy>\n"
"    Issue a TPM2_Clear command.\n"
"    <hierarchy> is one of:\n"
"        * TPM2_RH_LOCKOUT\n"
"        * TPM2_RH_PLATFORM\n"
"pcr_extend <pcr> <digest_addr>\n"
"    Extend PCR #<pcr> with digest at <digest_addr>.\n"
"    <pcr>: index of the PCR\n"
"    <digest_addr>: address of a 32-byte SHA256 digest\n"
"pcr_read <pcr> <digest_addr>\n"
"    Read PCR #<pcr> to memory address <digest_addr>.\n"
"    <pcr>: index of the PCR\n"
"    <digest_addr>: address to store the a 32-byte SHA256 digest\n"
);
