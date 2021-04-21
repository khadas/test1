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
        uint32_t base_addr;
};

#define CBUS_REG_IDX            0
#define PERIPHS_REG_IDX         1
#define VCBUS_REG_IDX           2
#define AOBUS_REG_IDX           3
#define HHI_REG_IDX             4
#define RESET_CBUS_REG_IDX      5
#define HDMITX_REG_IDX          6
#define HDMITX_SEC_REG_IDX      7
#define ELP_ESM_REG_IDX         8
/* new added in SC2 */
#define ANACTRL_REG_IDX		9
#define PWRCTRL_REG_IDX		10
#define RESETCTRL_REG_IDX	11
#define SYSCTRL_REG_IDX		12
#define REG_IDX_END		13

#define BASE_REG_OFFSET              24

#define PERIPHS_REG_ADDR(reg) \
	((PERIPHS_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define VCBUS_REG_ADDR(reg) \
	((VCBUS_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define AOBUS_REG_ADDR(reg) \
	((AOBUS_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define HHI_REG_ADDR(reg) \
	((HHI_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define RESET_CBUS_REG_ADDR(reg) \
	((RESET_CBUS_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define HDMITX_SEC_REG_ADDR(reg) \
	((HDMITX_SEC_REG_IDX << BASE_REG_OFFSET) + (reg))/*DWC*/
#define HDMITX_REG_ADDR(reg) \
        ((HDMITX_REG_IDX << BASE_REG_OFFSET) + (reg))/*TOP*/
#define ELP_ESM_REG_ADDR(reg) \
	((ELP_ESM_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define ANACTRL_REG_ADDR(reg) \
	((ANACTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define PWRCTRL_REG_ADDR(reg) \
	((PWRCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define RESETCTRL_REG_ADDR(reg) \
	((RESETCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))
#define SYSCTRL_REG_ADDR(reg) \
	((SYSCTRL_REG_IDX << BASE_REG_OFFSET) + ((reg) << 2))

struct reg_s {
	unsigned int reg;
	unsigned int val;
};

unsigned int hd_read_reg(unsigned int addr);
void hd_write_reg(unsigned int addr, unsigned int val);
void hd_set_reg_bits(unsigned int addr, unsigned int value, unsigned int offset,
	unsigned int len);
uint32_t hd_get_paddr(uint32_t addr);
unsigned int hdmitx_rd_reg(unsigned int addr);
void hdmitx_wr_reg(unsigned int addr, unsigned int data);
void hdmitx_set_reg_bits(unsigned int addr, unsigned int value,
        unsigned int offset, unsigned int len);
void hdmitx_poll_reg(unsigned int addr, unsigned int val, unsigned long timeout);

/* REG_BASE:  REGISTER_BASE_ADDR = 0xfe000000 */
#define CLKCTRL_SYS_CLK_EN0_REG2 0x0013
#define P_CLKCTRL_SYS_CLK_EN0_REG2 HHI_REG_ADDR(CLKCTRL_SYS_CLK_EN0_REG2)
#define CLKCTRL_VID_CLK_CTRL 0x0030
#define P_CLKCTRL_VID_CLK_CTRL HHI_REG_ADDR(CLKCTRL_VID_CLK_CTRL)
#define CLKCTRL_VID_CLK_CTRL2 0x0031
#define P_CLKCTRL_VID_CLK_CTRL2 HHI_REG_ADDR(CLKCTRL_VID_CLK_CTRL2)
#define CLKCTRL_VID_CLK_DIV 0x0032
#define P_CLKCTRL_VID_CLK_DIV HHI_REG_ADDR(CLKCTRL_VID_CLK_DIV)
#define CLKCTRL_HDMI_CLK_CTRL 0x0038
#define P_CLKCTRL_HDMI_CLK_CTRL HHI_REG_ADDR(CLKCTRL_HDMI_CLK_CTRL)
#define CLKCTRL_VID_PLL_CLK_DIV 0x0039
#define P_CLKCTRL_VID_PLL_CLK_DIV HHI_REG_ADDR(CLKCTRL_VID_PLL_CLK_DIV)
#define CLKCTRL_HDCP22_CLK_CTRL 0x0040
#define P_CLKCTRL_HDCP22_CLK_CTRL HHI_REG_ADDR(CLKCTRL_HDCP22_CLK_CTRL)

/* REG_BASE:  REGISTER_BASE_ADDR = 0xfe002000 */
#define RESETCTRL_RESET0 0x0000
#define P_RESETCTRL_RESET0 RESETCTRL_REG_ADDR(RESETCTRL_RESET0)
#define RESETCTRL_RESET2 0x0002
#define P_RESETCTRL_RESET2 RESETCTRL_REG_ADDR(RESETCTRL_RESET2)

/* REG_BASE:  REGISTER_BASE_ADDR = 0xfe004000 */
#define PADCTRL_PIN_MUX_REGB 0x0b
#define P_PADCTRL_PIN_MUX_REGB PERIPHS_REG_ADDR(PADCTRL_PIN_MUX_REGB)
#define PADCTRL_GPIOH_I 0x50
#define P_PADCTRL_GPIOH_I PERIPHS_REG_ADDR(PADCTRL_GPIOH_I)

/* REG_BASE:  REGISTER_BASE_ADDR = 0xfe008000 */
#define ANACTRL_HDMIPLL_CTRL0 0x0070
#define P_ANACTRL_HDMIPLL_CTRL0 ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_CTRL0)
#define ANACTRL_HDMIPLL_CTRL1 0x0071
#define P_ANACTRL_HDMIPLL_CTRL1 ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_CTRL1)
#define ANACTRL_HDMIPLL_CTRL2 0x0072
#define P_ANACTRL_HDMIPLL_CTRL2 ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_CTRL2)
#define ANACTRL_HDMIPLL_CTRL3 0x0073
#define P_ANACTRL_HDMIPLL_CTRL3 ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_CTRL3)
#define ANACTRL_HDMIPLL_CTRL4 0x0074
#define P_ANACTRL_HDMIPLL_CTRL4 ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_CTRL4)
#define ANACTRL_HDMIPLL_CTRL5 0x0075
#define P_ANACTRL_HDMIPLL_CTRL5 ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_CTRL5)
#define ANACTRL_HDMIPLL_CTRL6 0x0076
#define P_ANACTRL_HDMIPLL_CTRL6 ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_CTRL6)
#define ANACTRL_HDMIPLL_STS 0x0077
#define P_ANACTRL_HDMIPLL_STS ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_STS)
#define ANACTRL_HDMIPLL_VLOCK 0x0079
#define P_ANACTRL_HDMIPLL_VLOCK ANACTRL_REG_ADDR(ANACTRL_HDMIPLL_VLOCK)
#define ANACTRL_HDMIPHY_CTRL0 0x0080
#define P_ANACTRL_HDMIPHY_CTRL0 ANACTRL_REG_ADDR(ANACTRL_HDMIPHY_CTRL0)
#define ANACTRL_HDMIPHY_CTRL1 0x0081
#define P_ANACTRL_HDMIPHY_CTRL1 ANACTRL_REG_ADDR(ANACTRL_HDMIPHY_CTRL1)
#define ANACTRL_HDMIPHY_CTRL2 0x0082
#define P_ANACTRL_HDMIPHY_CTRL2 ANACTRL_REG_ADDR(ANACTRL_HDMIPHY_CTRL2)
#define ANACTRL_HDMIPHY_CTRL3 0x0083
#define P_ANACTRL_HDMIPHY_CTRL3 ANACTRL_REG_ADDR(ANACTRL_HDMIPHY_CTRL3)
#define ANACTRL_HDMIPHY_CTRL4 0x0084
#define P_ANACTRL_HDMIPHY_CTRL4 ANACTRL_REG_ADDR(ANACTRL_HDMIPHY_CTRL4)
#define ANACTRL_HDMIPHY_CTRL5 0x0085
#define P_ANACTRL_HDMIPHY_CTRL5 ANACTRL_REG_ADDR(ANACTRL_HDMIPHY_CTRL5)
#define ANACTRL_HDMIPHY_STS 0x0086
#define P_ANACTRL_HDMIPHY_STS ANACTRL_REG_ADDR(ANACTRL_HDMIPHY_STS)

/* REG_BASE:  REGISTER_BASE_ADDR = 0xfe00c000 */
#define PWRCTRL_MEM_PD11 0x001b
#define P_PWRCTRL_MEM_PD11 PWRCTRL_REG_ADDR(PWRCTRL_MEM_PD11)

/* REG_BASE:  REGISTER_BASE_ADDR = 0xfe010000 */
#define SYSCTRL_DEBUG_REG0 0x90
#define P_SYSCTRL_DEBUG_REG0 SYSCTRL_REG_ADDR(SYSCTRL_DEBUG_REG0)

/* REG_BASE:  REGISTER_BASE_ADDR = 0xff000000 */
#define VENC_DVI_SETTING 0x1b62	/* register.h:8014 */
#define P_VENC_DVI_SETTING VCBUS_REG_ADDR(VENC_DVI_SETTING)

#define VENC_VIDEO_TST_EN 0x1b70
#define P_VENC_VIDEO_TST_EN VCBUS_REG_ADDR(VENC_VIDEO_TST_EN)
#define VENC_VIDEO_TST_MDSEL 0x1b71
#define P_VENC_VIDEO_TST_MDSEL VCBUS_REG_ADDR(VENC_VIDEO_TST_MDSEL)
#define VENC_VIDEO_TST_Y 0x1b72
#define P_VENC_VIDEO_TST_Y VCBUS_REG_ADDR(VENC_VIDEO_TST_Y)
#define VENC_VIDEO_TST_CB 0x1b73
#define P_VENC_VIDEO_TST_CB VCBUS_REG_ADDR(VENC_VIDEO_TST_CB)
#define VENC_VIDEO_TST_CR 0x1b74
#define P_VENC_VIDEO_TST_CR VCBUS_REG_ADDR(VENC_VIDEO_TST_CR)
#define VENC_VIDEO_TST_CLRBAR_STRT 0x1b75
#define P_VENC_VIDEO_TST_CLRBAR_STRT VCBUS_REG_ADDR(VENC_VIDEO_TST_CLRBAR_STRT)
#define VENC_VIDEO_TST_CLRBAR_WIDTH 0x1b76
#define P_VENC_VIDEO_TST_CLRBAR_WIDTH \
		VCBUS_REG_ADDR(VENC_VIDEO_TST_CLRBAR_WIDTH)
#define VENC_VIDEO_TST_VDCNT_STSET 0x1b77
#define P_VENC_VIDEO_TST_VDCNT_STSET VCBUS_REG_ADDR(VENC_VIDEO_TST_VDCNT_STSET)
#define VENC_VDAC_SETTING 0x1b7e
#define P_VENC_VDAC_SETTING VCBUS_REG_ADDR(VENC_VDAC_SETTING)
#define ENCP_VIDEO_EN 0x1b80	/* register.h:8078 */
#define P_ENCP_VIDEO_EN VCBUS_REG_ADDR(ENCP_VIDEO_EN)
#define ENCP_VIDEO_SYNC_MODE 0x1b81	/* register.h:8079 */
#define P_ENCP_VIDEO_SYNC_MODE VCBUS_REG_ADDR(ENCP_VIDEO_SYNC_MODE)
#define ENCP_MACV_EN 0x1b82	/* register.h:8080 */
#define P_ENCP_MACV_EN VCBUS_REG_ADDR(ENCP_MACV_EN)
#define ENCP_VIDEO_Y_SCL 0x1b83	/* register.h:8081 */
#define P_ENCP_VIDEO_Y_SCL VCBUS_REG_ADDR(ENCP_VIDEO_Y_SCL)
#define ENCP_VIDEO_PB_SCL 0x1b84	/* register.h:8082 */
#define P_ENCP_VIDEO_PB_SCL VCBUS_REG_ADDR(ENCP_VIDEO_PB_SCL)
#define ENCP_VIDEO_PR_SCL 0x1b85	/* register.h:8083 */
#define P_ENCP_VIDEO_PR_SCL VCBUS_REG_ADDR(ENCP_VIDEO_PR_SCL)
#define ENCP_VIDEO_SYNC_SCL 0x1b86	/* register.h:8084 */
#define P_ENCP_VIDEO_SYNC_SCL VCBUS_REG_ADDR(ENCP_VIDEO_SYNC_SCL)
#define ENCP_VIDEO_MACV_SCL 0x1b87	/* register.h:8085 */
#define P_ENCP_VIDEO_MACV_SCL VCBUS_REG_ADDR(ENCP_VIDEO_MACV_SCL)
#define ENCP_VIDEO_Y_OFFST 0x1b88	/* register.h:8086 */
#define P_ENCP_VIDEO_Y_OFFST VCBUS_REG_ADDR(ENCP_VIDEO_Y_OFFST)
#define ENCP_VIDEO_PB_OFFST 0x1b89	/* register.h:8087 */
#define P_ENCP_VIDEO_PB_OFFST VCBUS_REG_ADDR(ENCP_VIDEO_PB_OFFST)
#define ENCP_VIDEO_PR_OFFST 0x1b8a	/* register.h:8088 */
#define P_ENCP_VIDEO_PR_OFFST VCBUS_REG_ADDR(ENCP_VIDEO_PR_OFFST)
#define ENCP_VIDEO_SYNC_OFFST 0x1b8b	/* register.h:8089 */
#define P_ENCP_VIDEO_SYNC_OFFST VCBUS_REG_ADDR(ENCP_VIDEO_SYNC_OFFST)
#define ENCP_VIDEO_MACV_OFFST 0x1b8c	/* register.h:8090 */
#define P_ENCP_VIDEO_MACV_OFFST VCBUS_REG_ADDR(ENCP_VIDEO_MACV_OFFST)
#define ENCP_VIDEO_MODE 0x1b8d	/* register.h:8092 */
#define P_ENCP_VIDEO_MODE VCBUS_REG_ADDR(ENCP_VIDEO_MODE)
#define ENCP_VIDEO_MODE_ADV 0x1b8e	/* register.h:8093 */
#define P_ENCP_VIDEO_MODE_ADV VCBUS_REG_ADDR(ENCP_VIDEO_MODE_ADV)
#define ENCP_DBG_PX_RST 0x1b90	/* register.h:8095 */
#define P_ENCP_DBG_PX_RST VCBUS_REG_ADDR(ENCP_DBG_PX_RST)
#define ENCP_DBG_LN_RST 0x1b91	/* register.h:8096 */
#define P_ENCP_DBG_LN_RST VCBUS_REG_ADDR(ENCP_DBG_LN_RST)
#define ENCP_DBG_PX_INT 0x1b92	/* register.h:8097 */
#define P_ENCP_DBG_PX_INT VCBUS_REG_ADDR(ENCP_DBG_PX_INT)
#define ENCP_DBG_LN_INT 0x1b93	/* register.h:8098 */
#define P_ENCP_DBG_LN_INT VCBUS_REG_ADDR(ENCP_DBG_LN_INT)
#define ENCP_VIDEO_YFP1_HTIME 0x1b94	/* register.h:8100 */
#define P_ENCP_VIDEO_YFP1_HTIME VCBUS_REG_ADDR(ENCP_VIDEO_YFP1_HTIME)
#define ENCP_VIDEO_YFP2_HTIME 0x1b95	/* register.h:8101 */
#define P_ENCP_VIDEO_YFP2_HTIME VCBUS_REG_ADDR(ENCP_VIDEO_YFP2_HTIME)
#define ENCP_VIDEO_YC_DLY 0x1b96	/* register.h:8102 */
#define P_ENCP_VIDEO_YC_DLY VCBUS_REG_ADDR(ENCP_VIDEO_YC_DLY)
#define ENCP_VIDEO_MAX_PXCNT 0x1b97	/* register.h:8103 */
#define P_ENCP_VIDEO_MAX_PXCNT VCBUS_REG_ADDR(ENCP_VIDEO_MAX_PXCNT)
#define ENCP_VIDEO_HSPULS_BEGIN 0x1b98	/* register.h:8104 */
#define P_ENCP_VIDEO_HSPULS_BEGIN VCBUS_REG_ADDR(ENCP_VIDEO_HSPULS_BEGIN)
#define ENCP_VIDEO_HSPULS_END 0x1b99	/* register.h:8105 */
#define P_ENCP_VIDEO_HSPULS_END VCBUS_REG_ADDR(ENCP_VIDEO_HSPULS_END)
#define ENCP_VIDEO_HSPULS_SWITCH 0x1b9a	/* register.h:8106 */
#define P_ENCP_VIDEO_HSPULS_SWITCH VCBUS_REG_ADDR(ENCP_VIDEO_HSPULS_SWITCH)
#define ENCP_VIDEO_VSPULS_BEGIN 0x1b9b	/* register.h:8107 */
#define P_ENCP_VIDEO_VSPULS_BEGIN VCBUS_REG_ADDR(ENCP_VIDEO_VSPULS_BEGIN)
#define ENCP_VIDEO_VSPULS_END 0x1b9c	/* register.h:8108 */
#define P_ENCP_VIDEO_VSPULS_END VCBUS_REG_ADDR(ENCP_VIDEO_VSPULS_END)
#define ENCP_VIDEO_VSPULS_BLINE 0x1b9d	/* register.h:8109 */
#define P_ENCP_VIDEO_VSPULS_BLINE VCBUS_REG_ADDR(ENCP_VIDEO_VSPULS_BLINE)
#define ENCP_VIDEO_VSPULS_ELINE 0x1b9e	/* register.h:8110 */
#define P_ENCP_VIDEO_VSPULS_ELINE VCBUS_REG_ADDR(ENCP_VIDEO_VSPULS_ELINE)
#define ENCP_VIDEO_EQPULS_BEGIN 0x1b9f	/* register.h:8111 */
#define P_ENCP_VIDEO_EQPULS_BEGIN VCBUS_REG_ADDR(ENCP_VIDEO_EQPULS_BEGIN)
#define ENCP_VIDEO_EQPULS_END 0x1ba0	/* register.h:8112 */
#define P_ENCP_VIDEO_EQPULS_END VCBUS_REG_ADDR(ENCP_VIDEO_EQPULS_END)
#define ENCP_VIDEO_EQPULS_BLINE 0x1ba1	/* register.h:8113 */
#define P_ENCP_VIDEO_EQPULS_BLINE VCBUS_REG_ADDR(ENCP_VIDEO_EQPULS_BLINE)
#define ENCP_VIDEO_EQPULS_ELINE 0x1ba2	/* register.h:8114 */
#define P_ENCP_VIDEO_EQPULS_ELINE VCBUS_REG_ADDR(ENCP_VIDEO_EQPULS_ELINE)
#define ENCP_VIDEO_HAVON_END 0x1ba3	/* register.h:8115 */
#define P_ENCP_VIDEO_HAVON_END VCBUS_REG_ADDR(ENCP_VIDEO_HAVON_END)
#define ENCP_VIDEO_HAVON_BEGIN 0x1ba4	/* register.h:8116 */
#define P_ENCP_VIDEO_HAVON_BEGIN VCBUS_REG_ADDR(ENCP_VIDEO_HAVON_BEGIN)
#define ENCP_VIDEO_VAVON_ELINE 0x1baf	/* register.h:8117 */
#define P_ENCP_VIDEO_VAVON_ELINE VCBUS_REG_ADDR(ENCP_VIDEO_VAVON_ELINE)
#define ENCP_VIDEO_VAVON_BLINE 0x1ba6	/* register.h:8118 */
#define P_ENCP_VIDEO_VAVON_BLINE VCBUS_REG_ADDR(ENCP_VIDEO_VAVON_BLINE)
#define ENCP_VIDEO_HSO_BEGIN 0x1ba7	/* register.h:8119 */
#define P_ENCP_VIDEO_HSO_BEGIN VCBUS_REG_ADDR(ENCP_VIDEO_HSO_BEGIN)
#define ENCP_VIDEO_HSO_END 0x1ba8	/* register.h:8120 */
#define P_ENCP_VIDEO_HSO_END VCBUS_REG_ADDR(ENCP_VIDEO_HSO_END)
#define ENCP_VIDEO_VSO_BEGIN 0x1ba9	/* register.h:8121 */
#define P_ENCP_VIDEO_VSO_BEGIN VCBUS_REG_ADDR(ENCP_VIDEO_VSO_BEGIN)
#define ENCP_VIDEO_VSO_END 0x1baa	/* register.h:8122 */
#define P_ENCP_VIDEO_VSO_END VCBUS_REG_ADDR(ENCP_VIDEO_VSO_END)
#define ENCP_VIDEO_VSO_BLINE 0x1bab	/* register.h:8123 */
#define P_ENCP_VIDEO_VSO_BLINE VCBUS_REG_ADDR(ENCP_VIDEO_VSO_BLINE)
#define ENCP_VIDEO_VSO_ELINE 0x1bac	/* register.h:8124 */
#define P_ENCP_VIDEO_VSO_ELINE VCBUS_REG_ADDR(ENCP_VIDEO_VSO_ELINE)
#define ENCP_VIDEO_SYNC_WAVE_CURVE 0x1bad	/* register.h:8125 */
#define P_ENCP_VIDEO_SYNC_WAVE_CURVE VCBUS_REG_ADDR(ENCP_VIDEO_SYNC_WAVE_CURVE)
#define ENCP_VIDEO_MAX_LNCNT 0x1bae	/* register.h:8126 */
#define P_ENCP_VIDEO_MAX_LNCNT VCBUS_REG_ADDR(ENCP_VIDEO_MAX_LNCNT)
#define ENCP_VIDEO_SY_VAL 0x1bb0	/* register.h:8127 */
#define P_ENCP_VIDEO_SY_VAL VCBUS_REG_ADDR(ENCP_VIDEO_SY_VAL)
#define ENCP_VIDEO_SY2_VAL 0x1bb1	/* register.h:8128 */
#define P_ENCP_VIDEO_SY2_VAL VCBUS_REG_ADDR(ENCP_VIDEO_SY2_VAL)
#define ENCP_VIDEO_BLANKY_VAL 0x1bb2	/* register.h:8129 */
#define P_ENCP_VIDEO_BLANKY_VAL VCBUS_REG_ADDR(ENCP_VIDEO_BLANKY_VAL)
#define ENCP_VIDEO_BLANKPB_VAL 0x1bb3	/* register.h:8130 */
#define P_ENCP_VIDEO_BLANKPB_VAL VCBUS_REG_ADDR(ENCP_VIDEO_BLANKPB_VAL)
#define ENCP_VIDEO_BLANKPR_VAL 0x1bb4	/* register.h:8131 */
#define P_ENCP_VIDEO_BLANKPR_VAL VCBUS_REG_ADDR(ENCP_VIDEO_BLANKPR_VAL)
#define ENCP_VIDEO_HOFFST 0x1bb5	/* register.h:8132 */
#define P_ENCP_VIDEO_HOFFST VCBUS_REG_ADDR(ENCP_VIDEO_HOFFST)
#define ENCP_VIDEO_VOFFST 0x1bb6	/* register.h:8133 */
#define P_ENCP_VIDEO_VOFFST VCBUS_REG_ADDR(ENCP_VIDEO_VOFFST)
#define ENCP_VIDEO_RGB_CTRL 0x1bb7	/* register.h:8134 */
#define P_ENCP_VIDEO_RGB_CTRL VCBUS_REG_ADDR(ENCP_VIDEO_RGB_CTRL)
#define ENCP_VIDEO_FILT_CTRL 0x1bb8	/* register.h:8135 */
#define P_ENCP_VIDEO_FILT_CTRL VCBUS_REG_ADDR(ENCP_VIDEO_FILT_CTRL)
#define ENCP_VIDEO_OFLD_VPEQ_OFST 0x1bb9	/* register.h:8136 */
#define P_ENCP_VIDEO_OFLD_VPEQ_OFST VCBUS_REG_ADDR(ENCP_VIDEO_OFLD_VPEQ_OFST)
#define ENCP_VIDEO_OFLD_VOAV_OFST 0x1bba	/* register.h:8137 */
#define P_ENCP_VIDEO_OFLD_VOAV_OFST VCBUS_REG_ADDR(ENCP_VIDEO_OFLD_VOAV_OFST)
#define ENCP_VIDEO_MATRIX_CB 0x1bbb	/* register.h:8138 */
#define P_ENCP_VIDEO_MATRIX_CB VCBUS_REG_ADDR(ENCP_VIDEO_MATRIX_CB)
#define ENCP_VIDEO_MATRIX_CR 0x1bbc	/* register.h:8139 */
#define P_ENCP_VIDEO_MATRIX_CR VCBUS_REG_ADDR(ENCP_VIDEO_MATRIX_CR)
#define ENCP_VIDEO_RGBIN_CTRL 0x1bbd	/* register.h:8140 */
#define P_ENCP_VIDEO_RGBIN_CTRL VCBUS_REG_ADDR(ENCP_VIDEO_RGBIN_CTRL)
#define ENCP_MACV_BLANKY_VAL 0x1bc0	/* register.h:8142 */
#define P_ENCP_MACV_BLANKY_VAL VCBUS_REG_ADDR(ENCP_MACV_BLANKY_VAL)
#define ENCP_MACV_MAXY_VAL 0x1bc1	/* register.h:8143 */
#define P_ENCP_MACV_MAXY_VAL VCBUS_REG_ADDR(ENCP_MACV_MAXY_VAL)
#define ENCP_MACV_1ST_PSSYNC_STRT 0x1bc2	/* register.h:8144 */
#define P_ENCP_MACV_1ST_PSSYNC_STRT VCBUS_REG_ADDR(ENCP_MACV_1ST_PSSYNC_STRT)
#define ENCP_MACV_PSSYNC_STRT 0x1bc3	/* register.h:8145 */
#define P_ENCP_MACV_PSSYNC_STRT VCBUS_REG_ADDR(ENCP_MACV_PSSYNC_STRT)
#define ENCP_MACV_AGC_STRT 0x1bc4	/* register.h:8146 */
#define P_ENCP_MACV_AGC_STRT VCBUS_REG_ADDR(ENCP_MACV_AGC_STRT)
#define ENCP_MACV_AGC_END 0x1bc5	/* register.h:8147 */
#define P_ENCP_MACV_AGC_END VCBUS_REG_ADDR(ENCP_MACV_AGC_END)
#define ENCP_MACV_WAVE_END 0x1bc6	/* register.h:8148 */
#define P_ENCP_MACV_WAVE_END VCBUS_REG_ADDR(ENCP_MACV_WAVE_END)
#define ENCP_MACV_STRTLINE 0x1bc7	/* register.h:8149 */
#define P_ENCP_MACV_STRTLINE VCBUS_REG_ADDR(ENCP_MACV_STRTLINE)
#define ENCP_MACV_ENDLINE 0x1bc8	/* register.h:8150 */
#define P_ENCP_MACV_ENDLINE VCBUS_REG_ADDR(ENCP_MACV_ENDLINE)
#define ENCP_MACV_TS_CNT_MAX_L 0x1bc9	/* register.h:8151 */
#define P_ENCP_MACV_TS_CNT_MAX_L VCBUS_REG_ADDR(ENCP_MACV_TS_CNT_MAX_L)
#define ENCP_MACV_TS_CNT_MAX_H 0x1bca	/* register.h:8152 */
#define P_ENCP_MACV_TS_CNT_MAX_H VCBUS_REG_ADDR(ENCP_MACV_TS_CNT_MAX_H)
#define ENCP_MACV_TIME_DOWN 0x1bcb	/* register.h:8153 */
#define P_ENCP_MACV_TIME_DOWN VCBUS_REG_ADDR(ENCP_MACV_TIME_DOWN)
#define ENCP_MACV_TIME_LO 0x1bcc	/* register.h:8154 */
#define P_ENCP_MACV_TIME_LO VCBUS_REG_ADDR(ENCP_MACV_TIME_LO)
#define ENCP_MACV_TIME_UP 0x1bcd	/* register.h:8155 */
#define P_ENCP_MACV_TIME_UP VCBUS_REG_ADDR(ENCP_MACV_TIME_UP)
#define ENCP_MACV_TIME_RST 0x1bce	/* register.h:8156 */
#define P_ENCP_MACV_TIME_RST VCBUS_REG_ADDR(ENCP_MACV_TIME_RST)
#define ENCP_VBI_CTRL 0x1bd0	/* register.h:8158 */
#define P_ENCP_VBI_CTRL VCBUS_REG_ADDR(ENCP_VBI_CTRL)
#define ENCP_VBI_SETTING 0x1bd1	/* register.h:8159 */
#define P_ENCP_VBI_SETTING VCBUS_REG_ADDR(ENCP_VBI_SETTING)
#define ENCP_VBI_BEGIN 0x1bd2	/* register.h:8160 */
#define P_ENCP_VBI_BEGIN VCBUS_REG_ADDR(ENCP_VBI_BEGIN)
#define ENCP_VBI_WIDTH 0x1bd3	/* register.h:8161 */
#define P_ENCP_VBI_WIDTH VCBUS_REG_ADDR(ENCP_VBI_WIDTH)
#define ENCP_VBI_HVAL 0x1bd4	/* register.h:8162 */
#define P_ENCP_VBI_HVAL VCBUS_REG_ADDR(ENCP_VBI_HVAL)
#define ENCP_VBI_DATA0 0x1bd5	/* register.h:8163 */
#define P_ENCP_VBI_DATA0 VCBUS_REG_ADDR(ENCP_VBI_DATA0)
#define ENCP_VBI_DATA1 0x1bd6	/* register.h:8164 */
#define P_ENCP_VBI_DATA1 VCBUS_REG_ADDR(ENCP_VBI_DATA1)

#define ENCI_VIDEO_MODE 0x1b00	/* register.h:8185 */
#define P_ENCI_VIDEO_MODE VCBUS_REG_ADDR(ENCI_VIDEO_MODE)
#define ENCI_VIDEO_MODE_ADV 0x1b01	/* register.h:8186 */
#define P_ENCI_VIDEO_MODE_ADV VCBUS_REG_ADDR(ENCI_VIDEO_MODE_ADV)
#define ENCI_VIDEO_FSC_ADJ 0x1b02	/* register.h:8187 */
#define P_ENCI_VIDEO_FSC_ADJ VCBUS_REG_ADDR(ENCI_VIDEO_FSC_ADJ)
#define ENCI_VIDEO_BRIGHT 0x1b03	/* register.h:8188 */
#define P_ENCI_VIDEO_BRIGHT VCBUS_REG_ADDR(ENCI_VIDEO_BRIGHT)
#define ENCI_VIDEO_CONT 0x1b04	/* register.h:8189 */
#define P_ENCI_VIDEO_CONT VCBUS_REG_ADDR(ENCI_VIDEO_CONT)
#define ENCI_VIDEO_SAT 0x1b05	/* register.h:8190 */
#define P_ENCI_VIDEO_SAT VCBUS_REG_ADDR(ENCI_VIDEO_SAT)
#define ENCI_VIDEO_HUE 0x1b06	/* register.h:8191 */
#define P_ENCI_VIDEO_HUE VCBUS_REG_ADDR(ENCI_VIDEO_HUE)
#define ENCI_VIDEO_SCH 0x1b07	/* register.h:8192 */
#define P_ENCI_VIDEO_SCH VCBUS_REG_ADDR(ENCI_VIDEO_SCH)
#define ENCI_SYNC_MODE 0x1b08	/* register.h:8193 */
#define P_ENCI_SYNC_MODE VCBUS_REG_ADDR(ENCI_SYNC_MODE)
#define ENCI_SYNC_CTRL 0x1b09	/* register.h:8194 */
#define P_ENCI_SYNC_CTRL VCBUS_REG_ADDR(ENCI_SYNC_CTRL)
#define ENCI_SYNC_HSO_BEGIN 0x1b0a	/* register.h:8195 */
#define P_ENCI_SYNC_HSO_BEGIN VCBUS_REG_ADDR(ENCI_SYNC_HSO_BEGIN)
#define ENCI_SYNC_HSO_END 0x1b0b	/* register.h:8196 */
#define P_ENCI_SYNC_HSO_END VCBUS_REG_ADDR(ENCI_SYNC_HSO_END)
#define ENCI_SYNC_VSO_EVN 0x1b0c	/* register.h:8197 */
#define P_ENCI_SYNC_VSO_EVN VCBUS_REG_ADDR(ENCI_SYNC_VSO_EVN)
#define ENCI_SYNC_VSO_ODD 0x1b0d	/* register.h:8198 */
#define P_ENCI_SYNC_VSO_ODD VCBUS_REG_ADDR(ENCI_SYNC_VSO_ODD)
#define ENCI_SYNC_VSO_EVNLN 0x1b0e	/* register.h:8199 */
#define P_ENCI_SYNC_VSO_EVNLN VCBUS_REG_ADDR(ENCI_SYNC_VSO_EVNLN)
#define ENCI_SYNC_VSO_ODDLN 0x1b0f	/* register.h:8200 */
#define P_ENCI_SYNC_VSO_ODDLN VCBUS_REG_ADDR(ENCI_SYNC_VSO_ODDLN)
#define ENCI_SYNC_HOFFST 0x1b10	/* register.h:8201 */
#define P_ENCI_SYNC_HOFFST VCBUS_REG_ADDR(ENCI_SYNC_HOFFST)
#define ENCI_SYNC_VOFFST 0x1b11	/* register.h:8202 */
#define P_ENCI_SYNC_VOFFST VCBUS_REG_ADDR(ENCI_SYNC_VOFFST)
#define ENCI_SYNC_ADJ 0x1b12	/* register.h:8203 */
#define P_ENCI_SYNC_ADJ VCBUS_REG_ADDR(ENCI_SYNC_ADJ)
#define ENCI_RGB_SETTING 0x1b13	/* register.h:8204 */
#define P_ENCI_RGB_SETTING VCBUS_REG_ADDR(ENCI_RGB_SETTING)
#define ENCI_DE_H_BEGIN 0x1b16	/* register.h:8207 */
#define P_ENCI_DE_H_BEGIN VCBUS_REG_ADDR(ENCI_DE_H_BEGIN)
#define ENCI_DE_H_END 0x1b17	/* register.h:8208 */
#define P_ENCI_DE_H_END VCBUS_REG_ADDR(ENCI_DE_H_END)
#define ENCI_DE_V_BEGIN_EVEN 0x1b18	/* register.h:8209 */
#define P_ENCI_DE_V_BEGIN_EVEN VCBUS_REG_ADDR(ENCI_DE_V_BEGIN_EVEN)
#define ENCI_DE_V_END_EVEN 0x1b19	/* register.h:8210 */
#define P_ENCI_DE_V_END_EVEN VCBUS_REG_ADDR(ENCI_DE_V_END_EVEN)
#define ENCI_DE_V_BEGIN_ODD 0x1b1a	/* register.h:8211 */
#define P_ENCI_DE_V_BEGIN_ODD VCBUS_REG_ADDR(ENCI_DE_V_BEGIN_ODD)
#define ENCI_DE_V_END_ODD 0x1b1b	/* register.h:8212 */
#define P_ENCI_DE_V_END_ODD VCBUS_REG_ADDR(ENCI_DE_V_END_ODD)
#define ENCI_VBI_SETTING 0x1b20	/* register.h:8213 */
#define P_ENCI_VBI_SETTING VCBUS_REG_ADDR(ENCI_VBI_SETTING)
#define ENCI_VBI_CCDT_EVN 0x1b21	/* register.h:8214 */
#define P_ENCI_VBI_CCDT_EVN VCBUS_REG_ADDR(ENCI_VBI_CCDT_EVN)
#define ENCI_VBI_CCDT_ODD 0x1b22	/* register.h:8215 */
#define P_ENCI_VBI_CCDT_ODD VCBUS_REG_ADDR(ENCI_VBI_CCDT_ODD)
#define ENCI_VBI_CC525_LN 0x1b23	/* register.h:8216 */
#define P_ENCI_VBI_CC525_LN VCBUS_REG_ADDR(ENCI_VBI_CC525_LN)
#define ENCI_VBI_CC625_LN 0x1b24	/* register.h:8217 */
#define P_ENCI_VBI_CC625_LN VCBUS_REG_ADDR(ENCI_VBI_CC625_LN)
#define ENCI_VBI_WSSDT 0x1b25	/* register.h:8218 */
#define P_ENCI_VBI_WSSDT VCBUS_REG_ADDR(ENCI_VBI_WSSDT)
#define ENCI_VBI_WSS_LN 0x1b26	/* register.h:8219 */
#define P_ENCI_VBI_WSS_LN VCBUS_REG_ADDR(ENCI_VBI_WSS_LN)
#define ENCI_VBI_CGMSDT_L 0x1b27	/* register.h:8220 */
#define P_ENCI_VBI_CGMSDT_L VCBUS_REG_ADDR(ENCI_VBI_CGMSDT_L)
#define ENCI_VBI_CGMSDT_H 0x1b28	/* register.h:8221 */
#define P_ENCI_VBI_CGMSDT_H VCBUS_REG_ADDR(ENCI_VBI_CGMSDT_H)
#define ENCI_VBI_CGMS_LN 0x1b29	/* register.h:8222 */
#define P_ENCI_VBI_CGMS_LN VCBUS_REG_ADDR(ENCI_VBI_CGMS_LN)
#define ENCI_VBI_TTX_HTIME 0x1b2a	/* register.h:8223 */
#define P_ENCI_VBI_TTX_HTIME VCBUS_REG_ADDR(ENCI_VBI_TTX_HTIME)
#define ENCI_VBI_TTX_LN 0x1b2b	/* register.h:8224 */
#define P_ENCI_VBI_TTX_LN VCBUS_REG_ADDR(ENCI_VBI_TTX_LN)
#define ENCI_VBI_TTXDT0 0x1b2c	/* register.h:8225 */
#define P_ENCI_VBI_TTXDT0 VCBUS_REG_ADDR(ENCI_VBI_TTXDT0)
#define ENCI_VBI_TTXDT1 0x1b2d	/* register.h:8226 */
#define P_ENCI_VBI_TTXDT1 VCBUS_REG_ADDR(ENCI_VBI_TTXDT1)
#define ENCI_VBI_TTXDT2 0x1b2e	/* register.h:8227 */
#define P_ENCI_VBI_TTXDT2 VCBUS_REG_ADDR(ENCI_VBI_TTXDT2)
#define ENCI_VBI_TTXDT3 0x1b2f	/* register.h:8228 */
#define P_ENCI_VBI_TTXDT3 VCBUS_REG_ADDR(ENCI_VBI_TTXDT3)
#define ENCI_MACV_N0 0x1b30	/* register.h:8229 */
#define P_ENCI_MACV_N0 VCBUS_REG_ADDR(ENCI_MACV_N0)
#define ENCI_MACV_N1 0x1b31	/* register.h:8230 */
#define P_ENCI_MACV_N1 VCBUS_REG_ADDR(ENCI_MACV_N1)
#define ENCI_MACV_N2 0x1b32	/* register.h:8231 */
#define P_ENCI_MACV_N2 VCBUS_REG_ADDR(ENCI_MACV_N2)
#define ENCI_MACV_N3 0x1b33	/* register.h:8232 */
#define P_ENCI_MACV_N3 VCBUS_REG_ADDR(ENCI_MACV_N3)
#define ENCI_MACV_N4 0x1b34	/* register.h:8233 */
#define P_ENCI_MACV_N4 VCBUS_REG_ADDR(ENCI_MACV_N4)
#define ENCI_MACV_N5 0x1b35	/* register.h:8234 */
#define P_ENCI_MACV_N5 VCBUS_REG_ADDR(ENCI_MACV_N5)
#define ENCI_MACV_N6 0x1b36	/* register.h:8235 */
#define P_ENCI_MACV_N6 VCBUS_REG_ADDR(ENCI_MACV_N6)
#define ENCI_MACV_N7 0x1b37	/* register.h:8236 */
#define P_ENCI_MACV_N7 VCBUS_REG_ADDR(ENCI_MACV_N7)
#define ENCI_MACV_N8 0x1b38	/* register.h:8237 */
#define P_ENCI_MACV_N8 VCBUS_REG_ADDR(ENCI_MACV_N8)
#define ENCI_MACV_N9 0x1b39	/* register.h:8238 */
#define P_ENCI_MACV_N9 VCBUS_REG_ADDR(ENCI_MACV_N9)
#define ENCI_MACV_N10 0x1b3a	/* register.h:8239 */
#define P_ENCI_MACV_N10 VCBUS_REG_ADDR(ENCI_MACV_N10)
#define ENCI_MACV_N11 0x1b3b	/* register.h:8240 */
#define P_ENCI_MACV_N11 VCBUS_REG_ADDR(ENCI_MACV_N11)
#define ENCI_MACV_N12 0x1b3c	/* register.h:8241 */
#define P_ENCI_MACV_N12 VCBUS_REG_ADDR(ENCI_MACV_N12)
#define ENCI_MACV_N13 0x1b3d	/* register.h:8242 */
#define P_ENCI_MACV_N13 VCBUS_REG_ADDR(ENCI_MACV_N13)
#define ENCI_MACV_N14 0x1b3e	/* register.h:8243 */
#define P_ENCI_MACV_N14 VCBUS_REG_ADDR(ENCI_MACV_N14)
#define ENCI_MACV_N15 0x1b3f	/* register.h:8244 */
#define P_ENCI_MACV_N15 VCBUS_REG_ADDR(ENCI_MACV_N15)
#define ENCI_MACV_N16 0x1b40	/* register.h:8245 */
#define P_ENCI_MACV_N16 VCBUS_REG_ADDR(ENCI_MACV_N16)
#define ENCI_MACV_N17 0x1b41	/* register.h:8246 */
#define P_ENCI_MACV_N17 VCBUS_REG_ADDR(ENCI_MACV_N17)
#define ENCI_MACV_N18 0x1b42	/* register.h:8247 */
#define P_ENCI_MACV_N18 VCBUS_REG_ADDR(ENCI_MACV_N18)
#define ENCI_MACV_N19 0x1b43	/* register.h:8248 */
#define P_ENCI_MACV_N19 VCBUS_REG_ADDR(ENCI_MACV_N19)
#define ENCI_MACV_N20 0x1b44	/* register.h:8249 */
#define P_ENCI_MACV_N20 VCBUS_REG_ADDR(ENCI_MACV_N20)
#define ENCI_MACV_N21 0x1b45	/* register.h:8250 */
#define P_ENCI_MACV_N21 VCBUS_REG_ADDR(ENCI_MACV_N21)
#define ENCI_MACV_N22 0x1b46	/* register.h:8251 */
#define P_ENCI_MACV_N22 VCBUS_REG_ADDR(ENCI_MACV_N22)
#define ENCI_DBG_PX_RST 0x1b48	/* register.h:8253 */
#define P_ENCI_DBG_PX_RST VCBUS_REG_ADDR(ENCI_DBG_PX_RST)
#define ENCI_DBG_FLDLN_RST 0x1b49	/* register.h:8254 */
#define P_ENCI_DBG_FLDLN_RST VCBUS_REG_ADDR(ENCI_DBG_FLDLN_RST)
#define ENCI_DBG_PX_INT 0x1b4a	/* register.h:8255 */
#define P_ENCI_DBG_PX_INT VCBUS_REG_ADDR(ENCI_DBG_PX_INT)
#define ENCI_DBG_FLDLN_INT 0x1b4b	/* register.h:8256 */
#define P_ENCI_DBG_FLDLN_INT VCBUS_REG_ADDR(ENCI_DBG_FLDLN_INT)
#define ENCI_DBG_MAXPX 0x1b4c	/* register.h:8257 */
#define P_ENCI_DBG_MAXPX VCBUS_REG_ADDR(ENCI_DBG_MAXPX)
#define ENCI_DBG_MAXLN 0x1b4d	/* register.h:8258 */
#define P_ENCI_DBG_MAXLN VCBUS_REG_ADDR(ENCI_DBG_MAXLN)
#define ENCI_MACV_MAX_AMP 0x1b50	/* register.h:8259 */
#define P_ENCI_MACV_MAX_AMP VCBUS_REG_ADDR(ENCI_MACV_MAX_AMP)
#define ENCI_MACV_PULSE_LO 0x1b51	/* register.h:8260 */
#define P_ENCI_MACV_PULSE_LO VCBUS_REG_ADDR(ENCI_MACV_PULSE_LO)
#define ENCI_MACV_PULSE_HI 0x1b52	/* register.h:8261 */
#define P_ENCI_MACV_PULSE_HI VCBUS_REG_ADDR(ENCI_MACV_PULSE_HI)
#define ENCI_MACV_BKP_MAX 0x1b53	/* register.h:8262 */
#define P_ENCI_MACV_BKP_MAX VCBUS_REG_ADDR(ENCI_MACV_BKP_MAX)
#define ENCI_CFILT_CTRL 0x1b54	/* register.h:8263 */
#define P_ENCI_CFILT_CTRL VCBUS_REG_ADDR(ENCI_CFILT_CTRL)
#define ENCI_CFILT7 0x1b55	/* register.h:8264 */
#define P_ENCI_CFILT7 VCBUS_REG_ADDR(ENCI_CFILT7)
#define ENCI_YC_DELAY 0x1b56	/* register.h:8265 */
#define P_ENCI_YC_DELAY VCBUS_REG_ADDR(ENCI_YC_DELAY)
#define ENCI_VIDEO_EN 0x1b57	/* register.h:8266 */
#define P_ENCI_VIDEO_EN VCBUS_REG_ADDR(ENCI_VIDEO_EN)
#define VENC_VIDEO_PROG_MODE 0x1b68	/* /../ucode/register.h:8023 */
#define P_VENC_VIDEO_PROG_MODE		VCBUS_REG_ADDR(VENC_VIDEO_PROG_MODE)

#define ENCI_DVI_HSO_BEGIN 0x1c00	/* register.h:8280 */
#define P_ENCI_DVI_HSO_BEGIN VCBUS_REG_ADDR(ENCI_DVI_HSO_BEGIN)
#define ENCI_DVI_HSO_END 0x1c01	/* register.h:8281 */
#define P_ENCI_DVI_HSO_END VCBUS_REG_ADDR(ENCI_DVI_HSO_END)
#define ENCI_DVI_VSO_BLINE_EVN 0x1c02	/* register.h:8282 */
#define P_ENCI_DVI_VSO_BLINE_EVN VCBUS_REG_ADDR(ENCI_DVI_VSO_BLINE_EVN)
#define ENCI_DVI_VSO_BLINE_ODD 0x1c03	/* register.h:8283 */
#define P_ENCI_DVI_VSO_BLINE_ODD VCBUS_REG_ADDR(ENCI_DVI_VSO_BLINE_ODD)
#define ENCI_DVI_VSO_ELINE_EVN 0x1c04	/* register.h:8284 */
#define P_ENCI_DVI_VSO_ELINE_EVN VCBUS_REG_ADDR(ENCI_DVI_VSO_ELINE_EVN)
#define ENCI_DVI_VSO_ELINE_ODD 0x1c05	/* register.h:8285 */
#define P_ENCI_DVI_VSO_ELINE_ODD VCBUS_REG_ADDR(ENCI_DVI_VSO_ELINE_ODD)
#define ENCI_DVI_VSO_BEGIN_EVN 0x1c06	/* register.h:8286 */
#define P_ENCI_DVI_VSO_BEGIN_EVN VCBUS_REG_ADDR(ENCI_DVI_VSO_BEGIN_EVN)
#define ENCI_DVI_VSO_BEGIN_ODD 0x1c07	/* register.h:8287 */
#define P_ENCI_DVI_VSO_BEGIN_ODD VCBUS_REG_ADDR(ENCI_DVI_VSO_BEGIN_ODD)
#define ENCI_DVI_VSO_END_EVN 0x1c08	/* register.h:8288 */
#define P_ENCI_DVI_VSO_END_EVN VCBUS_REG_ADDR(ENCI_DVI_VSO_END_EVN)
#define ENCI_DVI_VSO_END_ODD 0x1c09	/* register.h:8289 */
#define P_ENCI_DVI_VSO_END_ODD VCBUS_REG_ADDR(ENCI_DVI_VSO_END_ODD)
#define ENCI_CFILT_CTRL2 0x1c0a	/* register.h:8295 */
#define P_ENCI_CFILT_CTRL2 VCBUS_REG_ADDR(ENCI_CFILT_CTRL2)
#define ENCI_DACSEL_0 0x1c0b	/* register.h:8296 */
#define P_ENCI_DACSEL_0 VCBUS_REG_ADDR(ENCI_DACSEL_0)
#define ENCI_DACSEL_1 0x1c0c	/* register.h:8297 */
#define P_ENCI_DACSEL_1 VCBUS_REG_ADDR(ENCI_DACSEL_1)
#define ENCP_DACSEL_0 0x1c0d	/* register.h:8298 */
#define P_ENCP_DACSEL_0 VCBUS_REG_ADDR(ENCP_DACSEL_0)
#define ENCP_DACSEL_1 0x1c0e	/* register.h:8299 */
#define P_ENCP_DACSEL_1 VCBUS_REG_ADDR(ENCP_DACSEL_1)
#define ENCP_MAX_LINE_SWITCH_POINT 0x1c0f	/* register.h:8300 */
#define P_ENCP_MAX_LINE_SWITCH_POINT VCBUS_REG_ADDR(ENCP_MAX_LINE_SWITCH_POINT)
#define ENCI_TST_EN 0x1c10	/* register.h:8301 */
#define P_ENCI_TST_EN VCBUS_REG_ADDR(ENCI_TST_EN)
#define ENCI_TST_MDSEL 0x1c11	/* register.h:8302 */
#define P_ENCI_TST_MDSEL VCBUS_REG_ADDR(ENCI_TST_MDSEL)
#define ENCI_TST_Y 0x1c12	/* register.h:8303 */
#define P_ENCI_TST_Y VCBUS_REG_ADDR(ENCI_TST_Y)
#define ENCI_TST_CB 0x1c13	/* register.h:8304 */
#define P_ENCI_TST_CB VCBUS_REG_ADDR(ENCI_TST_CB)
#define ENCI_TST_CR 0x1c14	/* register.h:8305 */
#define P_ENCI_TST_CR VCBUS_REG_ADDR(ENCI_TST_CR)
#define ENCI_TST_CLRBAR_STRT 0x1c15	/* register.h:8306 */
#define P_ENCI_TST_CLRBAR_STRT VCBUS_REG_ADDR(ENCI_TST_CLRBAR_STRT)
#define ENCI_TST_CLRBAR_WIDTH 0x1c16	/* register.h:8307 */
#define P_ENCI_TST_CLRBAR_WIDTH VCBUS_REG_ADDR(ENCI_TST_CLRBAR_WIDTH)
#define ENCI_TST_VDCNT_STSET 0x1c17	/* register.h:8308 */
#define P_ENCI_TST_VDCNT_STSET VCBUS_REG_ADDR(ENCI_TST_VDCNT_STSET)
#define ENCI_VFIFO2VD_CTL 0x1c18	/* register.h:8313 */
#define P_ENCI_VFIFO2VD_CTL VCBUS_REG_ADDR(ENCI_VFIFO2VD_CTL)
#define ENCI_VFIFO2VD_PIXEL_START 0x1c19	/* register.h:8315 */
#define P_ENCI_VFIFO2VD_PIXEL_START \
	VCBUS_REG_ADDR(ENCI_VFIFO2VD_PIXEL_START)
#define ENCI_VFIFO2VD_PIXEL_END 0x1c1a	/* register.h:8317 */
#define P_ENCI_VFIFO2VD_PIXEL_END VCBUS_REG_ADDR(ENCI_VFIFO2VD_PIXEL_END)
#define ENCI_VFIFO2VD_LINE_TOP_START 0x1c1b	/* register.h:8319 */
#define P_ENCI_VFIFO2VD_LINE_TOP_START \
	VCBUS_REG_ADDR(ENCI_VFIFO2VD_LINE_TOP_START)
#define ENCI_VFIFO2VD_LINE_TOP_END 0x1c1c	/* register.h:8321 */
#define P_ENCI_VFIFO2VD_LINE_TOP_END \
	VCBUS_REG_ADDR(ENCI_VFIFO2VD_LINE_TOP_END)
#define ENCI_VFIFO2VD_LINE_BOT_START 0x1c1d	/* register.h:8323 */
#define P_ENCI_VFIFO2VD_LINE_BOT_START \
	VCBUS_REG_ADDR(ENCI_VFIFO2VD_LINE_BOT_START)
#define ENCI_VFIFO2VD_LINE_BOT_END 0x1c1e	/* register.h:8325 */
#define P_ENCI_VFIFO2VD_LINE_BOT_END \
	VCBUS_REG_ADDR(ENCI_VFIFO2VD_LINE_BOT_END)
#define ENCI_VFIFO2VD_CTL2 0x1c1f	/* register.h:8326 */
#define P_ENCI_VFIFO2VD_CTL2 VCBUS_REG_ADDR(ENCI_VFIFO2VD_CTL2)

#define ENCP_DVI_HSO_BEGIN 0x1c30	/* register.h:8354 */
#define P_ENCP_DVI_HSO_BEGIN VCBUS_REG_ADDR(ENCP_DVI_HSO_BEGIN)
#define ENCP_DVI_HSO_END 0x1c31	/* register.h:8355 */
#define P_ENCP_DVI_HSO_END VCBUS_REG_ADDR(ENCP_DVI_HSO_END)
#define ENCP_DVI_VSO_BLINE_EVN 0x1c32	/* register.h:8356 */
#define P_ENCP_DVI_VSO_BLINE_EVN VCBUS_REG_ADDR(ENCP_DVI_VSO_BLINE_EVN)
#define ENCP_DVI_VSO_BLINE_ODD 0x1c33	/* register.h:8357 */
#define P_ENCP_DVI_VSO_BLINE_ODD VCBUS_REG_ADDR(ENCP_DVI_VSO_BLINE_ODD)
#define ENCP_DVI_VSO_ELINE_EVN 0x1c34	/* register.h:8358 */
#define P_ENCP_DVI_VSO_ELINE_EVN VCBUS_REG_ADDR(ENCP_DVI_VSO_ELINE_EVN)
#define ENCP_DVI_VSO_ELINE_ODD 0x1c35	/* register.h:8359 */
#define P_ENCP_DVI_VSO_ELINE_ODD VCBUS_REG_ADDR(ENCP_DVI_VSO_ELINE_ODD)
#define ENCP_DVI_VSO_BEGIN_EVN 0x1c36	/* register.h:8360 */
#define P_ENCP_DVI_VSO_BEGIN_EVN VCBUS_REG_ADDR(ENCP_DVI_VSO_BEGIN_EVN)
#define ENCP_DVI_VSO_BEGIN_ODD 0x1c37	/* register.h:8361 */
#define P_ENCP_DVI_VSO_BEGIN_ODD VCBUS_REG_ADDR(ENCP_DVI_VSO_BEGIN_ODD)
#define ENCP_DVI_VSO_END_EVN 0x1c38	/* register.h:8362 */
#define P_ENCP_DVI_VSO_END_EVN VCBUS_REG_ADDR(ENCP_DVI_VSO_END_EVN)
#define ENCP_DVI_VSO_END_ODD 0x1c39	/* register.h:8363 */
#define P_ENCP_DVI_VSO_END_ODD VCBUS_REG_ADDR(ENCP_DVI_VSO_END_ODD)
#define ENCP_DE_H_BEGIN 0x1c3a	/* register.h:8364 */
#define P_ENCP_DE_H_BEGIN VCBUS_REG_ADDR(ENCP_DE_H_BEGIN)
#define ENCP_DE_H_END 0x1c3b	/* register.h:8365 */
#define P_ENCP_DE_H_END VCBUS_REG_ADDR(ENCP_DE_H_END)
#define ENCP_DE_V_BEGIN_EVEN 0x1c3c	/* register.h:8366 */
#define P_ENCP_DE_V_BEGIN_EVEN VCBUS_REG_ADDR(ENCP_DE_V_BEGIN_EVEN)
#define ENCP_DE_V_END_EVEN 0x1c3d	/* register.h:8367 */
#define P_ENCP_DE_V_END_EVEN VCBUS_REG_ADDR(ENCP_DE_V_END_EVEN)
#define ENCP_DE_V_BEGIN_ODD 0x1c3e	/* register.h:8368 */
#define P_ENCP_DE_V_BEGIN_ODD VCBUS_REG_ADDR(ENCP_DE_V_BEGIN_ODD)
#define ENCP_DE_V_END_ODD 0x1c3f	/* register.h:8369 */
#define P_ENCP_DE_V_END_ODD VCBUS_REG_ADDR(ENCP_DE_V_END_ODD)
#define ENCI_SYNC_LINE_LENGTH 0x1c40	/* register.h:8372 */
#define P_ENCI_SYNC_LINE_LENGTH VCBUS_REG_ADDR(ENCI_SYNC_LINE_LENGTH)
#define ENCI_SYNC_PIXEL_EN 0x1c41	/* register.h:8375 */
#define P_ENCI_SYNC_PIXEL_EN VCBUS_REG_ADDR(ENCI_SYNC_PIXEL_EN)
#define ENCI_SYNC_TO_LINE_EN 0x1c42	/* register.h:8382 */
#define P_ENCI_SYNC_TO_LINE_EN VCBUS_REG_ADDR(ENCI_SYNC_TO_LINE_EN)
#define ENCI_SYNC_TO_PIXEL 0x1c43	/* register.h:8384 */
#define P_ENCI_SYNC_TO_PIXEL VCBUS_REG_ADDR(ENCI_SYNC_TO_PIXEL)
#define ENCP_SYNC_LINE_LENGTH 0x1c44	/* register.h:8387 */
#define P_ENCP_SYNC_LINE_LENGTH VCBUS_REG_ADDR(ENCP_SYNC_LINE_LENGTH)
#define ENCP_SYNC_PIXEL_EN 0x1c45	/* register.h:8390 */
#define P_ENCP_SYNC_PIXEL_EN VCBUS_REG_ADDR(ENCP_SYNC_PIXEL_EN)
#define ENCP_SYNC_TO_LINE_EN 0x1c46	/* register.h:8397 */
#define P_ENCP_SYNC_TO_LINE_EN VCBUS_REG_ADDR(ENCP_SYNC_TO_LINE_EN)
#define ENCP_SYNC_TO_PIXEL 0x1c47	/* register.h:8399 */
#define P_ENCP_SYNC_TO_PIXEL VCBUS_REG_ADDR(ENCP_SYNC_TO_PIXEL)

#define VPP_POSTBLEND_H_SIZE 0x1d21
#define P_VPP_POSTBLEND_H_SIZE VCBUS_REG_ADDR(VPP_POSTBLEND_H_SIZE)


#define VPU_VIU_VENC_MUX_CTRL 0x271a	/* register.h:9214 */
#define P_VPU_VIU_VENC_MUX_CTRL VCBUS_REG_ADDR(VPU_VIU_VENC_MUX_CTRL)
#define VPU_HDMI_SETTING 0x271b	/* register.h:9229 */
#define P_VPU_HDMI_SETTING VCBUS_REG_ADDR(VPU_HDMI_SETTING)

#define VPU_HDMI_DATA_OVR 0x2727	/* register.h:9270 */
#define P_VPU_HDMI_DATA_OVR VCBUS_REG_ADDR(VPU_HDMI_DATA_OVR)
#define VPU_HDMI_FMT_CTRL 0x2743
#define P_VPU_HDMI_FMT_CTRL VCBUS_REG_ADDR(VPU_HDMI_FMT_CTRL)
/* For GXM and later */
#define VPU_HDMI_DITH_CNTL 0x27fc
#define P_VPU_HDMI_DITH_CNTL VCBUS_REG_ADDR(VPU_HDMI_DITH_CNTL)

#endif
