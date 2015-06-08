/*
 * Copyright (C) Marvell International Ltd. and its affiliates
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef _DDR3_HWS_HW_TRAINING_DEF_H
#define _DDR3_HWS_HW_TRAINING_DEF_H

#define SAR_DDR3_FREQ_MASK		0xfe00000
#define SAR_CPU_FAB_GET(cpu, fab)	(((cpu & 0x7) << 21) | \
					 ((fab & 0xf) << 24))

#define MAX_CS				4

#define MIN_DIMM_ADDR			0x50
#define FAR_END_DIMM_ADDR		0x50
#define MAX_DIMM_ADDR			0x60

#define SDRAM_CS_SIZE			0xfffffff
#define SDRAM_CS_BASE			0x0
#define SDRAM_DIMM_SIZE			0x80000000

#define CPU_CONFIGURATION_REG(id)	(0x21800 + (id * 0x100))
#define CPU_MRVL_ID_OFFSET		0x10
#define SAR1_CPU_CORE_MASK		0x00000018
#define SAR1_CPU_CORE_OFFSET		3

#define NEW_FABRIC_TWSI_ADDR		0x4e
#ifdef DB_784MP_GP
#define BUS_WIDTH_ECC_TWSI_ADDR		0x4e
#else
#define BUS_WIDTH_ECC_TWSI_ADDR		0x4f
#endif
#define MV_MAX_DDR3_STATIC_SIZE		50
#define MV_DDR3_MODES_NUMBER		30

#define RESUME_RL_PATTERNS_ADDR		0xfe0000
#define RESUME_RL_PATTERNS_SIZE		0x100
#define RESUME_TRAINING_VALUES_ADDR	(RESUME_RL_PATTERNS_ADDR + \
					 RESUME_RL_PATTERNS_SIZE)
#define RESUME_TRAINING_VALUES_MAX	0xcd0
#define BOOT_INFO_ADDR			(RESUME_RL_PATTERNS_ADDR + 0x1000)
#define CHECKSUM_RESULT_ADDR		(BOOT_INFO_ADDR + 0x1000)
#define NUM_OF_REGISTER_ADDR		(CHECKSUM_RESULT_ADDR + 4)
#define SUSPEND_MAGIC_WORD		0xdeadb002
#define REGISTER_LIST_END		0xffffffff

/* MISC */
#define INTER_REGS_BASE			SOC_REGS_PHY_BASE

/* DDR */
#define REG_SDRAM_CONFIG_ADDR			0x1400
#define REG_SDRAM_CONFIG_MASK			0x9fffffff
#define REG_SDRAM_CONFIG_RFRS_MASK		0x3fff
#define REG_SDRAM_CONFIG_WIDTH_OFFS		15
#define REG_SDRAM_CONFIG_REGDIMM_OFFS		17
#define REG_SDRAM_CONFIG_ECC_OFFS		18
#define REG_SDRAM_CONFIG_IERR_OFFS		19
#define REG_SDRAM_CONFIG_PUPRSTDIV_OFFS		28
#define REG_SDRAM_CONFIG_RSTRD_OFFS		30

#define REG_SDRAM_PINS_MUX			0x19d4

#define REG_DUNIT_CTRL_LOW_ADDR			0x1404
#define REG_DUNIT_CTRL_LOW_2T_OFFS		3
#define REG_DUNIT_CTRL_LOW_2T_MASK		0x3
#define REG_DUNIT_CTRL_LOW_DPDE_OFFS		14

#define REG_SDRAM_TIMING_LOW_ADDR		0x1408
#define REG_SDRAM_TIMING_HIGH_ADDR		0x140c
#define REG_SDRAM_TIMING_H_R2R_OFFS		7
#define REG_SDRAM_TIMING_H_R2R_MASK		0x3
#define REG_SDRAM_TIMING_H_R2W_W2R_OFFS		9
#define REG_SDRAM_TIMING_H_R2W_W2R_MASK		0x3
#define REG_SDRAM_TIMING_H_W2W_OFFS		11
#define REG_SDRAM_TIMING_H_W2W_MASK		0x1f
#define REG_SDRAM_TIMING_H_R2R_H_OFFS		19
#define REG_SDRAM_TIMING_H_R2R_H_MASK		0x7
#define REG_SDRAM_TIMING_H_R2W_W2R_H_OFFS	22
#define REG_SDRAM_TIMING_H_R2W_W2R_H_MASK	0x7

#define REG_SDRAM_ADDRESS_CTRL_ADDR		0x1410
#define REG_SDRAM_ADDRESS_SIZE_OFFS		2
#define REG_SDRAM_ADDRESS_SIZE_HIGH_OFFS	18
#define REG_SDRAM_ADDRESS_CTRL_STRUCT_OFFS	4

#define REG_SDRAM_OPEN_PAGES_ADDR		0x1414
#define REG_SDRAM_OPERATION_CS_OFFS		8

#define REG_SDRAM_OPERATION_ADDR		0x1418
#define REG_SDRAM_OPERATION_CWA_DELAY_SEL_OFFS	24
#define REG_SDRAM_OPERATION_CWA_DATA_OFFS	20
#define REG_SDRAM_OPERATION_CWA_DATA_MASK	0xf
#define REG_SDRAM_OPERATION_CWA_RC_OFFS		16
#define REG_SDRAM_OPERATION_CWA_RC_MASK		0xf
#define REG_SDRAM_OPERATION_CMD_MR0		0xf03
#define REG_SDRAM_OPERATION_CMD_MR1		0xf04
#define REG_SDRAM_OPERATION_CMD_MR2		0xf08
#define REG_SDRAM_OPERATION_CMD_MR3		0xf09
#define REG_SDRAM_OPERATION_CMD_RFRS		0xf02
#define REG_SDRAM_OPERATION_CMD_CWA		0xf0e
#define REG_SDRAM_OPERATION_CMD_RFRS_DONE	0xf
#define REG_SDRAM_OPERATION_CMD_MASK		0xf
#define REG_SDRAM_OPERATION_CS_OFFS		8

#define REG_OUDDR3_TIMING_ADDR			0x142c

#define REG_SDRAM_MODE_ADDR			0x141c

#define REG_SDRAM_EXT_MODE_ADDR			0x1420

#define REG_DDR_CONT_HIGH_ADDR			0x1424

#define REG_ODT_TIME_LOW_ADDR			0x1428
#define REG_ODT_ON_CTL_RD_OFFS                  12
#define REG_ODT_OFF_CTL_RD_OFFS                 16
#define REG_SDRAM_ERROR_ADDR                    0x1454
#define REG_SDRAM_AUTO_PWR_SAVE_ADDR            0x1474
#define REG_ODT_TIME_HIGH_ADDR			0x147c

#define REG_SDRAM_INIT_CTRL_ADDR		0x1480
#define REG_SDRAM_INIT_CTRL_OFFS		0
#define REG_SDRAM_INIT_CKE_ASSERT_OFFS		2
#define REG_SDRAM_INIT_RESET_DEASSERT_OFFS	3
#define REG_SDRAM_INIT_RESET_MASK_OFFS		1

#define REG_SDRAM_ODT_CTRL_LOW_ADDR		0x1494

#define REG_SDRAM_ODT_CTRL_HIGH_ADDR		0x1498
#define REG_SDRAM_ODT_CTRL_HIGH_OVRD_MASK	0x0
#define REG_SDRAM_ODT_CTRL_HIGH_OVRD_ENA	0x3

#define REG_DUNIT_ODT_CTRL_ADDR			0x149c
#define REG_DUNIT_ODT_CTRL_OVRD_OFFS            8
#define REG_DUNIT_ODT_CTRL_OVRD_VAL_OFFS        9

#define REG_DRAM_FIFO_CTRL_ADDR			0x14a0

#define REG_DRAM_AXI_CTRL_ADDR			0x14a8
#define REG_DRAM_AXI_CTRL_AXIDATABUSWIDTH_OFFS	0

#define REG_METAL_MASK_ADDR			0x14b0
#define REG_METAL_MASK_MASK			0xdfffffff
#define REG_METAL_MASK_RETRY_OFFS		0

#define REG_DRAM_ADDR_CTRL_DRIVE_STRENGTH_ADDR	0x14c0

#define REG_DRAM_DATA_DQS_DRIVE_STRENGTH_ADDR	0x14c4
#define REG_DRAM_VER_CAL_MACHINE_CTRL_ADDR      0x14c8
#define REG_DRAM_MAIN_PADS_CAL_ADDR		0x14cc

#define REG_DRAM_HOR_CAL_MACHINE_CTRL_ADDR      0x17c8

#define REG_CS_SIZE_SCRATCH_ADDR		0x1504
#define REG_DYNAMIC_POWER_SAVE_ADDR             0x1520
#define REG_DDR_IO_ADDR				0x1524
#define REG_DDR_IO_CLK_RATIO_OFFS		15

#define REG_DFS_ADDR				0x1528
#define REG_DFS_DLLNEXTSTATE_OFFS		0
#define REG_DFS_BLOCK_OFFS			1
#define REG_DFS_SR_OFFS				2
#define REG_DFS_ATSR_OFFS			3
#define REG_DFS_RECONF_OFFS			4
#define REG_DFS_CL_NEXT_STATE_OFFS		8
#define REG_DFS_CL_NEXT_STATE_MASK		0xf
#define REG_DFS_CWL_NEXT_STATE_OFFS		12
#define REG_DFS_CWL_NEXT_STATE_MASK		0x7

#define REG_READ_DATA_SAMPLE_DELAYS_ADDR	0x1538
#define REG_READ_DATA_SAMPLE_DELAYS_MASK	0x1f
#define REG_READ_DATA_SAMPLE_DELAYS_OFFS	8

#define REG_READ_DATA_READY_DELAYS_ADDR		0x153c
#define REG_READ_DATA_READY_DELAYS_MASK		0x1f
#define REG_READ_DATA_READY_DELAYS_OFFS		8

#define START_BURST_IN_ADDR			1

#define REG_DRAM_TRAINING_SHADOW_ADDR		0x18488
#define REG_DRAM_TRAINING_ADDR			0x15b0
#define REG_DRAM_TRAINING_LOW_FREQ_OFFS		0
#define REG_DRAM_TRAINING_PATTERNS_OFFS		4
#define REG_DRAM_TRAINING_MED_FREQ_OFFS		2
#define REG_DRAM_TRAINING_WL_OFFS		3
#define REG_DRAM_TRAINING_RL_OFFS		6
#define REG_DRAM_TRAINING_DQS_RX_OFFS		15
#define REG_DRAM_TRAINING_DQS_TX_OFFS		16
#define REG_DRAM_TRAINING_CS_OFFS		20
#define REG_DRAM_TRAINING_RETEST_OFFS		24
#define REG_DRAM_TRAINING_DFS_FREQ_OFFS		27
#define REG_DRAM_TRAINING_DFS_REQ_OFFS		29
#define REG_DRAM_TRAINING_ERROR_OFFS		30
#define REG_DRAM_TRAINING_AUTO_OFFS		31
#define REG_DRAM_TRAINING_RETEST_PAR		0x3
#define REG_DRAM_TRAINING_RETEST_MASK		0xf8ffffff
#define REG_DRAM_TRAINING_CS_MASK		0xff0fffff
#define REG_DRAM_TRAINING_PATTERNS_MASK		0xff0f0000

#define REG_DRAM_TRAINING_1_ADDR		0x15b4
#define REG_DRAM_TRAINING_1_TRNBPOINT_OFFS	16

#define REG_DRAM_TRAINING_2_ADDR		0x15b8
#define REG_DRAM_TRAINING_2_OVERRUN_OFFS	17
#define REG_DRAM_TRAINING_2_FIFO_RST_OFFS	4
#define REG_DRAM_TRAINING_2_RL_MODE_OFFS	3
#define REG_DRAM_TRAINING_2_WL_MODE_OFFS	2
#define REG_DRAM_TRAINING_2_ECC_MUX_OFFS	1
#define REG_DRAM_TRAINING_2_SW_OVRD_OFFS	0

#define REG_DRAM_TRAINING_PATTERN_BASE_ADDR	0x15bc
#define REG_DRAM_TRAINING_PATTERN_BASE_OFFS	3

#define REG_TRAINING_DEBUG_2_ADDR		0x15c4
#define REG_TRAINING_DEBUG_2_OFFS		16
#define REG_TRAINING_DEBUG_2_MASK		0x3

#define REG_TRAINING_DEBUG_3_ADDR		0x15c8
#define REG_TRAINING_DEBUG_3_OFFS		3
#define REG_TRAINING_DEBUG_3_MASK		0x7

#define	MR_CS_ADDR_OFFS				4

#define	REG_DDR3_MR0_ADDR			0x15d0
#define	REG_DDR3_MR0_CS_ADDR			0x1870
#define REG_DDR3_MR0_CL_MASK			0x74
#define	REG_DDR3_MR0_CL_OFFS			2
#define	REG_DDR3_MR0_CL_HIGH_OFFS		3
#define	CL_MASK					0xf

#define	REG_DDR3_MR1_ADDR			0x15d4
#define	REG_DDR3_MR1_CS_ADDR			0x1874
#define REG_DDR3_MR1_RTT_MASK			0xfffffdbb
#define REG_DDR3_MR1_DLL_ENA_OFFS		0
#define REG_DDR3_MR1_RTT_DISABLED		0x0
#define REG_DDR3_MR1_RTT_RZQ2			0x40
#define REG_DDR3_MR1_RTT_RZQ4			0x2
#define REG_DDR3_MR1_RTT_RZQ6			0x42
#define REG_DDR3_MR1_RTT_RZQ8			0x202
#define REG_DDR3_MR1_RTT_RZQ12			0x4
/* WL-disabled, OB-enabled */
#define REG_DDR3_MR1_OUTBUF_WL_MASK		0xffffef7f
/* Output Buffer Disabled */
#define REG_DDR3_MR1_OUTBUF_DIS_OFFS		12
#define REG_DDR3_MR1_WL_ENA_OFFS		7
#define REG_DDR3_MR1_WL_ENA			0x80	/* WL Enabled */
#define REG_DDR3_MR1_ODT_MASK			0xfffffdbb

#define	REG_DDR3_MR2_ADDR			0x15d8
#define	REG_DDR3_MR2_CS_ADDR			0x1878
#define	REG_DDR3_MR2_CWL_OFFS			3
#define	REG_DDR3_MR2_CWL_MASK			0x7
#define REG_DDR3_MR2_ODT_MASK			0xfffff9ff
#define	REG_DDR3_MR3_ADDR			0x15dc
#define	REG_DDR3_MR3_CS_ADDR			0x187c

#define REG_DDR3_RANK_CTRL_ADDR			0x15e0
#define REG_DDR3_RANK_CTRL_CS_ENA_MASK		0xf
#define REG_DDR3_RANK_CTRL_MIRROR_OFFS		4

#define REG_ZQC_CONF_ADDR			0x15e4

#define REG_DRAM_PHY_CONFIG_ADDR		0x15ec
#define REG_DRAM_PHY_CONFIG_MASK		0x3fffffff

#define REG_ODPG_CNTRL_ADDR			0x1600
#define REG_ODPG_CNTRL_OFFS			21

#define REG_PHY_LOCK_MASK_ADDR			0x1670
#define REG_PHY_LOCK_MASK_MASK			0xfffff000

#define REG_PHY_LOCK_STATUS_ADDR		0x1674
#define REG_PHY_LOCK_STATUS_LOCK_OFFS		9
#define REG_PHY_LOCK_STATUS_LOCK_MASK		0xfff
#define REG_PHY_LOCK_APLL_ADLL_STATUS_MASK	0x7ff

#define REG_PHY_REGISTRY_FILE_ACCESS_ADDR	0x16a0
#define REG_PHY_REGISTRY_FILE_ACCESS_OP_WR	0xc0000000
#define REG_PHY_REGISTRY_FILE_ACCESS_OP_RD	0x80000000
#define REG_PHY_REGISTRY_FILE_ACCESS_OP_DONE	0x80000000
#define REG_PHY_BC_OFFS				27
#define REG_PHY_CNTRL_OFFS			26
#define REG_PHY_CS_OFFS				16
#define REG_PHY_DQS_REF_DLY_OFFS		10
#define REG_PHY_PHASE_OFFS			8
#define REG_PHY_PUP_OFFS			22

#define REG_TRAINING_WL_ADDR			0x16ac
#define REG_TRAINING_WL_CS_MASK			0xfffffffc
#define REG_TRAINING_WL_UPD_OFFS		2
#define REG_TRAINING_WL_CS_DONE_OFFS		3
#define REG_TRAINING_WL_RATIO_MASK		0xffffff0f
#define REG_TRAINING_WL_1TO1			0x50
#define REG_TRAINING_WL_2TO1			0x10
#define REG_TRAINING_WL_DELAYEXP_MASK		0x20000000
#define REG_TRAINING_WL_RESULTS_MASK		0x000001ff
#define REG_TRAINING_WL_RESULTS_OFFS		20

#define REG_REGISTERED_DRAM_CTRL_ADDR		0x16d0
#define REG_REGISTERED_DRAM_CTRL_SR_FLOAT_OFFS	15
#define REG_REGISTERED_DRAM_CTRL_PARITY_MASK	0x3f

/* DLB */
#define REG_STATIC_DRAM_DLB_CONTROL		0x1700
#define DLB_BUS_OPTIMIZATION_WEIGHTS_REG	0x1704
#define DLB_AGING_REGISTER			0x1708
#define DLB_EVICTION_CONTROL_REG		0x170c
#define DLB_EVICTION_TIMERS_REGISTER_REG	0x1710
#define DLB_USER_COMMAND_REG			0x1714
#define DLB_BUS_WEIGHTS_DIFF_CS			0x1770
#define DLB_BUS_WEIGHTS_DIFF_BG			0x1774
#define DLB_BUS_WEIGHTS_SAME_BG			0x1778
#define DLB_BUS_WEIGHTS_RD_WR			0x177c
#define DLB_BUS_WEIGHTS_ATTR_SYS_PRIO		0x1780
#define DLB_MAIN_QUEUE_MAP			0x1784
#define DLB_LINE_SPLIT				0x1788

#define DLB_ENABLE				0x1
#define DLB_WRITE_COALESING			(0x1 << 2)
#define DLB_AXI_PREFETCH_EN			(0x1 << 3)
#define DLB_MBUS_PREFETCH_EN			(0x1 << 4)
#define PREFETCH_N_LN_SZ_TR			(0x1 << 6)
#define DLB_INTERJECTION_ENABLE			(0x1 << 3)

/* CPU */
#define REG_BOOTROM_ROUTINE_ADDR		0x182d0
#define REG_BOOTROM_ROUTINE_DRAM_INIT_OFFS	12

#define REG_DRAM_INIT_CTRL_STATUS_ADDR		0x18488
#define REG_DRAM_INIT_CTRL_TRN_CLK_OFFS		16
#define REG_CPU_DIV_CLK_CTRL_0_NEW_RATIO	0x000200ff
#define REG_DRAM_INIT_CTRL_STATUS_2_ADDR	0x1488

#define REG_CPU_DIV_CLK_CTRL_0_ADDR		0x18700

#define REG_CPU_DIV_CLK_CTRL_1_ADDR		0x18704
#define REG_CPU_DIV_CLK_CTRL_2_ADDR		0x18708

#define REG_CPU_DIV_CLK_CTRL_3_ADDR		0x1870c
#define REG_CPU_DIV_CLK_CTRL_3_FREQ_MASK	0xffffc0ff
#define REG_CPU_DIV_CLK_CTRL_3_FREQ_OFFS	8

#define REG_CPU_DIV_CLK_CTRL_4_ADDR		0x18710

#define REG_CPU_DIV_CLK_STATUS_0_ADDR		0x18718
#define REG_CPU_DIV_CLK_ALL_STABLE_OFFS		8

#define REG_CPU_PLL_CTRL_0_ADDR			0x1871c
#define REG_CPU_PLL_STATUS_0_ADDR		0x18724
#define REG_CORE_DIV_CLK_CTRL_ADDR		0x18740
#define REG_CORE_DIV_CLK_STATUS_ADDR		0x18744
#define REG_DDRPHY_APLL_CTRL_ADDR		0x18780

#define REG_DDRPHY_APLL_CTRL_2_ADDR		0x18784
#define REG_SFABRIC_CLK_CTRL_ADDR		0x20858
#define REG_SFABRIC_CLK_CTRL_SMPL_OFFS		8

/* DRAM Windows */
#define REG_XBAR_WIN_19_CTRL_ADDR		0x200e8
#define REG_XBAR_WIN_4_CTRL_ADDR		0x20040
#define REG_XBAR_WIN_4_BASE_ADDR		0x20044
#define REG_XBAR_WIN_4_REMAP_ADDR		0x20048
#define REG_FASTPATH_WIN_0_CTRL_ADDR		0x20184
#define REG_XBAR_WIN_7_REMAP_ADDR               0x20078

/* SRAM */
#define REG_CDI_CONFIG_ADDR			0x20220
#define REG_SRAM_WINDOW_0_ADDR			0x20240
#define REG_SRAM_WINDOW_0_ENA_OFFS		0
#define REG_SRAM_WINDOW_1_ADDR			0x20244
#define REG_SRAM_L2_ENA_ADDR			0x8500
#define REG_SRAM_CLEAN_BY_WAY_ADDR		0x87bc

/* Timers */
#define REG_TIMERS_CTRL_ADDR			0x20300
#define REG_TIMERS_EVENTS_ADDR			0x20304
#define REG_TIMER0_VALUE_ADDR			0x20314
#define REG_TIMER1_VALUE_ADDR			0x2031c
#define REG_TIMER0_ENABLE_MASK			0x1

#define MV_BOARD_REFCLK_25MHZ			25000000
#define CNTMR_RELOAD_REG(tmr)	(REG_TIMERS_CTRL_ADDR  + 0x10 + (tmr * 8))
#define CNTMR_VAL_REG(tmr)	(REG_TIMERS_CTRL_ADDR  + 0x14 + (tmr * 8))
#define CNTMR_CTRL_REG(tmr)	(REG_TIMERS_CTRL_ADDR)
#define CTCR_ARM_TIMER_EN_OFFS(timer)	(timer * 2)
#define CTCR_ARM_TIMER_EN_MASK(timer)	(1 << CTCR_ARM_TIMER_EN_OFFS(timer))
#define CTCR_ARM_TIMER_EN(timer)	(1 << CTCR_ARM_TIMER_EN_OFFS(timer))

#define CTCR_ARM_TIMER_AUTO_OFFS(timer)	(1 + (timer * 2))
#define CTCR_ARM_TIMER_AUTO_MASK(timer)	(1 << CTCR_ARM_TIMER_EN_OFFS(timer))
#define CTCR_ARM_TIMER_AUTO_EN(timer)	(1 << CTCR_ARM_TIMER_AUTO_OFFS(timer))

/* PMU */
#define REG_PMU_I_F_CTRL_ADDR			0x1c090
#define REG_PMU_DUNIT_BLK_OFFS			16
#define REG_PMU_DUNIT_RFRS_OFFS			20
#define REG_PMU_DUNIT_ACK_OFFS			24

/* MBUS */
#define MBUS_UNITS_PRIORITY_CONTROL_REG		(MBUS_REGS_OFFSET + 0x420)
#define FABRIC_UNITS_PRIORITY_CONTROL_REG	(MBUS_REGS_OFFSET + 0x424)
#define MBUS_UNITS_PREFETCH_CONTROL_REG		(MBUS_REGS_OFFSET + 0x428)
#define FABRIC_UNITS_PREFETCH_CONTROL_REG	(MBUS_REGS_OFFSET + 0x42c)

#define REG_PM_STAT_MASK_ADDR			0x2210c
#define REG_PM_STAT_MASK_CPU0_IDLE_MASK_OFFS	16

#define REG_PM_EVENT_STAT_MASK_ADDR		0x22120
#define REG_PM_EVENT_STAT_MASK_DFS_DONE_OFFS	17

#define REG_PM_CTRL_CONFIG_ADDR			0x22104
#define REG_PM_CTRL_CONFIG_DFS_REQ_OFFS		18

#define REG_FABRIC_LOCAL_IRQ_MASK_ADDR		0x218c4
#define REG_FABRIC_LOCAL_IRQ_PMU_MASK_OFFS	18

/* Controller revision info */
#define PCI_CLASS_CODE_AND_REVISION_ID		0x008
#define PCCRIR_REVID_OFFS			0	/* Revision ID */
#define PCCRIR_REVID_MASK			(0xff << PCCRIR_REVID_OFFS)

/* Power Management Clock Gating Control Register */
#define POWER_MNG_CTRL_REG			0x18220
#define PEX_DEVICE_AND_VENDOR_ID		0x000
#define PEX_CFG_DIRECT_ACCESS(if, reg)	(PEX_IF_REGS_BASE(if) + (reg))
#define PMC_PEXSTOPCLOCK_OFFS(p)	((p) < 8 ? (5 + (p)) : (18 + (p)))
#define PMC_PEXSTOPCLOCK_MASK(p)	(1 << PMC_PEXSTOPCLOCK_OFFS(p))
#define PMC_PEXSTOPCLOCK_EN(p)		(1 << PMC_PEXSTOPCLOCK_OFFS(p))
#define PMC_PEXSTOPCLOCK_STOP(p)	(0 << PMC_PEXSTOPCLOCK_OFFS(p))

/* TWSI */
#define TWSI_DATA_ADDR_MASK		0x7
#define TWSI_DATA_ADDR_OFFS		1

/* General */
#define MAX_CS				4

/* Frequencies */
#define FAB_OPT				21
#define CLK_CPU				12
#define CLK_VCO				(2 * CLK_CPU)
#define CLK_DDR				12

/* CPU Frequencies: */
#define CLK_CPU_1000			0
#define CLK_CPU_1066			1
#define CLK_CPU_1200			2
#define CLK_CPU_1333			3
#define CLK_CPU_1500			4
#define CLK_CPU_1666			5
#define CLK_CPU_1800			6
#define CLK_CPU_2000			7
#define CLK_CPU_600			8
#define CLK_CPU_667			9
#define CLK_CPU_800			0xa

/* Extra Cpu Frequencies: */
#define CLK_CPU_1600			11
#define CLK_CPU_2133			12
#define CLK_CPU_2200			13
#define CLK_CPU_2400			14

#define SAR1_CPU_CORE_MASK		0x00000018
#define SAR1_CPU_CORE_OFFSET		3

#endif /* _DDR3_HWS_HW_TRAINING_DEF_H */
