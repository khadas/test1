/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef _ARCH_MESON_S4_MEASURE_H_
#define _ARCH_MESON_S4_MEASURE_H_

static const char *clk_msr_table[] = {
	[0] = "cts_sys_clk",
	[1] = "cts_axi_clk",
	[2] = "cts_rtc_clk",
	[3] = "p22_usb2_ckout",
	[4] = "p21_usb2_ckout",
	[5] = "p20_usb2_ckout",
	[6] = "sys_cpu_clk_div16",
	[8] = "eth_mpll_test",
	[10] = "fclk_div5",
	[15] = "mpll_clk_50m",
	[16] = "sys_oscin32k_i",
	[17] = "rtc_pll_clk",
	[19] = "hifi_pll_clk",
	[20] = "gp0_pll_clk",
	[21] = "gp1_pll_clk",
	[22] = "eth_mppll_50m_ckout",
	[23] = "sys_pll_div16",
	[24] = "ddr_dpll_pt_clk",
	[27] = "rtc_sec_pulse_out",
	[28] = "rtc_osc_clk_out",
	[30] = "mod_eth_phy_ref_clk",
	[31] = "mod_eth_tx_clk",
	[32] = "cts_eth_clk125Mhz",
	[33] = "cts_eth_clk_rmii",
	[34] = "co_clkin_to_mac",
	[35] = "mod_eth_rx_clk_rmii",
	[36] = "co_rx_clk",
	[37] = "co_tx_clk",
	[38] = "eth_phy_rxclk",
	[39] = "eth_phy_plltxclk",
	[40] = "ephy_test_clk",
	[41] = "cts_audio_core_clk",
	[51] = "cts_vout_venc_clk_ph",
	[52] = "cts_vout_venc_clk",
	[79] = "cts_rama_clk",
	[106] = "deskew_pll_test_clk",
	[111] = "cts_sar_adc_clk",
	[112] = "cts_ts_clk",
	[113] = "cts_sd_emmc_C_clk(nand)",
	[115] = "cts_sd_emmc_A_clk",
	[116] = "gpio_msr_clk",
	[117] = "cts_spicc_1_clk",
	[118] = "cts_spicc_0_clk",
	[119] = "o_mst_sclk_vad",
	[120] = "o_mst_mclk_vad",
	[121] = "o_pdm_sysclk",
	[122] = "mod_audio_pdm_dclk_o",
	[123] = "o_vad_clk",
	[124] = "audio_mst_clk[0]",
	[125] = "audio_mst_clk[1]",
	[126] = "audio_mst_clk[2]",
	[127] = "audio_mst_clk[3]",
	[128] = "audio_mst_clk[4]",
	[129] = "audio_mst_clk[5]",
	[130] = "audio_mst_clk[6]",
	[131] = "audio_mst_clk[7]",
	[132] = "audio_mst_clk[8]",
	[133] = "audio_mst_clk[9]",
	[134] = "audio_mst_clk[10]",
	[135] = "audio_mst_clk[11]",
	[136] = "audio_mst_clk[12]",
	[137] = "audio_mst_clk[13]",
	[138] = "audio_mst_clk[14]",
	[139] = "audio_mst_clk[15]",
	[140] = "audio_mst_clk[16]",
	[141] = "audio_mst_clk[17]",
	[142] = "audio_mst_clk[18]",
	[143] = "audio_mst_clk[19]",
	[144] = "audio_mst_clk[20]",
	[145] = "audio_mst_clk[21]",
	[146] = "audio_mst_clk[22]",
	[147] = "audio_mst_clk[23]",
	[148] = "audio_mst_clk[24]",
	[149] = "audio_mst_clk[25]",
	[150] = "audio_mst_clk[26]",
	[151] = "audio_mst_clk[27]",
	[152] = "audio_mst_clk[28]",
	[153] = "audio_mst_clk[29]",
	[154] = "audio_mst_clk[30]",
	[155] = "audio_mst_clk[31]",
	[156] = "audio_mst_clk[32]",
	[157] = "audio_mst_clk[33]",
	[158] = "audio_mst_clk[34]",
	[159] = "audio_mst_clk[35]",
	[162] = "pwm_h_clk",
	[163] = "pwm_g_clk",
	[164] = "pwm_f_clk",
	[165] = "pwm_e_clk",
	[166] = "pwm_d_clk",
	[167] = "pwm_c_clk",
	[168] = "pwm_b_clk",
	[169] = "pwm_a_clk",
	[176] = "rng_ring_osc_clk[0]",
	[177] = "rng_ring_osc_clk[1]",
	[178] = "rng_ring_osc_clk[2]",
	[179] = "rng_ring_osc_clk[3]",
	[180] = "sys_cpu_osc_ring[0](ULVT16)",
	[181] = "sys_cpu_osc_ring[1](ULVT20)",
	[182] = "sys_cpu_osc_ring[2](ULVT16)",
	[183] = "sys_cpu_osc_ring[3](ULVT16)",
	[184] = "sys_cpu_osc_ring[4](ULVT16)",
	[185] = "am_ring_osc_clk_out_top[0](SVT16)",
	[186] = "am_ring_osc_clk_out_top[1](LVT20)",
};

#endif
