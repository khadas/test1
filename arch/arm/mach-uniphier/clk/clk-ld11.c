/*
 * Copyright (C) 2016 Socionext Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <spl.h>
#include <linux/bitops.h>
#include <linux/io.h>

#include "../init.h"
#include "../sc64-regs.h"
#include "../sg-regs.h"

#define SDCTRL_EMMC_HW_RESET	0x59810280

void uniphier_ld11_clk_init(void)
{
	/* if booted from a device other than USB, without stand-by MPU */
	if ((readl(SG_PINMON0) & BIT(27)) &&
	    uniphier_boot_device_raw() != BOOT_DEVICE_USB) {
		writel(1, SG_ETPHYPSHUT);
		writel(1, SG_ETPHYCNT);

		udelay(1); /* wait for regulator level 1.1V -> 2.5V */

		writel(3, SG_ETPHYCNT);
		writel(3, SG_ETPHYPSHUT);
		writel(7, SG_ETPHYCNT);
	}

	/* TODO: use "mmc-pwrseq-emmc" */
	writel(1, SDCTRL_EMMC_HW_RESET);

#ifdef CONFIG_USB_EHCI
	{
		/* FIXME: the current clk driver can not handle parents */
		u32 tmp;
		tmp = readl(SC_CLKCTRL4);
		tmp |= SC_CLKCTRL4_MIO | SC_CLKCTRL4_STDMAC;
		writel(tmp, SC_CLKCTRL4);
	}
#endif
}
