/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <amlogic/media/vout/hdmitx21/hdmitx_module.h>

const static struct hdmi_timing hdmi_timing_all[] = {
	{HDMI_1_640x480p60_4x3, "640x480p60hz", NULL, 1, 31469, 59940, 25175,
		800, 160, 16, 96, 48, 640, 525, 45, 10, 2, 33, 480, 1, 0, 0, 4, 3, 1, 1},
	{HDMI_2_720x480p60_4x3, "720x480p60hz", NULL, 1, 31469, 59940, 27000,
		858, 138, 16, 62, 60, 720, 525, 45, 9, 6, 30, 480, 7, 0, 0, 4, 3, 8, 9},
	{HDMI_3_720x480p60_16x9, "720x480p60hz", "480p60hz", 1, 31469, 59940, 27000,
		858, 138, 16, 62, 60, 720, 525, 45, 9, 6, 30, 480, 7, 0, 0, 16, 9, 32, 27},
	{HDMI_4_1280x720p60_16x9, "1280x720p60hz", "720p60hz", 1, 45000, 60000, 74250,
		1650, 370, 110, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_5_1920x1080i60_16x9, "1920x1080i60hz", "1080i60hz", 0, 33750, 60000, 74250,
		2200, 280, 88, 44, 148, 1920, 1125, 22, 2, 5, 15, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_6_720x480i60_4x3, "720x480i60hz", NULL, 0, 15734, 59940, 27000,
		1716, 276, 38, 124, 114, 1440, 525, 22, 4, 3, 15, 480, 4, 0, 0, 4, 3, 8, 9},
	{HDMI_7_720x480i60_16x9, "720x480i60hz", "480i60hz", 0, 15734, 59940, 27000,
		1716, 276, 38, 124, 114, 1440, 525, 22, 4, 3, 15, 480, 4, 0, 0, 16, 9, 32, 27},
	{HDMI_8_720x240p60_4x3, "720x240p60hz", NULL, 1, 15734, 59826, 27000,
		1716, 276, 38, 124, 114, 1440, 263, 23, 5, 3, 15, 240, 4, 0, 0, 4, 3, 4, 9},
	{HDMI_9_720x240p60_16x9, "720x240p60hz", NULL, 1, 15734, 59826, 27000,
		1716, 276, 38, 124, 114, 1440, 263, 23, 5, 3, 15, 240, 4, 0, 0, 16, 9, 16, 27},
	{HDMI_10_2880x480i60_4x3, "2880x480i60hz", NULL, 0, 15734, 59940, 54000,
		3432, 552, 76, 248, 228, 2880, 525, 22, 4, 3, 15, 480, 4, 0, 0, 4, 3, 2, 9},
	{HDMI_11_2880x480i60_16x9, "2880x480i60hz", NULL, 0, 15734, 59940, 54000,
		3432, 552, 76, 248, 228, 2880, 525, 22, 4, 3, 15, 480, 4, 0, 0, 16, 9, 8, 27},
	{HDMI_12_2880x240p60_4x3, "2880x240p60hz", NULL, 1, 15734, 59826, 54000,
		3432, 552, 76, 248, 228, 2880, 263, 23, 5, 3, 15, 240, 4, 0, 0, 4, 3, 1, 9},
	{HDMI_13_2880x240p60_16x9, "2880x240p60hz", NULL, 1, 15734, 59826, 54000,
		3432, 552, 76, 248, 228, 2880, 263, 23, 5, 3, 15, 240, 4, 0, 0, 16, 9, 4, 27},
	{HDMI_14_1440x480p60_4x3, "1440x480p60hz", NULL, 1, 31469, 59940, 54000,
		1716, 276, 32, 124, 120, 1440, 525, 45, 9, 6, 30, 480, 7, 0, 0, 4, 3, 4, 9},
	{HDMI_15_1440x480p60_16x9, "1440x480p60hz", NULL, 1, 31469, 59940, 54000,
		1716, 276, 32, 124, 120, 1440, 525, 45, 9, 6, 30, 480, 7, 0, 0, 16, 9, 16, 27},
	{HDMI_16_1920x1080p60_16x9, "1920x1080p60hz", "1080p60hz", 1, 67500, 60000, 148500,
		2200, 280, 88, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_17_720x576p50_4x3, "720x576p50hz", NULL, 1, 31250, 50000, 27000,
		864, 144, 12, 64, 68, 720, 625, 49, 5, 5, 39, 576, 1, 0, 0, 4, 3, 16, 15},
	{HDMI_18_720x576p50_16x9, "720x576p50hz", "576p50hz", 1, 31250, 50000, 27000,
		864, 144, 12, 64, 68, 720, 625, 49, 5, 5, 39, 576, 1, 0, 0, 16, 9, 64, 65},
	{HDMI_19_1280x720p50_16x9, "1280x720p50hz", "720p50hz", 1, 37500, 50000, 74250,
		1980, 700, 440, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_20_1920x1080i50_16x9, "1920x1080i50hz", "1080i50hz", 0, 28125, 50000, 74250,
		2640, 720, 528, 44, 148, 1920, 1125, 22, 2, 5, 15, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_21_720x576i50_4x3, "720x576i50hz", NULL, 0, 15625, 50000, 27000,
		1728, 288, 24, 126, 138, 1440, 625, 24, 2, 3, 19, 576, 1, 0, 0, 4, 3, 16, 15},
	{HDMI_22_720x576i50_16x9, "720x576i50hz", "576i50hz", 0, 15625, 50000, 27000,
		1728, 288, 24, 126, 138, 1440, 625, 24, 2, 3, 19, 576, 1, 0, 0, 16, 9, 64, 65},
	{HDMI_23_720x288p_4x3, "720x288p50hz", NULL, 1, 15625, 49761, 27000,
		1728, 288, 24, 126, 138, 1440, 314, 26, 4, 3, 19, 288, 1, 0, 0, 4, 3, 8, 15},
	{HDMI_24_720x288p_16x9, "720x288p50hz", NULL, 1, 15625, 49761, 27000,
		1728, 288, 24, 126, 138, 1440, 314, 26, 4, 3, 19, 288, 1, 0, 0, 16, 9, 32, 45},
	{HDMI_25_2880x576i50_4x3, "2880x576i50hz", NULL, 0, 15625, 50000, 54000,
		3456, 576, 48, 252, 276, 2880, 625, 24, 2, 3, 19, 576, 1, 0, 0, 4, 3, 2, 15},
	{HDMI_26_2880x576i50_16x9, "2880x576i50hz", NULL, 0, 15625, 50000, 54000,
		3456, 576, 48, 252, 276, 2880, 625, 24, 2, 3, 19, 576, 1, 0, 0, 16, 9, 16, 45},
	{HDMI_27_2880x288p50_4x3, "2880x288p50hz", NULL, 1, 15625, 49761, 54000,
		3456, 576, 48, 252, 276, 2880, 314, 26, 4, 3, 19, 288, 1, 0, 0, 4, 3, 1, 15},
	{HDMI_28_2880x288p50_16x9, "2880x288p50hz", NULL, 1, 15625, 49761, 54000,
		3456, 576, 48, 252, 276, 2880, 314, 26, 4, 3, 19, 288, 1, 0, 0, 16, 9, 8, 45},
	{HDMI_29_1440x576p_4x3, "1440x576p50hz", NULL, 1, 31250, 50000, 54000,
		1728, 288, 24, 128, 136, 1440, 625, 49, 5, 5, 39, 576, 1, 0, 0, 4, 3, 8, 15},
	{HDMI_30_1440x576p_16x9, "1440x576p50hz", NULL, 1, 31250, 50000, 54000,
		1728, 288, 24, 128, 136, 1440, 625, 49, 5, 5, 39, 576, 1, 0, 0, 16, 9, 32, 45},
	{HDMI_31_1920x1080p50_16x9, "1920x1080p50hz", "1080p50hz", 1, 56250, 50000, 148500,
		2640, 720, 528, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_32_1920x1080p24_16x9, "1920x1080p24hz", "1080p24hz", 1, 27000, 24000, 74250,
		2750, 830, 638, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_33_1920x1080p25_16x9, "1920x1080p25hz", "1080p25hz", 1, 28125, 25000, 74250,
		2640, 720, 528, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_34_1920x1080p30_16x9, "1920x1080p30hz", "1080p30hz", 1, 33750, 30000, 74250,
		2200, 280, 88, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_35_2880x480p60_4x3, "2880x480p60hz", NULL, 1, 31469, 59940, 108000,
		3432, 552, 64, 248, 240, 2880, 525, 45, 9, 6, 30, 480, 7, 0, 0, 4, 3, 2, 9},
	{HDMI_36_2880x480p60_16x9, "2880x480p60hz", NULL, 1, 31469, 59940, 108000,
		3432, 552, 64, 248, 240, 2880, 525, 45, 9, 6, 30, 480, 7, 0, 0, 16, 9, 8, 27},
	{HDMI_37_2880x576p50_4x3, "2880x576p50hz", NULL, 1, 31250, 50000, 108000,
		3456, 576, 48, 256, 272, 2880, 625, 49, 5, 5, 39, 576, 1, 0, 0, 4, 3, 4, 15},
	{HDMI_38_2880x576p50_16x9, "2880x576p50hz", NULL, 1, 31250, 50000, 108000,
		3456, 576, 48, 256, 272, 2880, 625, 49, 5, 5, 39, 576, 1, 0, 0, 16, 9, 16, 45},
	{HDMI_39_1920x1080i_t1250_50_16x9, "1920x1080i50hz", NULL, 0, 31250, 50000, 72000,
		2304, 384, 32, 168, 184, 1920, 1250, 85, 23, 5, 57, 1080, 1, 1, 0, 16, 9, 1, 1},
	{HDMI_40_1920x1080i100_16x9, "1920x1080i100hz", NULL, 0, 56250, 100000, 148500,
		2640, 720, 528, 44, 148, 1920, 1125, 22, 2, 5, 15, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_41_1280x720p100_16x9, "1280x720p100hz", NULL, 1, 75000, 100000, 148500,
		1980, 700, 440, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_42_720x576p100_4x3, "720x576p100hz", NULL, 1, 62500, 100000, 54000,
		864, 144, 12, 64, 68, 720, 625, 49, 5, 5, 39, 576, 1, 0, 0, 4, 3, 16, 15},
	{HDMI_43_720x576p100_16x9, "720x576p100hz", NULL, 1, 62500, 100000, 54000,
		864, 144, 12, 64, 68, 720, 625, 49, 5, 5, 39, 576, 1, 0, 0, 16, 9, 64, 45},
	{HDMI_44_720x576i100_4x3, "720x576i100hz", NULL, 0, 31250, 100000, 54000,
		1728, 288, 24, 126, 138, 1440, 625, 24, 2, 3, 19, 576, 1, 0, 0, 4, 3, 16, 15},
	{HDMI_45_720x576i100_16x9, "720x576i100hz", NULL, 0, 31250, 100000, 54000,
		1728, 288, 24, 126, 138, 1440, 625, 24, 2, 3, 19, 576, 1, 0, 0, 16, 9, 64, 45},
	{HDMI_46_1920x1080i120_16x9, "1920x1080i120hz", NULL, 0, 67500, 120000, 148500,
		2200, 280, 88, 44, 148, 1920, 1125, 22, 2, 5, 15, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_47_1280x720p120_16x9, "1280x720p120hz", NULL, 1, 90000, 120000, 148500,
		1650, 370, 110, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_48_720x480p120_4x3, "720x480p120hz", NULL, 1, 62937, 119880, 54000,
		858, 138, 16, 62, 60, 720, 525, 45, 9, 6, 30, 480, 7, 0, 0, 4, 3, 8, 9},
	{HDMI_49_720x480p120_16x9, "720x480p120hz", NULL, 1, 62937, 119880, 54000,
		858, 138, 16, 62, 60, 720, 525, 45, 9, 6, 30, 480, 7, 0, 0, 16, 9, 32, 27},
	{HDMI_50_720x480i120_4x3, "720x480i120hz", NULL, 0, 31469, 119880, 54000,
		1716, 276, 38, 124, 114, 1440, 525, 22, 4, 3, 15, 480, 4, 0, 0, 4, 3, 8, 9},
	{HDMI_51_720x480i120_16x9, "720x480i120hz", NULL, 0, 31469, 119880, 54000,
		1716, 276, 38, 124, 114, 1440, 525, 22, 4, 3, 15, 480, 4, 0, 0, 16, 9, 32, 27},
	{HDMI_52_720x576p200_4x3, "720x576p200hz", NULL, 1, 125000, 200000, 108000,
		864, 144, 12, 64, 68, 720, 625, 49, 5, 5, 39, 576, 1, 0, 0, 4, 3, 16, 15},
	{HDMI_53_720x576p200_16x9, "720x576p200hz", NULL, 1, 125000, 200000, 108000,
		864, 144, 12, 64, 68, 720, 625, 49, 5, 5, 39, 576, 1, 0, 0, 16, 9, 64, 45},
	{HDMI_54_720x576i200_4x3, "720x576i200hz", NULL, 0, 62500, 200000, 108000,
		1728, 288, 24, 126, 138, 1440, 625, 24, 2, 3, 19, 576, 1, 0, 0, 4, 3, 16, 15},
	{HDMI_55_720x576i200_16x9, "720x576i200hz", NULL, 0, 62500, 200000, 108000,
		1728, 288, 24, 126, 138, 1440, 625, 24, 2, 3, 19, 576, 1, 0, 0, 16, 9, 64, 45},
	{HDMI_56_720x480p240_4x3, "720x480p240hz", NULL, 1, 125874, 239760, 108000,
		858, 138, 16, 62, 60, 720, 525, 45, 9, 6, 30, 480, 7, 0, 0, 4, 3, 8, 9},
	{HDMI_57_720x480p240_16x9, "720x480p240hz", NULL, 1, 125874, 239760, 108000,
		858, 138, 16, 62, 60, 720, 525, 45, 9, 6, 30, 480, 7, 0, 0, 16, 9, 32, 27},
	{HDMI_58_720x480i240_4x3, "720x480i240hz", NULL, 0, 62937, 239760, 108000,
		1716, 276, 38, 124, 114, 1440, 525, 22, 4, 3, 15, 480, 4, 0, 0, 4, 3, 8, 9},
	{HDMI_59_720x480i240_16x9, "720x480i240hz", NULL, 0, 62937, 239760, 108000,
		1716, 276, 38, 124, 114, 1440, 525, 22, 4, 3, 15, 480, 4, 0, 0, 16, 9, 32, 27},
	{HDMI_60_1280x720p24_16x9, "1280x720p24hz", NULL, 1, 18000, 24000, 59400,
		3300, 2020, 1760, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_61_1280x720p25_16x9, "1280x720p25hz", NULL, 1, 18750, 25000, 74250,
		3960, 2680, 2420, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_62_1280x720p30_16x9, "1280x720p30hz", NULL, 1, 22500, 30000, 74250,
		3300, 2020, 1760, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_63_1920x1080p120_16x9, "1920x1080p120hz", NULL, 1, 135000, 120000, 297000,
		2200, 280, 88, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_64_1920x1080p100_16x9, "1920x1080p100hz", NULL, 1, 112500, 100000, 297000,
		2640, 720, 528, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_65_1280x720p24_64x27, "1280x720p24hz", NULL, 1, 18000, 24000, 59400,
		3300, 2020, 1760, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_66_1280x720p25_64x27, "1280x720p25hz", NULL, 1, 18750, 25000, 74250,
		3960, 2680, 2420, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_67_1280x720p30_64x27, "1280x720p30hz", NULL, 1, 22500, 30000, 74250,
		3300, 2020, 1760, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_68_1280x720p50_64x27, "1280x720p50hz", NULL, 1, 37500, 50000, 74250,
		1980, 700, 440, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_69_1280x720p60_64x27, "1280x720p60hz", NULL, 1, 45000, 60000, 74250,
		1650, 370, 110, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_70_1280x720p100_64x27, "1280x720p100hz", NULL, 1, 75000, 100000, 148500,
		1980, 700, 440, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_71_1280x720p120_64x27, "1280x720p120hz", NULL, 1, 90000, 120000, 148500,
		1650, 370, 110, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_72_1920x1080p24_64x27, "1920x1080p24hz", NULL, 1, 27000, 24000, 74250,
		2750, 830, 638, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_73_1920x1080p25_64x27, "1920x1080p25hz", NULL, 1, 28125, 25000, 74250,
		2640, 720, 528, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_74_1920x1080p30_64x27, "1920x1080p30hz", NULL, 1, 33750, 30000, 74250,
		2200, 280, 88, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_75_1920x1080p50_64x27, "1920x1080p50hz", NULL, 1, 56250, 50000, 148500,
		2640, 720, 528, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_76_1920x1080p60_64x27, "1920x1080p60hz", NULL, 1, 67500, 60000, 148500,
		2200, 280, 88, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_77_1920x1080p100_64x27, "1920x1080p100hz", NULL, 1, 112500, 100000, 297000,
		2640, 720, 528, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_78_1920x1080p120_64x27, "1920x1080p120hz", NULL, 1, 135000, 120000, 297000,
		2200, 280, 88, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_79_1680x720p24_64x27, "1680x720p24hz", NULL, 1, 18000, 24000, 59400,
		3300, 1620, 1360, 40, 220, 1680, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_80_1680x720p25_64x27, "1680x720p25hz", NULL, 1, 18750, 25000, 59400,
		3168, 1488, 1228, 40, 220, 1680, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_81_1680x720p30_64x27, "1680x720p30hz", NULL, 1, 22500, 30000, 59400,
		2640, 960, 700, 40, 220, 1680, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_82_1680x720p50_64x27, "1680x720p50hz", NULL, 1, 37500, 50000, 82500,
		2200, 520, 260, 40, 220, 1680, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_83_1680x720p60_64x27, "1680x720p60hz", NULL, 1, 45000, 60000, 99000,
		2200, 520, 260, 40, 220, 1680, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_84_1680x720p100_64x27, "1680x720p100hz", NULL, 1, 82500, 100000, 165000,
		2000, 320, 60, 40, 220, 1680, 825, 105, 5, 5, 95, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_85_1680x720p120_64x27, "1680x720p120hz", NULL, 1, 99000, 120000, 198000,
		2000, 320, 60, 40, 220, 1680, 825, 105, 5, 5, 95, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_86_2560x1080p24_64x27, "2560x1080p24hz", NULL, 1, 26400, 24000, 99000,
		3750, 1190, 998, 44, 148, 2560, 1100, 20, 4, 5, 11, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_87_2560x1080p25_64x27, "2560x1080p25hz", NULL, 1, 28125, 25000, 90000,
		3200, 640, 448, 44, 148, 2560, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_88_2560x1080p30_64x27, "2560x1080p30hz", NULL, 1, 33750, 30000, 118800,
		3520, 960, 768, 44, 148, 2560, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_89_2560x1080p50_64x27, "2560x1080p50hz", NULL, 1, 56250, 50000, 185625,
		3300, 740, 548, 44, 148, 2560, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_90_2560x1080p60_64x27, "2560x1080p60hz", NULL, 1, 66000, 60000, 198000,
		3000, 440, 248, 44, 148, 2560, 1100, 20, 4, 5, 11, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_91_2560x1080p100_64x27, "2560x1080p100hz", NULL, 1, 125000, 100000, 371250,
		2970, 410, 218, 44, 148, 2560, 1250, 170, 4, 5, 161, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_92_2560x1080p120_64x27, "2560x1080p120hz", NULL, 1, 150000, 120000, 495000,
		3300, 740, 548, 44, 148, 2560, 1250, 170, 4, 5, 161, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_93_3840x2160p24_16x9, "3840x2160p24hz", "2160p24hz", 1, 54000, 24000, 297000,
		5500, 1660, 1276, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_94_3840x2160p25_16x9, "3840x2160p25hz", "2160p25hz", 1, 56250, 25000, 297000,
		5280, 1440, 1056, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_95_3840x2160p30_16x9, "3840x2160p30hz", "2160p30hz", 1, 67500, 30000, 297000,
		4400, 560, 176, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_96_3840x2160p50_16x9, "3840x2160p50hz", "2160p50hz", 1, 112500, 50000, 594000,
		5280, 1440, 1056, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_97_3840x2160p60_16x9, "3840x2160p60hz", "2160p60hz", 1, 135000, 60000, 594000,
		4400, 560, 176, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_98_4096x2160p24_256x135, "4096x2160p24hz", "smpte24hz", 1, 54000, 24000, 297000, 5500,
		1404, 1020, 88, 296, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
	{HDMI_99_4096x2160p25_256x135, "4096x2160p25hz", NULL, 1, 56250, 25000, 297000,
		5280, 1184, 968, 88, 128, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
	{HDMI_100_4096x2160p30_256x135, "4096x2160p30hz", NULL, 1, 67500, 30000, 297000,
		4400, 304, 88, 88, 128, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
	{HDMI_101_4096x2160p50_256x135, "4096x2160p50hz", NULL, 1, 112500, 50000, 594000,
		5280, 1184, 968, 88, 128, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
	{HDMI_102_4096x2160p60_256x135, "4096x2160p60hz", NULL, 1, 135000, 60000, 594000,
		4400, 304, 88, 88, 128, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
	{HDMI_103_3840x2160p24_64x27, "3840x2160p24hz", NULL, 1, 54000, 24000, 297000,
		5500, 1660, 1276, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_104_3840x2160p25_64x27, "3840x2160p25hz", NULL, 1, 56250, 25000, 297000,
		5280, 1440, 1056, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_105_3840x2160p30_64x27, "3840x2160p30hz", NULL, 1, 67500, 30000, 297000,
		4400, 560, 176, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_106_3840x2160p50_64x27, "3840x2160p50hz", NULL, 1, 112500, 50000, 594000,
		5280, 1440, 1056, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_107_3840x2160p60_64x27, "3840x2160p60hz", NULL, 1, 135000, 60000, 594000,
		4400, 560, 176, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_108_1280x720p48_16x9, "1280x720p48hz", NULL, 1, 36000, 48000, 90000,
		2500, 1220, 960, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_109_1280x720p48_64x27, "1280x720p48hz", NULL, 1, 36000, 48000, 90000,
		2500, 1220, 960, 40, 220, 1280, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_110_1680x720p48_64x27, "1680x720p48hz", NULL, 1, 36000, 48000, 99000,
		2750, 1070, 810, 40, 220, 1680, 750, 30, 5, 5, 20, 720, 1, 1, 1, 64, 27, 64, 63},
	{HDMI_111_1920x1080p48_16x9, "1920x1080p48hz", NULL, 1, 54000, 48000, 148500,
		2750, 830, 638, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_112_1920x1080p48_64x27, "1920x1080p48hz", NULL, 1, 54000, 48000, 148500,
		2750, 830, 638, 44, 148, 1920, 1125, 45, 4, 5, 36, 1080, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_113_2560x1080p48_64x27, "2560x1080p48hz", NULL, 1, 52800, 48000, 198000,
		3750, 1190, 998, 44, 148, 2560, 1100, 20, 4, 5, 11, 1080, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_114_3840x2160p48_16x9, "3840x2160p48hz", NULL, 1, 108000, 48000, 594000,
		5500, 1660, 1276, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_115_4096x2160p48_256x135, "4096x2160p48hz", NULL, 1, 108000, 48000, 594000, 5500,
		1404, 1020, 88, 296, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
	{HDMI_116_3840x2160p48_64x27, "3840x2160p48hz", NULL, 1, 108000, 48000, 594000,
		5500, 1660, 1276, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_117_3840x2160p100_16x9, "3840x2160p100hz", NULL, 1, 225000, 100000, 1188000,
		5280, 1440, 1056, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_118_3840x2160p120_16x9, "3840x2160p120hz", NULL, 1, 270000, 120000, 1188000,
		4400, 560, 176, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_119_3840x2160p100_64x27, "3840x2160p100hz", NULL, 1, 225000, 100000, 1188000,
		5280, 1440, 1056, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_120_3840x2160p120_64x27, "3840x2160p120hz", NULL, 1, 270000, 120000, 1188000,
		4400, 560, 176, 88, 296, 3840, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_121_5120x2160p24_64x27, "5120x2160p24hz", NULL, 1, 52800, 24000, 396000,
		7500, 2380, 1996, 88, 296, 5120, 2200, 40, 8, 10, 22, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_122_5120x2160p25_64x27, "5120x2160p25hz", NULL, 1, 55000, 25000, 396000,
		7200, 2080, 1696, 88, 296, 5120, 2200, 40, 8, 10, 22, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_123_5120x2160p30_64x27, "5120x2160p30hz", NULL, 1, 66000, 30000, 396000,
		6000, 880, 664, 88, 128, 5120, 2200, 40, 8, 10, 22, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_124_5120x2160p48_64x27, "5120x2160p48hz", NULL, 1, 118800, 48000, 742500,
		6250, 1130, 746, 88, 296, 5120, 2475, 315, 8, 10, 297, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_125_5120x2160p50_64x27, "5120x2160p50hz", NULL, 1, 112500, 50000, 742500,
		6600, 1480, 1096, 88, 296, 5120, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_126_5120x2160p60_64x27, "5120x2160p60hz", NULL, 1, 135000, 60000, 742500,
		5500, 380, 164, 88, 128, 5120, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_127_5120x2160p100_64x27, "5120x2160p100hz", NULL, 1, 225000, 100000, 1485000,
		6600, 1480, 1096, 88, 296, 5120, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_193_5120x2160p120_64x27, "5120x2160p120hz", NULL, 1, 270000, 120000, 1485000,
		5500, 380, 164, 88, 128, 5120, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_194_7680x4320p24_16x9, "7680x4320p24hz", NULL, 1, 108000, 24000, 1188000, 11000,
		3320, 2552, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_195_7680x4320p25_16x9, "7680x4320p25hz", NULL, 1, 110000, 25000, 1188000, 10800,
		3120, 2352, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_196_7680x4320p30_16x9, "7680x4320p30hz", NULL, 1, 132000, 30000, 1188000,
		9000, 1320, 552, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_197_7680x4320p48_16x9, "7680x4320p48hz", NULL, 1, 216000, 48000, 2376000, 11000,
		3320, 2552, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_198_7680x4320p50_16x9, "7680x4320p50hz", NULL, 1, 220000, 50000, 2376000, 10800,
		3120, 2352, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_199_7680x4320p60_16x9, "7680x4320p60hz", NULL, 1, 264000, 60000, 2376000,
		9000, 1320, 552, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_200_7680x4320p100_16x9, "7680x4320p100hz", NULL, 1, 450000, 100000, 4752000, 10560,
		2880, 2112, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_201_7680x4320p120_16x9, "7680x4320p120hz", NULL, 1, 540000, 120000, 4752000, 8800,
		1120, 352, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 16, 9, 1, 1},
	{HDMI_202_7680x4320p24_64x27, "7680x4320p24hz", NULL, 1, 108000, 24000, 1188000, 11000,
		3320, 2552, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_203_7680x4320p25_64x27, "7680x4320p25hz", NULL, 1, 110000, 25000, 1188000, 10800,
		3120, 2352, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_204_7680x4320p30_64x27, "7680x4320p30hz", NULL, 1, 132000, 30000, 1188000,
		9000, 1320, 552, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_205_7680x4320p48_64x27, "7680x4320p48hz", NULL, 1, 216000, 48000, 2376000, 11000,
		3320, 2552, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_206_7680x4320p50_64x27, "7680x4320p50hz", NULL, 1, 220000, 50000, 2376000, 10800,
		3120, 2352, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_207_7680x4320p60_64x27, "7680x4320p60hz", NULL, 1, 264000, 60000, 2376000,
		9000, 1320, 552, 176, 592, 7680, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_208_7680x4320p100_64x27, "7680x4320p100hz", NULL, 1, 450000, 100000, 4752000, 10560,
		2880, 2112, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_209_7680x4320p120_64x27, "7680x4320p120hz", NULL, 1, 540000, 120000, 4752000, 8800,
		1120, 352, 176, 592, 7680, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 4, 3},
	{HDMI_210_10240x4320p24_64x27, "10240x4320p24hz", NULL, 1, 118800, 24000, 1485000, 12500,
		2260, 1492, 176, 592, 10240, 4950, 630, 16, 20, 594, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_211_10240x4320p25_64x27, "10240x4320p25hz", NULL, 1, 110000, 25000, 1485000, 13500,
		3260, 2492, 176, 592, 10240, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_212_10240x4320p30_64x27, "10240x4320p30hz", NULL, 1, 135000, 30000, 1485000, 11000,
		760, 288, 176, 296, 10240, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_213_10240x4320p48_64x27, "10240x4320p48hz", NULL, 1, 237600, 48000, 2970000, 12500,
		2260, 1492, 176, 592, 10240, 4950, 630, 16, 20, 594, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_214_10240x4320p50_64x27, "10240x4320p50hz", NULL, 1, 220000, 50000, 2970000, 13500,
		3260, 2492, 176, 592, 10240, 4400, 80, 16, 20, 44, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_215_10240x4320p60_64x27, "10240x4320p60hz", NULL, 1, 270000, 60000, 2970000, 11000,
		760, 288, 176, 296, 10240, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_216_10240x4320p100_64x27, "10240x4320p100hz", NULL, 1, 450000, 100000, 5940000, 13200,
		2960, 2192, 176, 592, 10240, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_217_10240x4320p120_64x27, "10240x4320p120hz", NULL, 1, 540000, 120000, 5940000, 11000,
		760, 288, 176, 296, 10240, 4500, 180, 16, 20, 144, 4320, 1, 1, 1, 64, 27, 1, 1},
	{HDMI_218_4096x2160p100_256x135, "4096x2160p100hz", NULL, 1, 225000, 100000, 1188000,
		5280, 1184, 800, 88, 296, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
	{HDMI_219_4096x2160p120_256x135, "4096x2160p120hz", NULL, 1, 270000, 120000, 1188000,
		4400, 304, 88, 88, 128, 4096, 2250, 90, 8, 10, 72, 2160, 1, 1, 1, 256, 135, 1, 1},
};
