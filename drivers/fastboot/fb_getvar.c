// SPDX-License-Identifier: BSD-2-Clause
/*
 * Copyright (C) 2016 The Android Open Source Project
 */

#include <common.h>
#include <fastboot.h>
#include <fastboot-internal.h>
#include <fb_mmc.h>
#include <fb_nand.h>
#include <fs.h>
#include <version.h>
#include <partition_table.h>

static void getvar_version(char *var_parameter, char *response);
static void getvar_bootloader_version(char *var_parameter, char *response);
static void getvar_downloadsize(char *var_parameter, char *response);
static void getvar_serialno(char *var_parameter, char *response);
static void getvar_version_baseband(char *var_parameter, char *response);
static void getvar_hw_revision(char *var_parameter, char *response);
static void getvar_off_mode_charge(char *var_parameter, char *response);
static void getvar_variant(char *var_parameter, char *response);
static void getvar_battery_soc_ok(char *var_parameter, char *response);
static void getvar_battery_voltage(char *var_parameter, char *response);
static void getvar_block_size(char *var_parameter, char *response);
static void getvar_secure(char *var_parameter, char *response);
static void getvar_unlocked(char *var_parameter, char *response);
static void getvar_is_userspace(char *var_parameter, char *response);
static void getvar_is_logical(char *var_parameter, char *response);
static void getvar_slot_count(char *var_parameter, char *response);
static void getvar_super_partition_name(char *var_parameter, char *response);



static void getvar_product(char *var_parameter, char *response);
static void getvar_current_slot(char *var_parameter, char *response);
static void getvar_slot_suffixes(char *var_parameter, char *response);
static void getvar_has_slot(char *var_parameter, char *response);
#if CONFIG_IS_ENABLED(FASTBOOT_FLASH)
static void getvar_partition_type(char *part_name, char *response);
static void getvar_partition_size(char *part_name, char *response);
#endif

static const struct {
	const char *variable;
	void (*dispatch)(char *var_parameter, char *response);
} getvar_dispatch[] = {
	{
		.variable = "version",
		.dispatch = getvar_version
	}, {
		.variable = "bootloader-version",
		.dispatch = getvar_bootloader_version
	}, {
		.variable = "version-bootloader",
		.dispatch = getvar_bootloader_version
	}, {
		.variable = "off-mode-charge",
		.dispatch = getvar_off_mode_charge
	}, {
		.variable = "hw-revision",
		.dispatch = getvar_hw_revision
	}, {
		.variable = "variant",
		.dispatch = getvar_variant
	}, {
		.variable = "battery-soc-ok",
		.dispatch = getvar_battery_soc_ok
	}, {
		.variable = "battery-voltage",
		.dispatch = getvar_battery_voltage
	}, {
		.variable = "erase-block-size",
		.dispatch = getvar_block_size
	}, {
		.variable = "logical-block-size",
		.dispatch = getvar_block_size
	}, {
		.variable = "secure",
		.dispatch = getvar_secure
	}, {
		.variable = "unlocked",
		.dispatch = getvar_unlocked
	}, {
		.variable = "is-userspace",
		.dispatch = getvar_is_userspace
	}, {
		.variable = "is-logical",
		.dispatch = getvar_is_logical
	}, {
		.variable = "super-partition-name",
		.dispatch = getvar_super_partition_name
	}, {
		.variable = "downloadsize",
		.dispatch = getvar_downloadsize
	}, {
		.variable = "max-download-size",
		.dispatch = getvar_downloadsize
	}, {
		.variable = "serialno",
		.dispatch = getvar_serialno
	}, {
		.variable = "version-baseband",
		.dispatch = getvar_version_baseband
	}, {
		.variable = "product",
		.dispatch = getvar_product
	}, {
		.variable = "current-slot",
		.dispatch = getvar_current_slot
	}, {
		.variable = "slot-count",
		.dispatch = getvar_slot_count
	}, {
		.variable = "slot-suffixes",
		.dispatch = getvar_slot_suffixes
	}, {
		.variable = "has_slot",
		.dispatch = getvar_has_slot
#if CONFIG_IS_ENABLED(FASTBOOT_FLASH_MMC)
	}, {
		.variable = "partition-type",
		.dispatch = getvar_partition_type
#endif
#if CONFIG_IS_ENABLED(FASTBOOT_FLASH)
	}, {
		.variable = "partition-size",
		.dispatch = getvar_partition_size
#endif
	}
};

static void getvar_version(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_response("INFOversion: ", response, "%s", FASTBOOT_VERSION);
	else
		fastboot_okay(FASTBOOT_VERSION, response);
}

static void getvar_bootloader_version(char *var_parameter, char *response)
{
	if (busy_flag == 1) {
		fastboot_response("INFOversion-bootloader: ", response, "%s", U_BOOT_VERSION);
	} else
		fastboot_okay(U_BOOT_VERSION, response);
}

static void getvar_hw_revision(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("hw-revision: 0", response);
	else
		fastboot_okay("0", response);
}

static void getvar_off_mode_charge(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("off-mode-charge: 0", response);
	else
		fastboot_okay("0", response);
}

static void getvar_variant(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("variant: US", response);
	else
		fastboot_okay("US", response);
}

static void getvar_battery_soc_ok(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("battery-soc-ok: yes", response);
	else
		fastboot_okay("yes", response);
}

static void getvar_battery_voltage(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("battery-voltage: 4", response);
	else
		fastboot_okay("4", response);
}

static void getvar_block_size(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("block-size: 2000", response);
	else
		fastboot_okay("2000", response);
}

static void getvar_secure(char *var_parameter, char *response)
{
	if (check_lock()) {
		if (busy_flag == 1)
			fastboot_busy("secure: yes", response);
		else
			fastboot_okay("yes", response);
	} else {
		if (busy_flag == 1)
			fastboot_busy("secure: no", response);
		else
			fastboot_okay("no", response);
	}
}

static void getvar_unlocked(char *var_parameter, char *response)
{
	if (check_lock()) {
		if (busy_flag == 1)
			fastboot_busy("secure: no", response);
		else
			fastboot_okay("no", response);
	} else {
		if (busy_flag == 1)
			fastboot_busy("secure: yes", response);
		else
			fastboot_okay("yes", response);
	}
}

static void getvar_is_userspace(char *var_parameter, char *response)
{
	if (dynamic_partition) {
		if (busy_flag == 1)
			fastboot_busy("is-userspace: no", response);
		else
			fastboot_okay("no", response);
	} else {
		if (busy_flag == 1)
			fastboot_busy("is-userspace: do not use dynamic", response);
		else
			fastboot_fail("do not use dynamic", response);
	}
}

static void getvar_super_partition_name(char *var_parameter, char *response)
{
	char *slot_name;
	slot_name = env_get("slot-suffixes");
	char name[64];
	if (has_boot_slot == 0) {
		strncpy(name, "super-partition-name: super", 64);
	} else {
		printf("slot-suffixes: %s\n", slot_name);
		if (strcmp(slot_name, "0") == 0) {
			strncpy(name, "super-partition-name: super_a", 64);
		} else if (strcmp(slot_name, "1") == 0) {
			strncpy(name, "super-partition-name: super_b", 64);
		}
	}
	if (busy_flag == 1)
		fastboot_busy(name, response);
	else
		fastboot_okay(name, response);
}

static void getvar_is_logical(char *var_parameter, char *response)
{
	if (!dynamic_partition) {
		if (busy_flag == 1)
			fastboot_response("INFOis_logical:", response, "%s: no", var_parameter);
		else
			fastboot_okay("no", response);
	} else {
		if (busy_flag == 1)
			fastboot_response("INFOis_logical:", response, "%s: yes", var_parameter);
		else
			fastboot_fail("yes", response);
	}
}

static void getvar_slot_count(char *var_parameter, char *response)
{
	if (has_boot_slot == 1) {
		if (busy_flag == 1)
			fastboot_busy("slot-count: 2", response);
		else
			fastboot_okay("2", response);
	}
	else {
		if (busy_flag == 1)
			fastboot_busy("slot-count: 0", response);
		else
			fastboot_okay("0", response);
	}
}

static void getvar_downloadsize(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_response("INFOdownloadsize: ", response, "0x%08x", fastboot_buf_size);
	else
		fastboot_response("OKAY", response, "0x%08x", fastboot_buf_size);
}

static void getvar_serialno(char *var_parameter, char *response)
{
	const char *tmp = env_get("serial#");

	if (busy_flag == 1) {
		if (tmp)
			fastboot_response("INFOserialno: ", response, "%s", tmp);
		else
			fastboot_busy("serialno: Value not set", response);
	} else {
		if (tmp)
			fastboot_okay(tmp, response);
		else
			fastboot_fail("Value not set", response);
	}
}

static void getvar_version_baseband(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("version-baseband: N/A", response);
	else
		fastboot_okay("N/A", response);
}

static void getvar_product(char *var_parameter, char *response)
{
	const char *board = env_get("board");

	if (busy_flag == 1) {
		if (board)
			fastboot_response("INFOproduct: ", response, "%s", board);
		else
			fastboot_busy("product: Board not set", response);
	} else {
		if (board)
			fastboot_okay(board, response);
		else
			fastboot_fail("Board not set", response);
	}
}

static void getvar_current_slot(char *var_parameter, char *response)
{
	/* A/B not implemented, for now always return _a */
	if (busy_flag == 1)
		fastboot_busy("current-slot: _a", response);
	else
		fastboot_okay("_a", response);
}

static void getvar_slot_suffixes(char *var_parameter, char *response)
{
	if (busy_flag == 1)
		fastboot_busy("slot-suffixes: _a,_b", response);
	else
		fastboot_okay("_a,_b", response);
}

static void getvar_has_slot(char *part_name, char *response)
{
	if (has_boot_slot == 0) {
		if (busy_flag == 1)
			fastboot_response("INFOhas-slot:", response, "%s: no", part_name);
		else
			fastboot_okay("no", response);
	} else {
		if ((strcmp(part_name, "system") == 0) || (strcmp(part_name, "vendor") == 0)
			|| (strcmp(part_name, "odm") == 0) || (strcmp(part_name, "product") == 0)
			|| (strcmp(part_name, "system_ext") == 0) || (strcmp(part_name, "dtbo") == 0)
			|| (strcmp(part_name, "metadata") == 0) || (strcmp(part_name, "vbmeta") == 0)){
			if (busy_flag == 1)
				fastboot_response("INFOhas-slot:", response, "%s: yes", part_name);
			else
				fastboot_okay("yes", response);
		} else {
			if (busy_flag == 1)
				fastboot_response("INFOhas-slot:", response, "%s: no", part_name);
			else
				fastboot_okay("no", response);
		}
	}
}

#if CONFIG_IS_ENABLED(FASTBOOT_FLASH)
static void getvar_partition_type(char *part_name, char *response)
{
	/*int r;
	struct blk_desc *dev_desc;
	disk_partition_t part_info;

	r = fastboot_mmc_get_part_info(part_name, &dev_desc, &part_info,
				       response);
	if (r >= 0) {
		r = fs_set_blk_dev_with_part(dev_desc, r);
		if (r < 0) {
			if (busy_flag == 1)
				fastboot_response("INFOpartition-type:", response, "%s: failed to set partition", part_name);
			else
				fastboot_fail("failed to set partition", response);
		} else {
			if (busy_flag == 1)
				fastboot_busy(fs_get_type_name(), response);
			else
				fastboot_okay(fs_get_type_name(), response);
		}
	}*/
	if ((strcmp(part_name, "system") == 0) || (strcmp(part_name, "vendor") == 0)
			|| (strcmp(part_name, "odm") == 0) || (strcmp(part_name, "product") == 0)
			|| (strcmp(part_name, "system_ext") == 0) || (strcmp(part_name, "dtbo") == 0)
			|| (strcmp(part_name, "metadata") == 0) || (strcmp(part_name, "vbmeta") == 0)
			|| (strcmp(part_name, "data") == 0) || (strcmp(part_name, "userdata") == 0)
			|| (strcmp(part_name, "cache") == 0)){
		if (busy_flag == 1)
			fastboot_response("INFOpartition-type:", response, "%s: ext4", part_name);
		else
			fastboot_okay("ext4", response);
	} else {
		if (busy_flag == 1)
			fastboot_response("INFOpartition-type:", response, "%s: raw", part_name);
		else
			fastboot_okay("raw", response);
	}
}

static void getvar_partition_size(char *part_name, char *response)
{
	int r;
	size_t size;
	char name[32];

	if (strcmp(part_name, "userdata") == 0)
		strncpy(name, "data", 4);
	else
		strncpy(name, part_name, 32);

#if CONFIG_IS_ENABLED(FASTBOOT_FLASH_MMC)
	struct blk_desc *dev_desc;
	disk_partition_t part_info;

	r = fastboot_mmc_get_part_info(name, &dev_desc, &part_info,
				       response);
	if (r >= 0)
		size = part_info.size * 512;
#endif
#if CONFIG_IS_ENABLED(FASTBOOT_FLASH_NAND)
	struct part_info *part_info;

	r = fastboot_nand_get_part_info(name, &part_info, response);
	if (r >= 0)
		size = part_info->size * 512;
#endif
	if (r >= 0) {
		if (busy_flag == 1) {
			char name[64];
			strncpy(name, "INFOpartition-size:", 64);
			strcat(name, part_name);
			strcat(name, ": ");
			fastboot_response(name, response, "0x%016zx", size);
		}
		else
			fastboot_response("OKAY", response, "0x%016zx", size);
	}
}
#endif

/**
 * fastboot_getvar() - Writes variable indicated by cmd_parameter to response.
 *
 * @cmd_parameter: Pointer to command parameter
 * @response: Pointer to fastboot response buffer
 *
 * Look up cmd_parameter first as an environment variable of the form
 * fastboot.<cmd_parameter>, if that exists return use its value to set
 * response.
 *
 * Otherwise lookup the name of variable and execute the appropriate
 * function to return the requested value.
 */
void fastboot_getvar(char *cmd_parameter, char *response)
{
	if (!cmd_parameter) {
		fastboot_fail("missing var", response);
	} else {
#define FASTBOOT_ENV_PREFIX	"fastboot."
		int i;
		char *var_parameter = cmd_parameter;
		char envstr[FASTBOOT_RESPONSE_LEN];
		const char *s;

		snprintf(envstr, sizeof(envstr) - 1,
			 FASTBOOT_ENV_PREFIX "%s", cmd_parameter);
		s = env_get(envstr);
		if (s) {
			fastboot_response("OKAY", response, "%s", s);
			return;
		}

		strsep(&var_parameter, ":");
		for (i = 0; i < ARRAY_SIZE(getvar_dispatch); ++i) {
			if (!strcmp(getvar_dispatch[i].variable,
				    cmd_parameter)) {
				getvar_dispatch[i].dispatch(var_parameter,
							    response);
				return;
			}
		}
		pr_warn("WARNING: unknown variable: %s\n", cmd_parameter);
		fastboot_fail("Variable not implemented", response);
	}
}
