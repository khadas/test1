/*
 * include/configs/alt.h
 *     This file is alt board configuration.
 *
 * Copyright (C) 2014 Renesas Electronics Corporation
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#ifndef __ALT_H
#define __ALT_H

#undef DEBUG
#define CONFIG_ARMV7
#define CONFIG_R8A7794
#define CONFIG_RMOBILE_BOARD_STRING "Alt"
#define CONFIG_SH_GPIO_PFC

#include <asm/arch/rmobile.h>

#define	CONFIG_CMD_EDITENV
#define	CONFIG_CMD_SAVEENV
#define CONFIG_CMD_MEMORY
#define CONFIG_CMD_DFL
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_RUN
#define CONFIG_CMD_LOADS
#define CONFIG_CMD_NET
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_NFS
#define CONFIG_CMD_BOOTZ
#define CONFIG_CMD_USB
#define CONFIG_CMD_SF
#define CONFIG_CMD_SPI

#if defined(CONFIG_RMOBILE_EXTRAM_BOOT)
#define CONFIG_SYS_TEXT_BASE	0x70000000
#else
#define CONFIG_SYS_TEXT_BASE	0xE6304000
#endif
#define CONFIG_SYS_THUMB_BUILD
#define CONFIG_SYS_GENERIC_BOARD

#define	CONFIG_CMDLINE_TAG
#define	CONFIG_SETUP_MEMORY_TAGS
#define	CONFIG_INITRD_TAG
#define	CONFIG_CMDLINE_EDITING

#define CONFIG_OF_LIBFDT
#define BOARD_LATE_INIT

#define CONFIG_BAUDRATE		38400
#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTARGS		""

#define CONFIG_VERSION_VARIABLE
#undef	CONFIG_SHOW_BOOT_PROGRESS

#define CONFIG_ARCH_CPU_INIT
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_TMU_TIMER

#if defined(CONFIG_RMOBILE_EXTRAM_BOOT)
#define CONFIG_SYS_INIT_SP_ADDR		0x7003FFFC
#else
#define CONFIG_SYS_INIT_SP_ADDR		0xE633FFFC
#endif
#define STACK_AREA_SIZE			0xC000
#define LOW_LEVEL_MERAM_STACK \
		(CONFIG_SYS_INIT_SP_ADDR + STACK_AREA_SIZE - 4)

/* MEMORY */
#define ALT_SDRAM_BASE		0x40000000
#define ALT_SDRAM_SIZE		(1024u * 1024 * 1024)
#define ALT_UBOOT_SDRAM_SIZE	(512 * 1024 * 1024)

#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		256
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		512
#define CONFIG_SYS_BAUDRATE_TABLE	{ 38400, 115200 }

/* SCIF */
#define CONFIG_SCIF_CONSOLE
#define CONFIG_CONS_SCIF2
#undef	CONFIG_SYS_CONSOLE_INFO_QUIET
#undef	CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
#undef	CONFIG_SYS_CONSOLE_ENV_OVERWRITE

#define CONFIG_SYS_MEMTEST_START	(ALT_SDRAM_BASE)
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + \
					 504 * 1024 * 1024)
#undef	CONFIG_SYS_ALT_MEMTEST
#undef	CONFIG_SYS_MEMTEST_SCRATCH
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE

#define CONFIG_SYS_SDRAM_BASE		(ALT_SDRAM_BASE)
#define CONFIG_SYS_SDRAM_SIZE		(ALT_UBOOT_SDRAM_SIZE)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x7fc0)
#define CONFIG_NR_DRAM_BANKS		1

#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_SYS_MONITOR_LEN		(256 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(1 * 1024 * 1024)
#define CONFIG_SYS_BOOTMAPSZ		(8 * 1024 * 1024)

/* FLASH */
#define CONFIG_SPI
#define CONFIG_SPI_FLASH_BAR
#define CONFIG_SH_QSPI
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_SPANSION
#define CONFIG_SPI_FLASH_QUAD
#define CONFIG_SYS_NO_FLASH

/* ENV setting */
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SECT_SIZE	(256 * 1024)
#define CONFIG_ENV_ADDR		0xC0000
#define CONFIG_ENV_OFFSET	(CONFIG_ENV_ADDR)
#define CONFIG_ENV_SIZE		(CONFIG_ENV_SECT_SIZE)

#define CONFIG_EXTRA_ENV_SETTINGS \
	"bootm_low=0x40e00000\0" \
	"bootm_size=0x100000\0" \

/* SH Ether */
#define	CONFIG_NET_MULTI
#define CONFIG_SH_ETHER
#define CONFIG_SH_ETHER_USE_PORT	0
#define CONFIG_SH_ETHER_PHY_ADDR	0x1
#define CONFIG_SH_ETHER_PHY_MODE PHY_INTERFACE_MODE_RMII
#define CONFIG_SH_ETHER_CACHE_WRITEBACK
#define CONFIG_SH_ETHER_CACHE_INVALIDATE
#define CONFIG_SH_ETHER_ALIGNE_SIZE 64
#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#define CONFIG_BITBANGMII
#define CONFIG_BITBANGMII_MULTI

/* Board Clock */
#define RMOBILE_XTAL_CLK        20000000u
#define CONFIG_SYS_CLK_FREQ     RMOBILE_XTAL_CLK
#define CONFIG_SH_TMU_CLK_FREQ  (CONFIG_SYS_CLK_FREQ / 2) /* EXT / 2 */
#define CONFIG_PLL1_CLK_FREQ    (CONFIG_SYS_CLK_FREQ * 156 / 2)
#define CONFIG_P_CLK_FREQ	(CONFIG_PLL1_CLK_FREQ / 24)
#define CONFIG_SH_SCIF_CLK_FREQ CONFIG_P_CLK_FREQ

#define CONFIG_SYS_TMU_CLK_DIV  4

/* i2c */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_SH
#define CONFIG_SYS_I2C_SLAVE		0x7F
#define CONFIG_SYS_I2C_SH_NUM_CONTROLLERS       3
#define CONFIG_SYS_I2C_SH_BASE0		0xE6500000
#define CONFIG_SYS_I2C_SH_SPEED0	400000
#define CONFIG_SYS_I2C_SH_BASE1		0xE6510000
#define CONFIG_SYS_I2C_SH_SPEED1	400000
#define CONFIG_SYS_I2C_SH_BASE2		0xE60B0000
#define CONFIG_SYS_I2C_SH_SPEED2	400000
#define CONFIG_SH_I2C_DATA_HIGH		4
#define CONFIG_SH_I2C_DATA_LOW		5
#define CONFIG_SH_I2C_CLOCK		10000000

#define CONFIG_SYS_I2C_POWERIC_ADDR 0x58 /* da9063 */

/* USB */
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_RMOBILE
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2

#endif /* __ALT_H */
