/*
 * Sun8i a33 platform dram controller init.
 *
 * (C) Copyright 2007-2015 Allwinner Technology Co.
 *                         Jerry Wang <wangflord@allwinnertech.com>
 * (C) Copyright 2015      Vishnu Patekar <vishnupatekar0510@gmail.com>
 * (C) Copyright 2015      Hans de Goede <hdegoede@redhat.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <errno.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/dram.h>
#include <asm/arch/prcm.h>
#include <linux/kconfig.h>

/* PLL runs at 2x dram-clk, controller runs at PLL / 4 (dram-clk / 2) */
#define DRAM_CLK_MUL 2
#define DRAM_CLK_DIV 4
#define DRAM_SIGMA_DELTA_ENABLE 1

struct dram_para {
	u8 cs1;
	u8 seq;
	u8 bank;
	u8 rank;
	u8 rows;
	u8 bus_width;
	u16 page_size;
};

static void mctl_set_cr(struct dram_para *para)
{
	struct sunxi_mctl_com_reg * const mctl_com =
			(struct sunxi_mctl_com_reg *)SUNXI_DRAM_COM_BASE;

	writel(MCTL_CR_CS1_CONTROL(para->cs1) | MCTL_CR_UNKNOWN |
	       MCTL_CR_CHANNEL(1) | MCTL_CR_DDR3 |
	       (para->seq ? MCTL_CR_SEQUENCE : 0) |
	       ((para->bus_width == 16) ? MCTL_CR_BUSW16 : MCTL_CR_BUSW8) |
	       MCTL_CR_PAGE_SIZE(para->page_size) | MCTL_CR_ROW(para->rows) |
	       MCTL_CR_BANK(para->bank) | MCTL_CR_RANK(para->rank),
	       &mctl_com->cr);
}

static void auto_detect_dram_size(struct dram_para *para)
{
	u8 orig_rank = para->rank;
	int rows, columns;

	/* Row detect */
	para->page_size = 512;
	para->seq = 1;
	para->rows = 16;
	para->rank = 1;
	mctl_set_cr(para);
	for (rows = 11 ; rows < 16 ; rows++) {
		if (mctl_mem_matches(1 << (rows + 9))) /* row-column */
			break;
	}

	/* Column (page size) detect */
	para->rows = 11;
	para->page_size = 8192;
	mctl_set_cr(para);
	for (columns = 9 ; columns < 13 ; columns++) {
		if (mctl_mem_matches(1 << columns))
			break;
	}

	para->seq = 0;
	para->rank = orig_rank;
	para->rows = rows;
	para->page_size = 1 << columns;
	mctl_set_cr(para);
}

static inline int ns_to_t(int nanoseconds)
{
	const unsigned int ctrl_freq =
		CONFIG_DRAM_CLK * DRAM_CLK_MUL / DRAM_CLK_DIV;

	return (ctrl_freq * nanoseconds + 999) / 1000;
}

static void auto_set_timing_para(struct dram_para *para)
{
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
		(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;
	u32 reg_val;

	u8 tccd		= 2;
	u8 tfaw		= ns_to_t(50);
	u8 trrd		= max(ns_to_t(10), 4);
	u8 trcd		= ns_to_t(15);
	u8 trc		= ns_to_t(53);
	u8 txp		= max(ns_to_t(8), 3);
	u8 twtr		= max(ns_to_t(8), 4);
	u8 trtp		= max(ns_to_t(8), 4);
	u8 twr		= max(ns_to_t(15), 3);
	u8 trp		= ns_to_t(15);
	u8 tras		= ns_to_t(38);

	u16 trefi	= ns_to_t(7800) / 32;
	u16 trfc	= ns_to_t(350);

	/* Fixed timing parameters */
	u8 tmrw		= 0;
	u8 tmrd		= 4;
	u8 tmod		= 12;
	u8 tcke		= 3;
	u8 tcksrx	= 5;
	u8 tcksre	= 5;
	u8 tckesr	= 4;
	u8 trasmax	= 24;
	u8 tcl		= 6; /* CL 12 */
	u8 tcwl		= 4; /* CWL 8 */
	u8 t_rdata_en	= 4;
	u8 wr_latency	= 2;

	u32 tdinit0	= (500 * CONFIG_DRAM_CLK) + 1;		/* 500us */
	u32 tdinit1	= (360 * CONFIG_DRAM_CLK) / 1000 + 1;	/* 360ns */
	u32 tdinit2	= (200 * CONFIG_DRAM_CLK) + 1;		/* 200us */
	u32 tdinit3	= (1 * CONFIG_DRAM_CLK) + 1;		/* 1us */

	u8 twtp		= tcwl + 2 + twr;	/* WL + BL / 2 + tWR */
	u8 twr2rd	= tcwl + 2 + twtr; 	/* WL + BL / 2 + tWTR */
	u8 trd2wr	= tcl + 2 + 1 - tcwl; 	/* RL + BL / 2 + 2 - WL */

	/* Set work mode register */
	mctl_set_cr(para);
	/* Set mode register */
	writel(MCTL_MR0, &mctl_ctl->mr0);
	writel(MCTL_MR1, &mctl_ctl->mr1);
	writel(MCTL_MR2, &mctl_ctl->mr2);
	writel(MCTL_MR3, &mctl_ctl->mr3);
	/* Set dram timing */
	reg_val = (twtp << 24) | (tfaw << 16) | (trasmax << 8) | (tras << 0);
	writel(reg_val, &mctl_ctl->dramtmg0);
	reg_val = (txp << 16) | (trtp << 8) | (trc << 0);
	writel(reg_val, &mctl_ctl->dramtmg1);
	reg_val = (tcwl << 24) | (tcl << 16) | (trd2wr << 8) | (twr2rd << 0);
	writel(reg_val, &mctl_ctl->dramtmg2);
	reg_val = (tmrw << 16) | (tmrd << 12) | (tmod << 0);
	writel(reg_val, &mctl_ctl->dramtmg3);
	reg_val = (trcd << 24) | (tccd << 16) | (trrd << 8) | (trp << 0);
	writel(reg_val, &mctl_ctl->dramtmg4);
	reg_val = (tcksrx << 24) | (tcksre << 16) | (tckesr << 8) | (tcke << 0);
	writel(reg_val, &mctl_ctl->dramtmg5);
	/* Set two rank timing and exit self-refresh timing */
	reg_val = readl(&mctl_ctl->dramtmg8);
	reg_val &= ~(0xff << 8);
	reg_val &= ~(0xff << 0);
	reg_val |= (0x33 << 8);
	reg_val |= (0x8 << 0);
	writel(reg_val, &mctl_ctl->dramtmg8);
	/* Set phy interface time */
	reg_val = (0x2 << 24) | (t_rdata_en << 16) | (0x1 << 8)
			| (wr_latency << 0);
	/* PHY interface write latency and read latency configure */
	writel(reg_val, &mctl_ctl->pitmg0);
	/* Set phy time  PTR0-2 use default */
	writel(((tdinit0 << 0) | (tdinit1 << 20)), &mctl_ctl->ptr3);
	writel(((tdinit2 << 0) | (tdinit3 << 20)), &mctl_ctl->ptr4);
	/* Set refresh timing */
	reg_val = (trefi << 16) | (trfc << 0);
	writel(reg_val, &mctl_ctl->rfshtmg);
}

static void mctl_set_pir(u32 val)
{
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
		(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;

	writel(val, &mctl_ctl->pir);
	mctl_await_completion(&mctl_ctl->pgsr0, 0x1, 0x1);
}

static void mctl_data_train_cfg(struct dram_para *para)
{
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
		(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;

	if (para->rank == 2)
		clrsetbits_le32(&mctl_ctl->dtcr, 0x3 << 24, 0x3 << 24);
	else
		clrsetbits_le32(&mctl_ctl->dtcr, 0x3 << 24, 0x1 << 24);
}

static int mctl_train_dram(struct dram_para *para)
{
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
		(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;

	mctl_data_train_cfg(para);
	mctl_set_pir(0x5f3);

	return ((readl(&mctl_ctl->pgsr0) >> 20) & 0xff) ? -EIO : 0;
}

static int mctl_channel_init(struct dram_para *para)
{
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
		(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;
	struct sunxi_mctl_com_reg * const mctl_com =
		(struct sunxi_mctl_com_reg *)SUNXI_DRAM_COM_BASE;
	u32 low_data_lines_status;  /* Training status of datalines 0 - 7 */
	u32 high_data_lines_status; /* Training status of datalines 8 - 15 */

	auto_set_timing_para(para);

	/* Disable dram VTC */
	clrbits_le32(&mctl_ctl->pgcr0, 0x3f << 0);

	/* Set ODT */
	if ((CONFIG_DRAM_CLK > 400) && IS_ENABLED(CONFIG_DRAM_ODT_EN)) {
		setbits_le32(DXnGCR0(0), 0x3 << 9);
		setbits_le32(DXnGCR0(1), 0x3 << 9);
	} else {
		clrbits_le32(DXnGCR0(0), 0x3 << 9);
		clrbits_le32(DXnGCR0(1), 0x3 << 9);
	}

	/* set PLL configuration */
	if (CONFIG_DRAM_CLK >= 480)
		setbits_le32(&mctl_ctl->pllgcr, 0x1 << 18);
	else
		setbits_le32(&mctl_ctl->pllgcr, 0x3 << 18);

	/* Auto detect dram config, set 2 rank and 16bit bus-width */
	para->cs1 = 0;
	para->rank = 2;
	para->bus_width = 16;
	mctl_set_cr(para);

	/* Open DQS gating */
	clrbits_le32(&mctl_ctl->pgcr2, (0x3 << 6));
	clrbits_le32(&mctl_ctl->dqsgmr, (0x1 << 8) | (0x7));

	mctl_data_train_cfg(para);

	/* ZQ calibration */
	writel(CONFIG_DRAM_ZQ & 0xff, &mctl_ctl->zqcr1);
	/* CA calibration */
	mctl_set_pir(0x00000003);
	/* More ZQ calibration */
	writel(readl(&mctl_ctl->zqsr0) | 0x10000000, &mctl_ctl->zqcr2);
	writel((CONFIG_DRAM_ZQ >> 8) & 0xff, &mctl_ctl->zqcr1);

	/* DQS gate training */
	if (mctl_train_dram(para) != 0) {
		low_data_lines_status  = (readl(DXnGSR0(0)) >> 24) & 0x03;
		high_data_lines_status = (readl(DXnGSR0(1)) >> 24) & 0x03;

		if (low_data_lines_status == 0x3)
			return -EIO;

		/* DRAM has only one rank */
		para->rank = 1;
		mctl_set_cr(para);

		if (low_data_lines_status == high_data_lines_status)
			goto done; /* 16 bit bus, 1 rank */

		if (!(low_data_lines_status & high_data_lines_status)) {
			/* Retry 16 bit bus-width with CS1 set */
			para->cs1 = 1;
			mctl_set_cr(para);
			if (mctl_train_dram(para) == 0)
				goto done;
		}

		/* Try 8 bit bus-width */
		writel(0x0, DXnGCR0(1)); /* Disable high DQ */
		para->cs1 = 0;
		para->bus_width = 8;
		mctl_set_cr(para);
		if (mctl_train_dram(para) != 0)
			return -EIO;
	}
done:
	/* Check the dramc status */
	mctl_await_completion(&mctl_ctl->statr, 0x1, 0x1);

	/* Close DQS gating */
	setbits_le32(&mctl_ctl->pgcr2, 0x3 << 6);

	/* Enable master access */
	writel(0xffffffff, &mctl_com->maer);

	return 0;
}

static void mctl_sys_init(struct dram_para *para)
{
	struct sunxi_ccm_reg * const ccm =
			(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
			(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;
	struct sunxi_mctl_com_reg * const mctl_com =
			(struct sunxi_mctl_com_reg *)SUNXI_DRAM_COM_BASE;

	clrsetbits_le32(&ccm->dram_pll_cfg, CCM_DRAMPLL_CFG_SRC_MASK,
			CCM_DRAMPLL_CFG_SRC_PLL11);

	clock_set_pll11(CONFIG_DRAM_CLK * 1000000 * DRAM_CLK_MUL,
			DRAM_SIGMA_DELTA_ENABLE);

	clrsetbits_le32(&ccm->dram_clk_cfg, CCM_DRAMCLK_CFG_DIV_MASK,
			CCM_DRAMCLK_CFG_DIV(DRAM_CLK_DIV) |
			CCM_DRAMCLK_CFG_RST | CCM_DRAMCLK_CFG_UPD);
	mctl_await_completion(&ccm->dram_clk_cfg, CCM_DRAMCLK_CFG_UPD, 0);

	setbits_le32(&ccm->ahb_reset0_cfg, 1 << AHB_RESET_OFFSET_MCTL);
	setbits_le32(&ccm->ahb_gate0, 1 << AHB_GATE_OFFSET_MCTL);
	setbits_le32(&ccm->mbus_reset, CCM_MBUS_RESET_RESET);
	setbits_le32(&ccm->mbus0_clk_cfg, MBUS_CLK_GATE);

	/* Set dram master access priority */
	writel(0x0, &mctl_com->mapr);
	writel(0x0f802f01, &mctl_ctl->sched);
	writel(0x0000400f, &mctl_ctl->clken);	/* normal */

	udelay(250);
}

unsigned long sunxi_dram_init(void)
{
	struct sunxi_mctl_com_reg * const mctl_com =
			(struct sunxi_mctl_com_reg *)SUNXI_DRAM_COM_BASE;
	struct sunxi_mctl_ctl_reg * const mctl_ctl =
			(struct sunxi_mctl_ctl_reg *)SUNXI_DRAM_CTL0_BASE;

	struct dram_para para = {
		.cs1 = 0,
		.bank = 1,
		.rank = 1,
		.rows = 15,
		.bus_width = 16,
		.page_size = 2048,
	};

	mctl_sys_init(&para);

	if (mctl_channel_init(&para) != 0)
		return 0;

	auto_detect_dram_size(&para);

	/* Enable master software clk */
	writel(readl(&mctl_com->swonr) | 0x3ffff, &mctl_com->swonr);

	/* Set DRAM ODT MAP */
	if (para.rank == 2)
		writel(0x00000303, &mctl_ctl->odtmap);
	else
		writel(0x00000201, &mctl_ctl->odtmap);

	return para.page_size * (para.bus_width / 8) *
		(1 << (para.bank + para.rank + para.rows));
}
