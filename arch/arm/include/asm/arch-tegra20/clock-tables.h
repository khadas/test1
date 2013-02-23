/*
 * Copyright (c) 2011 The Chromium OS Authors.
 * Copyright (c) 2010-2012 NVIDIA Corporation <www.nvidia.com>
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* Tegra20 clock PLL tables */

#ifndef _CLOCK_TABLES_H_
#define _CLOCK_TABLES_H_

/* The PLLs supported by the hardware */
enum clock_id {
	CLOCK_ID_FIRST,
	CLOCK_ID_CGENERAL = CLOCK_ID_FIRST,
	CLOCK_ID_MEMORY,
	CLOCK_ID_PERIPH,
	CLOCK_ID_AUDIO,
	CLOCK_ID_USB,
	CLOCK_ID_DISPLAY,

	/* now the simple ones */
	CLOCK_ID_FIRST_SIMPLE,
	CLOCK_ID_XCPU = CLOCK_ID_FIRST_SIMPLE,
	CLOCK_ID_EPCI,
	CLOCK_ID_SFROM32KHZ,

	/* These are the base clocks (inputs to the Tegra SOC) */
	CLOCK_ID_32KHZ,
	CLOCK_ID_OSC,

	CLOCK_ID_COUNT,	/* number of clocks */
	CLOCK_ID_NONE = -1,
};

/* The clocks supported by the hardware */
enum periph_id {
	PERIPH_ID_FIRST,

	/* Low word: 31:0 */
	PERIPH_ID_CPU = PERIPH_ID_FIRST,
	PERIPH_ID_RESERVED1,
	PERIPH_ID_RESERVED2,
	PERIPH_ID_AC97,
	PERIPH_ID_RTC,
	PERIPH_ID_TMR,
	PERIPH_ID_UART1,
	PERIPH_ID_UART2,

	/* 8 */
	PERIPH_ID_GPIO,
	PERIPH_ID_SDMMC2,
	PERIPH_ID_SPDIF,
	PERIPH_ID_I2S1,
	PERIPH_ID_I2C1,
	PERIPH_ID_NDFLASH,
	PERIPH_ID_SDMMC1,
	PERIPH_ID_SDMMC4,

	/* 16 */
	PERIPH_ID_TWC,
	PERIPH_ID_PWM,
	PERIPH_ID_I2S2,
	PERIPH_ID_EPP,
	PERIPH_ID_VI,
	PERIPH_ID_2D,
	PERIPH_ID_USBD,
	PERIPH_ID_ISP,

	/* 24 */
	PERIPH_ID_3D,
	PERIPH_ID_IDE,
	PERIPH_ID_DISP2,
	PERIPH_ID_DISP1,
	PERIPH_ID_HOST1X,
	PERIPH_ID_VCP,
	PERIPH_ID_RESERVED30,
	PERIPH_ID_CACHE2,

	/* Middle word: 63:32 */
	PERIPH_ID_MEM,
	PERIPH_ID_AHBDMA,
	PERIPH_ID_APBDMA,
	PERIPH_ID_RESERVED35,
	PERIPH_ID_KBC,
	PERIPH_ID_STAT_MON,
	PERIPH_ID_PMC,
	PERIPH_ID_FUSE,

	/* 40 */
	PERIPH_ID_KFUSE,
	PERIPH_ID_SBC1,
	PERIPH_ID_SNOR,
	PERIPH_ID_SPI1,
	PERIPH_ID_SBC2,
	PERIPH_ID_XIO,
	PERIPH_ID_SBC3,
	PERIPH_ID_DVC_I2C,

	/* 48 */
	PERIPH_ID_DSI,
	PERIPH_ID_TVO,
	PERIPH_ID_MIPI,
	PERIPH_ID_HDMI,
	PERIPH_ID_CSI,
	PERIPH_ID_TVDAC,
	PERIPH_ID_I2C2,
	PERIPH_ID_UART3,

	/* 56 */
	PERIPH_ID_RESERVED56,
	PERIPH_ID_EMC,
	PERIPH_ID_USB2,
	PERIPH_ID_USB3,
	PERIPH_ID_MPE,
	PERIPH_ID_VDE,
	PERIPH_ID_BSEA,
	PERIPH_ID_BSEV,

	/* Upper word 95:64 */
	PERIPH_ID_SPEEDO,
	PERIPH_ID_UART4,
	PERIPH_ID_UART5,
	PERIPH_ID_I2C3,
	PERIPH_ID_SBC4,
	PERIPH_ID_SDMMC3,
	PERIPH_ID_PCIE,
	PERIPH_ID_OWR,

	/* 72 */
	PERIPH_ID_AFI,
	PERIPH_ID_CORESIGHT,
	PERIPH_ID_RESERVED74,
	PERIPH_ID_AVPUCQ,
	PERIPH_ID_RESERVED76,
	PERIPH_ID_RESERVED77,
	PERIPH_ID_RESERVED78,
	PERIPH_ID_RESERVED79,

	/* 80 */
	PERIPH_ID_RESERVED80,
	PERIPH_ID_RESERVED81,
	PERIPH_ID_RESERVED82,
	PERIPH_ID_RESERVED83,
	PERIPH_ID_IRAMA,
	PERIPH_ID_IRAMB,
	PERIPH_ID_IRAMC,
	PERIPH_ID_IRAMD,

	/* 88 */
	PERIPH_ID_CRAM2,
	PERIPH_ID_SYNC_CLK_DOUBLER,
	PERIPH_ID_CLK_M_DOUBLER,
	PERIPH_ID_RESERVED91,
	PERIPH_ID_SUS_OUT,
	PERIPH_ID_DEV2_OUT,
	PERIPH_ID_DEV1_OUT,

	PERIPH_ID_COUNT,
	PERIPH_ID_NONE = -1,
};

enum pll_out_id {
	PLL_OUT1,
	PLL_OUT2,
	PLL_OUT3,
	PLL_OUT4
};

/* Converts a clock number to a clock register: 0=L, 1=H, 2=U */
#define PERIPH_REG(id) ((id) >> 5)

/* Mask value for a clock (within PERIPH_REG(id)) */
#define PERIPH_MASK(id) (1 << ((id) & 0x1f))

/* return 1 if a PLL ID is in range, and not a simple PLL */
#define clock_id_is_pll(id) ((id) >= CLOCK_ID_FIRST && \
		(id) < CLOCK_ID_FIRST_SIMPLE)

/* return 1 if a peripheral ID is in range */
#define clock_periph_id_isvalid(id) ((id) >= PERIPH_ID_FIRST && \
		(id) < PERIPH_ID_COUNT)

#endif	/* _CLOCK_TABLES_H_ */
