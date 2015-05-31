/*
 * (C) Copyright 2012-2013 Henrik Nordstrom <henrik@henriknordstrom.net>
 *
 * Configuration settings for the Allwinner A10 (sun4i) CPU
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * A10 specific configuration
 */

#ifdef CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_SUNXI
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#endif

#define CONFIG_SUNXI_USB_PHYS	3
#define CONFIG_NAND_SUNXI_GPC_PORTS	{16, 17, 18, 19, 20, 21, 22, 24}

/*
 * Include common sunxi configuration where most the settings are
 */
#include <configs/sunxi-common.h>

#define CONFIG_MACH_TYPE	(4104 | ((CONFIG_MACH_TYPE_COMPAT_REV) << 28))

#endif /* __CONFIG_H */
