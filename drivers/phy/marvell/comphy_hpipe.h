/*
 * Copyright (C) 2015-2016 Marvell International Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _COMPHY_HPIPE_H_
#define _COMPHY_HPIPE_H_

/* SerDes IP register */
#define SD_EXTERNAL_CONFIG0_REG			0
#define SD_EXTERNAL_CONFIG0_SD_PU_PLL_OFFSET	1
#define SD_EXTERNAL_CONFIG0_SD_PU_PLL_MASK	\
	(1 << SD_EXTERNAL_CONFIG0_SD_PU_PLL_OFFSET)
#define SD_EXTERNAL_CONFIG0_SD_PHY_GEN_RX_OFFSET 3
#define SD_EXTERNAL_CONFIG0_SD_PHY_GEN_RX_MASK	\
	(0xf << SD_EXTERNAL_CONFIG0_SD_PHY_GEN_RX_OFFSET)
#define SD_EXTERNAL_CONFIG0_SD_PHY_GEN_TX_OFFSET 7
#define SD_EXTERNAL_CONFIG0_SD_PHY_GEN_TX_MASK	\
	(0xf << SD_EXTERNAL_CONFIG0_SD_PHY_GEN_TX_OFFSET)
#define SD_EXTERNAL_CONFIG0_SD_PU_RX_OFFSET	11
#define SD_EXTERNAL_CONFIG0_SD_PU_RX_MASK	\
	(1 << SD_EXTERNAL_CONFIG0_SD_PU_RX_OFFSET)
#define SD_EXTERNAL_CONFIG0_SD_PU_TX_OFFSET	12
#define SD_EXTERNAL_CONFIG0_SD_PU_TX_MASK	\
	(1 << SD_EXTERNAL_CONFIG0_SD_PU_TX_OFFSET)
#define SD_EXTERNAL_CONFIG0_HALF_BUS_MODE_OFFSET 14
#define SD_EXTERNAL_CONFIG0_HALF_BUS_MODE_MASK	\
	(1 << SD_EXTERNAL_CONFIG0_HALF_BUS_MODE_OFFSET)
#define SD_EXTERNAL_CONFIG0_MEDIA_MODE_OFFSET	15
#define SD_EXTERNAL_CONFIG0_MEDIA_MODE_MASK	\
	(0x1 << SD_EXTERNAL_CONFIG0_MEDIA_MODE_OFFSET)

#define SD_EXTERNAL_CONFIG1_REG			0x4
#define SD_EXTERNAL_CONFIG1_RESET_IN_OFFSET	3
#define SD_EXTERNAL_CONFIG1_RESET_IN_MASK	\
	(0x1 << SD_EXTERNAL_CONFIG1_RESET_IN_OFFSET)
#define SD_EXTERNAL_CONFIG1_RX_INIT_OFFSET	4
#define SD_EXTERNAL_CONFIG1_RX_INIT_MASK	\
	(0x1 << SD_EXTERNAL_CONFIG1_RX_INIT_OFFSET)
#define SD_EXTERNAL_CONFIG1_RESET_CORE_OFFSET	5
#define SD_EXTERNAL_CONFIG1_RESET_CORE_MASK	\
	(0x1 << SD_EXTERNAL_CONFIG1_RESET_CORE_OFFSET)
#define SD_EXTERNAL_CONFIG1_RF_RESET_IN_OFFSET	6
#define SD_EXTERNAL_CONFIG1_RF_RESET_IN_MASK	\
	(0x1 << SD_EXTERNAL_CONFIG1_RF_RESET_IN_OFFSET)

#define SD_EXTERNAL_CONFIG2_REG			0x8
#define SD_EXTERNAL_CONFIG2_PIN_DFE_EN_OFFSET	4
#define SD_EXTERNAL_CONFIG2_PIN_DFE_EN_MASK	\
	(0x1 << SD_EXTERNAL_CONFIG2_PIN_DFE_EN_OFFSET)
#define SD_EXTERNAL_CONFIG2_SSC_ENABLE_OFFSET	7
#define SD_EXTERNAL_CONFIG2_SSC_ENABLE_MASK	\
	(0x1 << SD_EXTERNAL_CONFIG2_SSC_ENABLE_OFFSET)

#define SD_EXTERNAL_STATUS0_REG			0x18
#define SD_EXTERNAL_STATUS0_PLL_TX_OFFSET	2
#define SD_EXTERNAL_STATUS0_PLL_TX_MASK		\
	(0x1 << SD_EXTERNAL_STATUS0_PLL_TX_OFFSET)
#define SD_EXTERNAL_STATUS0_PLL_RX_OFFSET	3
#define SD_EXTERNAL_STATUS0_PLL_RX_MASK		\
	(0x1 << SD_EXTERNAL_STATUS0_PLL_RX_OFFSET)
#define SD_EXTERNAL_STATUS0_RX_INIT_OFFSET	4
#define SD_EXTERNAL_STATUS0_RX_INIT_MASK	\
	(0x1 << SD_EXTERNAL_STATUS0_RX_INIT_OFFSET)
#define SD_EXTERNAL_STATUS0_RF_RESET_IN_OFFSET	6
#define SD_EXTERNAL_STATUS0_RF_RESET_IN_MASK	\
	(0x1 << SD_EXTERNAL_STATUS0_RF_RESET_IN_OFFSET)

/* HPIPE register */
#define HPIPE_PWR_PLL_REG			0x4
#define HPIPE_PWR_PLL_REF_FREQ_OFFSET		0
#define HPIPE_PWR_PLL_REF_FREQ_MASK		\
	(0x1f << HPIPE_PWR_PLL_REF_FREQ_OFFSET)
#define HPIPE_PWR_PLL_PHY_MODE_OFFSET		5
#define HPIPE_PWR_PLL_PHY_MODE_MASK		\
	(0x7 << HPIPE_PWR_PLL_PHY_MODE_OFFSET)

#define HPIPE_KVCO_CALIB_CTRL_REG		0x8
#define HPIPE_KVCO_CALIB_CTRL_MAX_PLL_OFFSET	12
#define HPIPE_KVCO_CALIB_CTRL_MAX_PLL_MASK	\
	(0x1 << HPIPE_KVCO_CALIB_CTRL_MAX_PLL_OFFSET)

#define HPIPE_CAL_REG1_REG			0xc
#define HPIPE_CAL_REG_1_EXT_TXIMP_OFFSET	10
#define HPIPE_CAL_REG_1_EXT_TXIMP_MASK		\
	(0x1f << HPIPE_CAL_REG_1_EXT_TXIMP_OFFSET)
#define HPIPE_CAL_REG_1_EXT_TXIMP_EN_OFFSET	15
#define HPIPE_CAL_REG_1_EXT_TXIMP_EN_MASK	\
	(0x1 << HPIPE_CAL_REG_1_EXT_TXIMP_EN_OFFSET)

#define HPIPE_SQUELCH_FFE_SETTING_REG           0x018

#define HPIPE_DFE_REG0				0x01C
#define HPIPE_DFE_RES_FORCE_OFFSET		15
#define HPIPE_DFE_RES_FORCE_MASK		\
	(0x1 << HPIPE_DFE_RES_FORCE_OFFSET)

#define HPIPE_DFE_F3_F5_REG			0x028
#define HPIPE_DFE_F3_F5_DFE_EN_OFFSET		14
#define HPIPE_DFE_F3_F5_DFE_EN_MASK		\
	(0x1 << HPIPE_DFE_F3_F5_DFE_EN_OFFSET)
#define HPIPE_DFE_F3_F5_DFE_CTRL_OFFSET		15
#define HPIPE_DFE_F3_F5_DFE_CTRL_MASK		\
	(0x1 << HPIPE_DFE_F3_F5_DFE_CTRL_OFFSET)

#define HPIPE_G1_SET_0_REG			0x034
#define HPIPE_G1_SET_0_G1_TX_AMP_OFFSET		1
#define HPIPE_G1_SET_0_G1_TX_AMP_MASK		\
	(0x1f << HPIPE_G1_SET_0_G1_TX_AMP_OFFSET)
#define HPIPE_G1_SET_0_G1_TX_AMP_ADJ_OFFSET	6
#define HPIPE_G1_SET_0_G1_TX_AMP_ADJ_MASK	\
	(0x1 << HPIPE_G1_SET_0_G1_TX_AMP_ADJ_OFFSET)
#define HPIPE_G1_SET_0_G1_TX_EMPH1_OFFSET	7
#define HPIPE_G1_SET_0_G1_TX_EMPH1_MASK		\
	(0xf << HPIPE_G1_SET_0_G1_TX_EMPH1_OFFSET)
#define HPIPE_G1_SET_0_G1_TX_EMPH1_EN_OFFSET	11
#define HPIPE_G1_SET_0_G1_TX_EMPH1_EN_MASK	\
	(0x1 << HPIPE_G1_SET_0_G1_TX_EMPH1_EN_OFFSET)

#define HPIPE_G1_SET_1_REG			0x038
#define HPIPE_G1_SET_1_G1_RX_SELMUPI_OFFSET	0
#define HPIPE_G1_SET_1_G1_RX_SELMUPI_MASK	\
	(0x7 << HPIPE_G1_SET_1_G1_RX_SELMUPI_OFFSET)
#define HPIPE_G1_SET_1_G1_RX_SELMUPP_OFFSET	3
#define HPIPE_G1_SET_1_G1_RX_SELMUPP_MASK	\
	(0x7 << HPIPE_G1_SET_1_G1_RX_SELMUPP_OFFSET)
#define HPIPE_G1_SET_1_G1_RX_SELMUFI_OFFSET	6
#define HPIPE_G1_SET_1_G1_RX_SELMUFI_MASK	\
	(0x3 << HPIPE_G1_SET_1_G1_RX_SELMUFI_OFFSET)
#define HPIPE_G1_SET_1_G1_RX_SELMUFF_OFFSET	8
#define HPIPE_G1_SET_1_G1_RX_SELMUFF_MASK	\
	(0x3 << HPIPE_G1_SET_1_G1_RX_SELMUFF_OFFSET)
#define HPIPE_G1_SET_1_G1_RX_DFE_EN_OFFSET	10
#define HPIPE_G1_SET_1_G1_RX_DFE_EN_MASK	\
	(0x1 << HPIPE_G1_SET_1_G1_RX_DFE_EN_OFFSET)

#define HPIPE_G1_SET_1_G1_RX_DIGCK_DIV_OFFSET	11
#define HPIPE_G1_SET_1_G1_RX_DIGCK_DIV_MASK	\
	(0x3 << HPIPE_G1_SET_1_G1_RX_DIGCK_DIV_OFFSET)

#define HPIPE_G2_SET_0_REG			0x3c
#define HPIPE_G2_SET_0_G2_TX_AMP_OFFSET		1
#define HPIPE_G2_SET_0_G2_TX_AMP_MASK		\
	(0x1f << HPIPE_G2_SET_0_G2_TX_AMP_OFFSET)
#define HPIPE_G2_SET_0_G2_TX_AMP_ADJ_OFFSET	6
#define HPIPE_G2_SET_0_G2_TX_AMP_ADJ_MASK	\
	(0x1 << HPIPE_G2_SET_0_G2_TX_AMP_ADJ_OFFSET)
#define HPIPE_G2_SET_0_G2_TX_EMPH1_OFFSET	7
#define HPIPE_G2_SET_0_G2_TX_EMPH1_MASK		\
	(0xf << HPIPE_G2_SET_0_G2_TX_EMPH1_OFFSET)
#define HPIPE_G2_SET_0_G2_TX_EMPH1_EN_OFFSET	11
#define HPIPE_G2_SET_0_G2_TX_EMPH1_EN_MASK	\
	(0x1 << HPIPE_G2_SET_0_G2_TX_EMPH1_EN_OFFSET)

#define HPIPE_G2_SET_1_REG			0x040
#define HPIPE_G2_SET_1_G2_RX_SELMUPI_OFFSET	0
#define HPIPE_G2_SET_1_G2_RX_SELMUPI_MASK	\
	(0x7 << HPIPE_G2_SET_1_G2_RX_SELMUPI_OFFSET)
#define HPIPE_G2_SET_1_G2_RX_SELMUPP_OFFSET	3
#define HPIPE_G2_SET_1_G2_RX_SELMUPP_MASK	\
	(0x7 << HPIPE_G2_SET_1_G2_RX_SELMUPP_OFFSET)
#define HPIPE_G2_SET_1_G2_RX_SELMUFI_OFFSET	6
#define HPIPE_G2_SET_1_G2_RX_SELMUFI_MASK	\
	(0x3 << HPIPE_G2_SET_1_G2_RX_SELMUFI_OFFSET)
#define HPIPE_G2_SET_1_G2_RX_SELMUFF_OFFSET	8
#define HPIPE_G2_SET_1_G2_RX_SELMUFF_MASK	\
	(0x3 << HPIPE_G2_SET_1_G2_RX_SELMUFF_OFFSET)
#define HPIPE_G2_SET_1_G2_RX_DFE_EN_OFFSET	10
#define HPIPE_G2_SET_1_G2_RX_DFE_EN_MASK	\
	(0x1 << HPIPE_G2_SET_1_G2_RX_DFE_EN_OFFSET)
#define HPIPE_G2_SET_1_G2_RX_DIGCK_DIV_OFFSET	11
#define HPIPE_G2_SET_1_G2_RX_DIGCK_DIV_MASK	\
	(0x3 << HPIPE_G2_SET_1_G2_RX_DIGCK_DIV_OFFSET)

#define HPIPE_G3_SET_0_REG			0x44
#define HPIPE_G3_SET_0_G3_TX_AMP_OFFSET		1
#define HPIPE_G3_SET_0_G3_TX_AMP_MASK		\
	(0x1f << HPIPE_G3_SET_0_G3_TX_AMP_OFFSET)
#define HPIPE_G3_SET_0_G3_TX_AMP_ADJ_OFFSET	6
#define HPIPE_G3_SET_0_G3_TX_AMP_ADJ_MASK	\
	(0x1 << HPIPE_G3_SET_0_G3_TX_AMP_ADJ_OFFSET)
#define HPIPE_G3_SET_0_G3_TX_EMPH1_OFFSET	7
#define HPIPE_G3_SET_0_G3_TX_EMPH1_MASK		\
	(0xf << HPIPE_G3_SET_0_G3_TX_EMPH1_OFFSET)
#define HPIPE_G3_SET_0_G3_TX_EMPH1_EN_OFFSET	11
#define HPIPE_G3_SET_0_G3_TX_EMPH1_EN_MASK	\
	(0x1 << HPIPE_G3_SET_0_G3_TX_EMPH1_EN_OFFSET)
#define HPIPE_G3_SET_0_G3_TX_SLEW_RATE_SEL_OFFSET 12
#define HPIPE_G3_SET_0_G3_TX_SLEW_RATE_SEL_MASK	\
	(0x7 << HPIPE_G3_SET_0_G3_TX_SLEW_RATE_SEL_OFFSET)
#define HPIPE_G3_SET_0_G3_TX_SLEW_CTRL_EN_OFFSET 15
#define HPIPE_G3_SET_0_G3_TX_SLEW_CTRL_EN_MASK	\
	(0x1 << HPIPE_G3_SET_0_G3_TX_SLEW_CTRL_EN_OFFSET)

#define HPIPE_G3_SET_1_REG			0x048
#define HPIPE_G3_SET_1_G3_RX_SELMUPI_OFFSET	0
#define HPIPE_G3_SET_1_G3_RX_SELMUPI_MASK	\
	(0x7 << HPIPE_G3_SET_1_G3_RX_SELMUPI_OFFSET)
#define HPIPE_G3_SET_1_G3_RX_SELMUPF_OFFSET	3
#define HPIPE_G3_SET_1_G3_RX_SELMUPF_MASK	\
	(0x7 << HPIPE_G3_SET_1_G3_RX_SELMUPF_OFFSET)
#define HPIPE_G3_SET_1_G3_RX_SELMUFI_OFFSET	6
#define HPIPE_G3_SET_1_G3_RX_SELMUFI_MASK	\
	(0x3 << HPIPE_G3_SET_1_G3_RX_SELMUFI_OFFSET)
#define HPIPE_G3_SET_1_G3_RX_SELMUFF_OFFSET	8
#define HPIPE_G3_SET_1_G3_RX_SELMUFF_MASK	\
	(0x3 << HPIPE_G3_SET_1_G3_RX_SELMUFF_OFFSET)
#define HPIPE_G3_SET_1_G3_RX_DFE_EN_OFFSET	10
#define HPIPE_G3_SET_1_G3_RX_DFE_EN_MASK	\
	(0x1 << HPIPE_G3_SET_1_G3_RX_DFE_EN_OFFSET)
#define HPIPE_G3_SET_1_G3_RX_DIGCK_DIV_OFFSET	11
#define HPIPE_G3_SET_1_G3_RX_DIGCK_DIV_MASK	 \
	(0x3 << HPIPE_G3_SET_1_G3_RX_DIGCK_DIV_OFFSET)
#define HPIPE_G3_SET_1_G3_SAMPLER_INPAIRX2_EN_OFFSET	13
#define HPIPE_G3_SET_1_G3_SAMPLER_INPAIRX2_EN_MASK	\
	(0x1 << HPIPE_G3_SET_1_G3_SAMPLER_INPAIRX2_EN_OFFSET)

#define HPIPE_LOOPBACK_REG			0x08c
#define HPIPE_LOOPBACK_SEL_OFFSET		1
#define HPIPE_LOOPBACK_SEL_MASK			\
	(0x7 << HPIPE_LOOPBACK_SEL_OFFSET)

#define HPIPE_SYNC_PATTERN_REG                  0x090

#define HPIPE_INTERFACE_REG			0x94
#define HPIPE_INTERFACE_GEN_MAX_OFFSET		10
#define HPIPE_INTERFACE_GEN_MAX_MASK		\
	(0x3 << HPIPE_INTERFACE_GEN_MAX_OFFSET)
#define HPIPE_INTERFACE_LINK_TRAIN_OFFSET	14
#define HPIPE_INTERFACE_LINK_TRAIN_MASK		\
	(0x1 << HPIPE_INTERFACE_LINK_TRAIN_OFFSET)

#define HPIPE_ISOLATE_MODE_REG			0x98
#define HPIPE_ISOLATE_MODE_GEN_RX_OFFSET	0
#define HPIPE_ISOLATE_MODE_GEN_RX_MASK		\
	(0xf << HPIPE_ISOLATE_MODE_GEN_RX_OFFSET)
#define HPIPE_ISOLATE_MODE_GEN_TX_OFFSET	4
#define HPIPE_ISOLATE_MODE_GEN_TX_MASK		\
	(0xf << HPIPE_ISOLATE_MODE_GEN_TX_OFFSET)

#define HPIPE_G1_SET_2_REG			0xf4
#define HPIPE_G1_SET_2_G1_TX_EMPH0_OFFSET	0
#define HPIPE_G1_SET_2_G1_TX_EMPH0_MASK		\
	(0xf << HPIPE_G1_SET_2_G1_TX_EMPH0_OFFSET)
#define HPIPE_G1_SET_2_G1_TX_EMPH0_EN_OFFSET	4
#define HPIPE_G1_SET_2_G1_TX_EMPH0_EN_MASK	\
	(0x1 << HPIPE_G1_SET_2_G1_TX_EMPH0_MASK)

#define HPIPE_VTHIMPCAL_CTRL_REG                0x104

#define HPIPE_VDD_CAL_CTRL_REG			0x114
#define HPIPE_EXT_SELLV_RXSAMPL_OFFSET		5
#define HPIPE_EXT_SELLV_RXSAMPL_MASK		\
	(0x1f << HPIPE_EXT_SELLV_RXSAMPL_OFFSET)

#define HPIPE_PCIE_REG0                         0x120
#define HPIPE_PCIE_IDLE_SYNC_OFFSET		12
#define HPIPE_PCIE_IDLE_SYNC_MASK		\
	(0x1 << HPIPE_PCIE_IDLE_SYNC_OFFSET)
#define HPIPE_PCIE_SEL_BITS_OFFSET		13
#define HPIPE_PCIE_SEL_BITS_MASK		\
	(0x3 << HPIPE_PCIE_SEL_BITS_OFFSET)

#define HPIPE_LANE_ALIGN_REG			0x124
#define HPIPE_LANE_ALIGN_OFF_OFFSET		12
#define HPIPE_LANE_ALIGN_OFF_MASK		\
	(0x1 << HPIPE_LANE_ALIGN_OFF_OFFSET)

#define HPIPE_MISC_REG				0x13C
#define HPIPE_MISC_CLK100M_125M_OFFSET		4
#define HPIPE_MISC_CLK100M_125M_MASK		\
	(0x1 << HPIPE_MISC_CLK100M_125M_OFFSET)
#define HPIPE_MISC_ICP_FORCE_OFFSET		5
#define HPIPE_MISC_ICP_FORCE_MASK		\
	(0x1 << HPIPE_MISC_ICP_FORCE_OFFSET)
#define HPIPE_MISC_TXDCLK_2X_OFFSET		6
#define HPIPE_MISC_TXDCLK_2X_MASK		\
	(0x1 << HPIPE_MISC_TXDCLK_2X_OFFSET)
#define HPIPE_MISC_CLK500_EN_OFFSET		7
#define HPIPE_MISC_CLK500_EN_MASK		\
	(0x1 << HPIPE_MISC_CLK500_EN_OFFSET)
#define HPIPE_MISC_REFCLK_SEL_OFFSET		10
#define HPIPE_MISC_REFCLK_SEL_MASK		\
	(0x1 << HPIPE_MISC_REFCLK_SEL_OFFSET)

#define HPIPE_RX_CONTROL_1_REG			0x140
#define HPIPE_RX_CONTROL_1_RXCLK2X_SEL_OFFSET	11
#define HPIPE_RX_CONTROL_1_RXCLK2X_SEL_MASK	\
	(0x1 << HPIPE_RX_CONTROL_1_RXCLK2X_SEL_OFFSET)
#define HPIPE_RX_CONTROL_1_CLK8T_EN_OFFSET	12
#define HPIPE_RX_CONTROL_1_CLK8T_EN_MASK	\
	(0x1 << HPIPE_RX_CONTROL_1_CLK8T_EN_OFFSET)

#define HPIPE_PWR_CTR_REG			0x148
#define HPIPE_PWR_CTR_RST_DFE_OFFSET		0
#define HPIPE_PWR_CTR_RST_DFE_MASK		\
	(0x1 << HPIPE_PWR_CTR_RST_DFE_OFFSET)
#define HPIPE_PWR_CTR_SFT_RST_OFFSET		10
#define HPIPE_PWR_CTR_SFT_RST_MASK		\
	(0x1 << HPIPE_PWR_CTR_SFT_RST_OFFSET)

#define HPIPE_PLLINTP_REG1			0x150

#define HPIPE_SAMPLER_N_PROC_CALIB_CTRL_REG	0x16C
#define HPIPE_SMAPLER_OFFSET			12
#define HPIPE_SMAPLER_MASK			\
	(0x1 << HPIPE_SMAPLER_OFFSET)

#define HPIPE_TX_REG1_REG			0x174
#define HPIPE_TX_REG1_TX_EMPH_RES_OFFSET	5
#define HPIPE_TX_REG1_TX_EMPH_RES_MASK		\
	(0x3 << HPIPE_TX_REG1_TX_EMPH_RES_OFFSET)
#define HPIPE_TX_REG1_SLC_EN_OFFSET		10
#define HPIPE_TX_REG1_SLC_EN_MASK		\
	(0x3f << HPIPE_TX_REG1_SLC_EN_OFFSET)

#define HPIPE_PWR_CTR_DTL_REG				0x184
#define HPIPE_PWR_CTR_DTL_SQ_DET_EN_OFFSET		0
#define HPIPE_PWR_CTR_DTL_SQ_DET_EN_MASK		\
	(0x1 << HPIPE_PWR_CTR_DTL_SQ_DET_EN_OFFSET)
#define HPIPE_PWR_CTR_DTL_SQ_PLOOP_EN_OFFSET		1
#define HPIPE_PWR_CTR_DTL_SQ_PLOOP_EN_MASK		\
	(0x1 << HPIPE_PWR_CTR_DTL_SQ_PLOOP_EN_OFFSET)
#define HPIPE_PWR_CTR_DTL_FLOOP_EN_OFFSET		2
#define HPIPE_PWR_CTR_DTL_FLOOP_EN_MASK			\
	(0x1 << HPIPE_PWR_CTR_DTL_FLOOP_EN_OFFSET)
#define HPIPE_PWR_CTR_DTL_CLAMPING_SEL_OFFSET		4
#define HPIPE_PWR_CTR_DTL_CLAMPING_SEL_MASK		\
	(0x7 << HPIPE_PWR_CTR_DTL_CLAMPING_SEL_OFFSET)
#define HPIPE_PWR_CTR_DTL_INTPCLK_DIV_FORCE_OFFSET	10
#define HPIPE_PWR_CTR_DTL_INTPCLK_DIV_FORCE_MASK	\
	(0x1 << HPIPE_PWR_CTR_DTL_INTPCLK_DIV_FORCE_OFFSET)
#define HPIPE_PWR_CTR_DTL_CLK_MODE_OFFSET		12
#define HPIPE_PWR_CTR_DTL_CLK_MODE_MASK			\
	(0x3 << HPIPE_PWR_CTR_DTL_CLK_MODE_OFFSET)
#define HPIPE_PWR_CTR_DTL_CLK_MODE_FORCE_OFFSET		14
#define HPIPE_PWR_CTR_DTL_CLK_MODE_FORCE_MASK		\
	(1 << HPIPE_PWR_CTR_DTL_CLK_MODE_FORCE_OFFSET)

#define HPIPE_PHASE_CONTROL_REG			0x188
#define HPIPE_OS_PH_OFFSET_OFFSET		0
#define HPIPE_OS_PH_OFFSET_MASK			\
	(0x7f << HPIPE_OS_PH_OFFSET_OFFSET)
#define HPIPE_OS_PH_OFFSET_FORCE_OFFSET		7
#define HPIPE_OS_PH_OFFSET_FORCE_MASK		\
	(0x1 << HPIPE_OS_PH_OFFSET_FORCE_OFFSET)
#define HPIPE_OS_PH_VALID_OFFSET		8
#define HPIPE_OS_PH_VALID_MASK			\
	(0x1 << HPIPE_OS_PH_VALID_OFFSET)

#define HPIPE_TX_TRAIN_CTRL_0_REG		0x268
#define HPIPE_TX_TRAIN_P2P_HOLD_OFFSET		15
#define HPIPE_TX_TRAIN_P2P_HOLD_MASK		\
	(0x1 << HPIPE_TX_TRAIN_P2P_HOLD_OFFSET)

#define HPIPE_TX_TRAIN_CTRL_REG			0x26C
#define HPIPE_TX_TRAIN_CTRL_G1_OFFSET		0
#define HPIPE_TX_TRAIN_CTRL_G1_MASK		\
	(0x1 << HPIPE_TX_TRAIN_CTRL_G1_OFFSET)
#define HPIPE_TX_TRAIN_CTRL_GN1_OFFSET		1
#define HPIPE_TX_TRAIN_CTRL_GN1_MASK		\
	(0x1 << HPIPE_TX_TRAIN_CTRL_GN1_OFFSET)
#define HPIPE_TX_TRAIN_CTRL_G0_OFFSET		2
#define HPIPE_TX_TRAIN_CTRL_G0_MASK		\
	(0x1 << HPIPE_TX_TRAIN_CTRL_G0_OFFSET)

#define HPIPE_TX_TRAIN_CTRL_4_REG		0x278
#define HPIPE_TRX_TRAIN_TIMER_OFFSET		0
#define HPIPE_TRX_TRAIN_TIMER_MASK		\
	(0x3FF << HPIPE_TRX_TRAIN_TIMER_OFFSET)

#define HPIPE_PCIE_REG1				0x288
#define HPIPE_PCIE_REG3				0x290

#define HPIPE_TX_TRAIN_CTRL_5_REG		0x2A4
#define HPIPE_TX_TRAIN_START_SQ_EN_OFFSET	11
#define HPIPE_TX_TRAIN_START_SQ_EN_MASK		\
	(0x1 << HPIPE_TX_TRAIN_START_SQ_EN_OFFSET)
#define HPIPE_TX_TRAIN_START_FRM_DET_EN_OFFSET	12
#define HPIPE_TX_TRAIN_START_FRM_DET_EN_MASK	\
	(0x1 << HPIPE_TX_TRAIN_START_FRM_DET_EN_OFFSET)
#define HPIPE_TX_TRAIN_START_FRM_LOCK_EN_OFFSET	13
#define HPIPE_TX_TRAIN_START_FRM_LOCK_EN_MASK	\
	(0x1 << HPIPE_TX_TRAIN_START_FRM_LOCK_EN_OFFSET)
#define HPIPE_TX_TRAIN_WAIT_TIME_EN_OFFSET	14
#define HPIPE_TX_TRAIN_WAIT_TIME_EN_MASK	\
	(0x1 << HPIPE_TX_TRAIN_WAIT_TIME_EN_OFFSET)

#define HPIPE_TX_TRAIN_REG			0x31C
#define HPIPE_TX_TRAIN_CHK_INIT_OFFSET		4
#define HPIPE_TX_TRAIN_CHK_INIT_MASK		\
	(0x1 << HPIPE_TX_TRAIN_CHK_INIT_OFFSET)
#define HPIPE_TX_TRAIN_COE_FM_PIN_PCIE3_OFFSET	7
#define HPIPE_TX_TRAIN_COE_FM_PIN_PCIE3_MASK	\
	(0x1 << HPIPE_TX_TRAIN_COE_FM_PIN_PCIE3_OFFSET)

#define HPIPE_TX_TRAIN_CTRL_11_REG		0x438
#define HPIPE_TX_STATUS_CHECK_MODE_OFFSET	6
#define HPIPE_TX_TX_STATUS_CHECK_MODE_MASK	\
	(0x1 << HPIPE_TX_STATUS_CHECK_MODE_OFFSET)
#define HPIPE_TX_NUM_OF_PRESET_OFFSET		10
#define HPIPE_TX_NUM_OF_PRESET_MASK		\
	(0x7 << HPIPE_TX_NUM_OF_PRESET_OFFSET)
#define HPIPE_TX_SWEEP_PRESET_EN_OFFSET		15
#define HPIPE_TX_SWEEP_PRESET_EN_MASK		\
	(0x1 << HPIPE_TX_SWEEP_PRESET_EN_OFFSET)

#define HPIPE_G1_SETTINGS_3_REG				0x440
#define HPIPE_G1_SETTINGS_3_G1_FFE_CAP_SEL_OFFSET	0
#define HPIPE_G1_SETTINGS_3_G1_FFE_CAP_SEL_MASK		\
	(0xf << HPIPE_G1_SETTINGS_3_G1_FFE_CAP_SEL_OFFSET)
#define HPIPE_G1_SETTINGS_3_G1_FFE_RES_SEL_OFFSET	4
#define HPIPE_G1_SETTINGS_3_G1_FFE_RES_SEL_MASK		\
	(0x7 << HPIPE_G1_SETTINGS_3_G1_FFE_RES_SEL_OFFSET)
#define HPIPE_G1_SETTINGS_3_G1_FFE_SETTING_FORCE_OFFSET	7
#define HPIPE_G1_SETTINGS_3_G1_FFE_SETTING_FORCE_MASK	\
	(0x1 << HPIPE_G1_SETTINGS_3_G1_FFE_SETTING_FORCE_OFFSET)
#define HPIPE_G1_SETTINGS_3_G1_FBCK_SEL_OFFSET		9
#define HPIPE_G1_SETTINGS_3_G1_FBCK_SEL_MASK		\
	(0x1 << HPIPE_G1_SETTINGS_3_G1_FBCK_SEL_OFFSET)
#define HPIPE_G1_SETTINGS_3_G1_FFE_DEG_RES_LEVEL_OFFSET	12
#define HPIPE_G1_SETTINGS_3_G1_FFE_DEG_RES_LEVEL_MASK	\
	(0x3 << HPIPE_G1_SETTINGS_3_G1_FFE_DEG_RES_LEVEL_OFFSET)
#define HPIPE_G1_SETTINGS_3_G1_FFE_LOAD_RES_LEVEL_OFFSET	14
#define HPIPE_G1_SETTINGS_3_G1_FFE_LOAD_RES_LEVEL_MASK	\
	(0x3 << HPIPE_G1_SETTINGS_3_G1_FFE_LOAD_RES_LEVEL_OFFSET)

#define HPIPE_G1_SETTINGS_4_REG			0x444
#define HPIPE_G1_SETTINGS_4_G1_DFE_RES_OFFSET	8
#define HPIPE_G1_SETTINGS_4_G1_DFE_RES_MASK	\
	(0x3 << HPIPE_G1_SETTINGS_4_G1_DFE_RES_OFFSET)

#define HPIPE_G2_SETTINGS_3_REG			0x448
#define HPIPE_G2_SETTINGS_4_REG			0x44C

#define HPIPE_G3_SETTING_3_REG			0x450
#define HPIPE_G3_FFE_CAP_SEL_OFFSET		0
#define HPIPE_G3_FFE_CAP_SEL_MASK		\
	(0xf << HPIPE_G3_FFE_CAP_SEL_OFFSET)
#define HPIPE_G3_FFE_RES_SEL_OFFSET		4
#define HPIPE_G3_FFE_RES_SEL_MASK		\
	(0x7 << HPIPE_G3_FFE_RES_SEL_OFFSET)
#define HPIPE_G3_FFE_SETTING_FORCE_OFFSET	7
#define HPIPE_G3_FFE_SETTING_FORCE_MASK		\
	(0x1 << HPIPE_G3_FFE_SETTING_FORCE_OFFSET)
#define HPIPE_G3_FFE_DEG_RES_LEVEL_OFFSET	12
#define HPIPE_G3_FFE_DEG_RES_LEVEL_MASK		\
	(0x3 << HPIPE_G3_FFE_DEG_RES_LEVEL_OFFSET)
#define HPIPE_G3_FFE_LOAD_RES_LEVEL_OFFSET	14
#define HPIPE_G3_FFE_LOAD_RES_LEVEL_MASK	\
	(0x3 << HPIPE_G3_FFE_LOAD_RES_LEVEL_OFFSET)

#define HPIPE_G3_SETTING_4_REG			0x454
#define HPIPE_G3_DFE_RES_OFFSET			8
#define HPIPE_G3_DFE_RES_MASK			\
	(0x3 << HPIPE_G3_DFE_RES_OFFSET)

#define HPIPE_DFE_CTRL_28_REG			0x49C
#define HPIPE_DFE_CTRL_28_PIPE4_OFFSET		7
#define HPIPE_DFE_CTRL_28_PIPE4_MASK		\
	(0x1 << HPIPE_DFE_CTRL_28_PIPE4_OFFSET)

#define HPIPE_G1_SETTING_5_REG			0x538
#define HPIPE_G1_SETTING_5_G1_ICP_OFFSET	0
#define HPIPE_G1_SETTING_5_G1_ICP_MASK		\
	(0xf << HPIPE_G1_SETTING_5_G1_ICP_OFFSET)

#define HPIPE_LANE_CONFIG0_REG			0x600
#define HPIPE_LANE_CONFIG0_TXDEEMPH0_OFFSET	0
#define HPIPE_LANE_CONFIG0_TXDEEMPH0_MASK	\
	(0x1 << HPIPE_LANE_CONFIG0_TXDEEMPH0_OFFSET)

#define HPIPE_LANE_CONFIG1_REG			0x604
#define HPIPE_LANE_CONFIG1_MAX_PLL_OFFSET	9
#define HPIPE_LANE_CONFIG1_MAX_PLL_MASK		\
	(0x1 << HPIPE_LANE_CONFIG1_MAX_PLL_OFFSET)
#define HPIPE_LANE_CONFIG1_GEN2_PLL_OFFSET	10
#define HPIPE_LANE_CONFIG1_GEN2_PLL_MASK	\
	(0x1 << HPIPE_LANE_CONFIG1_GEN2_PLL_OFFSET)

#define HPIPE_LANE_STATUS1_REG			0x60C
#define HPIPE_LANE_STATUS1_PCLK_EN_OFFSET	0
#define HPIPE_LANE_STATUS1_PCLK_EN_MASK		\
	(0x1 << HPIPE_LANE_STATUS1_PCLK_EN_OFFSET)

#define HPIPE_LANE_CFG4_REG                     0x620
#define HPIPE_LANE_CFG4_DFE_CTRL_OFFSET		0
#define HPIPE_LANE_CFG4_DFE_CTRL_MASK		\
	(0x7 << HPIPE_LANE_CFG4_DFE_CTRL_OFFSET)
#define HPIPE_LANE_CFG4_DFE_OVER_OFFSET		6
#define HPIPE_LANE_CFG4_DFE_OVER_MASK		\
	(0x1 << HPIPE_LANE_CFG4_DFE_OVER_OFFSET)
#define HPIPE_LANE_CFG4_SSC_CTRL_OFFSET		7
#define HPIPE_LANE_CFG4_SSC_CTRL_MASK		\
	(0x1 << HPIPE_LANE_CFG4_SSC_CTRL_OFFSET)

#define HPIPE_LANE_EQU_CONFIG_0_REG		0x69C
#define HPIPE_CFG_PHY_RC_EP_OFFSET		12
#define HPIPE_CFG_PHY_RC_EP_MASK		\
	(0x1 << HPIPE_CFG_PHY_RC_EP_OFFSET)

#define HPIPE_LANE_EQ_CFG1_REG			0x6a0
#define HPIPE_CFG_UPDATE_POLARITY_OFFSET	12
#define HPIPE_CFG_UPDATE_POLARITY_MASK		\
	(0x1 << HPIPE_CFG_UPDATE_POLARITY_OFFSET)

#define HPIPE_RST_CLK_CTRL_REG			0x704
#define HPIPE_RST_CLK_CTRL_PIPE_RST_OFFSET	0
#define HPIPE_RST_CLK_CTRL_PIPE_RST_MASK	\
	(0x1 << HPIPE_RST_CLK_CTRL_PIPE_RST_OFFSET)
#define HPIPE_RST_CLK_CTRL_FIXED_PCLK_OFFSET	2
#define HPIPE_RST_CLK_CTRL_FIXED_PCLK_MASK	\
	(0x1 << HPIPE_RST_CLK_CTRL_FIXED_PCLK_OFFSET)
#define HPIPE_RST_CLK_CTRL_PIPE_WIDTH_OFFSET	3
#define HPIPE_RST_CLK_CTRL_PIPE_WIDTH_MASK	\
	(0x1 << HPIPE_RST_CLK_CTRL_PIPE_WIDTH_OFFSET)
#define HPIPE_RST_CLK_CTRL_CORE_FREQ_SEL_OFFSET	9
#define HPIPE_RST_CLK_CTRL_CORE_FREQ_SEL_MASK	\
	(0x1 << HPIPE_RST_CLK_CTRL_CORE_FREQ_SEL_OFFSET)

#define HPIPE_TST_MODE_CTRL_REG			0x708
#define HPIPE_TST_MODE_CTRL_MODE_MARGIN_OFFSET	2
#define HPIPE_TST_MODE_CTRL_MODE_MARGIN_MASK	\
	(0x1 << HPIPE_TST_MODE_CTRL_MODE_MARGIN_OFFSET)

#define HPIPE_CLK_SRC_LO_REG			0x70c
#define HPIPE_CLK_SRC_LO_BUNDLE_PERIOD_SEL_OFFSET 1
#define HPIPE_CLK_SRC_LO_BUNDLE_PERIOD_SEL_MASK	\
	(0x1 << HPIPE_CLK_SRC_LO_BUNDLE_PERIOD_SEL_OFFSET)
#define HPIPE_CLK_SRC_LO_BUNDLE_PERIOD_SCALE_OFFSET 2
#define HPIPE_CLK_SRC_LO_BUNDLE_PERIOD_SCALE_MASK \
	(0x3 << HPIPE_CLK_SRC_LO_BUNDLE_PERIOD_SCALE_OFFSET)
#define HPIPE_CLK_SRC_LO_PLL_RDY_DL_OFFSET	5
#define HPIPE_CLK_SRC_LO_PLL_RDY_DL_MASK	\
	(0x7 << HPIPE_CLK_SRC_LO_PLL_RDY_DL_OFFSET)

#define HPIPE_CLK_SRC_HI_REG			0x710
#define HPIPE_CLK_SRC_HI_LANE_STRT_OFFSET	0
#define HPIPE_CLK_SRC_HI_LANE_STRT_MASK		\
	(0x1 << HPIPE_CLK_SRC_HI_LANE_STRT_OFFSET)
#define HPIPE_CLK_SRC_HI_LANE_BREAK_OFFSET	1
#define HPIPE_CLK_SRC_HI_LANE_BREAK_MASK	\
	(0x1 << HPIPE_CLK_SRC_HI_LANE_BREAK_OFFSET)
#define HPIPE_CLK_SRC_HI_LANE_MASTER_OFFSET	2
#define HPIPE_CLK_SRC_HI_LANE_MASTER_MASK	\
	(0x1 << HPIPE_CLK_SRC_HI_LANE_MASTER_OFFSET)
#define HPIPE_CLK_SRC_HI_MODE_PIPE_OFFSET	7
#define HPIPE_CLK_SRC_HI_MODE_PIPE_MASK		\
	(0x1 << HPIPE_CLK_SRC_HI_MODE_PIPE_OFFSET)

#define HPIPE_GLOBAL_MISC_CTRL                  0x718
#define HPIPE_GLOBAL_PM_CTRL                    0x740
#define HPIPE_GLOBAL_PM_RXDLOZ_WAIT_OFFSET	0
#define HPIPE_GLOBAL_PM_RXDLOZ_WAIT_MASK	\
	(0xFF << HPIPE_GLOBAL_PM_RXDLOZ_WAIT_OFFSET)

#endif /* _COMPHY_HPIPE_H_ */

