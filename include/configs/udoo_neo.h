/*
 * Copyright 2014-2015 Freescale Semiconductor, Inc.
 * Copyright Jasbir Matharu
 * Copyright 2015 UDOO Team
 *
 * Configuration settings for the UDOO NEO board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <config_distro_defaults.h>
#include "mx6_common.h"

#include "imx6_spl.h"

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(3 * SZ_1M)
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_MXC_UART

/* MMC Configuration */
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR

/* Command definition */
#define CONFIG_MXC_UART_BASE		UART1_BASE
#define CONFIG_SYS_FSL_USDHC_NUM	2
#define CONFIG_SYS_MMC_ENV_DEV		0  /*USDHC2*/

/* Linux only */
#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttymxc0,115200\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_file=undefined\0" \
	"fdt_addr=0x83000000\0" \
	"ip_dyn=yes\0" \
	"mmcdev=0\0" \
	"mmcrootfstype=ext4\0" \
	"mmcautodetect=no\0" \
	"findfdt="\
		"if test $board_name = BASIC; then " \
			"setenv fdt_file imx6sx-udoo-neo-basic.dtb; fi; " \
		"if test $board_name = BASICKS; then " \
			"setenv fdt_file imx6sx-udoo-neo-basic.dtb; fi; " \
		"if test $board_name = FULL; then " \
			"setenv fdt_file imx6sx-udoo-neo-full.dtb; fi; " \
		"if test $board_name = EXTENDED; then " \
			"setenv fdt_file imx6sx-udoo-neo-extended.dtb; fi; " \
		"if test $fdt_file = UNDEFINED; then " \
			"echo WARNING: Could not determine dtb to use; fi; \0" \
	"kernel_addr_r=" __stringify(CONFIG_LOADADDR) "\0" \
	"pxefile_addr_r=" __stringify(CONFIG_LOADADDR) "\0" \
	"ramdisk_addr_r=0x83000000\0" \
	"ramdiskaddr=0x83000000\0" \
	"scriptaddr=" __stringify(CONFIG_LOADADDR) "\0" \
	BOOTENV

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0)

#define CONFIG_BOOTCOMMAND \
	"run findfdt; " \
	"run distro_bootcmd"

#include <config_distro_bootcmd.h>

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x10000)
#define CONFIG_STACKSIZE		SZ_128K

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* Environment organization */
#define CONFIG_ENV_OFFSET		(8 * SZ_64K)
#define CONFIG_ENV_SIZE			SZ_8K
#define CONFIG_ENV_IS_IN_MMC

#endif				/* __CONFIG_H */
