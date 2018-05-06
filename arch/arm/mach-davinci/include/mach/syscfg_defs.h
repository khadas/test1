/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011
 * Heiko Schocher, DENX Software Engineering, hs@denx.de.
 */
#ifndef _DV_SYSCFG_DEFS_H_
#define _DV_SYSCFG_DEFS_H_

#ifndef CONFIG_SOC_DA8XX
/* System Control Module register structure for DM365 */
struct dv_sys_module_regs {
	unsigned int	pinmux[5];	/* 0x00 */
	unsigned int	bootcfg;	/* 0x14 */
	unsigned int	arm_intmux;	/* 0x18 */
	unsigned int	edma_evtmux;	/* 0x1C */
	unsigned int	ddr_slew;	/* 0x20 */
	unsigned int	clkout;		/* 0x24 */
	unsigned int	device_id;	/* 0x28 */
	unsigned int	vdac_config;	/* 0x2C */
	unsigned int	timer64_ctl;	/* 0x30 */
	unsigned int	usbbphy_ctl;	/* 0x34 */
	unsigned int	misc;		/* 0x38 */
	unsigned int	mstpri[2];	/* 0x3C */
	unsigned int	vpss_clkctl;	/* 0x44 */
	unsigned int	peri_clkctl;	/* 0x48 */
	unsigned int	deepsleep;	/* 0x4C */
	unsigned int	dft_enable;	/* 0x50 */
	unsigned int	debounce[8];	/* 0x54 */
	unsigned int	vtpiocr;	/* 0x74 */
	unsigned int	pupdctl0;	/* 0x78 */
	unsigned int	pupdctl1;	/* 0x7C */
	unsigned int	hdimcopbt;	/* 0x80 */
	unsigned int	pll0_config;	/* 0x84 */
	unsigned int	pll1_config;	/* 0x88 */
};

#define VPTIO_RDY	(1 << 15)
#define VPTIO_IOPWRDN	(1 << 14)
#define VPTIO_CLRZ	(1 << 13)
#define VPTIO_LOCK	(1 << 7)
#define VPTIO_PWRDN	(1 << 6)

#define VPSS_CLK_CTL_VPSS_CLKMD	(1 << 7)

#define dv_sys_module_regs \
	((struct dv_sys_module_regs *)DAVINCI_SYSTEM_MODULE_BASE)

#endif /* !CONFIG_SOC_DA8XX */
#endif /* _DV_SYSCFG_DEFS_H_ */
