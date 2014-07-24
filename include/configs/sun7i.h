/*
 * (C) Copyright 2012-2013 Henrik Nordstrom <henrik@henriknordstrom.net>
 * (C) Copyright 2013 Luke Kenneth Casson Leighton <lkcl@lkcl.net>
 *
 * Configuration settings for the Allwinner A20 (sun7i) CPU
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * A20 specific configuration
 */
#define CONFIG_SUN7I		/* sun7i SoC generation */
#define CONFIG_CLK_FULL_SPEED		912000000

#define CONFIG_SYS_PROMPT		"sun7i# "

#ifdef CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_SUNXI

#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#ifndef CONFIG_SUNXI_USB_VBUS0_GPIO
#define CONFIG_SUNXI_USB_VBUS0_GPIO	SUNXI_GPH(6)
#endif
#ifndef CONFIG_SUNXI_USB_VBUS1_GPIO
#define CONFIG_SUNXI_USB_VBUS1_GPIO	SUNXI_GPH(3)
#endif
#endif

/*
 * Include common sunxi configuration where most the settings are
 */
#include <configs/sunxi-common.h>

#endif /* __CONFIG_H */
