/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/t5d_skt_v1/firmware/timing.c
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#include <asm/arch/secure_apb.h>
#include <asm/arch/timing.h>
#include <asm/arch/ddr_define.h>

ddr_set_t __ddr_setting[] __attribute__ ((section(".ddr_settings"))) = {
	{
	.cfg_board_common_setting.timming_magic								= 0,
	.cfg_board_common_setting.timming_max_valid_configs						= 1,
	.cfg_board_common_setting.timming_struct_version						= 0,
	.cfg_board_common_setting.timming_struct_org_size						= sizeof(ddr_set_t),
	.cfg_board_common_setting.timming_struct_real_size = 0,
	.cfg_board_common_setting.fast_boot								= { 0 },
	.cfg_board_common_setting.fast_boot[0] = 0x1,
	//.cfg_board_common_setting.fast_boot[3] = 0xC6,
	.cfg_board_common_setting.ddr_func = DDR_FUNC | DDR_FUNC_CONFIG_DFE_FUNCTION,
	.cfg_board_common_setting.board_id								= CONFIG_BOARD_ID_MASK,
	.cfg_board_common_setting.DramType								= CONFIG_DDR_TYPE_DDR4,
	.cfg_board_common_setting.dram_rank_config							= CONFIG_DDR0_32BIT_RANK01_CH0,
	.cfg_board_common_setting.DisabledDbyte								= CONFIG_DISABLE_D32_D63,
	.cfg_board_common_setting.dram_cs0_base_add							= 0,
	.cfg_board_common_setting.dram_cs1_base_add							= 0,
	.cfg_board_common_setting.dram_cs0_size_MB							= CONFIG_DDR0_SIZE_1024MB,
	.cfg_board_common_setting.dram_cs1_size_MB							= CONFIG_DDR1_SIZE_1024MB,
	.cfg_board_common_setting.dram_x4x8x16_mode							= CONFIG_DRAM_MODE_X16,
	.cfg_board_common_setting.Is2Ttiming								= CONFIG_USE_DDR_2T_MODE,
	.cfg_board_common_setting.log_level								= LOG_LEVEL_BASIC,
	.cfg_board_common_setting.ddr_rdbi_wr_enable							= DDR_WRITE_READ_DBI_DISABLE,
	/* pll ssc config:
	 *
	 *   pll_ssc_mode = (1<<20) | (1<<8) | ([strength] << 4) | [mode],
	 *      ppm = strength * 500
	 *      mode: 0=center, 1=up, 2=down
	 *
	 *   eg:
	 *     1. config 1000ppm center ss. then mode=0, strength=2
	 *        .pll_ssc_mode = (1<<20) | (1<<8) | (2 << 4) | 0,
	 *     2. config 3000ppm down ss. then mode=2, strength=6
	 *        .pll_ssc_mode = (1<<20) | (1<<8) | (6 << 4) | 2,
	 */
	.cfg_board_common_setting.pll_ssc_mode = (1 << 20) | (1 << 8) | (2 << 4) | 0,   //center_ssc_1000ppm,//SSC_DISABLE,(1 << 20) | (0 << 8) | (2 << 4) | 0,
	.cfg_board_common_setting.org_tdqs2dq								= 0,
	.cfg_board_common_setting.reserve1_test_function						= { 0 },
	.cfg_board_common_setting.ddr_dmc_remap								= DDR_DMC_REMAP_DDR4_32BIT,

#if 1
	//t5w ac pinmux
	.cfg_board_common_setting.ac_pinmux = {
		0, 0, 0, 1, 2, 3, 7, 27,
		21,	9, 2, 10, 5, 23, 0, 1,
		25,	11,	20,	3, 8, 28, 0, 0,
		0, 0, 6, 4, 12, 0, 0, 24,
		26, 13, 0
	},
#endif

	.cfg_board_common_setting.ddr_dqs_swap								= 0,
	.cfg_board_common_setting.ddr_dq_remap								= {
		0,  1,	2,  3,	4,  5,	6,  7,
		8,  9,	10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35
	},       //d0-d31 dm0 dm1 dm2 dm3

	.cfg_board_common_setting.ddr_vddee_setting							= { 0 },
	.cfg_board_SI_setting_ps[0].DRAMFreq = 1320,
	.cfg_board_SI_setting_ps[0].PllBypassEn = 0,
	.cfg_board_SI_setting_ps[0].training_SequenceCtrl = 0,
	.cfg_board_SI_setting_ps[0].ddr_odt_config = DDR_DRAM_ODT_W_CS0_ODT0,//DDR_DRAM_ODT_W_CS0_ODT01_CS1_ODT01__R_CS0_ODT1_CS1_ODT0, //DDR_DRAM_ODT_W_CS0_ODT0_CS1_ODT1,
	.cfg_board_SI_setting_ps[0].clk_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].cs_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].ac_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_p = DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_n = DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_p = DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_n = DDR_SOC_DATA_DRV_ODT_0_OHM,            //for pxp dram weak driver model
	.cfg_board_SI_setting_ps[0].dram_data_drv_ohm = DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_odt_ohm = DDR_DRAM_DDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_wr_odt_ohm = DDR_DRAM_DDR4_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_ac_odt_ohm = DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_pull_up_calibration_ohm = DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].lpddr4_dram_vout_voltage_range_setting = DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[0].dfe_offset = 0,
	.cfg_board_SI_setting_ps[0].vref_ac_permil = 0,
	.cfg_board_SI_setting_ps[0].vref_soc_data_permil = 0,
	.cfg_board_SI_setting_ps[0].vref_dram_data_permil = 0,
	.cfg_board_SI_setting_ps[0].max_core_timmming_frequency = 0,
	.cfg_board_SI_setting_ps[0].training_phase_parameter = { 0 },
	.cfg_board_SI_setting_ps[0].ac_trace_delay_org = {
		128, 128, 128, 128, 128, 128, 128, 128,
		384, 384, 384, 384, 384, 384, 384, 384,
		384, 384, 384, 384, 384, 384, 384, 384,
		384, 384, 384, 384, 384, 384, 384, 384,
		384, 384, 384, 384,
	}, //total 36
	.cfg_ddr_training_delay_ps[0].ac_trace_delay = {
		128, 128, 128, 128, 128, 128, 128, 256,
		256, 256, 256, 256, 256, 256+100, 256, 256,
		256, 256, 256, 256, 256, 256, 256, 256,
		256, 256, 256, 256, 256+30, 256, 256, 256,
		256, 256, 256+100, 256,
	}, //total 36
#if 0
	.cfg_ddr_training_delay_ps[0].write_dqs_delay = {
		128, 128, 128, 128, 128, 128, 128, 128
	},
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay = {
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
		192, 192, 192, 192, 192, 192, 192, 192,
	},
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay = {
		0, 0, 0, 0, 0, 0, 0, 0
	},         //total 8  //edge gate
	.cfg_ddr_training_delay_ps[0].read_dqs_delay = {
		64, 64, 64, 64, 64, 64, 64, 64
	},      //total 8
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	}, //total 72
	.cfg_ddr_training_delay_ps[0].soc_bit_vref = {
		0,  40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 50, 40, 50,
		40, 50, 40, 50
	}, //total 44
	.cfg_ddr_training_delay_ps[0].dram_bit_vref = {
		0,  32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32
	}, //total 36
#endif
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[0] = 0x0000009b,          // 155
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[1] = 0x000000a5,          // 165
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[2] = 0x0000009b,          // 155
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[3] = 0x0000008c,          // 140
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[4] = 0x0000009b,          // 155
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[5] = 0x0000009b,          // 155
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[6] = 0x0000009b,          // 155
	.cfg_ddr_training_delay_ps[0].write_dqs_delay[7] = 0x00000091,          // 145
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[0] = 0x000000e4,       // 228
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[1] = 0x000000cc,       // 204
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[2] = 0x000000dc,       // 220
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[3] = 0x000000ce,       // 206
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[4] = 0x000000e6,       // 230
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[5] = 0x000000d0,       // 208
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[6] = 0x000000de,       // 222
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[7] = 0x000000dc,       // 220
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[8] = 0x000000d5,       // 213
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[9] = 0x000000e6,       // 230
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[10] = 0x000000d7,      // 215
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[11] = 0x000000e6,      // 230
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[12] = 0x000000d8,      // 216
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[13] = 0x000000ee,      // 238
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[14] = 0x000000de,      // 222
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[15] = 0x000000e9,      // 233
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[16] = 0x000000e5,      // 229
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[17] = 0x000000e2,      // 226
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[18] = 0x000000da,      // 218
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[19] = 0x000000ca,      // 202
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[20] = 0x000000d6,      // 214
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[21] = 0x000000c9,      // 201
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[22] = 0x000000d4,      // 212
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[23] = 0x000000b9,      // 185
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[24] = 0x000000c8,      // 200
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[25] = 0x000000c5,      // 197
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[26] = 0x000000c9,      // 201
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[27] = 0x000000d7,      // 215
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[28] = 0x000000c7,      // 199
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[29] = 0x000000de,      // 222
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[30] = 0x000000c8,      // 200
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[31] = 0x000000d4,      // 212
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[32] = 0x000000cc,      // 204
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[33] = 0x000000d1,      // 209
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[34] = 0x000000c1,      // 193
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[35] = 0x000000ce,      // 206
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[36] = 0x000000e4,      // 228
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[37] = 0x000000cc,      // 204
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[38] = 0x000000dd,      // 221
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[39] = 0x000000d2,      // 210
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[40] = 0x000000e7,      // 231
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[41] = 0x000000d1,      // 209
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[42] = 0x000000de,      // 222
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[43] = 0x000000dc,      // 220
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[44] = 0x000000d9,      // 217
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[45] = 0x000000dc,      // 220
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[46] = 0x000000ca,      // 202
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[47] = 0x000000dc,      // 220
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[48] = 0x000000cf,      // 207
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[49] = 0x000000e6,      // 230
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[50] = 0x000000d5,      // 213
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[51] = 0x000000e2,      // 226
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[52] = 0x000000db,      // 219
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[53] = 0x000000d7,      // 215
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[54] = 0x000000da,      // 218
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[55] = 0x000000c8,      // 200
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[56] = 0x000000d3,      // 211
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[57] = 0x000000c8,      // 200
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[58] = 0x000000d5,      // 213
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[59] = 0x000000b6,      // 182
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[60] = 0x000000c5,      // 197
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[61] = 0x000000c3,      // 195
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[62] = 0x000000c8,      // 200
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[63] = 0x000000d4,      // 212
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[64] = 0x000000c5,      // 197
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[65] = 0x000000dc,      // 220
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[66] = 0x000000c9,      // 201
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[67] = 0x000000d0,      // 208
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[68] = 0x000000cb,      // 203
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[69] = 0x000000cf,      // 207
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[70] = 0x000000bf,      // 191
	.cfg_ddr_training_delay_ps[0].write_dq_bit_delay[71] = 0x000000cc,      // 204
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[0] = 0x00000322,      // 802
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[1] = 0x00000313,      // 787
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[2] = 0x0000031d,      // 797
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[3] = 0x00000334,      // 820
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[4] = 0x0000031f,      // 799
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[5] = 0x00000311,      // 785
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[6] = 0x0000031c,      // 796
	.cfg_ddr_training_delay_ps[0].read_dqs_gate_delay[7] = 0x00000336,      // 822
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[0] = 0x00000080,           // 114
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[1] = 0x00000080,           // 113
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[2] = 0x00000080,           // 103
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[3] = 0x00000080,           // 101
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[4] = 0x00000080,           // 121
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[5] = 0x00000080,           // 116
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[6] = 0x00000080,           // 124
	.cfg_ddr_training_delay_ps[0].read_dqs_delay[7] = 0x00000080,           // 102
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[0] = 0x0000004e,        // 78
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[1] = 0x00000036,        // 54
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[2] = 0x0000004d,        // 77
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[3] = 0x00000036,        // 54
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[4] = 0x00000051,        // 81
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[5] = 0x0000003c,        // 60
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[6] = 0x00000054,        // 84
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[7] = 0x00000036,        // 54
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[8] = 0x00000043,        // 67
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[9] = 0x0000004f,        // 79
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[10] = 0x0000003a,       // 58
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[11] = 0x0000004b,       // 75
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[12] = 0x0000003b,       // 59
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[13] = 0x00000051,       // 81
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[14] = 0x0000003f,       // 63
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[15] = 0x0000004b,       // 75
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[16] = 0x00000042,       // 66
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[17] = 0x00000045,       // 69
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[18] = 0x00000049,       // 73
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[19] = 0x00000031,       // 49
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[20] = 0x00000044,       // 68
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[21] = 0x0000002f,       // 47
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[22] = 0x00000046,       // 70
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[23] = 0x0000002d,       // 45
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[24] = 0x0000003f,       // 63
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[25] = 0x00000031,       // 49
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[26] = 0x0000003a,       // 58
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[27] = 0x00000050,       // 80
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[28] = 0x00000033,       // 51
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[29] = 0x00000041,       // 65
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[30] = 0x00000035,       // 53
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[31] = 0x00000043,       // 67
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[32] = 0x00000033,       // 51
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[33] = 0x00000046,       // 70
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[34] = 0x00000033,       // 51
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[35] = 0x0000003d,       // 61
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[36] = 0x00000054,       // 84
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[37] = 0x0000003e,       // 62
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[38] = 0x00000053,       // 83
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[39] = 0x0000003e,       // 62
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[40] = 0x00000056,       // 86
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[41] = 0x00000043,       // 67
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[42] = 0x0000005a,       // 90
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[43] = 0x00000040,       // 64
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[44] = 0x0000004a,       // 74
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[45] = 0x00000053,       // 83
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[46] = 0x0000003c,       // 60
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[47] = 0x0000004f,       // 79
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[48] = 0x00000041,       // 65
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[49] = 0x00000056,       // 86
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[50] = 0x00000044,       // 68
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[51] = 0x0000004b,       // 75
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[52] = 0x00000045,       // 69
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[53] = 0x00000049,       // 73
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[54] = 0x0000005a,       // 90
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[55] = 0x00000041,       // 65
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[56] = 0x00000056,       // 86
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[57] = 0x0000003e,       // 62
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[58] = 0x00000058,       // 88
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[59] = 0x0000003c,       // 60
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[60] = 0x00000054,       // 84
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[61] = 0x00000042,       // 66
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[62] = 0x0000004b,       // 75
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[63] = 0x00000059,       // 89
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[64] = 0x0000003c,       // 60
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[65] = 0x0000004d,       // 77
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[66] = 0x00000040,       // 64
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[67] = 0x0000004e,       // 78
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[68] = 0x0000003d,       // 61
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[69] = 0x00000051,       // 81
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[70] = 0x0000003d,       // 61
	.cfg_ddr_training_delay_ps[0].read_dq_bit_delay[71] = 0x00000047,       // 71
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[0] = (915 - 240) / 15,       // 43 (915-240)/15
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[1] = (915 - 240) / 15,       // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[2] = (915 - 240) / 15,       // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[3] = (915 - 240) / 15,       // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[4] = (915 - 240) / 15,       // 44
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[5] = (915 - 240) / 15,       // 41
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[6] = (915 - 240) / 15,       // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[7] = (915 - 240) / 15,       // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[8] = (915 - 240) / 15,       // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[9] = (915 - 240) / 15,       // 41
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[10] = (915 - 240) / 15,      // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[11] = (915 - 240) / 15,      // 40
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[12] = (915 - 240) / 15,      // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[13] = (915 - 240) / 15,      // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[14] = (915 - 240) / 15,      // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[15] = (915 - 240) / 15,      // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[16] = (915 - 240) / 15,      // 41
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[17] = (915 - 240) / 15,      // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[18] = (915 - 240) / 15,      // 44
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[19] = (915 - 240) / 15,      // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[20] = (915 - 240) / 15,      // 44
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[21] = (915 - 240) / 15,      // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[22] = (915 - 240) / 15,      // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[23] = (915 - 240) / 15,      // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[24] = (915 - 240) / 15,      // 44
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[25] = (915 - 240) / 15,      // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[26] = (915 - 240) / 15,      // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[27] = (915 - 240) / 15,      // 44
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[28] = (915 - 240) / 15,      // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[29] = (915 - 240) / 15,      // 42
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[30] = (915 - 240) / 15,      // 41
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[31] = (915 - 240) / 15,      // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[32] = 0x0000002b,            // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[33] = 0x0000002b,            // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[34] = 0x0000002b,            // 43
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[35] = 0x00000026,            // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[36] = 0x00000026,            // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[37] = 0x00000035,            // 53
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[38] = 0x00000026,            // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[39] = 0x00000033,            // 51
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[40] = 0x00000026,            // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[41] = 0x00000036,            // 54
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[42] = 0x00000026,            // 38
	.cfg_ddr_training_delay_ps[0].soc_bit_vref[43] = 0x00000036,            // 54

#if 1
	.cfg_ddr_training_delay_ps[0].reserve_training_parameter = {
		//cs0 write dqs,lane0-lane3
		(0 << 7) | 0,  (0 << 7) | 0,  (0 << 7) | 0,  (0 << 7) | 5,
		//cs1 write dqs,lane0-lane3
		(1 << 7) | 0,  (0 << 7) | 0,  (0 << 7) | 0,  (0 << 7) | 5,
		//cs0 read dqs,lane0-lane3
		(1 << 7) | 15, (1 << 7) | 15, (1 << 7) | 10, (1 << 7) | 10,
		//cs1 read dqs,lane0-lane3
		(1 << 7) | 15, (1 << 7) | 15, (1 << 7) | 15, (1 << 7) | 15,
	},
#endif
	.cfg_board_SI_setting_ps[1].DRAMFreq = 667,
	.cfg_board_SI_setting_ps[1].PllBypassEn = 0,
	.cfg_board_SI_setting_ps[1].training_SequenceCtrl = 0,
	.cfg_board_SI_setting_ps[1].ddr_odt_config = DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[1].clk_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].cs_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].ac_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_p = DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_n = DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_p = DDR_SOC_DATA_DRV_ODT_60_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_n = DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_ohm = DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_odt_ohm = DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_wr_odt_ohm = DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_ac_odt_ohm = DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_pull_up_calibration_ohm = DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].lpddr4_dram_vout_voltage_range_setting = DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[1].dfe_offset = 0,
	.cfg_board_SI_setting_ps[1].vref_ac_permil = 0,
	.cfg_board_SI_setting_ps[1].vref_soc_data_permil = 0,
	.cfg_board_SI_setting_ps[1].vref_dram_data_permil = 0,
	.cfg_board_SI_setting_ps[1].max_core_timmming_frequency = 0,
	.cfg_board_SI_setting_ps[1].training_phase_parameter = { 0 },
	.cfg_board_SI_setting_ps[1].ac_trace_delay_org = {
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128,
	}, //total 36
	.cfg_ddr_training_delay_ps[1].ac_trace_delay = {
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128, 128, 128, 128, 128,
		128, 128, 128, 128,
	}, //total 36
	.cfg_ddr_training_delay_ps[1].write_dqs_delay = {
		0, 0, 0, 0, 0, 0, 0, 0
	},
	.cfg_ddr_training_delay_ps[1].write_dq_bit_delay = {
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
		50, 50, 50, 50, 50, 50, 50, 50,
	},
	.cfg_ddr_training_delay_ps[1].read_dqs_gate_delay = {
		192, 192, 192, 192, 192, 192, 192, 192
	}, //total 8
	.cfg_ddr_training_delay_ps[1].read_dqs_delay = {
		64, 64, 64, 64, 64, 64, 64, 64
	},              //total 8
	.cfg_ddr_training_delay_ps[1].read_dq_bit_delay = {
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0
	}, //total 72
	.cfg_ddr_training_delay_ps[1].soc_bit_vref = {
		0,  40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40, 40, 40, 40, 40,
		40, 40, 40, 40
	}, //total 44
	.cfg_ddr_training_delay_ps[1].dram_bit_vref = {
		0,  32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32
	}, //total 36
	.cfg_ddr_training_delay_ps[1].reserve_training_parameter = { 0 },
}
};

pll_set_t __pll_setting = {
	.cpu_clk				= CONFIG_CPU_CLK / 24 * 24,
#ifdef CONFIG_PXP_EMULATOR
	.pxp					= 1,
#else
	.pxp					= 0,
#endif
	.spi_ctrl				= 0,
	.lCustomerID			= CONFIG_AML_CUSTOMER_ID,
#ifdef CONFIG_DEBUG_MODE
	.debug_mode				= CONFIG_DEBUG_MODE,
	.ddr_clk_debug			= CONFIG_DDR_CLK_DEBUG,
	.cpu_clk_debug			= CONFIG_CPU_CLK_DEBUG,
#endif

#ifdef CONFIG_AML_SUPPORT_TLV
	.nCFGTAddr              = AML_BL2_TMASTER_DDR_ADDR,
#endif
	.low_console_baud		= CONFIG_LOW_CONSOLE_BAUD,
};

#if 0
#define DDR_TIMMING_OFFSET(X)  (unsigned int)(unsigned long)(&(((ddr_set_t *)(0))->X))
#define DDR_TIMMING_OFFSET_SIZE(X)  sizeof(((ddr_set_t *)(0))->X)
#define DDR_TIMMING_TUNE(DDR_ID, PARA, VALUE) { DDR_ID, DDR_TIMMING_OFFSET(PARA), VALUE, DDR_TIMMING_OFFSET_SIZE(PARA), 0, 1 }

#define T963_H8_NTC_EID       0xC0A
#define T963_H8_SUM_EID       0xC4A
#define T963_H35_NTC_EID      0x2C1A
#define T963_H35_SUM_EID      0x2C5A
#define T963_H9_NTC_EID       0x6C2A
#define T963_H9_SUM_EID       0x6C6A
#define T963_H_NA_EID         0x1400

#define T963S_H8_NTC_EID      0xC8A
#define T963S_H8_SUM_EID      0xCCA
#define T963S_H35_SUM_EID     0x2CDA
#define T950D4_H5_NTC_EID     0x509
#define T950D4_H6_NTC_EID     0x909
#define T950D4_H8_NTC_EID     0xC0A
#define T950D4_H8_SUM_EID     0xC4A
#define T950D4_H35_NTC_EID    0x2C1A
#define T950D4_H35_SUM_EID    0x2C5A
#define T950X4_H5_NTC_EID     0xD09
#define T950X4_H8_NTC_EID     0xC8A
#define T950X4_H8_SUM_EID     0xCCA
#define T950X4_H35_SUM_EID    0x2CDA
#define T950X4_B5_SUM_EID     0x4C6
#endif

ddr_reg_t __ddr_reg[] = {
	/* demo, user defined override register */
	//DDR_TIMMING_TUNE(T963_H35_NTC_EID, cfg_board_SI_setting_ps[0].DRAMFreq, 1176),
	{0xaabbccdd, 0, 0, 0, 0, 0},
	{0x11223344, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
};

#define VCCK_VAL				CONFIG_VCCK_INIT_VOLTAGE
#define VDDEE_VAL				CONFIG_VDDEE_INIT_VOLTAGE
/* VCCK PWM table */
#if   (VCCK_VAL == 800)
	#define VCCK_VAL_REG	0x00220000
#elif (VCCK_VAL == 810)
	#define VCCK_VAL_REG	0x00210001
#elif (VCCK_VAL == 820)
	#define VCCK_VAL_REG	0x00200002
#elif (VCCK_VAL == 830)
	#define VCCK_VAL_REG	0x001F0003
#elif (VCCK_VAL == 840)
	#define VCCK_VAL_REG	0x001E0004
#elif (VCCK_VAL == 850)
	#define VCCK_VAL_REG	0x001D0005
#elif (VCCK_VAL == 860)
	#define VCCK_VAL_REG	0x001C0006
#elif (VCCK_VAL == 870)
	#define VCCK_VAL_REG	0x001B0007
#elif (VCCK_VAL == 880)
	#define VCCK_VAL_REG	0x001A0008
#elif (VCCK_VAL == 890)
	#define VCCK_VAL_REG	0x00190009
#elif (VCCK_VAL == 900)
	#define VCCK_VAL_REG	0x0018000A
#elif (VCCK_VAL == 910)
	#define VCCK_VAL_REG	0x0017000B
#elif (VCCK_VAL == 920)
	#define VCCK_VAL_REG	0x0016000C
#elif (VCCK_VAL == 930)
	#define VCCK_VAL_REG	0x0015000D
#elif (VCCK_VAL == 940)
	#define VCCK_VAL_REG	0x0014000E
#elif (VCCK_VAL == 950)
	#define VCCK_VAL_REG	0x0013000F
#elif (VCCK_VAL == 960)
	#define VCCK_VAL_REG	0x00120010
#elif (VCCK_VAL == 970)
	#define VCCK_VAL_REG	0x00110011
#elif (VCCK_VAL == 980)
	#define VCCK_VAL_REG	0x00100012
#elif (VCCK_VAL == 990)
	#define VCCK_VAL_REG	0x000F0013
#elif (VCCK_VAL == 1000)
	#define VCCK_VAL_REG	0x000E0014
#elif (VCCK_VAL == 1010)
	#define VCCK_VAL_REG	0x000D0015
#elif (VCCK_VAL == 1020)
	#define VCCK_VAL_REG	0x000C0016
#elif (VCCK_VAL == 1030)
	#define VCCK_VAL_REG	0x000B0017
#elif (VCCK_VAL == 1040)
	#define VCCK_VAL_REG	0x000A0018
#elif (VCCK_VAL == 1050)
	#define VCCK_VAL_REG	0x00090019
#elif (VCCK_VAL == 1060)
	#define VCCK_VAL_REG	0x0008001A
#elif (VCCK_VAL == 1070)
	#define VCCK_VAL_REG	0x0007001B
#elif (VCCK_VAL == 1080)
	#define VCCK_VAL_REG	0x0006001C
#elif (VCCK_VAL == 1090)
	#define VCCK_VAL_REG	0x0005001D
#elif (VCCK_VAL == 1100)
	#define VCCK_VAL_REG	0x0004001E
#elif (VCCK_VAL == 1110)
	#define VCCK_VAL_REG	0x0003001F
#elif (VCCK_VAL == 1120)
	#define VCCK_VAL_REG	0x00020020
#elif (VCCK_VAL == 1130)
	#define VCCK_VAL_REG	0x00010021
#elif (VCCK_VAL == 1140)
	#define VCCK_VAL_REG	0x00000022
#else
	#error "VCCK val out of range\n"
#endif

/* VDDEE PWM table */
#if   (VDDEE_VAL == 800)
	#define PWM_CONSTANT_OUT
	#define VDDEE_VAL_REG	0x0001D0000
#elif (VDDEE_VAL == 810)
	#define VDDEE_VAL_REG   0x0001C0000
#elif (VDDEE_VAL == 820)
	#define VDDEE_VAL_REG   0x0001B0001
#elif (VDDEE_VAL == 830)
	#define VDDEE_VAL_REG   0x0001A0002
#elif (VDDEE_VAL == 840)
	#define VDDEE_VAL_REG   0x000190003
#elif (VDDEE_VAL == 850)
	#define VDDEE_VAL_REG   0x000180004
#elif (VDDEE_VAL == 860)
	#define VDDEE_VAL_REG   0x000170005
#elif (VDDEE_VAL == 870)
	#define VDDEE_VAL_REG   0x000160006
#elif (VDDEE_VAL == 880)
	#define VDDEE_VAL_REG   0x000150007
#elif (VDDEE_VAL == 890)
	#define VDDEE_VAL_REG   0x000140008
#elif (VDDEE_VAL == 900)
	#define VDDEE_VAL_REG   0x000130009
#elif (VDDEE_VAL == 910)
	#define VDDEE_VAL_REG   0x00012000A
#elif (VDDEE_VAL == 920)
	#define VDDEE_VAL_REG   0x00011000B
#elif (VDDEE_VAL == 930)
	#define VDDEE_VAL_REG   0x00010000C
#elif (VDDEE_VAL == 940)
	#define VDDEE_VAL_REG   0x0000F000D
#elif (VDDEE_VAL == 950)
	#define VDDEE_VAL_REG   0x0000E000E
#elif (VDDEE_VAL == 960)
	#define VDDEE_VAL_REG   0x0000D000F
#elif (VDDEE_VAL == 970)
	#define VDDEE_VAL_REG   0x0000C0010
#elif (VDDEE_VAL == 980)
	#define VDDEE_VAL_REG   0x0000B0011
#elif (VDDEE_VAL == 990)
	#define VDDEE_VAL_REG   0x0000A0012
#elif (VDDEE_VAL == 1000)
	#define VDDEE_VAL_REG   0x000090013
#elif (VDDEE_VAL == 1010)
	#define VDDEE_VAL_REG   0x000080014
#elif (VDDEE_VAL == 1020)
	#define VDDEE_VAL_REG   0x000070015
#elif (VDDEE_VAL == 1030)
	#define VDDEE_VAL_REG   0x000060016
#elif (VDDEE_VAL == 1040)
	#define VDDEE_VAL_REG   0x000050017
#elif (VDDEE_VAL == 1050)
	#define VDDEE_VAL_REG   0x000040018
#elif (VDDEE_VAL == 1060)
	#define VDDEE_VAL_REG   0x000030019
#elif (VDDEE_VAL == 1070)
	#define VDDEE_VAL_REG   0x00002001A
#elif (VDDEE_VAL == 1080)
	#define VDDEE_VAL_REG   0x00001001B
#elif (VDDEE_VAL == 1090)
	#define VDDEE_VAL_REG   0x00000001C
#elif (VDDEE_VAL == 1100)
	#define PWM_CONSTANT_OUT
	#define VDDEE_VAL_REG	0x00000001F
#else
	#error "VDDEE val out of range\n"
#endif

/* for PWM use */
/* PWM driver check http://scgit.amlogic.com:8080/#/c/38093/ */
#define PWMAB_PWM_A                     ((0x0000 << 2) + 0xffd1b000)
#define PWMAB_PWM_B                     ((0x0001 << 2) + 0xffd1b000)
#define PWMAB_MISC_REG_AB       ((0x0002 << 2) + 0xffd1b000)

/* board vmin_value defines */
#define VMIN_FT_FF                           770
#define VMIN_FT_TT                           800
#define VMIN_FT_SS                           810
/* board vddee_value defines */
/* SS/TT/FF=1.0/1.0/1.0 V */
#define VMIN_EE_FF                          0x00090013
#define VMIN_EE_TT                          0x00090013
#define VMIN_EE_SS                          0x00090013

bl2_reg_t __bl2_reg[] = {
	/* demo, user defined override register */
	/* vmin value init */
	{0,	VMIN_FT_FF,	0xffffffff,	0,	BL2_VMIN_FT__FLAG_1, 0},
	{0,	VMIN_FT_TT,	0xffffffff,	0,	BL2_VMIN_FT__FLAG_2, 0},
	{0,	VMIN_FT_SS,	0xffffffff,	0,	BL2_VMIN_FT__FLAG_3, 0},
	/* eg: PWM init */
	/* PWM_A VCCK_VAL_REG */
	{ PWMAB_PWM_A,		       VCCK_VAL_REG,			   0xffffffff,	 0, BL2_INIT_STAGE_1, 0 },
	/* PWMAO_B VDDEE_VAL_REG */
#ifdef CONFIG_PDVFS_ENABLE
	{AO_PWM_PWM_B,	VMIN_EE_FF,	0xffffffff,	0,	BL2_VMIN_EE__FLAG_1, 0},
	{AO_PWM_PWM_B,	VMIN_EE_TT,	0xffffffff,	0,	BL2_VMIN_EE__FLAG_2, 0},
	{AO_PWM_PWM_B,	VMIN_EE_SS,	0xffffffff,	0,	BL2_VMIN_EE__FLAG_3, 0},
#else
	{ AO_PWM_PWM_B,	VDDEE_VAL_REG,	0xffffffff,	0,	BL2_INIT_STAGE_1, 0 },
#endif
	/*pwm needs to support full-height or full-low output*/
	{PWMAB_MISC_REG_AB,	((1 << 0) | (1 << 15) | (1 << 28)), ((1 << 0) | (1 << 15) | (1 << 28)), 0, BL2_INIT_STAGE_1, 0},
#ifdef PWM_CONSTANT_OUT
	{AO_PWM_MISC_REG_AB,	((1 << 1) | (1 << 23) | (1 << 29)), ((1 << 1) | (1 << 23) | (1 << 29))), 0, BL2_INIT_STAGE_1, 0},
#else
	{AO_PWM_MISC_REG_AB,	((1 << 1) | (1 << 23)), ((1 << 1) | (1 << 23)), 0, BL2_INIT_STAGE_1, 0},
#endif
	/* MUX GPIOAO_9 to PWMAO_B GPIOZ5 to PWM_A */
	{ AO_RTI_PINMUX_REG1,	       (4 << 4),		   (0xF << 4), 0, BL2_INIT_STAGE_1, 0 },
	{ PERIPHS_PIN_MUX_4,	       (1 << 20),		   (0xF << 20), 0, BL2_INIT_STAGE_1, 0 },
	/* Enable VCCK SET GPIOD_10 HIGH */
	//{ AO_RTI_PINMUX_REG1,	       (0 << 8),			   (0xF << 8),	 0, BL2_INIT_STAGE_1, 0 },
	//{ AO_GPIO_O_EN_N,	       (0 << 10),			   (1 << 10),	 0, BL2_INIT_STAGE_1, 0 },
	//{ AO_GPIO_O,		       (1 << 10),			   (1 << 10),	 0, BL2_INIT_STAGE_1, 0 },
	/* Enable 5V_EN ,set GPIOAO_10 low --> several millisecond--set high in board_init */
	{ AO_RTI_PINMUX_REG1,	       (0 << 8),		(0xF << 8),	 0, BL2_INIT_STAGE_1, 0 },
	{ AO_GPIO_O_EN_N,	       (0 << 10),		(1 << 10),	 0, BL2_INIT_STAGE_1, 0 },
	{ AO_GPIO_O,		       (0 << 10),		(1 << 10),	 0, BL2_INIT_STAGE_1, 0 },
	/* GPIOH_12 pull high */
	//{PREG_PAD_GPIO2_O,     (1 << 12),               (1 << 12),   0, BL2_INIT_STAGE_1, 0},
	//{PREG_PAD_GPIO2_EN_N,  (0 << 12),               (1 << 12),   0, BL2_INIT_STAGE_1, 0},
};
