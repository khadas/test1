/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef _LCD_CLK_CONFIG_H
#define _LCD_CLK_CONFIG_H

#include <linux/types.h>
#include <amlogic/media/vout/lcd/aml_lcd.h>

/* **********************************
 * clk config
 * **********************************/
#define LCD_PLL_MODE_DEFAULT         BIT(0)
#define LCD_PLL_MODE_SPECIAL_CNTL    BIT(1)
#define LCD_PLL_MODE_FRAC_SHIFT      BIT(2)

#define PLL_RETRY_MAX		20
#define LCD_CLK_CTRL_EN      0
#define LCD_CLK_CTRL_RST     1
#define LCD_CLK_CTRL_FRAC    2
#define LCD_CLK_CTRL_END     0xffff

#define LCD_CLK_REG_END      0xffff
#define LCD_CLK_CTRL_CNT_MAX 10
struct lcd_clk_ctrl_s {
	unsigned int flag;
	unsigned int reg;
	unsigned int bit;
	unsigned int len;
};

struct lcd_clk_data_s {
	/* clk path node parameters */
	unsigned int pll_od_fb;
	unsigned int pll_m_max;
	unsigned int pll_m_min;
	unsigned int pll_n_max;
	unsigned int pll_n_min;
	unsigned int pll_frac_range;
	unsigned int pll_frac_sign_bit;
	unsigned int pll_od_sel_max;
	unsigned int pll_ref_fmax;
	unsigned int pll_ref_fmin;
	unsigned int pll_vco_fmax;
	unsigned int pll_vco_fmin;
	unsigned int pll_out_fmax;
	unsigned int pll_out_fmin;
	unsigned int div_in_fmax;
	unsigned int div_out_fmax;
	unsigned int xd_out_fmax;

	unsigned char vclk_sel;
	unsigned char clk1_path_sel;//display 1 clk path sel tcon_pll0/1
	int enc_clk_msr_id;
	struct lcd_clk_ctrl_s *pll_ctrl_table;

	unsigned char ss_support;

	void (*clk_generate_parameter)(struct aml_lcd_drv_s *pdrv);
	void (*pll_frac_generate)(struct aml_lcd_drv_s *pdrv);
	void (*set_ss_level)(struct aml_lcd_drv_s *pdrv);
	void (*set_ss_advance)(struct aml_lcd_drv_s *pdrv);
	void (*clk_ss_enable)(struct aml_lcd_drv_s *pdrv, int status);
	void (*clk_set)(struct aml_lcd_drv_s *pdrv);
	void (*vclk_crt_set)(struct aml_lcd_drv_s *pdrv);
	void (*clk_disable)(struct aml_lcd_drv_s *pdrv);
	void (*clk_config_init_print)(struct aml_lcd_drv_s *pdrv);
	void (*clk_config_print)(struct aml_lcd_drv_s *pdrv);
	void (*prbs_clk_config)(struct aml_lcd_drv_s *pdrv, unsigned int lcd_prbs_mode);
	int (*prbs_test)(struct aml_lcd_drv_s *pdrv, unsigned int ms, unsigned int mode_flag);
};

struct lcd_clk_config_s { /* unit: kHz */
	/* IN-OUT parameters */
	unsigned int fin;
	unsigned int fout;

	/* pll parameters */
	unsigned int pll_id;
	unsigned int pll_offset;
	unsigned int pll_mode; /* txl */
	unsigned int pll_od_fb;
	unsigned int pll_m;
	unsigned int pll_n;
	unsigned int pll_fvco;
	unsigned int pll_od1_sel;
	unsigned int pll_od2_sel;
	unsigned int pll_od3_sel;
	unsigned int pll_tcon_div_sel;
	unsigned int pll_level;
	unsigned int pll_frac;
	unsigned int pll_frac_half_shift;
	unsigned int pll_fout;
	unsigned int ss_level;
	unsigned int ss_freq;
	unsigned int ss_mode;
	unsigned int ss_en;
	unsigned int edp_div0;
	unsigned int edp_div1;
	unsigned int div_sel;
	unsigned int xd;
	unsigned int phy_div;
	unsigned int div_sel_max;
	unsigned int xd_max;
	unsigned int err_fmin;
	unsigned int done;

	struct lcd_clk_data_s *data;
};

enum lcd_clk_mode_e {
	LCD_CLK_MODE_DEPENDENCE = 0,  /* pclk and phy use same pll */
	LCD_CLK_MODE_INDEPENDENCE,    /* pclk and phy use different pll */
	LCD_CLK_MODE_MAX,
};

#endif
