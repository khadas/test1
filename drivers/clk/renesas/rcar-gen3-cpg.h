/*
 * R-Car Gen3 Clock Pulse Generator
 *
 * Copyright (C) 2015-2016 Glider bvba
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 */

#ifndef __CLK_RENESAS_RCAR_GEN3_CPG_H__
#define __CLK_RENESAS_RCAR_GEN3_CPG_H__

enum rcar_gen3_clk_types {
	CLK_TYPE_GEN3_MAIN = CLK_TYPE_CUSTOM,
	CLK_TYPE_GEN3_PLL0,
	CLK_TYPE_GEN3_PLL1,
	CLK_TYPE_GEN3_PLL2,
	CLK_TYPE_GEN3_PLL3,
	CLK_TYPE_GEN3_PLL4,
	CLK_TYPE_GEN3_SD,
	CLK_TYPE_GEN3_RPC,
	CLK_TYPE_GEN3_R,
	CLK_TYPE_GEN3_PE,
	CLK_TYPE_GEN3_Z2,
};

#define DEF_GEN3_SD(_name, _id, _parent, _offset)	\
	DEF_BASE(_name, _id, CLK_TYPE_GEN3_SD, _parent, .offset = _offset)
#define DEF_GEN3_RPC(_name, _id, _parent, _offset)	\
	DEF_BASE(_name, _id, CLK_TYPE_GEN3_RPC, _parent, .offset = _offset)
#define DEF_GEN3_PE(_name, _id, _parent_sscg, _div_sscg, _parent_clean, \
		    _div_clean) \
	DEF_BASE(_name, _id, CLK_TYPE_FF,			\
		 (_parent_clean), .div = (_div_clean), 1)

struct rcar_gen3_cpg_pll_config {
	u8 extal_div;
	u8 pll1_mult;
	u8 pll1_div;
	u8 pll3_mult;
	u8 pll3_div;
};

#define CPG_RCKCR	0x240

struct gen3_clk_priv {
	void __iomem		*base;
	struct cpg_mssr_info	*info;
	struct clk		clk_extal;
	struct clk		clk_extalr;
	const struct rcar_gen3_cpg_pll_config *cpg_pll_config;
};

int gen3_clk_probe(struct udevice *dev);
int gen3_clk_remove(struct udevice *dev);

extern const struct clk_ops gen3_clk_ops;

#endif
