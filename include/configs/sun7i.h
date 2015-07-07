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

#ifdef CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_SUNXI
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#endif

#define CONFIG_SUNXI_USB_PHYS	3

#define CONFIG_ARMV7_PSCI		1
#define CONFIG_ARMV7_SECURE_BASE	SUNXI_SRAM_B_BASE
#define CONFIG_TIMER_CLK_FREQ		24000000

/*
 * Include common sunxi configuration where most the settings are
 */
#include <configs/sunxi-common.h>

#define CONFIG_MACH_TYPE	(4283 | ((CONFIG_MACH_TYPE_COMPAT_REV) << 28))

#endif /* __CONFIG_H */
