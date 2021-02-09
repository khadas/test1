/*
 * driver/amlogic/media/vout/lcd/lcd_debug.h
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _AML_LCD_DEBUG_H
#define _AML_LCD_DEBUG_H
#include <amlogic/media/vout/lcd/lcd_vout.h>
#include "lcd_reg.h"

#define LCD_DEBUG_REG_CNT_MAX    30
#define LCD_DEBUG_REG_END        0xffffffff

struct lcd_debug_info_reg_s {
	unsigned int *reg_pll_table;
	unsigned int *reg_clk_table;
	unsigned int *reg_encl_table;
	unsigned int *reg_pinmux_table;
	int (*prbs_test)(struct aml_lcd_drv_s *pdrv, unsigned int s, unsigned int mode_flag);
};

struct lcd_debug_info_if_s {
	void (*interface_print)(struct lcd_config_s *pconf);
	void (*reg_dump_interface)(struct aml_lcd_drv_s *pdrv);
	void (*reg_dump_phy)(struct aml_lcd_drv_s *pdrv);
};

static unsigned int lcd_reg_dump_clk_gp0_g12a[] = {
	HHI_GP0_PLL_CNTL0,
	HHI_GP0_PLL_CNTL1,
	HHI_GP0_PLL_CNTL2,
	HHI_GP0_PLL_CNTL3,
	HHI_GP0_PLL_CNTL4,
	HHI_GP0_PLL_CNTL5,
	HHI_GP0_PLL_CNTL6,
	HHI_VIID_CLK_DIV,
	HHI_VIID_CLK_CNTL,
	HHI_VID_CLK_CNTL2,
	HHI_MIPIDSI_PHY_CLK_CNTL,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_clk_hpll_g12a[] = {
	HHI_HDMI_PLL_CNTL0,
	HHI_HDMI_PLL_CNTL1,
	HHI_HDMI_PLL_CNTL2,
	HHI_HDMI_PLL_CNTL3,
	HHI_HDMI_PLL_CNTL4,
	HHI_HDMI_PLL_CNTL5,
	HHI_HDMI_PLL_CNTL6,
	HHI_VID_PLL_CLK_DIV,
	HHI_VIID_CLK_DIV,
	HHI_VIID_CLK_CNTL,
	HHI_VID_CLK_CNTL2,
	HHI_MIPIDSI_PHY_CLK_CNTL,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_clk_tl1[] = {
	HHI_TCON_PLL_CNTL0,
	HHI_TCON_PLL_CNTL1,
	HHI_TCON_PLL_CNTL2,
	HHI_TCON_PLL_CNTL3,
	HHI_TCON_PLL_CNTL4,
	HHI_VID_PLL_CLK_DIV,
	HHI_VIID_CLK_DIV,
	HHI_VIID_CLK_CNTL,
	HHI_VID_CLK_CNTL2,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_pll_t7_0[] = {
	ANACTRL_TCON_PLL0_CNTL0,
	ANACTRL_TCON_PLL0_CNTL1,
	ANACTRL_TCON_PLL0_CNTL2,
	ANACTRL_TCON_PLL0_CNTL3,
	ANACTRL_TCON_PLL0_CNTL4,
	ANACTRL_TCON_PLL0_STS,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_pll_t7_1[] = {
	ANACTRL_TCON_PLL1_CNTL0,
	ANACTRL_TCON_PLL1_CNTL1,
	ANACTRL_TCON_PLL1_CNTL2,
	ANACTRL_TCON_PLL1_CNTL3,
	ANACTRL_TCON_PLL1_CNTL4,
	ANACTRL_TCON_PLL1_STS,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_pll_t7_2[] = {
	ANACTRL_TCON_PLL2_CNTL0,
	ANACTRL_TCON_PLL2_CNTL1,
	ANACTRL_TCON_PLL2_CNTL2,
	ANACTRL_TCON_PLL2_CNTL3,
	ANACTRL_TCON_PLL2_CNTL4,
	ANACTRL_TCON_PLL2_STS,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_clk_t7_0[] = {
	CLKCTRL_VIID_CLK0_DIV,
	CLKCTRL_VIID_CLK0_CTRL,
	CLKCTRL_VID_CLK0_CTRL2,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_clk_t7_1[] = {
	CLKCTRL_VIID_CLK1_DIV,
	CLKCTRL_VIID_CLK1_CTRL,
	CLKCTRL_VID_CLK1_CTRL2,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_clk_t7_2[] = {
	CLKCTRL_VIID_CLK2_DIV,
	CLKCTRL_VIID_CLK2_CTRL,
	CLKCTRL_VID_CLK2_CTRL2,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_encl_dft[] = {
	VPU_VIU_VENC_MUX_CTRL,
	ENCL_VIDEO_EN,
	ENCL_VIDEO_MODE,
	ENCL_VIDEO_MODE_ADV,
	ENCL_VIDEO_MAX_PXCNT,
	ENCL_VIDEO_MAX_LNCNT,
	ENCL_VIDEO_HAVON_BEGIN,
	ENCL_VIDEO_HAVON_END,
	ENCL_VIDEO_VAVON_BLINE,
	ENCL_VIDEO_VAVON_ELINE,
	ENCL_VIDEO_HSO_BEGIN,
	ENCL_VIDEO_HSO_END,
	ENCL_VIDEO_VSO_BEGIN,
	ENCL_VIDEO_VSO_END,
	ENCL_VIDEO_VSO_BLINE,
	ENCL_VIDEO_VSO_ELINE,
	ENCL_VIDEO_RGBIN_CTRL,
	L_GAMMA_CNTL_PORT,
	L_RGB_BASE_ADDR,
	L_RGB_COEFF_ADDR,
	L_POL_CNTL_ADDR,
	L_DITH_CNTL_ADDR,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_encl_tl1[] = {
	VPU_VIU_VENC_MUX_CTRL,
	ENCL_VIDEO_EN,
	ENCL_VIDEO_MODE,
	ENCL_VIDEO_MODE_ADV,
	ENCL_VIDEO_MAX_PXCNT,
	ENCL_VIDEO_MAX_LNCNT,
	ENCL_VIDEO_HAVON_BEGIN,
	ENCL_VIDEO_HAVON_END,
	ENCL_VIDEO_VAVON_BLINE,
	ENCL_VIDEO_VAVON_ELINE,
	ENCL_VIDEO_HSO_BEGIN,
	ENCL_VIDEO_HSO_END,
	ENCL_VIDEO_VSO_BEGIN,
	ENCL_VIDEO_VSO_END,
	ENCL_VIDEO_VSO_BLINE,
	ENCL_VIDEO_VSO_ELINE,
	ENCL_VIDEO_RGBIN_CTRL,
	ENCL_INBUF_CNTL0,
	ENCL_INBUF_CNTL1,
	L_GAMMA_CNTL_PORT,
	L_RGB_BASE_ADDR,
	L_RGB_COEFF_ADDR,
	L_POL_CNTL_ADDR,
	L_DITH_CNTL_ADDR,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_encl_t7_0[] = {
	VPU_VIU_VENC_MUX_CTRL,
	ENCL_VIDEO_EN,
	ENCL_VIDEO_MODE,
	ENCL_VIDEO_MODE_ADV,
	ENCL_VIDEO_MAX_PXCNT,
	ENCL_VIDEO_MAX_LNCNT,
	ENCL_VIDEO_HAVON_BEGIN,
	ENCL_VIDEO_HAVON_END,
	ENCL_VIDEO_VAVON_BLINE,
	ENCL_VIDEO_VAVON_ELINE,
	ENCL_VIDEO_HSO_BEGIN,
	ENCL_VIDEO_HSO_END,
	ENCL_VIDEO_VSO_BEGIN,
	ENCL_VIDEO_VSO_END,
	ENCL_VIDEO_VSO_BLINE,
	ENCL_VIDEO_VSO_ELINE,
	ENCL_VIDEO_RGBIN_CTRL,
	ENCL_INBUF_CNTL0,
	ENCL_INBUF_CNTL1,
	LCD_GAMMA_CNTL_PORT0,
	LCD_RGB_BASE_ADDR,
	LCD_RGB_COEFF_ADDR,
	LCD_POL_CNTL_ADDR,
	LCD_DITH_CNTL_ADDR,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_encl_t7_1[] = {
	VPU_VIU_VENC_MUX_CTRL,
	ENCL_VIDEO_EN + (0x600 << 2),
	ENCL_VIDEO_MODE + (0x600 << 2),
	ENCL_VIDEO_MODE_ADV + (0x600 << 2),
	ENCL_VIDEO_MAX_PXCNT + (0x600 << 2),
	ENCL_VIDEO_MAX_LNCNT + (0x600 << 2),
	ENCL_VIDEO_HAVON_BEGIN + (0x600 << 2),
	ENCL_VIDEO_HAVON_END + (0x600 << 2),
	ENCL_VIDEO_VAVON_BLINE + (0x600 << 2),
	ENCL_VIDEO_VAVON_ELINE + (0x600 << 2),
	ENCL_VIDEO_HSO_BEGIN + (0x600 << 2),
	ENCL_VIDEO_HSO_END + (0x600 << 2),
	ENCL_VIDEO_VSO_BEGIN + (0x600 << 2),
	ENCL_VIDEO_VSO_END + (0x600 << 2),
	ENCL_VIDEO_VSO_BLINE + (0x600 << 2),
	ENCL_VIDEO_VSO_ELINE + (0x600 << 2),
	ENCL_VIDEO_RGBIN_CTRL + (0x600 << 2),
	ENCL_INBUF_CNTL0 + (0x600 << 2),
	ENCL_INBUF_CNTL1 + (0x600 << 2),
	LCD_GAMMA_CNTL_PORT0 + (0x100 << 2),
	LCD_RGB_BASE_ADDR + (0x100 << 2),
	LCD_RGB_COEFF_ADDR + (0x100 << 2),
	LCD_POL_CNTL_ADDR + (0x100 << 2),
	LCD_DITH_CNTL_ADDR + (0x100 << 2),
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_encl_t7_2[] = {
	VPU_VIU_VENC_MUX_CTRL,
	ENCL_VIDEO_EN + (0x800 << 2),
	ENCL_VIDEO_MODE + (0x800 << 2),
	ENCL_VIDEO_MODE_ADV + (0x800 << 2),
	ENCL_VIDEO_MAX_PXCNT + (0x800 << 2),
	ENCL_VIDEO_MAX_LNCNT + (0x800 << 2),
	ENCL_VIDEO_HAVON_BEGIN + (0x800 << 2),
	ENCL_VIDEO_HAVON_END + (0x800 << 2),
	ENCL_VIDEO_VAVON_BLINE + (0x800 << 2),
	ENCL_VIDEO_VAVON_ELINE + (0x800 << 2),
	ENCL_VIDEO_HSO_BEGIN + (0x800 << 2),
	ENCL_VIDEO_HSO_END + (0x800 << 2),
	ENCL_VIDEO_VSO_BEGIN + (0x800 << 2),
	ENCL_VIDEO_VSO_END + (0x800 << 2),
	ENCL_VIDEO_VSO_BLINE + (0x800 << 2),
	ENCL_VIDEO_VSO_ELINE + (0x800 << 2),
	ENCL_VIDEO_RGBIN_CTRL + (0x800 << 2),
	ENCL_INBUF_CNTL0 + (0x800 << 2),
	ENCL_INBUF_CNTL1 + (0x800 << 2),
	LCD_GAMMA_CNTL_PORT0 + (0x200 << 2),
	LCD_RGB_BASE_ADDR + (0x200 << 2),
	LCD_RGB_COEFF_ADDR + (0x200 << 2),
	LCD_POL_CNTL_ADDR + (0x200 << 2),
	LCD_DITH_CNTL_ADDR + (0x200 << 2),
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_pinmux_tl1[] = {
	PERIPHS_PIN_MUX_7,
	PERIPHS_PIN_MUX_8,
	PERIPHS_PIN_MUX_9,
	LCD_DEBUG_REG_END
};

static unsigned int lcd_reg_dump_pinmux_t7[] = {
	PADCTRL_PIN_MUX_REGK,
	LCD_DEBUG_REG_END
};

#endif

