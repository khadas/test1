/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * Configuration settings for the SAMSUNG SMDKV310 (EXYNOS4210) board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "exynos4-common.h"

#undef CONFIG_BOARD_COMMON
#undef CONFIG_USB_GADGET
#undef CONFIG_USB_GADGET_S3C_UDC_OTG
#undef CONFIG_USB_GADGET_S3C_UDC_OTG_PHY
#undef CONFIG_CMD_USB_MASS_STORAGE
#undef CONFIG_REVISION_TAG
#undef CONFIG_CMD_THOR_DOWNLOAD
#undef CONFIG_CMD_DFU

/* High Level Configuration Options */
#define CONFIG_EXYNOS4210		1	/* which is a EXYNOS4210 SoC */
#define CONFIG_SMDKV310			1	/* working with SMDKV310*/

/* Mach Type */
#define CONFIG_MACH_TYPE		MACH_TYPE_SMDKV310

#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define CONFIG_SYS_TEXT_BASE		0x43E00000

/* Handling Sleep Mode*/
#define S5P_CHECK_SLEEP			0x00000BAD
#define S5P_CHECK_DIDLE			0xBAD00000
#define S5P_CHECK_LPA			0xABAD0000

/* select serial console configuration */
#define CONFIG_SERIAL1			1	/* use SERIAL 1 */
#define EXYNOS4_DEFAULT_UART_OFFSET	0x010000

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define CONFIG_CMD_PING
#define CONFIG_CMD_ELF
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_NET

/* MMC SPL */
#define CONFIG_SKIP_LOWLEVEL_INIT
#define COPY_BL2_FNPTR_ADDR	0x00002488

#define CONFIG_SPL_TEXT_BASE	0x02021410

#define CONFIG_BOOTCOMMAND	"fatload mmc 0 40007000 uImage; bootm 40007000"

/* Miscellaneous configurable options */
#define CONFIG_SYS_PROMPT		"SMDKV310 # "
#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC2,115200n8\0"
/* memtest works on */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x6000000)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x3E00000)

/* SMDKV310 has 4 bank of DRAM */
#define CONFIG_NR_DRAM_BANKS	4
#define SDRAM_BANK_SIZE		(512UL << 20UL)	/* 512 MB */
#define PHYS_SDRAM_1		CONFIG_SYS_SDRAM_BASE
#define PHYS_SDRAM_1_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_2		(CONFIG_SYS_SDRAM_BASE + SDRAM_BANK_SIZE)
#define PHYS_SDRAM_2_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_3		(CONFIG_SYS_SDRAM_BASE + (2 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_3_SIZE	SDRAM_BANK_SIZE
#define PHYS_SDRAM_4		(CONFIG_SYS_SDRAM_BASE + (3 * SDRAM_BANK_SIZE))
#define PHYS_SDRAM_4_SIZE	SDRAM_BANK_SIZE

/* FLASH and environment organization */
#define CONFIG_IDENT_STRING		" for SMDKC210/V310"

#define CONFIG_CLK_1000_400_200

/* MIU (Memory Interleaving Unit) */
#define CONFIG_MIU_2BIT_INTERLEAVED

#define CONFIG_ENV_IS_IN_MMC		1
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_SIZE			(16 << 10)	/* 16 KB */
#define RESERVE_BLOCK_SIZE		(512)
#define BL1_SIZE			(16 << 10) /*16 K reserved for BL1*/
#define CONFIG_ENV_OFFSET		(RESERVE_BLOCK_SIZE + BL1_SIZE)

#define CONFIG_SPL_LDSCRIPT	"board/samsung/common/exynos-uboot-spl.lds"
#define CONFIG_SPL_MAX_FOOTPRINT	(14 * 1024)

#define CONFIG_SYS_INIT_SP_ADDR		0x02040000

/* U-boot copy size from boot Media to DRAM.*/
#define	COPY_BL2_SIZE		0x80000
#define BL2_START_OFFSET	((CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)/512)
#define BL2_SIZE_BLOC_COUNT	(COPY_BL2_SIZE/512)

/* Ethernet Controllor Driver */
#ifdef CONFIG_CMD_NET
#define CONFIG_SMC911X
#define CONFIG_SMC911X_BASE		0x5000000
#define CONFIG_SMC911X_16_BIT
#define CONFIG_ENV_SROM_BANK		1
#endif /*CONFIG_CMD_NET*/

#endif	/* __CONFIG_H */
