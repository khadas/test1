/*
 * board/amlogic/c2_af409/firmware/timing.c
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

#include <asm/arch/secure_apb.h>
#include <asm/arch/timing.h>
#include <asm/arch/ddr_define.h>

/* board clk defines */
#define CPU_CLK					1512
#define TIMMING_MAX_CONFIG		1

ddr_set_t __ddr_setting[] __attribute__ ((section(".ddr_settings"))) = {
#if 0//af400
{
	//af400
	.cfg_board_common_setting.	board_id					=	CONFIG_BOARD_ID_MASK,
	.cfg_board_common_setting.	DramType					=	CONFIG_DDR_TYPE_DDR4,
	.cfg_board_common_setting.	dram_rank_config			=	CONFIG_DDR0_32BIT_RANK0_CH0,
	.cfg_board_common_setting.	dram_cs0_size_MB			=	CONFIG_DDR0_SIZE_1024MB,
	.cfg_board_common_setting.	dram_cs1_size_MB			=	CONFIG_DDR1_SIZE_0MB,
	.cfg_board_common_setting.	pll_ssc_mode				=	DDR_PLL_SSC_DISABLE,
	.cfg_board_common_setting.	ddr_rdbi_wr_enable			=	DDR_WRITE_READ_DBI_DISABLE,
	.cfg_board_common_setting.	dram_x4x8x16_mode			=	CONFIG_DRAM_MODE_X16,
	.cfg_board_common_setting.	ddr_dmc_remap				=	DDR_DMC_REMAP_DDR4_32BIT,
	.cfg_board_common_setting.	fast_boot					=	{0},

	//DDR frequercy 1
	.cfg_board_SI_setting_ps[0].DRAMFreq					=	1176,//1008,//667,1008,1200
	.cfg_board_SI_setting_ps[0].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[0].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[0].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[0].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_48_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_48_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[0].reserve2					=	0,
	.cfg_board_SI_setting_ps[0].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[0].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[0].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[0].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[0].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[0].ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[0].	ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36
	#endif
	//write delay line setting
	#if 1
	.cfg_ddr_training_delay_ps[0].	write_dqs_delay = {128,128,128,128,128,128,128,128} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0].	write_dq_bit_delay = {
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,},
	#endif
	//.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {0,0,0,0,0,0,0,0} , //total 8 //edge mode
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8

	.cfg_ddr_training_delay_ps[0].	read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[0].	soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,50,40,50,40,50,40,50},//total 44
	.cfg_ddr_training_delay_ps[0].	dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36
	.cfg_ddr_training_delay_ps[0].	reserve_training_parameter	=	{0}	,
	//.cfg_ddr_training_delay_ps[0].reserve_training_parameter={((1<<7)|1),},

	//pinmux setting
	#if 1  //af409
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	8,	27,	10,	2,	9,	21,	5,	14,	1,	0,	25,	13,	12,	4,	7,	22,	0,	0,	0,	0,	6,	3,	20,	0,	0,	15,	26,	11,
	},
	#endif
	#if 0  //af419
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	27,	12,	21,	9,	8,	0,	14,	10,	6,	7,	20,	5,	22,	13,	15,	2,	0,	0,	0,	0,	11,	26,	4,	0,	0,	25,	3,	1,
	},
	#endif
	.cfg_board_common_setting.	ddr_dqs_swap	=	0,

	#if 1
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	0,1,2,3,4,5,6,7,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	},//d0-d31 dm0 dm1 dm2 dm3
	#endif

	.cfg_board_common_setting.	timming_magic				=	0x66223333,//ddr_set_t start
	.cfg_board_common_setting.	timming_max_valid_configs	=	TIMMING_MAX_CONFIG,//sizeof(__ddr_setting)/sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_version		=	0,
	.cfg_board_common_setting.	timming_struct_org_size		=	sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_real_size	=	0,	//0
	.cfg_board_common_setting.	ddr_func					=	0,
	.cfg_board_common_setting.	DisabledDbyte				=	CONFIG_DISABLE_D32_D63,
	.cfg_board_common_setting.	dram_cs0_base_add			=	0,
	.cfg_board_common_setting.	dram_cs1_base_add			=	0,

	.cfg_board_common_setting.	Is2Ttiming					=	CONFIG_USE_DDR_2T_MODE,
	.cfg_board_common_setting.	log_level					=	LOG_LEVEL_BASIC,
	.cfg_board_common_setting.	org_tdqs2dq					=	0,
	.cfg_board_common_setting.	reserve1_test_function		=	{0},
	.cfg_board_common_setting.	ddr_vddee_setting			=	{0},

	//DDR frequercy 2
	.cfg_board_SI_setting_ps[1].DRAMFreq					=	600,
	.cfg_board_SI_setting_ps[1].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[1].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[1].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[1].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[1].reserve2					=	0,
	.cfg_board_SI_setting_ps[1].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[1].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[1].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[1].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[1].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[1].ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36
	#endif
	.cfg_ddr_training_delay_ps[1]. write_dqs_delay = {0,0,0,0,0,0,0,0},
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32},
	#if 1
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,},
	#endif

	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_gate_delay = {192,192,192,192,192,192,192,192},//total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0},//total 72
	.cfg_ddr_training_delay_ps[1]. soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40},//total 44
	.cfg_ddr_training_delay_ps[1]. dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36

	.cfg_ddr_training_delay_ps[1].reserve_training_parameter	=	{0,0,0,0,0,0,0,0x7788},//ddr_set_t end
},
#endif //end af400

#if 1//af409
{
	//af409
	.cfg_board_common_setting.	board_id					=	CONFIG_BOARD_ID_MASK,
	.cfg_board_common_setting.	DramType					=	CONFIG_DDR_TYPE_DDR4,
	.cfg_board_common_setting.	dram_rank_config			=	CONFIG_DDR0_32BIT_RANK0_CH0,
	.cfg_board_common_setting.	dram_cs0_size_MB			=	CONFIG_DDR0_SIZE_1024MB,
	.cfg_board_common_setting.	dram_cs1_size_MB			=	CONFIG_DDR1_SIZE_0MB,
	.cfg_board_common_setting.	pll_ssc_mode				=	DDR_PLL_SSC_DISABLE,
	.cfg_board_common_setting.	ddr_rdbi_wr_enable			=	DDR_WRITE_READ_DBI_DISABLE,
	.cfg_board_common_setting.	dram_x4x8x16_mode			=	CONFIG_DRAM_MODE_X16,
	.cfg_board_common_setting.	ddr_dmc_remap				=	DDR_DMC_REMAP_DDR4_32BIT,
	.cfg_board_common_setting.	fast_boot					=	{0},

	//DDR frequercy 1
	.cfg_board_SI_setting_ps[0].DRAMFreq					=	1176,//667
	.cfg_board_SI_setting_ps[0].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[0].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[0].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[0].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_48_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[0].reserve2					=	0,
	.cfg_board_SI_setting_ps[0].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[0].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[0].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[0].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[0].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[0].ac_trace_delay_org = {
	128,128,100,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36

	#if 0
	.cfg_ddr_training_delay_ps[0].	ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36
	#endif
	#if 1
	.cfg_ddr_training_delay_ps[0].	ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,
	},//total 36
	#endif
	//write delay line setting
	#if 0
	.cfg_ddr_training_delay_ps[0].	write_dqs_delay = {0+256,0+256,0+256,0+256,0+256,0+256,0+256,0+256} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0].	write_dq_bit_delay = {
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,},
	#endif
	#if 1
	.cfg_ddr_training_delay_ps[0].	write_dqs_delay = {0+300,0+300,0+300,0+300,0+300,0+300,0+300,0+300} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0].	write_dq_bit_delay = {
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,
	50+300,50+300,50+300,50+300,50+300,50+300,50+300,50+300,},
	#endif
	//.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {192,192,192,192,192,192,192,192} , //total 8 //edge mode
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8

	.cfg_ddr_training_delay_ps[0].	read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[0].	soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40} , //total 44
	.cfg_ddr_training_delay_ps[0].	dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36
	.cfg_ddr_training_delay_ps[0].	reserve_training_parameter	=	{0}	,
	//.cfg_ddr_training_delay_ps[0].reserve_training_parameter={((1<<7)|1),},

	//pinmux setting
	#if 1  //af409
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	8,	27,	10,	2,	9,	21,	5,	14,	1,	0,	25,	13,	12,	4,	7,	22,	0,	0,	0,	0,	6,	3,	20,	0,	0,	15,	26,	11,
	},
	#endif
	#if 0  //af419
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	27,	12,	21,	9,	8,	0,	14,	10,	6,	7,	20,	5,	22,	13,	15,	2,	0,	0,	0,	0,	11,	26,	4,	0,	0,	25,	3,	1,
	},
	#endif
	.cfg_board_common_setting.	ddr_dqs_swap	=	0,

	#if 1
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	0,1,2,3,4,5,6,7,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	},//d0-d31 dm0 dm1 dm2 dm3
	#endif

	.cfg_board_common_setting.	timming_magic				=	0x66223333,//ddr_set_t start
	.cfg_board_common_setting.	timming_max_valid_configs	=	TIMMING_MAX_CONFIG,//sizeof(__ddr_setting)/sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_version		=	0,
	.cfg_board_common_setting.	timming_struct_org_size		=	sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_real_size	=	0,	//0
	.cfg_board_common_setting.	ddr_func					=	0,
	.cfg_board_common_setting.	DisabledDbyte				=	CONFIG_DISABLE_D32_D63,
	.cfg_board_common_setting.	dram_cs0_base_add			=	0,
	.cfg_board_common_setting.	dram_cs1_base_add			=	0,

	.cfg_board_common_setting.	Is2Ttiming					=	CONFIG_USE_DDR_2T_MODE,
	.cfg_board_common_setting.	log_level					=	LOG_LEVEL_BASIC,
	.cfg_board_common_setting.	org_tdqs2dq					=	0,
	.cfg_board_common_setting.	reserve1_test_function		=	{0},
	.cfg_board_common_setting.	ddr_vddee_setting			=	{0},

	//DDR frequercy 2
	.cfg_board_SI_setting_ps[1].DRAMFreq					=	600,
	.cfg_board_SI_setting_ps[1].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[1].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[1].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[1].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[1].reserve2					=	0,
	.cfg_board_SI_setting_ps[1].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[1].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[1].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[1].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[1].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[1].ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36
	#endif
	.cfg_ddr_training_delay_ps[1]. write_dqs_delay = {0,0,0,0,0,0,0,0},
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32},
	#if 1
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,},
	#endif

	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_gate_delay = {192,192,192,192,192,192,192,192},//total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0},//total 72
	.cfg_ddr_training_delay_ps[1]. soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40},//total 44
	.cfg_ddr_training_delay_ps[1]. dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36

	.cfg_ddr_training_delay_ps[1].reserve_training_parameter	=	{0,0,0,0,0,0,0,0x7788},//ddr_set_t end
},
#endif //end af409

#if 0//af419
{
	//af419
	.cfg_board_common_setting.	board_id					=	CONFIG_BOARD_ID_MASK,
	.cfg_board_common_setting.	DramType					=	CONFIG_DDR_TYPE_DDR4,
	.cfg_board_common_setting.	dram_rank_config			=	CONFIG_DDR0_32BIT_RANK0_CH0,
	.cfg_board_common_setting.	dram_cs0_size_MB			=	CONFIG_DDR0_SIZE_1024MB,
	.cfg_board_common_setting.	dram_cs1_size_MB			=	CONFIG_DDR1_SIZE_0MB,
	.cfg_board_common_setting.	pll_ssc_mode				=	DDR_PLL_SSC_DISABLE,
	.cfg_board_common_setting.	ddr_rdbi_wr_enable			=	DDR_WRITE_READ_DBI_DISABLE,
	.cfg_board_common_setting.	dram_x4x8x16_mode			=	CONFIG_DRAM_MODE_X16,
	.cfg_board_common_setting.	ddr_dmc_remap				=	DDR_DMC_REMAP_DDR4_32BIT,
	.cfg_board_common_setting.	fast_boot					=	{0},

	//DDR frequercy 1
	.cfg_board_SI_setting_ps[0].DRAMFreq					=	1176,//667,
	.cfg_board_SI_setting_ps[0].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[0].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[0].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[0].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_60_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[0].reserve2					=	0,
	.cfg_board_SI_setting_ps[0].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[0].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[0].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[0].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[0].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[0].ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[0].	ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36
	#endif
	//write delay line setting
	#if 1
	.cfg_ddr_training_delay_ps[0].	write_dqs_delay = {0+256,0+256,0+256,0+256,0+256,0+256,0+256,0+256} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0].	write_dq_bit_delay = {
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,},
	#endif
	//.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {192,192,192,192,192,192,192,192} , //total 8 //edge mode
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8

	.cfg_ddr_training_delay_ps[0].	read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[0].	soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40} , //total 44
	.cfg_ddr_training_delay_ps[0].	dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36
	.cfg_ddr_training_delay_ps[0].	reserve_training_parameter	=	{0}	,
	//.cfg_ddr_training_delay_ps[0].reserve_training_parameter={((1<<7)|1),},

	//pinmux setting
	#if 0  //af409
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	8,	27,	10,	2,	9,	21,	5,	14,	1,	0,	25,	13,	12,	4,	7,	22,	0,	0,	0,	0,	6,	3,	20,	0,	0,	15,	26,	11,
	},
	#endif
	#if 1  //af419
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	27,	12,	21,	9,	8,	0,	14,	10,	6,	7,	20,	5,	22,	13,	15,	2,	0,	0,	0,	0,	11,	26,	4,	0,	0,	25,	3,	1,
	},
	#endif
	.cfg_board_common_setting.	ddr_dqs_swap	=	0,

	#if 1
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	0,1,2,3,4,5,6,7,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	},//d0-d31 dm0 dm1 dm2 dm3
	#endif

	.cfg_board_common_setting.	timming_magic				=	0x66223333,//ddr_set_t start
	.cfg_board_common_setting.	timming_max_valid_configs	=	TIMMING_MAX_CONFIG,//sizeof(__ddr_setting)/sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_version		=	0,
	.cfg_board_common_setting.	timming_struct_org_size		=	sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_real_size	=	0,	//0
	.cfg_board_common_setting.	ddr_func					=	0,
	.cfg_board_common_setting.	DisabledDbyte				=	CONFIG_DISABLE_D32_D63,
	.cfg_board_common_setting.	dram_cs0_base_add			=	0,
	.cfg_board_common_setting.	dram_cs1_base_add			=	0,

	.cfg_board_common_setting.	Is2Ttiming					=	CONFIG_USE_DDR_2T_MODE,
	.cfg_board_common_setting.	log_level					=	LOG_LEVEL_BASIC,
	.cfg_board_common_setting.	org_tdqs2dq					=	0,
	.cfg_board_common_setting.	reserve1_test_function		=	{0},
	.cfg_board_common_setting.	ddr_vddee_setting			=	{0},

	//DDR frequercy 2
	.cfg_board_SI_setting_ps[1].DRAMFreq					=	600,
	.cfg_board_SI_setting_ps[1].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[1].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[1].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[1].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[1].reserve2					=	0,
	.cfg_board_SI_setting_ps[1].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[1].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[1].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[1].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[1].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[1].ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36
	#endif
	.cfg_ddr_training_delay_ps[1]. write_dqs_delay = {0,0,0,0,0,0,0,0},
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32},
	#if 1
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,},
	#endif

	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_gate_delay = {192,192,192,192,192,192,192,192},//total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0},//total 72
	.cfg_ddr_training_delay_ps[1]. soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40},//total 44
	.cfg_ddr_training_delay_ps[1]. dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36

	.cfg_ddr_training_delay_ps[1].reserve_training_parameter	=	{0,0,0,0,0,0,0,0x7788},//ddr_set_t end
},
#endif //end af419

#if 0//real DDR3
{
	//real DDR3
	.cfg_board_common_setting.	board_id					=	CONFIG_BOARD_ID_MASK,
	.cfg_board_common_setting.	DramType					=	CONFIG_DDR_TYPE_DDR3,
	.cfg_board_common_setting.	dram_rank_config			=	CONFIG_DDR0_32BIT_16BIT_RANK0_CH0,
	.cfg_board_common_setting.	dram_cs0_size_MB			=	CONFIG_DDR0_SIZE_768MB,
	.cfg_board_common_setting.	dram_cs1_size_MB			=	CONFIG_DDR1_SIZE_0MB,
	.cfg_board_common_setting.	pll_ssc_mode				=	DDR_PLL_SSC_DISABLE,
	.cfg_board_common_setting.	ddr_rdbi_wr_enable			=	DDR_WRITE_READ_DBI_DISABLE,
	.cfg_board_common_setting.	dram_x4x8x16_mode			=	CONFIG_DRAM_MODE_X16,
	.cfg_board_common_setting.	ddr_dmc_remap				=	DDR_DMC_REMAP_DDR3_32BIT,
	.cfg_board_common_setting.	fast_boot					=	{0},

	//DDR frequercy 1
	.cfg_board_SI_setting_ps[0].DRAMFreq					=	667,
	.cfg_board_SI_setting_ps[0].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[0].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[0].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[0].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_ohm			=	DDR_DRAM_DDR3_DRV_34_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_odt_ohm			=	DDR_DRAM_DDR3_ODT_60_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[0].reserve2					=	0,
	.cfg_board_SI_setting_ps[0].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[0].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[0].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[0].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[0].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[0].ac_trace_delay_org = {
	0,0,0,0,0,0,0,0,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[0].	ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,256,256,256,256,
	256,256,256,256,
	},//total 36
	#endif
	//write delay line setting
	#if 1
	.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {128-1,128-1,128+48,128+58,128+32,128+32,128+32,128+32} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {
	96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,
	96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,
	128+128,128+128,128+128,128+128,128+128,128+128,128+128,128+128,128+128,
	128+128,128+128,128+128,128+128,128+128,128+128,128+128,128+128,128+128,
	96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,
	96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,
	96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,
	96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,96+128,},
	#endif
	//.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {896-128,896-128,896-128,896-128,896-128,896-128,896-128,896-128} , //total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8

	.cfg_ddr_training_delay_ps[0].	read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[0].	soc_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,42,32,42,32,42,32,42,},//total 44
	.cfg_ddr_training_delay_ps[0].	dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36
	.cfg_ddr_training_delay_ps[0].	reserve_training_parameter	=	{0}	,
	//.cfg_ddr_training_delay_ps[0].reserve_training_parameter={((1<<7)|1),},

	//pinmux setting
	#if 0  //af409
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	8,	27,	10,	2,	9,	21,	5,	14,	1,	0,	25,	13,	12,	4,	7,	22,	0,	0,	0,	0,	6,	3,	20,	0,	0,	15,	26,	11,
	},
	#endif
	#if 0  //af419
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	27,	12,	21,	9,	8,	0,	14,	10,	6,	7,	20,	5,	22,	13,	15,	2,	0,	0,	0,	0,	11,	26,	4,	0,	0,	25,	3,	1,
	},
	#endif
	#if 1  //real DDR3
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	0,	0,	0,	0,	20,	21,	22,	0,	0,	25,	26,	27,	0
	},
	#endif
	.cfg_board_common_setting.	ddr_dqs_swap	=	0,

	#if 1
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	0,1,2,3,4,5,6,7,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	},//d0-d31 dm0 dm1 dm2 dm3
	#endif

	.cfg_board_common_setting.	timming_magic				=	0x66223333,//ddr_set_t start
	.cfg_board_common_setting.	timming_max_valid_configs	=	TIMMING_MAX_CONFIG,//sizeof(__ddr_setting)/sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_version		=	0,
	.cfg_board_common_setting.	timming_struct_org_size		=	sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_real_size	=	0,	//0
	.cfg_board_common_setting.	ddr_func					=	0,
	.cfg_board_common_setting.	DisabledDbyte				=	CONFIG_DISABLE_D32_D63,
	.cfg_board_common_setting.	dram_cs0_base_add			=	0,
	.cfg_board_common_setting.	dram_cs1_base_add			=	0,

	.cfg_board_common_setting.	Is2Ttiming					=	CONFIG_USE_DDR_2T_MODE,
	.cfg_board_common_setting.	log_level					=	LOG_LEVEL_BASIC,
	.cfg_board_common_setting.	org_tdqs2dq					=	0,
	.cfg_board_common_setting.	reserve1_test_function		=	{0},
	.cfg_board_common_setting.	ddr_vddee_setting			=	{0},

	//DDR frequercy 2
	.cfg_board_SI_setting_ps[1].DRAMFreq					=	600,
	.cfg_board_SI_setting_ps[1].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[1].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[1].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[1].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[1].reserve2					=	0,
	.cfg_board_SI_setting_ps[1].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[1].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[1].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[1].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[1].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[1].ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36
	#endif
	.cfg_ddr_training_delay_ps[1]. write_dqs_delay = {0,0,0,0,0,0,0,0},
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32},
	#if 1
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,},
	#endif

	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_gate_delay = {192,192,192,192,192,192,192,192},//total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0},//total 72
	.cfg_ddr_training_delay_ps[1]. soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40},//total 44
	.cfg_ddr_training_delay_ps[1]. dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36

	.cfg_ddr_training_delay_ps[1].reserve_training_parameter	=	{0,0,0,0,0,0,0,0x7788},//ddr_set_t end
},
#endif //end real DDR3

#if 0//af409 LPDDR4
{
	//af409
	.cfg_board_common_setting.	board_id					=	CONFIG_BOARD_ID_MASK,
	.cfg_board_common_setting.	DramType					=	CONFIG_DDR_TYPE_LPDDR4,
	.cfg_board_common_setting.	dram_rank_config			=	CONFIG_DDR0_32BIT_RANK0_CH0,
	.cfg_board_common_setting.	dram_cs0_size_MB			=	CONFIG_DDR0_SIZE_1024MB,
	.cfg_board_common_setting.	dram_cs1_size_MB			=	CONFIG_DDR1_SIZE_0MB,
	.cfg_board_common_setting.	pll_ssc_mode				=	DDR_PLL_SSC_DISABLE,
	.cfg_board_common_setting.	ddr_rdbi_wr_enable			=	DDR_WRITE_READ_DBI_DISABLE,
	.cfg_board_common_setting.	dram_x4x8x16_mode			=	CONFIG_DRAM_MODE_X16,
	.cfg_board_common_setting.	ddr_dmc_remap				=	DDR_DMC_REMAP_LPDDR4_32BIT,
	.cfg_board_common_setting.	fast_boot					=	{0},

	//DDR frequercy 1
	.cfg_board_SI_setting_ps[0].DRAMFreq					=	667,
	.cfg_board_SI_setting_ps[0].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[0].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[0].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[0].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_48_OHM,
	.cfg_board_SI_setting_ps[0].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_ohm			=	DDR_DRAM_LPDDR4_DRV_40_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_odt_ohm			=	DDR_DRAM_LPDDR4_ODT_120_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[0].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[0].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[0].reserve2					=	0,
	.cfg_board_SI_setting_ps[0].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[0].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[0].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[0].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[0].training_phase_parameter				=	{0},
	#if 0
	.cfg_board_SI_setting_ps[0].ac_trace_delay_org = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,
	},//total 36
	#endif
	#if 1
	.cfg_board_SI_setting_ps[0].ac_trace_delay_org = {
	0,0,0,0,0,0,0,0,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36
	#endif

	#if 0
	.cfg_ddr_training_delay_ps[0].	ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36
	#endif
	#if 1
	.cfg_ddr_training_delay_ps[0].	ac_trace_delay = {
	0,0,0,0,0,0,0,0,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36
	#endif
	//write delay line setting
	#if 0
	.cfg_ddr_training_delay_ps[0].	write_dqs_delay = {0+256,0+256,0+256,0+256,0+256,0+256,0+256,0+256} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0].	write_dq_bit_delay = {
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,
	50+256,50+256,50+256,50+256,50+256,50+256,50+256,50+256,},
	#endif
	#if 1
	.cfg_ddr_training_delay_ps[0].	write_dqs_delay = {0,0,0,0,0,0,0,0} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0].	write_dq_bit_delay = {
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,},
	#endif
	//.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dqs_gate_delay = {0,0,0,0,0,0,0,0} , //total 8 //edge mode
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8

	.cfg_ddr_training_delay_ps[0].	read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0].	read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[0].	soc_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,40,32,40,32,40,32,40} , //total 44
	.cfg_ddr_training_delay_ps[0].	dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36
	.cfg_ddr_training_delay_ps[0].	reserve_training_parameter	=	{0}	,
	//.cfg_ddr_training_delay_ps[0].reserve_training_parameter={((1<<7)|1),},

	//pinmux setting
	#if 0  //af409
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	8,	27,	10,	2,	9,	21,	5,	14,	1,	0,	25,	13,	12,	4,	7,	22,	0,	0,	0,	0,	6,	3,	20,	0,	0,	15,	26,	11,
	},
	#endif
	#if 0  //af419
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	27,	12,	21,	9,	8,	0,	14,	10,	6,	7,	20,	5,	22,	13,	15,	2,	0,	0,	0,	0,	11,	26,	4,	0,	0,	25,	3,	1,
	},
	#endif
	#if 1  //lpddr4
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	0,	1,
	0,	5,	1,	2,	0,	0,	4,	0,	5,	0,	1,	3,	3,	4,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
	},
	#endif
	.cfg_board_common_setting.	ddr_dqs_swap	=	0,

	#if 1
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	8,15,11,13,9,12,14,10,
	3,0,6,4,5,7,2,1,
	17,18,23,22,20,21,19,16,
	28,30,27,25,26,24,29,31,
	33,32,34,35
	},//d0-d31 dm0 dm1 dm2 dm3
	#endif

	.cfg_board_common_setting.	timming_magic				=	0x66223333,//ddr_set_t start
	.cfg_board_common_setting.	timming_max_valid_configs	=	TIMMING_MAX_CONFIG,//sizeof(__ddr_setting)/sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_version		=	0,
	.cfg_board_common_setting.	timming_struct_org_size		=	sizeof(ddr_set_t),
	.cfg_board_common_setting.	timming_struct_real_size	=	0,	//0
	.cfg_board_common_setting.	ddr_func					=	0,
	.cfg_board_common_setting.	DisabledDbyte				=	CONFIG_DISABLE_D32_D63,
	.cfg_board_common_setting.	dram_cs0_base_add			=	0,
	.cfg_board_common_setting.	dram_cs1_base_add			=	0,

	.cfg_board_common_setting.	Is2Ttiming					=	CONFIG_USE_DDR_1T_MODE,
	.cfg_board_common_setting.	log_level					=	LOG_LEVEL_BASIC,
	.cfg_board_common_setting.	org_tdqs2dq					=	0,
	.cfg_board_common_setting.	reserve1_test_function		=	{0},
	.cfg_board_common_setting.	ddr_vddee_setting			=	{0},

	//DDR frequercy 2
	.cfg_board_SI_setting_ps[1].DRAMFreq					=	600,
	.cfg_board_SI_setting_ps[1].PllBypassEn					=	0,
	.cfg_board_SI_setting_ps[1].training_SequenceCtrl		=	0,
	.cfg_board_SI_setting_ps[1].ddr_odt_config				=	DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps[1].clk_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].cs_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].ac_drv_ohm					=	DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_p			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_drv_ohm_n			=	DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_p			=	DDR_SOC_DATA_DRV_ODT_120_OHM,
	.cfg_board_SI_setting_ps[1].soc_data_odt_ohm_n			=	DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_ohm			=	DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_odt_ohm			=	DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_wr_odt_ohm		=	DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_ac_odt_ohm				=	DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps[1].dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps[1].lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps[1].reserve2					=	0,
	.cfg_board_SI_setting_ps[1].vref_ac_permil 				=	0,
	.cfg_board_SI_setting_ps[1].vref_soc_data_permil 		=	0,
	.cfg_board_SI_setting_ps[1].vref_dram_data_permil		=	0,
	.cfg_board_SI_setting_ps[1].max_core_timmming_frequency				=	0,
	.cfg_board_SI_setting_ps[1].training_phase_parameter				=	{0},
	.cfg_board_SI_setting_ps[1].ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36

	#if 1
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	},//total 36
	#endif
	.cfg_ddr_training_delay_ps[1]. write_dqs_delay = {0,0,0,0,0,0,0,0},
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32},
	#if 1
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,},
	#endif

	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_gate_delay = {192,192,192,192,192,192,192,192},//total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_delay = {64,64,64,64,64,64,64,64},//total 8
	.cfg_ddr_training_delay_ps[1]. read_dq_bit_delay = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0},//total 72
	.cfg_ddr_training_delay_ps[1]. soc_bit_vref = {
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40},//total 44
	.cfg_ddr_training_delay_ps[1]. dram_bit_vref = {
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32},//total 36

	.cfg_ddr_training_delay_ps[1].reserve_training_parameter	=	{0,0,0,0,0,0,0,0x7788},//ddr_set_t end
},
#endif //end af409 LPDDR4

#if 0  //for dd3 pxp
//ddr_set_t  ddr_set_t_default=
{
	.cfg_board_common_setting.	timming_magic	=	0	,
	.cfg_board_common_setting.	timming_max_valid_configs	=	sizeof(ddr_set_t_default)/sizeof(ddr_set_t)	,
	.cfg_board_common_setting.	timming_struct_version	=	0	,
	.cfg_board_common_setting.	timming_struct_org_size	=	sizeof(ddr_set_t)	,
	.cfg_board_common_setting.	timming_struct_real_size	=	0	,	//0
	.cfg_board_common_setting.	fast_boot	=	{0}	,
	.cfg_board_common_setting.	ddr_func	=	0	,
	.cfg_board_common_setting.	board_id	=	CONFIG_BOARD_ID_MASK	,
	.cfg_board_common_setting.	DramType	=	CONFIG_DDR_TYPE_DDR3	,
	.cfg_board_common_setting.	dram_rank_config	=	CONFIG_DDR0_32BIT_16BIT_RANK0_CH0	,
	.cfg_board_common_setting.	DisabledDbyte	=	CONFIG_DISABLE_D32_D63	,
	.cfg_board_common_setting.	dram_cs0_base_add	=	0	,
	.cfg_board_common_setting.	dram_cs1_base_add	=	0	,
	.cfg_board_common_setting.	dram_cs0_size_MB	=	CONFIG_DDR0_SIZE_768MB	,
	.cfg_board_common_setting.	dram_cs1_size_MB	=	CONFIG_DDR1_SIZE_0MB	,
	.cfg_board_common_setting.	dram_x4x8x16_mode	=	CONFIG_DRAM_MODE_X16	,
	.cfg_board_common_setting.	Is2Ttiming	=	CONFIG_USE_DDR_2T_MODE	,
	.cfg_board_common_setting.	log_level	=	LOG_LEVEL_BASIC	,
	.cfg_board_common_setting.	ddr_rdbi_wr_enable	=	DDR_WRITE_READ_DBI_DISABLE	,
	.cfg_board_common_setting.	pll_ssc_mode	=	DDR_PLL_SSC_DISABLE	,
	.cfg_board_common_setting.	org_tdqs2dq	=	0	,
	.cfg_board_common_setting.	reserve1_test_function	=	{0}	,
	.cfg_board_common_setting.	ddr_dmc_remap	=	DDR_DMC_REMAP_DDR3_32BIT	,
	#if 0
	.cfg_board_common_setting.	ac_pinmux	=
			{
	0,	0,	0,	1,	2,	3,
	8,	27,	10,	2,	9,	21,	5,	14,	1,	0,	25,	13,	12,	4,	7,	22,	0,	0,	0,	0,	6,	3,	20,	0,	0,	15,	26,	11,
		}	,

		//ac_group0-ac_group1
	#endif
	#if 1
	.cfg_board_common_setting.	ac_pinmux	=
	{
	0,	0,	0,	1,	2,	3,
	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	0,	0,	0,	0,	20,	21,	22,	0,	0,	25,	26,	27,	0
	}	,
	#endif
	.cfg_board_common_setting.	ddr_dqs_swap	=	0	,
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	3,2,0,1,7,6,5,4,
	14,13,12,15,8,9,11,10,
	20,21,22,23,16,17,19,18,
	24,25,28,26,31,30,27,29,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	2,3,1,0,6,7,4,5,
	11,10,9,8,15,14,13,12,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	3,2,0,1,7,6,5,4,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	//1,0,3,2,5,4,7,6,
	#endif
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	2,7,1,5,3,6,0,4,
	10,11,15,13,14,9,8,12,
	24,29,26,31,25,28,27,30,
	23,18,21,19,22,17,20,16,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif

	#if 1
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	0,1,2,3,4,5,6,7,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35,
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif
	.cfg_board_common_setting.	ddr_vddee_setting	=	{0}	,


	.cfg_board_SI_setting_ps[0].	DRAMFreq	=	667	,
	.cfg_board_SI_setting_ps[0].	PllBypassEn	=	0	,
	.cfg_board_SI_setting_ps[0].	training_SequenceCtrl	=	0	,
	.cfg_board_SI_setting_ps[0].	ddr_odt_config	=	DDR_DRAM_ODT_W_CS0_ODT0	,
	.cfg_board_SI_setting_ps[0].	clk_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[0].	cs_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[0].	ac_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_drv_ohm_p	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_drv_ohm_n	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_odt_ohm_p	=	DDR_SOC_DATA_DRV_ODT_120_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_odt_ohm_n	=	DDR_SOC_DATA_DRV_ODT_120_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_data_drv_ohm	=	DDR_DRAM_DDR3_DRV_34_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_data_odt_ohm	=	DDR_DRAM_DDR3_ODT_60_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_data_wr_odt_ohm	=	DDR_DRAM_DDR_WR_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_ac_odt_ohm	=	DDR_DRAM_DDR_AC_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[0].	lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ	,
	.cfg_board_SI_setting_ps[0].	reserve2	=	0	,
	.cfg_board_SI_setting_ps[0].	vref_ac_permil 	=	0	,
	.cfg_board_SI_setting_ps[0].	vref_soc_data_permil 	=	0	,
	.cfg_board_SI_setting_ps[0].	vref_dram_data_permil	=	0	,
	.cfg_board_SI_setting_ps[0].	max_core_timmming_frequency	=	0	,
	.cfg_board_SI_setting_ps[0].	training_phase_parameter	=	{0}	,
	.cfg_board_SI_setting_ps[0]. ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	},//total 36
	  #if 0
	.cfg_board_SI_setting_ps[0]. ac_trace_delay_org = {
	123,124,125,126,127,128,128,128,
	129,128,127,126,125,124,123,122,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #endif

	#if 1
	.cfg_ddr_training_delay_ps[0]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	  } , //total 36
	  #endif
	  #if 0
	.cfg_ddr_training_delay_ps[0]. ac_trace_delay = {
	123,124,0,126,127,0,0,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	  } , //total 36
	  #endif
	  #if 0
	  .cfg_ddr_training_delay_ps[0]. write_dqs_delay = {0,0,0,0,0,0,0,0} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,} ,
	#endif
	  #if 0 //real board
	.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {0,0,0,0,0,0,0,0} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {128,128,128,128,128,128,128,128} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {256,256,256,256,256,256,256,256} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,} ,


	#endif

	  #if 1 //for pxp
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {0,0,0,0,0,0,0,0} ,
	.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {128,128,128,128,128,128,128,128} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {256,256,256,256,256,256,256,256} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,} ,
	.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {128+512,128+512,128+512,128+512,128+512,128+512,128+512,128+512} , //total 8

	#else
	.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {128,128,128,128,128,128,128,128} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,
	64+128,64+128,64+128,64+128,64+128,64+128,64+128,64+128,} ,

	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {1094,1094,1094,1094,1094,1094,1094,1094} , //total 8
	.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {896,896,896,896,896,896,896,896} , //total 8
	#endif
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0]. read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0]. read_dq_bit_delay = {0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[0]. soc_bit_vref = {42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,
	42,42,42,42,42,42,42,42,42,42,
	42,42,42,42,42,58,42,58,42,58,42,58,} , //total 44
	.cfg_ddr_training_delay_ps[0]. dram_bit_vref = {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32} , //total 36
	.cfg_ddr_training_delay_ps[0].	reserve_training_parameter	=	{0}	,

	.cfg_board_SI_setting_ps[1].	DRAMFreq	=	667	,
	.cfg_board_SI_setting_ps[1].	PllBypassEn	=	0	,
	.cfg_board_SI_setting_ps[1].	training_SequenceCtrl	=	0	,
	.cfg_board_SI_setting_ps[1].	ddr_odt_config	=	DDR_DRAM_ODT_W_CS0_ODT0	,
	.cfg_board_SI_setting_ps[1].	clk_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[1].	cs_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[1].	ac_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_drv_ohm_p	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_drv_ohm_n	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_odt_ohm_p	=	DDR_SOC_DATA_DRV_ODT_60_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_odt_ohm_n	=	DDR_SOC_DATA_DRV_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_drv_ohm	=	DDR_DRAM_DDR4_DRV_34_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_odt_ohm	=	DDR_DRAM_DDR4_ODT_60_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_wr_odt_ohm	=	DDR_DRAM_DDR_WR_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_ac_odt_ohm	=	DDR_DRAM_DDR_AC_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[1].	lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ	,
	.cfg_board_SI_setting_ps[1].	reserve2	=	0	,
	.cfg_board_SI_setting_ps[1].	vref_ac_permil 	=	0	,
	.cfg_board_SI_setting_ps[1].	vref_soc_data_permil 	=	0	,
	.cfg_board_SI_setting_ps[1].	vref_dram_data_permil	=	0	,
	.cfg_board_SI_setting_ps[1].	max_core_timmming_frequency	=	0	,
	.cfg_board_SI_setting_ps[1].	training_phase_parameter	=	{0}	,
	.cfg_board_SI_setting_ps[1]. ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #if 0
	.cfg_board_SI_setting_ps[1]. ac_trace_delay_org = {
	123,124,125,126,127,128,128,128,
	129,128,127,126,125,124,123,122,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #endif

	#if 1
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #endif
	  #if 0
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	0,0,0,0,0,0,0,0, //0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,
	  } , //total 36
	  #endif
	.cfg_ddr_training_delay_ps[1]. write_dqs_delay = {0,0,0,0,0,0,0,0} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,
	#if 1
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,} ,
	#endif
	#if 0
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,} ,
	#endif
	#if 0
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64} ,
	//total 72
	#endif
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_gate_delay = {192,192,192,192,192,192,192,192} , //total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[1]. read_dq_bit_delay = {0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[1]. soc_bit_vref = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40} , //total 44
	.cfg_ddr_training_delay_ps[1]. dram_bit_vref = {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32} , //total 36
	.cfg_ddr_training_delay_ps[1].	reserve_training_parameter	=	{0}	,
},
#endif //end for dd3 pxp

#if 0  //for ddr4 pxp remap
//ddr_set_t  ddr_set_t_default=
{
	.cfg_board_common_setting.	timming_magic	=	0	,
	.cfg_board_common_setting.	timming_max_valid_configs	=	sizeof(ddr_set_t_default)/sizeof(ddr_set_t)	,
	.cfg_board_common_setting.	timming_struct_version	=	0	,
	.cfg_board_common_setting.	timming_struct_org_size	=	sizeof(ddr_set_t)	,
	.cfg_board_common_setting.	timming_struct_real_size	=	0	,	//0
	.cfg_board_common_setting.	fast_boot	=	{0}	,
	.cfg_board_common_setting.	ddr_func	=	0	,
	.cfg_board_common_setting.	board_id	=	CONFIG_BOARD_ID_MASK	,
	.cfg_board_common_setting.	DramType	=	CONFIG_DDR_TYPE_DDR4	,
	.cfg_board_common_setting.	dram_rank_config	=	CONFIG_DDR0_32BIT_RANK0_CH0	,
	.cfg_board_common_setting.	DisabledDbyte	=	CONFIG_DISABLE_D32_D63	,
	.cfg_board_common_setting.	dram_cs0_base_add	=	0	,
	.cfg_board_common_setting.	dram_cs1_base_add	=	0	,
	.cfg_board_common_setting.	dram_cs0_size_MB	=	CONFIG_DDR0_SIZE_1024MB	,
	.cfg_board_common_setting.	dram_cs1_size_MB	=	CONFIG_DDR1_SIZE_0MB	,
	.cfg_board_common_setting.	dram_x4x8x16_mode	=	CONFIG_DRAM_MODE_X16	,
	.cfg_board_common_setting.	Is2Ttiming	=	CONFIG_USE_DDR_2T_MODE	,
	.cfg_board_common_setting.	log_level	=	LOG_LEVEL_BASIC	,
	.cfg_board_common_setting.	ddr_rdbi_wr_enable	=	DDR_WRITE_READ_DBI_DISABLE	,
	.cfg_board_common_setting.	pll_ssc_mode	=	DDR_PLL_SSC_DISABLE	,
	.cfg_board_common_setting.	org_tdqs2dq	=	0	,
	.cfg_board_common_setting.	reserve1_test_function	=	{0}	,
	.cfg_board_common_setting.	ddr_dmc_remap	=	DDR_DMC_REMAP_DDR4_32BIT	,
	#if 1  //af409
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	8,	27,	10,	2,	9,	21,	5,	14,	1,	0,	25,	13,	12,	4,	7,	22,	0,	0,	0,	0,	6,	3,	20,	0,	0,	15,	26,	11,
	},
	#endif
	#if 0  //af419
	.cfg_board_common_setting.	ac_pinmux	= {
	0,	0,	0,	1,	2,	3,
	27,	12,	21,	9,	8,	0,	14,	10,	6,	7,	20,	5,	22,	13,	15,	2,	0,	0,	0,	0,	11,	26,	4,	0,	0,	25,	3,	1,
	},
	#endif
	#if 0
	.cfg_board_common_setting.	ac_pinmux	=
	{
	0,	0,	0,	1,	2,	3,
	0,	1,	2,	3,	4,	5,	6,	7,	8,	9,	10,	11,	12,	13,	14,	15,	0,	0,	0,	0,	20,	21,	22,	0,	0,	25,	26,	27,	0
	}	,
	#endif
	.cfg_board_common_setting.	ddr_dqs_swap	=	0	,
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	3,2,0,1,7,6,5,4,
	14,13,12,15,8,9,11,10,
	20,21,22,23,16,17,19,18,
	24,25,28,26,31,30,27,29,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	2,3,1,0,6,7,4,5,
	11,10,9,8,15,14,13,12,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	3,2,0,1,7,6,5,4,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	//1,0,3,2,5,4,7,6,
	#endif
	#if 0
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	2,7,1,5,3,6,0,4,
	10,11,15,13,14,9,8,12,
	24,29,26,31,25,28,27,30,
	23,18,21,19,22,17,20,16,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif

	#if 1
	.cfg_board_common_setting.	ddr_dq_remap	=	{
	0,1,2,3,4,5,6,7,
	8,9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,
	24,25,26,27,28,29,30,31,
	32,33,34,35
	}	,	 //d0-d31 dm0 dm1 dm2 dm3
	#endif
	.cfg_board_common_setting.	ddr_vddee_setting	=	{0}	,


	.cfg_board_SI_setting_ps[0].	DRAMFreq	=	667	,
	.cfg_board_SI_setting_ps[0].	PllBypassEn	=	0	,
	.cfg_board_SI_setting_ps[0].	training_SequenceCtrl	=	0	,
	.cfg_board_SI_setting_ps[0].	ddr_odt_config	=	DDR_DRAM_ODT_W_CS0_ODT0	,
	.cfg_board_SI_setting_ps[0].	clk_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[0].	cs_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[0].	ac_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_drv_ohm_p	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_drv_ohm_n	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_odt_ohm_p	=	DDR_SOC_DATA_DRV_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[0].	soc_data_odt_ohm_n	=	DDR_SOC_DATA_DRV_ODT_120_OHM	, //for pxp dram weak driver model
	.cfg_board_SI_setting_ps[0].	dram_data_drv_ohm	=	DDR_DRAM_DDR4_DRV_34_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_data_odt_ohm	=	DDR_DRAM_DDR4_ODT_60_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_data_wr_odt_ohm	=	DDR_DRAM_DDR_WR_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_ac_odt_ohm	=	DDR_DRAM_DDR_AC_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[0].	dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[0].	lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ	,
	.cfg_board_SI_setting_ps[0].	reserve2	=	0	,
	.cfg_board_SI_setting_ps[0].	vref_ac_permil 	=	0	,
	.cfg_board_SI_setting_ps[0].	vref_soc_data_permil 	=	0	,
	.cfg_board_SI_setting_ps[0].	vref_dram_data_permil	=	0	,
	.cfg_board_SI_setting_ps[0].	max_core_timmming_frequency	=	0	,
	.cfg_board_SI_setting_ps[0].	training_phase_parameter	=	{0}	,
	.cfg_board_SI_setting_ps[0]. ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	  } , //total 36
	  #if 0
	.cfg_board_SI_setting_ps[0]. ac_trace_delay_org = {
	123,124,125,126,127,128,128,128,
	129,128,127,126,125,124,123,122,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #endif

	#if 1
	.cfg_ddr_training_delay_ps[0]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,384,384,384,384,
	384,384,384,384,
	  } , //total 36
	  #endif
	  #if 0
	.cfg_ddr_training_delay_ps[0]. ac_trace_delay = {
	0,0,0,0,0,0,0,0, //0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,
	  } , //total 36
	  #endif
	#if 1
	.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {128,128,128,128,128,128,128,128} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,

	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,
	192,192,192,192,192,192,192,192,} ,
	#endif
	#if 0
	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,} ,
	#endif
	#if 0
	.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {0,0,0,0,0,0,0,0} ,
	.cfg_ddr_training_delay_ps[0]. write_dq_bit_delay = {64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64} ,
	//total 72
	#endif
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {0,0,0,0,0,0,0,0} , //total 8 //edge mode
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0]. read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[0]. read_dq_bit_delay = {0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[0]. soc_bit_vref = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,50,40,50,40,50,40,50} , //total 44
	.cfg_ddr_training_delay_ps[0]. dram_bit_vref = {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32} , //total 36
	.cfg_ddr_training_delay_ps[0].	reserve_training_parameter	=	{0}	,
	//.cfg_ddr_training_delay_ps[0].reserve_training_parameter={((1<<7)|1),},

	.cfg_board_SI_setting_ps[1].	DRAMFreq	=	667	,
	.cfg_board_SI_setting_ps[1].	PllBypassEn	=	0	,
	.cfg_board_SI_setting_ps[1].	training_SequenceCtrl	=	0	,
	.cfg_board_SI_setting_ps[1].	ddr_odt_config	=	DDR_DRAM_ODT_W_CS0_ODT0	,
	.cfg_board_SI_setting_ps[1].	clk_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[1].	cs_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[1].	ac_drv_ohm	=	DDR_SOC_AC_DRV_40_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_drv_ohm_p	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_drv_ohm_n	=	DDR_SOC_DATA_DRV_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_odt_ohm_p	=	DDR_SOC_DATA_DRV_ODT_60_OHM	,
	.cfg_board_SI_setting_ps[1].	soc_data_odt_ohm_n	=	DDR_SOC_DATA_DRV_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_drv_ohm	=	DDR_DRAM_DDR4_DRV_34_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_odt_ohm	=	DDR_DRAM_DDR4_ODT_60_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_wr_odt_ohm	=	DDR_DRAM_DDR_WR_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_ac_odt_ohm	=	DDR_DRAM_DDR_AC_ODT_0_OHM	,
	.cfg_board_SI_setting_ps[1].	dram_data_drv_pull_up_calibration_ohm	=	DDR_DRAM_LPDDR4_ODT_40_OHM	,
	.cfg_board_SI_setting_ps[1].	lpddr4_dram_vout_voltage_range_setting	=	DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ	,
	.cfg_board_SI_setting_ps[1].	reserve2	=	0	,
	.cfg_board_SI_setting_ps[1].	vref_ac_permil 	=	0	,
	.cfg_board_SI_setting_ps[1].	vref_soc_data_permil 	=	0	,
	.cfg_board_SI_setting_ps[1].	vref_dram_data_permil	=	0	,
	.cfg_board_SI_setting_ps[1].	max_core_timmming_frequency	=	0	,
	.cfg_board_SI_setting_ps[1].	training_phase_parameter	=	{0}	,
	.cfg_board_SI_setting_ps[1]. ac_trace_delay_org = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #if 0
	.cfg_board_SI_setting_ps[1]. ac_trace_delay_org = {
	123,124,125,126,127,128,128,128,
	129,128,127,126,125,124,123,122,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #endif

	#if 1
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,128,128,128,128,
	128,128,128,128,
	  } , //total 36
	  #endif
	  #if 0
	.cfg_ddr_training_delay_ps[1]. ac_trace_delay = {
	0,0,0,0,0,0,0,0, //0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,
	  } , //total 36
	  #endif
	.cfg_ddr_training_delay_ps[1]. write_dqs_delay = {0,0,0,0,0,0,0,0} ,
	//.cfg_ddr_training_delay_ps[0]. write_dqs_delay = {32,32,32,32,32,32,32,32} ,
	#if 1
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,
	50,50,50,50,50,50,50,50,} ,
	#endif
	#if 0
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,} ,
	#endif
	#if 0
	.cfg_ddr_training_delay_ps[1]. write_dq_bit_delay = {64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64,
	64,64,64,64,64,64,64,64} ,
	//total 72
	#endif
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {256,256,256,256,256,256,256,256} , //total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_gate_delay = {192,192,192,192,192,192,192,192} , //total 8
	//.cfg_ddr_training_delay_ps[0]. read_dqs_gate_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[1]. read_dqs_delay = {64,64,64,64,64,64,64,64} , //total 8
	.cfg_ddr_training_delay_ps[1]. read_dq_bit_delay = {0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0} , //total 72
	.cfg_ddr_training_delay_ps[1]. soc_bit_vref = {40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40,
	40,40,40,40,40,40,40,40,40,40,40} , //total 44
	.cfg_ddr_training_delay_ps[1]. dram_bit_vref = {32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,
	32,32,32,32,32,32,32,32,32,32,32,
	32,32,32} , //total 36
	.cfg_ddr_training_delay_ps[1].	reserve_training_parameter	=	{0}	,
},
#endif //end for ddr4 pxp remap
};
//ddr timing end

pll_set_t __pll_setting = {
	.cpu_clk				= CPU_CLK / 24 * 24,
#ifdef CONFIG_PXP_EMULATOR
	.pxp					= 1,
#else
	.pxp					= 0,
#endif
	.spi_ctrl				= 0,
	.lCustomerID			= AML_CUSTOMER_ID,
	.log_chl				= 0x3, /* 0x77: all channel enable. 0xFF: with stream info */
	.log_ctrl				= (1<<7) | /* (1<<7), print bl2 log into buffer */
#ifdef CONFIG_SILENT_CONSOLE
							  (1<<6),    /* do not print log buffer */
#else
							  (0<<6),    /* print log buffer before run bl31 */
#endif
.ddr_timming_save_mode 		= 1,
};

ddr_reg_t __ddr_reg[] = {
	/* demo, user defined override register */
	{0xaabbccdd, 0, 0, 0, 0, 0},
	{0x11223344, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0},
};



#define VCCK_VAL				AML_VCCK_INIT_VOLTAGE
#define VDDEE_VAL				AML_VDDEE_INIT_VOLTAGE
/* VCCK PWM table */
#if   (VCCK_VAL == 1039)
	#define VCCK_VAL_REG	0x00000022
#elif (VCCK_VAL == 1029)
	#define VCCK_VAL_REG	0x00010021
#elif (VCCK_VAL == 1019)
	#define VCCK_VAL_REG	0x00020020
#elif (VCCK_VAL == 1009)
	#define VCCK_VAL_REG	0x0003001f
#elif (VCCK_VAL == 999)
	#define VCCK_VAL_REG	0x0004001e
#elif (VCCK_VAL == 989)
	#define VCCK_VAL_REG	0x0005001d
#elif (VCCK_VAL == 979)
	#define VCCK_VAL_REG	0x0006001c
#elif (VCCK_VAL == 969)
	#define VCCK_VAL_REG	0x0007001b
#elif (VCCK_VAL == 959)
	#define VCCK_VAL_REG	0x0008001a
#elif (VCCK_VAL == 949)
	#define VCCK_VAL_REG	0x00090019
#elif (VCCK_VAL == 939)
	#define VCCK_VAL_REG	0x000a0018
#elif (VCCK_VAL == 929)
	#define VCCK_VAL_REG	0x000b0017
#elif (VCCK_VAL == 919)
	#define VCCK_VAL_REG	0x000c0016
#elif (VCCK_VAL == 909)
	#define VCCK_VAL_REG	0x000d0015
#elif (VCCK_VAL == 899)
	#define VCCK_VAL_REG	0x000e0014
#elif (VCCK_VAL == 889)
	#define VCCK_VAL_REG	0x000f0013
#elif (VCCK_VAL == 879)
	#define VCCK_VAL_REG	0x00100012
#elif (VCCK_VAL == 869)
	#define VCCK_VAL_REG	0x00110011
#elif (VCCK_VAL == 859)
	#define VCCK_VAL_REG	0x00120010
#elif (VCCK_VAL == 849)
	#define VCCK_VAL_REG	0x0013000f
#elif (VCCK_VAL == 839)
	#define VCCK_VAL_REG	0x0014000e
#elif (VCCK_VAL == 829)
	#define VCCK_VAL_REG	0x0015000d
#elif (VCCK_VAL == 819)
	#define VCCK_VAL_REG	0x0016000c
#elif (VCCK_VAL == 809)
	#define VCCK_VAL_REG	0x0017000b
#elif (VCCK_VAL == 799)
	#define VCCK_VAL_REG	0x0018000a
#elif (VCCK_VAL == 789)
	#define VCCK_VAL_REG	0x00190009
#elif (VCCK_VAL == 779)
	#define VCCK_VAL_REG	0x001a0008
#elif (VCCK_VAL == 769)
	#define VCCK_VAL_REG	0x001b0007
#elif (VCCK_VAL == 759)
	#define VCCK_VAL_REG	0x001c0006
#elif (VCCK_VAL == 749)
	#define VCCK_VAL_REG	0x001d0005
#elif (VCCK_VAL == 739)
	#define VCCK_VAL_REG	0x001e0004
#elif (VCCK_VAL == 729)
	#define VCCK_VAL_REG	0x001f0003
#elif (VCCK_VAL == 719)
	#define VCCK_VAL_REG	0x00200002
#elif (VCCK_VAL == 709)
	#define VCCK_VAL_REG	0x00210001
#elif (VCCK_VAL == 699)
	#define VCCK_VAL_REG	0x00220000
#else
	#error "VCCK val out of range\n"
#endif

/* VDDEE_VAL_REG: VDDEE PWM table  0.69v-0.89v*/
#if    (VDDEE_VAL == 711)
	#define VDDEE_VAL_REG	0x120000
#elif (VDDEE_VAL == 721)
	#define VDDEE_VAL_REG	0x110001
#elif (VDDEE_VAL == 731)
	#define VDDEE_VAL_REG	0x100002
#elif (VDDEE_VAL == 741)
	#define VDDEE_VAL_REG	0xf0003
#elif (VDDEE_VAL == 751)
	#define VDDEE_VAL_REG	0xe0004
#elif (VDDEE_VAL == 761)
	#define VDDEE_VAL_REG	0xd0005
#elif (VDDEE_VAL == 771)
	#define VDDEE_VAL_REG	0xc0006
#elif (VDDEE_VAL == 781)
	#define VDDEE_VAL_REG	0xb0007
#elif (VDDEE_VAL == 791)
	#define VDDEE_VAL_REG	0xa0008
#elif (VDDEE_VAL == 801)
	#define VDDEE_VAL_REG	0x90009
#elif (VDDEE_VAL == 811)
	#define VDDEE_VAL_REG	0x8000a
#elif (VDDEE_VAL == 821)
	#define VDDEE_VAL_REG	0x7000b
#elif (VDDEE_VAL == 831)
	#define VDDEE_VAL_REG	0x6000c
#elif (VDDEE_VAL == 841)
	#define VDDEE_VAL_REG	0x5000d
#elif (VDDEE_VAL == 851)
	#define VDDEE_VAL_REG	0x4000e
#elif (VDDEE_VAL == 861)
	#define VDDEE_VAL_REG	0x3000f
#elif (VDDEE_VAL == 871)
	#define VDDEE_VAL_REG	0x20010
#elif (VDDEE_VAL == 881)
	#define VDDEE_VAL_REG	0x10011
#elif (VDDEE_VAL == 891)
	#define VDDEE_VAL_REG	0x12
#else
	#error "VDDEE val out of range\n"
#endif

/* for PWM use */
/*
 * GPIOE_0   PWM_A    VDDEE_PWM
 *
 * GPIOE_1   PWM_B    VCCK_PWM
 */
/* PWM driver check http://scgit.amlogic.com:8080/#/c/38093/ */
#define PADCTRL_PIN_MUX_REG2   	((0x0002  << 2) + 0xfe000400)
#define PADCTRL_GPIOE_DS        ((0x0035  << 2) + 0xfe000400)

/* pwm clock and pwm controller */
#define CLKTREE_PWM_CLK_AB_CTRL ((0x0031  << 2) + 0xfe000800)
#define PWMAB_PWM_A            	((0x0000  << 2) + 0xfe002400)
#define PWMAB_PWM_B             ((0x0001  << 2) + 0xfe002400)
#define PWMAB_MISC_REG_AB       ((0x0002  << 2) + 0xfe002400)

bl2_reg_t __bl2_reg[] = {
	/* demo, user defined override register */
	{0,			0,            		0xffffffff,   0, 0, 0},
	{PWMAB_PWM_A,		VDDEE_VAL_REG,  	0xffffffff,	0, BL2_INIT_STAGE_1, 0},
	{PWMAB_PWM_B,		VCCK_VAL_REG,  		0xffffffff,	0, BL2_INIT_STAGE_1, 0},
	{PWMAB_MISC_REG_AB,	0x3 << 0, 		0x3, 		0, BL2_INIT_STAGE_1, 0},
	/* enable vddcpu dc-dc, set GPIOD_10 high */
	{PADCTRL_GPIOD_OEN,	0x0 << 10, 		0x1 << 10, 	0, BL2_INIT_STAGE_1, 0},
	{PADCTRL_GPIOD_O,	0x1 << 10, 		0x1 << 10, 	0, BL2_INIT_STAGE_1, 0},
	/* set pwm A and pwm B clock rate to 24M, enable them */
	{CLKTREE_PWM_CLK_AB_CTRL,1 << 8 | 1 << 24 , 	0xffffffff, 	0, BL2_INIT_STAGE_1, 0},
	/* set GPIOE_0 GPIOE_1 drive strength to 3*/
	{PADCTRL_GPIOE_DS,	0xf, 			0xf,		0, BL2_INIT_STAGE_1, 0},
	{PADCTRL_PIN_MUX_REG2,	0x3,			0xf,		0, BL2_INIT_STAGE_1, 0},
	{PADCTRL_PIN_MUX_REG2,	0x3 << 4,		0xf << 4,	0, BL2_INIT_STAGE_1, 0},
};
