// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <amlogic/cpu_id.h>
#include <config.h>
#include <common.h>
#include <amlogic/media/vpp/vpp.h>
#include <amlogic/media/vout/hdmitx/hdmi_common.h>
/* wait hdmi fix */
//#ifdef CONFIG_AML_HDMITX20
#include <amlogic/media/vout/hdmitx/hdmitx_module.h>
//#else
//#include <amlogic/media/vout/hdmitx21/hdmitx_module.h>
//#endif
#include "vpp_reg.h"
#include "vpp.h"
#include "hdr2.h"

#define VPP_PR(fmt, args...)     printf("vpp: "fmt"", ## args)

static unsigned char vpp_init_flag;

/***************************** gamma table ****************************/
#define GAMMA_SIZE (256)
static unsigned short gamma_table_r[GAMMA_SIZE] = {
	0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
	64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124,
	128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188,
	192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252,
	256, 260, 264, 268, 272, 276, 280, 284, 288, 292, 296, 300, 304, 308, 312, 316,
	320, 324, 328, 332, 336, 340, 344, 348, 352, 356, 360, 364, 368, 372, 376, 380,
	384, 388, 392, 396, 400, 404, 408, 412, 416, 420, 424, 428, 432, 436, 440, 444,
	448, 452, 456, 460, 464, 468, 472, 476, 480, 484, 488, 492, 496, 500, 504, 508,
	512, 516, 520, 524, 528, 532, 536, 540, 544, 548, 552, 556, 560, 564, 568, 572,
	576, 580, 584, 588, 592, 596, 600, 604, 608, 612, 616, 620, 624, 628, 632, 636,
	640, 644, 648, 652, 656, 660, 664, 668, 672, 676, 680, 684, 688, 692, 696, 700,
	704, 708, 712, 716, 720, 724, 728, 732, 736, 740, 744, 748, 752, 756, 760, 764,
	768, 772, 776, 780, 784, 788, 792, 796, 800, 804, 808, 812, 816, 820, 824, 828,
	832, 836, 840, 844, 848, 852, 856, 860, 864, 868, 872, 876, 880, 884, 888, 892,
	896, 900, 904, 908, 912, 916, 920, 924, 928, 932, 936, 940, 944, 948, 952, 956,
	960, 964, 968, 972, 976, 980, 984, 988, 992, 996, 1000, 1004, 1008, 1012, 1016, 1020,
};
static unsigned short gamma_table_g[GAMMA_SIZE] = {
	0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
	64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124,
	128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188,
	192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252,
	256, 260, 264, 268, 272, 276, 280, 284, 288, 292, 296, 300, 304, 308, 312, 316,
	320, 324, 328, 332, 336, 340, 344, 348, 352, 356, 360, 364, 368, 372, 376, 380,
	384, 388, 392, 396, 400, 404, 408, 412, 416, 420, 424, 428, 432, 436, 440, 444,
	448, 452, 456, 460, 464, 468, 472, 476, 480, 484, 488, 492, 496, 500, 504, 508,
	512, 516, 520, 524, 528, 532, 536, 540, 544, 548, 552, 556, 560, 564, 568, 572,
	576, 580, 584, 588, 592, 596, 600, 604, 608, 612, 616, 620, 624, 628, 632, 636,
	640, 644, 648, 652, 656, 660, 664, 668, 672, 676, 680, 684, 688, 692, 696, 700,
	704, 708, 712, 716, 720, 724, 728, 732, 736, 740, 744, 748, 752, 756, 760, 764,
	768, 772, 776, 780, 784, 788, 792, 796, 800, 804, 808, 812, 816, 820, 824, 828,
	832, 836, 840, 844, 848, 852, 856, 860, 864, 868, 872, 876, 880, 884, 888, 892,
	896, 900, 904, 908, 912, 916, 920, 924, 928, 932, 936, 940, 944, 948, 952, 956,
	960, 964, 968, 972, 976, 980, 984, 988, 992, 996, 1000, 1004, 1008, 1012, 1016, 1020,
};
static unsigned short gamma_table_b[GAMMA_SIZE] = {
	0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60,
	64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124,
	128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188,
	192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252,
	256, 260, 264, 268, 272, 276, 280, 284, 288, 292, 296, 300, 304, 308, 312, 316,
	320, 324, 328, 332, 336, 340, 344, 348, 352, 356, 360, 364, 368, 372, 376, 380,
	384, 388, 392, 396, 400, 404, 408, 412, 416, 420, 424, 428, 432, 436, 440, 444,
	448, 452, 456, 460, 464, 468, 472, 476, 480, 484, 488, 492, 496, 500, 504, 508,
	512, 516, 520, 524, 528, 532, 536, 540, 544, 548, 552, 556, 560, 564, 568, 572,
	576, 580, 584, 588, 592, 596, 600, 604, 608, 612, 616, 620, 624, 628, 632, 636,
	640, 644, 648, 652, 656, 660, 664, 668, 672, 676, 680, 684, 688, 692, 696, 700,
	704, 708, 712, 716, 720, 724, 728, 732, 736, 740, 744, 748, 752, 756, 760, 764,
	768, 772, 776, 780, 784, 788, 792, 796, 800, 804, 808, 812, 816, 820, 824, 828,
	832, 836, 840, 844, 848, 852, 856, 860, 864, 868, 872, 876, 880, 884, 888, 892,
	896, 900, 904, 908, 912, 916, 920, 924, 928, 932, 936, 940, 944, 948, 952, 956,
	960, 964, 968, 972, 976, 980, 984, 988, 992, 996, 1000, 1004, 1008, 1012, 1016, 1020,
};

/***************************** gxl hdr ****************************/

#define EOTF_LUT_SIZE 33
static unsigned int osd_eotf_r_mapping[EOTF_LUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

static unsigned int osd_eotf_g_mapping[EOTF_LUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

static unsigned int osd_eotf_b_mapping[EOTF_LUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

static unsigned int video_eotf_r_mapping[EOTF_LUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

static unsigned int video_eotf_g_mapping[EOTF_LUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

static unsigned int video_eotf_b_mapping[EOTF_LUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

#define EOTF_COEFF_NORM(a) ((int)((((a) * 4096.0) + 1) / 2))
#define EOTF_COEFF_SIZE 10
#define EOTF_COEFF_RIGHTSHIFT 1
static int osd_eotf_coeff[EOTF_COEFF_SIZE] = {
	EOTF_COEFF_NORM(1.0), EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(1.0), EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(1.0),
	EOTF_COEFF_RIGHTSHIFT /* right shift */
};

static int video_eotf_coeff[EOTF_COEFF_SIZE] = {
	EOTF_COEFF_NORM(1.0), EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(1.0), EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(0.0), EOTF_COEFF_NORM(1.0),
	EOTF_COEFF_RIGHTSHIFT /* right shift */
};

/******************** osd oetf **************/

#define OSD_OETF_LUT_SIZE 41
static unsigned int osd_oetf_r_mapping[OSD_OETF_LUT_SIZE] = {
		0, 150, 250, 330,
		395, 445, 485, 520,
		544, 632, 686, 725,
		756, 782, 803, 822,
		839, 854, 868, 880,
		892, 902, 913, 922,
		931, 939, 947, 954,
		961, 968, 974, 981,
		986, 993, 998, 1003,
		1009, 1014, 1018, 1023,
		0
};

static unsigned int osd_oetf_g_mapping[OSD_OETF_LUT_SIZE] = {
		0, 0, 0, 0,
		0, 32, 64, 96,
		128, 160, 196, 224,
		256, 288, 320, 352,
		384, 416, 448, 480,
		512, 544, 576, 608,
		640, 672, 704, 736,
		768, 800, 832, 864,
		896, 928, 960, 992,
		1023, 1023, 1023, 1023,
		1023
};

static unsigned int osd_oetf_b_mapping[OSD_OETF_LUT_SIZE] = {
		0, 0, 0, 0,
		0, 32, 64, 96,
		128, 160, 196, 224,
		256, 288, 320, 352,
		384, 416, 448, 480,
		512, 544, 576, 608,
		640, 672, 704, 736,
		768, 800, 832, 864,
		896, 928, 960, 992,
		1023, 1023, 1023, 1023,
		1023
};

/************ video oetf ***************/

#define VIDEO_OETF_LUT_SIZE 289
static unsigned int video_oetf_r_mapping[VIDEO_OETF_LUT_SIZE] = {
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   4,    8,   12,   16,   20,   24,   28,   32,
	  36,   40,   44,   48,   52,   56,   60,   64,
	  68,   72,   76,   80,   84,   88,   92,   96,
	 100,  104,  108,  112,  116,  120,  124,  128,
	 132,  136,  140,  144,  148,  152,  156,  160,
	 164,  168,  172,  176,  180,  184,  188,  192,
	 196,  200,  204,  208,  212,  216,  220,  224,
	 228,  232,  236,  240,  244,  248,  252,  256,
	 260,  264,  268,  272,  276,  280,  284,  288,
	 292,  296,  300,  304,  308,  312,  316,  320,
	 324,  328,  332,  336,  340,  344,  348,  352,
	 356,  360,  364,  368,  372,  376,  380,  384,
	 388,  392,  396,  400,  404,  408,  412,  416,
	 420,  424,  428,  432,  436,  440,  444,  448,
	 452,  456,  460,  464,  468,  472,  476,  480,
	 484,  488,  492,  496,  500,  504,  508,  512,
	 516,  520,  524,  528,  532,  536,  540,  544,
	 548,  552,  556,  560,  564,  568,  572,  576,
	 580,  584,  588,  592,  596,  600,  604,  608,
	 612,  616,  620,  624,  628,  632,  636,  640,
	 644,  648,  652,  656,  660,  664,  668,  672,
	 676,  680,  684,  688,  692,  696,  700,  704,
	 708,  712,  716,  720,  724,  728,  732,  736,
	 740,  744,  748,  752,  756,  760,  764,  768,
	 772,  776,  780,  784,  788,  792,  796,  800,
	 804,  808,  812,  816,  820,  824,  828,  832,
	 836,  840,  844,  848,  852,  856,  860,  864,
	 868,  872,  876,  880,  884,  888,  892,  896,
	 900,  904,  908,  912,  916,  920,  924,  928,
	 932,  936,  940,  944,  948,  952,  956,  960,
	 964,  968,  972,  976,  980,  984,  988,  992,
	 996, 1000, 1004, 1008, 1012, 1016, 1020, 1023,
	1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
	1023
};

static unsigned int video_oetf_g_mapping[VIDEO_OETF_LUT_SIZE] = {
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   4,    8,   12,   16,   20,   24,   28,   32,
	  36,   40,   44,   48,   52,   56,   60,   64,
	  68,   72,   76,   80,   84,   88,   92,   96,
	 100,  104,  108,  112,  116,  120,  124,  128,
	 132,  136,  140,  144,  148,  152,  156,  160,
	 164,  168,  172,  176,  180,  184,  188,  192,
	 196,  200,  204,  208,  212,  216,  220,  224,
	 228,  232,  236,  240,  244,  248,  252,  256,
	 260,  264,  268,  272,  276,  280,  284,  288,
	 292,  296,  300,  304,  308,  312,  316,  320,
	 324,  328,  332,  336,  340,  344,  348,  352,
	 356,  360,  364,  368,  372,  376,  380,  384,
	 388,  392,  396,  400,  404,  408,  412,  416,
	 420,  424,  428,  432,  436,  440,  444,  448,
	 452,  456,  460,  464,  468,  472,  476,  480,
	 484,  488,  492,  496,  500,  504,  508,  512,
	 516,  520,  524,  528,  532,  536,  540,  544,
	 548,  552,  556,  560,  564,  568,  572,  576,
	 580,  584,  588,  592,  596,  600,  604,  608,
	 612,  616,  620,  624,  628,  632,  636,  640,
	 644,  648,  652,  656,  660,  664,  668,  672,
	 676,  680,  684,  688,  692,  696,  700,  704,
	 708,  712,  716,  720,  724,  728,  732,  736,
	 740,  744,  748,  752,  756,  760,  764,  768,
	 772,  776,  780,  784,  788,  792,  796,  800,
	 804,  808,  812,  816,  820,  824,  828,  832,
	 836,  840,  844,  848,  852,  856,  860,  864,
	 868,  872,  876,  880,  884,  888,  892,  896,
	 900,  904,  908,  912,  916,  920,  924,  928,
	 932,  936,  940,  944,  948,  952,  956,  960,
	 964,  968,  972,  976,  980,  984,  988,  992,
	 996, 1000, 1004, 1008, 1012, 1016, 1020, 1023,
	1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
	1023
};

static unsigned int video_oetf_b_mapping[VIDEO_OETF_LUT_SIZE] = {
	   0,    0,    0,    0,    0,    0,    0,    0,
	   0,    0,    0,    0,    0,    0,    0,    0,
	   4,    8,   12,   16,   20,   24,   28,   32,
	  36,   40,   44,   48,   52,   56,   60,   64,
	  68,   72,   76,   80,   84,   88,   92,   96,
	 100,  104,  108,  112,  116,  120,  124,  128,
	 132,  136,  140,  144,  148,  152,  156,  160,
	 164,  168,  172,  176,  180,  184,  188,  192,
	 196,  200,  204,  208,  212,  216,  220,  224,
	 228,  232,  236,  240,  244,  248,  252,  256,
	 260,  264,  268,  272,  276,  280,  284,  288,
	 292,  296,  300,  304,  308,  312,  316,  320,
	 324,  328,  332,  336,  340,  344,  348,  352,
	 356,  360,  364,  368,  372,  376,  380,  384,
	 388,  392,  396,  400,  404,  408,  412,  416,
	 420,  424,  428,  432,  436,  440,  444,  448,
	 452,  456,  460,  464,  468,  472,  476,  480,
	 484,  488,  492,  496,  500,  504,  508,  512,
	 516,  520,  524,  528,  532,  536,  540,  544,
	 548,  552,  556,  560,  564,  568,  572,  576,
	 580,  584,  588,  592,  596,  600,  604,  608,
	 612,  616,  620,  624,  628,  632,  636,  640,
	 644,  648,  652,  656,  660,  664,  668,  672,
	 676,  680,  684,  688,  692,  696,  700,  704,
	 708,  712,  716,  720,  724,  728,  732,  736,
	 740,  744,  748,  752,  756,  760,  764,  768,
	 772,  776,  780,  784,  788,  792,  796,  800,
	 804,  808,  812,  816,  820,  824,  828,  832,
	 836,  840,  844,  848,  852,  856,  860,  864,
	 868,  872,  876,  880,  884,  888,  892,  896,
	 900,  904,  908,  912,  916,  920,  924,  928,
	 932,  936,  940,  944,  948,  952,  956,  960,
	 964,  968,  972,  976,  980,  984,  988,  992,
	 996, 1000, 1004, 1008, 1012, 1016, 1020, 1023,
	1023, 1023, 1023, 1023, 1023, 1023, 1023, 1023,
	1023
};

#define COEFF_NORM(a) ((int)((((a) * 2048.0) + 1) / 2))
#define COEFF_NORM12(a) ((int)((((a) * 8192.0) + 1) / 2))

#define MATRIX_5x3_COEF_SIZE 24
/******* osd1 matrix0 *******/
/* default rgb to yuv_limit */
static int osd_matrix_coeff[MATRIX_5x3_COEF_SIZE] = {
	0, 0, 0, /* pre offset */
	COEFF_NORM(0.2126),	COEFF_NORM(0.7152),	COEFF_NORM(0.0722),
	COEFF_NORM(-0.11457),	COEFF_NORM(-0.38543),	COEFF_NORM(0.5),
	COEFF_NORM(0.5),	COEFF_NORM(-0.45415),	COEFF_NORM(-0.045847),
	0, 0, 0, /* 30/31/32 */
	0, 0, 0, /* 40/41/42 */
	0, 512, 512, /* offset */
	0, 0, 0 /* mode, right_shift, clip_en */
};

static int vd1_matrix_coeff[MATRIX_5x3_COEF_SIZE] = {
	0, 0, 0, /* pre offset */
	COEFF_NORM(1.0),	COEFF_NORM(0.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(1.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(0.0),	COEFF_NORM(1.0),
	0, 0, 0, /* 30/31/32 */
	0, 0, 0, /* 40/41/42 */
	0, 0, 0, /* offset */
	0, 0, 0 /* mode, right_shift, clip_en */
};

static int vd2_matrix_coeff[MATRIX_5x3_COEF_SIZE] = {
	0, 0, 0, /* pre offset */
	COEFF_NORM(1.0),	COEFF_NORM(0.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(1.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(0.0),	COEFF_NORM(1.0),
	0, 0, 0, /* 30/31/32 */
	0, 0, 0, /* 40/41/42 */
	0, 0, 0, /* offset */
	0, 0, 0 /* mode, right_shift, clip_en */
};

static int post_matrix_coeff[MATRIX_5x3_COEF_SIZE] = {
	0, 0, 0, /* pre offset */
	COEFF_NORM(1.0),	COEFF_NORM(0.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(1.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(0.0),	COEFF_NORM(1.0),
	0, 0, 0, /* 30/31/32 */
	0, 0, 0, /* 40/41/42 */
	0, 0, 0, /* offset */
	0, 0, 0 /* mode, right_shift, clip_en */
};

static int xvycc_matrix_coeff[MATRIX_5x3_COEF_SIZE] = {
	0, 0, 0, /* pre offset */
	COEFF_NORM(1.0),	COEFF_NORM(0.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(1.0),	COEFF_NORM(0.0),
	COEFF_NORM(0.0),	COEFF_NORM(0.0),	COEFF_NORM(1.0),
	0, 0, 0, /* 30/31/32 */
	0, 0, 0, /* 40/41/42 */
	0, 0, 0, /* offset */
	0, 0, 0 /* mode, right_shift, clip_en */
};

static int RGB709_to_YUV709l_coeff[MATRIX_5x3_COEF_SIZE] = {
	0, 0, 0, /* pre offset */
	COEFF_NORM(0.181873),	COEFF_NORM(0.611831),	COEFF_NORM(0.061765),
	COEFF_NORM(-0.100251),	COEFF_NORM(-0.337249),	COEFF_NORM(0.437500),
	COEFF_NORM(0.437500),	COEFF_NORM(-0.397384),	COEFF_NORM(-0.040116),
	0, 0, 0, /* 10'/11'/12' */
	0, 0, 0, /* 20'/21'/22' */
	64, 512, 512, /* offset */
	0, 0, 0 /* mode, right_shift, clip_en */
};

/*  eotf matrix: bypass */
static int eotf_bypass_coeff[EOTF_COEFF_SIZE] = {
	EOTF_COEFF_NORM(1.0),	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(1.0),	EOTF_COEFF_NORM(0.0),
	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(0.0),	EOTF_COEFF_NORM(1.0),
	EOTF_COEFF_RIGHTSHIFT /* right shift */
};

/* eotf lut: linear */
static unsigned int eotf_33_linear_mapping[EOTF_LUT_SIZE] = {
	0x0000,	0x0200,	0x0400, 0x0600,
	0x0800, 0x0a00, 0x0c00, 0x0e00,
	0x1000, 0x1200, 0x1400, 0x1600,
	0x1800, 0x1a00, 0x1c00, 0x1e00,
	0x2000, 0x2200, 0x2400, 0x2600,
	0x2800, 0x2a00, 0x2c00, 0x2e00,
	0x3000, 0x3200, 0x3400, 0x3600,
	0x3800, 0x3a00, 0x3c00, 0x3e00,
	0x4000
};

/* osd oetf lut: linear */
static unsigned int oetf_41_linear_mapping[OSD_OETF_LUT_SIZE] = {
	0, 0, 0, 0,
	0, 32, 64, 96,
	128, 160, 196, 224,
	256, 288, 320, 352,
	384, 416, 448, 480,
	512, 544, 576, 608,
	640, 672, 704, 736,
	768, 800, 832, 864,
	896, 928, 960, 992,
	1023, 1023, 1023, 1023,
	1023
};

/*static int YUV709l_to_RGB709_coeff[MATRIX_5x3_COEF_SIZE] = { */
/*	-64, -512, -512,  pre offset */
/*	COEFF_NORM(1.16895),	COEFF_NORM(0.00000),	COEFF_NORM(1.79977), */
/*	COEFF_NORM(1.16895),	COEFF_NORM(-0.21408),	COEFF_NORM(-0.53500), */
/*	COEFF_NORM(1.16895),	COEFF_NORM(2.12069),	COEFF_NORM(0.00000), */
/*	0, 0, 0,  30/31/32 */
/*	0, 0, 0,  40/41/42 */
/*	0, 0, 0,  offset */
/*	0, 0, 0  mode, right_shift, clip_en */
/*}; */

static int YUV709l_to_RGB709_coeff12[MATRIX_5x3_COEF_SIZE] = {
	-256, -2048, -2048, /* pre offset */
	COEFF_NORM12(1.16895),	COEFF_NORM12(0.00000),	COEFF_NORM12(1.79977),
	COEFF_NORM12(1.16895),	COEFF_NORM12(-0.21408),	COEFF_NORM12(-0.53500),
	COEFF_NORM12(1.16895),	COEFF_NORM12(2.12069),	COEFF_NORM12(0.00000),
	0, 0, 0, /* 30/31/32 */
	0, 0, 0, /* 40/41/42 */
	0, 0, 0, /* offset */
	0, 0, 0 /* mode, right_shift, clip_en */
};

#define SIGN(a) ((a < 0) ? "-" : "+")
#define DECI(a) ((a) / 1024)
#define FRAC(a) ((((a) >= 0) ? \
	((a) & 0x3ff) : ((~(a) + 1) & 0x3ff)) * 10000 / 1024)

#define INORM	50000
#ifdef CONFIG_AML_HDMITX
static u32 bt2020_primaries[3][2] = {
	{0.17 * INORM + 0.5, 0.797 * INORM + 0.5},	/* G */
	{0.131 * INORM + 0.5, 0.046 * INORM + 0.5},	/* B */
	{0.708 * INORM + 0.5, 0.292 * INORM + 0.5},	/* R */
};

static u32 bt2020_white_point[2] = {
	0.3127 * INORM + 0.5, 0.3290 * INORM + 0.5
};
#endif

static int vpp_get_chip_type(void)
{
	unsigned int cpu_type;

	cpu_type = get_cpu_id().family_id;
	return cpu_type;
}

int is_osd_high_version(void)
{
	u32 family_id = get_cpu_id().family_id;

	if (family_id == MESON_CPU_MAJOR_ID_G12A ||
	    family_id == MESON_CPU_MAJOR_ID_G12B ||
	    family_id >= MESON_CPU_MAJOR_ID_SM1)
		return 1;
	else
		return 0;
}

/* OSD csc defines end */

static void vpp_set_matrix_default_init(void)
{
	/* default probe_sel, for highlight en */
	vpp_reg_setb(VPP_MATRIX_CTRL, 0xf, 11, 4);
}

static void vpp_top_post2_matrix_yuv2rgb(int vpp_top)
{
	int *m = NULL;
	/* POST2 matrix: YUV limit -> RGB  default is 12bit*/
	m = YUV709l_to_RGB709_coeff12;

	if (vpp_top == 0) {
		/* VPP WRAP POST2 matrix */
		vpp_reg_write(VPP_POST2_MATRIX_PRE_OFFSET0_1,
			(((m[0] >> 2) & 0xfff) << 16) | ((m[1] >> 2) & 0xfff));
		vpp_reg_write(VPP_POST2_MATRIX_PRE_OFFSET2,
			(m[2] >> 2) & 0xfff);
		vpp_reg_write(VPP_POST2_MATRIX_COEF00_01,
			(((m[3] >> 2) & 0x1fff) << 16) | ((m[4] >> 2) & 0x1fff));
		vpp_reg_write(VPP_POST2_MATRIX_COEF02_10,
			(((m[5] >> 2) & 0x1fff) << 16) | ((m[6] >> 2) & 0x1fff));
		vpp_reg_write(VPP_POST2_MATRIX_COEF11_12,
			(((m[7] >> 2) & 0x1fff) << 16) | ((m[8] >> 2) & 0x1fff));
		vpp_reg_write(VPP_POST2_MATRIX_COEF20_21,
			(((m[9] >> 2) & 0x1fff) << 16) | ((m[10] >> 2) & 0x1fff));
		vpp_reg_write(VPP_POST2_MATRIX_COEF22,
			(m[11] >> 2) & 0x1fff);
		vpp_reg_write(VPP_POST2_MATRIX_OFFSET0_1,
			(((m[18] >> 2) & 0xfff) << 16) | ((m[19] >> 2) & 0xfff));
		vpp_reg_write(VPP_POST2_MATRIX_OFFSET2,
			(m[20] >> 2) & 0xfff);
		vpp_reg_setb(VPP_POST2_MATRIX_EN_CTRL, 1, 0, 1);
	} else if (vpp_top == 1) {
		vpp_reg_write(VPP1_MATRIX_PRE_OFFSET0_1,
			(((m[0] >> 2) & 0xfff) << 16) | ((m[1] >> 2) & 0xfff));
		vpp_reg_write(VPP1_MATRIX_PRE_OFFSET2,
			(m[2] >> 2) & 0xfff);
		vpp_reg_write(VPP1_MATRIX_COEF00_01,
			(((m[3] >> 2) & 0x1fff) << 16) | ((m[4] >> 2) & 0x1fff));
		vpp_reg_write(VPP1_MATRIX_COEF02_10,
			(((m[5] >> 2) & 0x1fff) << 16) | ((m[6] >> 2) & 0x1fff));
		vpp_reg_write(VPP1_MATRIX_COEF11_12,
			(((m[7] >> 2) & 0x1fff) << 16) | ((m[8] >> 2) & 0x1fff));
		vpp_reg_write(VPP1_MATRIX_COEF20_21,
			(((m[9] >> 2) & 0x1fff) << 16) | ((m[10] >> 2) & 0x1fff));
		vpp_reg_write(VPP1_MATRIX_COEF22,
			(m[11] >> 2) & 0x1fff);

		vpp_reg_write(VPP1_MATRIX_OFFSET0_1,
			(((m[18] >> 2) & 0xfff) << 16) | ((m[19] >> 2) & 0xfff));
		vpp_reg_write(VPP1_MATRIX_OFFSET2,
			(m[20] >> 2) & 0xfff);

		vpp_reg_setb(VPP1_MATRIX_EN_CTRL, 1, 0, 1);
	} else if (vpp_top == 2) {
		vpp_reg_write(VPP2_MATRIX_PRE_OFFSET0_1,
			(((m[0] >> 2) & 0xfff) << 16) | ((m[1] >> 2) & 0xfff));
		vpp_reg_write(VPP2_MATRIX_PRE_OFFSET2,
			(m[2] >> 2) & 0xfff);
		vpp_reg_write(VPP2_MATRIX_COEF00_01,
			(((m[3] >> 2) & 0x1fff) << 16) | ((m[4] >> 2) & 0x1fff));
		vpp_reg_write(VPP2_MATRIX_COEF02_10,
			(((m[5] >> 2) & 0x1fff) << 16) | ((m[6] >> 2) & 0x1fff));
		vpp_reg_write(VPP2_MATRIX_COEF11_12,
			(((m[7] >> 2) & 0x1fff) << 16) | ((m[8] >> 2) & 0x1fff));
		vpp_reg_write(VPP2_MATRIX_COEF20_21,
			(((m[9] >> 2) & 0x1fff) << 16) | ((m[10] >> 2) & 0x1fff));
		vpp_reg_write(VPP2_MATRIX_COEF22,
			(m[11] >> 2) & 0x1fff);

		vpp_reg_write(VPP2_MATRIX_OFFSET0_1,
			(((m[18] >> 2) & 0xfff) << 16) | ((m[19] >> 2) & 0xfff));
		vpp_reg_write(VPP2_MATRIX_OFFSET2,
			(m[20] >> 2) & 0xfff);

		vpp_reg_setb(VPP2_MATRIX_EN_CTRL, 1, 0, 1);
	}

}
static void vpp_set_matrix_ycbcr2rgb(int vd1_or_vd2_or_post, int mode)
{
	//VPP_PR("%s: %d, %d\n", __func__, vd1_or_vd2_or_post, mode);

	if (is_osd_high_version()) {
		/* vpp top0 */
		vpp_top_post2_matrix_yuv2rgb(0);
		VPP_PR("g12a/b post2(bit12) matrix: YUV limit -> RGB ..............\n");
		return;
	}
	if (vd1_or_vd2_or_post == 0) { //vd1
		vpp_reg_setb(VPP_MATRIX_CTRL, 1, 5, 1);
		vpp_reg_setb(VPP_MATRIX_CTRL, 1, 8, 3);
	} else if (vd1_or_vd2_or_post == 1) { //vd2
		vpp_reg_setb(VPP_MATRIX_CTRL, 1, 4, 1);
		vpp_reg_setb(VPP_MATRIX_CTRL, 2, 8, 3);
	} else if (vd1_or_vd2_or_post == 3) { //osd
		vpp_reg_setb(VPP_MATRIX_CTRL, 1, 7, 1);
		vpp_reg_setb(VPP_MATRIX_CTRL, 4, 8, 3);
	} else if (vd1_or_vd2_or_post == 4) { //xvycc
		vpp_reg_setb(VPP_MATRIX_CTRL, 1, 6, 1);
		vpp_reg_setb(VPP_MATRIX_CTRL, 3, 8, 3);
	} else {
		vpp_reg_setb(VPP_MATRIX_CTRL, 1, 0, 1);
		vpp_reg_setb(VPP_MATRIX_CTRL, 0, 8, 3);
		if (mode == 0)
			vpp_reg_setb(VPP_MATRIX_CTRL, 1, 1, 2);
		else if (mode == 1)
			vpp_reg_setb(VPP_MATRIX_CTRL, 0, 1, 2);
	}

	if (mode == 0) { /* 601 limit to RGB */
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET0_1, 0x0064C8FF);
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET2, 0x006400C8);
		//1.164     0       1.596
		//1.164   -0.392    -0.813
		//1.164   2.017     0
		vpp_reg_write(VPP_MATRIX_COEF00_01, 0x04A80000);
		vpp_reg_write(VPP_MATRIX_COEF02_10, 0x066204A8);
		vpp_reg_write(VPP_MATRIX_COEF11_12, 0x1e701cbf);
		vpp_reg_write(VPP_MATRIX_COEF20_21, 0x04A80812);
		vpp_reg_write(VPP_MATRIX_COEF22, 0x00000000);
		vpp_reg_write(VPP_MATRIX_OFFSET0_1, 0x00000000);
		vpp_reg_write(VPP_MATRIX_OFFSET2, 0x00000000);
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET0_1, 0x0FC00E00);
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET2, 0x00000E00);
	} else if (mode == 1) { /* 601 limit to RGB  */
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET0_1, 0x0000E00);
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET2, 0x0E00);
		//	1	0			1.402
		//	1	-0.34414	-0.71414
		//	1	1.772		0
		vpp_reg_write(VPP_MATRIX_COEF00_01, (0x400 << 16) |0);
		vpp_reg_write(VPP_MATRIX_COEF02_10, (0x59c << 16) |0x400);
		vpp_reg_write(VPP_MATRIX_COEF11_12, (0x1ea0 << 16) |0x1d24);
		vpp_reg_write(VPP_MATRIX_COEF20_21, (0x400 << 16) |0x718);
		vpp_reg_write(VPP_MATRIX_COEF22, 0x0);
		vpp_reg_write(VPP_MATRIX_OFFSET0_1, 0x0);
		vpp_reg_write(VPP_MATRIX_OFFSET2, 0x0);
	} else if (mode == 2) { /* 709F to RGB */
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET0_1, 0x0000E00);
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET2, 0x0E00);
		//	1	0			1.402
		//	1	-0.34414	-0.71414
		//	1	1.772		0
		vpp_reg_write(VPP_MATRIX_COEF00_01, 0x04000000);
		vpp_reg_write(VPP_MATRIX_COEF02_10, 0x064D0400);
		vpp_reg_write(VPP_MATRIX_COEF11_12, 0x1F411E21);
		vpp_reg_write(VPP_MATRIX_COEF20_21, 0x0400076D);
		vpp_reg_write(VPP_MATRIX_COEF22, 0x0);
		vpp_reg_write(VPP_MATRIX_OFFSET0_1, 0x0);
		vpp_reg_write(VPP_MATRIX_OFFSET2, 0x0);
	} else if (mode == 3) { /* 709L to RGB */
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET0_1, 0x0FC00E00);
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET2, 0x00000E00);
		/* ycbcr limit range, 709 to RGB */
		/* -16      1.164  0      1.793  0 */
		/* -128     1.164 -0.213 -0.534  0 */
		/* -128     1.164  2.115  0      0 */
		vpp_reg_write(VPP_MATRIX_COEF00_01, 0x04A80000);
		vpp_reg_write(VPP_MATRIX_COEF02_10, 0x072C04A8);
		vpp_reg_write(VPP_MATRIX_COEF11_12, 0x1F261DDD);
		vpp_reg_write(VPP_MATRIX_COEF20_21, 0x04A80876);
		vpp_reg_write(VPP_MATRIX_COEF22, 0x0);
		vpp_reg_write(VPP_MATRIX_OFFSET0_1, 0x0);
		vpp_reg_write(VPP_MATRIX_OFFSET2, 0x0);
	}
	vpp_reg_setb(VPP_MATRIX_CLIP, 0, 5, 3);
}


void set_vpp_matrix(int m_select, int *s, int on)
{
	int *m = NULL;
	int size = 0;
	int i;

	pr_info("set_vpp_matrix m_select = %d on = %d\n",m_select,on);

	if (m_select == VPP_MATRIX_OSD) {
		m = osd_matrix_coeff;
		size = MATRIX_5x3_COEF_SIZE;
	} else if (m_select == VPP_MATRIX_POST) {
		m = post_matrix_coeff;
		size = MATRIX_5x3_COEF_SIZE;
	} else if (m_select == VPP_MATRIX_VD1) {
		m = vd1_matrix_coeff;
		size = MATRIX_5x3_COEF_SIZE;
	} else if (m_select == VPP_MATRIX_VD2) {
		m = vd2_matrix_coeff;
		size = MATRIX_5x3_COEF_SIZE;
	} else if (m_select == VPP_MATRIX_XVYCC) {
		m = xvycc_matrix_coeff;
		size = MATRIX_5x3_COEF_SIZE;
	} else if (m_select == VPP_MATRIX_EOTF) {
		m = video_eotf_coeff;
		size = EOTF_COEFF_SIZE;
	} else if (m_select == VPP_MATRIX_OSD_EOTF) {
		m = osd_eotf_coeff;
		size = EOTF_COEFF_SIZE;
	} else
		return;

	if (s)
		for (i = 0; i < size; i++)
			m[i] = s[i];

	if (m_select == VPP_MATRIX_OSD) {
		/* osd matrix, VPP_MATRIX_0 */
		vpp_reg_write(VIU_OSD1_MATRIX_PRE_OFFSET0_1,
			((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
		vpp_reg_write(VIU_OSD1_MATRIX_PRE_OFFSET2,
			m[2] & 0xfff);
		vpp_reg_write(VIU_OSD1_MATRIX_COEF00_01,
			((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
		vpp_reg_write(VIU_OSD1_MATRIX_COEF02_10,
			((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff));
		vpp_reg_write(VIU_OSD1_MATRIX_COEF11_12,
			((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
		vpp_reg_write(VIU_OSD1_MATRIX_COEF20_21,
			((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
		if (m[21]) {
			vpp_reg_write(VIU_OSD1_MATRIX_COEF22_30,
				((m[11] & 0x1fff) << 16) | (m[12] & 0x1fff));
			vpp_reg_write(VIU_OSD1_MATRIX_COEF31_32,
				((m[13] & 0x1fff) << 16) | (m[14] & 0x1fff));
			vpp_reg_write(VIU_OSD1_MATRIX_COEF40_41,
				((m[15] & 0x1fff) << 16) | (m[16] & 0x1fff));
			vpp_reg_write(VIU_OSD1_MATRIX_COLMOD_COEF42,
				m[17] & 0x1fff);
		} else {
			vpp_reg_write(VIU_OSD1_MATRIX_COEF22_30,
				(m[11] & 0x1fff) << 16);
		}
		vpp_reg_write(VIU_OSD1_MATRIX_OFFSET0_1,
			((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
		vpp_reg_write(VIU_OSD1_MATRIX_OFFSET2,
			m[20] & 0xfff);
		vpp_reg_setb(VIU_OSD1_MATRIX_COLMOD_COEF42,
			m[21], 30, 2);
		vpp_reg_setb(VIU_OSD1_MATRIX_COLMOD_COEF42,
			m[22], 16, 3);
		/* 23 reserved for clipping control */
		vpp_reg_setb(VIU_OSD1_MATRIX_CTRL, on, 0, 1);
		vpp_reg_setb(VIU_OSD1_MATRIX_CTRL, 0, 1, 1);
	} else if (m_select == VPP_MATRIX_EOTF) {
		/* eotf matrix, VPP_MATRIX_EOTF */
		for (i = 0; i < 5; i++)
			vpp_reg_write(VIU_EOTF_CTL + i + 1,
				((m[i * 2] & 0x1fff) << 16)
				| (m[i * 2 + 1] & 0x1fff));

		vpp_reg_setb(VIU_EOTF_CTL, on, 30, 1);
		vpp_reg_setb(VIU_EOTF_CTL, on, 31, 1);
	} else if (m_select == VPP_MATRIX_OSD_EOTF) {
		/* osd eotf matrix, VPP_MATRIX_OSD_EOTF */
		for (i = 0; i < 5; i++)
			vpp_reg_write(VIU_OSD1_EOTF_CTL + i + 1,
				((m[i * 2] & 0x1fff) << 16)
				| (m[i * 2 + 1] & 0x1fff));

		vpp_reg_setb(VIU_OSD1_EOTF_CTL, on, 30, 1);
		vpp_reg_setb(VIU_OSD1_EOTF_CTL, on, 31, 1);
	} else {
		/* vd1 matrix, VPP_MATRIX_1 */
		/* post matrix, VPP_MATRIX_2 */
		/* xvycc matrix, VPP_MATRIX_3 */
		/* vd2 matrix, VPP_MATRIX_6 */
		if (m_select == VPP_MATRIX_POST) {
			/* post matrix */
			m = post_matrix_coeff;
			vpp_reg_setb(VPP_MATRIX_CTRL, on, 0, 1);
			vpp_reg_setb(VPP_MATRIX_CTRL, 0, 8, 3);
		} else if (m_select == VPP_MATRIX_VD1) {
			/* vd1 matrix */
			m = vd1_matrix_coeff;
			vpp_reg_setb(VPP_MATRIX_CTRL, on, 5, 1);
			vpp_reg_setb(VPP_MATRIX_CTRL, 1, 8, 3);
		} else if (m_select == VPP_MATRIX_VD2) {
			/* vd2 matrix */
			m = vd2_matrix_coeff;
			vpp_reg_setb(VPP_MATRIX_CTRL, on, 4, 1);
			vpp_reg_setb(VPP_MATRIX_CTRL, 2, 8, 3);
		} else if (m_select == VPP_MATRIX_XVYCC) {
			/* xvycc matrix */
			m = xvycc_matrix_coeff;
			vpp_reg_setb(VPP_MATRIX_CTRL, on, 6, 1);
			vpp_reg_setb(VPP_MATRIX_CTRL, 3, 8, 3);
		}
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET0_1,
			((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
		vpp_reg_write(VPP_MATRIX_PRE_OFFSET2,
			m[2] & 0xfff);
		vpp_reg_write(VPP_MATRIX_COEF00_01,
			((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
		vpp_reg_write(VPP_MATRIX_COEF02_10,
			((m[5]  & 0x1fff) << 16) | (m[6] & 0x1fff));
		vpp_reg_write(VPP_MATRIX_COEF11_12,
			((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
		vpp_reg_write(VPP_MATRIX_COEF20_21,
			((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
		vpp_reg_write(VPP_MATRIX_COEF22,
			m[11] & 0x1fff);
		if (m[21]) {
			vpp_reg_write(VPP_MATRIX_COEF13_14,
				((m[12] & 0x1fff) << 16) | (m[13] & 0x1fff));
			vpp_reg_write(VPP_MATRIX_COEF15_25,
				((m[14] & 0x1fff) << 16) | (m[17] & 0x1fff));
			vpp_reg_write(VPP_MATRIX_COEF23_24,
				((m[15] & 0x1fff) << 16) | (m[16] & 0x1fff));
		}
		vpp_reg_write(VPP_MATRIX_OFFSET0_1,
			((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
		vpp_reg_write(VPP_MATRIX_OFFSET2,
			m[20] & 0xfff);
		vpp_reg_setb(VPP_MATRIX_CLIP,
			m[21], 3, 2);
		vpp_reg_setb(VPP_MATRIX_CLIP,
			m[22], 5, 3);
	}
}

const char lut_name[4][16] = {
	"OSD_EOTF",
	"OSD_OETF",
	"EOTF",
	"OETF",
};

void set_vpp_lut(
	enum vpp_lut_sel_e lut_sel,
	unsigned int *r,
	unsigned int *g,
	unsigned int *b,
	int on)
{
	unsigned int *r_map = NULL;
	unsigned int *g_map = NULL;
	unsigned int *b_map = NULL;
	unsigned int addr_port;
	unsigned int data_port;
	unsigned int ctrl_port;
	int i;

	if (lut_sel == VPP_LUT_OSD_EOTF) {
		r_map = osd_eotf_r_mapping;
		g_map = osd_eotf_g_mapping;
		b_map = osd_eotf_b_mapping;
		addr_port = VIU_OSD1_EOTF_LUT_ADDR_PORT;
		data_port = VIU_OSD1_EOTF_LUT_DATA_PORT;
		ctrl_port = VIU_OSD1_EOTF_CTL;
	} else if (lut_sel == VPP_LUT_EOTF) {
		r_map = video_eotf_r_mapping;
		g_map = video_eotf_g_mapping;
		b_map = video_eotf_b_mapping;
		addr_port = VIU_EOTF_LUT_ADDR_PORT;
		data_port = VIU_EOTF_LUT_DATA_PORT;
		ctrl_port = VIU_EOTF_CTL;
	} else if (lut_sel == VPP_LUT_OSD_OETF) {
		r_map = osd_oetf_r_mapping;
		g_map = osd_oetf_g_mapping;
		b_map = osd_oetf_b_mapping;
		addr_port = VIU_OSD1_OETF_LUT_ADDR_PORT;
		data_port = VIU_OSD1_OETF_LUT_DATA_PORT;
		ctrl_port = VIU_OSD1_OETF_CTL;
	} else if (lut_sel == VPP_LUT_OETF) {
#if 0
		load_knee_lut(on);
		return;
#else
		r_map = video_oetf_r_mapping;
		g_map = video_oetf_g_mapping;
		b_map = video_oetf_b_mapping;
		addr_port = XVYCC_LUT_R_ADDR_PORT;
		data_port = XVYCC_LUT_R_DATA_PORT;
		ctrl_port = XVYCC_LUT_CTL;
#endif
	} else
		return;

	if (lut_sel == VPP_LUT_OSD_OETF) {
		if (r && r_map)
			for (i = 0; i < OSD_OETF_LUT_SIZE; i++)
				r_map[i] = r[i];
		if (g && g_map)
			for (i = 0; i < OSD_OETF_LUT_SIZE; i++)
				g_map[i] = g[i];
		if (r && r_map)
			for (i = 0; i < OSD_OETF_LUT_SIZE; i++)
				b_map[i] = b[i];
		vpp_reg_write(addr_port, 0);
		for (i = 0; i < 20; i++)
			vpp_reg_write(data_port,
				r_map[i * 2]
				| (r_map[i * 2 + 1] << 16));
		vpp_reg_write(data_port,
			r_map[OSD_OETF_LUT_SIZE - 1]
			| (g_map[0] << 16));
		for (i = 0; i < 20; i++)
			vpp_reg_write(data_port,
				g_map[i * 2 + 1]
				| (g_map[i * 2 + 2] << 16));
		for (i = 0; i < 20; i++)
			vpp_reg_write(data_port,
				b_map[i * 2]
				| (b_map[i * 2 + 1] << 16));
		vpp_reg_write(data_port,
			b_map[OSD_OETF_LUT_SIZE - 1]);
		if (on)
			vpp_reg_setb(ctrl_port, 7, 29, 3);
		else
			vpp_reg_setb(ctrl_port, 0, 29, 3);
	} else if ((lut_sel == VPP_LUT_OSD_EOTF) || (lut_sel == VPP_LUT_EOTF)) {
		if (r && r_map)
			for (i = 0; i < EOTF_LUT_SIZE; i++)
				r_map[i] = r[i];
		if (g && g_map)
			for (i = 0; i < EOTF_LUT_SIZE; i++)
				g_map[i] = g[i];
		if (r && r_map)
			for (i = 0; i < EOTF_LUT_SIZE; i++)
				b_map[i] = b[i];
		vpp_reg_write(addr_port, 0);
		for (i = 0; i < 16; i++)
			vpp_reg_write(data_port,
				r_map[i * 2]
				| (r_map[i * 2 + 1] << 16));
		vpp_reg_write(data_port,
			r_map[EOTF_LUT_SIZE - 1]
			| (g_map[0] << 16));
		for (i = 0; i < 16; i++)
			vpp_reg_write(data_port,
				g_map[i * 2 + 1]
				| (g_map[i * 2 + 2] << 16));
		for (i = 0; i < 16; i++)
			vpp_reg_write(data_port,
				b_map[i * 2]
				| (b_map[i * 2 + 1] << 16));
		vpp_reg_write(data_port, b_map[EOTF_LUT_SIZE - 1]);
		if (on)
			vpp_reg_setb(ctrl_port, 7, 27, 3);
		else
			vpp_reg_setb(ctrl_port, 0, 27, 3);
		vpp_reg_setb(ctrl_port, 1, 31, 1);
	} else if (lut_sel == VPP_LUT_OETF) {
		if (r && r_map)
			for (i = 0; i < VIDEO_OETF_LUT_SIZE; i++)
				r_map[i] = r[i];
		if (g && g_map)
			for (i = 0; i < VIDEO_OETF_LUT_SIZE; i++)
				g_map[i] = g[i];
		if (r && r_map)
			for (i = 0; i < VIDEO_OETF_LUT_SIZE; i++)
				b_map[i] = b[i];
		vpp_reg_write(ctrl_port, 0x0);
		vpp_reg_write(addr_port, 0);
		for (i = 0; i < VIDEO_OETF_LUT_SIZE; i++)
			vpp_reg_write(data_port, r_map[i]);
		vpp_reg_write(addr_port + 2, 0);
		for (i = 0; i < VIDEO_OETF_LUT_SIZE; i++)
			vpp_reg_write(data_port + 2, g_map[i]);
		vpp_reg_write(addr_port + 4, 0);
		for (i = 0; i < VIDEO_OETF_LUT_SIZE; i++)
			vpp_reg_write(data_port + 4, b_map[i]);
		if (on)
			vpp_reg_write(ctrl_port, 0x7f);
		else
			vpp_reg_write(ctrl_port, 0x0);
	}
}

 /*
for G12A, set osd2 matrix(10bit) RGB2YUV
 */
 static void set_osd1_rgb2yuv(bool on)
 {
	int *m = NULL;

	if (is_osd_high_version()) {
		/* RGB -> 709 limit */
		m = RGB709_to_YUV709l_coeff;

		/* VPP WRAP OSD1 matrix */
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_PRE_OFFSET0_1,
			((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_PRE_OFFSET2,
			m[2] & 0xfff);
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_COEF00_01,
			((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_COEF02_10,
			((m[5]  & 0x1fff) << 16) | (m[6] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_COEF11_12,
			((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_COEF20_21,
			((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_COEF22,
			m[11] & 0x1fff);

		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_OFFSET0_1,
			((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
		vpp_reg_write(VPP_WRAP_OSD1_MATRIX_OFFSET2,
			m[20] & 0xfff);

		vpp_reg_setb(VPP_WRAP_OSD1_MATRIX_EN_CTRL, on, 0, 1);

		VPP_PR("%s rgb2yuv on = %d..............\n", __func__, on);
	} else {
		vpp_reg_setb(VIU_OSD1_BLK0_CFG_W0, 0, 7, 1);
		/* eotf lut bypass */
		set_vpp_lut(VPP_LUT_OSD_EOTF,
			eotf_33_linear_mapping, /* R */
			eotf_33_linear_mapping, /* G */
			eotf_33_linear_mapping, /* B */
			CSC_OFF);
		/* eotf matrix bypass */
		set_vpp_matrix(VPP_MATRIX_OSD_EOTF,
			eotf_bypass_coeff,
			CSC_OFF);
		/* oetf lut bypass */
		set_vpp_lut(VPP_LUT_OSD_OETF,
			oetf_41_linear_mapping, /* R */
			oetf_41_linear_mapping, /* G */
			oetf_41_linear_mapping, /* B */
			CSC_OFF);
		/* osd matrix RGB709 to YUV709 limit */
		set_vpp_matrix(VPP_MATRIX_OSD,
			RGB709_to_YUV709l_coeff,
			CSC_ON);
	}
 }

 /*
for G12A, set osd2 matrix(10bit) RGB2YUV
 */
static void set_osd2_rgb2yuv(bool on)
{
	int *m = NULL;

	if (is_osd_high_version()) {
		/* RGB -> 709 limit */
		m = RGB709_to_YUV709l_coeff;

		/* VPP WRAP OSD2 matrix */
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_PRE_OFFSET0_1,
			((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_PRE_OFFSET2,
			m[2] & 0xfff);
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_COEF00_01,
			((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_COEF02_10,
			((m[5]  & 0x1fff) << 16) | (m[6] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_COEF11_12,
			((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_COEF20_21,
			((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_COEF22,
			m[11] & 0x1fff);

		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_OFFSET0_1,
			((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
		vpp_reg_write(VPP_WRAP_OSD2_MATRIX_OFFSET2,
			m[20] & 0xfff);

		vpp_reg_setb(VPP_WRAP_OSD2_MATRIX_EN_CTRL, on, 0, 1);

		VPP_PR("%s rgb2yuv on = %d..............\n", __func__, on);
	}
}

 /*
for G12A, set osd3 matrix(10bit) RGB2YUV
 */
static void set_osd3_rgb2yuv(bool on)
{
	int *m = NULL;

	if (is_osd_high_version()) {
		/* RGB -> 709 limit */
		m = RGB709_to_YUV709l_coeff;

		/* VPP WRAP OSD3 matrix */
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_PRE_OFFSET0_1,
			((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_PRE_OFFSET2,
			m[2] & 0xfff);
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_COEF00_01,
			((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_COEF02_10,
			((m[5]  & 0x1fff) << 16) | (m[6] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_COEF11_12,
			((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_COEF20_21,
			((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_COEF22,
			m[11] & 0x1fff);

		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_OFFSET0_1,
			((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
		vpp_reg_write(VPP_WRAP_OSD3_MATRIX_OFFSET2,
			m[20] & 0xfff);

		vpp_reg_setb(VPP_WRAP_OSD3_MATRIX_EN_CTRL, on, 0, 1);

		VPP_PR("%s rgb2yuv on = %d..............\n", __func__, on);
	}
}

 /*
for T7, set osd4 matrix(10bit) RGB2YUV
 */
static void set_osd4_rgb2yuv(bool on)
{
	int *m = NULL;

	if (is_osd_high_version()) {
		/* RGB -> 709 limit */
		m = RGB709_to_YUV709l_coeff;

		/* VPP WRAP OSD3 matrix */
		vpp_reg_write(VIU_OSD4_MATRIX_PRE_OFFSET0_1,
			((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
		vpp_reg_write(VIU_OSD4_MATRIX_PRE_OFFSET2,
			m[2] & 0xfff);
		vpp_reg_write(VIU_OSD4_MATRIX_COEF00_01,
			((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
		vpp_reg_write(VIU_OSD4_MATRIX_COEF02_10,
			((m[5]  & 0x1fff) << 16) | (m[6] & 0x1fff));
		vpp_reg_write(VIU_OSD4_MATRIX_COEF11_12,
			((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
		vpp_reg_write(VIU_OSD4_MATRIX_COEF20_21,
			((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
		vpp_reg_write(VIU_OSD4_MATRIX_COEF22,
			m[11] & 0x1fff);

		vpp_reg_write(VIU_OSD4_MATRIX_OFFSET0_1,
			((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
		vpp_reg_write(VIU_OSD4_MATRIX_OFFSET2,
			m[20] & 0xfff);

		vpp_reg_setb(VIU_OSD4_MATRIX_EN_CTRL, on, 0, 1);

		VPP_PR("T7 osd4 matrix rgb2yuv..............\n");
	}
}

#ifndef AML_T7_DISPLAY
static void set_viu2_osd_matrix_rgb2yuv(bool on)
{
	int *m = RGB709_to_YUV709l_coeff;

	/* RGB -> 709 limit */
	if (is_osd_high_version()) {
		/* VPP WRAP OSD3 matrix */
		vpp_reg_write(VIU2_OSD1_MATRIX_PRE_OFFSET0_1,
			      ((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
		vpp_reg_write(VIU2_OSD1_MATRIX_PRE_OFFSET2,
			      m[2] & 0xfff);
		vpp_reg_write(VIU2_OSD1_MATRIX_COEF00_01,
			      ((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
		vpp_reg_write(VIU2_OSD1_MATRIX_COEF02_10,
			      ((m[5]  & 0x1fff) << 16) | (m[6] & 0x1fff));
		vpp_reg_write(VIU2_OSD1_MATRIX_COEF11_12,
			      ((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
		vpp_reg_write(VIU2_OSD1_MATRIX_COEF20_21,
			      ((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
		vpp_reg_write(VIU2_OSD1_MATRIX_COEF22,
			      m[11] & 0x1fff);

		vpp_reg_write(VIU2_OSD1_MATRIX_OFFSET0_1,
			      ((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
		vpp_reg_write(VIU2_OSD1_MATRIX_OFFSET2,
			      m[20] & 0xfff);

		vpp_reg_setb(VIU2_OSD1_MATRIX_EN_CTRL, on, 0, 1);
	}
}
#endif

static void set_vpp_osd2_rgb2yuv(bool on)
{
	int *m = NULL;

	/* RGB -> 709 limit */
	m = RGB709_to_YUV709l_coeff;

	/* VPP WRAP OSD3 matrix */
	vpp_reg_write(VPP_OSD2_MATRIX_PRE_OFFSET0_1,
		      ((m[0] & 0xfff) << 16) | (m[1] & 0xfff));
	vpp_reg_write(VPP_OSD2_MATRIX_PRE_OFFSET2,
		      m[2] & 0xfff);
	vpp_reg_write(VPP_OSD2_MATRIX_COEF00_01,
		      ((m[3] & 0x1fff) << 16) | (m[4] & 0x1fff));
	vpp_reg_write(VPP_OSD2_MATRIX_COEF02_10,
		      ((m[5] & 0x1fff) << 16) | (m[6] & 0x1fff));
	vpp_reg_write(VPP_OSD2_MATRIX_COEF11_12,
		      ((m[7] & 0x1fff) << 16) | (m[8] & 0x1fff));
	vpp_reg_write(VPP_OSD2_MATRIX_COEF20_21,
		      ((m[9] & 0x1fff) << 16) | (m[10] & 0x1fff));
	vpp_reg_write(VPP_OSD2_MATRIX_COEF22,
		      m[11] & 0x1fff);
	vpp_reg_write(VPP_OSD2_MATRIX_OFFSET0_1,
		      ((m[18] & 0xfff) << 16) | (m[19] & 0xfff));
	vpp_reg_write(VPP_OSD2_MATRIX_OFFSET2,
		      m[20] & 0xfff);
	vpp_reg_setb(VPP_OSD2_MATRIX_EN_CTRL, on, 0, 1);
	VPP_PR("vpp osd2 matrix rgb2yuv..............\n");
}

/*
for txlx, set vpp default data path to u10
 */
static void set_vpp_bitdepth(void)
{
	u32 chip_id = get_cpu_id().family_id;

	if (is_osd_high_version()) {
		/*after this step vd1 output data is U12,*/
		if (chip_id == MESON_CPU_MAJOR_ID_T7) {
			/* osd dolby bypass en */
			vpp_reg_setb(MALI_AFBCD_TOP_CTRL, 1, 14, 1);
			vpp_reg_setb(MALI_AFBCD_TOP_CTRL, 1, 19, 1);
			/* osd_din_ext 12bit */
			vpp_reg_setb(MALI_AFBCD_TOP_CTRL, 0, 15, 1);
			vpp_reg_setb(MALI_AFBCD_TOP_CTRL, 0, 20, 1);

			vpp_reg_setb(MALI_AFBCD1_TOP_CTRL, 1, 19, 1);
			vpp_reg_setb(MALI_AFBCD1_TOP_CTRL, 0, 20, 1);

			vpp_reg_setb(MALI_AFBCD2_TOP_CTRL, 1, 19, 1);
			vpp_reg_setb(MALI_AFBCD2_TOP_CTRL, 0, 20, 1);
		} else {
			vpp_reg_write(DOLBY_PATH_CTRL, 0xf);
		}
	}
}

/* osd+video brightness */
static void video_adj2_brightness(int val)
{
	if (val < -255)
		val = -255;
	else if (val > 255)
		val = 255;

	VPP_PR("brightness_post:%d\n", val);

	vpp_reg_setb(VPP_VADJ2_Y, val << 1, 8, 10);

	vpp_reg_setb(VPP_VADJ_CTRL, 1, 2, 1);
}

/* osd+video contrast */
static void video_adj2_contrast(int val)
{
	if (val < -127)
		val = -127;
	else if (val > 127)
		val = 127;

	VPP_PR("contrast_post:%d\n", val);

	val += 0x80;

	vpp_reg_setb(VPP_VADJ2_Y, val, 0, 8);
	vpp_reg_setb(VPP_VADJ_CTRL, 1, 2, 1);
}

/* osd+video saturation/hue */
static void amvecm_saturation_hue_post(int sat, int hue)
{
	int hue_post;  /*-25~25*/
	int saturation_post;  /*-128~127*/
	int i, ma, mb, mab, mc, md;
	int hue_cos[] = {
		/*0~12*/
		256, 256, 256, 255, 255, 254, 253, 252, 251, 250,
		248, 247, 245, 243, 241, 239, 237, 234, 231, 229,
		226, 223, 220, 216, 213, 209  /*13~25*/
	};
	int hue_sin[] = {
		-147, -142, -137, -132, -126, -121, -115, -109, -104,
		-98, -92, -86, -80, /*-25~-13*/-74,  -68,  -62,  -56,
		-50,  -44,  -38,  -31,  -25, -19, -13,  -6, /*-12~-1*/
		0, /*0*/
		6,   13,   19,	25,   31,   38,   44,	50,   56,
		62,	68,  74,      /*1~12*/	80,   86,   92,	98,  104,
		109,  115,  121,  126,  132, 137, 142, 147 /*13~25*/
	};

	if (sat < -128)
		sat = -128;
	else if (sat > 128)
		sat = 128;

	if (hue < -25)
		hue = -25;
	else if (hue > 25)
		hue = 25;

	VPP_PR("saturation sat_post:%d hue_post:%d\n", sat, hue);

	saturation_post = sat;
	hue_post = hue;
	i = (hue_post > 0) ? hue_post : -hue_post;
	ma = (hue_cos[i]*(saturation_post + 128)) >> 7;
	mb = (hue_sin[25+hue_post]*(saturation_post + 128)) >> 7;
	if (ma > 511)
		ma = 511;
	if (ma < -512)
		ma = -512;
	if (mb > 511)
		mb = 511;
	if (mb < -512)
		mb = -512;
	mab =  ((ma & 0x3ff) << 16) | (mb & 0x3ff);

	vpp_reg_write(VPP_VADJ2_MA_MB, mab);
	mc = (s16)((mab<<22)>>22); /* mc = -mb */
	mc = 0 - mc;
	if (mc > 511)
		mc = 511;
	if (mc < -512)
		mc = -512;
	md = (s16)((mab<<6)>>22);  /* md =	ma; */
	mab = ((mc&0x3ff)<<16)|(md&0x3ff);

	vpp_reg_write(VPP_VADJ2_MC_MD, mab);
	vpp_reg_setb(VPP_VADJ_CTRL, 1, 2, 1);
}

/* init osd+video brightness/contrast/saturaion/hue */
void vpp_pq_init(int brightness, int contrast, int sat, int hue)
{
	video_adj2_brightness(brightness);
	video_adj2_contrast(contrast);
	amvecm_saturation_hue_post(sat, hue);
}

void vpp_pq_load(void)
{
	int i = 0, cnt = 0;
	char const *pq = env_get("pq");
	char *tk, *str, *tmp[4];
	short val[4];

	if (pq == NULL) {
		VPP_PR("%s pq val error !!!\n", __func__);
		return;
	}

	str = strdup(pq);

	for (tk = strsep(&str, ","); tk != NULL; tk = strsep(&str, ",")) {
		tmp[cnt] = tk;
		if (cnt++ > 4)
			break;
	}

	if (cnt == 4) {
		for (i = 0; i < 4; i++) {
			val[i] = simple_strtol(tmp[i], NULL, 10);
			/* VPP_PR("pq[%d]: %d\n", i, val[i]); */
		}
		vpp_pq_init(val[0], val[1], val[2], val[3]);
	}
}

void vpp_load_gamma_table(unsigned short *data, unsigned int len, enum vpp_gamma_sel_e flag)
{
	unsigned short *table = NULL;
	unsigned int i;

	switch (flag) {
	case VPP_GAMMA_R:
		table = gamma_table_r;
		break;
	case VPP_GAMMA_G:
		table = gamma_table_g;
		break;
	case VPP_GAMMA_B:
		table = gamma_table_b;
		break;
	default:
		break;
	}
	if (table == NULL) {
		VPP_PR("error: %s: invalid flag: %d\n", __func__, flag);
		return;
	}
	if (len != GAMMA_SIZE) {
		VPP_PR("error: %s: invalid len: %d\n", __func__, len);
		return;
	}

	for (i = 0; i < GAMMA_SIZE; i++)
		table[i] = data[i];
	VPP_PR("%s: successful\n", __func__);
}

void vpp_enable_lcd_gamma_table(int index)
{
	unsigned int reg;

	if (get_cpu_id().family_id >= MESON_CPU_MAJOR_ID_T7) {
		switch (index) {
		case 1:
			reg = LCD_GAMMA_CNTL_PORT0 + 0x100;
			break;
		case 2:
			reg = LCD_GAMMA_CNTL_PORT0 + 0x200;
			break;
		case 0:
		default:
			reg = LCD_GAMMA_CNTL_PORT0;
			break;
		}
	} else {
		reg = L_GAMMA_CNTL_PORT;
	}

	vpp_reg_setb(reg, 1, GAMMA_EN, 1);
}

void vpp_disable_lcd_gamma_table(int index)
{
	unsigned int reg;

	if (get_cpu_id().family_id >= MESON_CPU_MAJOR_ID_T7) {
		switch (index) {
		case 1:
			reg = LCD_GAMMA_CNTL_PORT0 + 0x100;
			break;
		case 2:
			reg = LCD_GAMMA_CNTL_PORT0 + 0x200;
			break;
		case 0:
		default:
			reg = LCD_GAMMA_CNTL_PORT0;
			break;
		}
	} else {
		reg = L_GAMMA_CNTL_PORT;
	}
	vpp_reg_setb(reg, 0, GAMMA_EN, 1);
}

#define GAMMA_RETRY        1000
static void vpp_set_lcd_gamma_table(int index, u16 *data, u32 rgb_mask)
{
	unsigned int reg_encl_en, reg_cntl_port, reg_data_port, reg_addr_port;
	int i;
	int cnt = 0;

	if (get_cpu_id().family_id >= MESON_CPU_MAJOR_ID_T7) {
		switch (index) {
		case 1:
			reg_encl_en = ENCL_VIDEO_EN + 0x600;
			reg_cntl_port = LCD_GAMMA_CNTL_PORT0 + 0x100;
			reg_data_port = LCD_GAMMA_DATA_PORT0 + 0x100;
			reg_addr_port = LCD_GAMMA_ADDR_PORT0 + 0x100;
			break;
		case 2:
			reg_encl_en = ENCL_VIDEO_EN + 0x800;
			reg_cntl_port = LCD_GAMMA_CNTL_PORT0 + 0x200;
			reg_data_port = LCD_GAMMA_DATA_PORT0 + 0x200;
			reg_addr_port = LCD_GAMMA_ADDR_PORT0 + 0x200;
			break;
		case 0:
		default:
			reg_encl_en = ENCL_VIDEO_EN;
			reg_cntl_port = LCD_GAMMA_CNTL_PORT0;
			reg_data_port = LCD_GAMMA_DATA_PORT0;
			reg_addr_port = LCD_GAMMA_ADDR_PORT0;
			break;
		}
	} else {
		reg_encl_en = ENCL_VIDEO_EN;
		reg_cntl_port = L_GAMMA_CNTL_PORT;
		reg_data_port = L_GAMMA_DATA_PORT;
		reg_addr_port = L_GAMMA_ADDR_PORT;
	}

	if (get_cpu_id().family_id >= MESON_CPU_MAJOR_ID_T7) {
		vpp_reg_write(reg_addr_port, (1 << 8));
		for (i = 0; i < 256; i++)
			vpp_reg_write(reg_data_port,
				(data[i] << 20) |
				(data[i] << 10) |
				(data[i] << 0));
		return;
	}

	if (!(vpp_reg_read(reg_encl_en) & 0x1))
		return;

	vpp_reg_setb(reg_cntl_port, 0, GAMMA_EN, 1);

	while (!(vpp_reg_read(reg_cntl_port) & (0x1 << ADR_RDY))) {
		udelay(10);
		if (cnt++ > GAMMA_RETRY)
			break;
	}
	cnt = 0;
	vpp_reg_write(reg_addr_port, (0x1 << H_AUTO_INC) |
				    (0x1 << rgb_mask)   |
				    (0x0 << HADR));
	for (i = 0; i < 256; i++) {
		while (!(vpp_reg_read(reg_cntl_port) & (0x1 << WR_RDY))) {
			udelay(10);
			if (cnt++ > GAMMA_RETRY)
				break;
		}
		cnt = 0;
		vpp_reg_write(reg_data_port, data[i]);
	}
	while (!(vpp_reg_read(reg_cntl_port) & (0x1 << ADR_RDY))) {
		udelay(10);
		if (cnt++ > GAMMA_RETRY)
			break;
	}
	vpp_reg_write(reg_addr_port, (0x1 << H_AUTO_INC) |
				    (0x1 << rgb_mask)   |
				    (0x23 << HADR));

}

void vpp_init_lcd_gamma_table(int index)
{
	VPP_PR("%s\n", __func__);

	vpp_disable_lcd_gamma_table(index);

	vpp_set_lcd_gamma_table(index, gamma_table_r, H_SEL_R);
	vpp_set_lcd_gamma_table(index, gamma_table_g, H_SEL_G);
	vpp_set_lcd_gamma_table(index, gamma_table_b, H_SEL_B);

	vpp_enable_lcd_gamma_table(index);
}

void vpp_matrix_update(int type)
{
	if (vpp_init_flag == 0)
		return;

	VPP_PR("%s: %d\n", __func__, type);

	switch (type) {
	case VPP_CM_RGB:
		/* 709 limit to RGB */
		vpp_set_matrix_ycbcr2rgb(2, 3);
		break;
	case VPP_CM_YUV:
		break;
	default:
		break;
	}
}

void vpp_viu2_matrix_update(int type)
{
	if (vpp_init_flag == 0)
		return;

	if (get_cpu_id().family_id < MESON_CPU_MAJOR_ID_G12A)
		return;

	VPP_PR("%s: %d\n", __func__, type);

	switch (type) {
	case VPP_CM_RGB:
		/* default RGB */
		#ifndef AML_T7_DISPLAY
		set_viu2_osd_matrix_rgb2yuv(0);
		#else
		/* vpp_top1: yuv2rgb */
		vpp_top_post2_matrix_yuv2rgb(1);
		#endif
		break;
	case VPP_CM_YUV:
		/* RGB to 709 limit */
		#ifndef AML_T7_DISPLAY
		set_viu2_osd_matrix_rgb2yuv(1);
		#endif
		break;
	default:
		break;
	}
}

static void vpp_ofifo_init(void)
{
	unsigned int data32;

	data32 = vpp_reg_read(VPP_OFIFO_SIZE);
	data32 |= 0xfff;
	vpp_reg_write(VPP_OFIFO_SIZE, data32);

	data32 = 0x08080808;
	vpp_reg_write(VPP_HOLD_LINES, data32);
}

#ifdef CONFIG_AML_HDMITX
static void amvecm_cp_hdr_info(struct master_display_info_s *hdr_data)
{
	int i, j;

	hdr_data->features =
		(0 << 30) /*sdr output 709*/
		| (1 << 29)	/*video available*/
		| (5 << 26)	/* unspecified */
		| (0 << 25)	/* limit */
		| (1 << 24)	/* color available */
		| (9 << 16)	/* bt2020 */
		| (16 << 8)	/* bt2020-10 */
		| (10 << 0);	/* bt2020c */

	for (i = 0; i < 3; i++)
		for (j = 0; j < 2; j++)
			hdr_data->primaries[i][j] =
					bt2020_primaries[i][j];
	hdr_data->white_point[0] = bt2020_white_point[0];
	hdr_data->white_point[1] = bt2020_white_point[1];
	/* default luminance */
	hdr_data->luminance[0] = 1000 * 10000;
	hdr_data->luminance[1] = 50;

	/* content_light_level */
	hdr_data->max_content = 0;
	hdr_data->max_frame_average = 0;
	hdr_data->luminance[0] = hdr_data->luminance[0] / 10000;
	hdr_data->present_flag = 1;
}
#endif

void hdr_tx_pkt_cb(void)
{
	int hdr_policy = 0;
#ifdef CONFIG_AML_HDMITX
	struct master_display_info_s hdr_data;
	struct hdr_info *hdrinfo = NULL;
#endif
	const char *hdr_policy_env = env_get("hdr_policy");

	if (!hdr_policy_env)
		return;

	hdr_policy = simple_strtoul(hdr_policy_env, NULL, 10);
#ifdef CONFIG_AML_HDMITX
	hdrinfo = hdmitx_get_rx_hdr_info();

	if ((hdrinfo && hdrinfo->hdr_sup_eotf_smpte_st_2084) &&
		hdr_policy == 0) {
		if (is_hdmi_mode(env_get("outputmode"))) {
			hdr_func(OSD1_HDR, SDR_HDR);
			hdr_func(OSD2_HDR, SDR_HDR);
			hdr_func(VD1_HDR, SDR_HDR);
		}
		if (is_hdmi_mode(env_get("outputmode2")))
			hdr_func(OSD3_HDR, SDR_HDR);
		amvecm_cp_hdr_info(&hdr_data);
		hdmitx_set_drm_pkt(&hdr_data);
	}
#endif

	VPP_PR("hdr_policy = %d\n", hdr_policy);
#ifdef CONFIG_AML_HDMITX
	if (hdrinfo)
		VPP_PR("Rx hdr_info.hdr_sup_eotf_smpte_st_2084 = %d\n",
		       hdrinfo->hdr_sup_eotf_smpte_st_2084);
#endif
}

static bool is_vpp_supported(int chip_id)
{
	if ((chip_id == MESON_CPU_MAJOR_ID_A1) ||
		(chip_id == MESON_CPU_MAJOR_ID_C1) ||
		(chip_id == MESON_CPU_MAJOR_ID_C2))
		return false;
	else
		return true;
}

void vpp_init(void)
{
	int chip_id;

	chip_id = vpp_get_chip_type();
	VPP_PR("%s, chip_id=%d\n", __func__, chip_id);
	if (!is_vpp_supported(chip_id)) {
		VPP_PR("%s, vpp not supported\n", __func__);
		return;
	}
	vpp_init_flag = 1;

	/* init vpu fifo control register */
	vpp_ofifo_init();

	vpp_set_matrix_default_init();

	if (is_osd_high_version()) {
		/* >= g12a: osd out is rgb */
		set_osd1_rgb2yuv(0);
		set_osd2_rgb2yuv(0);
		if (chip_id != MESON_CPU_MAJOR_ID_TL1 ||
		    chip_id != MESON_CPU_MAJOR_ID_S4)
			set_osd3_rgb2yuv(0);

		if (chip_id != MESON_CPU_MAJOR_ID_T7)
			set_vpp_osd2_rgb2yuv(1);
		else
			set_osd4_rgb2yuv(0);
		/* set vpp data path to u12 */
		set_vpp_bitdepth();
		hdr_func(OSD1_HDR, HDR_BYPASS);
		hdr_func(OSD2_HDR, HDR_BYPASS);
		hdr_func(OSD3_HDR, HDR_BYPASS);
		hdr_func(VD1_HDR, HDR_BYPASS);
		hdr_func(VD2_HDR, HDR_BYPASS);
	} else {
		/* set dummy data default YUV black */
		vpp_reg_write(VPP_DUMMY_DATA1, 0x108080);
		/* osd1: rgb->yuv limit , osd2: yuv limit */
		set_osd1_rgb2yuv(1);
	}
}
