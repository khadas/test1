/*
 * Copyright (C) 2016 Google, Inc
 * Written by Simon Glass <sjg@chromium.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <syscon.h>
#include <asm/arch/clock.h>
#include <asm/arch/cru_rk3399.h>

static int rockchip_get_cruclk(struct udevice **devp)
{
	return uclass_get_device_by_driver(UCLASS_CLK,
			DM_GET_DRIVER(clk_rk3399), devp);
}

void *rockchip_get_cru(void)
{
	struct rk3399_clk_priv *priv;
	struct udevice *dev;
	int ret;

	ret = rockchip_get_cruclk(&dev);
	if (ret)
		return ERR_PTR(ret);

	priv = dev_get_priv(dev);

	return priv->cru;
}
