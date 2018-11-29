/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2018 MediaTek Inc.
 */

#ifndef _DT_BINDINGS_CLK_MT2701_H
#define _DT_BINDINGS_CLK_MT2701_H

/* TOPCKGEN */
#define CLK_TOP_FCLKS_OFF			0

#define CLK_TOP_DPI				0
#define CLK_TOP_DMPLL				1
#define CLK_TOP_VENCPLL				2
#define CLK_TOP_HDMI_0_PIX340M			3
#define CLK_TOP_HDMI_0_DEEP340M			4
#define CLK_TOP_HDMI_0_PLL340M			5
#define CLK_TOP_HADDS2_FB			6
#define CLK_TOP_WBG_DIG_416M			7
#define CLK_TOP_DSI0_LNTC_DSI			8
#define CLK_TOP_HDMI_SCL_RX			9
#define CLK_TOP_32K_EXTERNAL			10
#define CLK_TOP_HDMITX_CLKDIG_CTS		11
#define CLK_TOP_AUD_EXT1			12
#define CLK_TOP_AUD_EXT2			13
#define CLK_TOP_NFI1X_PAD			14

#define CLK_TOP_SYSPLL				15
#define CLK_TOP_SYSPLL_D2			16
#define CLK_TOP_SYSPLL_D3			17
#define CLK_TOP_SYSPLL_D5			18
#define CLK_TOP_SYSPLL_D7			19
#define CLK_TOP_SYSPLL1_D2			20
#define CLK_TOP_SYSPLL1_D4			21
#define CLK_TOP_SYSPLL1_D8			22
#define CLK_TOP_SYSPLL1_D16			23
#define CLK_TOP_SYSPLL2_D2			24
#define CLK_TOP_SYSPLL2_D4			25
#define CLK_TOP_SYSPLL2_D8			26
#define CLK_TOP_SYSPLL3_D2			27
#define CLK_TOP_SYSPLL3_D4			28
#define CLK_TOP_SYSPLL4_D2			29
#define CLK_TOP_SYSPLL4_D4			30
#define CLK_TOP_UNIVPLL				31
#define CLK_TOP_UNIVPLL_D2			32
#define CLK_TOP_UNIVPLL_D3			33
#define CLK_TOP_UNIVPLL_D5			34
#define CLK_TOP_UNIVPLL_D7			35
#define CLK_TOP_UNIVPLL_D26			36
#define CLK_TOP_UNIVPLL_D52			37
#define CLK_TOP_UNIVPLL_D108			38
#define CLK_TOP_USB_PHY48M			39
#define CLK_TOP_UNIVPLL1_D2			40
#define CLK_TOP_UNIVPLL1_D4			41
#define CLK_TOP_UNIVPLL1_D8			42
#define CLK_TOP_UNIVPLL2_D2			43
#define CLK_TOP_UNIVPLL2_D4			44
#define CLK_TOP_UNIVPLL2_D8			45
#define CLK_TOP_UNIVPLL2_D16			46
#define CLK_TOP_UNIVPLL2_D32			47
#define CLK_TOP_UNIVPLL3_D2			48
#define CLK_TOP_UNIVPLL3_D4			49
#define CLK_TOP_UNIVPLL3_D8			50
#define CLK_TOP_MSDCPLL				51
#define CLK_TOP_MSDCPLL_D2			52
#define CLK_TOP_MSDCPLL_D4			53
#define CLK_TOP_MSDCPLL_D8			54
#define CLK_TOP_MMPLL				55
#define CLK_TOP_MMPLL_D2			56
#define CLK_TOP_DMPLL_D2			57
#define CLK_TOP_DMPLL_D4			58
#define CLK_TOP_DMPLL_X2			59
#define CLK_TOP_TVDPLL				60
#define CLK_TOP_TVDPLL_D2			61
#define CLK_TOP_TVDPLL_D4			62
#define CLK_TOP_VDECPLL				63
#define CLK_TOP_TVD2PLL				64
#define CLK_TOP_TVD2PLL_D2			65
#define CLK_TOP_MIPIPLL				66
#define CLK_TOP_MIPIPLL_D2			67
#define CLK_TOP_MIPIPLL_D4			68
#define CLK_TOP_HDMIPLL				69
#define CLK_TOP_HDMIPLL_D2			70
#define CLK_TOP_HDMIPLL_D3			71
#define CLK_TOP_ARMPLL_1P3G			72
#define CLK_TOP_AUDPLL				73
#define CLK_TOP_AUDPLL_D4			74
#define CLK_TOP_AUDPLL_D8			75
#define CLK_TOP_AUDPLL_D16			76
#define CLK_TOP_AUDPLL_D24			77
#define CLK_TOP_AUD1PLL_98M			78
#define CLK_TOP_AUD2PLL_90M			79
#define CLK_TOP_HADDS2PLL_98M			80
#define CLK_TOP_HADDS2PLL_294M			81
#define CLK_TOP_ETHPLL_500M			82
#define CLK_TOP_CLK26M_D8			83
#define CLK_TOP_32K_INTERNAL			84
#define CLK_TOP_AXISEL_D4			85
#define CLK_TOP_8BDAC				86

#define CLK_TOP_AXI_SEL				87
#define CLK_TOP_MEM_SEL				88
#define CLK_TOP_DDRPHYCFG_SEL			89
#define CLK_TOP_MM_SEL				90
#define CLK_TOP_PWM_SEL				91
#define CLK_TOP_VDEC_SEL			92
#define CLK_TOP_MFG_SEL				93
#define CLK_TOP_CAMTG_SEL			94
#define CLK_TOP_UART_SEL			95
#define CLK_TOP_SPI0_SEL			96
#define CLK_TOP_USB20_SEL			97
#define CLK_TOP_MSDC30_0_SEL			98
#define CLK_TOP_MSDC30_1_SEL			99
#define CLK_TOP_MSDC30_2_SEL			100
#define CLK_TOP_AUDIO_SEL			101
#define CLK_TOP_AUDINTBUS_SEL			102
#define CLK_TOP_PMICSPI_SEL			103
#define CLK_TOP_SCP_SEL				104
#define CLK_TOP_DPI0_SEL			105
#define CLK_TOP_DPI1_SEL			106
#define CLK_TOP_TVE_SEL				107
#define CLK_TOP_HDMI_SEL			108
#define CLK_TOP_APLL_SEL			109
#define CLK_TOP_RTC_SEL				110
#define CLK_TOP_NFI2X_SEL			111
#define CLK_TOP_EMMC_HCLK_SEL			112
#define CLK_TOP_FLASH_SEL			113
#define CLK_TOP_DI_SEL				114
#define CLK_TOP_NR_SEL				115
#define CLK_TOP_OSD_SEL				116
#define CLK_TOP_HDMIRX_BIST_SEL			117
#define CLK_TOP_INTDIR_SEL			118
#define CLK_TOP_ASM_I_SEL			119
#define CLK_TOP_ASM_M_SEL			120
#define CLK_TOP_ASM_H_SEL			121
#define CLK_TOP_MS_CARD_SEL			122
#define CLK_TOP_ETHIF_SEL			123
#define CLK_TOP_HDMIRX26_24_SEL			124
#define CLK_TOP_MSDC30_3_SEL			125
#define CLK_TOP_CMSYS_SEL			126
#define CLK_TOP_SPI1_SEL			127
#define CLK_TOP_SPI2_SEL			128
#define CLK_TOP_8BDAC_SEL			129
#define CLK_TOP_AUD2DVD_SEL			130
#define CLK_TOP_PADMCLK_SEL			131
#define CLK_TOP_AUD_MUX1_SEL			132
#define CLK_TOP_AUD_MUX2_SEL			133
#define CLK_TOP_AUDPLL_MUX_SEL			134
#define CLK_TOP_AUD_K1_SRC_SEL			135
#define CLK_TOP_AUD_K2_SRC_SEL			136
#define CLK_TOP_AUD_K3_SRC_SEL			137
#define CLK_TOP_AUD_K4_SRC_SEL			138
#define CLK_TOP_AUD_K5_SRC_SEL			139
#define CLK_TOP_AUD_K6_SRC_SEL			140

#define CLK_TOP_AUD_EXTCK1_DIV			141
#define CLK_TOP_AUD_EXTCK2_DIV			142
#define CLK_TOP_AUD_MUX1_DIV			143
#define CLK_TOP_AUD_MUX2_DIV			144
#define CLK_TOP_AUD_K1_SRC_DIV			145
#define CLK_TOP_AUD_K2_SRC_DIV			146
#define CLK_TOP_AUD_K3_SRC_DIV			147
#define CLK_TOP_AUD_K4_SRC_DIV			148
#define CLK_TOP_AUD_K5_SRC_DIV			149
#define CLK_TOP_AUD_K6_SRC_DIV			150
#define CLK_TOP_AUD_48K_TIMING			151
#define CLK_TOP_AUD_44K_TIMING			152
#define CLK_TOP_AUD_I2S1_MCLK			153
#define CLK_TOP_AUD_I2S2_MCLK			154
#define CLK_TOP_AUD_I2S3_MCLK			155
#define CLK_TOP_AUD_I2S4_MCLK			156
#define CLK_TOP_AUD_I2S5_MCLK			157
#define CLK_TOP_AUD_I2S6_MCLK			158
#define CLK_TOP_NR				159

/* APMIXEDSYS */
#define CLK_APMIXED_ARMPLL			0
#define CLK_APMIXED_MAINPLL			1
#define CLK_APMIXED_UNIVPLL			2
#define CLK_APMIXED_MMPLL			3
#define CLK_APMIXED_MSDCPLL			4
#define CLK_APMIXED_TVDPLL			5
#define CLK_APMIXED_AUD1PLL			6
#define CLK_APMIXED_TRGPLL			7
#define CLK_APMIXED_ETHPLL			8
#define CLK_APMIXED_VDECPLL			9
#define CLK_APMIXED_HADDS2PLL			10
#define CLK_APMIXED_AUD2PLL			11
#define CLK_APMIXED_TVD2PLL			12
#define CLK_APMIXED_NR				13

/* INFRACFG */
#define CLK_INFRA_DBG				0
#define CLK_INFRA_SMI				1
#define CLK_INFRA_QAXI_CM4			2
#define CLK_INFRA_AUD_SPLIN_B			3
#define CLK_INFRA_AUDIO				4
#define CLK_INFRA_EFUSE				5
#define CLK_INFRA_L2C_SRAM			6
#define CLK_INFRA_M4U				7
#define CLK_INFRA_CONNMCU			8
#define CLK_INFRA_TRNG				9
#define CLK_INFRA_RAMBUFIF			10
#define CLK_INFRA_CPUM				11
#define CLK_INFRA_KP				12
#define CLK_INFRA_CEC				13
#define CLK_INFRA_IRRX				14
#define CLK_INFRA_PMICSPI			15
#define CLK_INFRA_PMICWRAP			16
#define CLK_INFRA_DDCCI				17
#define CLK_INFRA_CPUSEL			18
#define CLK_INFRA_NR				19

/* PERICFG */
#define CLK_PERI_NFI				0
#define CLK_PERI_THERM				1
#define CLK_PERI_PWM1				2
#define CLK_PERI_PWM2				3
#define CLK_PERI_PWM3				4
#define CLK_PERI_PWM4				5
#define CLK_PERI_PWM5				6
#define CLK_PERI_PWM6				7
#define CLK_PERI_PWM7				8
#define CLK_PERI_PWM				9
#define CLK_PERI_USB0				10
#define CLK_PERI_USB1				11
#define CLK_PERI_AP_DMA				12
#define CLK_PERI_MSDC30_0			13
#define CLK_PERI_MSDC30_1			14
#define CLK_PERI_MSDC30_2			15
#define CLK_PERI_MSDC30_3			16
#define CLK_PERI_MSDC50_3			17
#define CLK_PERI_NLI				18
#define CLK_PERI_UART0				19
#define CLK_PERI_UART1				20
#define CLK_PERI_UART2				21
#define CLK_PERI_UART3				22
#define CLK_PERI_BTIF				23
#define CLK_PERI_I2C0				24
#define CLK_PERI_I2C1				25
#define CLK_PERI_I2C2				26
#define CLK_PERI_I2C3				27
#define CLK_PERI_AUXADC				28
#define CLK_PERI_SPI0				39
#define CLK_PERI_ETH				30
#define CLK_PERI_USB0_MCU			31

#define CLK_PERI_USB1_MCU			32
#define CLK_PERI_USB_SLV			33
#define CLK_PERI_GCPU				34
#define CLK_PERI_NFI_ECC			35
#define CLK_PERI_NFI_PAD			36
#define CLK_PERI_FLASH				37
#define CLK_PERI_HOST89_INT			38
#define CLK_PERI_HOST89_SPI			39
#define CLK_PERI_HOST89_DVD			40
#define CLK_PERI_SPI1				41
#define CLK_PERI_SPI2				42
#define CLK_PERI_FCI				43
#define CLK_PERI_NR				44

/* AUDIO */
#define CLK_AUD_AFE				0
#define CLK_AUD_LRCK_DETECT			1
#define CLK_AUD_I2S				2
#define CLK_AUD_APLL_TUNER			3
#define CLK_AUD_HDMI				4
#define CLK_AUD_SPDF				5
#define CLK_AUD_SPDF2				6
#define CLK_AUD_APLL				7
#define CLK_AUD_TML				8
#define CLK_AUD_AHB_IDLE_EXT			9
#define CLK_AUD_AHB_IDLE_INT			10

#define CLK_AUD_I2SIN1				11
#define CLK_AUD_I2SIN2				12
#define CLK_AUD_I2SIN3				13
#define CLK_AUD_I2SIN4				14
#define CLK_AUD_I2SIN5				15
#define CLK_AUD_I2SIN6				16
#define CLK_AUD_I2SO1				17
#define CLK_AUD_I2SO2				18
#define CLK_AUD_I2SO3				19
#define CLK_AUD_I2SO4				20
#define CLK_AUD_I2SO5				21
#define CLK_AUD_I2SO6				22
#define CLK_AUD_ASRCI1				23
#define CLK_AUD_ASRCI2				24
#define CLK_AUD_ASRCO1				25
#define CLK_AUD_ASRCO2				26
#define CLK_AUD_ASRC11				27
#define CLK_AUD_ASRC12				28
#define CLK_AUD_HDMIRX				29
#define CLK_AUD_INTDIR				30
#define CLK_AUD_A1SYS				31
#define CLK_AUD_A2SYS				32
#define CLK_AUD_AFE_CONN			33
#define CLK_AUD_AFE_PCMIF			34
#define CLK_AUD_AFE_MRGIF			35

#define CLK_AUD_MMIF_UL1			36
#define CLK_AUD_MMIF_UL2			37
#define CLK_AUD_MMIF_UL3			38
#define CLK_AUD_MMIF_UL4			39
#define CLK_AUD_MMIF_UL5			40
#define CLK_AUD_MMIF_UL6			41
#define CLK_AUD_MMIF_DL1			42
#define CLK_AUD_MMIF_DL2			43
#define CLK_AUD_MMIF_DL3			44
#define CLK_AUD_MMIF_DL4			45
#define CLK_AUD_MMIF_DL5			46
#define CLK_AUD_MMIF_DL6			47
#define CLK_AUD_MMIF_DLMCH			48
#define CLK_AUD_MMIF_ARB1			49
#define CLK_AUD_MMIF_AWB1			50
#define CLK_AUD_MMIF_AWB2			51
#define CLK_AUD_MMIF_DAI			52

#define CLK_AUD_DMIC1				53
#define CLK_AUD_DMIC2				54
#define CLK_AUD_ASRCI3				55
#define CLK_AUD_ASRCI4				56
#define CLK_AUD_ASRCI5				57
#define CLK_AUD_ASRCI6				58
#define CLK_AUD_ASRCO3				59
#define CLK_AUD_ASRCO4				60
#define CLK_AUD_ASRCO5				61
#define CLK_AUD_ASRCO6				62
#define CLK_AUD_MEM_ASRC1			63
#define CLK_AUD_MEM_ASRC2			64
#define CLK_AUD_MEM_ASRC3			65
#define CLK_AUD_MEM_ASRC4			66
#define CLK_AUD_MEM_ASRC5			67
#define CLK_AUD_DSD_ENC				68
#define CLK_AUD_ASRC_BRG			60
#define CLK_AUD_NR				70

/* MMSYS */
#define CLK_MM_SMI_COMMON			0
#define CLK_MM_SMI_LARB0			1
#define CLK_MM_CMDQ				2
#define CLK_MM_MUTEX				3
#define CLK_MM_DISP_COLOR			4
#define CLK_MM_DISP_BLS				5
#define CLK_MM_DISP_WDMA			6
#define CLK_MM_DISP_RDMA			7
#define CLK_MM_DISP_OVL				8
#define CLK_MM_MDP_TDSHP			9
#define CLK_MM_MDP_WROT				10
#define CLK_MM_MDP_WDMA				11
#define CLK_MM_MDP_RSZ1				12
#define CLK_MM_MDP_RSZ0				13
#define CLK_MM_MDP_RDMA				14
#define CLK_MM_MDP_BLS_26M			15
#define CLK_MM_CAM_MDP				16
#define CLK_MM_FAKE_ENG				17
#define CLK_MM_MUTEX_32K			18
#define CLK_MM_DISP_RDMA1			19
#define CLK_MM_DISP_UFOE			20

#define CLK_MM_DSI_ENGINE			21
#define CLK_MM_DSI_DIG				22
#define CLK_MM_DPI_DIGL				23
#define CLK_MM_DPI_ENGINE			24
#define CLK_MM_DPI1_DIGL			25
#define CLK_MM_DPI1_ENGINE			26
#define CLK_MM_TVE_OUTPUT			27
#define CLK_MM_TVE_INPUT			28
#define CLK_MM_HDMI_PIXEL			29
#define CLK_MM_HDMI_PLL				30
#define CLK_MM_HDMI_AUDIO			31
#define CLK_MM_HDMI_SPDIF			32
#define CLK_MM_TVE_FMM				33
#define CLK_MM_NR				34

/* IMGSYS */
#define CLK_IMG_SMI_COMM			0
#define CLK_IMG_RESZ				1
#define CLK_IMG_JPGDEC_SMI			2
#define CLK_IMG_JPGDEC				3
#define CLK_IMG_VENC_LT				4
#define CLK_IMG_VENC				5
#define CLK_IMG_NR				6

/* VDEC */
#define CLK_VDEC_CKGEN				0
#define CLK_VDEC_LARB				1
#define CLK_VDEC_NR				2

/* HIFSYS */
#define CLK_HIFSYS_USB0PHY			0
#define CLK_HIFSYS_USB1PHY			1
#define CLK_HIFSYS_PCIE0			2
#define CLK_HIFSYS_PCIE1			3
#define CLK_HIFSYS_PCIE2			4
#define CLK_HIFSYS_NR				5

/* ETHSYS */
#define CLK_ETHSYS_HSDMA			0
#define CLK_ETHSYS_ESW				1
#define CLK_ETHSYS_GP2				2
#define CLK_ETHSYS_GP1				3
#define CLK_ETHSYS_PCM				4
#define CLK_ETHSYS_GDMA				5
#define CLK_ETHSYS_I2S				6
#define CLK_ETHSYS_CRYPTO			7
#define CLK_ETHSYS_NR				8

/* G3DSYS */
#define CLK_G3DSYS_CORE				0
#define CLK_G3DSYS_NR				1

#endif /* _DT_BINDINGS_CLK_MT2701_H */
