/*
 * drivers/amlogic/media/osd/osd_io.h
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
*/


#ifndef _OSD_IO_H_
#define _OSD_IO_H_

#include <asm/arch/io.h>
#include <asm/arch/secure_apb.h>

#ifndef REG_BASE_VCBUS
#define REG_BASE_VCBUS                  (0xFF900000L)
#endif

/* osd super scale */
#ifndef OSDSR_HV_SIZEIN
#define OSDSR_HV_SIZEIN              VPP_OSDSC_DITHER_CTRL
#endif

#ifndef OSDSR_CTRL_MODE
#define OSDSR_CTRL_MODE              VPP_OSDSC_DITHER_LUT_1
#endif

#ifdef OSDSR_ABIC_HCOEF
#define OSDSR_ABIC_HCOEF             VPP_OSDSC_DITHER_LUT_2
#endif

#ifndef OSDSR_YBIC_HCOEF
#define OSDSR_YBIC_HCOEF             VPP_OSDSC_DITHER_LUT_3
#endif

#ifndef OSDSR_CBIC_HCOEF
#define OSDSR_CBIC_HCOEF             VPP_OSDSC_DITHER_LUT_4
#endif

#ifndef OSDSR_ABIC_VCOEF
#define OSDSR_ABIC_VCOEF             VPP_OSDSC_DITHER_LUT_5
#endif

#ifndef OSDSR_YBIC_VCOEF
#define OSDSR_YBIC_VCOEF             VPP_OSDSC_DITHER_LUT_6
#endif

#ifndef OSDSR_CBIC_VCOEF
#define OSDSR_CBIC_VCOEF             VPP_OSDSC_DITHER_LUT_7
#endif

#ifndef OSDSR_VAR_PARA
#define OSDSR_VAR_PARA               VPP_OSDSC_DITHER_LUT_8
#endif

#ifndef OSDSR_CONST_PARA
#define OSDSR_CONST_PARA             VPP_OSDSC_DITHER_LUT_9
#endif

#ifndef OSDSR_RKE_EXTWIN
#define OSDSR_RKE_EXTWIN             VPP_OSDSC_DITHER_LUT_10
#endif

#ifndef OSDSR_UK_GRAD2DDIAG_TH_RATE
#define OSDSR_UK_GRAD2DDIAG_TH_RATE  VPP_OSDSC_DITHER_LUT_11
#endif

#ifndef OSDSR_UK_GRAD2DDIAG_LIMIT
#define OSDSR_UK_GRAD2DDIAG_LIMIT    VPP_OSDSC_DITHER_LUT_12
#endif

#ifndef OSDSR_UK_GRAD2DADJA_TH_RATE
#define OSDSR_UK_GRAD2DADJA_TH_RATE  VPP_OSDSC_DITHER_LUT_13
#endif

#ifndef OSDSR_UK_GRAD2DADJA_LIMIT
#define OSDSR_UK_GRAD2DADJA_LIMIT    VPP_OSDSC_DITHER_LUT_14
#endif

#ifndef OSDSR_UK_BST_GAIN
#define OSDSR_UK_BST_GAIN            VPP_OSDSC_DITHER_LUT_15
#endif

#ifndef VPP_OSD1_SCALE_CTRL
#define VPP_OSD1_SCALE_CTRL                        0x1a73
#endif

#ifndef VPP_OSD2_SCALE_CTRL
#define VPP_OSD2_SCALE_CTRL                        0x1a74
#endif

#ifndef VPP_OSD3_SCALE_CTRL
#define VPP_OSD3_SCALE_CTRL                        0x1a75
#endif

#ifndef VPP_OSD4_SCALE_CTRL
#define VPP_OSD4_SCALE_CTRL                        0x1a76
#endif

#ifndef MALI_AFBCD1_TOP_CTRL
#define MALI_AFBCD1_TOP_CTRL                       0x1a55
#endif

#ifndef VPP_VD1_DSC_CTRL
#define VPP_VD1_DSC_CTRL                           0x1a83
#endif

#ifndef VPP_VD2_DSC_CTRL
#define VPP_VD2_DSC_CTRL                           0x1a84
#endif

#ifndef VPP_VD3_DSC_CTRL
#define VPP_VD3_DSC_CTRL                           0x1a85
#endif

#ifndef VIU_OSD3_BLK1_CFG_W4
#define VIU_OSD3_BLK1_CFG_W4                       0x3d99
#endif

#ifndef VIU_OSD3_BLK2_CFG_W4
#define VIU_OSD3_BLK2_CFG_W4                       0x3d9a
#endif

#ifndef VIU_OSD3_CTRL_STAT
#define VIU_OSD3_CTRL_STAT                         0x3d80
#endif

#define REG_OFFSET_VCBUS(reg)           ((reg << 2))
#define REG_ADDR_VCBUS(reg)             (REG_BASE_VCBUS + REG_OFFSET_VCBUS(reg))
#define REG_OSD_ADDR(reg)               (reg + 0L)

static inline u32 osd_reg_read(u32 reg)
{
	u32 val;

	if (reg > 0x10000)
		val = *(volatile unsigned int *)REG_OSD_ADDR(reg);
	else
		val = *(volatile unsigned int *)REG_ADDR_VCBUS(reg);
	return val;
}

static inline void osd_reg_write(u32 reg,
				 const u32 val)
{
	if (reg > 0x10000)
		*(volatile unsigned int *)REG_OSD_ADDR(reg) = (val);
	else
		*(volatile unsigned int *)REG_ADDR_VCBUS(reg) = (val);
}

static inline void osd_reg_set_mask(u32 reg,
				    const u32 mask)
{
	osd_reg_write(reg, (osd_reg_read(reg) | (mask)));
}

static inline void osd_reg_clr_mask(u32 reg,
				    const u32 mask)
{
	osd_reg_write(reg, (osd_reg_read(reg) & (~(mask))));
}

static inline void osd_reg_set_bits(u32 reg,
				    const u32 value,
				    const u32 start,
				    const u32 len)
{
	osd_reg_write(reg, ((osd_reg_read(reg) &
			     ~(((1L << (len)) - 1) << (start))) |
			    (((value) & ((1L << (len)) - 1)) << (start))));
}

#define VSYNCOSD_RD_MPEG_REG(reg) osd_reg_read(reg)
#define VSYNCOSD_WR_MPEG_REG(reg, val) osd_reg_write(reg, val)
#define VSYNCOSD_WR_MPEG_REG_BITS(reg, val, start, len) \
	osd_reg_set_bits(reg, val, start, len)
#define VSYNCOSD_SET_MPEG_REG_MASK(reg, mask) osd_reg_set_mask(reg, mask)
#define VSYNCOSD_CLR_MPEG_REG_MASK(reg, mask) osd_reg_clr_mask(reg, mask)

#endif
