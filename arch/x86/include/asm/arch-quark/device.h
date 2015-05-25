/*
 * Copyright (C) 2015, Bin Meng <bmeng.cn@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _QUARK_DEVICE_H_
#define _QUARK_DEVICE_H_

#include <pci.h>

#define QUARK_HOST_BRIDGE_DEV	0
#define QUARK_HOST_BRIDGE_FUNC	0

#define QUARK_DEV_20		20
#define QUARK_MMC_SDIO_FUNC	0
#define QUARK_UART0_FUNC	1
#define QUARK_USB_DEVICE_FUNC	2
#define QUARK_USB_EHCI_FUNC	3
#define QUARK_USB_OHCI_FUNC	4
#define QUARK_UART1_FUNC	5
#define QUARK_EMAC0_FUNC	6
#define QUARK_EMAC1_FUNC	7

#define QUARK_DEV_21		21
#define QUARK_SPI0_FUNC		0
#define QUARK_SPI1_FUNC		1
#define QUARK_I2C_GPIO_FUNC	2

#define QUARK_DEV_23		23
#define QUARK_PCIE0_FUNC	0
#define QUARK_PCIE1_FUNC	1

#define QUARK_LGC_BRIDGE_DEV	31
#define QUARK_LGC_BRIDGE_FUNC	0

#define QUARK_HOST_BRIDGE	\
	PCI_BDF(0, QUARK_HOST_BRIDGE_DEV, QUARK_HOST_BRIDGE_FUNC)
#define QUARK_MMC_SDIO		\
	PCI_BDF(0, QUARK_DEV_20, QUARK_MMC_SDIO_FUNC)
#define QUARK_UART0		\
	PCI_BDF(0, QUARK_DEV_20, QUARK_UART0_FUNC)
#define QUARK_USB_DEVICE	\
	PCI_BDF(0, QUARK_DEV_20, QUARK_USB_DEVICE_FUNC)
#define QUARK_USB_EHCI		\
	PCI_BDF(0, QUARK_DEV_20, QUARK_USB_EHCI_FUNC)
#define QUARK_USB_OHCI		\
	PCI_BDF(0, QUARK_DEV_20, QUARK_USB_OHCI_FUNC)
#define QUARK_UART1		\
	PCI_BDF(0, QUARK_DEV_20, QUARK_UART1_FUNC)
#define QUARK_EMAC0		\
	PCI_BDF(0, QUARK_DEV_20, QUARK_EMAC0_FUNC)
#define QUARK_EMAC1		\
	PCI_BDF(0, QUARK_DEV_20, QUARK_EMAC1_FUNC)
#define QUARK_SPI0		\
	PCI_BDF(0, QUARK_DEV_21, QUARK_SPI0_FUNC)
#define QUARK_SPI1		\
	PCI_BDF(0, QUARK_DEV_21, QUARK_SPI1_FUNC)
#define QUARK_I2C_GPIO		\
	PCI_BDF(0, QUARK_DEV_21, QUARK_I2C_GPIO_FUNC)
#define QUARK_PCIE0		\
	PCI_BDF(0, QUARK_DEV_23, QUARK_PCIE0_FUNC)
#define QUARK_PCIE1		\
	PCI_BDF(0, QUARK_DEV_23, QUARK_PCIE1_FUNC)
#define QUARK_LEGACY_BRIDGE	\
	PCI_BDF(0, QUARK_LGC_BRIDGE_DEV, QUARK_LGC_BRIDGE_FUNC)

#endif /* _QUARK_DEVICE_H_ */
