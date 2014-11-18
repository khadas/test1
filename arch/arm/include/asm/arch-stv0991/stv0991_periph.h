/*
 * (C) Copyright 2014
 * Vikas Manocha, ST Micoelectronics, vikas.manocha@st.com.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_ARM_ARCH_PERIPH_H
#define __ASM_ARM_ARCH_PERIPH_H

/*
 * Peripherals required for pinmux configuration. List will
 * grow with support for more devices getting added.
 * Numbering based on interrupt table.
 *
 */
enum periph_id {
	UART_GPIOC_30_31 = 0,
	UART_GPIOB_16_17,
	ETH_GPIOB_10_31_C_0_4,
	PERIPH_ID_I2C0,
	PERIPH_ID_I2C1,
	PERIPH_ID_I2C2,
	PERIPH_ID_I2C3,
	PERIPH_ID_I2C4,
	PERIPH_ID_I2C5,
	PERIPH_ID_I2C6,
	PERIPH_ID_I2C7,
	PERIPH_ID_SPI0,
	PERIPH_ID_SPI1,
	PERIPH_ID_SPI2,
	PERIPH_ID_SDMMC0,
	PERIPH_ID_SDMMC1,
	PERIPH_ID_SDMMC2,
	PERIPH_ID_SDMMC3,
	PERIPH_ID_I2S1,
};

enum periph_clock {
	UART_CLOCK_CFG = 0,
	ETH_CLOCK_CFG,
};

#endif /* __ASM_ARM_ARCH_PERIPH_H */
