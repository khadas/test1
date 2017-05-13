/*
 *  (C) Copyright 2010,2011
 *  NVIDIA Corporation <www.nvidia.com>
 *  (C) Copyright 2011-2012
 *  Avionic Design GmbH <www.avionic-design.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include "tegra20-common.h"

/* High-level configuration options */
#define CONFIG_TEGRA_BOARD_STRING	"Avionic Design Tamonten Evaluation Carrier"

/* Board-specific serial config */
#define CONFIG_TEGRA_ENABLE_UARTD	/* UARTD: debug UART */
#define CONFIG_SYS_NS16550_COM1		NV_PA_APB_UARTD_BASE

/* NAND support */
#define CONFIG_CMD_NAND
#define CONFIG_TEGRA_NAND
#define CONFIG_SYS_MAX_NAND_DEVICE	1

/* Environment in NAND, aligned to start of last sector */
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_OFFSET		(SZ_512M - SZ_128K) /* 128K sectors */

/* USB host support */
#define CONFIG_USB_EHCI_HCD
#define CONFIG_USB_EHCI_TEGRA

/* USB networking support */
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_SMSC95XX

#include "tegra-common-post.h"

#endif /* __CONFIG_H */
