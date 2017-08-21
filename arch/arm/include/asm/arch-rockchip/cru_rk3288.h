/*
 * (C) Copyright 2015 Google, Inc
 *
 * (C) Copyright 2008-2014 Rockchip Electronics
 * Peter, Software Engineering, <superpeter.cai@gmail.com>.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_CRU_RK3288_H
#define _ASM_ARCH_CRU_RK3288_H

#define OSC_HZ		(24 * 1000 * 1000)

#define APLL_HZ		(1800 * 1000000)
#define GPLL_HZ		(594 * 1000000)
#define CPLL_HZ		(384 * 1000000)
#define NPLL_HZ		(384 * 1000000)

/* The SRAM is clocked off aclk_bus, so we want to max it out for boot speed */
#define PD_BUS_ACLK_HZ	297000000
#define PD_BUS_HCLK_HZ	148500000
#define PD_BUS_PCLK_HZ	74250000

#define PERI_ACLK_HZ	148500000
#define PERI_HCLK_HZ	148500000
#define PERI_PCLK_HZ	74250000

/* Private data for the clock driver - used by rockchip_get_cru() */
struct rk3288_clk_priv {
	struct rk3288_grf *grf;
	struct rk3288_cru *cru;
	ulong rate;
};

struct rk3288_cru {
	struct rk3288_pll {
		u32 con0;
		u32 con1;
		u32 con2;
		u32 con3;
	} pll[5];
	u32 cru_mode_con;
	u32 reserved0[3];
	u32 cru_clksel_con[43];
	u32 reserved1[21];
	u32 cru_clkgate_con[19];
	u32 reserved2;
	u32 cru_glb_srst_fst_value;
	u32 cru_glb_srst_snd_value;
	u32 cru_softrst_con[12];
	u32 cru_misc_con;
	u32 cru_glb_cnt_th;
	u32 cru_glb_rst_con;
	u32 reserved3;
	u32 cru_glb_rst_st;
	u32 reserved4;
	u32 cru_sdmmc_con[2];
	u32 cru_sdio0_con[2];
	u32 cru_sdio1_con[2];
	u32 cru_emmc_con[2];
};
check_member(rk3288_cru, cru_emmc_con[1], 0x021c);

/* CRU_CLKSEL11_CON */
enum {
	HSICPHY_DIV_SHIFT	= 8,
	HSICPHY_DIV_MASK	= 0x3f << HSICPHY_DIV_SHIFT,

	MMC0_PLL_SHIFT		= 6,
	MMC0_PLL_MASK		= 3 << MMC0_PLL_SHIFT,
	MMC0_PLL_SELECT_CODEC	= 0,
	MMC0_PLL_SELECT_GENERAL,
	MMC0_PLL_SELECT_24MHZ,

	MMC0_DIV_SHIFT		= 0,
	MMC0_DIV_MASK		= 0x3f << MMC0_DIV_SHIFT,
};

/* CRU_CLKSEL12_CON */
enum {
	EMMC_PLL_SHIFT		= 0xe,
	EMMC_PLL_MASK		= 3 << EMMC_PLL_SHIFT,
	EMMC_PLL_SELECT_CODEC	= 0,
	EMMC_PLL_SELECT_GENERAL,
	EMMC_PLL_SELECT_24MHZ,

	EMMC_DIV_SHIFT		= 8,
	EMMC_DIV_MASK		= 0x3f << EMMC_DIV_SHIFT,

	SDIO0_PLL_SHIFT		= 6,
	SDIO0_PLL_MASK		= 3 << SDIO0_PLL_SHIFT,
	SDIO0_PLL_SELECT_CODEC	= 0,
	SDIO0_PLL_SELECT_GENERAL,
	SDIO0_PLL_SELECT_24MHZ,

	SDIO0_DIV_SHIFT		= 0,
	SDIO0_DIV_MASK		= 0x3f << SDIO0_DIV_SHIFT,
};

/* CRU_CLKSEL21_CON */
enum {
	MAC_DIV_CON_SHIFT	= 0xf,
	MAC_DIV_CON_MASK	= 0x1f << MAC_DIV_CON_SHIFT,

	RMII_EXTCLK_SHIFT	= 4,
	RMII_EXTCLK_MASK	= 1 << RMII_EXTCLK_SHIFT,
	RMII_EXTCLK_SELECT_INT_DIV_CLK = 0,
	RMII_EXTCLK_SELECT_EXT_CLK = 1,

	EMAC_PLL_SHIFT		= 0,
	EMAC_PLL_MASK		= 0x3 << EMAC_PLL_SHIFT,
	EMAC_PLL_SELECT_NEW	= 0x0,
	EMAC_PLL_SELECT_CODEC	= 0x1,
	EMAC_PLL_SELECT_GENERAL	= 0x2,
};

/* CRU_CLKSEL25_CON */
enum {
	SPI1_PLL_SHIFT		= 0xf,
	SPI1_PLL_MASK		= 1 << SPI1_PLL_SHIFT,
	SPI1_PLL_SELECT_CODEC	= 0,
	SPI1_PLL_SELECT_GENERAL,

	SPI1_DIV_SHIFT		= 8,
	SPI1_DIV_MASK		= 0x7f << SPI1_DIV_SHIFT,

	SPI0_PLL_SHIFT		= 7,
	SPI0_PLL_MASK		= 1 << SPI0_PLL_SHIFT,
	SPI0_PLL_SELECT_CODEC	= 0,
	SPI0_PLL_SELECT_GENERAL,

	SPI0_DIV_SHIFT		= 0,
	SPI0_DIV_MASK		= 0x7f << SPI0_DIV_SHIFT,
};

/* CRU_CLKSEL37_CON */
enum {
	PCLK_CORE_DBG_DIV_SHIFT	= 9,
	PCLK_CORE_DBG_DIV_MASK	= 0x1f << PCLK_CORE_DBG_DIV_SHIFT,

	ATCLK_CORE_DIV_CON_SHIFT = 4,
	ATCLK_CORE_DIV_CON_MASK	= 0x1f << ATCLK_CORE_DIV_CON_SHIFT,

	CLK_L2RAM_DIV_SHIFT	= 0,
	CLK_L2RAM_DIV_MASK	= 7 << CLK_L2RAM_DIV_SHIFT,
};

/* CRU_CLKSEL39_CON */
enum {
	ACLK_HEVC_PLL_SHIFT	= 0xe,
	ACLK_HEVC_PLL_MASK	= 3 << ACLK_HEVC_PLL_SHIFT,
	ACLK_HEVC_PLL_SELECT_CODEC = 0,
	ACLK_HEVC_PLL_SELECT_GENERAL,
	ACLK_HEVC_PLL_SELECT_NEW,

	ACLK_HEVC_DIV_SHIFT	= 8,
	ACLK_HEVC_DIV_MASK	= 0x1f << ACLK_HEVC_DIV_SHIFT,

	SPI2_PLL_SHIFT		= 7,
	SPI2_PLL_MASK		= 1 << SPI2_PLL_SHIFT,
	SPI2_PLL_SELECT_CODEC	= 0,
	SPI2_PLL_SELECT_GENERAL,

	SPI2_DIV_SHIFT		= 0,
	SPI2_DIV_MASK		= 0x7f << SPI2_DIV_SHIFT,
};

/* CRU_MODE_CON */
enum {
	CRU_MODE_MASK		= 3,

	NPLL_MODE_SHIFT		= 0xe,
	NPLL_MODE_MASK		= CRU_MODE_MASK << NPLL_MODE_SHIFT,
	NPLL_MODE_SLOW		= 0,
	NPLL_MODE_NORMAL,
	NPLL_MODE_DEEP,

	GPLL_MODE_SHIFT		= 0xc,
	GPLL_MODE_MASK		= CRU_MODE_MASK << GPLL_MODE_SHIFT,
	GPLL_MODE_SLOW		= 0,
	GPLL_MODE_NORMAL,
	GPLL_MODE_DEEP,

	CPLL_MODE_SHIFT		= 8,
	CPLL_MODE_MASK		= CRU_MODE_MASK << CPLL_MODE_SHIFT,
	CPLL_MODE_SLOW		= 0,
	CPLL_MODE_NORMAL,
	CPLL_MODE_DEEP,

	DPLL_MODE_SHIFT		= 4,
	DPLL_MODE_MASK		= CRU_MODE_MASK << DPLL_MODE_SHIFT,
	DPLL_MODE_SLOW		= 0,
	DPLL_MODE_NORMAL,
	DPLL_MODE_DEEP,

	APLL_MODE_SHIFT		= 0,
	APLL_MODE_MASK		= CRU_MODE_MASK << APLL_MODE_SHIFT,
	APLL_MODE_SLOW		= 0,
	APLL_MODE_NORMAL,
	APLL_MODE_DEEP,
};

/* CRU_APLL_CON0 */
enum {
	CLKR_SHIFT		= 8,
	CLKR_MASK		= 0x3f << CLKR_SHIFT,

	CLKOD_SHIFT		= 0,
	CLKOD_MASK		= 0xf << CLKOD_SHIFT,
};

/* CRU_APLL_CON1 */
enum {
	LOCK_SHIFT		= 0x1f,
	LOCK_MASK		= 1 << LOCK_SHIFT,
	LOCK_UNLOCK		= 0,
	LOCK_LOCK,

	CLKF_SHIFT		= 0,
	CLKF_MASK		= 0x1fff << CLKF_SHIFT,
};

/* CRU_GLB_RST_ST */
enum {
	GLB_POR_RST,
	FST_GLB_RST_ST		= BIT(0),
	SND_GLB_RST_ST		= BIT(1),
	FST_GLB_TSADC_RST_ST	= BIT(2),
	SND_GLB_TSADC_RST_ST	= BIT(3),
	FST_GLB_WDT_RST_ST	= BIT(4),
	SND_GLB_WDT_RST_ST	= BIT(5),
	GLB_RST_ST_MASK		= GENMASK(5, 0),
};

#endif
