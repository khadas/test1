/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __IOMUX_VF610_H__
#define __IOMUX_VF610_H__

#include <asm/imx-common/iomux-v3.h>

/* Pad control groupings */
#define VF610_UART_PAD_CTRL	(PAD_CTL_PUS_100K_UP | PAD_CTL_DSE_25ohm | \
				PAD_CTL_OBE_IBE_ENABLE)
#define VF610_SDHC_PAD_CTRL	(PAD_CTL_PUS_100K_UP | PAD_CTL_DSE_20ohm | \
				PAD_CTL_OBE_IBE_ENABLE)
#define VF610_ENET_PAD_CTRL	(PAD_CTL_PUS_47K_UP | PAD_CTL_DSE_50ohm | \
				PAD_CTL_OBE_IBE_ENABLE)
#define VF610_DDR_PAD_CTRL	PAD_CTL_DSE_25ohm
#define VF610_I2C_PAD_CTRL	(PAD_CTL_PUS_47K_UP | PAD_CTL_DSE_50ohm | \
				PAD_CTL_SPEED_HIGH | PAD_CTL_OBE_IBE_ENABLE)

enum {
	VF610_PAD_PTA6__RMII0_CLKIN		= IOMUX_PAD(0x0000, 0x0000, 2, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTA6__RMII0_CLKOUT		= IOMUX_PAD(0x0000, 0x0000, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTB4__UART1_TX		= IOMUX_PAD(0x0068, 0x0068, 2, 0x0380, 0, VF610_UART_PAD_CTRL),
	VF610_PAD_PTB5__UART1_RX		= IOMUX_PAD(0x006c, 0x006c, 2, 0x037c, 0, VF610_UART_PAD_CTRL),
	VF610_PAD_PTB10__UART0_TX		= IOMUX_PAD(0x0080, 0x0080, 1, __NA_, 0, VF610_UART_PAD_CTRL),
	VF610_PAD_PTB11__UART0_RX		= IOMUX_PAD(0x0084, 0x0084, 1, __NA_, 0, VF610_UART_PAD_CTRL),
	VF610_PAD_PTC1__RMII0_MDIO		= IOMUX_PAD(0x00b8, 0x00b8, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC0__RMII0_MDC		= IOMUX_PAD(0x00b4, 0x00b4, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC2__RMII0_CRS_DV		= IOMUX_PAD(0x00bc, 0x00bc, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC3__RMII0_RD1		= IOMUX_PAD(0x00c0, 0x00c0, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC4__RMII0_RD0		= IOMUX_PAD(0x00c4, 0x00c4, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC5__RMII0_RXER		= IOMUX_PAD(0x00c8, 0x00c8, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC6__RMII0_TD1		= IOMUX_PAD(0x00cc, 0x00cc, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC7__RMII0_TD0		= IOMUX_PAD(0x00D0, 0x00D0, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC8__RMII0_TXEN		= IOMUX_PAD(0x00D4, 0x00D4, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC10__RMII1_MDIO		= IOMUX_PAD(0x00dc, 0x00dc, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC9__RMII1_MDC		= IOMUX_PAD(0x00d8, 0x00d8, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC11__RMII1_CRS_DV		= IOMUX_PAD(0x00e0, 0x00e0, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC12__RMII1_RD1		= IOMUX_PAD(0x00e4, 0x00e4, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC13__RMII1_RD0		= IOMUX_PAD(0x00e8, 0x00e8, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC14__RMII1_RXER		= IOMUX_PAD(0x00ec, 0x00ec, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC15__RMII1_TD1		= IOMUX_PAD(0x00f0, 0x00f0, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC16__RMII1_TD0		= IOMUX_PAD(0x00f4, 0x00f4, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTC17__RMII1_TXEN		= IOMUX_PAD(0x00f8, 0x00f8, 1, __NA_, 0, VF610_ENET_PAD_CTRL),
	VF610_PAD_PTA24__ESDHC1_CLK		= IOMUX_PAD(0x0038, 0x0038, 5, __NA_, 0, VF610_SDHC_PAD_CTRL),
	VF610_PAD_PTA25__ESDHC1_CMD		= IOMUX_PAD(0x003c, 0x003c, 5, __NA_, 0, VF610_SDHC_PAD_CTRL),
	VF610_PAD_PTA26__ESDHC1_DAT0		= IOMUX_PAD(0x0040, 0x0040, 5, __NA_, 0, VF610_SDHC_PAD_CTRL),
	VF610_PAD_PTA27__ESDHC1_DAT1		= IOMUX_PAD(0x0044, 0x0044, 5, __NA_, 0, VF610_SDHC_PAD_CTRL),
	VF610_PAD_PTA28__ESDHC1_DAT2		= IOMUX_PAD(0x0048, 0x0048, 5, __NA_, 0, VF610_SDHC_PAD_CTRL),
	VF610_PAD_PTA29__ESDHC1_DAT3		= IOMUX_PAD(0x004c, 0x004c, 5, __NA_, 0, VF610_SDHC_PAD_CTRL),
	VF610_PAD_PTB14__I2C0_SCL		= IOMUX_PAD(0x0090, 0x0090, 2, 0x033c, 1, VF610_I2C_PAD_CTRL),
	VF610_PAD_PTB15__I2C0_SDA		= IOMUX_PAD(0x0094, 0x0094, 2, 0x0340, 1, VF610_I2C_PAD_CTRL),
	VF610_PAD_DDR_A15__DDR_A_15		= IOMUX_PAD(0x0220, 0x0220, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A14__DDR_A_14		= IOMUX_PAD(0x0224, 0x0224, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A13__DDR_A_13		= IOMUX_PAD(0x0228, 0x0228, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A12__DDR_A_12		= IOMUX_PAD(0x022c, 0x022c, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A11__DDR_A_11		= IOMUX_PAD(0x0230, 0x0230, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A10__DDR_A_10		= IOMUX_PAD(0x0234, 0x0234, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A9__DDR_A_9		= IOMUX_PAD(0x0238, 0x0238, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A8__DDR_A_8		= IOMUX_PAD(0x023c, 0x023c, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A7__DDR_A_7		= IOMUX_PAD(0x0240, 0x0240, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A6__DDR_A_6		= IOMUX_PAD(0x0244, 0x0244, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A5__DDR_A_5		= IOMUX_PAD(0x0248, 0x0248, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A4__DDR_A_4		= IOMUX_PAD(0x024c, 0x024c, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A3__DDR_A_3		= IOMUX_PAD(0x0250, 0x0250, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A2__DDR_A_2		= IOMUX_PAD(0x0254, 0x0254, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_A1__DDR_A_1		= IOMUX_PAD(0x0258, 0x0258, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_BA2__DDR_BA_2		= IOMUX_PAD(0x0260, 0x0260, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_BA1__DDR_BA_1		= IOMUX_PAD(0x0264, 0x0264, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_BA0__DDR_BA_0		= IOMUX_PAD(0x0268, 0x0268, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_CAS__DDR_CAS_B		= IOMUX_PAD(0x026c, 0x026c, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_CKE__DDR_CKE_0		= IOMUX_PAD(0x0270, 0x0270, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_CLK__DDR_CLK_0		= IOMUX_PAD(0x0274, 0x0274, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_CS__DDR_CS_B_0		= IOMUX_PAD(0x0278, 0x0278, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D15__DDR_D_15		= IOMUX_PAD(0x027c, 0x027c, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D14__DDR_D_14		= IOMUX_PAD(0x0280, 0x0280, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D13__DDR_D_13		= IOMUX_PAD(0x0284, 0x0284, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D12__DDR_D_12		= IOMUX_PAD(0x0288, 0x0288, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D11__DDR_D_11		= IOMUX_PAD(0x028c, 0x028c, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D10__DDR_D_10		= IOMUX_PAD(0x0290, 0x0290, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D9__DDR_D_9		= IOMUX_PAD(0x0294, 0x0294, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D8__DDR_D_8		= IOMUX_PAD(0x0298, 0x0298, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D7__DDR_D_7		= IOMUX_PAD(0x029c, 0x029c, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D6__DDR_D_6		= IOMUX_PAD(0x02a0, 0x02a0, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D5__DDR_D_5		= IOMUX_PAD(0x02a4, 0x02a4, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D4__DDR_D_4		= IOMUX_PAD(0x02a8, 0x02a8, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D3__DDR_D_3		= IOMUX_PAD(0x02ac, 0x02ac, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D2__DDR_D_2		= IOMUX_PAD(0x02b0, 0x02b0, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D1__DDR_D_1		= IOMUX_PAD(0x02b4, 0x02b4, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_D0__DDR_D_0		= IOMUX_PAD(0x02b8, 0x02b8, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_DQM1__DDR_DQM_1		= IOMUX_PAD(0x02bc, 0x02bc, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_DQM0__DDR_DQM_0		= IOMUX_PAD(0x02c0, 0x02c0, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_DQS1__DDR_DQS_1		= IOMUX_PAD(0x02c4, 0x02c4, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_DQS0__DDR_DQS_0		= IOMUX_PAD(0x02c8, 0x02c8, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_RAS__DDR_RAS_B		= IOMUX_PAD(0x02cc, 0x02cc, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_WE__DDR_WE_B		= IOMUX_PAD(0x02d0, 0x02d0, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_ODT1__DDR_ODT_0		= IOMUX_PAD(0x02d4, 0x02d4, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
	VF610_PAD_DDR_ODT0__DDR_ODT_1		= IOMUX_PAD(0x02d8, 0x02d8, 0, __NA_, 0, VF610_DDR_PAD_CTRL),
};

#endif	/* __IOMUX_VF610_H__ */
