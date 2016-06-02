/*
 * Copyright 2013 Broadcom Corporation.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ARCH_BCM235XX_SYSMAP_H

#define BSC1_BASE_ADDR		0x3e016000
#define BSC2_BASE_ADDR		0x3e017000
#define BSC3_BASE_ADDR		0x3e018000
#define GPIO2_BASE_ADDR		0x35003000
#define HSOTG_BASE_ADDR		0x3f120000
#define HSOTG_CTRL_BASE_ADDR	0x3f130000
#define KONA_MST_CLK_BASE_ADDR	0x3f001000
#define KONA_SLV_CLK_BASE_ADDR	0x3e011000
#define PMU_BSC_BASE_ADDR	0x3500d000
#define SDIO1_BASE_ADDR		0x3f180000
#define SDIO2_BASE_ADDR		0x3f190000
#define SDIO3_BASE_ADDR		0x3f1a0000
#define SDIO4_BASE_ADDR		0x3f1b0000
#define TIMER_BASE_ADDR		0x3e00d000

#define HSOTG_DCTL_OFFSET					0x00000804
#define    HSOTG_DCTL_SFTDISCON_MASK				0x00000002

#define HSOTG_CTRL_PHY_P1CTL_OFFSET				0x00000008
#define    HSOTG_CTRL_PHY_P1CTL_SOFT_RESET_MASK			0x00000002
#define    HSOTG_CTRL_PHY_P1CTL_NON_DRIVING_MASK		0x00000001

#endif
