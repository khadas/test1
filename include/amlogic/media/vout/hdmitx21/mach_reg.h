/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#ifndef __MACH_REG_H__
#define __MACH_REG_H__

/*
 * RePacket HDMI related registers rd/wr
 */
struct reg_map {
	u32 phy_addr;
};

#define VPUCTRL_REG_IDX		0
#define HDMITX_COR_REG_IDX	1
#define HDMITX_TOP_REG_IDX	2
#define SYSCTRL_REG_IDX		3
#define PWRCTRL_REG_IDX		4
#define ANACTRL_REG_IDX		5
#define RESETCTRL_REG_IDX	6
#define CLKCTRL_REG_IDX		7
#define PADCTRL_REG_IDX		8
#define REG_IDX_END		9 /* END */

#define BASE_REG_OFFSET              24

struct reg_s {
	unsigned int reg;
	unsigned int val;
};

unsigned int hd21_read_reg(unsigned int addr);
void hd21_write_reg(unsigned int addr, unsigned int val);
void hd21_set_reg_bits(unsigned int addr, unsigned int value, unsigned int offset,
	unsigned int len);
u32 TO21_PHY_ADDR(u32 addr);
uint32_t hd_get_paddr(uint32_t addr);
unsigned int hdmitx21_rd_reg(unsigned int addr);
void hdmitx21_wr_reg(unsigned int addr, unsigned int data);
void hdmitx21_set_reg_bits(unsigned int addr, unsigned int value,
	unsigned int offset, unsigned int len);
void hdmitx21_poll_reg(unsigned int addr, unsigned int exp_data,
	unsigned int mask, unsigned int max_try);

void hdmitx21_set_default_clk(void);
void hdmitx21_set_audioclk(bool en);
void hdmitx21_venc_en(bool en, bool pi_mode);

#define ANACTRL_REG_ADDR(reg) \
	((ANACTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define PWRCTRL_REG_ADDR(reg) \
	((PWRCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define RESETCTRL_REG_ADDR(reg) \
	((RESETCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define SYSCTRL_REG_ADDR(reg) \
	((SYSCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define CLKCTRL_REG_ADDR(reg) \
	((CLKCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define VPUCTRL_REG_ADDR(reg) \
	((VPUCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define PADCTRL_REG_ADDR(reg) \
	((PADCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))

//  PAD_CTRL
#define PADCTRL_PIN_MUX_REGN          PADCTRL_REG_ADDR(0x0017)
#define PADCTRL_GPIOW_I               PADCTRL_REG_ADDR(0x0090)
//  SYS_CTRL
#define SYSCTRL_VPU_SECURE_REG0       SYSCTRL_REG_ADDR(0x0061)
#define SYSCTRL_VPU_SECURE_REG1       SYSCTRL_REG_ADDR(0x0062)
#define SYSCTRL_DEBUG_REG0            SYSCTRL_REG_ADDR(0x0090)
//  CLK_CTRL
#define CLKCTRL_OSCIN_CTRL            CLKCTRL_REG_ADDR(0x0001)
#define CLKCTRL_SYS_CLK_EN0_REG2      CLKCTRL_REG_ADDR(0x0013)
#define CLKCTRL_VID_CLK0_CTRL         CLKCTRL_REG_ADDR(0x0030)
#define CLKCTRL_VID_CLK0_CTRL2        CLKCTRL_REG_ADDR(0x0031)
#define CLKCTRL_VID_CLK0_DIV          CLKCTRL_REG_ADDR(0x0032)
#define CLKCTRL_VIID_CLK0_DIV         CLKCTRL_REG_ADDR(0x0033)
#define CLKCTRL_VIID_CLK0_CTRL        CLKCTRL_REG_ADDR(0x0034)
#define CLKCTRL_ENC0_HDMI_CLK_CTRL    CLKCTRL_REG_ADDR(0x0035)
#define CLKCTRL_ENC2_HDMI_CLK_CTRL    CLKCTRL_REG_ADDR(0x0036)
#define CLKCTRL_ENC_HDMI_CLK_CTRL     CLKCTRL_REG_ADDR(0x0037)
#define CLKCTRL_HDMI_CLK_CTRL         CLKCTRL_REG_ADDR(0x0038)
#define CLKCTRL_VID_PLL_CLK0_DIV      CLKCTRL_REG_ADDR(0x0039)
#define CLKCTRL_HTX_CLK_CTRL0         CLKCTRL_REG_ADDR(0x0047)
#define CLKCTRL_HTX_CLK_CTRL1         CLKCTRL_REG_ADDR(0x0048)
#define CLKCTRL_VID_CLK1_CTRL         CLKCTRL_REG_ADDR(0x0073)
#define CLKCTRL_VID_CLK1_CTRL2        CLKCTRL_REG_ADDR(0x0074)
#define CLKCTRL_VID_CLK1_DIV          CLKCTRL_REG_ADDR(0x0075)
#define CLKCTRL_VIID_CLK1_DIV         CLKCTRL_REG_ADDR(0x0076)
#define CLKCTRL_VIID_CLK1_CTRL        CLKCTRL_REG_ADDR(0x0077)
#define CLKCTRL_VID_CLK2_CTRL         CLKCTRL_REG_ADDR(0x0078)
#define CLKCTRL_VID_CLK2_CTRL2        CLKCTRL_REG_ADDR(0x0079)
#define CLKCTRL_VID_CLK2_DIV          CLKCTRL_REG_ADDR(0x007a)
#define CLKCTRL_VIID_CLK2_DIV         CLKCTRL_REG_ADDR(0x007b)
#define CLKCTRL_VIID_CLK2_CTRL        CLKCTRL_REG_ADDR(0x007c)
#define CLKCTRL_VID_PLL_CLK1_DIV      CLKCTRL_REG_ADDR(0x007d)
#define CLKCTRL_VID_PLL_CLK2_DIV      CLKCTRL_REG_ADDR(0x007e)
#define CLKCTRL_HDMI_VID_PLL_CLK_DIV  CLKCTRL_REG_ADDR(0x0081)
#define CLKCTRL_EFUSE_A73_CFG2        CLKCTRL_REG_ADDR(0x0128)
//  PWR_CTRL
#define PWRCTRL_PWR_ACK0              PWRCTRL_REG_ADDR(0x0000)
#define PWRCTRL_MEM_PD11              PWRCTRL_REG_ADDR(0x001b)
#define PWRCTRL_A73TOP_FSM_JUMP       PWRCTRL_REG_ADDR(0x02f7)
//  RESET_CTRL - Registers
#define RESETCTRL_RESET0              RESETCTRL_REG_ADDR(0x0000)
//  ANA_CTRL - Registers
#define ANACTRL_SYS0PLL_CTRL0         ANACTRL_REG_ADDR(0x0000)
#define ANACTRL_HDMIPLL_CTRL0         ANACTRL_REG_ADDR(0x0070)
#define ANACTRL_HDMIPLL_CTRL1         ANACTRL_REG_ADDR(0x0071)
#define ANACTRL_HDMIPLL_CTRL2         ANACTRL_REG_ADDR(0x0072)
#define ANACTRL_HDMIPLL_CTRL3         ANACTRL_REG_ADDR(0x0073)
#define ANACTRL_HDMIPLL_CTRL4         ANACTRL_REG_ADDR(0x0074)
#define ANACTRL_HDMIPLL_CTRL5         ANACTRL_REG_ADDR(0x0075)
#define ANACTRL_HDMIPLL_CTRL6         ANACTRL_REG_ADDR(0x0076)
#define ANACTRL_HDMIPLL_STS           ANACTRL_REG_ADDR(0x0077)
#define ANACTRL_HDMIPLL_VLOCK         ANACTRL_REG_ADDR(0x0079)
#define ANACTRL_HDMIPHY_CTRL0         ANACTRL_REG_ADDR(0x0080)
#define ANACTRL_HDMIPHY_CTRL1         ANACTRL_REG_ADDR(0x0081)
#define ANACTRL_HDMIPHY_CTRL2         ANACTRL_REG_ADDR(0x0082)
#define ANACTRL_HDMIPHY_CTRL3         ANACTRL_REG_ADDR(0x0083)
#define ANACTRL_HDMIPHY_CTRL4         ANACTRL_REG_ADDR(0x0084)
#define ANACTRL_HDMIPHY_CTRL5         ANACTRL_REG_ADDR(0x0085)
#define ANACTRL_HDMIPHY_STS           ANACTRL_REG_ADDR(0x0086)
#define ANACTRL_DIF_PHY_STS           ANACTRL_REG_ADDR(0x00f3)
// VPU REGISTERS
#define ENCI_VIDEO_MODE               VPUCTRL_REG_ADDR(0x1b00)
#define ENCI_VIDEO_MODE_ADV           VPUCTRL_REG_ADDR(0x1b01)
#define ENCI_VIDEO_FSC_ADJ            VPUCTRL_REG_ADDR(0x1b02)
#define ENCI_VIDEO_BRIGHT             VPUCTRL_REG_ADDR(0x1b03)
#define ENCI_VIDEO_CONT               VPUCTRL_REG_ADDR(0x1b04)
#define ENCI_VIDEO_SAT                VPUCTRL_REG_ADDR(0x1b05)
#define ENCI_VIDEO_HUE                VPUCTRL_REG_ADDR(0x1b06)
#define ENCI_VIDEO_SCH                VPUCTRL_REG_ADDR(0x1b07)
#define ENCI_SYNC_MODE                VPUCTRL_REG_ADDR(0x1b08)
#define ENCI_SYNC_CTRL                VPUCTRL_REG_ADDR(0x1b09)
#define ENCI_SYNC_HSO_BEGIN           VPUCTRL_REG_ADDR(0x1b0a)
#define ENCI_SYNC_HSO_END             VPUCTRL_REG_ADDR(0x1b0b)
#define ENCI_SYNC_VSO_EVN             VPUCTRL_REG_ADDR(0x1b0c)
#define ENCI_SYNC_VSO_ODD             VPUCTRL_REG_ADDR(0x1b0d)
#define ENCI_SYNC_VSO_EVNLN           VPUCTRL_REG_ADDR(0x1b0e)
#define ENCI_SYNC_VSO_ODDLN           VPUCTRL_REG_ADDR(0x1b0f)
#define ENCI_SYNC_HOFFST              VPUCTRL_REG_ADDR(0x1b10)
#define ENCI_SYNC_VOFFST              VPUCTRL_REG_ADDR(0x1b11)
#define ENCI_SYNC_ADJ                 VPUCTRL_REG_ADDR(0x1b12)
#define ENCI_RGB_SETTING              VPUCTRL_REG_ADDR(0x1b13)
#define ENCI_DE_H_BEGIN               VPUCTRL_REG_ADDR(0x1b16)
#define ENCI_DE_H_END                 VPUCTRL_REG_ADDR(0x1b17)
#define ENCI_DE_V_BEGIN_EVEN          VPUCTRL_REG_ADDR(0x1b18)
#define ENCI_DE_V_END_EVEN            VPUCTRL_REG_ADDR(0x1b19)
#define ENCI_DE_V_BEGIN_ODD           VPUCTRL_REG_ADDR(0x1b1a)
#define ENCI_DE_V_END_ODD             VPUCTRL_REG_ADDR(0x1b1b)
#define ENCI_VBI_SETTING              VPUCTRL_REG_ADDR(0x1b20)
#define ENCI_VBI_CCDT_EVN             VPUCTRL_REG_ADDR(0x1b21)
#define ENCI_VBI_CCDT_ODD             VPUCTRL_REG_ADDR(0x1b22)
#define ENCI_VBI_CC525_LN             VPUCTRL_REG_ADDR(0x1b23)
#define ENCI_VBI_CC625_LN             VPUCTRL_REG_ADDR(0x1b24)
#define ENCI_VBI_WSSDT                VPUCTRL_REG_ADDR(0x1b25)
#define ENCI_VBI_WSS_LN               VPUCTRL_REG_ADDR(0x1b26)
#define ENCI_VBI_CGMSDT_L             VPUCTRL_REG_ADDR(0x1b27)
#define ENCI_VBI_CGMSDT_H             VPUCTRL_REG_ADDR(0x1b28)
#define ENCI_VBI_CGMS_LN              VPUCTRL_REG_ADDR(0x1b29)
#define ENCI_VBI_TTX_HTIME            VPUCTRL_REG_ADDR(0x1b2a)
#define ENCI_VBI_TTX_LN               VPUCTRL_REG_ADDR(0x1b2b)
#define ENCI_VBI_TTXDT0               VPUCTRL_REG_ADDR(0x1b2c)
#define ENCI_VBI_TTXDT1               VPUCTRL_REG_ADDR(0x1b2d)
#define ENCI_VBI_TTXDT2               VPUCTRL_REG_ADDR(0x1b2e)
#define ENCI_VBI_TTXDT3               VPUCTRL_REG_ADDR(0x1b2f)
#define ENCI_MACV_N0                  VPUCTRL_REG_ADDR(0x1b30)
#define ENCI_MACV_N1                  VPUCTRL_REG_ADDR(0x1b31)
#define ENCI_MACV_N2                  VPUCTRL_REG_ADDR(0x1b32)
#define ENCI_MACV_N3                  VPUCTRL_REG_ADDR(0x1b33)
#define ENCI_MACV_N4                  VPUCTRL_REG_ADDR(0x1b34)
#define ENCI_MACV_N5                  VPUCTRL_REG_ADDR(0x1b35)
#define ENCI_MACV_N6                  VPUCTRL_REG_ADDR(0x1b36)
#define ENCI_MACV_N7                  VPUCTRL_REG_ADDR(0x1b37)
#define ENCI_MACV_N8                  VPUCTRL_REG_ADDR(0x1b38)
#define ENCI_MACV_N9                  VPUCTRL_REG_ADDR(0x1b39)
#define ENCI_MACV_N10                 VPUCTRL_REG_ADDR(0x1b3a)
#define ENCI_MACV_N11                 VPUCTRL_REG_ADDR(0x1b3b)
#define ENCI_MACV_N12                 VPUCTRL_REG_ADDR(0x1b3c)
#define ENCI_MACV_N13                 VPUCTRL_REG_ADDR(0x1b3d)
#define ENCI_MACV_N14                 VPUCTRL_REG_ADDR(0x1b3e)
#define ENCI_MACV_N15                 VPUCTRL_REG_ADDR(0x1b3f)
#define ENCI_MACV_N16                 VPUCTRL_REG_ADDR(0x1b40)
#define ENCI_MACV_N17                 VPUCTRL_REG_ADDR(0x1b41)
#define ENCI_MACV_N18                 VPUCTRL_REG_ADDR(0x1b42)
#define ENCI_MACV_N19                 VPUCTRL_REG_ADDR(0x1b43)
#define ENCI_MACV_N20                 VPUCTRL_REG_ADDR(0x1b44)
#define ENCI_MACV_N21                 VPUCTRL_REG_ADDR(0x1b45)
#define ENCI_MACV_N22                 VPUCTRL_REG_ADDR(0x1b46)
#define ENCI_DBG_PX_RST               VPUCTRL_REG_ADDR(0x1b48)
#define ENCI_DBG_FLDLN_RST            VPUCTRL_REG_ADDR(0x1b49)
#define ENCI_DBG_PX_INT               VPUCTRL_REG_ADDR(0x1b4a)
#define ENCI_DBG_FLDLN_INT            VPUCTRL_REG_ADDR(0x1b4b)
#define ENCI_DBG_MAXPX                VPUCTRL_REG_ADDR(0x1b4c)
#define ENCI_DBG_MAXLN                VPUCTRL_REG_ADDR(0x1b4d)
#define ENCI_MACV_MAX_AMP             VPUCTRL_REG_ADDR(0x1b50)
#define ENCI_MACV_PULSE_LO            VPUCTRL_REG_ADDR(0x1b51)
#define ENCI_MACV_PULSE_HI            VPUCTRL_REG_ADDR(0x1b52)
#define ENCI_MACV_BKP_MAX             VPUCTRL_REG_ADDR(0x1b53)
#define ENCI_CFILT_CTRL               VPUCTRL_REG_ADDR(0x1b54)
#define ENCI_CFILT7                   VPUCTRL_REG_ADDR(0x1b55)
#define ENCI_YC_DELAY                 VPUCTRL_REG_ADDR(0x1b56)
#define ENCI_VIDEO_EN                 VPUCTRL_REG_ADDR(0x1b57)
#define ENCP_VFIFO2VD_CTL             VPUCTRL_REG_ADDR(0x1b58)
#define ENCP_VFIFO2VD_PIXEL_START     VPUCTRL_REG_ADDR(0x1b59)
#define ENCP_VFIFO2VD_PIXEL_END       VPUCTRL_REG_ADDR(0x1b5a)
#define ENCP_VFIFO2VD_LINE_TOP_START  VPUCTRL_REG_ADDR(0x1b5b)
#define ENCP_VFIFO2VD_LINE_TOP_END    VPUCTRL_REG_ADDR(0x1b5c)
#define ENCP_VFIFO2VD_LINE_BOT_START  VPUCTRL_REG_ADDR(0x1b5d)
#define ENCP_VFIFO2VD_LINE_BOT_END    VPUCTRL_REG_ADDR(0x1b5e)
#define VENC_SYNC_ROUTE               VPUCTRL_REG_ADDR(0x1b60)
#define VENC_VIDEO_EXSRC              VPUCTRL_REG_ADDR(0x1b61)
#define VENC_DVI_SETTING              VPUCTRL_REG_ADDR(0x1b62)
#define VENC_VIDEO_PROG_MODE          VPUCTRL_REG_ADDR(0x1b68)
#define VENC_ENCI_LINE                VPUCTRL_REG_ADDR(0x1b69)
#define VENC_ENCI_PIXEL               VPUCTRL_REG_ADDR(0x1b6a)
#define VENC_ENCP_LINE                VPUCTRL_REG_ADDR(0x1b6b)
#define VENC_ENCP_PIXEL               VPUCTRL_REG_ADDR(0x1b6c)
#define VENC_STATA                    VPUCTRL_REG_ADDR(0x1b6d)
#define VENC_VIDEO_TST_EN             VPUCTRL_REG_ADDR(0x1b70)
#define VENC_VIDEO_TST_MDSEL          VPUCTRL_REG_ADDR(0x1b71)
#define VENC_VIDEO_TST_Y              VPUCTRL_REG_ADDR(0x1b72)
#define VENC_VIDEO_TST_CB             VPUCTRL_REG_ADDR(0x1b73)
#define VENC_VIDEO_TST_CR             VPUCTRL_REG_ADDR(0x1b74)
#define VENC_VIDEO_TST_CLRBAR_STRT    VPUCTRL_REG_ADDR(0x1b75)
#define VENC_VIDEO_TST_CLRBAR_WIDTH   VPUCTRL_REG_ADDR(0x1b76)
#define VENC_VIDEO_TST_VDCNT_STSET    VPUCTRL_REG_ADDR(0x1b77)
#define VENC_VDAC_SETTING             VPUCTRL_REG_ADDR(0x1b7e)
#define ENCP_VIDEO_EN                 VPUCTRL_REG_ADDR(0x1b80)
#define ENCP_VIDEO_SYNC_MODE          VPUCTRL_REG_ADDR(0x1b81)
#define ENCP_MACV_EN                  VPUCTRL_REG_ADDR(0x1b82)
#define ENCP_VIDEO_Y_SCL              VPUCTRL_REG_ADDR(0x1b83)
#define ENCP_VIDEO_PB_SCL             VPUCTRL_REG_ADDR(0x1b84)
#define ENCP_VIDEO_PR_SCL             VPUCTRL_REG_ADDR(0x1b85)
#define ENCP_VIDEO_SYNC_SCL           VPUCTRL_REG_ADDR(0x1b86)
#define ENCP_VIDEO_MACV_SCL           VPUCTRL_REG_ADDR(0x1b87)
#define ENCP_VIDEO_Y_OFFST            VPUCTRL_REG_ADDR(0x1b88)
#define ENCP_VIDEO_PB_OFFST           VPUCTRL_REG_ADDR(0x1b89)
#define ENCP_VIDEO_PR_OFFST           VPUCTRL_REG_ADDR(0x1b8a)
#define ENCP_VIDEO_SYNC_OFFST         VPUCTRL_REG_ADDR(0x1b8b)
#define ENCP_VIDEO_MACV_OFFST         VPUCTRL_REG_ADDR(0x1b8c)
#define ENCP_VIDEO_MODE               VPUCTRL_REG_ADDR(0x1b8d)
#define ENCP_VIDEO_MODE_ADV           VPUCTRL_REG_ADDR(0x1b8e)
#define ENCP_DBG_PX_RST               VPUCTRL_REG_ADDR(0x1b90)
#define ENCP_DBG_LN_RST               VPUCTRL_REG_ADDR(0x1b91)
#define ENCP_DBG_PX_INT               VPUCTRL_REG_ADDR(0x1b92)
#define ENCP_DBG_LN_INT               VPUCTRL_REG_ADDR(0x1b93)
#define ENCP_VIDEO_YFP1_HTIME         VPUCTRL_REG_ADDR(0x1b94)
#define ENCP_VIDEO_YFP2_HTIME         VPUCTRL_REG_ADDR(0x1b95)
#define ENCP_VIDEO_YC_DLY             VPUCTRL_REG_ADDR(0x1b96)
#define ENCP_VIDEO_MAX_PXCNT          VPUCTRL_REG_ADDR(0x1b97)
#define ENCP_VIDEO_HSPULS_BEGIN       VPUCTRL_REG_ADDR(0x1b98)
#define ENCP_VIDEO_HSPULS_END         VPUCTRL_REG_ADDR(0x1b99)
#define ENCP_VIDEO_HSPULS_SWITCH      VPUCTRL_REG_ADDR(0x1b9a)
#define ENCP_VIDEO_VSPULS_BEGIN       VPUCTRL_REG_ADDR(0x1b9b)
#define ENCP_VIDEO_VSPULS_END         VPUCTRL_REG_ADDR(0x1b9c)
#define ENCP_VIDEO_VSPULS_BLINE       VPUCTRL_REG_ADDR(0x1b9d)
#define ENCP_VIDEO_VSPULS_ELINE       VPUCTRL_REG_ADDR(0x1b9e)
#define ENCP_VIDEO_EQPULS_BEGIN       VPUCTRL_REG_ADDR(0x1b9f)
#define ENCP_VIDEO_EQPULS_END         VPUCTRL_REG_ADDR(0x1ba0)
#define ENCP_VIDEO_EQPULS_BLINE       VPUCTRL_REG_ADDR(0x1ba1)
#define ENCP_VIDEO_EQPULS_ELINE       VPUCTRL_REG_ADDR(0x1ba2)
#define ENCP_VIDEO_HAVON_END          VPUCTRL_REG_ADDR(0x1ba3)
#define ENCP_VIDEO_HAVON_BEGIN        VPUCTRL_REG_ADDR(0x1ba4)
#define ENCP_VIDEO_VAVON_ELINE        VPUCTRL_REG_ADDR(0x1baf)
#define ENCP_VIDEO_VAVON_BLINE        VPUCTRL_REG_ADDR(0x1ba6)
#define ENCP_VIDEO_HSO_BEGIN          VPUCTRL_REG_ADDR(0x1ba7)
#define ENCP_VIDEO_HSO_END            VPUCTRL_REG_ADDR(0x1ba8)
#define ENCP_VIDEO_VSO_BEGIN          VPUCTRL_REG_ADDR(0x1ba9)
#define ENCP_VIDEO_VSO_END            VPUCTRL_REG_ADDR(0x1baa)
#define ENCP_VIDEO_VSO_BLINE          VPUCTRL_REG_ADDR(0x1bab)
#define ENCP_VIDEO_VSO_ELINE          VPUCTRL_REG_ADDR(0x1bac)
#define ENCP_VIDEO_SYNC_WAVE_CURVE    VPUCTRL_REG_ADDR(0x1bad)
#define ENCP_VIDEO_MAX_LNCNT          VPUCTRL_REG_ADDR(0x1bae)
#define ENCP_VIDEO_SY_VAL             VPUCTRL_REG_ADDR(0x1bb0)
#define ENCP_VIDEO_SY2_VAL            VPUCTRL_REG_ADDR(0x1bb1)
#define ENCP_VIDEO_BLANKY_VAL         VPUCTRL_REG_ADDR(0x1bb2)
#define ENCP_VIDEO_BLANKPB_VAL        VPUCTRL_REG_ADDR(0x1bb3)
#define ENCP_VIDEO_BLANKPR_VAL        VPUCTRL_REG_ADDR(0x1bb4)
#define ENCP_VIDEO_HOFFST             VPUCTRL_REG_ADDR(0x1bb5)
#define ENCP_VIDEO_VOFFST             VPUCTRL_REG_ADDR(0x1bb6)
#define ENCP_VIDEO_RGB_CTRL           VPUCTRL_REG_ADDR(0x1bb7)
#define ENCP_VIDEO_FILT_CTRL          VPUCTRL_REG_ADDR(0x1bb8)
#define ENCP_VIDEO_OFLD_VPEQ_OFST     VPUCTRL_REG_ADDR(0x1bb9)
#define ENCP_VIDEO_OFLD_VOAV_OFST     VPUCTRL_REG_ADDR(0x1bba)
#define ENCP_VIDEO_MATRIX_CB          VPUCTRL_REG_ADDR(0x1bbb)
#define ENCP_VIDEO_MATRIX_CR          VPUCTRL_REG_ADDR(0x1bbc)
#define ENCP_VIDEO_RGBIN_CTRL         VPUCTRL_REG_ADDR(0x1bbd)
#define ENCI_MACV_N22                 VPUCTRL_REG_ADDR(0x1b46)
#define ENCI_DBG_PX_RST               VPUCTRL_REG_ADDR(0x1b48)
#define ENCI_DBG_FLDLN_RST            VPUCTRL_REG_ADDR(0x1b49)
#define ENCI_DBG_PX_INT               VPUCTRL_REG_ADDR(0x1b4a)
#define ENCI_DBG_FLDLN_INT            VPUCTRL_REG_ADDR(0x1b4b)
#define ENCI_DBG_MAXPX                VPUCTRL_REG_ADDR(0x1b4c)
#define ENCI_DBG_MAXLN                VPUCTRL_REG_ADDR(0x1b4d)
#define ENCI_MACV_MAX_AMP             VPUCTRL_REG_ADDR(0x1b50)
#define ENCI_MACV_PULSE_LO            VPUCTRL_REG_ADDR(0x1b51)
#define ENCI_MACV_PULSE_HI            VPUCTRL_REG_ADDR(0x1b52)
#define ENCI_MACV_BKP_MAX             VPUCTRL_REG_ADDR(0x1b53)
#define ENCI_CFILT_CTRL               VPUCTRL_REG_ADDR(0x1b54)
#define ENCI_CFILT7                   VPUCTRL_REG_ADDR(0x1b55)
#define ENCI_YC_DELAY                 VPUCTRL_REG_ADDR(0x1b56)
#define ENCI_VIDEO_EN                 VPUCTRL_REG_ADDR(0x1b57)
#define ENCP_MACV_MAXY_VAL            VPUCTRL_REG_ADDR(0x1bc1)
#define ENCP_MACV_1ST_PSSYNC_STRT     VPUCTRL_REG_ADDR(0x1bc2)
#define ENCP_VIDEO_BLANKPB_VAL        VPUCTRL_REG_ADDR(0x1bb3)
#define ENCP_VIDEO_BLANKPR_VAL        VPUCTRL_REG_ADDR(0x1bb4)
#define ENCP_VIDEO_HOFFST             VPUCTRL_REG_ADDR(0x1bb5)
#define ENCP_VIDEO_VOFFST             VPUCTRL_REG_ADDR(0x1bb6)
#define ENCP_MACV_STRTLINE            VPUCTRL_REG_ADDR(0x1bc7)
#define ENCP_MACV_ENDLINE             VPUCTRL_REG_ADDR(0x1bc8)
#define ENCP_MACV_TS_CNT_MAX_L        VPUCTRL_REG_ADDR(0x1bc9)
#define ENCP_MACV_TS_CNT_MAX_H        VPUCTRL_REG_ADDR(0x1bca)
#define ENCP_MACV_TIME_DOWN           VPUCTRL_REG_ADDR(0x1bcb)
#define ENCP_MACV_TIME_LO             VPUCTRL_REG_ADDR(0x1bcc)
#define ENCP_MACV_TIME_UP             VPUCTRL_REG_ADDR(0x1bcd)
#define ENCP_MACV_TIME_RST            VPUCTRL_REG_ADDR(0x1bce)
#define ENCP_VRR_CTRL                 VPUCTRL_REG_ADDR(0x1be8)
#define ENCP_VRR_ADJ_LMT              VPUCTRL_REG_ADDR(0x1be9)
#define ENCP_VRR_CTRL1                VPUCTRL_REG_ADDR(0x1bea)
#define ENCI_DVI_HSO_BEGIN            VPUCTRL_REG_ADDR(0x1c00)
#define ENCI_DVI_HSO_END              VPUCTRL_REG_ADDR(0x1c01)
#define ENCI_DVI_VSO_BLINE_EVN        VPUCTRL_REG_ADDR(0x1c02)
#define ENCI_DVI_VSO_BLINE_ODD        VPUCTRL_REG_ADDR(0x1c03)
#define ENCI_DVI_VSO_ELINE_EVN        VPUCTRL_REG_ADDR(0x1c04)
#define ENCI_DVI_VSO_ELINE_ODD        VPUCTRL_REG_ADDR(0x1c05)
#define ENCI_DVI_VSO_BEGIN_EVN        VPUCTRL_REG_ADDR(0x1c06)
#define ENCI_DVI_VSO_BEGIN_ODD        VPUCTRL_REG_ADDR(0x1c07)
#define ENCI_DVI_VSO_END_EVN          VPUCTRL_REG_ADDR(0x1c08)
#define ENCI_DVI_VSO_END_ODD          VPUCTRL_REG_ADDR(0x1c09)
#define ENCI_CFILT_CTRL2              VPUCTRL_REG_ADDR(0x1c0a)
#define ENCI_DACSEL_0                 VPUCTRL_REG_ADDR(0x1c0b)
#define ENCI_DACSEL_1                 VPUCTRL_REG_ADDR(0x1c0c)
#define ENCP_DACSEL_0                 VPUCTRL_REG_ADDR(0x1c0d)
#define ENCP_DACSEL_1                 VPUCTRL_REG_ADDR(0x1c0e)
#define ENCP_MAX_LINE_SWITCH_POINT    VPUCTRL_REG_ADDR(0x1c0f)
#define ENCI_TST_EN                   VPUCTRL_REG_ADDR(0x1c10)
#define ENCI_TST_MDSEL                VPUCTRL_REG_ADDR(0x1c11)
#define ENCI_TST_Y                    VPUCTRL_REG_ADDR(0x1c12)
#define ENCI_TST_CB                   VPUCTRL_REG_ADDR(0x1c13)
#define ENCI_TST_CR                   VPUCTRL_REG_ADDR(0x1c14)
#define ENCI_TST_CLRBAR_STRT          VPUCTRL_REG_ADDR(0x1c15)
#define ENCI_TST_CLRBAR_WIDTH         VPUCTRL_REG_ADDR(0x1c16)
#define ENCI_TST_VDCNT_STSET          VPUCTRL_REG_ADDR(0x1c17)
#define ENCI_VFIFO2VD_CTL             VPUCTRL_REG_ADDR(0x1c18)
#define ENCI_VFIFO2VD_PIXEL_START     VPUCTRL_REG_ADDR(0x1c19)
#define ENCI_VFIFO2VD_PIXEL_END       VPUCTRL_REG_ADDR(0x1c1a)
#define ENCI_VFIFO2VD_LINE_TOP_START  VPUCTRL_REG_ADDR(0x1c1b)
#define ENCI_VFIFO2VD_LINE_TOP_END    VPUCTRL_REG_ADDR(0x1c1c)
#define ENCI_VFIFO2VD_LINE_BOT_START  VPUCTRL_REG_ADDR(0x1c1d)
#define ENCI_VFIFO2VD_LINE_BOT_END    VPUCTRL_REG_ADDR(0x1c1e)
#define ENCI_VFIFO2VD_CTL2            VPUCTRL_REG_ADDR(0x1c1f)
#define ENCP_DVI_HSO_BEGIN            VPUCTRL_REG_ADDR(0x1c30)
#define ENCP_DVI_HSO_END              VPUCTRL_REG_ADDR(0x1c31)
#define ENCP_DVI_VSO_BLINE_EVN        VPUCTRL_REG_ADDR(0x1c32)
#define ENCP_DVI_VSO_BLINE_ODD        VPUCTRL_REG_ADDR(0x1c33)
#define ENCP_DVI_VSO_ELINE_EVN        VPUCTRL_REG_ADDR(0x1c34)
#define ENCP_DVI_VSO_ELINE_ODD        VPUCTRL_REG_ADDR(0x1c35)
#define ENCP_DVI_VSO_BEGIN_EVN        VPUCTRL_REG_ADDR(0x1c36)
#define ENCP_DVI_VSO_BEGIN_ODD        VPUCTRL_REG_ADDR(0x1c37)
#define ENCP_DVI_VSO_END_EVN          VPUCTRL_REG_ADDR(0x1c38)
#define ENCP_DVI_VSO_END_ODD          VPUCTRL_REG_ADDR(0x1c39)
#define ENCP_DE_H_BEGIN               VPUCTRL_REG_ADDR(0x1c3a)
#define ENCP_DE_H_END                 VPUCTRL_REG_ADDR(0x1c3b)
#define ENCP_DE_V_BEGIN_EVEN          VPUCTRL_REG_ADDR(0x1c3c)
#define ENCP_DE_V_END_EVEN            VPUCTRL_REG_ADDR(0x1c3d)
#define ENCP_DE_V_BEGIN_ODD           VPUCTRL_REG_ADDR(0x1c3e)
#define ENCP_DE_V_END_ODD             VPUCTRL_REG_ADDR(0x1c3f)
#define VPU_VENC_CTRL                 VPUCTRL_REG_ADDR(0x1cef)
#define VPU_VENCL_DITH_LUT_12         VPUCTRL_REG_ADDR(0x1cfc)
#define ENCP1_VFIFO2VD_CTL            VPUCTRL_REG_ADDR(0x2158)
#define VENC2_DVI_SETTING_MORE        VPUCTRL_REG_ADDR(0x2451)
#define VPU2_VENCL_DITH_LUT_12        VPUCTRL_REG_ADDR(0x24fc)
#define ENCP1_VFIFO2VD_CTL2           VPUCTRL_REG_ADDR(0x2250)
#define ENCP2_VFIFO2VD_CTL            VPUCTRL_REG_ADDR(0x2358)
#define ENCP2_VFIFO2VD_CTL2           VPUCTRL_REG_ADDR(0x2450)
#define VPU_CRC_CTRL                  VPUCTRL_REG_ADDR(0x2701)
#define VPU_VIU_VENC_MUX_CTRL         VPUCTRL_REG_ADDR(0x271a)
#define VPU_HDMI_SETTING              VPUCTRL_REG_ADDR(0x271b)
#define ENCI_INFO_READ                VPUCTRL_REG_ADDR(0x271c)
#define ENCP_INFO_READ                VPUCTRL_REG_ADDR(0x271d)
#define ENCT_INFO_READ                VPUCTRL_REG_ADDR(0x271e)
#define ENCL_INFO_READ                VPUCTRL_REG_ADDR(0x271f)
#define VPU_HDMI_FMT_CTRL             VPUCTRL_REG_ADDR(0x2743)
#define VPU_HDMI_DITH_CNTL            VPUCTRL_REG_ADDR(0x27fc)

#endif
