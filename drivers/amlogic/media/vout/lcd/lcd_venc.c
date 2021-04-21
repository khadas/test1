// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <malloc.h>
#include <asm/arch/io.h>
#ifdef CONFIG_AML_VPP
#include <amlogic/media/vpp/vpp.h>
#endif
#include <amlogic/media/vout/lcd/aml_lcd.h>
#include "lcd_reg.h"
#include "lcd_common.h"

#define LCD_WAIT_VSYNC_TIMEOUT    50000
void lcd_wait_vsync(struct aml_lcd_drv_s *pdrv)
{
#ifndef CONFIG_AML_LCD_PXP
	unsigned int offset, reg;
	int line_cnt, line_cnt_previous;
	int i = 0;

	if (pdrv->data->chip_type >= LCD_CHIP_T7) {
		offset = pdrv->data->offset_venc[pdrv->index];
		reg = VPU_VENCP_STAT + offset;
	} else {
		reg = ENCL_INFO_READ;
	}

	line_cnt = 0x1fff;
	line_cnt_previous = lcd_vcbus_getb(reg, 16, 13);
	while (i++ < LCD_WAIT_VSYNC_TIMEOUT) {
		line_cnt = lcd_vcbus_getb(reg, 16, 13);
		if (line_cnt < line_cnt_previous)
			break;
		line_cnt_previous = line_cnt;
		udelay(2);
	}
	/*LCDPR("line_cnt=%d, line_cnt_previous=%d, i=%d\n",
	 *	line_cnt, line_cnt_previous, i);
	 */
#endif
}

static void lcd_gamma_init(struct aml_lcd_drv_s *pdrv)
{
	if (pdrv->data->chip_type == LCD_CHIP_T7)
		return;
#ifndef CONFIG_AML_LCD_PXP
#ifdef CONFIG_AML_VPP
	lcd_wait_vsync(pdrv);
	vpp_disable_lcd_gamma_table(pdrv->index);

	vpp_init_lcd_gamma_table(pdrv->index);

	lcd_wait_vsync(pdrv);
	vpp_enable_lcd_gamma_table(pdrv->index);
#endif
#endif
}

static void lcd_set_encl_tcon(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_config_s *pconf = &pdrv->config;
	unsigned int offset_if, offset_data;
	unsigned int reg_rgb_base, reg_rgb_coeff, reg_dith_ctrl, reg_pol_ctrl;
	unsigned int reg_de_hs, reg_de_he, reg_de_vs, reg_de_ve;
	unsigned int reg_hsync_hs, reg_hsync_he, reg_hsync_vs, reg_hsync_ve;
	unsigned int reg_vsync_hs, reg_vsync_he, reg_vsync_vs, reg_vsync_ve;

	if (pdrv->data->chip_type == LCD_CHIP_T7) {
		offset_data = pdrv->data->offset_venc_data[pdrv->index];
		offset_if = pdrv->data->offset_venc_if[pdrv->index];
		reg_rgb_base = LCD_RGB_BASE_ADDR + offset_data;
		reg_rgb_coeff = LCD_RGB_COEFF_ADDR + offset_data;
		reg_dith_ctrl = LCD_DITH_CNTL_ADDR + offset_data;
		reg_pol_ctrl = LCD_POL_CNTL_ADDR + offset_data;
		reg_de_hs = DE_HS_ADDR + offset_if;
		reg_de_he = DE_HE_ADDR + offset_if;
		reg_de_vs = DE_VS_ADDR + offset_if;
		reg_de_ve = DE_VE_ADDR + offset_if;
		reg_hsync_hs = HSYNC_HS_ADDR + offset_if;
		reg_hsync_he = HSYNC_HE_ADDR + offset_if;
		reg_hsync_vs = HSYNC_VS_ADDR + offset_if;
		reg_hsync_ve = HSYNC_VE_ADDR + offset_if;
		reg_vsync_hs = VSYNC_HS_ADDR + offset_if;
		reg_vsync_he = VSYNC_HE_ADDR + offset_if;
		reg_vsync_vs = VSYNC_VS_ADDR + offset_if;
		reg_vsync_ve = VSYNC_VE_ADDR + offset_if;
	} else {
		reg_rgb_base = L_RGB_BASE_ADDR;
		reg_rgb_coeff = L_RGB_COEFF_ADDR;
		reg_dith_ctrl = L_POL_CNTL_ADDR;
		reg_pol_ctrl = L_DITH_CNTL_ADDR;
		reg_de_hs = L_DE_HS_ADDR;
		reg_de_he = L_DE_HE_ADDR;
		reg_de_vs = L_DE_VS_ADDR;
		reg_de_ve = L_DE_VE_ADDR;
		reg_hsync_hs = L_HSYNC_HS_ADDR;
		reg_hsync_he = L_HSYNC_HE_ADDR;
		reg_hsync_vs = L_HSYNC_VS_ADDR;
		reg_hsync_ve = L_HSYNC_VE_ADDR;
		reg_vsync_hs = L_VSYNC_HS_ADDR;
		reg_vsync_he = L_VSYNC_HE_ADDR;
		reg_vsync_vs = L_VSYNC_VS_ADDR;
		reg_vsync_ve = L_VSYNC_VE_ADDR;
	}

	lcd_vcbus_write(reg_rgb_base, 0x0);
	lcd_vcbus_write(reg_rgb_coeff, 0x400);

	switch (pconf->basic.lcd_bits) {
	case 6:
		lcd_vcbus_write(reg_dith_ctrl,  0x600);
		break;
	case 8:
		lcd_vcbus_write(reg_dith_ctrl,  0x400);
		break;
	case 10:
	default:
		lcd_vcbus_write(reg_dith_ctrl,  0x0);
		break;
	}

	switch (pconf->basic.lcd_type) {
	case LCD_LVDS:
		lcd_vcbus_setb(reg_pol_ctrl, 1, 0, 1);
		if (pconf->timing.vsync_pol)
			lcd_vcbus_setb(reg_pol_ctrl, 1, 1, 1);
		break;
	case LCD_VBYONE:
		if (pconf->timing.hsync_pol)
			lcd_vcbus_setb(reg_pol_ctrl, 1, 0, 1);
		if (pconf->timing.vsync_pol)
			lcd_vcbus_setb(reg_pol_ctrl, 1, 1, 1);
		break;
	case LCD_MIPI:
		//lcd_vcbus_setb(reg_pol_ctrl, 0x3, 0, 2);
		/*lcd_vcbus_write(reg_pol_ctrl,
		 *	(lcd_vcbus_read(reg_pol_ctrl) |
		 *	 ((0 << 2) | (vs_pol_adj << 1) | (hs_pol_adj << 0))));
		 */
		/*lcd_vcbus_write(reg_pol_ctrl, (lcd_vcbus_read(reg_pol_ctrl) |
		 *	 ((1 << LCD_TCON_DE_SEL) | (1 << LCD_TCON_VS_SEL) |
		 *	  (1 << LCD_TCON_HS_SEL))));
		 */
		break;
	case LCD_EDP:
		lcd_vcbus_setb(reg_pol_ctrl, 1, 0, 1);
		break;
	default:
		break;
	}

	/* DE signal */
	lcd_vcbus_write(reg_de_hs,    pconf->timing.de_hs_addr);
	lcd_vcbus_write(reg_de_he,    pconf->timing.de_he_addr);
	lcd_vcbus_write(reg_de_vs,    pconf->timing.de_vs_addr);
	lcd_vcbus_write(reg_de_ve,    pconf->timing.de_ve_addr);

	/* Hsync signal */
	lcd_vcbus_write(reg_hsync_hs, pconf->timing.hs_hs_addr);
	lcd_vcbus_write(reg_hsync_he, pconf->timing.hs_he_addr);
	lcd_vcbus_write(reg_hsync_vs, pconf->timing.hs_vs_addr);
	lcd_vcbus_write(reg_hsync_ve, pconf->timing.hs_ve_addr);

	/* Vsync signal */
	lcd_vcbus_write(reg_vsync_hs, pconf->timing.vs_hs_addr);
	lcd_vcbus_write(reg_vsync_he, pconf->timing.vs_he_addr);
	lcd_vcbus_write(reg_vsync_vs, pconf->timing.vs_vs_addr);
	lcd_vcbus_write(reg_vsync_ve, pconf->timing.vs_ve_addr);
}

void lcd_set_venc(struct aml_lcd_drv_s *pdrv)
{
	struct lcd_config_s *pconf = &pdrv->config;
	unsigned int hstart, hend, vstart, vend;
	unsigned int reg_disp_viu_ctrl, offset;
	unsigned int pre_de_vs = 0, pre_de_ve = 0, pre_de_hs = 0, pre_de_he = 0;

	if (lcd_debug_print_flag & LCD_DBG_PR_NORMAL)
		LCDPR("[%d]: %s\n", pdrv->index, __func__);

	hstart = pconf->timing.video_on_pixel;
	hend = pconf->basic.h_active + hstart - 1;
	vstart = pconf->timing.video_on_line;
	vend = pconf->basic.v_active + vstart - 1;
	offset = pdrv->data->offset_venc[pdrv->index];
	switch (pdrv->index) {
	case 0:
		reg_disp_viu_ctrl = VPU_DISP_VIU0_CTRL;
		break;
	case 1:
		reg_disp_viu_ctrl = VPU_DISP_VIU1_CTRL;
		break;
	case 2:
		reg_disp_viu_ctrl = VPU_DISP_VIU2_CTRL;
		break;
	default:
		LCDERR("[%d]: %s: invalid drv_index\n", pdrv->index, __func__);
		return;
	}

	lcd_vcbus_write(ENCL_VIDEO_EN + offset, 0);

	lcd_vcbus_write(ENCL_VIDEO_MODE + offset, 0x8000); /* bit[15] shadown en */
	lcd_vcbus_write(ENCL_VIDEO_MODE_ADV + offset, 0x0418); /* Sampling rate: 1 */

	lcd_vcbus_write(ENCL_VIDEO_FILT_CTRL + offset, 0x1000); /* bypass filter */
	lcd_vcbus_write(ENCL_VIDEO_MAX_PXCNT + offset, pconf->basic.h_period - 1);
	lcd_vcbus_write(ENCL_VIDEO_MAX_LNCNT + offset, pconf->basic.v_period - 1);
	lcd_vcbus_write(ENCL_VIDEO_HAVON_BEGIN + offset, hstart);
	lcd_vcbus_write(ENCL_VIDEO_HAVON_END + offset,   hend);
	lcd_vcbus_write(ENCL_VIDEO_VAVON_BLINE + offset, vstart);
	lcd_vcbus_write(ENCL_VIDEO_VAVON_ELINE + offset, vend);
	if (pconf->basic.lcd_type == LCD_P2P ||
	    pconf->basic.lcd_type == LCD_MLVDS) {
		switch (pdrv->data->chip_type) {
		case LCD_CHIP_TL1:
		case LCD_CHIP_TM2:
			pre_de_vs = vstart - 1 - 4;
			pre_de_ve = vstart - 1;
			pre_de_hs = hstart + PRE_DE_DELAY;
			pre_de_he = pconf->basic.h_active - 1 + pre_de_hs;
			break;
		default:
			pre_de_vs = vstart - 8;
			pre_de_ve = pconf->basic.v_active + pre_de_vs;
			pre_de_hs = hstart + PRE_DE_DELAY;
			pre_de_he = pconf->basic.h_active - 1 + pre_de_hs;
			break;
		}
		lcd_vcbus_write(ENCL_VIDEO_V_PRE_DE_BLINE + offset, pre_de_vs);
		lcd_vcbus_write(ENCL_VIDEO_V_PRE_DE_ELINE + offset, pre_de_ve);
		lcd_vcbus_write(ENCL_VIDEO_H_PRE_DE_BEGIN + offset, pre_de_hs);
		lcd_vcbus_write(ENCL_VIDEO_H_PRE_DE_END + offset,   pre_de_he);
	}

	lcd_vcbus_write(ENCL_VIDEO_HSO_BEGIN + offset, pconf->timing.hs_hs_addr);
	lcd_vcbus_write(ENCL_VIDEO_HSO_END + offset,   pconf->timing.hs_he_addr);
	lcd_vcbus_write(ENCL_VIDEO_VSO_BEGIN + offset, pconf->timing.vs_hs_addr);
	lcd_vcbus_write(ENCL_VIDEO_VSO_END + offset,   pconf->timing.vs_he_addr);
	lcd_vcbus_write(ENCL_VIDEO_VSO_BLINE + offset, pconf->timing.vs_vs_addr);
	lcd_vcbus_write(ENCL_VIDEO_VSO_ELINE + offset, pconf->timing.vs_ve_addr);
	lcd_vcbus_write(ENCL_VIDEO_RGBIN_CTRL + offset, 3);

	switch (pdrv->data->chip_type) {
	case LCD_CHIP_TL1:
	case LCD_CHIP_TM2:
	case LCD_CHIP_T5:
	case LCD_CHIP_T5D:
		/*[15:14]: 2'b10 or 2'b01*/
		lcd_vcbus_write(ENCL_INBUF_CNTL1 + offset,
				(2 << 14) | (pconf->basic.h_active - 1));
		lcd_vcbus_write(ENCL_INBUF_CNTL0 + offset, 0x200);
		break;
	case LCD_CHIP_T7:
		lcd_vcbus_write(ENCL_INBUF_CNTL1 + offset,
				(5 << 13) | (pconf->basic.h_active - 1));
		lcd_vcbus_write(ENCL_INBUF_CNTL0 + offset, 0x200);
		break;
	default:
		break;
	}

	/* default black pattern */
	lcd_vcbus_write(ENCL_TST_MDSEL + offset, 0);
	lcd_vcbus_write(ENCL_TST_Y + offset, 0);
	lcd_vcbus_write(ENCL_TST_CB + offset, 0);
	lcd_vcbus_write(ENCL_TST_CR + offset, 0);
	lcd_vcbus_write(ENCL_TST_EN + offset, 1);
	lcd_vcbus_setb(ENCL_VIDEO_MODE_ADV + offset, 0, 3, 1);

	lcd_vcbus_write(ENCL_VIDEO_EN + offset, 1);
	if (pdrv->data->chip_type == LCD_CHIP_T7) {
		/*
		 * bit31: lvds enable
		 * bit30: vx1 enable
		 * bit29: hdmitx enable
		 * bit28: dsi_edp enable
		 */
		switch (pdrv->config.basic.lcd_type) {
		case LCD_LVDS:
			lcd_vcbus_write(reg_disp_viu_ctrl, (1 << 31) |
							   (0 << 30) |
							   (0 << 29) |
							   (0 << 28));
			break;
		case LCD_VBYONE:
			lcd_vcbus_write(reg_disp_viu_ctrl, (0 << 31) |
							   (1 << 30) |
							   (0 << 29) |
							   (0 << 28));
			break;
		case LCD_MIPI:
		case LCD_EDP:
			lcd_vcbus_write(reg_disp_viu_ctrl, (0 << 31) |
							   (0 << 30) |
							   (0 << 29) |
							   (1 << 28));
			break;
		default:
			break;
		}
	}
	lcd_vcbus_write(VPU_VENC_CTRL + offset, 2);

	lcd_set_encl_tcon(pdrv);
	lcd_gamma_init(pdrv);
}
