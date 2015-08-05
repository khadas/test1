/*
 * Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

/*
 * THIS FILE IS AUTO-GENERATED - DO NOT EDIT!
 *
 * To generate this file, use the tegra-pinmux-scripts tool available from
 * https://github.com/NVIDIA/tegra-pinmux-scripts
 * Run "board-to-uboot.py p2371-0000".
 */

#ifndef _PINMUX_CONFIG_P2371_0000_H_
#define _PINMUX_CONFIG_P2371_0000_H_

#define GPIO_INIT(_gpio, _init)				\
	{						\
		.gpio	= GPIO_P##_gpio,		\
		.init	= TEGRA_GPIO_INIT_##_init,	\
	}

static const struct tegra_gpio_config p2371_0000_gpio_inits[] = {
	/*        gpio, init_val */
	GPIO_INIT(A5,   IN),
	GPIO_INIT(E4,   OUT0),
	GPIO_INIT(E6,   IN),
	GPIO_INIT(G0,   IN),
	GPIO_INIT(G3,   OUT0),
	GPIO_INIT(H0,   OUT0),
	GPIO_INIT(H2,   IN),
	GPIO_INIT(H3,   OUT0),
	GPIO_INIT(H4,   OUT0),
	GPIO_INIT(H5,   IN),
	GPIO_INIT(H6,   OUT0),
	GPIO_INIT(H7,   OUT0),
	GPIO_INIT(I0,   OUT0),
	GPIO_INIT(I1,   IN),
	GPIO_INIT(I2,   OUT0),
	GPIO_INIT(I3,   OUT0),
	GPIO_INIT(K4,   IN),
	GPIO_INIT(K5,   OUT0),
	GPIO_INIT(K6,   IN),
	GPIO_INIT(K7,   OUT0),
	GPIO_INIT(L0,   OUT0),
	GPIO_INIT(S4,   OUT0),
	GPIO_INIT(S5,   OUT0),
	GPIO_INIT(S6,   OUT0),
	GPIO_INIT(S7,   OUT0),
	GPIO_INIT(T0,   OUT0),
	GPIO_INIT(T1,   OUT0),
	GPIO_INIT(V1,   OUT0),
	GPIO_INIT(V2,   OUT0),
	GPIO_INIT(V5,   OUT0),
	GPIO_INIT(V6,   OUT0),
	GPIO_INIT(V7,   OUT1),
	GPIO_INIT(X0,   IN),
	GPIO_INIT(X1,   IN),
	GPIO_INIT(X2,   IN),
	GPIO_INIT(X3,   IN),
	GPIO_INIT(X4,   IN),
	GPIO_INIT(X5,   IN),
	GPIO_INIT(X6,   IN),
	GPIO_INIT(X7,   IN),
	GPIO_INIT(Y1,   IN),
	GPIO_INIT(Z0,   IN),
	GPIO_INIT(Z4,   OUT0),
	GPIO_INIT(BB2,  OUT0),
	GPIO_INIT(BB3,  OUT0),
	GPIO_INIT(CC1,  IN),
	GPIO_INIT(CC6,  IN),
	GPIO_INIT(CC7,  OUT0),
};

#define PINCFG(_pingrp, _mux, _pull, _tri, _io, _od, _e_io_hv)	\
	{							\
		.pingrp		= PMUX_PINGRP_##_pingrp,	\
		.func		= PMUX_FUNC_##_mux,		\
		.pull		= PMUX_PULL_##_pull,		\
		.tristate	= PMUX_TRI_##_tri,		\
		.io		= PMUX_PIN_##_io,		\
		.od		= PMUX_PIN_OD_##_od,		\
		.e_io_hv	= PMUX_PIN_E_IO_HV_##_e_io_hv,	\
		.lock		= PMUX_PIN_LOCK_DEFAULT,	\
	}

static const struct pmux_pingrp_config p2371_0000_pingrps[] = {
	/*     pingrp,               mux,        pull,   tri,      e_input, od,      e_io_hv */
	PINCFG(PEX_L0_RST_N_PA0,     PE0,        NORMAL, NORMAL,   OUTPUT,  DISABLE, HIGH),
	PINCFG(PEX_L0_CLKREQ_N_PA1,  PE0,        NORMAL, NORMAL,   INPUT,   DISABLE, HIGH),
	PINCFG(PEX_WAKE_N_PA2,       PE,         NORMAL, NORMAL,   INPUT,   DISABLE, HIGH),
	PINCFG(PEX_L1_RST_N_PA3,     PE1,        NORMAL, NORMAL,   OUTPUT,  DISABLE, HIGH),
	PINCFG(PEX_L1_CLKREQ_N_PA4,  PE1,        NORMAL, NORMAL,   INPUT,   DISABLE, HIGH),
	PINCFG(SATA_LED_ACTIVE_PA5,  DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PA6,                  RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(DAP1_FS_PB0,          I2S1,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP1_DIN_PB1,         I2S1,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP1_DOUT_PB2,        I2S1,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP1_SCLK_PB3,        I2S1,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SPI2_MOSI_PB4,        RSVD2,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPI2_MISO_PB5,        RSVD2,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPI2_SCK_PB6,         RSVD2,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPI2_CS0_PB7,         RSVD2,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPI1_MOSI_PC0,        SPI1,       DOWN,   NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SPI1_MISO_PC1,        SPI1,       DOWN,   NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SPI1_SCK_PC2,         SPI1,       DOWN,   NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SPI1_CS0_PC3,         SPI1,       UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SPI1_CS1_PC4,         SPI1,       UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SPI4_SCK_PC5,         SPI4,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPI4_CS0_PC6,         SPI4,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPI4_MOSI_PC7,        SPI4,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPI4_MISO_PD0,        SPI4,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(UART3_TX_PD1,         UARTC,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART3_RX_PD2,         UARTC,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(UART3_RTS_PD3,        UARTC,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART3_CTS_PD4,        UARTC,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DMIC1_CLK_PE0,        DMIC1,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(DMIC1_DAT_PE1,        DMIC1,      DOWN,   NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DMIC2_CLK_PE2,        DMIC2,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(DMIC2_DAT_PE3,        DMIC2,      DOWN,   NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DMIC3_CLK_PE4,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(DMIC3_DAT_PE5,        RSVD2,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PE6,                  DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PE7,                  PWM3,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(GEN3_I2C_SCL_PF0,     I2C3,       NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(GEN3_I2C_SDA_PF1,     I2C3,       NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(UART2_TX_PG0,         DEFAULT,    NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(UART2_RX_PG1,         UARTB,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART2_RTS_PG2,        RSVD2,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART2_CTS_PG3,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(WIFI_EN_PH0,          DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(WIFI_RST_PH1,         RSVD0,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(WIFI_WAKE_AP_PH2,     DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(AP_WAKE_BT_PH3,       DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(BT_RST_PH4,           DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(BT_WAKE_AP_PH5,       DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PH6,                  DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(AP_WAKE_NFC_PH7,      DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(NFC_EN_PI0,           DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(NFC_INT_PI1,          DEFAULT,    NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(GPS_EN_PI2,           DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(GPS_RST_PI3,          DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART4_TX_PI4,         UARTD,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART4_RX_PI5,         UARTD,      NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(UART4_RTS_PI6,        UARTD,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART4_CTS_PI7,        UARTD,      NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(GEN1_I2C_SDA_PJ0,     I2C1,       NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(GEN1_I2C_SCL_PJ1,     I2C1,       NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(GEN2_I2C_SCL_PJ2,     I2C2,       NORMAL, NORMAL,   INPUT,   DISABLE, HIGH),
	PINCFG(GEN2_I2C_SDA_PJ3,     I2C2,       NORMAL, NORMAL,   INPUT,   DISABLE, HIGH),
	PINCFG(DAP4_FS_PJ4,          I2S4B,      NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP4_DIN_PJ5,         I2S4B,      NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP4_DOUT_PJ6,        I2S4B,      NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP4_SCLK_PJ7,        I2S4B,      NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PK0,                  I2S5B,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PK1,                  I2S5B,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PK2,                  I2S5B,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PK3,                  I2S5B,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PK4,                  DEFAULT,    NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PK5,                  DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PK6,                  DEFAULT,    NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PK7,                  DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PL0,                  DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PL1,                  SOC,        UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC1_CLK_PM0,       SDMMC1,     NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC1_CMD_PM1,       SDMMC1,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC1_DAT3_PM2,      SDMMC1,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC1_DAT2_PM3,      SDMMC1,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC1_DAT1_PM4,      SDMMC1,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC1_DAT0_PM5,      SDMMC1,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC3_CLK_PP0,       SDMMC3,     NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC3_CMD_PP1,       SDMMC3,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC3_DAT3_PP2,      SDMMC3,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC3_DAT2_PP3,      SDMMC3,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC3_DAT1_PP4,      SDMMC3,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(SDMMC3_DAT0_PP5,      SDMMC3,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(CAM1_MCLK_PS0,        EXTPERIPH3, NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CAM2_MCLK_PS1,        EXTPERIPH3, NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CAM_I2C_SCL_PS2,      I2CVI,      NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(CAM_I2C_SDA_PS3,      I2CVI,      NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(CAM_RST_PS4,          DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CAM_AF_EN_PS5,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CAM_FLASH_EN_PS6,     DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CAM1_PWDN_PS7,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CAM2_PWDN_PT0,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CAM1_STROBE_PT1,      DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART1_TX_PU0,         UARTA,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART1_RX_PU1,         UARTA,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(UART1_RTS_PU2,        UARTA,      NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(UART1_CTS_PU3,        UARTA,      UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(LCD_BL_PWM_PV0,       PWM0,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(LCD_BL_EN_PV1,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(LCD_RST_PV2,          DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(LCD_GPIO1_PV3,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(LCD_GPIO2_PV4,        PWM1,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(AP_READY_PV5,         DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(TOUCH_RST_PV6,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(TOUCH_CLK_PV7,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(MODEM_WAKE_AP_PX0,    DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(TOUCH_INT_PX1,        DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(MOTION_INT_PX2,       DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(ALS_PROX_INT_PX3,     DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(TEMP_ALERT_PX4,       DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(BUTTON_POWER_ON_PX5,  DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(BUTTON_VOL_UP_PX6,    DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(BUTTON_VOL_DOWN_PX7,  DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(BUTTON_SLIDE_SW_PY0,  RSVD0,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(BUTTON_HOME_PY1,      DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(LCD_TE_PY2,           DISPLAYA,   DOWN,   NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PWR_I2C_SCL_PY3,      I2CPMU,     NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(PWR_I2C_SDA_PY4,      I2CPMU,     NORMAL, NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(CLK_32K_OUT_PY5,      SOC,        UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PZ0,                  DEFAULT,    UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PZ1,                  SDMMC1,     UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PZ2,                  RSVD2,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PZ3,                  RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PZ4,                  DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PZ5,                  SOC,        UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP2_FS_PAA0,         I2S2,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP2_SCLK_PAA1,       I2S2,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP2_DIN_PAA2,        I2S2,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(DAP2_DOUT_PAA3,       I2S2,       NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(AUD_MCLK_PBB0,        AUD,        NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(DVFS_PWM_PBB1,        CLDVFS,     NORMAL, TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(DVFS_CLK_PBB2,        DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(GPIO_X1_AUD_PBB3,     DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(GPIO_X3_AUD_PBB4,     RSVD0,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(HDMI_CEC_PCC0,        CEC,        NORMAL, NORMAL,   INPUT,   DISABLE, HIGH),
	PINCFG(HDMI_INT_DP_HPD_PCC1, DEFAULT,    DOWN,   NORMAL,   INPUT,   DISABLE, NORMAL),
	PINCFG(SPDIF_OUT_PCC2,       RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SPDIF_IN_PCC3,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(USB_VBUS_EN0_PCC4,    USB,        NORMAL, NORMAL,   INPUT,   DISABLE, HIGH),
	PINCFG(USB_VBUS_EN1_PCC5,    RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, NORMAL),
	PINCFG(DP_HPD0_PCC6,         DEFAULT,    DOWN,   NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(PCC7,                 DEFAULT,    NORMAL, NORMAL,   OUTPUT,  DISABLE, NORMAL),
	PINCFG(SPI2_CS1_PDD0,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(QSPI_SCK_PEE0,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(QSPI_CS_N_PEE1,       RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(QSPI_IO0_PEE2,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(QSPI_IO1_PEE3,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(QSPI_IO2_PEE4,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(QSPI_IO3_PEE5,        RSVD1,      DOWN,   TRISTATE, OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CORE_PWR_REQ,         CORE,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CPU_PWR_REQ,          CPU,        NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(PWR_INT_N,            PMI,        UP,     NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(CLK_32K_IN,           CLK,        NORMAL, NORMAL,   INPUT,   DISABLE, DEFAULT),
	PINCFG(JTAG_RTCK,            JTAG,       NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(CLK_REQ,              SYS,        NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
	PINCFG(SHUTDOWN,             SHUTDOWN,   NORMAL, NORMAL,   OUTPUT,  DISABLE, DEFAULT),
};

#define DRVCFG(_drvgrp, _slwf, _slwr, _drvup, _drvdn, _lpmd, _schmt, _hsm) \
	{						\
		.drvgrp = PMUX_DRVGRP_##_drvgrp,	\
		.slwf   = _slwf,			\
		.slwr   = _slwr,			\
		.drvup  = _drvup,			\
		.drvdn  = _drvdn,			\
		.lpmd   = PMUX_LPMD_##_lpmd,		\
		.schmt  = PMUX_SCHMT_##_schmt,		\
		.hsm    = PMUX_HSM_##_hsm,		\
	}

static const struct pmux_drvgrp_config p2371_0000_drvgrps[] = {
};

#endif /* PINMUX_CONFIG_P2371_0000_H */
