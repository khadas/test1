/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2016-2017 Intel Corporation
 */

#ifndef _RESET_MANAGER_ARRIA10_H_
#define _RESET_MANAGER_ARRIA10_H_

#include <dt-bindings/reset/altr,rst-mgr-a10.h>

void socfpga_watchdog_disable(void);
void socfpga_reset_deassert_noc_ddr_scheduler(void);
int socfpga_is_wdt_in_reset(void);
void socfpga_emac_manage_reset(ulong emacbase, u32 state);
int socfpga_reset_deassert_bridges_handoff(void);
void socfpga_reset_assert_fpga_connected_peripherals(void);
void socfpga_reset_deassert_osc1wd0(void);
void socfpga_reset_uart(int assert);
int socfpga_bridges_reset(void);

struct socfpga_reset_manager {
	u32	stat;
	u32	ramstat;
	u32	miscstat;
	u32	ctrl;
	u32	hdsken;
	u32	hdskreq;
	u32	hdskack;
	u32	counts;
	u32	mpumodrst;
	u32	per0modrst;
	u32	per1modrst;
	u32	brgmodrst;
	u32	sysmodrst;
	u32	coldmodrst;
	u32	nrstmodrst;
	u32	dbgmodrst;
	u32	mpuwarmmask;
	u32	per0warmmask;
	u32	per1warmmask;
	u32	brgwarmmask;
	u32	syswarmmask;
	u32	nrstwarmmask;
	u32	l3warmmask;
	u32	tststa;
	u32	tstscratch;
	u32	hdsktimeout;
	u32	hmcintr;
	u32	hmcintren;
	u32	hmcintrens;
	u32	hmcintrenr;
	u32	hmcgpout;
	u32	hmcgpin;
};

/*
 * SocFPGA Arria10 reset IDs, bank mapping is as follows:
 * 0 ... mpumodrst
 * 1 ... per0modrst
 * 2 ... per1modrst
 * 3 ... brgmodrst
 * 4 ... sysmodrst
 */
#define RSTMGR_EMAC0		RSTMGR_DEFINE(1, 0)
#define RSTMGR_EMAC1		RSTMGR_DEFINE(1, 1)
#define RSTMGR_EMAC2		RSTMGR_DEFINE(1, 2)
#define RSTMGR_NAND		RSTMGR_DEFINE(1, 5)
#define RSTMGR_QSPI		RSTMGR_DEFINE(1, 6)
#define RSTMGR_SDMMC		RSTMGR_DEFINE(1, 7)
#define RSTMGR_DMA		RSTMGR_DEFINE(1, 16)
#define RSTMGR_SPIM0		RSTMGR_DEFINE(1, 17)
#define RSTMGR_SPIM1		RSTMGR_DEFINE(1, 18)
#define RSTMGR_L4WD0		RSTMGR_DEFINE(2, 0)
#define RSTMGR_L4WD1		RSTMGR_DEFINE(2, 1)
#define RSTMGR_L4SYSTIMER0	RSTMGR_DEFINE(2, 2)
#define RSTMGR_L4SYSTIMER1	RSTMGR_DEFINE(2, 3)
#define RSTMGR_SPTIMER0		RSTMGR_DEFINE(2, 4)
#define RSTMGR_SPTIMER1		RSTMGR_DEFINE(2, 5)
#define RSTMGR_UART0		RSTMGR_DEFINE(2, 16)
#define RSTMGR_UART1		RSTMGR_DEFINE(2, 17)
#define RSTMGR_DDRSCH		RSTMGR_DEFINE(3, 6)

#define ALT_RSTMGR_CTL_SWWARMRSTREQ_SET_MSK	BIT(1)
#define ALT_RSTMGR_PER0MODRST_EMAC0_SET_MSK	BIT(0)
#define ALT_RSTMGR_PER0MODRST_EMAC1_SET_MSK	BIT(1)
#define ALT_RSTMGR_PER0MODRST_EMAC2_SET_MSK	BIT(2)
#define ALT_RSTMGR_PER0MODRST_USB0_SET_MSK	BIT(3)
#define ALT_RSTMGR_PER0MODRST_USB1_SET_MSK	BIT(4)
#define ALT_RSTMGR_PER0MODRST_NAND_SET_MSK	BIT(5)
#define ALT_RSTMGR_PER0MODRST_QSPI_SET_MSK	BIT(6)
#define ALT_RSTMGR_PER0MODRST_SDMMC_SET_MSK	BIT(7)
#define ALT_RSTMGR_PER0MODRST_EMACECC0_SET_MSK	BIT(8)
#define ALT_RSTMGR_PER0MODRST_EMACECC1_SET_MSK	BIT(9)
#define ALT_RSTMGR_PER0MODRST_EMACECC2_SET_MSK	BIT(10)
#define ALT_RSTMGR_PER0MODRST_USBECC0_SET_MSK	BIT(11)
#define ALT_RSTMGR_PER0MODRST_USBECC1_SET_MSK	BIT(12)
#define ALT_RSTMGR_PER0MODRST_NANDECC_SET_MSK	BIT(13)
#define ALT_RSTMGR_PER0MODRST_QSPIECC_SET_MSK	BIT(14)
#define ALT_RSTMGR_PER0MODRST_SDMMCECC_SET_MSK	BIT(15)
#define ALT_RSTMGR_PER0MODRST_DMA_SET_MSK	BIT(16)
#define ALT_RSTMGR_PER0MODRST_SPIM0_SET_MSK	BIT(17)
#define ALT_RSTMGR_PER0MODRST_SPIM1_SET_MSK	BIT(18)
#define ALT_RSTMGR_PER0MODRST_SPIS0_SET_MSK	BIT(19)
#define ALT_RSTMGR_PER0MODRST_SPIS1_SET_MSK	BIT(20)
#define ALT_RSTMGR_PER0MODRST_DMAECC_SET_MSK	BIT(21)
#define ALT_RSTMGR_PER0MODRST_EMACPTP_SET_MSK	BIT(22)
#define ALT_RSTMGR_PER0MODRST_DMAIF0_SET_MSK	BIT(24)
#define ALT_RSTMGR_PER0MODRST_DMAIF1_SET_MSK	BIT(25)
#define ALT_RSTMGR_PER0MODRST_DMAIF2_SET_MSK	BIT(26)
#define ALT_RSTMGR_PER0MODRST_DMAIF3_SET_MSK	BIT(27)
#define ALT_RSTMGR_PER0MODRST_DMAIF4_SET_MSK	BIT(28)
#define ALT_RSTMGR_PER0MODRST_DMAIF5_SET_MSK	BIT(29)
#define ALT_RSTMGR_PER0MODRST_DMAIF6_SET_MSK	BIT(30)
#define ALT_RSTMGR_PER0MODRST_DMAIF7_SET_MSK	BIT(31)

#define ALT_RSTMGR_PER1MODRST_WD0_SET_MSK	BIT(0)
#define ALT_RSTMGR_PER1MODRST_WD1_SET_MSK	BIT(1)
#define ALT_RSTMGR_PER1MODRST_L4SYSTMR0_SET_MSK	BIT(2)
#define ALT_RSTMGR_PER1MODRST_L4SYSTMR1_SET_MSK	BIT(3)
#define ALT_RSTMGR_PER1MODRST_SPTMR0_SET_MSK	BIT(4)
#define ALT_RSTMGR_PER1MODRST_SPTMR1_SET_MSK	BIT(5)
#define ALT_RSTMGR_PER1MODRST_I2C0_SET_MSK	BIT(8)
#define ALT_RSTMGR_PER1MODRST_I2C1_SET_MSK	BIT(9)
#define ALT_RSTMGR_PER1MODRST_I2C2_SET_MSK	BIT(10)
#define ALT_RSTMGR_PER1MODRST_I2C3_SET_MSK	BIT(11)
#define ALT_RSTMGR_PER1MODRST_I2C4_SET_MSK	BIT(12)
#define ALT_RSTMGR_PER1MODRST_UART0_SET_MSK	BIT(16)
#define ALT_RSTMGR_PER1MODRST_UART1_SET_MSK	BIT(17)
#define ALT_RSTMGR_PER1MODRST_GPIO0_SET_MSK	BIT(24)
#define ALT_RSTMGR_PER1MODRST_GPIO1_SET_MSK	BIT(25)
#define ALT_RSTMGR_PER1MODRST_GPIO2_SET_MSK	BIT(26)

#define ALT_RSTMGR_BRGMODRST_H2F_SET_MSK	BIT(0)
#define ALT_RSTMGR_BRGMODRST_LWH2F_SET_MSK	BIT(1)
#define ALT_RSTMGR_BRGMODRST_F2H_SET_MSK	BIT(2)
#define ALT_RSTMGR_BRGMODRST_F2SSDRAM0_SET_MSK	BIT(3)
#define ALT_RSTMGR_BRGMODRST_F2SSDRAM1_SET_MSK	BIT(4)
#define ALT_RSTMGR_BRGMODRST_F2SSDRAM2_SET_MSK	BIT(5)
#define ALT_RSTMGR_BRGMODRST_DDRSCH_SET_MSK	BIT(6)

#define ALT_RSTMGR_HDSKEN_SDRSELFREFEN_SET_MSK	BIT(0)
#define ALT_RSTMGR_HDSKEN_FPGAMGRHSEN_SET_MSK	BIT(1)
#define ALT_RSTMGR_HDSKEN_FPGAHSEN_SET_MSK	BIT(2)
#define ALT_RSTMGR_HDSKEN_ETRSTALLEN_SET_MSK	BIT(3)

#endif /* _RESET_MANAGER_ARRIA10_H_ */
