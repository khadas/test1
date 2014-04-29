/*
 * Copyright (c) 2010-2014, NVIDIA CORPORATION. All rights reserved.
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/pinmux.h>

#define PIN(pin, f0, f1, f2, f3)	\
	{				\
		.funcs = {		\
			PMUX_FUNC_##f0,	\
			PMUX_FUNC_##f1,	\
			PMUX_FUNC_##f2,	\
			PMUX_FUNC_##f3,	\
		},			\
	}

#define PIN_RESERVED {}

static const struct pmux_pingrp_desc tegra30_pingroups[] = {
	/*  pin,                  f0,           f1,       f2,       f3 */
	/* Offset 0x3000 */
	PIN(ULPI_DATA0_PO1,       SPI3,         HSI,      UARTA,    ULPI),
	PIN(ULPI_DATA1_PO2,       SPI3,         HSI,      UARTA,    ULPI),
	PIN(ULPI_DATA2_PO3,       SPI3,         HSI,      UARTA,    ULPI),
	PIN(ULPI_DATA3_PO4,       SPI3,         HSI,      UARTA,    ULPI),
	PIN(ULPI_DATA4_PO5,       SPI2,         HSI,      UARTA,    ULPI),
	PIN(ULPI_DATA5_PO6,       SPI2,         HSI,      UARTA,    ULPI),
	PIN(ULPI_DATA6_PO7,       SPI2,         HSI,      UARTA,    ULPI),
	PIN(ULPI_DATA7_PO0,       SPI2,         HSI,      UARTA,    ULPI),
	PIN(ULPI_CLK_PY0,         SPI1,         RSVD2,    UARTD,    ULPI),
	PIN(ULPI_DIR_PY1,         SPI1,         RSVD2,    UARTD,    ULPI),
	PIN(ULPI_NXT_PY2,         SPI1,         RSVD2,    UARTD,    ULPI),
	PIN(ULPI_STP_PY3,         SPI1,         RSVD2,    UARTD,    ULPI),
	PIN(DAP3_FS_PP0,          I2S2,         RSVD2,    DISPLAYA, DISPLAYB),
	PIN(DAP3_DIN_PP1,         I2S2,         RSVD2,    DISPLAYA, DISPLAYB),
	PIN(DAP3_DOUT_PP2,        I2S2,         RSVD2,    DISPLAYA, DISPLAYB),
	PIN(DAP3_SCLK_PP3,        I2S2,         RSVD2,    DISPLAYA, DISPLAYB),
	PIN(PV0,                  RSVD1,        RSVD2,    RSVD3,    RSVD4),
	PIN(PV1,                  RSVD1,        RSVD2,    RSVD3,    RSVD4),
	PIN(SDMMC1_CLK_PZ0,       SDMMC1,       RSVD2,    RSVD3,    UARTA),
	PIN(SDMMC1_CMD_PZ1,       SDMMC1,       RSVD2,    RSVD3,    UARTA),
	PIN(SDMMC1_DAT3_PY4,      SDMMC1,       RSVD2,    UARTE,    UARTA),
	PIN(SDMMC1_DAT2_PY5,      SDMMC1,       RSVD2,    UARTE,    UARTA),
	PIN(SDMMC1_DAT1_PY6,      SDMMC1,       RSVD2,    UARTE,    UARTA),
	PIN(SDMMC1_DAT0_PY7,      SDMMC1,       RSVD2,    UARTE,    UARTA),
	PIN(PV2,                  OWR,          RSVD2,    RSVD3,    RSVD4),
	PIN(PV3,                  CLK_12M_OUT,  RSVD2,    RSVD3,    RSVD4),
	PIN(CLK2_OUT_PW5,         EXTPERIPH2,   RSVD2,    RSVD3,    RSVD4),
	PIN(CLK2_REQ_PCC5,        DAP,          RSVD2,    RSVD3,    RSVD4),
	PIN(LCD_PWR1_PC1,         DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_PWR2_PC6,         DISPLAYA,     DISPLAYB, SPI5,     HDCP),
	PIN(LCD_SDIN_PZ2,         DISPLAYA,     DISPLAYB, SPI5,     RSVD4),
	PIN(LCD_SDOUT_PN5,        DISPLAYA,     DISPLAYB, SPI5,     HDCP),
	PIN(LCD_WR_N_PZ3,         DISPLAYA,     DISPLAYB, SPI5,     HDCP),
	PIN(LCD_CS0_N_PN4,        DISPLAYA,     DISPLAYB, SPI5,     RSVD4),
	PIN(LCD_DC0_PN6,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_SCK_PZ4,          DISPLAYA,     DISPLAYB, SPI5,     HDCP),
	PIN(LCD_PWR0_PB2,         DISPLAYA,     DISPLAYB, SPI5,     HDCP),
	PIN(LCD_PCLK_PB3,         DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_DE_PJ1,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_HSYNC_PJ3,        DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_VSYNC_PJ4,        DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D0_PE0,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D1_PE1,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D2_PE2,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D3_PE3,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D4_PE4,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D5_PE5,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D6_PE6,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D7_PE7,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D8_PF0,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D9_PF1,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D10_PF2,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D11_PF3,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D12_PF4,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D13_PF5,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D14_PF6,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D15_PF7,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D16_PM0,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D17_PM1,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D18_PM2,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D19_PM3,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D20_PM4,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D21_PM5,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D22_PM6,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_D23_PM7,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_CS1_N_PW0,        DISPLAYA,     DISPLAYB, SPI5,     RSVD4),
	PIN(LCD_M1_PW1,           DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(LCD_DC1_PD2,          DISPLAYA,     DISPLAYB, RSVD3,    RSVD4),
	PIN(HDMI_INT_PN7,         HDMI,         RSVD2,    RSVD3,    RSVD4),
	PIN(DDC_SCL_PV4,          I2C4,         RSVD2,    RSVD3,    RSVD4),
	PIN(DDC_SDA_PV5,          I2C4,         RSVD2,    RSVD3,    RSVD4),
	PIN(CRT_HSYNC_PV6,        CRT,          RSVD2,    RSVD3,    RSVD4),
	PIN(CRT_VSYNC_PV7,        CRT,          RSVD2,    RSVD3,    RSVD4),
	PIN(VI_D0_PT4,            DDR,          RSVD2,    VI,       RSVD4),
	PIN(VI_D1_PD5,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D2_PL0,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D3_PL1,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D4_PL2,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D5_PL3,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D6_PL4,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D7_PL5,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D8_PL6,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D9_PL7,            DDR,          SDMMC2,   VI,       RSVD4),
	PIN(VI_D10_PT2,           DDR,          RSVD2,    VI,       RSVD4),
	PIN(VI_D11_PT3,           DDR,          RSVD2,    VI,       RSVD4),
	PIN(VI_PCLK_PT0,          RSVD1,        SDMMC2,   VI,       RSVD4),
	PIN(VI_MCLK_PT1,          VI,           VI_ALT1,  VI_ALT2,  VI_ALT3),
	PIN(VI_VSYNC_PD6,         DDR,          RSVD2,    VI,       RSVD4),
	PIN(VI_HSYNC_PD7,         DDR,          RSVD2,    VI,       RSVD4),
	PIN(UART2_RXD_PC3,        UARTB,        SPDIF,    UARTA,    SPI4),
	PIN(UART2_TXD_PC2,        UARTB,        SPDIF,    UARTA,    SPI4),
	PIN(UART2_RTS_N_PJ6,      UARTA,        UARTB,    GMI,      SPI4),
	PIN(UART2_CTS_N_PJ5,      UARTA,        UARTB,    GMI,      SPI4),
	PIN(UART3_TXD_PW6,        UARTC,        RSVD2,    GMI,      RSVD4),
	PIN(UART3_RXD_PW7,        UARTC,        RSVD2,    GMI,      RSVD4),
	PIN(UART3_CTS_N_PA1,      UARTC,        RSVD2,    GMI,      RSVD4),
	PIN(UART3_RTS_N_PC0,      UARTC,        PWM0,     GMI,      RSVD4),
	PIN(PU0,                  OWR,          UARTA,    GMI,      RSVD4),
	PIN(PU1,                  RSVD1,        UARTA,    GMI,      RSVD4),
	PIN(PU2,                  RSVD1,        UARTA,    GMI,      RSVD4),
	PIN(PU3,                  PWM0,         UARTA,    GMI,      RSVD4),
	PIN(PU4,                  PWM1,         UARTA,    GMI,      RSVD4),
	PIN(PU5,                  PWM2,         UARTA,    GMI,      RSVD4),
	PIN(PU6,                  PWM3,         UARTA,    GMI,      RSVD4),
	PIN(GEN1_I2C_SDA_PC5,     I2C1,         RSVD2,    RSVD3,    RSVD4),
	PIN(GEN1_I2C_SCL_PC4,     I2C1,         RSVD2,    RSVD3,    RSVD4),
	PIN(DAP4_FS_PP4,          I2S3,         RSVD2,    GMI,      RSVD4),
	PIN(DAP4_DIN_PP5,         I2S3,         RSVD2,    GMI,      RSVD4),
	PIN(DAP4_DOUT_PP6,        I2S3,         RSVD2,    GMI,      RSVD4),
	PIN(DAP4_SCLK_PP7,        I2S3,         RSVD2,    GMI,      RSVD4),
	PIN(CLK3_OUT_PEE0,        EXTPERIPH3,   RSVD2,    RSVD3,    RSVD4),
	PIN(CLK3_REQ_PEE1,        DEV3,         RSVD2,    RSVD3,    RSVD4),
	PIN(GMI_WP_N_PC7,         RSVD1,        NAND,     GMI,      GMI_ALT),
	PIN(GMI_IORDY_PI5,        RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_WAIT_PI7,         RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_ADV_N_PK0,        RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_CLK_PK1,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_CS0_N_PJ0,        RSVD1,        NAND,     GMI,      DTV),
	PIN(GMI_CS1_N_PJ2,        RSVD1,        NAND,     GMI,      DTV),
	PIN(GMI_CS2_N_PK3,        RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_CS3_N_PK4,        RSVD1,        NAND,     GMI,      GMI_ALT),
	PIN(GMI_CS4_N_PK2,        RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_CS6_N_PI3,        NAND,         NAND_ALT, GMI,      SATA),
	PIN(GMI_CS7_N_PI6,        NAND,         NAND_ALT, GMI,      GMI_ALT),
	PIN(GMI_AD0_PG0,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD1_PG1,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD2_PG2,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD3_PG3,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD4_PG4,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD5_PG5,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD6_PG6,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD7_PG7,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD8_PH0,          PWM0,         NAND,     GMI,      RSVD4),
	PIN(GMI_AD9_PH1,          PWM1,         NAND,     GMI,      RSVD4),
	PIN(GMI_AD10_PH2,         PWM2,         NAND,     GMI,      RSVD4),
	PIN(GMI_AD11_PH3,         PWM3,         NAND,     GMI,      RSVD4),
	PIN(GMI_AD12_PH4,         RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD13_PH5,         RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD14_PH6,         RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_AD15_PH7,         RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_A16_PJ7,          UARTD,        SPI4,     GMI,      GMI_ALT),
	PIN(GMI_A17_PB0,          UARTD,        SPI4,     GMI,      DTV),
	PIN(GMI_A18_PB1,          UARTD,        SPI4,     GMI,      DTV),
	PIN(GMI_A19_PK7,          UARTD,        SPI4,     GMI,      RSVD4),
	PIN(GMI_WR_N_PI0,         RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_OE_N_PI1,         RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_DQS_PI2,          RSVD1,        NAND,     GMI,      RSVD4),
	PIN(GMI_RST_N_PI4,        NAND,         NAND_ALT, GMI,      RSVD4),
	PIN(GEN2_I2C_SCL_PT5,     I2C2,         HDCP,     GMI,      RSVD4),
	PIN(GEN2_I2C_SDA_PT6,     I2C2,         HDCP,     GMI,      RSVD4),
	PIN(SDMMC4_CLK_PCC4,      INVALID,      NAND,     GMI,      SDMMC4),
	PIN(SDMMC4_CMD_PT7,       I2C3,         NAND,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT0_PAA0,     UARTE,        SPI3,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT1_PAA1,     UARTE,        SPI3,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT2_PAA2,     UARTE,        SPI3,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT3_PAA3,     UARTE,        SPI3,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT4_PAA4,     I2C3,         I2S4,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT5_PAA5,     VGP3,         I2S4,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT6_PAA6,     VGP4,         I2S4,     GMI,      SDMMC4),
	PIN(SDMMC4_DAT7_PAA7,     VGP5,         I2S4,     GMI,      SDMMC4),
	PIN(SDMMC4_RST_N_PCC3,    VGP6,         RSVD2,    RSVD3,    SDMMC4),
	PIN(CAM_MCLK_PCC0,        VI,           VI_ALT1,  VI_ALT3,  SDMMC4),
	PIN(PCC1,                 I2S4,         RSVD2,    RSVD3,    SDMMC4),
	PIN(PBB0,                 I2S4,         RSVD2,    RSVD3,    SDMMC4),
	PIN(CAM_I2C_SCL_PBB1,     VGP1,         I2C3,     RSVD3,    SDMMC4),
	PIN(CAM_I2C_SDA_PBB2,     VGP2,         I2C3,     RSVD3,    SDMMC4),
	PIN(PBB3,                 VGP3,         DISPLAYA, DISPLAYB, SDMMC4),
	PIN(PBB4,                 VGP4,         DISPLAYA, DISPLAYB, SDMMC4),
	PIN(PBB5,                 VGP5,         DISPLAYA, DISPLAYB, SDMMC4),
	PIN(PBB6,                 VGP6,         DISPLAYA, DISPLAYB, SDMMC4),
	PIN(PBB7,                 I2S4,         RSVD2,    RSVD3,    SDMMC4),
	PIN(PCC2,                 I2S4,         RSVD2,    RSVD3,    RSVD4),
	PIN(JTAG_RTCK_PU7,        RTCK,         RSVD2,    RSVD3,    RSVD4),
	PIN(PWR_I2C_SCL_PZ6,      I2CPWR,       RSVD2,    RSVD3,    RSVD4),
	PIN(PWR_I2C_SDA_PZ7,      I2CPWR,       RSVD2,    RSVD3,    RSVD4),
	PIN(KB_ROW0_PR0,          KBC,          NAND,     RSVD3,    RSVD4),
	PIN(KB_ROW1_PR1,          KBC,          NAND,     RSVD3,    RSVD4),
	PIN(KB_ROW2_PR2,          KBC,          NAND,     RSVD3,    RSVD4),
	PIN(KB_ROW3_PR3,          KBC,          NAND,     RSVD3,    INVALID),
	PIN(KB_ROW4_PR4,          KBC,          NAND,     TRACE,    RSVD4),
	PIN(KB_ROW5_PR5,          KBC,          NAND,     TRACE,    OWR),
	PIN(KB_ROW6_PR6,          KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW7_PR7,          KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW8_PS0,          KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW9_PS1,          KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW10_PS2,         KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW11_PS3,         KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW12_PS4,         KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW13_PS5,         KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW14_PS6,         KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_ROW15_PS7,         KBC,          NAND,     SDMMC2,   MIO),
	PIN(KB_COL0_PQ0,          KBC,          NAND,     TRACE,    TEST),
	PIN(KB_COL1_PQ1,          KBC,          NAND,     TRACE,    TEST),
	PIN(KB_COL2_PQ2,          KBC,          NAND,     TRACE,    RSVD4),
	PIN(KB_COL3_PQ3,          KBC,          NAND,     TRACE,    RSVD4),
	PIN(KB_COL4_PQ4,          KBC,          NAND,     TRACE,    RSVD4),
	PIN(KB_COL5_PQ5,          KBC,          NAND,     TRACE,    RSVD4),
	PIN(KB_COL6_PQ6,          KBC,          NAND,     TRACE,    MIO),
	PIN(KB_COL7_PQ7,          KBC,          NAND,     TRACE,    MIO),
	PIN(CLK_32K_OUT_PA0,      BLINK,        RSVD2,    RSVD3,    RSVD4),
	PIN(SYS_CLK_REQ_PZ5,      SYSCLK,       RSVD2,    RSVD3,    RSVD4),
	PIN(CORE_PWR_REQ,         CORE_PWR_REQ, RSVD2,    RSVD3,    RSVD4),
	PIN(CPU_PWR_REQ,          CPU_PWR_REQ,  RSVD2,    RSVD3,    RSVD4),
	PIN(PWR_INT_N,            PWR_INT_N,    RSVD2,    RSVD3,    RSVD4),
	PIN(CLK_32K_IN,           CLK_32K_IN,   RSVD2,    RSVD3,    RSVD4),
	PIN(OWR,                  OWR,          CEC,      RSVD3,    RSVD4),
	PIN(DAP1_FS_PN0,          I2S0,         HDA,      GMI,      SDMMC2),
	PIN(DAP1_DIN_PN1,         I2S0,         HDA,      GMI,      SDMMC2),
	PIN(DAP1_DOUT_PN2,        I2S0,         HDA,      GMI,      SDMMC2),
	PIN(DAP1_SCLK_PN3,        I2S0,         HDA,      GMI,      SDMMC2),
	PIN(CLK1_REQ_PEE2,        DAP,          HDA,      RSVD3,    RSVD4),
	PIN(CLK1_OUT_PW4,         EXTPERIPH1,   RSVD2,    RSVD3,    RSVD4),
	PIN(SPDIF_IN_PK6,         SPDIF,        HDA,      I2C1,     SDMMC2),
	PIN(SPDIF_OUT_PK5,        SPDIF,        RSVD2,    I2C1,     SDMMC2),
	PIN(DAP2_FS_PA2,          I2S1,         HDA,      RSVD3,    GMI),
	PIN(DAP2_DIN_PA4,         I2S1,         HDA,      RSVD3,    GMI),
	PIN(DAP2_DOUT_PA5,        I2S1,         HDA,      RSVD3,    GMI),
	PIN(DAP2_SCLK_PA3,        I2S1,         HDA,      RSVD3,    GMI),
	PIN(SPI2_MOSI_PX0,        SPI6,         SPI2,     SPI3,     GMI),
	PIN(SPI2_MISO_PX1,        SPI6,         SPI2,     SPI3,     GMI),
	PIN(SPI2_CS0_N_PX3,       SPI6,         SPI2,     SPI3,     GMI),
	PIN(SPI2_SCK_PX2,         SPI6,         SPI2,     SPI3,     GMI),
	PIN(SPI1_MOSI_PX4,        SPI2,         SPI1,     SPI2_ALT, GMI),
	PIN(SPI1_SCK_PX5,         SPI2,         SPI1,     SPI2_ALT, GMI),
	PIN(SPI1_CS0_N_PX6,       SPI2,         SPI1,     SPI2_ALT, GMI),
	PIN(SPI1_MISO_PX7,        SPI3,         SPI1,     SPI2_ALT, RSVD4),
	PIN(SPI2_CS1_N_PW2,       SPI3,         SPI2,     SPI2_ALT, I2C1),
	PIN(SPI2_CS2_N_PW3,       SPI3,         SPI2,     SPI2_ALT, I2C1),
	PIN(SDMMC3_CLK_PA6,       UARTA,        PWM2,     SDMMC3,   SPI3),
	PIN(SDMMC3_CMD_PA7,       UARTA,        PWM3,     SDMMC3,   SPI2),
	PIN(SDMMC3_DAT0_PB7,      RSVD1,        RSVD2,    SDMMC3,   SPI3),
	PIN(SDMMC3_DAT1_PB6,      RSVD1,        RSVD2,    SDMMC3,   SPI3),
	PIN(SDMMC3_DAT2_PB5,      RSVD1,        PWM1,     SDMMC3,   SPI3),
	PIN(SDMMC3_DAT3_PB4,      RSVD1,        PWM0,     SDMMC3,   SPI3),
	PIN(SDMMC3_DAT4_PD1,      PWM1,         SPI4,     SDMMC3,   SPI2),
	PIN(SDMMC3_DAT5_PD0,      PWM0,         SPI4,     SDMMC3,   SPI2),
	PIN(SDMMC3_DAT6_PD3,      SPDIF,        SPI4,     SDMMC3,   SPI2),
	PIN(SDMMC3_DAT7_PD4,      SPDIF,        SPI4,     SDMMC3,   SPI2),
	PIN(PEX_L0_PRSNT_N_PDD0,  PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L0_RST_N_PDD1,    PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L0_CLKREQ_N_PDD2, PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_WAKE_N_PDD3,      PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L1_PRSNT_N_PDD4,  PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L1_RST_N_PDD5,    PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L1_CLKREQ_N_PDD6, PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L2_PRSNT_N_PDD7,  PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L2_RST_N_PCC6,    PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(PEX_L2_CLKREQ_N_PCC7, PCIE,         HDA,      RSVD3,    RSVD4),
	PIN(HDMI_CEC_PEE3,        CEC,          RSVD2,    RSVD3,    RSVD4),
};
const struct pmux_pingrp_desc *tegra_soc_pingroups = tegra30_pingroups;
