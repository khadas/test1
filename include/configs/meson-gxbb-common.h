/*
 * Configuration for Amlogic Meson GXBB SoCs
 * (C) Copyright 2016 Beniamino Galvani <b.galvani@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MESON_GXBB_COMMON_CONFIG_H
#define __MESON_GXBB_COMMON_CONFIG_H

#define CONFIG_CPU_ARMV8
#define CONFIG_REMAKE_ELF
#define CONFIG_NR_DRAM_BANKS		1
#define CONFIG_ENV_IS_NOWHERE		1
#define CONFIG_ENV_SIZE			0x2000
#define CONFIG_SYS_MAXARGS		32
#define CONFIG_SYS_MALLOC_LEN		(32 << 20)
#define CONFIG_SYS_CBSIZE		1024

#define CONFIG_SYS_SDRAM_BASE		0
#define CONFIG_SYS_TEXT_BASE		0x01000000
#define CONFIG_SYS_INIT_SP_ADDR		0x20000000
#define CONFIG_SYS_LOAD_ADDR		CONFIG_SYS_TEXT_BASE

/* Generic Interrupt Controller Definitions */
#define GICD_BASE			0xc4301000
#define GICC_BASE			0xc4302000

#define CONFIG_CMD_ENV

/* Monitor Command Prompt */
/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_LONGHELP
#define CONFIG_CMDLINE_EDITING

#include <config_distro_defaults.h>

#define BOOT_TARGET_DEVICES(func) \
	func(DHCP, dhcp, na)

#include <config_distro_bootcmd.h>

#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_addr_r=0x01000000\0" \
	"scriptaddr=0x1f000000\0" \
	"kernel_addr_r=0x01080000\0" \
	"pxefile_addr_r=0x01080000\0" \
	"ramdisk_addr_r=0x10000000\0" \
	MESON_FDTFILE_SETTING \
	BOOTENV

#endif /* __MESON_GXBB_COMMON_CONFIG_H */
