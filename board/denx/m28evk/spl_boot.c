/*
 * DENX M28 Boot setup
 *
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 *
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <config.h>
#include <asm/io.h>
#include <asm/arch/iomux-mx28.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/sys_proto.h>

#define	MUX_CONFIG_LED	(MXS_PAD_3V3 | MXS_PAD_4MA | MXS_PAD_NOPULL)
#define	MUX_CONFIG_LCD	(MXS_PAD_3V3 | MXS_PAD_4MA | MXS_PAD_NOPULL)
#define	MUX_CONFIG_TSC	(MXS_PAD_3V3 | MXS_PAD_8MA | MXS_PAD_PULLUP)
#define	MUX_CONFIG_SSP0	(MXS_PAD_3V3 | MXS_PAD_12MA | MXS_PAD_PULLUP)
#define	MUX_CONFIG_SSP2	(MXS_PAD_3V3 | MXS_PAD_4MA | MXS_PAD_PULLUP)
#define	MUX_CONFIG_GPMI	(MXS_PAD_1V8 | MXS_PAD_4MA | MXS_PAD_NOPULL)
#define	MUX_CONFIG_ENET	(MXS_PAD_3V3 | MXS_PAD_4MA | MXS_PAD_PULLUP)
#define	MUX_CONFIG_EMI	(MXS_PAD_3V3 | MXS_PAD_12MA | MXS_PAD_NOPULL)

const iomux_cfg_t iomux_setup[] = {
	/* LED */
	MX28_PAD_ENET0_RXD3__GPIO_4_10 | MUX_CONFIG_LED,

	/* framebuffer */
	MX28_PAD_LCD_D00__LCD_D0 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D01__LCD_D1 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D02__LCD_D2 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D03__LCD_D3 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D04__LCD_D4 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D05__LCD_D5 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D06__LCD_D6 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D07__LCD_D7 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D08__LCD_D8 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D09__LCD_D9 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D10__LCD_D10 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D11__LCD_D11 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D12__LCD_D12 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D13__LCD_D13 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D14__LCD_D14 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D15__LCD_D15 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D16__LCD_D16 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D17__LCD_D17 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D18__LCD_D18 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D19__LCD_D19 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D20__LCD_D20 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D21__LCD_D21 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D22__LCD_D22 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_D23__LCD_D23 | MUX_CONFIG_LCD,
	MX28_PAD_LCD_DOTCLK__LCD_DOTCLK | MUX_CONFIG_LCD,
	MX28_PAD_LCD_ENABLE__LCD_ENABLE | MUX_CONFIG_LCD,

	/* UART1 */
	MX28_PAD_PWM0__DUART_RX,
	MX28_PAD_PWM1__DUART_TX,
	MX28_PAD_AUART0_TX__DUART_RTS,
	MX28_PAD_AUART0_RX__DUART_CTS,

	/* UART2 */
	MX28_PAD_AUART1_RX__AUART1_RX,
	MX28_PAD_AUART1_TX__AUART1_TX,
	MX28_PAD_AUART1_RTS__AUART1_RTS,
	MX28_PAD_AUART1_CTS__AUART1_CTS,

	/* CAN */
	MX28_PAD_GPMI_RDY2__CAN0_TX,
	MX28_PAD_GPMI_RDY3__CAN0_RX,

	/* TSC2007 */
	MX28_PAD_SAIF0_MCLK__GPIO_3_20 | MUX_CONFIG_TSC,

	/* MMC0 */
	MX28_PAD_SSP0_DATA0__SSP0_D0 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA1__SSP0_D1 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA2__SSP0_D2 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA3__SSP0_D3 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA4__SSP0_D4 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA5__SSP0_D5 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA6__SSP0_D6 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DATA7__SSP0_D7 | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_CMD__SSP0_CMD | MUX_CONFIG_SSP0,
	MX28_PAD_SSP0_DETECT__SSP0_CARD_DETECT |
		(MXS_PAD_3V3 | MXS_PAD_12MA | MXS_PAD_NOPULL),
	MX28_PAD_SSP0_SCK__SSP0_SCK |
		(MXS_PAD_3V3 | MXS_PAD_12MA | MXS_PAD_NOPULL),
	MX28_PAD_PWM3__GPIO_3_28 | MUX_CONFIG_SSP0,	/* Power .. FIXME */
	MX28_PAD_AUART2_CTS__GPIO_3_10,	/* WP ... FIXME */

	/* GPMI NAND */
	MX28_PAD_GPMI_D00__GPMI_D0 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D01__GPMI_D1 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D02__GPMI_D2 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D03__GPMI_D3 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D04__GPMI_D4 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D05__GPMI_D5 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D06__GPMI_D6 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_D07__GPMI_D7 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_CE0N__GPMI_CE0N | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_RDY0__GPMI_READY0 | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_RDN__GPMI_RDN |
		(MXS_PAD_1V8 | MXS_PAD_8MA | MXS_PAD_PULLUP),
	MX28_PAD_GPMI_WRN__GPMI_WRN | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_ALE__GPMI_ALE | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_CLE__GPMI_CLE | MUX_CONFIG_GPMI,
	MX28_PAD_GPMI_RESETN__GPMI_RESETN | MUX_CONFIG_GPMI,

	/* FEC Ethernet */
	MX28_PAD_ENET0_MDC__ENET0_MDC | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_MDIO__ENET0_MDIO | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RX_EN__ENET0_RX_EN | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TX_EN__ENET0_TX_EN | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RXD0__ENET0_RXD0 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RXD1__ENET0_RXD1 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TXD0__ENET0_TXD0 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TXD1__ENET0_TXD1 | MUX_CONFIG_ENET,
	MX28_PAD_ENET_CLK__CLKCTRL_ENET | MUX_CONFIG_ENET,

	MX28_PAD_ENET0_COL__ENET1_TX_EN | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_CRS__ENET1_RX_EN | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RXD2__ENET1_RXD0 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_RXD3__ENET1_RXD1 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TXD2__ENET1_TXD0 | MUX_CONFIG_ENET,
	MX28_PAD_ENET0_TXD3__ENET1_TXD1 | MUX_CONFIG_ENET,

	/* I2C */
	MX28_PAD_I2C0_SCL__I2C0_SCL,
	MX28_PAD_I2C0_SDA__I2C0_SDA,

	/* EMI */
	MX28_PAD_EMI_D00__EMI_DATA0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D01__EMI_DATA1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D02__EMI_DATA2 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D03__EMI_DATA3 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D04__EMI_DATA4 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D05__EMI_DATA5 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D06__EMI_DATA6 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D07__EMI_DATA7 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D08__EMI_DATA8 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D09__EMI_DATA9 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D10__EMI_DATA10 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D11__EMI_DATA11 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D12__EMI_DATA12 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D13__EMI_DATA13 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D14__EMI_DATA14 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_D15__EMI_DATA15 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_ODT0__EMI_ODT0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQM0__EMI_DQM0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_ODT1__EMI_ODT1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQM1__EMI_DQM1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DDR_OPEN_FB__EMI_DDR_OPEN_FEEDBACK | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CLK__EMI_CLK | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQS0__EMI_DQS0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DQS1__EMI_DQS1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_DDR_OPEN__EMI_DDR_OPEN | MUX_CONFIG_EMI,

	MX28_PAD_EMI_A00__EMI_ADDR0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A01__EMI_ADDR1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A02__EMI_ADDR2 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A03__EMI_ADDR3 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A04__EMI_ADDR4 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A05__EMI_ADDR5 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A06__EMI_ADDR6 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A07__EMI_ADDR7 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A08__EMI_ADDR8 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A09__EMI_ADDR9 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A10__EMI_ADDR10 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A11__EMI_ADDR11 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A12__EMI_ADDR12 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A13__EMI_ADDR13 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_A14__EMI_ADDR14 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_BA0__EMI_BA0 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_BA1__EMI_BA1 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_BA2__EMI_BA2 | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CASN__EMI_CASN | MUX_CONFIG_EMI,
	MX28_PAD_EMI_RASN__EMI_RASN | MUX_CONFIG_EMI,
	MX28_PAD_EMI_WEN__EMI_WEN | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CE0N__EMI_CE0N | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CE1N__EMI_CE1N | MUX_CONFIG_EMI,
	MX28_PAD_EMI_CKE__EMI_CKE | MUX_CONFIG_EMI,

	/* SPI2 (for flash) */
	MX28_PAD_SSP2_SCK__SSP2_SCK | MUX_CONFIG_SSP2,
	MX28_PAD_SSP2_MOSI__SSP2_CMD | MUX_CONFIG_SSP2,
	MX28_PAD_SSP2_MISO__SSP2_D0 | MUX_CONFIG_SSP2,
	MX28_PAD_SSP2_SS0__SSP2_D3 |
		(MXS_PAD_3V3 | MXS_PAD_8MA | MXS_PAD_PULLUP),
};

void board_init_ll(void)
{
	mx28_common_spl_init(iomux_setup, ARRAY_SIZE(iomux_setup));
}
