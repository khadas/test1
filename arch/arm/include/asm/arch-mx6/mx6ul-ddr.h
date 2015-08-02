/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_ARCH_MX6UL_DDR_H__
#define __ASM_ARCH_MX6UL_DDR_H__

#ifndef CONFIG_MX6UL
#error "wrong CPU"
#endif

#define MX6_IOM_DRAM_DQM0	0x020e0244
#define MX6_IOM_DRAM_DQM1	0x020e0248

#define MX6_IOM_DRAM_RAS	0x020e024c
#define MX6_IOM_DRAM_CAS	0x020e0250
#define MX6_IOM_DRAM_CS0	0x020e0254
#define MX6_IOM_DRAM_CS1	0x020e0258
#define MX6_IOM_DRAM_SDWE_B	0x020e025c
#define MX6_IOM_DRAM_SDODT0	0x020e0260
#define MX6_IOM_DRAM_SDODT1	0x020e0264
#define MX6_IOM_DRAM_SDBA0	0x020e0268
#define MX6_IOM_DRAM_SDBA1	0x020e026c
#define MX6_IOM_DRAM_SDBA2	0x020e0270
#define MX6_IOM_DRAM_SDCKE0	0x020e0274
#define MX6_IOM_DRAM_SDCKE1	0x020e0278
#define MX6_IOM_DRAM_SDCLK_0	0x020e027c
#define MX6_IOM_DRAM_SDQS0	0x020e0280
#define MX6_IOM_DRAM_SDQS1	0x020e0284
#define MX6_IOM_DRAM_RESET	0x020e0288

#define MX6_IOM_GRP_ADDDS	0x020e0490
#define MX6_IOM_DDRMODE_CTL	0x020e0494
#define MX6_IOM_GRP_B0DS	0x020e0498
#define MX6_IOM_GRP_DDRPK	0x020e049c
#define MX6_IOM_GRP_CTLDS	0x020e04a0
#define MX6_IOM_GRP_B1DS	0x020e04a4
#define MX6_IOM_GRP_DDRHYS	0x020e04a8
#define MX6_IOM_GRP_DDRPKE	0x020e04ac
#define MX6_IOM_GRP_DDRMODE	0x020e04b0
#define MX6_IOM_GRP_DDR_TYPE	0x020e04b4

#endif	/*__ASM_ARCH_MX6SX_DDR_H__ */
