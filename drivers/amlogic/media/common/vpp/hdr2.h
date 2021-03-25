/*
 * drivers/vpp/hdr2..h
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
#ifndef __HDR2_H__
#define __HDR2_H__

enum hdr_module_sel {
	VD1_HDR = 0x1,
	VD2_HDR = 0x2,
	VD3_HDR = 0x3,
	OSD1_HDR = 0x4,
	OSD2_HDR = 0x5,
	VDIN0_HDR = 0x8,
	VDIN1_HDR = 0x10,
	DI_HDR = 0x20,
	OSD3_HDR = 0x40,
	HDR_MAX
};

enum hdr_matrix_sel {
	HDR_IN_MTX = 0x1,
	HDR_GAMUT_MTX = 0x2,
	HDR_OUT_MTX = 0x4,
	HDR_MTX_MAX
};

enum hdr_lut_sel {
	HDR_EOTF_LUT = 0x1,
	HDR_OOTF_LUT = 0x2,
	HDR_OETF_LUT = 0x4,
	HDR_CGAIN_LUT = 0x8,
	HDR_LUT_MAX
};

enum hdr_process_sel {
	HDR_BYPASS = 0x1,
	HDR_SDR = 0x2,
	SDR_HDR = 0x4,
	HLG_BYPASS = 0x8,
	HLG_SDR = 0x10,
	HLG_HDR = 0x20,
	SDR_HLG = 0X40,
	HDRPLUS_SDR = 0x80,
	HDR_OFF = 0x100,
	RGB_BYPASS = 0x200,
	HDR_p_MAX
};

#define MTX_ON  1
#define MTX_OFF 0

#define MTX_ONLY  1
#define HDR_ONLY  0

#define LUT_ON  1
#define LUT_OFF 0

#define HDR2_EOTF_LUT_SIZE 143
#define HDR2_OOTF_LUT_SIZE 149
#define HDR2_OETF_LUT_SIZE 149
#define HDR2_CGAIN_LUT_SIZE 65

struct hdr_proc_mtx_param_s {
	int mtx_only;
	int mtx_in[15];
	int mtx_gamut[9];
	int mtx_gamut_mode;
	int mtx_cgain[15];
	int mtx_ogain[15];
	int mtx_out[15];
	int mtxi_pre_offset[3];
	int mtxi_pos_offset[3];
	int mtxo_pre_offset[3];
	int mtxo_pos_offset[3];
	unsigned int mtx_on;
	enum hdr_process_sel p_sel;
};

struct hdr_proc_lut_param_s {
	int eotf_lut[143];
	int oetf_lut[149];
	int ogain_lut[149];
	int cgain_lut[65];
	unsigned int lut_on;
	unsigned int bitdepth;
	unsigned int cgain_en;
};

void hdr_func(enum hdr_module_sel module_sel,
	      enum hdr_process_sel hdr_process_select);

#ifndef OSD2_HDR2_CTRL
#define OSD2_HDR2_CTRL                             0x5b00
#endif
#ifndef OSD2_HDR2_CLK_GATE
#define OSD2_HDR2_CLK_GATE                         0x5b01
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF00_01
#define OSD2_HDR2_MATRIXI_COEF00_01                0x5b02
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF02_10
#define OSD2_HDR2_MATRIXI_COEF02_10                0x5b03
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF11_12
#define OSD2_HDR2_MATRIXI_COEF11_12                0x5b04
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF20_21
#define OSD2_HDR2_MATRIXI_COEF20_21                0x5b05
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF22
#define OSD2_HDR2_MATRIXI_COEF22                   0x5b06
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF30_31
#define OSD2_HDR2_MATRIXI_COEF30_31                0x5b07
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF32_40
#define OSD2_HDR2_MATRIXI_COEF32_40                0x5b08
#endif
#ifndef OSD2_HDR2_MATRIXI_COEF41_42
#define OSD2_HDR2_MATRIXI_COEF41_42                0x5b09
#endif
#ifndef OSD2_HDR2_MATRIXI_OFFSET0_1
#define OSD2_HDR2_MATRIXI_OFFSET0_1                0x5b0a
#endif
#ifndef OSD2_HDR2_MATRIXI_OFFSET2
#define OSD2_HDR2_MATRIXI_OFFSET2                  0x5b0b
#endif
#ifndef OSD2_HDR2_MATRIXI_PRE_OFFSET0_1
#define OSD2_HDR2_MATRIXI_PRE_OFFSET0_1            0x5b0c
#endif
#ifndef OSD2_HDR2_MATRIXI_PRE_OFFSET2
#define OSD2_HDR2_MATRIXI_PRE_OFFSET2              0x5b0d
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF00_01
#define OSD2_HDR2_MATRIXO_COEF00_01                0x5b0e
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF02_10
#define OSD2_HDR2_MATRIXO_COEF02_10                0x5b0f
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF11_12
#define OSD2_HDR2_MATRIXO_COEF11_12                0x5b10
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF20_21
#define OSD2_HDR2_MATRIXO_COEF20_21                0x5b11
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF22
#define OSD2_HDR2_MATRIXO_COEF22                   0x5b12
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF30_31
#define OSD2_HDR2_MATRIXO_COEF30_31                0x5b13
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF32_40
#define OSD2_HDR2_MATRIXO_COEF32_40                0x5b14
#endif
#ifndef OSD2_HDR2_MATRIXO_COEF41_42
#define OSD2_HDR2_MATRIXO_COEF41_42                0x5b15
#endif
#ifndef OSD2_HDR2_MATRIXO_OFFSET0_1
#define OSD2_HDR2_MATRIXO_OFFSET0_1                0x5b16
#endif
#ifndef OSD2_HDR2_MATRIXO_OFFSET2
#define OSD2_HDR2_MATRIXO_OFFSET2                  0x5b17
#endif
#ifndef OSD2_HDR2_MATRIXO_PRE_OFFSET0_1
#define OSD2_HDR2_MATRIXO_PRE_OFFSET0_1            0x5b18
#endif
#ifndef OSD2_HDR2_MATRIXO_PRE_OFFSET2
#define OSD2_HDR2_MATRIXO_PRE_OFFSET2              0x5b19
#endif
#ifndef OSD2_HDR2_MATRIXI_CLIP
#define OSD2_HDR2_MATRIXI_CLIP                     0x5b1a
#endif
#ifndef OSD2_HDR2_MATRIXO_CLIP
#define OSD2_HDR2_MATRIXO_CLIP                     0x5b1b
#endif
#ifndef OSD2_HDR2_CGAIN_OFFT
#define OSD2_HDR2_CGAIN_OFFT                       0x5b1c
#endif
#ifndef OSD2_HDR2_HIST_RD
#define OSD2_HDR2_HIST_RD                          0x5b1d
#endif
#ifndef OSD2_EOTF_LUT_ADDR_PORT
#define OSD2_EOTF_LUT_ADDR_PORT                    0x5b1e
#endif
#ifndef OSD2_EOTF_LUT_DATA_PORT
#define OSD2_EOTF_LUT_DATA_PORT                    0x5b1f
#endif
#ifndef OSD2_OETF_LUT_ADDR_PORT
#define OSD2_OETF_LUT_ADDR_PORT                    0x5b20
#endif
#ifndef OSD2_OETF_LUT_DATA_PORT
#define OSD2_OETF_LUT_DATA_PORT                    0x5b21
#endif
#ifndef OSD2_CGAIN_LUT_ADDR_PORT
#define OSD2_CGAIN_LUT_ADDR_PORT                   0x5b22
#endif
#ifndef OSD2_CGAIN_LUT_DATA_PORT
#define OSD2_CGAIN_LUT_DATA_PORT                   0x5b23
#endif
#ifndef OSD2_HDR2_CGAIN_COEF0
#define OSD2_HDR2_CGAIN_COEF0                      0x5b24
#endif
#ifndef OSD2_HDR2_CGAIN_COEF1
#define OSD2_HDR2_CGAIN_COEF1                      0x5b25
#endif
#ifndef OSD2_OGAIN_LUT_ADDR_PORT
#define OSD2_OGAIN_LUT_ADDR_PORT                   0x5b26
#endif
#ifndef OSD2_OGAIN_LUT_DATA_PORT
#define OSD2_OGAIN_LUT_DATA_PORT                   0x5b27
#endif
#ifndef OSD2_HDR2_ADPS_CTRL
#define OSD2_HDR2_ADPS_CTRL                        0x5b28
#endif
#ifndef OSD2_HDR2_ADPS_ALPHA0
#define OSD2_HDR2_ADPS_ALPHA0                      0x5b29
#endif
#ifndef OSD2_HDR2_ADPS_ALPHA1
#define OSD2_HDR2_ADPS_ALPHA1                      0x5b2a
#endif
#ifndef OSD2_HDR2_ADPS_BETA0
#define OSD2_HDR2_ADPS_BETA0                       0x5b2b
#endif
#ifndef OSD2_HDR2_ADPS_BETA1
#define OSD2_HDR2_ADPS_BETA1                       0x5b2c
#endif
#ifndef OSD2_HDR2_ADPS_BETA2
#define OSD2_HDR2_ADPS_BETA2                       0x5b2d
#endif
#ifndef OSD2_HDR2_ADPS_COEF0
#define OSD2_HDR2_ADPS_COEF0                       0x5b2e
#endif
#ifndef OSD2_HDR2_ADPS_COEF1
#define OSD2_HDR2_ADPS_COEF1                       0x5b2f
#endif
#ifndef OSD2_HDR2_GMUT_CTRL
#define OSD2_HDR2_GMUT_CTRL                        0x5b30
#endif
#ifndef OSD2_HDR2_GMUT_COEF0
#define OSD2_HDR2_GMUT_COEF0                       0x5b31
#endif
#ifndef OSD2_HDR2_GMUT_COEF1
#define OSD2_HDR2_GMUT_COEF1                       0x5b32
#endif
#ifndef OSD2_HDR2_GMUT_COEF2
#define OSD2_HDR2_GMUT_COEF2                       0x5b33
#endif
#ifndef OSD2_HDR2_GMUT_COEF3
#define OSD2_HDR2_GMUT_COEF3                       0x5b34
#endif
#ifndef OSD2_HDR2_GMUT_COEF4
#define OSD2_HDR2_GMUT_COEF4                       0x5b35
#endif
#ifndef OSD2_HDR2_PIPE_CTRL1
#define OSD2_HDR2_PIPE_CTRL1                       0x5b36
#endif
#ifndef OSD2_HDR2_PIPE_CTRL2
#define OSD2_HDR2_PIPE_CTRL2                       0x5b37
#endif
#ifndef OSD2_HDR2_PIPE_CTRL3
#define OSD2_HDR2_PIPE_CTRL3                       0x5b38
#endif
#ifndef OSD2_HDR2_PROC_WIN1
#define OSD2_HDR2_PROC_WIN1                        0x5b39
#endif

#ifndef OSD2_HDR2_PROC_WIN2
#define OSD2_HDR2_PROC_WIN2                        0x5b3a
#endif
#ifndef OSD2_HDR2_MATRIXI_EN_CTRL
#define OSD2_HDR2_MATRIXI_EN_CTRL                  0x5b3b
#endif
#ifndef OSD2_HDR2_MATRIXO_EN_CTRL
#define OSD2_HDR2_MATRIXO_EN_CTRL                  0x5b3c
#endif
#ifndef OSD2_HDR2_HIST_CTRL
#define OSD2_HDR2_HIST_CTRL                        0x5b3d
#endif
#ifndef OSD2_HDR2_HIST_H_START_END
#define OSD2_HDR2_HIST_H_START_END                 0x5b3e
#endif
#ifndef OSD2_HDR2_HIST_V_START_END
#define OSD2_HDR2_HIST_V_START_END                 0x5b3f
#endif

#endif
