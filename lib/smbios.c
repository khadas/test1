/*
 * Copyright (C) 2015, Bin Meng <bmeng.cn@gmail.com>
 *
 * Adapted from coreboot src/arch/x86/smbios.c
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <smbios.h>
#include <tables_csum.h>
#include <version.h>
#include <asm/cpu.h>

DECLARE_GLOBAL_DATA_PTR;

/**
 * smbios_add_string() - add a string to the string area
 *
 * This adds a string to the string area which is appended directly after
 * the formatted portion of an SMBIOS structure.
 *
 * @start:	string area start address
 * @str:	string to add
 * @return:	string number in the string area
 */
static int smbios_add_string(char *start, const char *str)
{
	int i = 1;
	char *p = start;

	for (;;) {
		if (!*p) {
			strcpy(p, str);
			p += strlen(str);
			*p++ = '\0';
			*p++ = '\0';

			return i;
		}

		if (!strcmp(p, str))
			return i;

		p += strlen(p) + 1;
		i++;
	}
}

/**
 * smbios_string_table_len() - compute the string area size
 *
 * This computes the size of the string area including the string terminator.
 *
 * @start:	string area start address
 * @return:	string area size
 */
static int smbios_string_table_len(char *start)
{
	char *p = start;
	int i, len = 0;

	while (*p) {
		i = strlen(p) + 1;
		p += i;
		len += i;
	}

	return len + 1;
}

static int smbios_write_type0(uintptr_t *current, int handle)
{
	struct smbios_type0 *t = (struct smbios_type0 *)*current;
	int len = sizeof(struct smbios_type0);

	memset(t, 0, sizeof(struct smbios_type0));
	fill_smbios_header(t, SMBIOS_BIOS_INFORMATION, len, handle);
	t->vendor = smbios_add_string(t->eos, "U-Boot");
	t->bios_ver = smbios_add_string(t->eos, PLAIN_VERSION);
	t->bios_release_date = smbios_add_string(t->eos, U_BOOT_DMI_DATE);
	t->bios_rom_size = (CONFIG_ROM_SIZE / 65536) - 1;
	t->bios_characteristics = BIOS_CHARACTERISTICS_PCI_SUPPORTED |
				  BIOS_CHARACTERISTICS_SELECTABLE_BOOT |
				  BIOS_CHARACTERISTICS_UPGRADEABLE;
#ifdef CONFIG_GENERATE_ACPI_TABLE
	t->bios_characteristics_ext1 = BIOS_CHARACTERISTICS_EXT1_ACPI;
#endif
	t->bios_characteristics_ext2 = BIOS_CHARACTERISTICS_EXT2_TARGET;
	t->bios_major_release = 0xff;
	t->bios_minor_release = 0xff;
	t->ec_major_release = 0xff;
	t->ec_minor_release = 0xff;

	len = t->length + smbios_string_table_len(t->eos);
	*current += len;

	return len;
}

static int smbios_write_type1(uintptr_t *current, int handle)
{
	struct smbios_type1 *t = (struct smbios_type1 *)*current;
	int len = sizeof(struct smbios_type1);

	memset(t, 0, sizeof(struct smbios_type1));
	fill_smbios_header(t, SMBIOS_SYSTEM_INFORMATION, len, handle);
	t->manufacturer = smbios_add_string(t->eos, CONFIG_SMBIOS_MANUFACTURER);
	t->product_name = smbios_add_string(t->eos, CONFIG_SMBIOS_PRODUCT_NAME);

	len = t->length + smbios_string_table_len(t->eos);
	*current += len;

	return len;
}

static int smbios_write_type2(uintptr_t *current, int handle)
{
	struct smbios_type2 *t = (struct smbios_type2 *)*current;
	int len = sizeof(struct smbios_type2);

	memset(t, 0, sizeof(struct smbios_type2));
	fill_smbios_header(t, SMBIOS_BOARD_INFORMATION, len, handle);
	t->manufacturer = smbios_add_string(t->eos, CONFIG_SMBIOS_MANUFACTURER);
	t->product_name = smbios_add_string(t->eos, CONFIG_SMBIOS_PRODUCT_NAME);
	t->feature_flags = SMBIOS_BOARD_FEATURE_HOSTING;
	t->board_type = SMBIOS_BOARD_MOTHERBOARD;

	len = t->length + smbios_string_table_len(t->eos);
	*current += len;

	return len;
}

static int smbios_write_type3(uintptr_t *current, int handle)
{
	struct smbios_type3 *t = (struct smbios_type3 *)*current;
	int len = sizeof(struct smbios_type3);

	memset(t, 0, sizeof(struct smbios_type3));
	fill_smbios_header(t, SMBIOS_SYSTEM_ENCLOSURE, len, handle);
	t->manufacturer = smbios_add_string(t->eos, CONFIG_SMBIOS_MANUFACTURER);
	t->chassis_type = SMBIOS_ENCLOSURE_DESKTOP;
	t->bootup_state = SMBIOS_STATE_SAFE;
	t->power_supply_state = SMBIOS_STATE_SAFE;
	t->thermal_state = SMBIOS_STATE_SAFE;
	t->security_status = SMBIOS_SECURITY_NONE;

	len = t->length + smbios_string_table_len(t->eos);
	*current += len;

	return len;
}

static int smbios_write_type4(uintptr_t *current, int handle)
{
	struct smbios_type4 *t = (struct smbios_type4 *)*current;
	int len = sizeof(struct smbios_type4);
	const char *vendor;
	char *name;
	char processor_name[CPU_MAX_NAME_LEN];
	struct cpuid_result res;

	memset(t, 0, sizeof(struct smbios_type4));
	fill_smbios_header(t, SMBIOS_PROCESSOR_INFORMATION, len, handle);
	t->processor_type = SMBIOS_PROCESSOR_TYPE_CENTRAL;
	t->processor_family = gd->arch.x86;
	vendor = cpu_vendor_name(gd->arch.x86_vendor);
	t->processor_manufacturer = smbios_add_string(t->eos, vendor);
	res = cpuid(1);
	t->processor_id[0] = res.eax;
	t->processor_id[1] = res.edx;
	name = cpu_get_name(processor_name);
	t->processor_version = smbios_add_string(t->eos, name);
	t->status = SMBIOS_PROCESSOR_STATUS_ENABLED;
	t->processor_upgrade = SMBIOS_PROCESSOR_UPGRADE_NONE;
	t->l1_cache_handle = 0xffff;
	t->l2_cache_handle = 0xffff;
	t->l3_cache_handle = 0xffff;
	t->processor_family2 = t->processor_family;

	len = t->length + smbios_string_table_len(t->eos);
	*current += len;

	return len;
}

static int smbios_write_type32(uintptr_t *current, int handle)
{
	struct smbios_type32 *t = (struct smbios_type32 *)*current;
	int len = sizeof(struct smbios_type32);

	memset(t, 0, sizeof(struct smbios_type32));
	fill_smbios_header(t, SMBIOS_SYSTEM_BOOT_INFORMATION, len, handle);

	*current += len;

	return len;
}

static int smbios_write_type127(uintptr_t *current, int handle)
{
	struct smbios_type127 *t = (struct smbios_type127 *)*current;
	int len = sizeof(struct smbios_type127);

	memset(t, 0, sizeof(struct smbios_type127));
	fill_smbios_header(t, SMBIOS_END_OF_TABLE, len, handle);

	*current += len;

	return len;
}

static smbios_write_type smbios_write_funcs[] = {
	smbios_write_type0,
	smbios_write_type1,
	smbios_write_type2,
	smbios_write_type3,
	smbios_write_type4,
	smbios_write_type32,
	smbios_write_type127
};

uintptr_t write_smbios_table(uintptr_t addr)
{
	struct smbios_entry *se;
	u32 tables;
	int len = 0;
	int max_struct_size = 0;
	int handle = 0;
	char *istart;
	int isize;
	int i;

	/* 16 byte align the table address */
	addr = ALIGN(addr, 16);

	se = (struct smbios_entry *)addr;
	memset(se, 0, sizeof(struct smbios_entry));

	addr += sizeof(struct smbios_entry);
	addr = ALIGN(addr, 16);
	tables = addr;

	/* populate minimum required tables */
	for (i = 0; i < ARRAY_SIZE(smbios_write_funcs); i++) {
		int tmp = smbios_write_funcs[i](&addr, handle++);
		max_struct_size = max(max_struct_size, tmp);
		len += tmp;
	}

	memcpy(se->anchor, "_SM_", 4);
	se->length = sizeof(struct smbios_entry);
	se->major_ver = SMBIOS_MAJOR_VER;
	se->minor_ver = SMBIOS_MINOR_VER;
	se->max_struct_size = max_struct_size;
	memcpy(se->intermediate_anchor, "_DMI_", 5);
	se->struct_table_length = len;
	se->struct_table_address = tables;
	se->struct_count = handle;

	/* calculate checksums */
	istart = (char *)se + SMBIOS_INTERMEDIATE_OFFSET;
	isize = sizeof(struct smbios_entry) - SMBIOS_INTERMEDIATE_OFFSET;
	se->intermediate_checksum = table_compute_checksum(istart, isize);
	se->checksum = table_compute_checksum(se, sizeof(struct smbios_entry));

	return addr;
}
