/*
 * Copyright 2016 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef FSL_MMDC_H
#define FSL_MMDC_H

#define CONFIG_SYS_MMDC_CORE_ODT_TIMING		0x12554000
#define CONFIG_SYS_MMDC_CORE_TIMING_CFG_0	0xbabf7954
#define CONFIG_SYS_MMDC_CORE_TIMING_CFG_1	0xff328f64
#define CONFIG_SYS_MMDC_CORE_TIMING_CFG_2	0x01ff00db

#define CONFIG_SYS_MMDC_CORE_MISC		0x00001680
#define CONFIG_SYS_MMDC_PHY_MEASURE_UNIT	0x00000800
#define CONFIG_SYS_MMDC_CORE_RDWR_CMD_DELAY	0x00002000
#define CONFIG_SYS_MMDC_PHY_ODT_CTRL		0x0000022a

#define CONFIG_SYS_MMDC_CORE_OUT_OF_RESET_DELAY	0x00bf1023

#define CONFIG_SYS_MMDC_CORE_ADDR_PARTITION	0x0000007f

#define CONFIG_SYS_MMDC_PHY_ZQ_HW_CTRL		0xa1390003

#define	FORCE_ZQ_AUTO_CALIBRATION		(0x1 << 16)

/* PHY Write Leveling Configuration and Error Status (MPWLGCR) */
#define WR_LVL_HW_EN				0x00000001

/* PHY Pre-defined Compare and CA delay-line Configuration (MPPDCMPR2) */
#define MPR_COMPARE_EN				0x00000001

#define CONFIG_SYS_MMDC_PHY_RD_DLY_LINES_CFG	0x40404040

/* MMDC PHY Read DQS gating control register 0 (MPDGCTRL0) */
#define AUTO_RD_DQS_GATING_CALIBRATION_EN	0x10000000

/* MMDC PHY Read Delay HW Calibration Control Register (MPRDDLHWCTL) */
#define AUTO_RD_CALIBRATION_EN			0x00000010

#define CONFIG_SYS_MMDC_CORE_PWR_DOWN_CTRL	0x00030035

#define CONFIG_SYS_MMDC_CORE_PWR_SAV_CTRL_STAT	0x00001067

#define CONFIG_SYS_MMDC_CORE_REFRESH_CTL	0x103e8000

#define START_REFRESH				0x00000001

/* MMDC Core Special Command Register (MDSCR) */
#define CMD_ADDR_MSB_MR_OP(x)   (x << 24)

#define  CMD_ADDR_LSB_MR_ADDR(x)    (x << 16)

#define DISABLE_CFG_REQ		0x0
#define CONFIGURATION_REQ	(0x1  << 15)
#define WL_EN			(0x1  << 9)

#define	CMD_NORMAL		(0x0 << 4)
#define	CMD_PRECHARGE		(0x1 << 4)
#define	CMD_AUTO_REFRESH	(0x2 << 4)
#define	CMD_LOAD_MODE_REG	(0x3 << 4)
#define	CMD_ZQ_CALIBRATION	(0x4 << 4)
#define	CMD_PRECHARGE_BANK_OPEN	(0x5 << 4)
#define	CMD_MRR			(0x6 << 4)

#define CMD_BANK_ADDR_0		0x0
#define CMD_BANK_ADDR_1		0x1
#define CMD_BANK_ADDR_2		0x2
#define CMD_BANK_ADDR_3		0x3
#define CMD_BANK_ADDR_4		0x4
#define CMD_BANK_ADDR_5		0x5
#define CMD_BANK_ADDR_6		0x6
#define CMD_BANK_ADDR_7		0x7

/* MMDC Registers */
struct mmdc_p_regs {
	u32 mdctl;
	u32 mdpdc;
	u32 mdotc;
	u32 mdcfg0;
	u32 mdcfg1;
	u32 mdcfg2;
	u32 mdmisc;
	u32 mdscr;
	u32 mdref;
	u32 res1[2];
	u32 mdrwd;
	u32 mdor;
	u32 mdmrr;
	u32 mdcfg3lp;
	u32 mdmr4;
	u32 mdasp;
	u32 res2[239];
	u32 maarcr;
	u32 mapsr;
	u32 maexidr0;
	u32 maexidr1;
	u32 madpcr0;
	u32 madpcr1;
	u32 madpsr0;
	u32 madpsr1;
	u32 madpsr2;
	u32 madpsr3;
	u32 madpsr4;
	u32 madpsr5;
	u32 masbs0;
	u32 masbs1;
	u32 res3[2];
	u32 magenp;
	u32 res4[239];
	u32 mpzqhwctrl;
	u32 mpzqswctrl;
	u32 mpwlgcr;
	u32 mpwldectrl0;
	u32 mpwldectrl1;
	u32 mpwldlst;
	u32 mpodtctrl;
	u32 mprddqby0dl;
	u32 mprddqby1dl;
	u32 mprddqby2dl;
	u32 mprddqby3dl;
	u32 res5[4];
	u32 mpdgctrl0;
	u32 mpdgctrl1;
	u32 mpdgdlst0;
	u32 mprddlctl;
	u32 mprddlst;
	u32 mpwrdlctl;
	u32 mpwrdlst;
	u32 mpsdctrl;
	u32 mpzqlp2ctl;
	u32 mprddlhwctl;
	u32 mpwrdlhwctl;
	u32 mprddlhwst0;
	u32 mprddlhwst1;
	u32 mpwrdlhwst0;
	u32 mpwrdlhwst1;
	u32 mpwlhwerr;
	u32 mpdghwst0;
	u32 mpdghwst1;
	u32 mpdghwst2;
	u32 mpdghwst3;
	u32 mppdcmpr1;
	u32 mppdcmpr2;
	u32 mpswdar0;
	u32 mpswdrdr0;
	u32 mpswdrdr1;
	u32 mpswdrdr2;
	u32 mpswdrdr3;
	u32 mpswdrdr4;
	u32 mpswdrdr5;
	u32 mpswdrdr6;
	u32 mpswdrdr7;
	u32 mpmur0;
	u32 mpwrcadl;
	u32 mpdccr;
};

#endif /* FSL_MMDC_H */
