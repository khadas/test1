/*
 * Copyright (c) 2011 The Chromium OS Authors.
 * (C) Copyright 2008
 * Graeme Russ, graeme.russ@gmail.com.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <fdtdec.h>
#include <asm/io.h>
#include <asm/msr.h>
#include <asm/mtrr.h>
#include <asm/arch/sysinfo.h>
#include <asm/arch/timestamp.h>

DECLARE_GLOBAL_DATA_PTR;

int arch_cpu_init(void)
{
	int ret = get_coreboot_info(&lib_sysinfo);
	if (ret != 0) {
		printf("Failed to parse coreboot tables.\n");
		return ret;
	}

	timestamp_init();

	return x86_cpu_init_f();
}

int board_early_init_f(void)
{
	return 0;
}

int print_cpuinfo(void)
{
	return default_print_cpuinfo();
}

int last_stage_init(void)
{
	if (gd->flags & GD_FLG_COLD_BOOT)
		timestamp_add_to_bootstage();

	return 0;
}

void board_final_cleanup(void)
{
	/*
	 * Un-cache the ROM so the kernel has one
	 * more MTRR available.
	 *
	 * Coreboot should have assigned this to the
	 * top available variable MTRR.
	 */
	u8 top_mtrr = (native_read_msr(MTRR_CAP_MSR) & 0xff) - 1;
	u8 top_type = native_read_msr(MTRR_PHYS_BASE_MSR(top_mtrr)) & 0xff;

	/* Make sure this MTRR is the correct Write-Protected type */
	if (top_type == MTRR_TYPE_WRPROT) {
		struct mtrr_state state;

		mtrr_open(&state);
		wrmsrl(MTRR_PHYS_BASE_MSR(top_mtrr), 0);
		wrmsrl(MTRR_PHYS_MASK_MSR(top_mtrr), 0);
		mtrr_close(&state);
	}

	if (!fdtdec_get_config_bool(gd->fdt_blob, "u-boot,no-apm-finalize")) {
		/*
		 * Issue SMI to coreboot to lock down ME and registers
		 * when allowed via device tree
		 */
		printf("Finalizing coreboot\n");
		outb(0xcb, 0xb2);
	}
}

int misc_init_r(void)
{
	return 0;
}

int arch_misc_init(void)
{
	return 0;
}
