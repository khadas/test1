/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __DDR_H__
#define __DDR_H__
struct board_specific_parameters {
	u32 n_ranks;
	u32 datarate_mhz_high;
	u32 rank_gb;
	u32 clk_adjust;
	u32 wrlvl_start;
	u32 wrlvl_ctl_2;
	u32 wrlvl_ctl_3;
};

/*
 * These tables contain all valid speeds we want to override with board
 * specific parameters. datarate_mhz_high values need to be in ascending order
 * for each n_ranks group.
 */

static const struct board_specific_parameters udimm0[] = {
	/*
	 * memory controller 0
	 *   num|  hi| rank|  clk| wrlvl |   wrlvl   |  wrlvl |
	 * ranks| mhz| GB  |adjst| start |   ctl2    |  ctl3  |
	 */
	{2,  1200, 2, 5,     7, 0x0808090a, 0x0b0c0c0a},
	{2,  1500, 2, 5,     6, 0x07070809, 0x0a0b0b09},
	{2,  1600, 2, 5,     8, 0x090b0b0d, 0x0d0e0f0b},
	{2,  1700, 2, 4,     7, 0x080a0a0c, 0x0c0d0e0a},
	{2,  1900, 2, 5,     9, 0x0a0b0c0e, 0x0f10120c},
	{2,  2140, 2, 4,     8, 0x090a0b0d, 0x0e0f110b},
	{1,  1200, 2, 5,     7, 0x0808090a, 0x0b0c0c0a},
	{1,  1500, 2, 5,     6, 0x07070809, 0x0a0b0b09},
	{1,  1600, 2, 5,     8, 0x090b0b0d, 0x0d0e0f0b},
	{1,  1700, 2, 4,     7, 0x080a0a0c, 0x0c0d0e0a},
	{1,  1900, 2, 5,     9, 0x0a0b0c0e, 0x0f10120c},
	{1,  2140, 2, 4,     8, 0x090a0b0d, 0x0e0f110b},
	{}
};

static const struct board_specific_parameters rdimm0[] = {
	/*
	 * memory controller 0
	 *   num|  hi| rank|  clk| wrlvl |   wrlvl   |  wrlvl |
	 * ranks| mhz| GB  |adjst| start |   ctl2    |  ctl3  |
	 */
	/* TODO: need tuning these parameters if RDIMM is used */
	{4,  1350, 0, 5,     9, 0x08070605, 0x06070806},
	{4,  1666, 0, 5,    11, 0x0a080706, 0x07090906},
	{4,  2140, 0, 5,    12, 0x0b090807, 0x080a0b07},
	{2,  1350, 0, 5,     9, 0x08070605, 0x06070806},
	{2,  1666, 0, 5,    11, 0x0a090806, 0x08090a06},
	{2,  2140, 0, 5,    12, 0x0b090807, 0x080a0b07},
	{1,  1350, 0, 5,     9, 0x08070605, 0x06070806},
	{1,  1666, 0, 5,    11, 0x0a090806, 0x08090a06},
	{1,  2140, 0, 4,    12, 0x0b090807, 0x080a0b07},
	{}
};

static const struct board_specific_parameters *udimms[] = {
	udimm0,
};

static const struct board_specific_parameters *rdimms[] = {
	rdimm0,
};
#endif
