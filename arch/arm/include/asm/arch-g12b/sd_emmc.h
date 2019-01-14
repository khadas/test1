/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * (C) Copyright 2016 Carlo Caione <carlo@caione.org>
 */

#ifndef __SD_EMMC_H__
#define __SD_EMMC_H__

#include <mmc.h>

#define SDIO_PORT_A			0
#define SDIO_PORT_B			1
#define SDIO_PORT_C			2

#define SD_EMMC_CLKSRC_24M		24000000	/* 24 MHz */
#define SD_EMMC_CLKSRC_DIV2		1000000000	/* 1 GHz */


#define MESON_SD_EMMC_CLOCK		0x00
#define CLK_MAX_DIV   63
#define	Cfg_div 	0
#define Cfg_src		6
#define Cfg_co_phase	8
#define	Cfg_tx_phase	10
#define	Cfg_rx_phase	12
#define	Cfg_sram_pd		14
#define	Cfg_tx_delay	16
#define	Cfg_rx_delay	22
#define	Cfg_always_on	28
#define	Cfg_irq_sdio_sleep   29
#define Cfg_irq_sdio_sleep_ds		30

#define MESON_SD_EMMC_CFG		0x44
#define   CFG_BUS_WIDTH_MASK		GENMASK(1, 0)
#define   CFG_BUS_WIDTH_1		0
#define   CFG_BUS_WIDTH_4		1
#define   CFG_BUS_WIDTH_8		2
#define   CFG_BL_LEN_MASK		GENMASK(7, 4)
#define   CFG_BL_LEN_SHIFT		4
#define   CFG_BL_LEN_512		(9 << 4)
#define   CFG_RESP_TIMEOUT_MASK		GENMASK(11, 8)
#define   CFG_RESP_TIMEOUT_256		(8 << 8)
#define   CFG_RC_CC_MASK		GENMASK(15, 12)
#define   CFG_RC_CC_16			(4 << 12)
#define   CFG_SDCLK_ALWAYS_ON		BIT(18)
#define   CFG_AUTO_CLK			BIT(23)

#define MESON_SD_EMMC_STATUS		0x48
#define   STATUS_MASK			GENMASK(15, 0)
#define   STATUS_ERR_MASK		GENMASK(12, 0)
#define   STATUS_RXD_ERR_MASK		GENMASK(7, 0)
#define   STATUS_TXD_ERR		BIT(8)
#define   STATUS_DESC_ERR		BIT(9)
#define   STATUS_RESP_ERR		BIT(10)
#define   STATUS_RESP_TIMEOUT		BIT(11)
#define   STATUS_DESC_TIMEOUT		BIT(12)
#define   STATUS_END_OF_CHAIN		BIT(13)

#define MESON_SD_EMMC_IRQ_EN		0x4c

#define MESON_SD_EMMC_CMD_CFG		0x50
#define   CMD_CFG_LENGTH_MASK		GENMASK(8, 0)
#define   CMD_CFG_BLOCK_MODE		BIT(9)
#define   CMD_CFG_R1B			BIT(10)
#define   CMD_CFG_END_OF_CHAIN		BIT(11)
#define   CMD_CFG_TIMEOUT_4S		(12 << 12)
#define   CMD_CFG_NO_RESP		BIT(16)
#define   CMD_CFG_DATA_IO		BIT(18)
#define   CMD_CFG_DATA_WR		BIT(19)
#define   CMD_CFG_RESP_NOCRC		BIT(20)
#define   CMD_CFG_RESP_128		BIT(21)
#define   CMD_CFG_CMD_INDEX_SHIFT	24
#define   CMD_CFG_OWNER			BIT(31)

#define MESON_SD_EMMC_CMD_ARG		0x54
#define MESON_SD_EMMC_CMD_DAT		0x58
#define MESON_SD_EMMC_CMD_RSP		0x5c
#define MESON_SD_EMMC_CMD_RSP1		0x60
#define MESON_SD_EMMC_CMD_RSP2		0x64
#define MESON_SD_EMMC_CMD_RSP3		0x68

#define SD_EMMC_RXD_ERROR               (1 << 0)
#define SD_EMMC_TXD_ERROR               (1 << 1)
#define SD_EMMC_DESC_ERROR              (1 << 2)
#define SD_EMMC_RESP_CRC_ERROR          (1 << 3)
#define SD_EMMC_RESP_TIMEOUT_ERROR      (1 << 4)
#define SD_EMMC_DESC_TIMEOUT_ERROR      (1 << 5)

struct meson_mmc_platdata {
	struct mmc_config cfg;
	struct mmc mmc;
	void *regbase;
	void *w_buf;
};

#endif
