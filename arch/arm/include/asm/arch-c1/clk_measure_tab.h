/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef _ARCH_MESON_A1_MEASURE_H_
#define _ARCH_MESON_A1_MEASURE_H_

static const char* clk_msr_table[] = {
	[0] = "tdmout_b_sclk",
	[1] = "tdmout_a_sclk",
	[2] = "tdmin_lb_sclk",
	[3] = "tdmin_b_sclk",
	[4] = "tdmin_a_sclk",
	[5] = "vad_clk",
	[6] = "resampleA_clk",
	[7] = "pdm_sysclk",
	[8] = "pdm_dclk",
	[9] = "locker_out_clk",
	[10] = "locker_in_clk",
	[12] = "tdmin_vad_clk",
	[13] = "au_adc_clk",
	[14] = "au_dac_clk",
	[16] = "spicc_a_clk",
	[17] = "spifc_clk",
	[18] = "sd_emmc_a_clk",
	[19] = "spicc_b_clk",
	[24] = "ts_clk",
	[25] = "pwm_f_clk",
	[26] = "pwm_e_clk",
	[27] = "pwm_d_clk",
	[28] = "pwm_c_clk",
	[29] = "pwm_b_clk",
	[30] = "pwm_a_clk",
	[31] = "saradc_clk",
	[32] = "usb_bus",
	[33] = "dsp_b_clk",
	[34] = "dsp_a_clk",
	[35] = "axi_clk",
	[36] = "sys_clk",
	[39] = "gpio_msr",
	[40] = "rng_ring_osc0",
	[41] = "rng_ring_osc1",
	[42] = "rng_ring_osc2",
	[43] = "rng_ring_osc3",
	[44] = "dds_out",
	[45] = "cpu_clk_div16",
	[46] = "osc_ring_cpu0",
	[47] = "osc_ring_cpu1",
	[48] = "osc_ring_cpu2",
	[49] = "osc_ring_cpu3",
	[50] = "osc_ring_ddr",
	[51] = "osc_ring_dmc",
	[52] = "osc_ring_dspa",
	[53] = "osc_ring_dspb",
	[54] = "osc_ring_rama",
	[55] = "osc_ring_ramb",
	[56] = "osc_ring_ramc",
	[57] = "osc_ring_dos0",
	[58] = "osc_ring_dos1",
	[59] = "osc_ring_dos2",
	[60] = "osc_ring_dos3",
	[62] = "eth_mppll_50m",
	[63] = "co_clkin_to_mac",
	[64] = "eth_phy_plltxclk",
	[65] = "eth_phy_rxclk",
	[66] = "co_tx_clk",
	[67] = "co_rx_clk",
	[68] = "cts_mipi_isp_clk",
	[69] = "cts_mipi_csi_phy_clk",
	[70] = "cts_nna_axi_clk",
	[71] = "cts_nna_core_clk",
	[72] = "cts_eth_clk_rmii",
	[73] = "cts_eth_clk125Mhz",
	[74] = "cts_jpeg_enc_clk ",
	[75] = "cts_rtc_clk",
	[76] = "cts_ge2d_clk",
	[77] = "cts_gdc_axi_clk",
	[78] = "cts_gdc_core_clk",
	[79] = "cts_pwm_j_clk",
	[80] = "cts_pwm_i_clk",
	[81] = "cts_pwm_h_clk",
	[82] = "cts_pwm_g_clk",
	[83] = "cts_wave_cclk",
	[84] = "cts_wave_bclk",
	[85] = "cts_wave_aclk",
	[86] = "cts_sd_emmc_C_clk",
	[87] = "cts_sd_emmc_B_clk",
	[88] = "ephy_test_clk",
	[89] = "mipi_csi_phy0_clk",
	[90] = "mipi_csi_phy1_clk",
	[91] = "mod_eth_phy_ref_clk",
	[92] = "ddr_dpll_pt_clk",
};

#endif
