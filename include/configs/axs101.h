/*
 * Copyright (C) 2013-2014 Synopsys, Inc. All rights reserved.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _CONFIG_AXS101_H_
#define _CONFIG_AXS101_H_

/*
 *  CPU configuration
 */
#define CONFIG_ARC700
#define CONFIG_ARC_MMU_VER		3
#define CONFIG_SYS_CACHELINE_SIZE	32
#define CONFIG_SYS_CLK_FREQ		750000000
#define CONFIG_SYS_TIMER_RATE		CONFIG_SYS_CLK_FREQ

/* dwgmac doesn't work with D$ enabled now */
#define CONFIG_SYS_DCACHE_OFF

/*
 * Board configuration
 */
#define CONFIG_SYS_GENERIC_BOARD
#define CONFIG_SKIP_LOWLEVEL_INIT	/* U-Boot is in RAM already */

#define CONFIG_ARCH_EARLY_INIT_R

#define ARC_FPGA_PERIPHERAL_BASE	0xE0000000
#define ARC_APB_PERIPHERAL_BASE		0xF0000000
#define ARC_DWMMC_BASE			(ARC_FPGA_PERIPHERAL_BASE + 0x15000)
#define ARC_DWGMAC_BASE			(ARC_FPGA_PERIPHERAL_BASE + 0x18000)

/*
 * Memory configuration
 */
#define CONFIG_SYS_TEXT_BASE		0x81000000
#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE

#define CONFIG_SYS_DDR_SDRAM_BASE	0x80000000
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE
#define CONFIG_SYS_SDRAM_SIZE		0x10000000	/* 256 Mb */

#define CONFIG_SYS_INIT_SP_ADDR		\
	(CONFIG_SYS_SDRAM_BASE + 0x1000 - GENERATED_GBL_DATA_SIZE)

#define CONFIG_SYS_MALLOC_LEN		0x200000	/* 2 MB */
#define CONFIG_SYS_BOOTM_LEN		0x2000000	/* 32 MB */
#define CONFIG_SYS_LOAD_ADDR		0x82000000

/*
 * NAND Flash configuration
 */
#define CONFIG_SYS_NO_FLASH
#define CONFIG_SYS_NAND_BASE		(ARC_FPGA_PERIPHERAL_BASE + 0x16000)
#define CONFIG_SYS_MAX_NAND_DEVICE	1

/*
 * UART configuration
 *
 * CONFIG_CONS_INDEX = 1 - Debug UART
 * CONFIG_CONS_INDEX = 4 - FPGA UART connected to FTDI/USB
 */
#define CONFIG_CONS_INDEX		4
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	-4
#if (CONFIG_CONS_INDEX == 1)
	/* Debug UART */
#	define CONFIG_SYS_NS16550_CLK		33333000
#else
	/* FPGA UARTs use different clock */
#	define CONFIG_SYS_NS16550_CLK		33333333
#endif
#define CONFIG_SYS_NS16550_COM1		(ARC_APB_PERIPHERAL_BASE + 0x5000)
#define CONFIG_SYS_NS16550_COM2		(ARC_FPGA_PERIPHERAL_BASE + 0x20000)
#define CONFIG_SYS_NS16550_COM3		(ARC_FPGA_PERIPHERAL_BASE + 0x21000)
#define CONFIG_SYS_NS16550_COM4		(ARC_FPGA_PERIPHERAL_BASE + 0x22000)
#define CONFIG_SYS_NS16550_MEM32

#define CONFIG_BAUDRATE			115200
/*
 * I2C configuration
 */
#define CONFIG_HARD_I2C
#define CONFIG_DW_I2C
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_I2C_ENV_EEPROM_BUS	2
#define CONFIG_SYS_I2C_SPEED		100000
#define CONFIG_SYS_I2C_SLAVE		0
#define CONFIG_SYS_I2C_BASE		0xE001D000
#define CONFIG_SYS_I2C_BASE1		0xE001E000
#define CONFIG_SYS_I2C_BASE2		0xE001F000
#define CONFIG_SYS_I2C_BUS_MAX		3
#define IC_CLK				50

/*
 * EEPROM configuration
 */
#define CONFIG_SYS_I2C_MULTI_EEPROMS
#define CONFIG_SYS_I2C_EEPROM_ADDR		(0xA8 >> 1)
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
#define CONFIG_SYS_I2C_EEPROM_ADDR_OVERFLOW	1
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	3
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	32

/*
 * SD/MMC configuration
 */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_DWMMC
#define CONFIG_DOS_PARTITION

/*
 * Ethernet PHY configuration
 */
#define CONFIG_PHYLIB
#define CONFIG_MII
#define CONFIG_PHY_GIGE

/*
 * Ethernet configuration
 */
#define CONFIG_DESIGNWARE_ETH
#define CONFIG_DW_AUTONEG
#define CONFIG_DW_SEARCH_PHY
#define CONFIG_NET_MULTI

/*
 * Command line configuration
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_DHCP
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_ELF
#define CONFIG_CMD_FAT
#define CONFIG_CMD_I2C
#define CONFIG_CMD_MMC
#define CONFIG_CMD_NAND
#define CONFIG_CMD_PING
#define CONFIG_CMD_RARP

#define CONFIG_OF_LIBFDT

#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_MAXARGS		16

/*
 * Environment settings
 */
#define CONFIG_ENV_IS_IN_EEPROM
#define CONFIG_ENV_SIZE			0x00200		/* 512 bytes */
#define CONFIG_ENV_OFFSET		0

/*
 * Environment configuration
 */
#define CONFIG_BOOTDELAY		3
#define CONFIG_BOOTFILE			"uImage"
#define CONFIG_BOOTARGS			"console=ttyS3,115200n8"
#define CONFIG_LOADADDR			CONFIG_SYS_LOAD_ADDR

/*
 * Console configuration
 */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT		"AXS# "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
						sizeof(CONFIG_SYS_PROMPT) + 16)

/*
 * Misc utility configuration
 */
#define CONFIG_BOUNCE_BUFFER

#endif /* _CONFIG_AXS101_H_ */
