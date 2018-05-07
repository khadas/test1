// SPDX-License-Identifier: GPL-2.0
/*
 * Allwinner SUNXI "glue layer"
 *
 * Copyright © 2015 Hans de Goede <hdegoede@redhat.com>
 * Copyright © 2013 Jussi Kivilinna <jussi.kivilinna@iki.fi>
 *
 * Based on the sw_usb "Allwinner OTG Dual Role Controller" code.
 *  Copyright 2007-2012 (C) Allwinner Technology Co., Ltd.
 *  javen <javen@allwinnertech.com>
 *
 * Based on the DA8xx "glue layer" code.
 *  Copyright (c) 2008-2009 MontaVista Software, Inc. <source@mvista.com>
 *  Copyright (C) 2005-2006 by Texas Instruments
 *
 * This file is part of the Inventra Controller Driver for Linux.
 */
#include <common.h>
#include <dm.h>
#include <asm/arch/cpu.h>
#include <asm/arch/clock.h>
#include <asm/arch/gpio.h>
#include <asm/arch/usb_phy.h>
#include <asm-generic/gpio.h>
#include <dm/lists.h>
#include <dm/root.h>
#include <linux/usb/musb.h>
#include "linux-compat.h"
#include "musb_core.h"
#include "musb_uboot.h"

/******************************************************************************
 ******************************************************************************
 * From the Allwinner driver
 ******************************************************************************
 ******************************************************************************/

/******************************************************************************
 * From include/sunxi_usb_bsp.h
 ******************************************************************************/

/* reg offsets */
#define  USBC_REG_o_ISCR	0x0400
#define  USBC_REG_o_PHYCTL	0x0404
#define  USBC_REG_o_PHYBIST	0x0408
#define  USBC_REG_o_PHYTUNE	0x040c

#define  USBC_REG_o_VEND0	0x0043

/* Interface Status and Control */
#define  USBC_BP_ISCR_VBUS_VALID_FROM_DATA	30
#define  USBC_BP_ISCR_VBUS_VALID_FROM_VBUS	29
#define  USBC_BP_ISCR_EXT_ID_STATUS		28
#define  USBC_BP_ISCR_EXT_DM_STATUS		27
#define  USBC_BP_ISCR_EXT_DP_STATUS		26
#define  USBC_BP_ISCR_MERGED_VBUS_STATUS	25
#define  USBC_BP_ISCR_MERGED_ID_STATUS		24

#define  USBC_BP_ISCR_ID_PULLUP_EN		17
#define  USBC_BP_ISCR_DPDM_PULLUP_EN		16
#define  USBC_BP_ISCR_FORCE_ID			14
#define  USBC_BP_ISCR_FORCE_VBUS_VALID		12
#define  USBC_BP_ISCR_VBUS_VALID_SRC		10

#define  USBC_BP_ISCR_HOSC_EN			7
#define  USBC_BP_ISCR_VBUS_CHANGE_DETECT	6
#define  USBC_BP_ISCR_ID_CHANGE_DETECT		5
#define  USBC_BP_ISCR_DPDM_CHANGE_DETECT	4
#define  USBC_BP_ISCR_IRQ_ENABLE		3
#define  USBC_BP_ISCR_VBUS_CHANGE_DETECT_EN	2
#define  USBC_BP_ISCR_ID_CHANGE_DETECT_EN	1
#define  USBC_BP_ISCR_DPDM_CHANGE_DETECT_EN	0

/******************************************************************************
 * From usbc/usbc.c
 ******************************************************************************/

struct sunxi_musb_config {
	struct musb_hdrc_config *config;
	u8 rst_bit;
	u8 clkgate_bit;
};

struct sunxi_glue {
	struct musb_host_data mdata;
	struct sunxi_ccm_reg *ccm;
	struct sunxi_musb_config *cfg;
	struct device dev;
};
#define to_sunxi_glue(d)	container_of(d, struct sunxi_glue, dev)

static u32 USBC_WakeUp_ClearChangeDetect(u32 reg_val)
{
	u32 temp = reg_val;

	temp &= ~(1 << USBC_BP_ISCR_VBUS_CHANGE_DETECT);
	temp &= ~(1 << USBC_BP_ISCR_ID_CHANGE_DETECT);
	temp &= ~(1 << USBC_BP_ISCR_DPDM_CHANGE_DETECT);

	return temp;
}

static void USBC_EnableIdPullUp(__iomem void *base)
{
	u32 reg_val;

	reg_val = musb_readl(base, USBC_REG_o_ISCR);
	reg_val |= (1 << USBC_BP_ISCR_ID_PULLUP_EN);
	reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
	musb_writel(base, USBC_REG_o_ISCR, reg_val);
}

static void USBC_EnableDpDmPullUp(__iomem void *base)
{
	u32 reg_val;

	reg_val = musb_readl(base, USBC_REG_o_ISCR);
	reg_val |= (1 << USBC_BP_ISCR_DPDM_PULLUP_EN);
	reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
	musb_writel(base, USBC_REG_o_ISCR, reg_val);
}

static void USBC_ForceIdToLow(__iomem void *base)
{
	u32 reg_val;

	reg_val = musb_readl(base, USBC_REG_o_ISCR);
	reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_ID);
	reg_val |= (0x02 << USBC_BP_ISCR_FORCE_ID);
	reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
	musb_writel(base, USBC_REG_o_ISCR, reg_val);
}

static void USBC_ForceIdToHigh(__iomem void *base)
{
	u32 reg_val;

	reg_val = musb_readl(base, USBC_REG_o_ISCR);
	reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_ID);
	reg_val |= (0x03 << USBC_BP_ISCR_FORCE_ID);
	reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
	musb_writel(base, USBC_REG_o_ISCR, reg_val);
}

static void USBC_ForceVbusValidToLow(__iomem void *base)
{
	u32 reg_val;

	reg_val = musb_readl(base, USBC_REG_o_ISCR);
	reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_VBUS_VALID);
	reg_val |= (0x02 << USBC_BP_ISCR_FORCE_VBUS_VALID);
	reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
	musb_writel(base, USBC_REG_o_ISCR, reg_val);
}

static void USBC_ForceVbusValidToHigh(__iomem void *base)
{
	u32 reg_val;

	reg_val = musb_readl(base, USBC_REG_o_ISCR);
	reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_VBUS_VALID);
	reg_val |= (0x03 << USBC_BP_ISCR_FORCE_VBUS_VALID);
	reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
	musb_writel(base, USBC_REG_o_ISCR, reg_val);
}

static void USBC_ConfigFIFO_Base(void)
{
	u32 reg_value;

	/* config usb fifo, 8kb mode */
	reg_value = readl(SUNXI_SRAMC_BASE + 0x04);
	reg_value &= ~(0x03 << 0);
	reg_value |= (1 << 0);
	writel(reg_value, SUNXI_SRAMC_BASE + 0x04);
}

/******************************************************************************
 * Needed for the DFU polling magic
 ******************************************************************************/

static u8 last_int_usb;

bool dfu_usb_get_reset(void)
{
	return !!(last_int_usb & MUSB_INTR_RESET);
}

/******************************************************************************
 * MUSB Glue code
 ******************************************************************************/

static irqreturn_t sunxi_musb_interrupt(int irq, void *__hci)
{
	struct musb		*musb = __hci;
	irqreturn_t		retval = IRQ_NONE;

	/* read and flush interrupts */
	musb->int_usb = musb_readb(musb->mregs, MUSB_INTRUSB);
	last_int_usb = musb->int_usb;
	if (musb->int_usb)
		musb_writeb(musb->mregs, MUSB_INTRUSB, musb->int_usb);
	musb->int_tx = musb_readw(musb->mregs, MUSB_INTRTX);
	if (musb->int_tx)
		musb_writew(musb->mregs, MUSB_INTRTX, musb->int_tx);
	musb->int_rx = musb_readw(musb->mregs, MUSB_INTRRX);
	if (musb->int_rx)
		musb_writew(musb->mregs, MUSB_INTRRX, musb->int_rx);

	if (musb->int_usb || musb->int_tx || musb->int_rx)
		retval |= musb_interrupt(musb);

	return retval;
}

/* musb_core does not call enable / disable in a balanced manner <sigh> */
static bool enabled = false;

static int sunxi_musb_enable(struct musb *musb)
{
	int ret;

	pr_debug("%s():\n", __func__);

	musb_ep_select(musb->mregs, 0);
	musb_writeb(musb->mregs, MUSB_FADDR, 0);

	if (enabled)
		return 0;

	/* select PIO mode */
	musb_writeb(musb->mregs, USBC_REG_o_VEND0, 0);

	if (is_host_enabled(musb)) {
		ret = sunxi_usb_phy_vbus_detect(0);
		if (ret == 1) {
			printf("A charger is plugged into the OTG: ");
			return -ENODEV;
		}
		ret = sunxi_usb_phy_id_detect(0);
		if (ret == 1) {
			printf("No host cable detected: ");
			return -ENODEV;
		}
		sunxi_usb_phy_power_on(0); /* port power on */
	}

	USBC_ForceVbusValidToHigh(musb->mregs);

	enabled = true;
	return 0;
}

static void sunxi_musb_disable(struct musb *musb)
{
	pr_debug("%s():\n", __func__);

	if (!enabled)
		return;

	if (is_host_enabled(musb))
		sunxi_usb_phy_power_off(0); /* port power off */

	USBC_ForceVbusValidToLow(musb->mregs);
	mdelay(200); /* Wait for the current session to timeout */

	enabled = false;
}

static int sunxi_musb_init(struct musb *musb)
{
	struct sunxi_glue *glue = to_sunxi_glue(musb->controller);

	pr_debug("%s():\n", __func__);

	musb->isr = sunxi_musb_interrupt;

	setbits_le32(&glue->ccm->ahb_gate0, 1 << AHB_GATE_OFFSET_USB0);
	if (glue->cfg->clkgate_bit)
		setbits_le32(&glue->ccm->ahb_gate0,
			     1 << glue->cfg->clkgate_bit);
#ifdef CONFIG_SUNXI_GEN_SUN6I
	setbits_le32(&glue->ccm->ahb_reset0_cfg, 1 << AHB_GATE_OFFSET_USB0);
	if (glue->cfg->rst_bit)
		setbits_le32(&glue->ccm->ahb_reset0_cfg,
			     1 << glue->cfg->rst_bit);
#endif

	sunxi_usb_phy_init(0);

	USBC_ConfigFIFO_Base();
	USBC_EnableDpDmPullUp(musb->mregs);
	USBC_EnableIdPullUp(musb->mregs);

	if (is_host_enabled(musb)) {
		/* Host mode */
		USBC_ForceIdToLow(musb->mregs);
	} else {
		/* Peripheral mode */
		USBC_ForceIdToHigh(musb->mregs);
	}
	USBC_ForceVbusValidToHigh(musb->mregs);

	return 0;
}

static const struct musb_platform_ops sunxi_musb_ops = {
	.init		= sunxi_musb_init,
	.enable		= sunxi_musb_enable,
	.disable	= sunxi_musb_disable,
};

/* Allwinner OTG supports up to 5 endpoints */
#define SUNXI_MUSB_MAX_EP_NUM		6
#define SUNXI_MUSB_RAM_BITS		11

static struct musb_fifo_cfg sunxi_musb_mode_cfg[] = {
	MUSB_EP_FIFO_SINGLE(1, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(1, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(5, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(5, FIFO_RX, 512),
};

/* H3/V3s OTG supports only 4 endpoints */
#define SUNXI_MUSB_MAX_EP_NUM_H3	5

static struct musb_fifo_cfg sunxi_musb_mode_cfg_h3[] = {
	MUSB_EP_FIFO_SINGLE(1, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(1, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(2, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(3, FIFO_RX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_TX, 512),
	MUSB_EP_FIFO_SINGLE(4, FIFO_RX, 512),
};

static struct musb_hdrc_config musb_config = {
	.fifo_cfg       = sunxi_musb_mode_cfg,
	.fifo_cfg_size  = ARRAY_SIZE(sunxi_musb_mode_cfg),
	.multipoint	= true,
	.dyn_fifo	= true,
	.num_eps	= SUNXI_MUSB_MAX_EP_NUM,
	.ram_bits	= SUNXI_MUSB_RAM_BITS,
};

static struct musb_hdrc_config musb_config_h3 = {
	.fifo_cfg       = sunxi_musb_mode_cfg_h3,
	.fifo_cfg_size  = ARRAY_SIZE(sunxi_musb_mode_cfg_h3),
	.multipoint	= true,
	.dyn_fifo	= true,
	.soft_con       = true,
	.num_eps	= SUNXI_MUSB_MAX_EP_NUM_H3,
	.ram_bits	= SUNXI_MUSB_RAM_BITS,
};

static int musb_usb_probe(struct udevice *dev)
{
	struct sunxi_glue *glue = dev_get_priv(dev);
	struct musb_host_data *host = &glue->mdata;
	struct usb_bus_priv *priv = dev_get_uclass_priv(dev);
	struct musb_hdrc_platform_data pdata;
	void *base = dev_read_addr_ptr(dev);
	int ret;

	if (!base)
		return -EINVAL;

	glue->cfg = (struct sunxi_musb_config *)dev_get_driver_data(dev);
	if (!glue->cfg)
		return -EINVAL;

	glue->ccm = (struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	if (IS_ERR(glue->ccm))
		return PTR_ERR(glue->ccm);

	priv->desc_before_addr = true;

	memset(&pdata, 0, sizeof(pdata));
	pdata.power = 250;
	pdata.platform_ops = &sunxi_musb_ops;
	pdata.config = glue->cfg->config;

#ifdef CONFIG_USB_MUSB_HOST
	pdata.mode = MUSB_HOST;
	host->host = musb_init_controller(&pdata, &glue->dev, base);
	if (!host->host)
		return -EIO;

	ret = musb_lowlevel_init(host);
	if (!ret)
		printf("Allwinner mUSB OTG (Host)\n");
#else
	pdata.mode = MUSB_PERIPHERAL;
	ret = musb_register(&pdata, &glue->dev, base);
	if (!ret)
		printf("Allwinner mUSB OTG (Peripheral)\n");
#endif

	return ret;
}

static int musb_usb_remove(struct udevice *dev)
{
	struct sunxi_glue *glue = dev_get_priv(dev);
	struct musb_host_data *host = &glue->mdata;

	musb_stop(host->host);

	sunxi_usb_phy_exit(0);
#ifdef CONFIG_SUNXI_GEN_SUN6I
	clrbits_le32(&glue->ccm->ahb_reset0_cfg, 1 << AHB_GATE_OFFSET_USB0);
	if (glue->cfg->rst_bit)
		clrbits_le32(&glue->ccm->ahb_reset0_cfg,
			     1 << glue->cfg->rst_bit);
#endif
	clrbits_le32(&glue->ccm->ahb_gate0, 1 << AHB_GATE_OFFSET_USB0);
	if (glue->cfg->clkgate_bit)
		clrbits_le32(&glue->ccm->ahb_gate0,
			     1 << glue->cfg->clkgate_bit);

	free(host->host);
	host->host = NULL;

	return 0;
}

static const struct sunxi_musb_config sun4i_a10_cfg = {
	.config = &musb_config,
};

static const struct sunxi_musb_config sun8i_h3_cfg = {
	.config = &musb_config_h3,
	.rst_bit = 23,
	.clkgate_bit = 23,
};

static const struct udevice_id sunxi_musb_ids[] = {
	{ .compatible = "allwinner,sun4i-a10-musb",
			.data = (ulong)&sun4i_a10_cfg },
	{ .compatible = "allwinner,sun6i-a31-musb",
			.data = (ulong)&sun4i_a10_cfg },
	{ .compatible = "allwinner,sun8i-a33-musb",
			.data = (ulong)&sun4i_a10_cfg },
	{ .compatible = "allwinner,sun8i-h3-musb",
			.data = (ulong)&sun8i_h3_cfg },
	{ }
};

U_BOOT_DRIVER(usb_musb) = {
	.name		= "sunxi-musb",
#ifdef CONFIG_USB_MUSB_HOST
	.id		= UCLASS_USB,
#else
	.id		= UCLASS_USB_DEV_GENERIC,
#endif
	.of_match	= sunxi_musb_ids,
	.probe		= musb_usb_probe,
	.remove		= musb_usb_remove,
#ifdef CONFIG_USB_MUSB_HOST
	.ops		= &musb_usb_ops,
#endif
	.platdata_auto_alloc_size = sizeof(struct usb_platdata),
	.priv_auto_alloc_size = sizeof(struct sunxi_glue),
};
