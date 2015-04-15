/*
 * Copyright (c) 2011-2013, NVIDIA Corporation.
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <errno.h>
#include <fdtdec.h>
#include <malloc.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch-tegra/dc.h>
#include "displayport.h"
#include "sor.h"

DECLARE_GLOBAL_DATA_PTR;

#define DEBUG_SOR 0

#define APBDEV_PMC_DPD_SAMPLE				0x20
#define APBDEV_PMC_DPD_SAMPLE_ON_DISABLE		0
#define APBDEV_PMC_DPD_SAMPLE_ON_ENABLE			1
#define APBDEV_PMC_SEL_DPD_TIM				0x1c8
#define APBDEV_PMC_SEL_DPD_TIM_SEL_DPD_TIM_DEFAULT	0x7f
#define APBDEV_PMC_IO_DPD2_REQ				0x1c0
#define APBDEV_PMC_IO_DPD2_REQ_LVDS_SHIFT		25
#define APBDEV_PMC_IO_DPD2_REQ_LVDS_OFF			(0 << 25)
#define APBDEV_PMC_IO_DPD2_REQ_LVDS_ON			(1 << 25)
#define APBDEV_PMC_IO_DPD2_REQ_CODE_SHIFT               30
#define APBDEV_PMC_IO_DPD2_REQ_CODE_DEFAULT_MASK        (0x3 << 30)
#define APBDEV_PMC_IO_DPD2_REQ_CODE_IDLE                (0 << 30)
#define APBDEV_PMC_IO_DPD2_REQ_CODE_DPD_OFF             (1 << 30)
#define APBDEV_PMC_IO_DPD2_REQ_CODE_DPD_ON              (2 << 30)
#define APBDEV_PMC_IO_DPD2_STATUS			0x1c4
#define APBDEV_PMC_IO_DPD2_STATUS_LVDS_SHIFT		25
#define APBDEV_PMC_IO_DPD2_STATUS_LVDS_OFF		(0 << 25)
#define APBDEV_PMC_IO_DPD2_STATUS_LVDS_ON		(1 << 25)

static inline u32 tegra_sor_readl(struct tegra_dc_sor_data *sor, u32 reg)
{
	return readl((u32 *)sor->base + reg);
}

static inline void tegra_sor_writel(struct tegra_dc_sor_data *sor, u32 reg,
				    u32 val)
{
	writel(val, (u32 *)sor->base + reg);
}

static inline void tegra_sor_write_field(struct tegra_dc_sor_data *sor,
	u32 reg, u32 mask, u32 val)
{
	u32 reg_val = tegra_sor_readl(sor, reg);
	reg_val &= ~mask;
	reg_val |= val;
	tegra_sor_writel(sor, reg, reg_val);
}

static int tegra_dc_sor_poll_register(struct tegra_dc_sor_data *sor, u32 reg,
				      u32 mask, u32 exp_val,
				      int poll_interval_us, int timeout_ms)
{
	u32 reg_val = 0;
	ulong start;

	start = get_timer(0);
	do {
		reg_val = tegra_sor_readl(sor, reg);
		if (((reg_val & mask) == exp_val))
			return 0;
		udelay(poll_interval_us);
	} while (get_timer(start) < timeout_ms);

	debug("sor_poll_register 0x%x: timeout, (reg_val)0x%08x & (mask)0x%08x != (exp_val)0x%08x\n",
	      reg, reg_val, mask, exp_val);

	return -ETIMEDOUT;
}

int tegra_dc_sor_set_power_state(struct tegra_dc_sor_data *sor, int pu_pd)
{
	u32 reg_val;
	u32 orig_val;

	orig_val = tegra_sor_readl(sor, PWR);

	reg_val = pu_pd ? PWR_NORMAL_STATE_PU :
		PWR_NORMAL_STATE_PD; /* normal state only */

	if (reg_val == orig_val)
		return 0;	/* No update needed */

	reg_val |= PWR_SETTING_NEW_TRIGGER;
	tegra_sor_writel(sor, PWR, reg_val);

	/* Poll to confirm it is done */
	if (tegra_dc_sor_poll_register(sor, PWR,
				       PWR_SETTING_NEW_DEFAULT_MASK,
				       PWR_SETTING_NEW_DONE,
				       100, TEGRA_SOR_TIMEOUT_MS)) {
		debug("dc timeout waiting for SOR_PWR = NEW_DONE\n");
		return -EFAULT;
	}

	return 0;
}

void tegra_dc_sor_set_dp_linkctl(struct tegra_dc_sor_data *sor, int ena,
				 u8 training_pattern,
				 const struct tegra_dp_link_config *link_cfg)
{
	u32 reg_val;

	reg_val = tegra_sor_readl(sor, DP_LINKCTL(sor->portnum));

	if (ena)
		reg_val |= DP_LINKCTL_ENABLE_YES;
	else
		reg_val &= DP_LINKCTL_ENABLE_NO;

	reg_val &= ~DP_LINKCTL_TUSIZE_MASK;
	reg_val |= (link_cfg->tu_size << DP_LINKCTL_TUSIZE_SHIFT);

	if (link_cfg->enhanced_framing)
		reg_val |= DP_LINKCTL_ENHANCEDFRAME_ENABLE;

	tegra_sor_writel(sor, DP_LINKCTL(sor->portnum), reg_val);

	switch (training_pattern) {
	case training_pattern_1:
		tegra_sor_writel(sor, DP_TPG, 0x41414141);
		break;
	case training_pattern_2:
	case training_pattern_3:
		reg_val = (link_cfg->link_bw == SOR_LINK_SPEED_G5_4) ?
			0x43434343 : 0x42424242;
		tegra_sor_writel(sor, DP_TPG, reg_val);
		break;
	default:
		tegra_sor_writel(sor, DP_TPG, 0x50505050);
		break;
	}
}

static int tegra_dc_sor_enable_lane_sequencer(struct tegra_dc_sor_data *sor,
					      int pu, int is_lvds)
{
	u32 reg_val;

	/* SOR lane sequencer */
	if (pu) {
		reg_val = LANE_SEQ_CTL_SETTING_NEW_TRIGGER |
			LANE_SEQ_CTL_SEQUENCE_DOWN |
			LANE_SEQ_CTL_NEW_POWER_STATE_PU;
	} else {
		reg_val = LANE_SEQ_CTL_SETTING_NEW_TRIGGER |
			LANE_SEQ_CTL_SEQUENCE_UP |
			LANE_SEQ_CTL_NEW_POWER_STATE_PD;
	}

	if (is_lvds)
		reg_val |= 15 << LANE_SEQ_CTL_DELAY_SHIFT;
	else
		reg_val |= 1 << LANE_SEQ_CTL_DELAY_SHIFT;

	tegra_sor_writel(sor, LANE_SEQ_CTL, reg_val);

	if (tegra_dc_sor_poll_register(sor, LANE_SEQ_CTL,
				       LANE_SEQ_CTL_SETTING_MASK,
				       LANE_SEQ_CTL_SETTING_NEW_DONE,
				       100, TEGRA_SOR_TIMEOUT_MS)) {
		debug("dp: timeout while waiting for SOR lane sequencer to power down lanes\n");
		return -1;
	}

	return 0;
}

static int tegra_dc_sor_power_dplanes(struct tegra_dc_sor_data *sor,
				      u32 lane_count, int pu)
{
	u32 reg_val;

	reg_val = tegra_sor_readl(sor, DP_PADCTL(sor->portnum));

	if (pu) {
		switch (lane_count) {
		case 4:
			reg_val |= (DP_PADCTL_PD_TXD_3_NO |
				DP_PADCTL_PD_TXD_2_NO);
			/* fall through */
		case 2:
			reg_val |= DP_PADCTL_PD_TXD_1_NO;
		case 1:
			reg_val |= DP_PADCTL_PD_TXD_0_NO;
			break;
		default:
			debug("dp: invalid lane number %d\n", lane_count);
			return -1;
		}

		tegra_sor_writel(sor, DP_PADCTL(sor->portnum), reg_val);
		tegra_dc_sor_set_lane_count(sor, lane_count);
	}

	return tegra_dc_sor_enable_lane_sequencer(sor, pu, 0);
}

void tegra_dc_sor_set_panel_power(struct tegra_dc_sor_data *sor,
				  int power_up)
{
	u32 reg_val;

	reg_val = tegra_sor_readl(sor, DP_PADCTL(sor->portnum));

	if (power_up)
		reg_val |= DP_PADCTL_PAD_CAL_PD_POWERUP;
	else
		reg_val &= ~DP_PADCTL_PAD_CAL_PD_POWERUP;

	tegra_sor_writel(sor, DP_PADCTL(sor->portnum), reg_val);
}

static void tegra_dc_sor_config_pwm(struct tegra_dc_sor_data *sor, u32 pwm_div,
				    u32 pwm_dutycycle)
{
	tegra_sor_writel(sor, PWM_DIV, pwm_div);
	tegra_sor_writel(sor, PWM_CTL,
			 (pwm_dutycycle & PWM_CTL_DUTY_CYCLE_MASK) |
			 PWM_CTL_SETTING_NEW_TRIGGER);

	if (tegra_dc_sor_poll_register(sor, PWM_CTL,
				       PWM_CTL_SETTING_NEW_SHIFT,
				       PWM_CTL_SETTING_NEW_DONE,
				       100, TEGRA_SOR_TIMEOUT_MS)) {
		debug("dp: timeout while waiting for SOR PWM setting\n");
	}
}

static void tegra_dc_sor_set_dp_mode(struct tegra_dc_sor_data *sor,
				const struct tegra_dp_link_config *link_cfg)
{
	u32 reg_val;

	tegra_dc_sor_set_link_bandwidth(sor, link_cfg->link_bw);

	tegra_dc_sor_set_dp_linkctl(sor, 1, training_pattern_none, link_cfg);
	reg_val = tegra_sor_readl(sor, DP_CONFIG(sor->portnum));
	reg_val &= ~DP_CONFIG_WATERMARK_MASK;
	reg_val |= link_cfg->watermark;
	reg_val &= ~DP_CONFIG_ACTIVESYM_COUNT_MASK;
	reg_val |= (link_cfg->active_count <<
		DP_CONFIG_ACTIVESYM_COUNT_SHIFT);
	reg_val &= ~DP_CONFIG_ACTIVESYM_FRAC_MASK;
	reg_val |= (link_cfg->active_frac <<
		DP_CONFIG_ACTIVESYM_FRAC_SHIFT);
	if (link_cfg->activepolarity)
		reg_val |= DP_CONFIG_ACTIVESYM_POLARITY_POSITIVE;
	else
		reg_val &= ~DP_CONFIG_ACTIVESYM_POLARITY_POSITIVE;
	reg_val |= (DP_CONFIG_ACTIVESYM_CNTL_ENABLE |
		DP_CONFIG_RD_RESET_VAL_NEGATIVE);

	tegra_sor_writel(sor, DP_CONFIG(sor->portnum), reg_val);

	/* program h/vblank sym */
	tegra_sor_write_field(sor, DP_AUDIO_HBLANK_SYMBOLS,
			      DP_AUDIO_HBLANK_SYMBOLS_MASK,
			      link_cfg->hblank_sym);

	tegra_sor_write_field(sor, DP_AUDIO_VBLANK_SYMBOLS,
			      DP_AUDIO_VBLANK_SYMBOLS_MASK,
			      link_cfg->vblank_sym);
}

static inline void tegra_dc_sor_super_update(struct tegra_dc_sor_data *sor)
{
	tegra_sor_writel(sor, SUPER_STATE0, 0);
	tegra_sor_writel(sor, SUPER_STATE0, 1);
	tegra_sor_writel(sor, SUPER_STATE0, 0);
}

static inline void tegra_dc_sor_update(struct tegra_dc_sor_data *sor)
{
	tegra_sor_writel(sor, STATE0, 0);
	tegra_sor_writel(sor, STATE0, 1);
	tegra_sor_writel(sor, STATE0, 0);
}

static int tegra_dc_sor_io_set_dpd(struct tegra_dc_sor_data *sor, int up)
{
	u32 reg_val;
	void *pmc_base = sor->pmc_base;

	if (up) {
		writel(APBDEV_PMC_DPD_SAMPLE_ON_ENABLE,
		       pmc_base + APBDEV_PMC_DPD_SAMPLE);
		writel(10, pmc_base + APBDEV_PMC_SEL_DPD_TIM);
	}

	reg_val = readl(pmc_base + APBDEV_PMC_IO_DPD2_REQ);
	reg_val &= ~(APBDEV_PMC_IO_DPD2_REQ_LVDS_ON ||
			APBDEV_PMC_IO_DPD2_REQ_CODE_DEFAULT_MASK);

	reg_val = up ? APBDEV_PMC_IO_DPD2_REQ_LVDS_ON |
			APBDEV_PMC_IO_DPD2_REQ_CODE_DPD_OFF :
			APBDEV_PMC_IO_DPD2_REQ_LVDS_OFF |
			APBDEV_PMC_IO_DPD2_REQ_CODE_DPD_ON;

	writel(reg_val, pmc_base + APBDEV_PMC_IO_DPD2_REQ);

	/* Polling */
	u32 temp = 10 * 1000;
	do {
		udelay(20);
		reg_val = readl(pmc_base + APBDEV_PMC_IO_DPD2_STATUS);
		if (temp > 20)
			temp -= 20;
		else
			break;
	} while ((reg_val & APBDEV_PMC_IO_DPD2_STATUS_LVDS_ON) != 0);

	if ((reg_val & APBDEV_PMC_IO_DPD2_STATUS_LVDS_ON) != 0) {
		debug("PMC_IO_DPD2 polling failed (0x%x)\n", reg_val);
		return -EIO;
	}

	if (up) {
		writel(APBDEV_PMC_DPD_SAMPLE_ON_DISABLE,
		       pmc_base + APBDEV_PMC_DPD_SAMPLE);
	}

	return 0;
}

void tegra_dc_sor_set_internal_panel(struct tegra_dc_sor_data *sor, int is_int)
{
	u32 reg_val;

	reg_val = tegra_sor_readl(sor, DP_SPARE(sor->portnum));
	if (is_int)
		reg_val |= DP_SPARE_PANEL_INTERNAL;
	else
		reg_val &= ~DP_SPARE_PANEL_INTERNAL;

	reg_val |= DP_SPARE_SOR_CLK_SEL_MACRO_SORCLK |
		DP_SPARE_SEQ_ENABLE_YES;
	tegra_sor_writel(sor, DP_SPARE(sor->portnum), reg_val);
}

void tegra_dc_sor_read_link_config(struct tegra_dc_sor_data *sor, u8 *link_bw,
				   u8 *lane_count)
{
	u32 reg_val;

	reg_val = tegra_sor_readl(sor, CLK_CNTRL);
	*link_bw = (reg_val & CLK_CNTRL_DP_LINK_SPEED_MASK)
		>> CLK_CNTRL_DP_LINK_SPEED_SHIFT;
	reg_val = tegra_sor_readl(sor,
		DP_LINKCTL(sor->portnum));

	switch (reg_val & DP_LINKCTL_LANECOUNT_MASK) {
	case DP_LINKCTL_LANECOUNT_ZERO:
		*lane_count = 0;
		break;
	case DP_LINKCTL_LANECOUNT_ONE:
		*lane_count = 1;
		break;
	case DP_LINKCTL_LANECOUNT_TWO:
		*lane_count = 2;
		break;
	case DP_LINKCTL_LANECOUNT_FOUR:
		*lane_count = 4;
		break;
	default:
		printf("Unknown lane count\n");
	}
}

void tegra_dc_sor_set_link_bandwidth(struct tegra_dc_sor_data *sor, u8 link_bw)
{
	tegra_sor_write_field(sor, CLK_CNTRL,
			      CLK_CNTRL_DP_LINK_SPEED_MASK,
			      link_bw << CLK_CNTRL_DP_LINK_SPEED_SHIFT);
}

void tegra_dc_sor_set_lane_count(struct tegra_dc_sor_data *sor, u8 lane_count)
{
	u32 reg_val;

	reg_val = tegra_sor_readl(sor, DP_LINKCTL(sor->portnum));
	reg_val &= ~DP_LINKCTL_LANECOUNT_MASK;
	switch (lane_count) {
	case 0:
		break;
	case 1:
		reg_val |= DP_LINKCTL_LANECOUNT_ONE;
		break;
	case 2:
		reg_val |= DP_LINKCTL_LANECOUNT_TWO;
		break;
	case 4:
		reg_val |= DP_LINKCTL_LANECOUNT_FOUR;
		break;
	default:
		/* 0 should be handled earlier. */
		printf("dp: Invalid lane count %d\n", lane_count);
		return;
	}
	tegra_sor_writel(sor, DP_LINKCTL(sor->portnum), reg_val);
}

/*
 * The SOR power sequencer does not work for t124 so SW has to
 *  go through the power sequence manually
 * Power up steps from spec:
 * STEP	PDPORT	PDPLL	PDBG	PLLVCOD	PLLCAPD	E_DPD	PDCAL
 * 1	1	1	1	1	1	1	1
 * 2	1	1	1	1	1	0	1
 * 3	1	1	0	1	1	0	1
 * 4	1	0	0	0	0	0	1
 * 5	0	0	0	0	0	0	1
 */
static int tegra_dc_sor_power_up(struct tegra_dc_sor_data *sor, int is_lvds)
{
	int ret;

	if (sor->power_is_up)
		return 0;

	/* Set link bw */
	tegra_dc_sor_set_link_bandwidth(sor, is_lvds ?
					CLK_CNTRL_DP_LINK_SPEED_LVDS :
					CLK_CNTRL_DP_LINK_SPEED_G1_62);

	/* step 1 */
	tegra_sor_write_field(sor, PLL2,
			      PLL2_AUX7_PORT_POWERDOWN_MASK | /* PDPORT */
			      PLL2_AUX6_BANDGAP_POWERDOWN_MASK | /* PDBG */
			      PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_MASK, /* PLLCAPD */
			      PLL2_AUX7_PORT_POWERDOWN_ENABLE |
			      PLL2_AUX6_BANDGAP_POWERDOWN_ENABLE |
			      PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_ENABLE);
	tegra_sor_write_field(sor, PLL0, PLL0_PWR_MASK | /* PDPLL */
			      PLL0_VCOPD_MASK, /* PLLVCOPD */
			      PLL0_PWR_OFF | PLL0_VCOPD_ASSERT);
	tegra_sor_write_field(sor, DP_PADCTL(sor->portnum),
			      DP_PADCTL_PAD_CAL_PD_POWERDOWN, /* PDCAL */
			      DP_PADCTL_PAD_CAL_PD_POWERDOWN);

	/* step 2 */
	ret = tegra_dc_sor_io_set_dpd(sor, 1);
	if (ret)
		return ret;
	udelay(15);

	/* step 3 */
	tegra_sor_write_field(sor, PLL2,
			      PLL2_AUX6_BANDGAP_POWERDOWN_MASK,
			      PLL2_AUX6_BANDGAP_POWERDOWN_DISABLE);
	udelay(25);

	/* step 4 */
	tegra_sor_write_field(sor, PLL0,
			      PLL0_PWR_MASK | /* PDPLL */
			      PLL0_VCOPD_MASK, /* PLLVCOPD */
			      PLL0_PWR_ON | PLL0_VCOPD_RESCIND);
	/* PLLCAPD */
	tegra_sor_write_field(sor, PLL2,
			      PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_MASK,
			      PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_DISABLE);
	udelay(225);

	/* step 5 PDPORT */
	tegra_sor_write_field(sor, PLL2,
			      PLL2_AUX7_PORT_POWERDOWN_MASK,
			      PLL2_AUX7_PORT_POWERDOWN_DISABLE);

	sor->power_is_up = 1;

	return 0;
}

#if DEBUG_SOR
static void dump_sor_reg(struct tegra_dc_sor_data *sor)
{
#define DUMP_REG(a) printk(BIOS_INFO, "%-32s  %03x  %08x\n",		\
		#a, a, tegra_sor_readl(sor, a));

	DUMP_REG(SUPER_STATE0);
	DUMP_REG(SUPER_STATE1);
	DUMP_REG(STATE0);
	DUMP_REG(STATE1);
	DUMP_REG(NV_HEAD_STATE0(0));
	DUMP_REG(NV_HEAD_STATE0(1));
	DUMP_REG(NV_HEAD_STATE1(0));
	DUMP_REG(NV_HEAD_STATE1(1));
	DUMP_REG(NV_HEAD_STATE2(0));
	DUMP_REG(NV_HEAD_STATE2(1));
	DUMP_REG(NV_HEAD_STATE3(0));
	DUMP_REG(NV_HEAD_STATE3(1));
	DUMP_REG(NV_HEAD_STATE4(0));
	DUMP_REG(NV_HEAD_STATE4(1));
	DUMP_REG(NV_HEAD_STATE5(0));
	DUMP_REG(NV_HEAD_STATE5(1));
	DUMP_REG(CRC_CNTRL);
	DUMP_REG(CLK_CNTRL);
	DUMP_REG(CAP);
	DUMP_REG(PWR);
	DUMP_REG(TEST);
	DUMP_REG(PLL0);
	DUMP_REG(PLL1);
	DUMP_REG(PLL2);
	DUMP_REG(PLL3);
	DUMP_REG(CSTM);
	DUMP_REG(LVDS);
	DUMP_REG(CRCA);
	DUMP_REG(CRCB);
	DUMP_REG(SEQ_CTL);
	DUMP_REG(LANE_SEQ_CTL);
	DUMP_REG(SEQ_INST(0));
	DUMP_REG(SEQ_INST(1));
	DUMP_REG(SEQ_INST(2));
	DUMP_REG(SEQ_INST(3));
	DUMP_REG(SEQ_INST(4));
	DUMP_REG(SEQ_INST(5));
	DUMP_REG(SEQ_INST(6));
	DUMP_REG(SEQ_INST(7));
	DUMP_REG(SEQ_INST(8));
	DUMP_REG(PWM_DIV);
	DUMP_REG(PWM_CTL);
	DUMP_REG(MSCHECK);
	DUMP_REG(XBAR_CTRL);
	DUMP_REG(DP_LINKCTL(0));
	DUMP_REG(DP_LINKCTL(1));
	DUMP_REG(DC(0));
	DUMP_REG(DC(1));
	DUMP_REG(LANE_DRIVE_CURRENT(0));
	DUMP_REG(PR(0));
	DUMP_REG(LANE4_PREEMPHASIS(0));
	DUMP_REG(POSTCURSOR(0));
	DUMP_REG(DP_CONFIG(0));
	DUMP_REG(DP_CONFIG(1));
	DUMP_REG(DP_MN(0));
	DUMP_REG(DP_MN(1));
	DUMP_REG(DP_PADCTL(0));
	DUMP_REG(DP_PADCTL(1));
	DUMP_REG(DP_DEBUG(0));
	DUMP_REG(DP_DEBUG(1));
	DUMP_REG(DP_SPARE(0));
	DUMP_REG(DP_SPARE(1));
	DUMP_REG(DP_TPG);

	return;
}
#endif

static void tegra_dc_sor_config_panel(struct tegra_dc_sor_data *sor,
			int is_lvds,
			const struct tegra_dp_link_config *link_cfg,
			const struct display_timing *timing)
{
	const int	head_num = 0;
	u32		reg_val	 = STATE1_ASY_OWNER_HEAD0 << head_num;
	u32		vtotal, htotal;
	u32		vsync_end, hsync_end;
	u32		vblank_end, hblank_end;
	u32		vblank_start, hblank_start;

	reg_val |= is_lvds ? STATE1_ASY_PROTOCOL_LVDS_CUSTOM :
		STATE1_ASY_PROTOCOL_DP_A;
	reg_val |= STATE1_ASY_SUBOWNER_NONE |
		STATE1_ASY_CRCMODE_COMPLETE_RASTER;

	reg_val |= STATE1_ASY_HSYNCPOL_NEGATIVE_TRUE;
	reg_val |= STATE1_ASY_VSYNCPOL_NEGATIVE_TRUE;
	reg_val |= (link_cfg->bits_per_pixel > 18) ?
		STATE1_ASY_PIXELDEPTH_BPP_24_444 :
		STATE1_ASY_PIXELDEPTH_BPP_18_444;

	tegra_sor_writel(sor, STATE1, reg_val);

	/*
	 * Skipping programming NV_HEAD_STATE0, assuming:
	 * interlacing: PROGRESSIVE, dynamic range: VESA, colorspace: RGB
	 */
	vtotal = timing->vsync_len.typ + timing->vback_porch.typ +
		timing->vactive.typ + timing->vfront_porch.typ;
	htotal = timing->hsync_len.typ + timing->hback_porch.typ +
		timing->hactive.typ + timing->hfront_porch.typ;

	tegra_sor_writel(sor, NV_HEAD_STATE1(head_num),
			 vtotal << NV_HEAD_STATE1_VTOTAL_SHIFT |
			 htotal << NV_HEAD_STATE1_HTOTAL_SHIFT);

	vsync_end = timing->vsync_len.typ - 1;
	hsync_end = timing->hsync_len.typ - 1;
	tegra_sor_writel(sor, NV_HEAD_STATE2(head_num),
			 vsync_end << NV_HEAD_STATE2_VSYNC_END_SHIFT |
			 hsync_end << NV_HEAD_STATE2_HSYNC_END_SHIFT);

	vblank_end = vsync_end + timing->vback_porch.typ;
	hblank_end = hsync_end + timing->hback_porch.typ;
	tegra_sor_writel(sor, NV_HEAD_STATE3(head_num),
			 vblank_end << NV_HEAD_STATE3_VBLANK_END_SHIFT |
			 hblank_end << NV_HEAD_STATE3_HBLANK_END_SHIFT);

	vblank_start = vblank_end + timing->vactive.typ;
	hblank_start = hblank_end + timing->hactive.typ;
	tegra_sor_writel(sor, NV_HEAD_STATE4(head_num),
			 vblank_start << NV_HEAD_STATE4_VBLANK_START_SHIFT |
			 hblank_start << NV_HEAD_STATE4_HBLANK_START_SHIFT);

	/* TODO: adding interlace mode support */
	tegra_sor_writel(sor, NV_HEAD_STATE5(head_num), 0x1);

	tegra_sor_write_field(sor, CSTM,
			      CSTM_ROTCLK_DEFAULT_MASK |
			      CSTM_LVDS_EN_ENABLE,
			      2 << CSTM_ROTCLK_SHIFT |
			      is_lvds ? CSTM_LVDS_EN_ENABLE :
			      CSTM_LVDS_EN_DISABLE);

	 tegra_dc_sor_config_pwm(sor, 1024, 1024);
}

static void tegra_dc_sor_enable_dc(struct dc_ctlr *disp_ctrl)
{
	u32 reg_val = readl(&disp_ctrl->cmd.state_access);

	writel(reg_val | WRITE_MUX_ACTIVE, &disp_ctrl->cmd.state_access);
	writel(VSYNC_H_POSITION(1), &disp_ctrl->disp.disp_timing_opt);

	/* Enable DC now - otherwise pure text console may not show. */
	writel(CTRL_MODE_C_DISPLAY << CTRL_MODE_SHIFT,
	       &disp_ctrl->cmd.disp_cmd);
	writel(reg_val, &disp_ctrl->cmd.state_access);
}

int tegra_dc_sor_enable_dp(struct tegra_dc_sor_data *sor,
			   const struct tegra_dp_link_config *link_cfg)
{
	int ret;

	tegra_sor_write_field(sor, CLK_CNTRL,
			      CLK_CNTRL_DP_CLK_SEL_MASK,
			      CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK);

	tegra_sor_write_field(sor, PLL2,
			      PLL2_AUX6_BANDGAP_POWERDOWN_MASK,
			      PLL2_AUX6_BANDGAP_POWERDOWN_DISABLE);
	udelay(25);

	tegra_sor_write_field(sor, PLL3,
			      PLL3_PLLVDD_MODE_MASK,
			      PLL3_PLLVDD_MODE_V3_3);
	tegra_sor_writel(sor, PLL0,
			 0xf << PLL0_ICHPMP_SHFIT |
			 0x3 << PLL0_VCOCAP_SHIFT |
			 PLL0_PLLREG_LEVEL_V45 |
			 PLL0_RESISTORSEL_EXT |
			 PLL0_PWR_ON | PLL0_VCOPD_RESCIND);
	tegra_sor_write_field(sor, PLL2,
			      PLL2_AUX1_SEQ_MASK |
			      PLL2_AUX9_LVDSEN_OVERRIDE |
			      PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_MASK,
			      PLL2_AUX1_SEQ_PLLCAPPD_OVERRIDE |
			      PLL2_AUX9_LVDSEN_OVERRIDE |
			      PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_DISABLE);
	tegra_sor_writel(sor, PLL1, PLL1_TERM_COMPOUT_HIGH |
			 PLL1_TMDS_TERM_ENABLE);

	if (tegra_dc_sor_poll_register(sor, PLL2,
				       PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_MASK,
				       PLL2_AUX8_SEQ_PLLCAPPD_ENFORCE_DISABLE,
				       100, TEGRA_SOR_TIMEOUT_MS)) {
		printf("DP failed to lock PLL\n");
		return -EIO;
	}

	tegra_sor_write_field(sor, PLL2, PLL2_AUX2_MASK |
			      PLL2_AUX7_PORT_POWERDOWN_MASK,
			      PLL2_AUX2_OVERRIDE_POWERDOWN |
			      PLL2_AUX7_PORT_POWERDOWN_DISABLE);

	ret = tegra_dc_sor_power_up(sor, 0);
	if (ret) {
		debug("DP failed to power up\n");
		return ret;
	}

	/* re-enable SOR clock */
	clock_sor_enable_edp_clock();

	/* Power up lanes */
	tegra_dc_sor_power_dplanes(sor, link_cfg->lane_count, 1);

	tegra_dc_sor_set_dp_mode(sor, link_cfg);
	debug("%s ret\n", __func__);

	return 0;
}

int tegra_dc_sor_attach(struct tegra_dc_sor_data *sor,
			const struct tegra_dp_link_config *link_cfg,
			const struct display_timing *timing)
{
	const void *blob = gd->fdt_blob;
	struct dc_ctlr *disp_ctrl;
	u32 reg_val;
	int node;

	/* Use the first display controller */
	debug("%s\n", __func__);
	node = fdtdec_next_compatible(blob, 0, COMPAT_NVIDIA_TEGRA124_DC);
	if (node < 0)
		return -ENOENT;
	disp_ctrl = (struct dc_ctlr *)fdtdec_get_addr(blob, node, "reg");

	tegra_dc_sor_enable_dc(disp_ctrl);
	tegra_dc_sor_config_panel(sor, 0, link_cfg, timing);

	writel(0x9f00, &disp_ctrl->cmd.state_ctrl);
	writel(0x9f, &disp_ctrl->cmd.state_ctrl);

	writel(PW0_ENABLE | PW1_ENABLE | PW2_ENABLE | PW3_ENABLE |
	       PW4_ENABLE | PM0_ENABLE | PM1_ENABLE,
	       &disp_ctrl->cmd.disp_pow_ctrl);

	reg_val = tegra_sor_readl(sor, TEST);
	if (reg_val & TEST_ATTACHED_TRUE)
		return -EEXIST;

	tegra_sor_writel(sor, SUPER_STATE1,
			 SUPER_STATE1_ATTACHED_NO);

	/*
	 * Enable display2sor clock at least 2 cycles before DC start,
	 * to clear sor internal valid signal.
	 */
	writel(SOR_ENABLE, &disp_ctrl->disp.disp_win_opt);
	writel(GENERAL_ACT_REQ, &disp_ctrl->cmd.state_ctrl);
	writel(0, &disp_ctrl->disp.disp_win_opt);
	writel(GENERAL_ACT_REQ, &disp_ctrl->cmd.state_ctrl);

	/* Attach head */
	tegra_dc_sor_update(sor);
	tegra_sor_writel(sor, SUPER_STATE1,
			 SUPER_STATE1_ATTACHED_YES);
	tegra_sor_writel(sor, SUPER_STATE1,
			 SUPER_STATE1_ATTACHED_YES |
			 SUPER_STATE1_ASY_HEAD_OP_AWAKE |
			 SUPER_STATE1_ASY_ORMODE_NORMAL);
	tegra_dc_sor_super_update(sor);

	/* Enable dc */
	reg_val = readl(&disp_ctrl->cmd.state_access);
	writel(reg_val | WRITE_MUX_ACTIVE, &disp_ctrl->cmd.state_access);
	writel(CTRL_MODE_C_DISPLAY << CTRL_MODE_SHIFT,
	       &disp_ctrl->cmd.disp_cmd);
	writel(SOR_ENABLE, &disp_ctrl->disp.disp_win_opt);
	writel(reg_val, &disp_ctrl->cmd.state_access);

	if (tegra_dc_sor_poll_register(sor, TEST,
				       TEST_ACT_HEAD_OPMODE_DEFAULT_MASK,
				       TEST_ACT_HEAD_OPMODE_AWAKE,
				       100,
				       TEGRA_SOR_ATTACH_TIMEOUT_MS)) {
		printf("dc timeout waiting for OPMOD = AWAKE\n");
		return -ETIMEDOUT;
	} else {
		debug("%s: sor is attached\n", __func__);
	}

#if DEBUG_SOR
	dump_sor_reg(sor);
#endif
	debug("%s: ret=%d\n", __func__, 0);

	return 0;
}

void tegra_dc_sor_set_lane_parm(struct tegra_dc_sor_data *sor,
		const struct tegra_dp_link_config *link_cfg)
{
	tegra_sor_writel(sor, LANE_DRIVE_CURRENT(sor->portnum),
			 link_cfg->drive_current);
	tegra_sor_writel(sor, PR(sor->portnum),
			 link_cfg->preemphasis);
	tegra_sor_writel(sor, POSTCURSOR(sor->portnum),
			 link_cfg->postcursor);
	tegra_sor_writel(sor, LVDS, 0);

	tegra_dc_sor_set_link_bandwidth(sor, link_cfg->link_bw);
	tegra_dc_sor_set_lane_count(sor, link_cfg->lane_count);

	tegra_sor_write_field(sor, DP_PADCTL(sor->portnum),
			      DP_PADCTL_TX_PU_ENABLE |
			      DP_PADCTL_TX_PU_VALUE_DEFAULT_MASK,
			      DP_PADCTL_TX_PU_ENABLE |
			      2 << DP_PADCTL_TX_PU_VALUE_SHIFT);

	/* Precharge */
	tegra_sor_write_field(sor, DP_PADCTL(sor->portnum), 0xf0, 0xf0);
	udelay(20);

	tegra_sor_write_field(sor, DP_PADCTL(sor->portnum), 0xf0, 0x0);
}

void tegra_dc_sor_power_down_unused_lanes(struct tegra_dc_sor_data *sor,
			const struct tegra_dp_link_config *link_cfg)
{
	u32 pad_ctrl = 0;
	u32 drive_current = 0;
	u32 pre_emphasis = 0;
	int err = 0;

	switch (link_cfg->lane_count) {
	case 4:
		pad_ctrl = DP_PADCTL_PD_TXD_0_NO |
			DP_PADCTL_PD_TXD_1_NO |
			DP_PADCTL_PD_TXD_2_NO |
			DP_PADCTL_PD_TXD_3_NO;
		break;
	case 2:
		pad_ctrl = DP_PADCTL_PD_TXD_0_NO |
			DP_PADCTL_PD_TXD_1_NO |
			DP_PADCTL_PD_TXD_2_YES |
			DP_PADCTL_PD_TXD_3_YES;
		break;
	case 1:
		pad_ctrl = DP_PADCTL_PD_TXD_0_NO |
			DP_PADCTL_PD_TXD_1_YES |
			DP_PADCTL_PD_TXD_2_YES |
			DP_PADCTL_PD_TXD_3_YES;
		break;
	default:
		printf("Invalid sor lane count: %u\n", link_cfg->lane_count);
		return;
	}

	pad_ctrl |= DP_PADCTL_PAD_CAL_PD_POWERDOWN;
	tegra_sor_writel(sor, DP_PADCTL(sor->portnum), pad_ctrl);

	err = tegra_dc_sor_enable_lane_sequencer(sor, 0, 0);
	if (err) {
		debug("Wait for lane power down failed: %d\n", err);
		return;
	}

	/* Set to a known-good pre-calibrated setting */
	switch (link_cfg->link_bw) {
	case SOR_LINK_SPEED_G1_62:
	case SOR_LINK_SPEED_G2_7:
		drive_current = 0x13131313;
		pre_emphasis = 0;
		break;
	case SOR_LINK_SPEED_G5_4:
		drive_current = 0x19191919;
		pre_emphasis = 0x09090909;
	default:
		printf("Invalid sor link bandwidth: %d\n", link_cfg->link_bw);
		return;
	}

	tegra_sor_writel(sor, LANE_DRIVE_CURRENT(sor->portnum),
			 drive_current);
	tegra_sor_writel(sor, PR(sor->portnum), pre_emphasis);
}

int tegra_dc_sor_init(struct tegra_dc_sor_data **sorp)
{
	const void *blob = gd->fdt_blob;
	struct tegra_dc_sor_data *sor;
	int node;

	node = fdtdec_next_compatible(blob, 0, COMPAT_NVIDIA_TEGRA124_SOR);
	if (node < 0)
		return -ENOENT;
	sor = calloc(1, sizeof(*sor));
	if (!sor)
		return -ENOMEM;
	sor->base = (void *)fdtdec_get_addr(blob, node, "reg");

	node = fdtdec_next_compatible(blob, 0, COMPAT_NVIDIA_TEGRA124_PMC);
	if (node < 0)
		return -ENOENT;
	sor->pmc_base = (void *)fdtdec_get_addr(blob, node, "reg");

	sor->power_is_up = 0;
	sor->portnum = 0;
	*sorp = sor;

	return 0;
}
