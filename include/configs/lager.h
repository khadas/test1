/*
 * include/configs/lager.h
 *     This file is lager board configuration.
 *
 * Copyright (C) 2013, 2014 Renesas Electronics Corporation
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef __LAGER_H
#define __LAGER_H

#undef DEBUG
#define CONFIG_R8A7790
#define CONFIG_ARCH_RMOBILE_BOARD_STRING "Lager"

#include "rcar-gen2-common.h"

#if defined(CONFIG_ARCH_RMOBILE_EXTRAM_BOOT)
#define CONFIG_SYS_TEXT_BASE	0xB0000000
#else
#define CONFIG_SYS_TEXT_BASE	0xE8080000
#endif

/* STACK */
#if defined(CONFIGF_RMOBILE_EXTRAM_BOOT)
#define CONFIG_SYS_INIT_SP_ADDR		0xB003FFFC
#else
#define CONFIG_SYS_INIT_SP_ADDR		0xE827FFFC
#endif
#define STACK_AREA_SIZE			0xC000
#define LOW_LEVEL_MERAM_STACK	\
		(CONFIG_SYS_INIT_SP_ADDR + STACK_AREA_SIZE - 4)

/* MEMORY */
#define RCAR_GEN2_SDRAM_BASE		0x40000000
#define RCAR_GEN2_SDRAM_SIZE		(2048u * 1024 * 1024)
#define RCAR_GEN2_UBOOT_SDRAM_SIZE	(512 * 1024 * 1024)

/* SCIF */

/* SPI */
#define CONFIG_SPI
#define CONFIG_SH_QSPI

/* SH Ether */
#define CONFIG_SH_ETHER
#define CONFIG_SH_ETHER_USE_PORT	0
#define CONFIG_SH_ETHER_PHY_ADDR	0x1
#define CONFIG_SH_ETHER_PHY_MODE PHY_INTERFACE_MODE_RMII
#define CONFIG_SH_ETHER_ALIGNE_SIZE	64
#define CONFIG_SH_ETHER_CACHE_WRITEBACK
#define CONFIG_SH_ETHER_CACHE_INVALIDATE
#define CONFIG_BITBANGMII
#define CONFIG_BITBANGMII_MULTI

/* I2C */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_RCAR
#define CONFIG_SYS_RCAR_I2C0_SPEED	400000
#define CONFIG_SYS_RCAR_I2C1_SPEED	400000
#define CONFIG_SYS_RCAR_I2C2_SPEED	400000
#define CONFIG_SYS_RCAR_I2C3_SPEED	400000
#define CONFIF_SYS_RCAR_I2C_NUM_CONTROLLERS	4

#define CONFIG_SYS_I2C_POWERIC_ADDR 0x58 /* da9063 */

/* Board Clock */
#define RMOBILE_XTAL_CLK	20000000u
#define CONFIG_SYS_CLK_FREQ	RMOBILE_XTAL_CLK
#define CONFIG_SH_TMU_CLK_FREQ	(CONFIG_SYS_CLK_FREQ / 2) /* EXT / 2 */
#define CONFIG_PLL1_CLK_FREQ	(CONFIG_SYS_CLK_FREQ * 156 / 2)
#define CONFIG_PLL1_DIV2_CLK_FREQ	(CONFIG_PLL1_CLK_FREQ / 2)
#define CONFIG_MP_CLK_FREQ	(CONFIG_PLL1_DIV2_CLK_FREQ / 15)
#define CONFIG_HP_CLK_FREQ	(CONFIG_PLL1_CLK_FREQ / 12)

#define CONFIG_SYS_TMU_CLK_DIV	4

/* USB */
#define CONFIG_USB_EHCI_RMOBILE
#define CONFIG_USB_MAX_CONTROLLER_COUNT	3

/* MMC */
#define CONFIG_SH_MMCIF
#define CONFIG_SH_MMCIF_ADDR		0xEE220000
#define CONFIG_SH_MMCIF_CLK		97500000

/* Module stop status bits */
/* INTC-RT */
#define CONFIG_SMSTP0_ENA	0x00400000
/* MSIF */
#define CONFIG_SMSTP2_ENA	0x00002000
/* INTC-SYS, IRQC */
#define CONFIG_SMSTP4_ENA	0x00000180
/* SCIF0 */
#define CONFIG_SMSTP7_ENA	0x00200000

/* SDHI */
#define CONFIG_SH_SDHI_FREQ	97500000

#endif	/* __LAGER_H */
