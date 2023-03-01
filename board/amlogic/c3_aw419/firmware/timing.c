// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <asm/arch/secure_apb.h>
#include <asm/arch/timing.h>
#include <asm/arch/ddr_define.h>

/* board clk defines */
#define CPU_CLK                                 1512
#define DSU_CLK                                 1200

//bit 6 adc_channel bit 0-5 adc value,chan 3 value 8 is layer 2
#define DDR_ID_ACS_ADC   ((3 << 6) | (8))

#define DDR_RESV_CHECK_ID_ENABLE  0Xfe
#define SAR_ADC_DDR_ID_BASE   0
#define SAR_ADC_DDR_ID_STEP   80
#define CARMEL_BOARD_1G_1G_ADC_ID   \
	SAR_ADC_DDR_ID_BASE + SAR_ADC_DDR_ID_STEP	//85  0-125 step 0
#define CARMEL_BOARD_2G_1G_ADC_ID   \
	SAR_ADC_DDR_ID_BASE + SAR_ADC_DDR_ID_STEP + SAR_ADC_DDR_ID_STEP	//167 126-200 step 1
#define DDR_TIMMING_OFFSET(X)  \
	(unsigned int)(unsigned long)(&(((ddr_set_ps0_only_t *)(0))->X))
#define DDR_TIMMING_OFFSET_SIZE(X) sizeof(((ddr_set_ps0_only_t *)(0))->X)
#define DDR_TIMMING_TUNE_TIMMING0(DDR_ID, PARA, VALUE)  \
	{ DDR_ID, DDR_TIMMING_OFFSET(PARA), \
	VALUE, DDR_TIMMING_OFFSET_SIZE(PARA), 0, DDR_RESV_CHECK_ID_ENABLE }
#define DDR_TIMMING_TUNE_TIMMING1(DDR_ID, PARA, VALUE) \
	{ DDR_ID, sizeof(((ddr_set_ps0_only_t) + DDR_TIMMING_OFFSET(PARA), \
	VALUE, DDR_TIMMING_OFFSET_SIZE(PARA), 0, DDR_RESV_CHECK_ID_ENABLE }

//bit24-31 define ID and size
#define DDR_ID_FROM_EFUSE  (0Xff << 24)
#define DDR_ID_FROM_ADC  (0Xfeu << 24)
#define DDR_ID_FROM_GPIO_CONFIG1  (0Xfd << 24)
#define DDR_ID_START_MASK  (0XFFDDCCBB)

#define DDR_ADC_CH0  (0X0 << 6)
#define DDR_ADC_CH1  (0X1 << 6)
#define DDR_ADC_CH2  (0X2 << 6)
#define DDR_ADC_CH3  (0X3 << 6)

#define DDR_ADC_VALUE0  (0X0 << 0)
#define DDR_ADC_VALUE1  (0X1 << 0)
#define DDR_ADC_VALUE2  (0X2 << 0)
#define DDR_ADC_VALUE3  (0X3 << 0)
#define DDR_ADC_VALUE4  (0X4 << 0)
#define DDR_ADC_VALUE5  (0X5 << 0)
#define DDR_ADC_VALUE6  (0X6 << 0)
#define DDR_ADC_VALUE7  (0X7 << 0)
#define DDR_ADC_VALUE8  (0X8 << 0)
#define DDR_ADC_VALUE9  (0X9 << 0)
#define DDR_ADC_VALUE10  (0Xa << 0)
#define DDR_ADC_VALUE11  (0Xb << 0)
#define DDR_ADC_VALUE12  (0Xc << 0)
#define DDR_ADC_VALUE13 (0Xd << 0)
#define DDR_ADC_VALUE14  (0Xe << 0)
#define DDR_ADC_VALUE15  (0Xf << 0)

typedef struct ddr_para_data {
	/*bit0-23 ddr_id value,bit 24-31 ddr_id source,
	 * 0xfe source from adc, 0xfd source from gpio_default_config
	 */
	//start from    DDR_ID_START_MASK,ddr_id;

    //bit 0-15 parameter offset value,bit16-23 overrid size,bit24-31 mux ddr_id source
	//reg_offset
	//unsigned int  reg_offset;
	//unsigned int  value;

	//bit0-15 only support data size =1byte or 2bytes,no support int value
	uint32_t value:16;  //bit0-15
	uint32_t reg_offset:12;	//bit16-27
	uint32_t data_size:4;	//bit28-31 if data size =15,then  will mean DDR_ID start

} ddr_para_data_t;

typedef struct ddr_para_data_start {
	uint32_t id_value:24;	//bit0-23  efuse id or ddr id
	//uint32_t      id_adc_ch : 2;//bit6-7
	uint32_t id_src_from:8;	//bit24-31 ddr id from adc or gpio
} ddr_para_data_start_t;
/*#define DDR_TIMMING_OFFSET(X)  \
 *	(unsigned int)(unsigned long)(&(((ddr_set_ps0_only_t *)(0))->X))
 *#define DDR_TIMMING_OFFSET_SIZE(X) sizeof(((ddr_set_ps0_only_t *)(0))->X)
 *#define DDR_TIMMING_TUNE_TIMMING0(DDR_ID, PARA, VALUE) \
 *	{ DDR_ID, DDR_TIMMING_OFFSET(PARA), VALUE, DDR_TIMMING_OFFSET_SIZE(PARA), \
 *	0, DDR_RESV_CHECK_ID_ENABLE }
 *#define DDR_TIMMING_TUNE_TIMMING1(DDR_ID, PARA, VALUE)  \
 * { DDR_ID, sizeof(((ddr_set_ps0_only_t)+ DDR_TIMMING_OFFSET(PARA), VALUE, \
 *  DDR_TIMMING_OFFSET_SIZE(PARA), 0, DDR_RESV_CHECK_ID_ENABLE }
 */
#define DDR_TIMMING_TUNE_TIMMING0_F(PARA, VALUE)  \
	(((DDR_TIMMING_OFFSET(PARA)) << 16) | ((DDR_TIMMING_OFFSET_SIZE(PARA)) << 28) | VALUE)
#define DDR_TIMMING_TUNE_TIMMING1_F(PARA, VALUE) \
	(((sizeof(ddr_set_ps0_only_t) + DDR_TIMMING_OFFSET(PARA)) << 16) | \
	((DDR_TIMMING_OFFSET_SIZE(PARA)) << 28) | VALUE)

#define DDR_TIMMING_TUNE_START(id_src_from, id_adc_ch, id_value) \
	(id_src_from | id_adc_ch | id_value)
#define DDR_TIMMING_TUNE_STRUCT_SIZE(a)  sizeof(a)

#if 1
uint32_t __bl2_ddr_reg_data[] __attribute__ ((section(".ddr_2acs_data"))) = {
	DDR_TIMMING_TUNE_START(DDR_ID_FROM_ADC, DDR_ADC_CH1, DDR_ADC_VALUE1),
	//data start
	DDR_TIMMING_TUNE_TIMMING0_F(cfg_board_common_setting.Is2Ttiming, CONFIG_USE_DDR_2T_MODE),
};

//_ddr_para_2nd_setting

uint32_t __ddr_parameter_reg_index[] __attribute__ ((section(".ddr_2acs_index"))) = {
	DDR_ID_START_MASK,
	DDR_TIMMING_TUNE_STRUCT_SIZE(__bl2_ddr_reg_data),
	//0,
};
#endif

#define C3_DDR4_1RANK 1

ddr_set_ps0_only_t __ddr_setting[] __attribute__ ((section(".ddr_param"))) = {
#ifdef C3_DDR4_1RANK
	{
	//timing_config,4layer 2pcs ddr4 rank0, aw419.
	.cfg_board_common_setting.timming_magic = 0,
	.cfg_board_common_setting.timming_max_valid_configs =
	 sizeof(__ddr_setting[0]) / sizeof(ddr_set_ps0_only_t),
	.cfg_board_common_setting.timming_struct_version = 0,
	.cfg_board_common_setting.timming_struct_org_size = sizeof(ddr_set_ps0_only_t),
	.cfg_board_common_setting.timming_struct_real_size = 0,
	.cfg_board_common_setting.fast_boot = { 0x1, 0, 0, 0},//{ 0, 0, (1 << 3) | (4)},
	.cfg_board_common_setting.ddr_func = DDR_FUNC | DDR_FUNC_ENABLE_DDR_ID |
		DDR_FUNC_CONFIG_DFE_FUNCTION,
	//.cfg_board_common_setting.ddr_func = DDR_FUNC |
	//	DDR_FUNC_CONFIG_DFE_FUNCTION,
	.cfg_board_common_setting.board_id = CONFIG_BOARD_ID_MASK,
	.cfg_board_common_setting.DramType = CONFIG_DDR_TYPE_DDR4,
	.cfg_board_common_setting.dram_rank_config = CONFIG_DDR0_32BIT_RANK0_CH0,
	.cfg_board_common_setting.DisabledDbyte = CONFIG_DISABLE_D32_D63,
	.cfg_board_common_setting.dram_cs0_base_add = 0,
	.cfg_board_common_setting.dram_cs1_base_add = 0,
	.cfg_board_common_setting.dram_cs0_size_MB = CONFIG_DDR0_SIZE_2048MB,
	.cfg_board_common_setting.dram_cs1_size_MB = CONFIG_DDR1_SIZE_0MB,
	.cfg_board_common_setting.dram_x4x8x16_mode = CONFIG_DRAM_MODE_X16,
	.cfg_board_common_setting.Is2Ttiming = CONFIG_USE_DDR_2T_MODE,
	.cfg_board_common_setting.log_level = LOG_LEVEL_BASIC,
	.cfg_board_common_setting.ddr_rdbi_wr_enable = DDR_WRITE_READ_DBI_DISABLE,

	//center_ssc_1000ppm,//SSC_DISABLE,(1 << 20) | (0 << 8) | (2 << 4) | 0,
	.cfg_board_common_setting.pll_ssc_mode = (1 << 20) | (1 << 8) | (2 << 4) | 0,
	.cfg_board_common_setting.org_tdqs2dq = 0,
	.cfg_board_common_setting.reserve1_test_function = {0},
	.cfg_board_common_setting.ddr_dmc_remap = DDR_DMC_REMAP_DDR4_32BIT,

	.cfg_board_common_setting.ac_pinmux = {
		0, 0, 0, 1, 2, 3,
		27, 10, 25, 5, 28, 11, 24,
		0, 26, 7, 4, 21, 2, 20, 8,
		13, 0, 0, 0, 0, 6, 12, 3, 0, 0, 9, 1, 23, 0
	},
	.cfg_board_common_setting.ddr_dqs_swap = 0,
	.cfg_board_common_setting.ddr_dq_remap = {
		0, 1, 2, 3, 4,  5, 6, 7,
		8,  9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35
	},  //d0-d31 dm0 dm1 dm2 dm3
	.cfg_board_common_setting.ddr_vddee_setting = {0},
	.cfg_board_SI_setting_ps.DRAMFreq = 1320,
	.cfg_board_SI_setting_ps.PllBypassEn = 0,
	.cfg_board_SI_setting_ps.training_SequenceCtrl = 0,
	.cfg_board_SI_setting_ps.ddr_odt_config = DDR_DRAM_ODT_W_CS0_ODT0,
	.cfg_board_SI_setting_ps.clk_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps.cs_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps.ac_drv_ohm = DDR_SOC_AC_DRV_40_OHM,
	.cfg_board_SI_setting_ps.soc_data_drv_ohm_p = DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps.soc_data_drv_ohm_n = DDR_SOC_DATA_DRV_ODT_40_OHM,
	.cfg_board_SI_setting_ps.soc_data_odt_ohm_p = DDR_SOC_DATA_DRV_ODT_60_OHM,
	.cfg_board_SI_setting_ps.soc_data_odt_ohm_n = DDR_SOC_DATA_DRV_ODT_0_OHM,
	.cfg_board_SI_setting_ps.dram_data_drv_ohm = DDR_DRAM_DDR4_DRV_34_OHM,
	.cfg_board_SI_setting_ps.dram_data_odt_ohm = DDR_DRAM_DDR4_ODT_60_OHM,
	.cfg_board_SI_setting_ps.dram_data_wr_odt_ohm = DDR_DRAM_DDR_WR_ODT_0_OHM,
	.cfg_board_SI_setting_ps.dram_ac_odt_ohm = DDR_DRAM_DDR_AC_ODT_0_OHM,
	.cfg_board_SI_setting_ps.dram_data_drv_pull_up_calibration_ohm =
			DDR_DRAM_LPDDR4_ODT_40_OHM,
	.cfg_board_SI_setting_ps.lpddr4_dram_vout_voltage_range_setting =
			DDR_DRAM_LPDDR4_OUTPUT_1_3_VDDQ,
	.cfg_board_SI_setting_ps.dfe_offset = 0,
	.cfg_board_SI_setting_ps.vref_ac_permil = 0,
	.cfg_board_SI_setting_ps.vref_soc_data_permil = 680,
	.cfg_board_SI_setting_ps.vref_dram_data_permil = 700,
	.cfg_board_SI_setting_ps.max_core_timmming_frequency = 0,
	.cfg_board_SI_setting_ps.training_phase_parameter = {0},
	.cfg_board_SI_setting_ps.ac_trace_delay_org = {
		128, 128, 128 + 40, 128, 128, 128, 128, 128,
		384, 384, 384,      384, 384, 384, 384, 384,
		384, 384, 384,      384, 384, 384, 384, 384,
		384, 384, 384,      384, 384, 384, 384, 384,
		384, 384, 384,      384,
	},
	//total 36
	.cfg_ddr_training_delay_ps.ac_trace_delay = {
		128, 128, 128 + 40, 128, 128, 128, 128, 384,
		384, 384, 384, 384, 384, 384, 384, 384,
		384, 384, 384, 384, 384, 384, 384, 384,
		384, 384, 384, 384, 384, 384, 384, 384,
		384, 384, 384, 384,
		},

	.cfg_ddr_training_delay_ps.write_dqs_delay[0] = 0x00000164,// 356
	.cfg_ddr_training_delay_ps.write_dqs_delay[1] = 0x00000169,// 361
	.cfg_ddr_training_delay_ps.write_dqs_delay[2] = 0x0000016e,// 366
	.cfg_ddr_training_delay_ps.write_dqs_delay[3] = 0x00000169,// 361
	.cfg_ddr_training_delay_ps.write_dqs_delay[4] = 0x00000155,// 341
	.cfg_ddr_training_delay_ps.write_dqs_delay[5] = 0x00000155,// 341
	.cfg_ddr_training_delay_ps.write_dqs_delay[6] = 0x00000155,// 341
	.cfg_ddr_training_delay_ps.write_dqs_delay[7] = 0x00000155,// 341
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[0] = 0x000001b1,// 433
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[1] = 0x000001a3,// 419
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[2] = 0x000001b1,// 433
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[3] = 0x0000019a,// 410
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[4] = 0x000001b9,// 441
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[5] = 0x0000019f,// 415
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[6] = 0x000001a1,// 417
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[7] = 0x000001a3,// 419
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[8] = 0x000001a7,// 423
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[9] = 0x000001b9,// 441
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[10] = 0x0000018e,// 398
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[11] = 0x000001bc,// 444
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[12] = 0x00000191,// 401
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[13] = 0x000001b5,// 437
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[14] = 0x0000019f,// 415
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[15] = 0x000001b0,// 432
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[16] = 0x0000019f,// 415
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[17] = 0x000001a6,// 422
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[18] = 0x000001af,// 431
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[19] = 0x00000192,// 402
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[20] = 0x000001be,// 446
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[21] = 0x00000191,// 401
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[22] = 0x000001bf,// 447
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[23] = 0x000001a1,// 417
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[24] = 0x000001a8,// 424
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[25] = 0x0000018d,// 397
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[26] = 0x000001a4,// 420
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[27] = 0x000001b6,// 438
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[28] = 0x0000019f,// 415
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[29] = 0x000001c1,// 449
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[30] = 0x000001a0,// 416
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[31] = 0x000001a0,// 416
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[32] = 0x0000018b,// 395
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[33] = 0x000001a1,// 417
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[34] = 0x00000186,// 390
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[35] = 0x000001a1,// 417
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[36] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[37] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[38] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[39] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[40] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[41] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[42] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[43] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[44] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[45] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[46] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[47] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[48] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[49] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[50] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[51] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[52] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[53] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[54] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[55] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[56] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[57] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[58] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[59] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[60] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[61] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[62] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[63] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[64] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[65] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[66] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[67] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[68] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[69] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[70] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.write_dq_bit_delay[71] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[0] = 0x00000285,// 645
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[1] = 0x00000286,// 646
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[2] = 0x0000028c,// 652
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[3] = 0x0000028e,// 654
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[4] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[5] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[6] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_gate_delay[7] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_delay[0] = 0x00000075,// 117
	.cfg_ddr_training_delay_ps.read_dqs_delay[1] = 0x0000008a,// 138
	.cfg_ddr_training_delay_ps.read_dqs_delay[2] = 0x00000085,// 133
	.cfg_ddr_training_delay_ps.read_dqs_delay[3] = 0x0000007f,// 127
	.cfg_ddr_training_delay_ps.read_dqs_delay[4] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_delay[5] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_delay[6] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dqs_delay[7] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[0] = 0x00000042,// 66
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[1] = 0x00000035,// 53
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[2] = 0x0000003e,// 62
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[3] = 0x00000032,// 50
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[4] = 0x0000005c,// 92
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[5] = 0x00000036,// 54
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[6] = 0x00000040,// 64
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[7] = 0x00000033,// 51
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[8] = 0x0000003d,// 61
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[9] = 0x0000005a,// 90
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[10] = 0x00000034,// 52
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[11] = 0x0000005d,// 93
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[12] = 0x00000035,// 53
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[13] = 0x0000005a,// 90
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[14] = 0x00000039,// 57
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[15] = 0x00000058,// 88
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[16] = 0x0000003c,// 60
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[17] = 0x00000048,// 72
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[18] = 0x00000051,// 81
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[19] = 0x00000031,// 49
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[20] = 0x00000062,// 98
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[21] = 0x0000002e,// 46
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[22] = 0x00000061,// 97
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[23] = 0x00000039,// 57
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[24] = 0x00000057,// 87
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[25] = 0x00000030,// 48
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[26] = 0x00000046,// 70
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[27] = 0x00000058,// 88
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[28] = 0x00000039,// 57
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[29] = 0x00000060,// 96
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[30] = 0x00000035,// 53
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[31] = 0x00000047,// 71
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[32] = 0x0000002d,// 45
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[33] = 0x00000047,// 71
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[34] = 0x0000002e,// 46
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[35] = 0x00000041,// 65
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[36] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[37] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[38] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[39] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[40] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[41] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[42] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[43] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[44] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[45] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[46] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[47] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[48] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[49] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[50] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[51] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[52] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[53] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[54] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[55] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[56] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[57] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[58] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[59] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[60] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[61] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[62] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[63] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[64] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[65] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[66] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[67] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[68] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[69] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[70] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.read_dq_bit_delay[71] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref[0] = 0x00000021,// 33
	.cfg_ddr_training_delay_ps.soc_bit_vref[1] = 0x0000001f,// 31
	.cfg_ddr_training_delay_ps.soc_bit_vref[2] = 0x0000001f,// 31
	.cfg_ddr_training_delay_ps.soc_bit_vref[3] = 0x00000024,// 36
	.cfg_ddr_training_delay_ps.soc_bit_vref[4] = 0x0000001f,// 31
	.cfg_ddr_training_delay_ps.soc_bit_vref[5] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[6] = 0x00000021,// 33
	.cfg_ddr_training_delay_ps.soc_bit_vref[7] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[8] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[9] = 0x00000021,// 33
	.cfg_ddr_training_delay_ps.soc_bit_vref[10] = 0x00000023,// 35
	.cfg_ddr_training_delay_ps.soc_bit_vref[11] = 0x0000001d,// 29
	.cfg_ddr_training_delay_ps.soc_bit_vref[12] = 0x00000023,// 35
	.cfg_ddr_training_delay_ps.soc_bit_vref[13] = 0x0000001d,// 29
	.cfg_ddr_training_delay_ps.soc_bit_vref[14] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[15] = 0x00000023,// 35
	.cfg_ddr_training_delay_ps.soc_bit_vref[16] = 0x0000001f,// 31
	.cfg_ddr_training_delay_ps.soc_bit_vref[17] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[18] = 0x0000001d,// 29
	.cfg_ddr_training_delay_ps.soc_bit_vref[19] = 0x00000025,// 37
	.cfg_ddr_training_delay_ps.soc_bit_vref[20] = 0x0000001e,// 30
	.cfg_ddr_training_delay_ps.soc_bit_vref[21] = 0x00000024,// 36
	.cfg_ddr_training_delay_ps.soc_bit_vref[22] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[23] = 0x0000001c,// 28
	.cfg_ddr_training_delay_ps.soc_bit_vref[24] = 0x0000001d,// 29
	.cfg_ddr_training_delay_ps.soc_bit_vref[25] = 0x00000022,// 34
	.cfg_ddr_training_delay_ps.soc_bit_vref[26] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[27] = 0x00000021,// 33
	.cfg_ddr_training_delay_ps.soc_bit_vref[28] = 0x0000001f,// 31
	.cfg_ddr_training_delay_ps.soc_bit_vref[29] = 0x0000001e,// 30
	.cfg_ddr_training_delay_ps.soc_bit_vref[30] = 0x00000021,// 33
	.cfg_ddr_training_delay_ps.soc_bit_vref[31] = 0x00000022,// 34
	.cfg_ddr_training_delay_ps.soc_bit_vref[32] = 0x00000024,// 36
	.cfg_ddr_training_delay_ps.soc_bit_vref[33] = 0x00000022,// 34
	.cfg_ddr_training_delay_ps.soc_bit_vref[34] = 0x00000021,// 33
	.cfg_ddr_training_delay_ps.soc_bit_vref[35] = 0x00000020,// 32
	.cfg_ddr_training_delay_ps.soc_bit_vref[36] = 0x00000026,// 38
	.cfg_ddr_training_delay_ps.soc_bit_vref[37] = 0x0000002f,// 47
	.cfg_ddr_training_delay_ps.soc_bit_vref[38] = 0x00000026,// 38
	.cfg_ddr_training_delay_ps.soc_bit_vref[39] = 0x0000002f,// 47
	.cfg_ddr_training_delay_ps.soc_bit_vref[40] = 0x00000026,// 38
	.cfg_ddr_training_delay_ps.soc_bit_vref[41] = 0x0000002b,// 43
	.cfg_ddr_training_delay_ps.soc_bit_vref[42] = 0x00000026,// 38
	.cfg_ddr_training_delay_ps.soc_bit_vref[43] = 0x0000002f,// 47
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[0] = 0x0000002d,// 45
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[1] = 0x0000002b,// 43
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[2] = 0x0000002b,// 43
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[3] = 0x00000030,// 48
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[4] = 0x0000002b,// 43
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[5] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[6] = 0x0000002d,// 45
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[7] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[8] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[9] = 0x0000002d,// 45
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[10] = 0x0000002f,// 47
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[11] = 0x00000029,// 41
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[12] = 0x0000002f,// 47
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[13] = 0x00000029,// 41
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[14] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[15] = 0x0000002f,// 47
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[16] = 0x0000002b,// 43
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[17] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[18] = 0x00000029,// 41
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[19] = 0x00000031,// 49
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[20] = 0x0000002a,// 42
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[21] = 0x00000030,// 48
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[22] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[23] = 0x00000028,// 40
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[24] = 0x00000029,// 41
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[25] = 0x0000002e,// 46
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[26] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[27] = 0x0000002d,// 45
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[28] = 0x0000002b,// 43
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[29] = 0x0000002a,// 42
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[30] = 0x0000002d,// 45
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[31] = 0x0000002e,// 46
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[32] = 0x00000030,// 48
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[33] = 0x0000002e,// 46
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[34] = 0x0000002d,// 45
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[35] = 0x0000002c,// 44
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[36] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[37] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[38] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[39] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[40] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[41] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[42] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.soc_bit_vref_dac1[43] = 0x00000000,// 0
	.cfg_ddr_training_delay_ps.dram_bit_vref = {
		0,  32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32, 32, 32, 32, 32,
		32, 32, 32, 32
	},
//total 36
// #if 1
	.cfg_ddr_training_delay_ps.reserve_training_parameter = {
		//cs0 write dqs,lane0-lane3
		(0 << 7) | 5, (0 << 7) | 0, (0 << 7) | 5, (0 << 7) | 0,
		//(0 << 7) | 0, (0 << 7) | 0, (0 << 7) | 5, (0 << 7) | 5,
		//cs1 write dqs,lane0-lane3
		(0 << 7) | 0, (0 << 7) | 0, (0 << 7) | 0, (0 << 7) | 0,
		//cs0 read dqs,lane0-lane3
		(1 << 7) | 15, (1 << 7) | 15, (1 << 7) | 20, (1 << 7) | 20,
		//(0 << 7) | 11, (0 << 7) | 15, (0 << 7) | 20, (0 << 7) | 18,
		//cs1 read dqs,lane0-lane3
		(0 << 7) | 0, (0 << 7) | 0, (0 << 7) | 0, (0 << 7) | 0,
	},
// #endif

// .cfg_ddr_training_delay_ps.reserve_training_parameter[0] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[1] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[2] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[3] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[4] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[5] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[6] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[7] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[8] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[9] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[10] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[11] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[12] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[13] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[14] = 0x00000000,// 0
// .cfg_ddr_training_delay_ps.reserve_training_parameter[15] = 0x00000000,// 0
},
#endif
};

board_clk_set_t __board_clk_setting
__attribute__ ((section(".clk_param"))) = {
	/* clock settings for bl2 */
	.cpu_clk	= CPU_CLK / 24 * 24,
	.dsu_clk	= DSU_CLK / 24 * 24,
#ifdef CONFIG_PXP_DDR
	.pxp = 1,
#else
	.pxp = 0,
#endif
	.low_console_baud = CONFIG_LOW_CONSOLE_BAUD,
};

#define VCCK_VAL                                AML_VCCK_INIT_VOLTAGE
#define VDDEE_VAL                               AML_VDDEE_INIT_VOLTAGE
/* VCCK PWM table */
#if   (VCCK_VAL == 1040)
#define VCCK_VAL_REG    0x00000022
#elif (VCCK_VAL == 1030)
#define VCCK_VAL_REG    0x00010021
#elif (VCCK_VAL == 1020)
#define VCCK_VAL_REG    0x00020020
#elif (VCCK_VAL == 1010)
#define VCCK_VAL_REG    0x0003001f
#elif (VCCK_VAL == 1000)
#define VCCK_VAL_REG    0x0004001e
#elif (VCCK_VAL == 990)
#define VCCK_VAL_REG    0x0005001d
#elif (VCCK_VAL == 980)
#define VCCK_VAL_REG    0x0006001c
#elif (VCCK_VAL == 970)
#define VCCK_VAL_REG    0x0007001b
#elif (VCCK_VAL == 960)
#define VCCK_VAL_REG    0x0008001a
#elif (VCCK_VAL == 950)
#define VCCK_VAL_REG    0x00090019
#elif (VCCK_VAL == 940)
#define VCCK_VAL_REG    0x000a0018
#elif (VCCK_VAL == 930)
#define VCCK_VAL_REG    0x000b0017
#elif (VCCK_VAL == 920)
#define VCCK_VAL_REG    0x000c0016
#elif (VCCK_VAL == 910)
#define VCCK_VAL_REG    0x000d0015
#elif (VCCK_VAL == 900)
#define VCCK_VAL_REG    0x000e0014
#elif (VCCK_VAL == 890)
#define VCCK_VAL_REG    0x000f0013
#elif (VCCK_VAL == 880)
#define VCCK_VAL_REG    0x00100012
#elif (VCCK_VAL == 870)
#define VCCK_VAL_REG    0x00110011
#elif (VCCK_VAL == 860)
#define VCCK_VAL_REG    0x00120010
#elif (VCCK_VAL == 850)
#define VCCK_VAL_REG    0x0013000f
#elif (VCCK_VAL == 840)
#define VCCK_VAL_REG    0x0014000e
#elif (VCCK_VAL == 830)
#define VCCK_VAL_REG    0x0015000d
#elif (VCCK_VAL == 820)
#define VCCK_VAL_REG    0x0016000c
#elif (VCCK_VAL == 810)
#define VCCK_VAL_REG    0x0017000b
#elif (VCCK_VAL == 800)
#define VCCK_VAL_REG    0x0018000a
#elif (VCCK_VAL == 790)
#define VCCK_VAL_REG    0x00190009
#elif (VCCK_VAL == 780)
#define VCCK_VAL_REG    0x001a0008
#elif (VCCK_VAL == 770)
#define VCCK_VAL_REG    0x001b0007
#elif (VCCK_VAL == 760)
#define VCCK_VAL_REG    0x001c0006
#elif (VCCK_VAL == 750)
#define VCCK_VAL_REG    0x001d0005
#elif (VCCK_VAL == 740)
#define VCCK_VAL_REG    0x001e0004
#elif (VCCK_VAL == 730)
#define VCCK_VAL_REG    0x001f0003
#elif (VCCK_VAL == 720)
#define VCCK_VAL_REG    0x00200002
#elif (VCCK_VAL == 710)
#define VCCK_VAL_REG    0x00210001
#elif (VCCK_VAL == 700)
#define VCCK_VAL_REG    0x00220000
#else
#error "VCCK val out of range\n"
#endif

/* VDDEE_VAL_REG */
#if    (VDDEE_VAL == 710)
#define VDDEE_VAL_REG   0x120000
#elif (VDDEE_VAL == 720)
#define VDDEE_VAL_REG   0x110001
#elif (VDDEE_VAL == 730)
#define VDDEE_VAL_REG   0x100002
#elif (VDDEE_VAL == 740)
#define VDDEE_VAL_REG   0xf0003
#elif (VDDEE_VAL == 750)
#define VDDEE_VAL_REG   0xe0004
#elif (VDDEE_VAL == 760)
#define VDDEE_VAL_REG   0xd0005
#elif (VDDEE_VAL == 770)
#define VDDEE_VAL_REG   0xc0006
#elif (VDDEE_VAL == 780)
#define VDDEE_VAL_REG   0xb0007
#elif (VDDEE_VAL == 790)
#define VDDEE_VAL_REG   0xa0008
#elif (VDDEE_VAL == 800)
#define VDDEE_VAL_REG   0x90009
#elif (VDDEE_VAL == 810)
#define VDDEE_VAL_REG   0x8000a
#elif (VDDEE_VAL == 820)
#define VDDEE_VAL_REG   0x7000b
#elif (VDDEE_VAL == 830)
#define VDDEE_VAL_REG   0x6000c
#elif (VDDEE_VAL == 840)
#define VDDEE_VAL_REG   0x5000d
#elif (VDDEE_VAL == 850)
#define VDDEE_VAL_REG   0x4000e
#elif (VDDEE_VAL == 860)
#define VDDEE_VAL_REG   0x3000f
#elif (VDDEE_VAL == 870)
#define VDDEE_VAL_REG   0x20010
#elif (VDDEE_VAL == 880)
#define VDDEE_VAL_REG   0x10011
#elif (VDDEE_VAL == 890)
#define VDDEE_VAL_REG   0x12
#else
#error "VDDEE val out of range\n"
#endif

bl2_reg_t __bl2_reg[] __attribute__ ((section(".generic_param"))) = {
	//need fine tune
	{ 0, 0, 0xffffffff, 0, 0, 0 },
	/* bit0 in flag, 1: enable bl22, 0: disable bl22 */
	{ 0, 0, 0xffffffff, 0, 1, 0 },
};

/* gpio/pinmux/pwm init */
register_ops_t __bl2_ops_reg[MAX_REG_OPS_ENTRIES]
__attribute__ ((section(".misc_param"))) = {
	/* config vddee and vcck pwm - pwm_a and pwm_b*/
	{ PWMAB_PWM_A,		   VDDEE_VAL_REG, 0xffffffff, 0, 0, 0 },
	{ PWMAB_PWM_B,		   VCCK_VAL_REG,  0xffffffff, 0, 0, 0 },
	{ PWMAB_MISC_REG_AB, (0x3 << 0) | (0x1 << 15) | (0x1 << 23),
				(0x3 << 0) | (0x1 << 15) | (0x1 << 23), 0, 0, 0 },
	/* set pwm a and pwm b clock rate to 24M, enable them */
	{ CLKCTRL_PWM_CLK_AB_CTRL, ((0x1 << 8) | (0x1 << 24)), 0xffffffff, 0, 0, 0 },
	/* set GPIOE_0 GPIOE_1 drive strength to 3 */
	{ PADCTRL_GPIOE_DS,	   0xf,		  0xf,	      0, 0, 0 },
	/* set GPIOE_0 GPIOE_1 mux to pwma pwmb */
	{ PADCTRL_PIN_MUX_REGI,	   (0x1 << 0),	  (0xf << 0), 0, 0, 0 },
	{ PADCTRL_PIN_MUX_REGI,	   (0x1 << 4),	  (0xf << 4), 0, 0, 0 },
};

#define DEV_FIP_SIZE 0x300000
#define DDR_FIP_SIZE 0x40000
/* for all the storage parameter */
#ifdef CONFIG_MTD_SPI_NAND
/* for spinand storage parameter */
storage_parameter_t __store_para __attribute__ ((section(".store_param"))) = {
	.common				= {
		.version = 0x01,
		.device_fip_container_size = DEV_FIP_SIZE,
		.device_fip_container_copies = 4,
		.ddr_fip_container_size = DDR_FIP_SIZE,
	},
	.nand				= {
		.version = 0x02,
		/* bbt page get from info page, not used here */
		.bbt_pages = 1,
		.bbt_start_block = 20,
		.discrete_mode = 1,
		/* page size get from info page, not used here */
		.setup_data.spi_nand_page_size = 2048,
		/* planes per lun get from info page, not used here */
		.reserved.spi_nand_planes_per_lun = (1 << 0) | (96 << 8) | (0x3b << 16),
		.reserved_area_blk_cnt = 48,
		.page_per_block = 64,
		.use_param_page_list = 0,
	},
};
#else
storage_parameter_t __store_para __attribute__ ((section(".store_param"))) = {
	.common					= {
		.version			= 0x01,
		.device_fip_container_size	= DEV_FIP_SIZE,
		.device_fip_container_copies	= 4,
		.ddr_fip_container_size		= DDR_FIP_SIZE,
	},
	.nand					= {
		.version			= 0x01,
		.bbt_pages			= 0x1,
		.bbt_start_block		= 20,
		.discrete_mode			= 1,
		.setup_data.nand_setup_data	= (2 << 20) |		    \
						  (0 << 19) |			  \
						  (1 << 17) |			  \
						  (1 << 14) |			  \
						  (0 << 13) |			  \
						  (64 << 6) |			  \
						  (8 << 0),
		.reserved_area_blk_cnt		= 48,
		.page_per_block			= 64,
		.use_param_page_list		= 0,
	},
};
#endif
