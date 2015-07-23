/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * Header file for the Marvell's Feroceon CPU core.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _MVEBU_SOC_H
#define _MVEBU_SOC_H

#define SOC_MV78460_ID		0x7846
#define SOC_88F6810_ID		0x6810
#define SOC_88F6820_ID		0x6820
#define SOC_88F6828_ID		0x6828

/* A38x revisions */
#define MV_88F68XX_Z1_ID	0x0
#define MV_88F68XX_A0_ID	0x4

/* TCLK Core Clock definition */
#ifndef CONFIG_SYS_TCLK
#define CONFIG_SYS_TCLK		250000000	/* 250MHz */
#endif

/* SOC specific definations */
#define INTREG_BASE		0xd0000000
#define INTREG_BASE_ADDR_REG	(INTREG_BASE + 0x20080)
#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SYS_MVEBU_DDR_A38X)
/*
 * On A38x switching the regs base address without running from
 * SDRAM doesn't seem to work. So let the SPL still use the
 * default base address and switch to the new address in the
 * main u-boot later.
 */
#define SOC_REGS_PHY_BASE	0xd0000000
#else
#define SOC_REGS_PHY_BASE	0xf1000000
#endif
#define MVEBU_REGISTER(x)	(SOC_REGS_PHY_BASE + x)

#define MVEBU_SDRAM_SCRATCH	(MVEBU_REGISTER(0x01504))
#define MVEBU_L2_CACHE_BASE	(MVEBU_REGISTER(0x08000))
#define CONFIG_SYS_PL310_BASE	MVEBU_L2_CACHE_BASE
#define MVEBU_SPI_BASE		(MVEBU_REGISTER(0x10600))
#define MVEBU_TWSI_BASE		(MVEBU_REGISTER(0x11000))
#define MVEBU_UART0_BASE	(MVEBU_REGISTER(0x12000))
#define MVEBU_UART1_BASE	(MVEBU_REGISTER(0x12100))
#define MVEBU_MPP_BASE		(MVEBU_REGISTER(0x18000))
#define MVEBU_GPIO0_BASE	(MVEBU_REGISTER(0x18100))
#define MVEBU_GPIO1_BASE	(MVEBU_REGISTER(0x18140))
#define MVEBU_GPIO2_BASE	(MVEBU_REGISTER(0x18180))
#define MVEBU_SYSTEM_REG_BASE	(MVEBU_REGISTER(0x18200))
#define MVEBU_CPU_WIN_BASE	(MVEBU_REGISTER(0x20000))
#define MVEBU_SDRAM_BASE	(MVEBU_REGISTER(0x20180))
#define MVEBU_TIMER_BASE	(MVEBU_REGISTER(0x20300))
#define MVEBU_EGIGA2_BASE	(MVEBU_REGISTER(0x30000))
#define MVEBU_EGIGA3_BASE	(MVEBU_REGISTER(0x34000))
#define MVEBU_REG_PCIE_BASE	(MVEBU_REGISTER(0x40000))
#define MVEBU_USB20_BASE	(MVEBU_REGISTER(0x58000))
#define MVEBU_EGIGA0_BASE	(MVEBU_REGISTER(0x70000))
#define MVEBU_EGIGA1_BASE	(MVEBU_REGISTER(0x74000))
#define MVEBU_AXP_SATA_BASE	(MVEBU_REGISTER(0xa0000))
#define MVEBU_SATA0_BASE	(MVEBU_REGISTER(0xa8000))
#define MVEBU_SDIO_BASE		(MVEBU_REGISTER(0xd8000))

#define SDRAM_MAX_CS		4
#define SDRAM_ADDR_MASK		0xFF000000

/* MVEBU CPU memory windows */
#define MVCPU_WIN_CTRL_DATA	CPU_WIN_CTRL_DATA
#define MVCPU_WIN_ENABLE	CPU_WIN_ENABLE
#define MVCPU_WIN_DISABLE	CPU_WIN_DISABLE

#endif /* _MVEBU_SOC_H */
