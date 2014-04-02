/*
 * Copyright 2011 Calxeda, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <linux/ctype.h>
#include <errno.h>
#include <common.h>
#include <asm/io.h>
#include <part_efi.h>
#include <malloc.h>

/*
 * UUID - Universally Unique IDentifier - 128 bits unique number.
 *        There are 5 versions and one variant of UUID defined by RFC4122
 *        specification. A UUID contains a set of fields. The set varies
 *        depending on the version of the UUID, as shown below:
 *        - time, MAC address(v1),
 *        - user ID(v2),
 *        - MD5 of name or URL(v3),
 *        - random data(v4),
 *        - SHA-1 of name or URL(v5),
 *
 * Layout of UUID:
 * timestamp - 60-bit: time_low, time_mid, time_hi_and_version
 * version   - 4 bit (bit 4 through 7 of the time_hi_and_version)
 * clock seq - 14 bit: clock_seq_hi_and_reserved, clock_seq_low
 * variant:  - bit 6 and 7 of clock_seq_hi_and_reserved
 * node      - 48 bit
 *
 * source: https://www.ietf.org/rfc/rfc4122.txt
 *
 * UUID binary format (16 bytes):
 *
 * 4B-2B-2B-2B-6B (big endian - network byte order)
 *
 * UUID string is 36 length of characters (36 bytes):
 *
 * 0        9    14   19   24
 * xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
 *    be     be   be   be       be
 *
 * where x is a hexadecimal character. Fields are separated by '-'s.
 * When converting to a binary UUID, le means the field should be converted
 * to little endian and be means it should be converted to big endian.
 *
 * UUID is also used as GUID (Globally Unique Identifier) with the same binary
 * format but it differs in string format like below.
 *
 * GUID:
 * 0        9    14   19   24
 * xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
 *    le     le   le   be       be
 *
 * GUID is used e.g. in GPT (GUID Partition Table) as a partiions unique id.
 */
int uuid_str_valid(const char *uuid)
{
	int i, valid;

	if (uuid == NULL)
		return 0;

	for (i = 0, valid = 1; uuid[i] && valid; i++) {
		switch (i) {
		case 8: case 13: case 18: case 23:
			valid = (uuid[i] == '-');
			break;
		default:
			valid = isxdigit(uuid[i]);
			break;
		}
	}

	if (i != UUID_STR_LEN || !valid)
		return 0;

	return 1;
}

/*
 * uuid_str_to_bin() - convert string UUID or GUID to big endian binary data.
 *
 * @param uuid_str - pointer to UUID or GUID string [37B]
 * @param uuid_bin - pointer to allocated array for big endian output [16B]
 * @str_format     - UUID string format: 0 - UUID; 1 - GUID
 */
int uuid_str_to_bin(char *uuid_str, unsigned char *uuid_bin, int str_format)
{
	uint16_t tmp16;
	uint32_t tmp32;
	uint64_t tmp64;

	if (!uuid_str_valid(uuid_str))
		return -EINVAL;

	if (str_format == UUID_STR_FORMAT_STD) {
		tmp32 = cpu_to_be32(simple_strtoul(uuid_str, NULL, 16));
		memcpy(uuid_bin, &tmp32, 4);

		tmp16 = cpu_to_be16(simple_strtoul(uuid_str + 9, NULL, 16));
		memcpy(uuid_bin + 4, &tmp16, 2);

		tmp16 = cpu_to_be16(simple_strtoul(uuid_str + 14, NULL, 16));
		memcpy(uuid_bin + 6, &tmp16, 2);
	} else {
		tmp32 = cpu_to_le32(simple_strtoul(uuid_str, NULL, 16));
		memcpy(uuid_bin, &tmp32, 4);

		tmp16 = cpu_to_le16(simple_strtoul(uuid_str + 9, NULL, 16));
		memcpy(uuid_bin + 4, &tmp16, 2);

		tmp16 = cpu_to_le16(simple_strtoul(uuid_str + 14, NULL, 16));
		memcpy(uuid_bin + 6, &tmp16, 2);
	}

	tmp16 = cpu_to_be16(simple_strtoul(uuid_str + 19, NULL, 16));
	memcpy(uuid_bin + 8, &tmp16, 2);

	tmp64 = cpu_to_be64(simple_strtoull(uuid_str + 24, NULL, 16));
	memcpy(uuid_bin + 10, (char *)&tmp64 + 2, 6);

	return 0;
}

/*
 * uuid_bin_to_str() - convert big endian binary data to string UUID or GUID.
 *
 * @param uuid_bin - pointer to binary data of UUID (big endian) [16B]
 * @param uuid_str - pointer to allocated array for output string [37B]
 * @str_format     - UUID string format: 0 - UUID; 1 - GUID
 */
void uuid_bin_to_str(unsigned char *uuid_bin, char *uuid_str, int str_format)
{
	const u8 uuid_char_order[UUID_BIN_LEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8,
						  9, 10, 11, 12, 13, 14, 15};
	const u8 guid_char_order[UUID_BIN_LEN] = {3, 2, 1, 0, 5, 4, 7, 6, 8,
						  9, 10, 11, 12, 13, 14, 15};
	const u8 *char_order;
	int i;

	/*
	 * UUID and GUID bin data - always in big endian:
	 * 4B-2B-2B-2B-6B
	 * be be be be be
	 */
	if (str_format == UUID_STR_FORMAT_STD)
		char_order = uuid_char_order;
	else
		char_order = guid_char_order;

	for (i = 0; i < 16; i++) {
		sprintf(uuid_str, "%02x", uuid_bin[char_order[i]]);
		uuid_str += 2;
		switch (i) {
		case 3:
		case 5:
		case 7:
		case 9:
			*uuid_str++ = '-';
			break;
		}
	}
}

/*
 * gen_rand_uuid() - this function generates a random binary UUID version 4.
 *                   In this version all fields beside 4 bits of version and
 *                   2 bits of variant are randomly generated.
 *
 * @param uuid_bin - pointer to allocated array [16B]. Output is in big endian.
*/
#ifdef CONFIG_RANDOM_UUID
void gen_rand_uuid(unsigned char *uuid_bin)
{
	struct uuid uuid;
	unsigned int *ptr = (unsigned int *)&uuid;
	int i;

	/* Set all fields randomly */
	for (i = 0; i < sizeof(struct uuid) / sizeof(*ptr); i++)
		*(ptr + i) = cpu_to_be32(rand());

	clrsetbits_be16(&uuid.time_hi_and_version,
			UUID_VERSION_MASK,
			UUID_VERSION << UUID_VERSION_SHIFT);

	clrsetbits_8(&uuid.clock_seq_hi_and_reserved,
		     UUID_VARIANT_MASK,
		     UUID_VARIANT << UUID_VARIANT_SHIFT);

	memcpy(uuid_bin, &uuid, sizeof(struct uuid));
}

/*
 * gen_rand_uuid_str() - this function generates UUID v4 (random) in two string
 *                       formats UUID or GUID.
 *
 * @param uuid_str - pointer to allocated array [37B].
 * @param          - uuid output type: UUID - 0, GUID - 1
 */
void gen_rand_uuid_str(char *uuid_str, int str_format)
{
	unsigned char uuid_bin[UUID_BIN_LEN];

	/* Generate UUID (big endian) */
	gen_rand_uuid(uuid_bin);

	/* Convert UUID bin to UUID or GUID formated STRING  */
	uuid_bin_to_str(uuid_bin, uuid_str, str_format);
}
#endif
