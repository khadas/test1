/*
 * Copyright (C) 2013, Intel Corporation
 * Copyright (C) 2014, Bin Meng <bmeng.cn@gmail.com>
 *
 * This file is automatically generated. Please do NOT modify !!!
 *
 * SPDX-License-Identifier:	Intel
 */

#ifndef __VPDHEADER_H__
#define __VPDHEADER_H__

struct __packed upd_region {
	u64	sign;			/* Offset 0x0000 */
	u64	reserved;		/* Offset 0x0008 */
	u8	dummy[240];		/* Offset 0x0010 */
	u8	hda_verb_header[12];	/* Offset 0x0100 */
	u32	hda_verb_length;	/* Offset 0x010C */
	u8	hda_verb_data0[16];	/* Offset 0x0110 */
	u8	hda_verb_data1[16];	/* Offset 0x0120 */
	u8	hda_verb_data2[16];	/* Offset 0x0130 */
	u8	hda_verb_data3[16];	/* Offset 0x0140 */
	u8	hda_verb_data4[16];	/* Offset 0x0150 */
	u8	hda_verb_data5[16];	/* Offset 0x0160 */
	u8	hda_verb_data6[16];	/* Offset 0x0170 */
	u8	hda_verb_data7[16];	/* Offset 0x0180 */
	u8	hda_verb_data8[16];	/* Offset 0x0190 */
	u8	hda_verb_data9[16];	/* Offset 0x01A0 */
	u8	hda_verb_data10[16];	/* Offset 0x01B0 */
	u8	hda_verb_data11[16];	/* Offset 0x01C0 */
	u8	hda_verb_data12[16];	/* Offset 0x01D0 */
	u8	hda_verb_data13[16];	/* Offset 0x01E0 */
	u8	hda_verb_pad[47];	/* Offset 0x01F0 */
	u16	terminator;		/* Offset 0x021F */
};

#define VPD_IMAGE_ID	0x445056574F4E4E4D	/* 'MNNOWVPD' */
#define VPD_IMAGE_REV	0x00000301

struct __packed vpd_region {
	u64	sign;			/* Offset 0x0000 */
	u32	img_rev;		/* Offset 0x0008 */
	u32	upd_offset;		/* Offset 0x000C */
	u8	unused[16];		/* Offset 0x0010 */
	u32	fsp_res_memlen;		/* Offset 0x0020 */
	u8	disable_pcie1;		/* Offset 0x0024 */
	u8	disable_pcie2;		/* Offset 0x0025 */
	u8	disable_pcie3;		/* Offset 0x0026 */
	u8	enable_azalia;		/* Offset 0x0027 */
	u8	legacy_seg_decode;	/* Offset 0x0028 */
	u8	pcie_port_ioh;		/* Offset 0x0029 */
};

#endif
