/*
 * Copyright (c) 2015, NVIDIA CORPORATION. All rights reserved.
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#ifndef _TEGRA210_PINMUX_H_
#define _TEGRA210_PINMUX_H_

enum pmux_pingrp {
	PMUX_PINGRP_SDMMC1_CLK_PM0,
	PMUX_PINGRP_SDMMC1_CMD_PM1,
	PMUX_PINGRP_SDMMC1_DAT3_PM2,
	PMUX_PINGRP_SDMMC1_DAT2_PM3,
	PMUX_PINGRP_SDMMC1_DAT1_PM4,
	PMUX_PINGRP_SDMMC1_DAT0_PM5,
	PMUX_PINGRP_SDMMC3_CLK_PP0 = (0x1c / 4),
	PMUX_PINGRP_SDMMC3_CMD_PP1,
	PMUX_PINGRP_SDMMC3_DAT0_PP5,
	PMUX_PINGRP_SDMMC3_DAT1_PP4,
	PMUX_PINGRP_SDMMC3_DAT2_PP3,
	PMUX_PINGRP_SDMMC3_DAT3_PP2,
	PMUX_PINGRP_PEX_L0_RST_N_PA0 = (0x38 / 4),
	PMUX_PINGRP_PEX_L0_CLKREQ_N_PA1,
	PMUX_PINGRP_PEX_WAKE_N_PA2,
	PMUX_PINGRP_PEX_L1_RST_N_PA3,
	PMUX_PINGRP_PEX_L1_CLKREQ_N_PA4,
	PMUX_PINGRP_SATA_LED_ACTIVE_PA5,
	PMUX_PINGRP_SPI1_MOSI_PC0,
	PMUX_PINGRP_SPI1_MISO_PC1,
	PMUX_PINGRP_SPI1_SCK_PC2,
	PMUX_PINGRP_SPI1_CS0_PC3,
	PMUX_PINGRP_SPI1_CS1_PC4,
	PMUX_PINGRP_SPI2_MOSI_PB4,
	PMUX_PINGRP_SPI2_MISO_PB5,
	PMUX_PINGRP_SPI2_SCK_PB6,
	PMUX_PINGRP_SPI2_CS0_PB7,
	PMUX_PINGRP_SPI2_CS1_PDD0,
	PMUX_PINGRP_SPI4_MOSI_PC7,
	PMUX_PINGRP_SPI4_MISO_PD0,
	PMUX_PINGRP_SPI4_SCK_PC5,
	PMUX_PINGRP_SPI4_CS0_PC6,
	PMUX_PINGRP_QSPI_SCK_PEE0,
	PMUX_PINGRP_QSPI_CS_N_PEE1,
	PMUX_PINGRP_QSPI_IO0_PEE2,
	PMUX_PINGRP_QSPI_IO1_PEE3,
	PMUX_PINGRP_QSPI_IO2_PEE4,
	PMUX_PINGRP_QSPI_IO3_PEE5,
	PMUX_PINGRP_DMIC1_CLK_PE0 = (0xa4 / 4),
	PMUX_PINGRP_DMIC1_DAT_PE1,
	PMUX_PINGRP_DMIC2_CLK_PE2,
	PMUX_PINGRP_DMIC2_DAT_PE3,
	PMUX_PINGRP_DMIC3_CLK_PE4,
	PMUX_PINGRP_DMIC3_DAT_PE5,
	PMUX_PINGRP_GEN1_I2C_SCL_PJ1,
	PMUX_PINGRP_GEN1_I2C_SDA_PJ0,
	PMUX_PINGRP_GEN2_I2C_SCL_PJ2,
	PMUX_PINGRP_GEN2_I2C_SDA_PJ3,
	PMUX_PINGRP_GEN3_I2C_SCL_PF0,
	PMUX_PINGRP_GEN3_I2C_SDA_PF1,
	PMUX_PINGRP_CAM_I2C_SCL_PS2,
	PMUX_PINGRP_CAM_I2C_SDA_PS3,
	PMUX_PINGRP_PWR_I2C_SCL_PY3,
	PMUX_PINGRP_PWR_I2C_SDA_PY4,
	PMUX_PINGRP_UART1_TX_PU0,
	PMUX_PINGRP_UART1_RX_PU1,
	PMUX_PINGRP_UART1_RTS_PU2,
	PMUX_PINGRP_UART1_CTS_PU3,
	PMUX_PINGRP_UART2_TX_PG0,
	PMUX_PINGRP_UART2_RX_PG1,
	PMUX_PINGRP_UART2_RTS_PG2,
	PMUX_PINGRP_UART2_CTS_PG3,
	PMUX_PINGRP_UART3_TX_PD1,
	PMUX_PINGRP_UART3_RX_PD2,
	PMUX_PINGRP_UART3_RTS_PD3,
	PMUX_PINGRP_UART3_CTS_PD4,
	PMUX_PINGRP_UART4_TX_PI4,
	PMUX_PINGRP_UART4_RX_PI5,
	PMUX_PINGRP_UART4_RTS_PI6,
	PMUX_PINGRP_UART4_CTS_PI7,
	PMUX_PINGRP_DAP1_FS_PB0,
	PMUX_PINGRP_DAP1_DIN_PB1,
	PMUX_PINGRP_DAP1_DOUT_PB2,
	PMUX_PINGRP_DAP1_SCLK_PB3,
	PMUX_PINGRP_DAP2_FS_PAA0,
	PMUX_PINGRP_DAP2_DIN_PAA2,
	PMUX_PINGRP_DAP2_DOUT_PAA3,
	PMUX_PINGRP_DAP2_SCLK_PAA1,
	PMUX_PINGRP_DAP4_FS_PJ4,
	PMUX_PINGRP_DAP4_DIN_PJ5,
	PMUX_PINGRP_DAP4_DOUT_PJ6,
	PMUX_PINGRP_DAP4_SCLK_PJ7,
	PMUX_PINGRP_CAM1_MCLK_PS0,
	PMUX_PINGRP_CAM2_MCLK_PS1,
	PMUX_PINGRP_JTAG_RTCK,
	PMUX_PINGRP_CLK_32K_IN,
	PMUX_PINGRP_CLK_32K_OUT_PY5,
	PMUX_PINGRP_BATT_BCL,
	PMUX_PINGRP_CLK_REQ,
	PMUX_PINGRP_CPU_PWR_REQ,
	PMUX_PINGRP_PWR_INT_N,
	PMUX_PINGRP_SHUTDOWN,
	PMUX_PINGRP_CORE_PWR_REQ,
	PMUX_PINGRP_AUD_MCLK_PBB0,
	PMUX_PINGRP_DVFS_PWM_PBB1,
	PMUX_PINGRP_DVFS_CLK_PBB2,
	PMUX_PINGRP_GPIO_X1_AUD_PBB3,
	PMUX_PINGRP_GPIO_X3_AUD_PBB4,
	PMUX_PINGRP_PCC7,
	PMUX_PINGRP_HDMI_CEC_PCC0,
	PMUX_PINGRP_HDMI_INT_DP_HPD_PCC1,
	PMUX_PINGRP_SPDIF_OUT_PCC2,
	PMUX_PINGRP_SPDIF_IN_PCC3,
	PMUX_PINGRP_USB_VBUS_EN0_PCC4,
	PMUX_PINGRP_USB_VBUS_EN1_PCC5,
	PMUX_PINGRP_DP_HPD0_PCC6,
	PMUX_PINGRP_WIFI_EN_PH0,
	PMUX_PINGRP_WIFI_RST_PH1,
	PMUX_PINGRP_WIFI_WAKE_AP_PH2,
	PMUX_PINGRP_AP_WAKE_BT_PH3,
	PMUX_PINGRP_BT_RST_PH4,
	PMUX_PINGRP_BT_WAKE_AP_PH5,
	PMUX_PINGRP_AP_WAKE_NFC_PH7,
	PMUX_PINGRP_NFC_EN_PI0,
	PMUX_PINGRP_NFC_INT_PI1,
	PMUX_PINGRP_GPS_EN_PI2,
	PMUX_PINGRP_GPS_RST_PI3,
	PMUX_PINGRP_CAM_RST_PS4,
	PMUX_PINGRP_CAM_AF_EN_PS5,
	PMUX_PINGRP_CAM_FLASH_EN_PS6,
	PMUX_PINGRP_CAM1_PWDN_PS7,
	PMUX_PINGRP_CAM2_PWDN_PT0,
	PMUX_PINGRP_CAM1_STROBE_PT1,
	PMUX_PINGRP_LCD_TE_PY2,
	PMUX_PINGRP_LCD_BL_PWM_PV0,
	PMUX_PINGRP_LCD_BL_EN_PV1,
	PMUX_PINGRP_LCD_RST_PV2,
	PMUX_PINGRP_LCD_GPIO1_PV3,
	PMUX_PINGRP_LCD_GPIO2_PV4,
	PMUX_PINGRP_AP_READY_PV5,
	PMUX_PINGRP_TOUCH_RST_PV6,
	PMUX_PINGRP_TOUCH_CLK_PV7,
	PMUX_PINGRP_MODEM_WAKE_AP_PX0,
	PMUX_PINGRP_TOUCH_INT_PX1,
	PMUX_PINGRP_MOTION_INT_PX2,
	PMUX_PINGRP_ALS_PROX_INT_PX3,
	PMUX_PINGRP_TEMP_ALERT_PX4,
	PMUX_PINGRP_BUTTON_POWER_ON_PX5,
	PMUX_PINGRP_BUTTON_VOL_UP_PX6,
	PMUX_PINGRP_BUTTON_VOL_DOWN_PX7,
	PMUX_PINGRP_BUTTON_SLIDE_SW_PY0,
	PMUX_PINGRP_BUTTON_HOME_PY1,
	PMUX_PINGRP_PA6,
	PMUX_PINGRP_PE6,
	PMUX_PINGRP_PE7,
	PMUX_PINGRP_PH6,
	PMUX_PINGRP_PK0,
	PMUX_PINGRP_PK1,
	PMUX_PINGRP_PK2,
	PMUX_PINGRP_PK3,
	PMUX_PINGRP_PK4,
	PMUX_PINGRP_PK5,
	PMUX_PINGRP_PK6,
	PMUX_PINGRP_PK7,
	PMUX_PINGRP_PL0,
	PMUX_PINGRP_PL1,
	PMUX_PINGRP_PZ0,
	PMUX_PINGRP_PZ1,
	PMUX_PINGRP_PZ2,
	PMUX_PINGRP_PZ3,
	PMUX_PINGRP_PZ4,
	PMUX_PINGRP_PZ5,
	PMUX_PINGRP_COUNT,
};

enum pmux_drvgrp {
	PMUX_DRVGRP_ALS_PROX_INT = (0x10 / 4),
	PMUX_DRVGRP_AP_READY,
	PMUX_DRVGRP_AP_WAKE_BT,
	PMUX_DRVGRP_AP_WAKE_NFC,
	PMUX_DRVGRP_AUD_MCLK,
	PMUX_DRVGRP_BATT_BCL,
	PMUX_DRVGRP_BT_RST,
	PMUX_DRVGRP_BT_WAKE_AP,
	PMUX_DRVGRP_BUTTON_HOME,
	PMUX_DRVGRP_BUTTON_POWER_ON,
	PMUX_DRVGRP_BUTTON_SLIDE_SW,
	PMUX_DRVGRP_BUTTON_VOL_DOWN,
	PMUX_DRVGRP_BUTTON_VOL_UP,
	PMUX_DRVGRP_CAM1_MCLK,
	PMUX_DRVGRP_CAM1_PWDN,
	PMUX_DRVGRP_CAM1_STROBE,
	PMUX_DRVGRP_CAM2_MCLK,
	PMUX_DRVGRP_CAM2_PWDN,
	PMUX_DRVGRP_CAM_AF_EN,
	PMUX_DRVGRP_CAM_FLASH_EN,
	PMUX_DRVGRP_CAM_I2C_SCL,
	PMUX_DRVGRP_CAM_I2C_SDA,
	PMUX_DRVGRP_CAM_RST,
	PMUX_DRVGRP_CLK_32K_IN,
	PMUX_DRVGRP_CLK_32K_OUT,
	PMUX_DRVGRP_CLK_REQ,
	PMUX_DRVGRP_CORE_PWR_REQ,
	PMUX_DRVGRP_CPU_PWR_REQ,
	PMUX_DRVGRP_DAP1_DIN,
	PMUX_DRVGRP_DAP1_DOUT,
	PMUX_DRVGRP_DAP1_FS,
	PMUX_DRVGRP_DAP1_SCLK,
	PMUX_DRVGRP_DAP2_DIN,
	PMUX_DRVGRP_DAP2_DOUT,
	PMUX_DRVGRP_DAP2_FS,
	PMUX_DRVGRP_DAP2_SCLK,
	PMUX_DRVGRP_DAP4_DIN,
	PMUX_DRVGRP_DAP4_DOUT,
	PMUX_DRVGRP_DAP4_FS,
	PMUX_DRVGRP_DAP4_SCLK,
	PMUX_DRVGRP_DMIC1_CLK,
	PMUX_DRVGRP_DMIC1_DAT,
	PMUX_DRVGRP_DMIC2_CLK,
	PMUX_DRVGRP_DMIC2_DAT,
	PMUX_DRVGRP_DMIC3_CLK,
	PMUX_DRVGRP_DMIC3_DAT,
	PMUX_DRVGRP_DP_HPD0,
	PMUX_DRVGRP_DVFS_CLK,
	PMUX_DRVGRP_DVFS_PWM,
	PMUX_DRVGRP_GEN1_I2C_SCL,
	PMUX_DRVGRP_GEN1_I2C_SDA,
	PMUX_DRVGRP_GEN2_I2C_SCL,
	PMUX_DRVGRP_GEN2_I2C_SDA,
	PMUX_DRVGRP_GEN3_I2C_SCL,
	PMUX_DRVGRP_GEN3_I2C_SDA,
	PMUX_DRVGRP_PA6,
	PMUX_DRVGRP_PCC7,
	PMUX_DRVGRP_PE6,
	PMUX_DRVGRP_PE7,
	PMUX_DRVGRP_PH6,
	PMUX_DRVGRP_PK0,
	PMUX_DRVGRP_PK1,
	PMUX_DRVGRP_PK2,
	PMUX_DRVGRP_PK3,
	PMUX_DRVGRP_PK4,
	PMUX_DRVGRP_PK5,
	PMUX_DRVGRP_PK6,
	PMUX_DRVGRP_PK7,
	PMUX_DRVGRP_PL0,
	PMUX_DRVGRP_PL1,
	PMUX_DRVGRP_PZ0,
	PMUX_DRVGRP_PZ1,
	PMUX_DRVGRP_PZ2,
	PMUX_DRVGRP_PZ3,
	PMUX_DRVGRP_PZ4,
	PMUX_DRVGRP_PZ5,
	PMUX_DRVGRP_GPIO_X1_AUD,
	PMUX_DRVGRP_GPIO_X3_AUD,
	PMUX_DRVGRP_GPS_EN,
	PMUX_DRVGRP_GPS_RST,
	PMUX_DRVGRP_HDMI_CEC,
	PMUX_DRVGRP_HDMI_INT_DP_HPD,
	PMUX_DRVGRP_JTAG_RTCK,
	PMUX_DRVGRP_LCD_BL_EN,
	PMUX_DRVGRP_LCD_BL_PWM,
	PMUX_DRVGRP_LCD_GPIO1,
	PMUX_DRVGRP_LCD_GPIO2,
	PMUX_DRVGRP_LCD_RST,
	PMUX_DRVGRP_LCD_TE,
	PMUX_DRVGRP_MODEM_WAKE_AP,
	PMUX_DRVGRP_MOTION_INT,
	PMUX_DRVGRP_NFC_EN,
	PMUX_DRVGRP_NFC_INT,
	PMUX_DRVGRP_PEX_L0_CLKREQ_N,
	PMUX_DRVGRP_PEX_L0_RST_N,
	PMUX_DRVGRP_PEX_L1_CLKREQ_N,
	PMUX_DRVGRP_PEX_L1_RST_N,
	PMUX_DRVGRP_PEX_WAKE_N,
	PMUX_DRVGRP_PWR_I2C_SCL,
	PMUX_DRVGRP_PWR_I2C_SDA,
	PMUX_DRVGRP_PWR_INT_N,
	PMUX_DRVGRP_QSPI_SCK = (0x1bc / 4),
	PMUX_DRVGRP_SATA_LED_ACTIVE,
	PMUX_DRVGRP_SDMMC1,
	PMUX_DRVGRP_SDMMC2,
	PMUX_DRVGRP_SDMMC3 = (0x1dc / 4),
	PMUX_DRVGRP_SDMMC4,
	PMUX_DRVGRP_SHUTDOWN = (0x1f4 / 4),
	PMUX_DRVGRP_SPDIF_IN,
	PMUX_DRVGRP_SPDIF_OUT,
	PMUX_DRVGRP_SPI1_CS0,
	PMUX_DRVGRP_SPI1_CS1,
	PMUX_DRVGRP_SPI1_MISO,
	PMUX_DRVGRP_SPI1_MOSI,
	PMUX_DRVGRP_SPI1_SCK,
	PMUX_DRVGRP_SPI2_CS0,
	PMUX_DRVGRP_SPI2_CS1,
	PMUX_DRVGRP_SPI2_MISO,
	PMUX_DRVGRP_SPI2_MOSI,
	PMUX_DRVGRP_SPI2_SCK,
	PMUX_DRVGRP_SPI4_CS0,
	PMUX_DRVGRP_SPI4_MISO,
	PMUX_DRVGRP_SPI4_MOSI,
	PMUX_DRVGRP_SPI4_SCK,
	PMUX_DRVGRP_TEMP_ALERT,
	PMUX_DRVGRP_TOUCH_CLK,
	PMUX_DRVGRP_TOUCH_INT,
	PMUX_DRVGRP_TOUCH_RST,
	PMUX_DRVGRP_UART1_CTS,
	PMUX_DRVGRP_UART1_RTS,
	PMUX_DRVGRP_UART1_RX,
	PMUX_DRVGRP_UART1_TX,
	PMUX_DRVGRP_UART2_CTS,
	PMUX_DRVGRP_UART2_RTS,
	PMUX_DRVGRP_UART2_RX,
	PMUX_DRVGRP_UART2_TX,
	PMUX_DRVGRP_UART3_CTS,
	PMUX_DRVGRP_UART3_RTS,
	PMUX_DRVGRP_UART3_RX,
	PMUX_DRVGRP_UART3_TX,
	PMUX_DRVGRP_UART4_CTS,
	PMUX_DRVGRP_UART4_RTS,
	PMUX_DRVGRP_UART4_RX,
	PMUX_DRVGRP_UART4_TX,
	PMUX_DRVGRP_USB_VBUS_EN0,
	PMUX_DRVGRP_USB_VBUS_EN1,
	PMUX_DRVGRP_WIFI_EN,
	PMUX_DRVGRP_WIFI_RST,
	PMUX_DRVGRP_WIFI_WAKE_AP,
	PMUX_DRVGRP_COUNT,
};

enum pmux_func {
	PMUX_FUNC_DEFAULT,
	PMUX_FUNC_AUD,
	PMUX_FUNC_BCL,
	PMUX_FUNC_BLINK,
	PMUX_FUNC_CCLA,
	PMUX_FUNC_CEC,
	PMUX_FUNC_CLDVFS,
	PMUX_FUNC_CLK,
	PMUX_FUNC_CORE,
	PMUX_FUNC_CPU,
	PMUX_FUNC_DISPLAYA,
	PMUX_FUNC_DISPLAYB,
	PMUX_FUNC_DMIC1,
	PMUX_FUNC_DMIC2,
	PMUX_FUNC_DMIC3,
	PMUX_FUNC_DP,
	PMUX_FUNC_DTV,
	PMUX_FUNC_EXTPERIPH3,
	PMUX_FUNC_I2C1,
	PMUX_FUNC_I2C2,
	PMUX_FUNC_I2C3,
	PMUX_FUNC_I2CPMU,
	PMUX_FUNC_I2CVI,
	PMUX_FUNC_I2S1,
	PMUX_FUNC_I2S2,
	PMUX_FUNC_I2S3,
	PMUX_FUNC_I2S4A,
	PMUX_FUNC_I2S4B,
	PMUX_FUNC_I2S5A,
	PMUX_FUNC_I2S5B,
	PMUX_FUNC_IQC0,
	PMUX_FUNC_IQC1,
	PMUX_FUNC_JTAG,
	PMUX_FUNC_PE,
	PMUX_FUNC_PE0,
	PMUX_FUNC_PE1,
	PMUX_FUNC_PMI,
	PMUX_FUNC_PWM0,
	PMUX_FUNC_PWM1,
	PMUX_FUNC_PWM2,
	PMUX_FUNC_PWM3,
	PMUX_FUNC_QSPI,
	PMUX_FUNC_SATA,
	PMUX_FUNC_SDMMC1,
	PMUX_FUNC_SDMMC3,
	PMUX_FUNC_SHUTDOWN,
	PMUX_FUNC_SOC,
	PMUX_FUNC_SOR0,
	PMUX_FUNC_SOR1,
	PMUX_FUNC_SPDIF,
	PMUX_FUNC_SPI1,
	PMUX_FUNC_SPI2,
	PMUX_FUNC_SPI3,
	PMUX_FUNC_SPI4,
	PMUX_FUNC_SYS,
	PMUX_FUNC_TOUCH,
	PMUX_FUNC_UART,
	PMUX_FUNC_UARTA,
	PMUX_FUNC_UARTB,
	PMUX_FUNC_UARTC,
	PMUX_FUNC_UARTD,
	PMUX_FUNC_USB,
	PMUX_FUNC_VGP1,
	PMUX_FUNC_VGP2,
	PMUX_FUNC_VGP3,
	PMUX_FUNC_VGP4,
	PMUX_FUNC_VGP5,
	PMUX_FUNC_VGP6,
	PMUX_FUNC_VIMCLK,
	PMUX_FUNC_VIMCLK2,
	PMUX_FUNC_RSVD0,
	PMUX_FUNC_RSVD1,
	PMUX_FUNC_RSVD2,
	PMUX_FUNC_RSVD3,
	PMUX_FUNC_COUNT,
};

#define TEGRA_PMX_SOC_DRV_GROUP_BASE_REG 0x8d4
#define TEGRA_PMX_SOC_HAS_IO_CLAMPING
#define TEGRA_PMX_SOC_HAS_DRVGRPS
#define TEGRA_PMX_PINS_HAVE_E_INPUT
#define TEGRA_PMX_PINS_HAVE_LOCK
#define TEGRA_PMX_PINS_HAVE_OD
#define TEGRA_PMX_PINS_HAVE_E_IO_HV
#include <asm/arch-tegra/pinmux.h>

#endif /* _TEGRA210_PINMUX_H_ */
