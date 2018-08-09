/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * logicore_dp_tx_regif.h
 *
 * Register interface definition for XILINX LogiCore DisplayPort v6.1 TX
 * (Source) based on Xilinx dp_v3_1 driver sources
 *
 * (C) Copyright 2016
 * Dirk Eibach,  Guntermann & Drunck GmbH, dirk.eibach@gdsys.cc
 */

#ifndef __GDSYS_LOGICORE_DP_TX_REGIF_H__
#define __GDSYS_LOGICORE_DP_TX_REGIF_H__

enum {
	/* link configuration field */
	REG_LINK_BW_SET =		0x000,
	REG_LANE_COUNT_SET =		0x004,
	REG_ENHANCED_FRAME_EN =		0x008,
	REG_TRAINING_PATTERN_SET =	0x00C,
	REG_LINK_QUAL_PATTERN_SET =	0x010,
	REG_SCRAMBLING_DISABLE =	0x014,
	REG_DOWNSPREAD_CTRL =		0x018,
	REG_SOFT_RESET =		0x01C,
};

enum {
	/* core enables */
	REG_ENABLE =			0x080,
	REG_ENABLE_MAIN_STREAM =	0x084,
	REG_ENABLE_SEC_STREAM =		0x088,
	REG_FORCE_SCRAMBLER_RESET =	0x0C0,
	REG_MST_CONFIG =		0x0D0,
	REG_LINE_RESET_DISABLE =	0x0F0,
};

enum {
	/* core ID */
	REG_VERSION =			0x0F8,
	REG_CORE_ID =			0x0FC,
};

enum {
	/* AUX channel interface */
	REG_AUX_CMD =			0x100,
	REG_AUX_WRITE_FIFO =		0x104,
	REG_AUX_ADDRESS =		0x108,
	REG_AUX_CLK_DIVIDER =		0x10C,
	REG_USER_FIFO_OVERFLOW =	0x110,
	REG_INTERRUPT_SIG_STATE =	0x130,
	REG_AUX_REPLY_DATA =		0x134,
	REG_AUX_REPLY_CODE =		0x138,
	REG_AUX_REPLY_COUNT =		0x13C,
	REG_INTERRUPT_STATUS =		0x140,
	REG_INTERRUPT_MASK =		0x144,
	REG_REPLY_DATA_COUNT =		0x148,
	REG_REPLY_STATUS =		0x14C,
	REG_HPD_DURATION =		0x150,
};

enum {
	/* main stream attributes for SST / MST STREAM1 */
	REG_STREAM1_MSA_START =		0x180,
	REG_MAIN_STREAM_HTOTAL =	0x180,
	REG_MAIN_STREAM_VTOTAL =	0x184,
	REG_MAIN_STREAM_POLARITY =	0x188,
	REG_MAIN_STREAM_HSWIDTH =	0x18C,
	REG_MAIN_STREAM_VSWIDTH =	0x190,
	REG_MAIN_STREAM_HRES =		0x194,
	REG_MAIN_STREAM_VRES =		0x198,
	REG_MAIN_STREAM_HSTART =	0x19C,
	REG_MAIN_STREAM_VSTART =	0x1A0,
	REG_MAIN_STREAM_MISC0 =		0x1A4,
	REG_MAIN_STREAM_MISC1 =		0x1A8,
	REG_M_VID =			0x1AC,
	REG_TU_SIZE =			0x1B0,
	REG_N_VID =			0x1B4,
	REG_USER_PIXEL_WIDTH =		0x1B8,
	REG_USER_DATA_COUNT_PER_LANE =	0x1BC,
	REG_MAIN_STREAM_INTERLACED =	0x1C0,
	REG_MIN_BYTES_PER_TU =		0x1C4,
	REG_FRAC_BYTES_PER_TU =		0x1C8,
	REG_INIT_WAIT =			0x1CC,
	REG_STREAM1 =			0x1D0,
	REG_STREAM2 =			0x1D4,
	REG_STREAM3 =			0x1D8,
	REG_STREAM4 =			0x1DC,
};

enum {
	/* PHY configuration status */
	REG_PHY_CONFIG =		0x200,
	REG_PHY_VOLTAGE_DIFF_LANE_0 =	0x220,
	REG_PHY_VOLTAGE_DIFF_LANE_1 =	0x224,
	REG_PHY_VOLTAGE_DIFF_LANE_2 =	0x228,
	REG_PHY_VOLTAGE_DIFF_LANE_3 =	0x22C,
	REG_PHY_TRANSMIT_PRBS7 =	0x230,
	REG_PHY_CLOCK_SELECT =		0x234,
	REG_PHY_POWER_DOWN =		0x238,
	REG_PHY_PRECURSOR_LANE_0 =	0x23C,
	REG_PHY_PRECURSOR_LANE_1 =	0x240,
	REG_PHY_PRECURSOR_LANE_2 =	0x244,
	REG_PHY_PRECURSOR_LANE_3 =	0x248,
	REG_PHY_POSTCURSOR_LANE_0 =	0x24C,
	REG_PHY_POSTCURSOR_LANE_1 =	0x250,
	REG_PHY_POSTCURSOR_LANE_2 =	0x254,
	REG_PHY_POSTCURSOR_LANE_3 =	0x258,
	REG_PHY_STATUS =		0x280,
	REG_GT_DRP_COMMAND =		0x2A0,
	REG_GT_DRP_READ_DATA =		0x2A4,
	REG_GT_DRP_CHANNEL_STATUS =	0x2A8,
};

enum {
	/* DisplayPort audio */
	REG_AUDIO_CONTROL =		0x300,
	REG_AUDIO_CHANNELS =		0x304,
	REG_AUDIO_INFO_DATA =		0x308,
	REG_AUDIO_MAUD =		0x328,
	REG_AUDIO_NAUD =		0x32C,
	REG_AUDIO_EXT_DATA =		0x330,
};

enum {
	/* HDCP */
	REG_HDCP_ENABLE =		0x400,
};

enum {
	/* main stream attributes for MST STREAM2, 3, and 4 */
	REG_STREAM2_MSA_START =		0x500,
	REG_STREAM3_MSA_START =		0x550,
	REG_STREAM4_MSA_START =		0x5A0,

	REG_VC_PAYLOAD_BUFFER_ADDR =	0x800,
};

enum {
	LINK_BW_SET_162GBPS = 0x06,
	LINK_BW_SET_270GBPS = 0x0A,
	LINK_BW_SET_540GBPS = 0x14,
};

enum {
	LANE_COUNT_SET_1 = 0x1,
	LANE_COUNT_SET_2 = 0x2,
	LANE_COUNT_SET_4 = 0x4,
};

enum {
	TRAINING_PATTERN_SET_OFF =	0x0,
	/* training pattern 1 used for clock recovery */
	TRAINING_PATTERN_SET_TP1 =	0x1,
	/* training pattern 2 used for channel equalization */
	TRAINING_PATTERN_SET_TP2 =	0x2,
	/*
	 * training pattern 3 used for channel equalization for cores with DP
	 * v1.2
	 */
	TRAINING_PATTERN_SET_TP3 =	0x3,
};

enum {
	LINK_QUAL_PATTERN_SET_OFF =		0x0,
	/* D10.2 unscrambled test pattern transmitted */
	LINK_QUAL_PATTERN_SET_D102_TEST =	0x1,
	/* symbol error rate measurement pattern transmitted */
	LINK_QUAL_PATTERN_SET_SER_MES =		0x2,
	/* pseudo random bit sequence 7 transmitted */
	LINK_QUAL_PATTERN_SET_PRBS7 =		0x3,
};

enum {
	SOFT_RESET_VIDEO_STREAM1_MASK =		0x00000001,
	SOFT_RESET_VIDEO_STREAM2_MASK =		0x00000002,
	SOFT_RESET_VIDEO_STREAM3_MASK =		0x00000004,
	SOFT_RESET_VIDEO_STREAM4_MASK =		0x00000008,
	SOFT_RESET_AUX_MASK =			0x00000080,
	SOFT_RESET_VIDEO_STREAM_ALL_MASK =	0x0000000F,
};

enum {
	MST_CONFIG_MST_EN_MASK =	0x00000001,
};

enum {
	LINE_RESET_DISABLE_MASK =	0x1,
};

#define AUX_CMD_NBYTES_TRANSFER_MASK	0x0000000F

#define AUX_CMD_SHIFT		8
#define AUX_CMD_MASK			0x00000F00
enum {
	AUX_CMD_I2C_WRITE =		0x0,
	AUX_CMD_I2C_READ =		0x1,
	AUX_CMD_I2C_WRITE_STATUS =	0x2,
	AUX_CMD_I2C_WRITE_MOT =		0x4,
	AUX_CMD_I2C_READ_MOT =		0x5,
	AUX_CMD_I2C_WRITE_STATUS_MOT =	0x6,
	AUX_CMD_WRITE =			0x8,
	AUX_CMD_READ =			0x9,
};

#define AUX_CLK_DIVIDER_VAL_MASK		0x00FF

#define AUX_CLK_DIVIDER_AUX_SIG_WIDTH_FILT_SHIFT 8
#define AUX_CLK_DIVIDER_AUX_SIG_WIDTH_FILT_MASK 0xFF00

enum {
	INTERRUPT_SIG_STATE_HPD_STATE_MASK =		0x00000001,
	INTERRUPT_SIG_STATE_REQUEST_STATE_MASK =	0x00000002,
	INTERRUPT_SIG_STATE_REPLY_STATE_MASK =		0x00000004,
	INTERRUPT_SIG_STATE_REPLY_TIMEOUT_MASK =	0x00000008,
};

enum {
	AUX_REPLY_CODE_ACK =		0x0,
	AUX_REPLY_CODE_I2C_ACK =	0x0,
	AUX_REPLY_CODE_NACK =		0x1,
	AUX_REPLY_CODE_DEFER =		0x2,
	AUX_REPLY_CODE_I2C_NACK =	0x4,
	AUX_REPLY_CODE_I2C_DEFER =	0x8,
};

enum {
	INTERRUPT_STATUS_HPD_IRQ_MASK =			0x00000001,
	INTERRUPT_STATUS_HPD_EVENT_MASK =		0x00000002,
	INTERRUPT_STATUS_REPLY_RECEIVED_MASK =		0x00000004,
	INTERRUPT_STATUS_REPLY_TIMEOUT_MASK =		0x00000008,
	INTERRUPT_STATUS_HPD_PULSE_DETECTED_MASK =	0x00000010,
	INTERRUPT_STATUS_EXT_PKT_TXD_MASK =		0x00000020,
};

enum {
	INTERRUPT_MASK_HPD_IRQ_MASK =			0x00000001,
	INTERRUPT_MASK_HPD_EVENT_MASK =			0x00000002,
	INTERRUPT_MASK_REPLY_RECEIVED_MASK =		0x00000004,
	INTERRUPT_MASK_REPLY_TIMEOUT_MASK =		0x00000008,
	INTERRUPT_MASK_HPD_PULSE_DETECTED_MASK =	0x00000010,
	INTERRUPT_MASK_EXT_PKT_TXD_MASK =		0x00000020,
};

#define REPLY_STATUS_REPLY_STATUS_STATE_SHIFT 4
#define REPLY_STATUS_REPLY_STATUS_STATE_MASK	0x00000FF0
enum {
	REPLY_STATUS_REPLY_RECEIVED_MASK =	0x00000001,
	REPLY_STATUS_REPLY_IN_PROGRESS_MASK =	0x00000002,
	REPLY_STATUS_REQUEST_IN_PROGRESS_MASK =	0x00000004,
	REPLY_STATUS_REPLY_ERROR_MASK =		0x00000008,
};

#define MAIN_STREAMX_POLARITY_VSYNC_POL_SHIFT 1
enum {
	MAIN_STREAMX_POLARITY_HSYNC_POL_MASK =	0x00000001,
	MAIN_STREAMX_POLARITY_VSYNC_POL_MASK =	0x00000002,
};

enum {
	MAIN_STREAMX_MISC0_SYNC_CLK_MASK = 0x00000001,
};

#define MAIN_STREAMX_MISC0_COMPONENT_FORMAT_SHIFT 1
#define MAIN_STREAMX_MISC0_COMPONENT_FORMAT_MASK 0x00000006
enum {
	MAIN_STREAMX_MISC0_COMPONENT_FORMAT_RGB =	0x0,
	MAIN_STREAMX_MISC0_COMPONENT_FORMAT_YCBCR422 =	0x1,
	MAIN_STREAMX_MISC0_COMPONENT_FORMAT_YCBCR444 =	0x2,
};

#define MAIN_STREAMX_MISC0_DYNAMIC_RANGE_SHIFT 3
#define MAIN_STREAMX_MISC0_DYNAMIC_RANGE_MASK 0x00000008

#define MAIN_STREAMX_MISC0_YCBCR_COLORIMETRY_SHIFT 4
#define MAIN_STREAMX_MISC0_YCBCR_COLORIMETRY_MASK 0x00000010

#define MAIN_STREAMX_MISC0_BDC_SHIFT 5
#define MAIN_STREAMX_MISC0_BDC_MASK 0x000000E0
enum {
	MAIN_STREAMX_MISC0_BDC_6BPC =	0x0,
	MAIN_STREAMX_MISC0_BDC_8BPC =	0x1,
	MAIN_STREAMX_MISC0_BDC_10BPC =	0x2,
	MAIN_STREAMX_MISC0_BDC_12BPC =	0x3,
	MAIN_STREAMX_MISC0_BDC_16BPC =	0x4,
};

enum {
	PHY_CONFIG_PHY_RESET_ENABLE_MASK =		0x0000000,
	PHY_CONFIG_PHY_RESET_MASK =			0x0000001,
	PHY_CONFIG_GTTX_RESET_MASK =			0x0000002,
	PHY_CONFIG_GT_ALL_RESET_MASK =			0x0000003,
	PHY_CONFIG_TX_PHY_PMA_RESET_MASK =		0x0000100,
	PHY_CONFIG_TX_PHY_PCS_RESET_MASK =		0x0000200,
	PHY_CONFIG_TX_PHY_POLARITY_MASK =		0x0000800,
	PHY_CONFIG_TX_PHY_PRBSFORCEERR_MASK =		0x0001000,
	PHY_CONFIG_TX_PHY_POLARITY_IND_LANE_MASK =	0x0010000,
	PHY_CONFIG_TX_PHY_POLARITY_LANE0_MASK =		0x0020000,
	PHY_CONFIG_TX_PHY_POLARITY_LANE1_MASK =		0x0040000,
	PHY_CONFIG_TX_PHY_POLARITY_LANE2_MASK =		0x0080000,
	PHY_CONFIG_TX_PHY_POLARITY_LANE3_MASK =		0x0100000,
	PHY_CONFIG_TX_PHY_8B10BEN_MASK =		0x0200000,
};

#define PHY_CONFIG_TX_PHY_LOOPBACK_SHIFT 13
#define PHY_CONFIG_TX_PHY_LOOPBACK_MASK 0x000E000

enum {
	PHY_CLOCK_SELECT_162GBPS =	0x1,
	PHY_CLOCK_SELECT_270GBPS =	0x3,
	PHY_CLOCK_SELECT_540GBPS =	0x5,
};

enum {
	VS_LEVEL_0	= 0x2,
	VS_LEVEL_1	= 0x5,
	VS_LEVEL_2	= 0x8,
	VS_LEVEL_3	= 0xF,
	VS_LEVEL_OFFSET	= 0x4,
};

enum {
	PE_LEVEL_0 =	0x00,
	PE_LEVEL_1 =	0x0E,
	PE_LEVEL_2 =	0x14,
	PE_LEVEL_3 =	0x1B,
};

enum {
	PHY_STATUS_RESET_LANE_2_3_DONE_SHIFT =		2,
	PHY_STATUS_TX_ERROR_LANE_0_SHIFT =		18,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_1_SHIFT =	20,
	PHY_STATUS_TX_ERROR_LANE_1_SHIFT =		22,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_0_SHIFT =	16,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_2_SHIFT =	24,
	PHY_STATUS_TX_ERROR_LANE_2_SHIFT =		26,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_3_SHIFT =	28,
	PHY_STATUS_TX_ERROR_LANE_3_SHIFT =		30,
};

enum {
	PHY_STATUS_RESET_LANE_0_DONE_MASK =		0x00000001,
	PHY_STATUS_RESET_LANE_1_DONE_MASK =		0x00000002,
	PHY_STATUS_RESET_LANE_2_3_DONE_MASK =		0x0000000C,
	PHY_STATUS_PLL_LANE0_1_LOCK_MASK =		0x00000010,
	PHY_STATUS_PLL_LANE2_3_LOCK_MASK =		0x00000020,
	PHY_STATUS_PLL_FABRIC_LOCK_MASK =		0x00000040,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_0_MASK =	0x00030000,
	PHY_STATUS_TX_ERROR_LANE_0_MASK =		0x000C0000,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_1_MASK =	0x00300000,
	PHY_STATUS_TX_ERROR_LANE_1_MASK =		0x00C00000,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_2_MASK =	0x03000000,
	PHY_STATUS_TX_ERROR_LANE_2_MASK =		0x0C000000,
	PHY_STATUS_TX_BUFFER_STATUS_LANE_3_MASK =	0x30000000,
	PHY_STATUS_TX_ERROR_LANE_3_MASK =		0xC0000000,
};

#define PHY_STATUS_LANE_0_READY_MASK \
	(PHY_STATUS_RESET_LANE_0_DONE_MASK | \
	PHY_STATUS_PLL_LANE0_1_LOCK_MASK)
#define PHY_STATUS_LANES_0_1_READY_MASK \
	(PHY_STATUS_LANE_0_READY_MASK | \
	PHY_STATUS_RESET_LANE_1_DONE_MASK)
/*
 * PHY_STATUS_ALL_LANES_READY_MASK seems to be missing lanes 0 and 1 in
 * Xilinx dp_v3_0 implementation
 */
#define PHY_STATUS_ALL_LANES_READY_MASK \
	(PHY_STATUS_LANES_0_1_READY_MASK | \
	PHY_STATUS_RESET_LANE_2_3_DONE_MASK | \
	PHY_STATUS_PLL_LANE2_3_LOCK_MASK)

/**
 * phy_status_lanes_ready_mask() - Generate phy status ready mask
 * @lane_count: Number of lanes for which to generate a mask
 *
 * Return: The generated phy status ready mask
 */
static inline u32 phy_status_lanes_ready_mask(u8 lane_count)
{
	if (lane_count > 2)
		return PHY_STATUS_ALL_LANES_READY_MASK;

	if (lane_count == 2)
		return PHY_STATUS_LANES_0_1_READY_MASK;

	return PHY_STATUS_LANE_0_READY_MASK;
}

#define GT_DRP_COMMAND_DRP_ADDR_MASK	0x000F
#define GT_DRP_COMMAND_DRP_RW_CMD_MASK	0x0080
#define GT_DRP_COMMAND_DRP_W_DATA_SHIFT 16
#define GT_DRP_COMMAND_DRP_W_DATA_MASK	0xFF00

#define HDCP_ENABLE_BYPASS_DISABLE_MASK	0x0001

#endif /* __GDSYS_LOGICORE_DP_TX_REGIF_H__ */
