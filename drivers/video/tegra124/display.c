/*
 * Copyright 2014 Google Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Extracted from Chromium coreboot commit 3f59b13d
 */

#include <common.h>
#include <dm.h>
#include <edid.h>
#include <errno.h>
#include <displayport.h>
#include <edid.h>
#include <fdtdec.h>
#include <lcd.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/pwm.h>
#include <asm/arch-tegra/dc.h>
#include "displayport.h"

DECLARE_GLOBAL_DATA_PTR;

/* return in 1000ths of a Hertz */
static int tegra_dc_calc_refresh(const struct display_timing *timing)
{
	int h_total, v_total, refresh;
	int pclk = timing->pixelclock.typ;

	h_total = timing->hactive.typ + timing->hfront_porch.typ +
			timing->hback_porch.typ + timing->hsync_len.typ;
	v_total = timing->vactive.typ + timing->vfront_porch.typ +
			timing->vback_porch.typ + timing->vsync_len.typ;
	if (!pclk || !h_total || !v_total)
		return 0;
	refresh = pclk / h_total;
	refresh *= 1000;
	refresh /= v_total;

	return refresh;
}

static void print_mode(const struct display_timing *timing)
{
	int refresh = tegra_dc_calc_refresh(timing);

	debug("MODE:%dx%d@%d.%03uHz pclk=%d\n",
	      timing->hactive.typ, timing->vactive.typ, refresh / 1000,
	      refresh % 1000, timing->pixelclock.typ);
}

static int update_display_mode(struct dc_ctlr *disp_ctrl,
			       const struct display_timing *timing,
			       int href_to_sync, int vref_to_sync)
{
	print_mode(timing);

	writel(0x1, &disp_ctrl->disp.disp_timing_opt);

	writel(vref_to_sync << 16 | href_to_sync,
	       &disp_ctrl->disp.ref_to_sync);

	writel(timing->vsync_len.typ << 16 | timing->hsync_len.typ,
	       &disp_ctrl->disp.sync_width);

	writel(((timing->vback_porch.typ - vref_to_sync) << 16) |
		timing->hback_porch.typ, &disp_ctrl->disp.back_porch);

	writel(((timing->vfront_porch.typ + vref_to_sync) << 16) |
		timing->hfront_porch.typ, &disp_ctrl->disp.front_porch);

	writel(timing->hactive.typ | (timing->vactive.typ << 16),
	       &disp_ctrl->disp.disp_active);

	/**
	 * We want to use PLLD_out0, which is PLLD / 2:
	 *   PixelClock = (PLLD / 2) / ShiftClockDiv / PixelClockDiv.
	 *
	 * Currently most panels work inside clock range 50MHz~100MHz, and PLLD
	 * has some requirements to have VCO in range 500MHz~1000MHz (see
	 * clock.c for more detail). To simplify calculation, we set
	 * PixelClockDiv to 1 and ShiftClockDiv to 1. In future these values
	 * may be calculated by clock_display, to allow wider frequency range.
	 *
	 * Note ShiftClockDiv is a 7.1 format value.
	 */
	const u32 shift_clock_div = 1;
	writel((PIXEL_CLK_DIVIDER_PCD1 << PIXEL_CLK_DIVIDER_SHIFT) |
	       ((shift_clock_div - 1) * 2) << SHIFT_CLK_DIVIDER_SHIFT,
	       &disp_ctrl->disp.disp_clk_ctrl);
	debug("%s: PixelClock=%u, ShiftClockDiv=%u\n", __func__,
	      timing->pixelclock.typ, shift_clock_div);
	return 0;
}

static u32 tegra_dc_poll_register(void *reg,
	u32 mask, u32 exp_val, u32 poll_interval_us, u32 timeout_us)
{
	u32 temp = timeout_us;
	u32 reg_val = 0;

	do {
		udelay(poll_interval_us);
		reg_val = readl(reg);
		if (timeout_us > poll_interval_us)
			timeout_us -= poll_interval_us;
		else
			break;
	} while ((reg_val & mask) != exp_val);

	if ((reg_val & mask) == exp_val)
		return 0;	/* success */

	return temp;
}

int tegra_dc_sor_general_act(struct dc_ctlr *disp_ctrl)
{
	writel(GENERAL_ACT_REQ, &disp_ctrl->cmd.state_ctrl);

	if (tegra_dc_poll_register(&disp_ctrl->cmd.state_ctrl,
				   GENERAL_ACT_REQ, 0, 100,
				   DC_POLL_TIMEOUT_MS * 1000)) {
		debug("dc timeout waiting for DC to stop\n");
		return -ETIMEDOUT;
	}

	return 0;
}

static struct display_timing min_mode = {
	.hsync_len = { .typ = 1 },
	.vsync_len = { .typ = 1 },
	.hback_porch = { .typ = 20 },
	.vback_porch = { .typ = 0 },
	.hactive = { .typ = 16 },
	.vactive = { .typ = 16 },
	.hfront_porch = { .typ = 1 },
	.vfront_porch = { .typ = 2 },
};

/* Disable windows and set minimum raster timings */
void tegra_dc_sor_disable_win_short_raster(struct dc_ctlr *disp_ctrl,
					   int *dc_reg_ctx)
{
	const int href_to_sync = 0, vref_to_sync = 1;
	int selected_windows, i;

	selected_windows = readl(&disp_ctrl->cmd.disp_win_header);

	/* Store and clear window options */
	for (i = 0; i < DC_N_WINDOWS; ++i) {
		writel(WINDOW_A_SELECT << i, &disp_ctrl->cmd.disp_win_header);
		dc_reg_ctx[i] = readl(&disp_ctrl->win.win_opt);
		writel(0, &disp_ctrl->win.win_opt);
		writel(WIN_A_ACT_REQ << i, &disp_ctrl->cmd.state_ctrl);
	}

	writel(selected_windows, &disp_ctrl->cmd.disp_win_header);

	/* Store current raster timings and set minimum timings */
	dc_reg_ctx[i++] = readl(&disp_ctrl->disp.ref_to_sync);
	writel(href_to_sync | (vref_to_sync << 16),
	       &disp_ctrl->disp.ref_to_sync);

	dc_reg_ctx[i++] = readl(&disp_ctrl->disp.sync_width);
	writel(min_mode.hsync_len.typ | (min_mode.vsync_len.typ << 16),
	       &disp_ctrl->disp.sync_width);

	dc_reg_ctx[i++] = readl(&disp_ctrl->disp.back_porch);
	writel(min_mode.hback_porch.typ | (min_mode.vback_porch.typ << 16),
	       &disp_ctrl->disp.back_porch);

	dc_reg_ctx[i++] = readl(&disp_ctrl->disp.front_porch);
	writel(min_mode.hfront_porch.typ | (min_mode.vfront_porch.typ << 16),
	       &disp_ctrl->disp.front_porch);

	dc_reg_ctx[i++] = readl(&disp_ctrl->disp.disp_active);
	writel(min_mode.hactive.typ | (min_mode.vactive.typ << 16),
	       &disp_ctrl->disp.disp_active);

	writel(GENERAL_ACT_REQ, &disp_ctrl->cmd.state_ctrl);
}

/* Restore previous windows status and raster timings */
void tegra_dc_sor_restore_win_and_raster(struct dc_ctlr *disp_ctrl,
					 int *dc_reg_ctx)
{
	int selected_windows, i;

	selected_windows = readl(&disp_ctrl->cmd.disp_win_header);

	for (i = 0; i < DC_N_WINDOWS; ++i) {
		writel(WINDOW_A_SELECT << i, &disp_ctrl->cmd.disp_win_header);
		writel(dc_reg_ctx[i], &disp_ctrl->win.win_opt);
		writel(WIN_A_ACT_REQ << i, &disp_ctrl->cmd.state_ctrl);
	}

	writel(selected_windows, &disp_ctrl->cmd.disp_win_header);

	writel(dc_reg_ctx[i++], &disp_ctrl->disp.ref_to_sync);
	writel(dc_reg_ctx[i++], &disp_ctrl->disp.sync_width);
	writel(dc_reg_ctx[i++], &disp_ctrl->disp.back_porch);
	writel(dc_reg_ctx[i++], &disp_ctrl->disp.front_porch);
	writel(dc_reg_ctx[i++], &disp_ctrl->disp.disp_active);

	writel(GENERAL_UPDATE, &disp_ctrl->cmd.state_ctrl);
}

static int tegra_depth_for_bpp(int bpp)
{
	switch (bpp) {
	case 32:
		return COLOR_DEPTH_R8G8B8A8;
	case 16:
		return COLOR_DEPTH_B5G6R5;
	default:
		debug("Unsupported LCD bit depth");
		return -1;
	}
}

static int update_window(struct dc_ctlr *disp_ctrl,
			 u32 frame_buffer, int fb_bits_per_pixel,
			 const struct display_timing *timing)
{
	const u32 colour_white = 0xffffff;
	int colour_depth;
	u32 val;

	writel(WINDOW_A_SELECT, &disp_ctrl->cmd.disp_win_header);

	writel(((timing->vactive.typ << 16) | timing->hactive.typ),
	       &disp_ctrl->win.size);
	writel(((timing->vactive.typ << 16) |
		(timing->hactive.typ * fb_bits_per_pixel / 8)),
		&disp_ctrl->win.prescaled_size);
	writel(((timing->hactive.typ * fb_bits_per_pixel / 8 + 31) /
		32 * 32), &disp_ctrl->win.line_stride);

	colour_depth = tegra_depth_for_bpp(fb_bits_per_pixel);
	if (colour_depth == -1)
		return -EINVAL;

	writel(colour_depth, &disp_ctrl->win.color_depth);

	writel(frame_buffer, &disp_ctrl->winbuf.start_addr);
	writel(0x1000 << V_DDA_INC_SHIFT | 0x1000 << H_DDA_INC_SHIFT,
	       &disp_ctrl->win.dda_increment);

	writel(colour_white, &disp_ctrl->disp.blend_background_color);
	writel(CTRL_MODE_C_DISPLAY << CTRL_MODE_SHIFT,
	       &disp_ctrl->cmd.disp_cmd);

	writel(WRITE_MUX_ACTIVE, &disp_ctrl->cmd.state_access);

	val = GENERAL_ACT_REQ | WIN_A_ACT_REQ;
	val |= GENERAL_UPDATE | WIN_A_UPDATE;
	writel(val, &disp_ctrl->cmd.state_ctrl);

	/* Enable win_a */
	val = readl(&disp_ctrl->win.win_opt);
	writel(val | WIN_ENABLE, &disp_ctrl->win.win_opt);

	return 0;
}

static int tegra_dc_init(struct dc_ctlr *disp_ctrl)
{
	/* do not accept interrupts during initialization */
	writel(0x00000000, &disp_ctrl->cmd.int_mask);
	writel(WRITE_MUX_ASSEMBLY | READ_MUX_ASSEMBLY,
	       &disp_ctrl->cmd.state_access);
	writel(WINDOW_A_SELECT, &disp_ctrl->cmd.disp_win_header);
	writel(0x00000000, &disp_ctrl->win.win_opt);
	writel(0x00000000, &disp_ctrl->win.byte_swap);
	writel(0x00000000, &disp_ctrl->win.buffer_ctrl);

	writel(0x00000000, &disp_ctrl->win.pos);
	writel(0x00000000, &disp_ctrl->win.h_initial_dda);
	writel(0x00000000, &disp_ctrl->win.v_initial_dda);
	writel(0x00000000, &disp_ctrl->win.dda_increment);
	writel(0x00000000, &disp_ctrl->win.dv_ctrl);

	writel(0x01000000, &disp_ctrl->win.blend_layer_ctrl);
	writel(0x00000000, &disp_ctrl->win.blend_match_select);
	writel(0x00000000, &disp_ctrl->win.blend_nomatch_select);
	writel(0x00000000, &disp_ctrl->win.blend_alpha_1bit);

	writel(0x00000000, &disp_ctrl->winbuf.start_addr_hi);
	writel(0x00000000, &disp_ctrl->winbuf.addr_h_offset);
	writel(0x00000000, &disp_ctrl->winbuf.addr_v_offset);

	writel(0x00000000, &disp_ctrl->com.crc_checksum);
	writel(0x00000000, &disp_ctrl->com.pin_output_enb[0]);
	writel(0x00000000, &disp_ctrl->com.pin_output_enb[1]);
	writel(0x00000000, &disp_ctrl->com.pin_output_enb[2]);
	writel(0x00000000, &disp_ctrl->com.pin_output_enb[3]);
	writel(0x00000000, &disp_ctrl->disp.disp_signal_opt0);

	return 0;
}

static void dump_config(int panel_bpp, struct display_timing *timing)
{
	printf("timing->hactive.typ = %d\n", timing->hactive.typ);
	printf("timing->vactive.typ = %d\n", timing->vactive.typ);
	printf("timing->pixelclock.typ = %d\n", timing->pixelclock.typ);

	printf("timing->hfront_porch.typ = %d\n", timing->hfront_porch.typ);
	printf("timing->hsync_len.typ = %d\n", timing->hsync_len.typ);
	printf("timing->hback_porch.typ = %d\n", timing->hback_porch.typ);

	printf("timing->vfront_porch.typ  %d\n", timing->vfront_porch.typ);
	printf("timing->vsync_len.typ = %d\n", timing->vsync_len.typ);
	printf("timing->vback_porch.typ = %d\n", timing->vback_porch.typ);

	printf("panel_bits_per_pixel = %d\n", panel_bpp);
}

static int display_update_config_from_edid(struct udevice *dp_dev,
					   int *panel_bppp,
					   struct display_timing *timing)
{
	u8 buf[EDID_SIZE];
	int bpc, ret;

	ret = display_port_read_edid(dp_dev, buf, sizeof(buf));
	if (ret < 0)
		return ret;
	ret = edid_get_timing(buf, ret, timing, &bpc);
	if (ret)
		return ret;

	/* Use this information if valid */
	if (bpc != -1)
		*panel_bppp = bpc * 3;

	return 0;
}

/* Somewhat torturous method */
static int get_backlight_info(const void *blob, struct gpio_desc *vdd,
			      struct gpio_desc *enable, int *pwmp)
{
	int sor, panel, backlight, power;
	const u32 *prop;
	int len;
	int ret;

	*pwmp = 0;
	sor = fdtdec_next_compatible(blob, 0, COMPAT_NVIDIA_TEGRA124_SOR);
	if (sor < 0)
		return -ENOENT;
	panel = fdtdec_lookup_phandle(blob, sor, "nvidia,panel");
	if (panel < 0)
		return -ENOENT;
	backlight = fdtdec_lookup_phandle(blob, panel, "backlight");
	if (backlight < 0)
		return -ENOENT;
	ret = gpio_request_by_name_nodev(blob, backlight, "enable-gpios", 0,
					 enable, GPIOD_IS_OUT);
	if (ret)
		return ret;
	prop = fdt_getprop(blob, backlight, "pwms", &len);
	if (!prop || len != 3 * sizeof(u32))
		return -EINVAL;
	*pwmp = fdt32_to_cpu(prop[1]);

	power = fdtdec_lookup_phandle(blob, backlight, "power-supply");
	if (power < 0)
		return -ENOENT;
	ret = gpio_request_by_name_nodev(blob, power, "gpio", 0, vdd,
					 GPIOD_IS_OUT);
	if (ret)
		goto err;

	return 0;

err:
	dm_gpio_free(NULL, enable);
	return ret;
}

int display_init(void *lcdbase, int fb_bits_per_pixel,
		 struct display_timing *timing)
{
	struct dc_ctlr *dc_ctlr;
	const void *blob = gd->fdt_blob;
	struct udevice *dp_dev;
	const int href_to_sync = 1, vref_to_sync = 1;
	int panel_bpp = 18;	/* default 18 bits per pixel */
	u32 plld_rate;
	struct gpio_desc vdd_gpio, enable_gpio;
	int pwm;
	int node;
	int ret;

	ret = uclass_get_device(UCLASS_DISPLAY_PORT, 0, &dp_dev);
	if (ret)
		return ret;

	node = fdtdec_next_compatible(blob, 0, COMPAT_NVIDIA_TEGRA124_DC);
	if (node < 0)
		return -ENOENT;
	dc_ctlr = (struct dc_ctlr *)fdtdec_get_addr(blob, node, "reg");
	if (fdtdec_decode_display_timing(blob, node, 0, timing))
		return -EINVAL;

	ret = display_update_config_from_edid(dp_dev, &panel_bpp, timing);
	if (ret) {
		debug("%s: Failed to decode EDID, using defaults\n", __func__);
		dump_config(panel_bpp, timing);
	}

	if (!get_backlight_info(blob, &vdd_gpio, &enable_gpio, &pwm)) {
		dm_gpio_set_value(&vdd_gpio, 1);
		debug("%s: backlight vdd setting gpio %08x to %d\n",
		      __func__, gpio_get_number(&vdd_gpio), 1);
	}

	/*
	 * The plld is programmed with the assumption of the SHIFT_CLK_DIVIDER
	 * and PIXEL_CLK_DIVIDER are zero (divide by 1). See the
	 * update_display_mode() for detail.
	 */
	plld_rate = clock_set_display_rate(timing->pixelclock.typ * 2);
	if (plld_rate == 0) {
		printf("dc: clock init failed\n");
		return -EIO;
	} else if (plld_rate != timing->pixelclock.typ * 2) {
		debug("dc: plld rounded to %u\n", plld_rate);
		timing->pixelclock.typ = plld_rate / 2;
	}

	/* Init dc */
	ret = tegra_dc_init(dc_ctlr);
	if (ret) {
		debug("dc: init failed\n");
		return ret;
	}

	/* Configure dc mode */
	ret = update_display_mode(dc_ctlr, timing, href_to_sync, vref_to_sync);
	if (ret) {
		debug("dc: failed to configure display mode\n");
		return ret;
	}

	/* Enable dp */
	ret = display_port_enable(dp_dev, panel_bpp, timing);
	if (ret)
		return ret;

	ret = update_window(dc_ctlr, (ulong)lcdbase, fb_bits_per_pixel, timing);
	if (ret)
		return ret;

	/* Set up Tegra PWM to drive the panel backlight */
	pwm_enable(pwm, 0, 220, 0x2e);
	udelay(10 * 1000);

	if (dm_gpio_is_valid(&enable_gpio)) {
		dm_gpio_set_value(&enable_gpio, 1);
		debug("%s: backlight enable setting gpio %08x to %d\n",
		      __func__, gpio_get_number(&enable_gpio), 1);
	}

	return 0;
}
