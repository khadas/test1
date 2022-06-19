// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <amlogic/media/vout/hdmitx21/hdmitx.h>
#include "hdmitx_drv.h"

static void dump32(u32 start, u32 end)
{
	u32 value = 0;

	for (; start <= end; start += 4) {
		value = hd21_read_reg(start);
		if (value)
			pr_info("[0x%08x] 0x%08x\n", TO21_PHY_ADDR(start), value);
	}
}

static void dumptop(u32 start, u32 end)
{
	u32 value = 0;

	start = (((start) & 0xffff) | TOP_OFFSET_MASK);
	end = (((end) & 0xffff) | TOP_OFFSET_MASK);
	for (; start <= end; start += 4) {
		value = hdmitx21_rd_reg(start);
		if (value)
			pr_info("[0x%08x] 0x%02x\n", start, value);
	}
}

static void dumpcor(u32 start, u32 end)
{
	u32 value = 0;

	for (; start <= end; start++) {
		value = hdmitx21_rd_reg(start);
		if (value)
			pr_info("[0x%08x] 0x%02x\n", start, value);
	}
}

#define CONNECT2REG(reg) ({ \
	typeof(reg) _reg = (reg); \
	(hdmitx21_rd_reg(_reg) & 0xff) + \
	((hdmitx21_rd_reg(_reg + 1) & 0xff) << 8); })

#define CONNECT3REG(reg) ({ \
	typeof(reg) _reg = (reg); \
	(hdmitx21_rd_reg(_reg) & 0xff) + \
	((hdmitx21_rd_reg(_reg + 1) & 0xff) << 8) + \
	((hdmitx21_rd_reg(_reg + 2) & 0xff) << 16); })

#define CONNECT4REG(reg) ({ \
	typeof(reg) _reg = (reg); \
	(hdmitx21_rd_reg(_reg) & 0xff) + \
	((hdmitx21_rd_reg(_reg + 1) & 0xff) << 8) + \
	((hdmitx21_rd_reg(_reg + 2) & 0xff) << 16) + \
	((hdmitx21_rd_reg(_reg + 3) & 0xff) << 24); })

static int dump_hdmivpfdet_show(void)
{
	u32 reg;
	u32 val;
	u32 total, active, front, sync, back, blank;
	struct hdmitx_dev *hdev = get_hdmitx21_device();

	pr_info("\n--------vp fdet info--------\n");

	hdmitx21_wr_reg(VP_FDET_CLEAR_IVCTX, 0);
	hdmitx21_wr_reg(VP_FDET_STATUS_IVCTX, 0);
	mdelay(hdev->pxp_mode ? 1 : 50); /* at least 1 frame? */

	reg = VP_FDET_FRAME_RATE_IVCTX;
	val = CONNECT3REG(reg);
	if (val)
		pr_info("frame_rate [%x] 0x%x 200000000/%d Hz\n",
			reg, val, val);

	reg = VP_FDET_PIXEL_COUNT_IVCTX;
	val = CONNECT2REG(reg);
	active = val;
	if (val)
		pr_info("hactive [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_HFRONT_COUNT_IVCTX;
	val = CONNECT2REG(reg);
	front = val;
	if (val)
		pr_info("hfront [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_HSYNC_HIGH_COUNT_IVCTX;
	val = CONNECT2REG(reg);
	sync = val;
	if (val)
		pr_info("hsync [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_HBACK_COUNT_IVCTX;
	val = CONNECT2REG(reg);
	back = val;
	if (val)
		pr_info("hback [%x] 0x%x %d\n", reg, val, val);

	blank = front + sync + back;
	total = active + blank;
	if (blank)
		pr_info("Calc hblank 0x%x %d\n", blank, blank);
	if (total)
		pr_info("Calc htotal 0x%x %d\n", total, total);

	reg = VP_FDET__LINE__COUNT_IVCTX;
	val = CONNECT2REG(reg);
	active = val;
	if (val)
		pr_info("vactive [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_VSYNC_HIGH_COUNT_EVEN_IVCTX;
	val = CONNECT2REG(reg);
	sync = val;
	if (val)
		pr_info("vsync_high_count_even [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET_VFRONT_COUNT_EVEN_IVCTX;
	val = CONNECT2REG(reg);
	front = val;
	if (val)
		pr_info("vfront_count_even [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET_VBACK_COUNT_EVEN_IVCTX;
	val = CONNECT2REG(reg);
	back = val;
	if (val)
		pr_info("vback_count_even [%x] 0x%x %d\n",
			reg, val, val);

	blank = front + sync + back;
	total = active + blank;
	if (blank)
		pr_info("Calc vblank 0x%x %d\n", blank, blank);
	if (total)
		pr_info("Calc vtotal 0x%x %d\n", total, total);

	reg = VP_FDET_CONFIG_IVCTX;
	val = hdmitx21_rd_reg(reg);
	if (val)
		pr_info("[%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_STATUS_IVCTX;
	val = hdmitx21_rd_reg(reg);
	if (val) {
		pr_info("status [%x] 0x%x %d\n", reg, val, val);
		pr_info("  hsync_polarity %d\n", (val >> 0) & 1);
		pr_info("  vsync_polarity %d\n", (val >> 1) & 1);
		pr_info("  interlaced %d\n", (val >> 2) & 1);
		pr_info("  video656 %d\n", (val >> 3) & 1);
	}

	reg = VP_FDET_INTERLACE_THRESHOLD_IVCTX;
	val = hdmitx21_rd_reg(reg);
	if (val)
		pr_info("interlace_threshold [%x] %x %d\n",
			reg, val, val);

	reg = VP_FDET_FRAME_RATE_DELTA_THRESHOLD_IVCTX;
	val = CONNECT3REG(reg);
	if (val)
		pr_info("frame_rate_delta_threshold [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET_HSYNC_LOW_COUNT_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("hsync_low_count [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_VSYNC_LOW_COUNT_EVEN_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("vsync_low_count_even [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET_VSYNC_LOW_COUNT_ODD_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("vsync_low_count_odd [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET_VSYNC_HIGH_COUNT_ODD_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("vsync_high_count_odd [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET_VFRONT_COUNT_ODD_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("vfront_count_odd [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_VBACK_COUNT_ODD_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("frame_count [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_FRAME_COUNT_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("frame_count [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET__LINE__RATE_DELTA_THRESHOLD_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("line_rate_delta_threshold [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET__LINE__RATE_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("line_rate [%x] 0x%x %d\n", reg, val, val);

	reg = VP_FDET_VSYNC_HSYNC_OFFSET_EVEN_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("vsync_hsync_offset_even [%x] 0x%x %d\n",
			reg, val, val);

	reg = VP_FDET_VSYNC_HSYNC_OFFSET_ODD_IVCTX;
	val = CONNECT2REG(reg);
	if (val)
		pr_info("vsync_hsync_offset_odd [%x] 0x%x %d\n",
			reg, val, val);

#define PR_DETAIL(n, str) \
	do { \
		if ((val >> (n)) & 1) \
			pr_info(" %s", str) ; \
	} while (0)

	reg = VP_FDET_IRQ_MASK_IVCTX;
	val = CONNECT3REG(reg);
	if (val) {
		pr_info("irq_mask [%x] 0x%x %d\n", reg, val, val);

		PR_DETAIL(0, "hsync_polarity");
		PR_DETAIL(1, "vsync_polarity");
		PR_DETAIL(2, "interlaced");
		PR_DETAIL(3, "video656");
		PR_DETAIL(4, "frame_rate");
		PR_DETAIL(5, "pixel_count");
		PR_DETAIL(6, "line_count");
		PR_DETAIL(7, "hsync_low_count");
		PR_DETAIL(8, "hsync_high_count");
		PR_DETAIL(9, "hfront_count");
		PR_DETAIL(10, "hback_count");
		PR_DETAIL(11, "vsync_low_count_even");
		PR_DETAIL(12, "vsync_high_count_even");
		PR_DETAIL(13, "vfront_count_even");
		PR_DETAIL(14, "vback_count_even");
		PR_DETAIL(15, "vsync_low_count_odd");
		PR_DETAIL(16, "vsync_high_count_odd");
		PR_DETAIL(17, "vfront_count_odd");
		PR_DETAIL(18, "vback_count_odd");
		PR_DETAIL(19, "line_rate");
		PR_DETAIL(20, "vsync_hsync_offset_even");
		PR_DETAIL(21, "vsync_hsync_offset_odd");
		PR_DETAIL(22, "frame_and_pixel_cnt_done");
		pr_info("\n");
	}

	reg = VP_FDET_IRQ_STATUS_IVCTX;
	val = CONNECT3REG(reg);
	if (val) {
		pr_info("irq_status [%x] 0x%x %d\n",
			reg, val, val);
		PR_DETAIL(0, "hsync_polarity");
		PR_DETAIL(1, "vsync_polarity");
		PR_DETAIL(2, "interlaced");
		PR_DETAIL(3, "video656");
		PR_DETAIL(4, "frame_rate");
		PR_DETAIL(5, "pixel_count");
		PR_DETAIL(6, "line_count");
		PR_DETAIL(7, "hsync_low_count");
		PR_DETAIL(8, "hsync_high_count");
		PR_DETAIL(9, "hfront_count");
		PR_DETAIL(10, "hback_count");
		PR_DETAIL(11, "vsync_low_count_even");
		PR_DETAIL(12, "vsync_high_count_even");
		PR_DETAIL(13, "vfront_count_even");
		PR_DETAIL(14, "vback_count_even");
		PR_DETAIL(15, "vsync_low_count_odd");
		PR_DETAIL(16, "vsync_high_count_odd");
		PR_DETAIL(17, "vfront_count_odd");
		PR_DETAIL(18, "vback_count_odd");
		PR_DETAIL(19, "line_rate");
		PR_DETAIL(20, "vsync_hsync_offset_even");
		PR_DETAIL(21, "vsync_hsync_offset_odd");
		PR_DETAIL(22, "frame_and_pixel_cnt_done");
		pr_info("\n");
	}
	return 0;
}

void hdmitx21_dump_regs(void)
{
	// ((0x0000 << 2) + 0xfe008000) ~ ((0x00f3 << 2) + 0xfe008000)
	dump32(ANACTRL_SYS0PLL_CTRL0, ANACTRL_DIF_PHY_STS);
	// ((0x0001 << 2) + 0xfe000000) ~ ((0x0128 << 2) + 0xfe000000)
	dump32(CLKCTRL_OSCIN_CTRL, CLKCTRL_EFUSE_A73_CFG2);
	// ((0x0000 << 2) + 0xfe00c000) ~ ((0x027f << 2) + 0xfe00c000)
	dump32(PWRCTRL_PWR_ACK0, PWRCTRL_A73TOP_FSM_JUMP);
	// ((0x1b00 << 2) + 0xff000000) ~ ((0x1bea << 2) + 0xff000000)
	dump32(ENCI_VIDEO_MODE, ENCP_VRR_CTRL1);
	// ((0x1c00 << 2) + 0xff000000) ~((0x1cfc << 2) + 0xff000000)
	dump32(ENCI_DVI_HSO_BEGIN, VPU_VENCL_DITH_LUT_12);
	// ((0x2158 << 2) + 0xff000000) ~ ((0x2250 << 2) + 0xff000000)
	dump32(ENCP1_VFIFO2VD_CTL, ENCP1_VFIFO2VD_CTL2);
	// ((0x2358 << 2) + 0xff000000) ~ ((0x2450 << 2) + 0xff000000)
	dump32(ENCP2_VFIFO2VD_CTL, ENCP2_VFIFO2VD_CTL2);
	// ((0x2451 << 2) + 0xff000000) ~ ((0x24fc << 2) + 0xff000000)
	dump32(VENC2_DVI_SETTING_MORE, VPU2_VENCL_DITH_LUT_12);
	// ((0x2701 << 2) + 0xff000000) ~ ((0x24fc << 2) + 0xff000000)
	dump32(VPU_CRC_CTRL, VPUCTRL_REG_ADDR(0x27fd));
	// 0xfe300000 ~ 0xfe300000 + (0x041 << 2)
	dumptop(HDMITX_TOP_SW_RESET, HDMITX_TOP_SECURE_DATA);
	// 0x00000000 - 0x00000018
	dumpcor(INTR3_IVCTX, AON_CYP_CTL_IVCTX);
	// 0x00000100 - 0x00000130
	dumpcor(VND_IDL_IVCTX, TOP_INTR_IVCTX);
	// 0x00000200 - 0x000002d5
	dumpcor(DEBUG_MODE_EN_IVCTX, DROP_GEN_TYPE_5_IVCTX);
	// 0x00000300 - 0x0000031a
	dumpcor(TX_ZONE_CTL0_IVCTX, FIFO_10TO20_CTRL_IVCTX);
	// 0x00000400 - 0x000004a0
	dumpcor(BIST_RST_IVCTX, CR_BLACK_HIGH_IVCTX);
	// 0x00000607 - 0x000006ff
	dumpcor(TPI_MISC_IVCTX, RSVD11_HW_TPI_IVCTX);
	// 0x00000800 - 0x00000876
	dumpcor(CP2TX_CTRL_0_IVCTX, CP2TX_GP1_IVCTX);
	// 0x000008a0 - 0x000008d0
	dumpcor(HDCP2X_DEBUG_CTRL0_IVCTX, HDCP2X_DEBUG_STAT16_IVCTX);
	// 0x00000900 - 0x00000934
	dumpcor(SCRCTL_IVCTX, RSVD1_HDMI2_IVCTX);
	// 0x00000a00 - 0x00000a6e
	dumpcor(RSVD0_AIP_IVCTX, AUDIO_CLK_DIV_IVCTX);
	// 0x00000b00 - 0x00000be1
	dumpcor(VP_FEATURES_IVCTX, VP_EMBD_SYNC_ENC_CONFIG_IVCTX);
	// 0x00000d00 - 0x00000d3c
	dumpcor(VP_CMS_CSC0_FEATURES_IVCTX, VP_CMS_CSC0_MULTI_CSC_OUT_RCR_OFFSET_IVCTX);
	//0x00000d80 - 0x00000ddc
	dumpcor(VP_CMS_CSC1_FEATURES_IVCTX, VP_CMS_CSC1_PIXCAP_OUT_CR_IVCTX);
	// 0x00000f00 - 0x00000f26
	dumpcor(D_HDR_GEN_CTL_IVCTX, D_HDR_SPARE_9_IVCTX);
	// 0x00000f80 - 0x00000fa9
	dumpcor(DSC_PKT_GEN_CTL_IVCTX, DSC_PKT_SPARE_9_IVCTX);
	dump_infoframe_packets();
	dump_hdmivpfdet_show();
}
