/*
 * Copyright 2016 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __LS1012ARDB_H__
#define __LS1012ARDB_H__

#include "ls1012a_common.h"


#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	1
#define CONFIG_NR_DRAM_BANKS		2
#define CONFIG_SYS_SDRAM_SIZE		0x40000000

#define CONFIG_SYS_MMDC_CORE_CONTROL_1		0x05180000
#define CONFIG_SYS_MMDC_CORE_CONTROL_2		0x85180000

#define CONFIG_CMD_MEMINFO
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		0x9fffffff

/*
* USB
*/
#define CONFIG_HAS_FSL_XHCI_USB

#ifdef CONFIG_HAS_FSL_XHCI_USB
#define CONFIG_USB_XHCI_FSL
#define CONFIG_USB_MAX_CONTROLLER_COUNT         1
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS      2
#define CONFIG_USB_STORAGE
#endif

/*
 * I2C IO expander
 */

#define I2C_MUX_IO1_ADDR	0x24
#define __SW_BOOT_MASK		0xFC
#define __SW_BOOT_EMU		0x10
#define __SW_BOOT_BANK1		0x00
#define __SW_BOOT_BANK2		0x01
#define __SW_REV_MASK		0x07
#define __SW_REV_A		0xF8
#define __SW_REV_B		0xF0

/*  MMC  */
#define CONFIG_MMC
#ifdef CONFIG_MMC
#define CONFIG_FSL_ESDHC
#define CONFIG_SYS_FSL_MMC_HAS_CAPBLT_VS33
#define CONFIG_GENERIC_MMC
#define CONFIG_DOS_PARTITION
#endif

/* SATA */
#define CONFIG_LIBATA
#define	CONFIG_SCSI
#define CONFIG_SCSI_AHCI
#define CONFIG_SCSI_AHCI_PLAT
#define CONFIG_CMD_SCSI
#define CONFIG_DOS_PARTITION
#define CONFIG_BOARD_LATE_INIT

#define CONFIG_SYS_SATA				AHCI_BASE_ADDR

#define CONFIG_SYS_SCSI_MAX_SCSI_ID		1
#define CONFIG_SYS_SCSI_MAX_LUN			1
#define CONFIG_SYS_SCSI_MAX_DEVICE		(CONFIG_SYS_SCSI_MAX_SCSI_ID * \
						CONFIG_SYS_SCSI_MAX_LUN)
#define CONFIG_PCI		/* Enable PCI/PCIE */
#define CONFIG_PCIE1		/* PCIE controller 1 */
#define CONFIG_PCIE_LAYERSCAPE	/* Use common FSL Layerscape PCIe code */
#define FSL_PCIE_COMPAT "fsl,ls1043a-pcie"

#define CONFIG_SYS_PCI_64BIT

#define CONFIG_SYS_PCIE_CFG0_PHYS_OFF	0x00000000
#define CONFIG_SYS_PCIE_CFG0_SIZE	0x00001000	/* 4k */
#define CONFIG_SYS_PCIE_CFG1_PHYS_OFF	0x00001000
#define CONFIG_SYS_PCIE_CFG1_SIZE	0x00001000	/* 4k */

#define CONFIG_SYS_PCIE_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE_IO_PHYS_OFF	0x00010000
#define CONFIG_SYS_PCIE_IO_SIZE		0x00010000	/* 64k */

#define CONFIG_SYS_PCIE_MEM_BUS         0x08000000
#define CONFIG_SYS_PCIE_MEM_PHYS_OFF    0x04000000
#define CONFIG_SYS_PCIE_MEM_SIZE        0x80000000      /* 128M */

#define CONFIG_NET_MULTI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_CMD_PCI

#define CONFIG_CMD_MEMINFO
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		0x9fffffff

#endif /* __LS1012ARDB_H__ */
