/*
 * Copyright (c) 2014-2016 Marcel Ziswiler
 *
 * Configuration settings for the Toradex Apalis T30 modules.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

#include "tegra30-common.h"

/* High-level configuration options */
#define CONFIG_DISPLAY_BOARDINFO_LATE	/* Calls show_board_info() */

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTA
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTA_BASE

#define CONFIG_MACH_TYPE		MACH_TYPE_APALIS_T30

/* I2C */
#define CONFIG_SYS_I2C_TEGRA

/* Environment in eMMC, before config block at the end of 1st "boot sector" */
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_OFFSET		(-CONFIG_ENV_SIZE + \
					 CONFIG_TDX_CFG_BLOCK_OFFSET)
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_SYS_MMC_ENV_PART		1

/* USB host support */
#define CONFIG_USB_EHCI_HCD
#define CONFIG_USB_EHCI_TEGRA

/* PCI host support */
#define CONFIG_CMD_PCI

/* PCI networking support */
#define CONFIG_E1000_NO_NVM

/* General networking support */
#define CONFIG_IP_DEFRAG
#define CONFIG_TFTP_BLOCKSIZE		16352
#define CONFIG_TFTP_TSIZE

/* Miscellaneous commands */
#define CONFIG_FAT_WRITE

/* Increase console I/O buffer size */
#undef CONFIG_SYS_CBSIZE
#define CONFIG_SYS_CBSIZE		1024

/* Increase arguments buffer size */
#undef CONFIG_SYS_BARGSIZE
#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

/* Increase print buffer size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/* Increase maximum number of arguments */
#undef CONFIG_SYS_MAXARGS
#define CONFIG_SYS_MAXARGS		32

#include "tegra-common-usb-gadget.h"
#include "tegra-common-post.h"

#endif /* __CONFIG_H */
