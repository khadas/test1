/*
 * drivers/amlogic/media/vout/vout_reg.h
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

#ifndef _VOUT_REG_H
#define _VOUT_REG_H

#ifndef REG_BASE_VCBUS
#define REG_BASE_VCBUS                  (0xff900000L)
#endif
#define REG_OFFSET_VCBUS(reg)           ((reg << 2))
#define REG_ADDR_VCBUS(reg)             (REG_BASE_VCBUS + REG_OFFSET_VCBUS(reg))

#define REG_CLK_ADDR(reg)               (reg + 0L)
#define REG_VOUT_ADDR(reg)              (reg + 0L)

#ifndef HHI_VPU_CLKC_CNTL
#define HHI_VPU_CLKC_CNTL                          (0xff63c000 + (0x06d << 2))
#endif
#ifndef CLKCTRL_VPU_CLKC_CTRL
#define CLKCTRL_VPU_CLKC_CTRL                      ((0x003c  << 2) + 0xfe000000)
#endif
#ifndef VPU_VIU_VENC_MUX_CTRL
#define VPU_VIU_VENC_MUX_CTRL                      ((0x271a  << 2) + 0xff000000)
#endif
#ifndef VPU_VENCX_CLK_CTRL
#define VPU_VENCX_CLK_CTRL                         ((0x2785  << 2) + 0xff000000)
#endif
#ifndef VPU_VENC_CTRL
#define VPU_VENC_CTRL                              ((0x1cef  << 2) + 0xff000000)
#endif

static inline unsigned int vout_reg_read(unsigned int idx, u32 reg)
{
	unsigned int temp, val;

	if (vout_conf_check())
		return 0;

	if (reg > 0x10000) {
		temp = reg + (vout_conf->offset[idx] << 2);
		val = *(volatile unsigned int *)REG_VOUT_ADDR(temp);
	} else {
		temp = reg + vout_conf->offset[idx];
		val = *(volatile unsigned int *)REG_ADDR_VCBUS(temp);
	}

	return val;
}

static inline void vout_reg_write(unsigned int idx, u32 reg, const u32 val)
{
	unsigned int temp;

	if (vout_conf_check())
		return;

	if (reg > 0x10000) {
		temp = reg + (vout_conf->offset[idx] << 2);
		*(volatile unsigned int *)REG_VOUT_ADDR(temp) = (val);
	} else {
		temp = reg + vout_conf->offset[idx];
		*(volatile unsigned int *)REG_ADDR_VCBUS(temp) = (val);
	}
}

static inline void vout_reg_setb(unsigned int idx, unsigned int reg, unsigned int val,
		unsigned int start, unsigned int len)
{
	vout_reg_write(idx, reg, ((vout_reg_read(idx, reg) &
			~(((1L << (len))-1) << (start))) |
			(((val)&((1L<<(len))-1)) << (start))));
}

static inline unsigned int vout_clk_read(u32 reg)
{
	return *(volatile unsigned int *)(REG_CLK_ADDR(reg));
}

static inline void vout_clk_write(u32 reg, const u32 val)
{
	*(volatile unsigned int *)REG_CLK_ADDR(reg) = (val);
}

static inline void vout_clk_setb(unsigned int reg, unsigned int val,
		unsigned int start, unsigned int len)
{
	vout_clk_write(reg, ((vout_clk_read(reg) &
			~(((1L << (len))-1) << (start))) |
			(((val)&((1L<<(len))-1)) << (start))));
}

#endif
