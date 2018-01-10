/*
 * Copyright (C) 2015 Timesys Corporation
 * Copyright (C) 2015 General Electric Company
 * Copyright (C) 2014 Advantech
 * Copyright (C) 2012 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the GE MX6Q Bx50v3 boards.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __GE_BX50V3_CONFIG_H
#define __GE_BX50V3_CONFIG_H

#include <asm/arch/imx-regs.h>
#include <asm/mach-imx/gpio.h>

#define BX50V3_BOOTARGS_EXTRA
#if defined(CONFIG_TARGET_GE_B450V3)
#define CONFIG_BOARD_NAME	"General Electric B450v3"
#elif defined(CONFIG_TARGET_GE_B650V3)
#define CONFIG_BOARD_NAME	"General Electric B650v3"
#elif defined(CONFIG_TARGET_GE_B850V3)
#define CONFIG_BOARD_NAME	"General Electric B850v3"
#undef BX50V3_BOOTARGS_EXTRA
#define BX50V3_BOOTARGS_EXTRA	"video=DP-1:1024x768@60 " \
				"video=HDMI-A-1:1024x768@60 "
#else
#define CONFIG_BOARD_NAME	"General Electric BA16 Generic"
#endif

#define CONFIG_MXC_UART_BASE	UART3_BASE
#define CONSOLE_DEV	"ttymxc2"

#define CONFIG_SUPPORT_EMMC_BOOT


#include "mx6_common.h"
#include <linux/sizes.h>

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG
#define CONFIG_SYS_MALLOC_LEN		(10 * SZ_1M)

#define CONFIG_HW_WATCHDOG
#define CONFIG_IMX_WATCHDOG
#define CONFIG_WATCHDOG_TIMEOUT_MSECS 6000

#define CONFIG_LAST_STAGE_INIT

#define CONFIG_MXC_GPIO
#define CONFIG_MXC_UART

#define CONFIG_MXC_OCOTP

/* SATA Configs */
#ifdef CONFIG_CMD_SATA
#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_DWC_AHSATA_PORT_ID	0
#define CONFIG_DWC_AHSATA_BASE_ADDR	SATA_ARB_BASE_ADDR
#define CONFIG_LBA48
#endif

/* MMC Configs */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR      0
#define CONFIG_BOUNCE_BUFFER

/* USB Configs */
#ifdef CONFIG_USB
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_MXC_USB_PORTSC	(PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS	0

#define CONFIG_USBD_HS
#define CONFIG_USB_GADGET_MASS_STORAGE
#endif

/* Networking Configs */
#ifdef CONFIG_NET
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RGMII
#define CONFIG_ETHPRIME		"FEC"
#define CONFIG_FEC_MXC_PHYADDR		4
#define CONFIG_PHY_ATHEROS
#endif

/* Serial Flash */
#ifdef CONFIG_CMD_SF
#define CONFIG_MXC_SPI
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		0
#define CONFIG_SF_DEFAULT_SPEED	20000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
#endif

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX	1

#define CONFIG_LOADADDR	0x12000000
#define CONFIG_SYS_TEXT_BASE	0x17800000

#define CONFIG_EXTRA_ENV_SETTINGS \
	"script=boot.scr\0" \
	"bootlimit=10\0" \
	"image=/boot/fitImage\0" \
	"console=" CONSOLE_DEV "\0" \
	"fdt_high=0xffffffff\0"	  \
	"sddev=0\0" \
	"emmcdev=1\0" \
	"partnum=1\0" \
	"setargs=setenv bootargs console=${console},${baudrate} " \
		"root=/dev/${rootdev} ro rootwait cma=128M " \
		BX50V3_BOOTARGS_EXTRA "\0" \
	"loadimage=" \
		"ext2load ${dev} ${devnum}:${partnum} ${loadaddr} ${image}\0" \
	"tryboot=" \
		"if run loadimage; then " \
			"run doboot; " \
		"fi;\0" \
	"doboot=echo Booting from ${dev}:${devnum}:${partnum} ...; " \
		"run setargs; " \
		"bootm ${loadaddr}#conf@${confidx};\0 " \

#define CONFIG_MMCBOOTCOMMAND \
	"setenv dev mmc; " \
	"setenv devnum ${emmcdev}; " \
	\
	"if ext2load ${dev} ${devnum}:5 0x7000A000 /boot/active/boot.img ; " \
	"then " \
		"source 0x7000A000; " \
	"fi; " \
	\
	"setenv rootdev mmcblk0p${partnum}; " \
	\
	"if mmc dev ${devnum}; then " \
		"run tryboot; " \
	"fi; " \

#define CONFIG_USBBOOTCOMMAND \
	"echo Unsupported; " \

#ifdef CONFIG_CMD_USB
#define CONFIG_BOOTCOMMAND CONFIG_USBBOOTCOMMAND
#else
#define CONFIG_BOOTCOMMAND CONFIG_MMCBOOTCOMMAND
#endif

#define CONFIG_ARP_TIMEOUT     200UL

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP
#define CONFIG_AUTO_COMPLETE

#define CONFIG_SYS_MEMTEST_START       0x10000000
#define CONFIG_SYS_MEMTEST_END         0x10010000
#define CONFIG_SYS_MEMTEST_SCRATCH     0x10800000

#define CONFIG_SYS_LOAD_ADDR           CONFIG_LOADADDR

#define CONFIG_CMDLINE_EDITING

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS           1
#define PHYS_SDRAM                     MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE          PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR       IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE       IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* environment organization */
#define CONFIG_ENV_SIZE		(8 * 1024)
#define CONFIG_ENV_OFFSET		(768 * 1024)
#define CONFIG_ENV_SECT_SIZE		(64 * 1024)
#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED

#ifndef CONFIG_SYS_DCACHE_OFF
#endif

#define CONFIG_SYS_FSL_USDHC_NUM	3

/* Framebuffer */
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_IPUV3
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO
#define CONFIG_IMX_HDMI
#define CONFIG_IMX_VIDEO_SKIP
#endif

#define CONFIG_PWM_IMX
#define CONFIG_IMX6_PWM_PER_CLK	66000000

#define CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_PCIE_IMX
#define CONFIG_PCIE_IMX_PERST_GPIO	IMX_GPIO_NR(7, 12)
#define CONFIG_PCIE_IMX_POWER_GPIO	IMX_GPIO_NR(1, 5)

/* I2C Configs */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_SPEED		  100000
#define CONFIG_SYS_I2C_MXC_I2C1
#define CONFIG_SYS_I2C_MXC_I2C2
#define CONFIG_SYS_I2C_MXC_I2C3

#define CONFIG_SYS_NUM_I2C_BUSES        11
#define CONFIG_SYS_I2C_MAX_HOPS         1
#define CONFIG_SYS_I2C_BUSES	{	{0, {I2C_NULL_HOP} }, \
					{1, {I2C_NULL_HOP} }, \
					{2, {I2C_NULL_HOP} }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 0} } }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 1} } }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 2} } }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 3} } }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 4} } }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 5} } }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 6} } }, \
					{0, {{I2C_MUX_PCA9547, 0x70, 7} } }, \
				}

#define CONFIG_BCH

#define CONFIG_BOOTCOUNT_LIMIT
#define CONFIG_BOOTCOUNT_EXT
#define CONFIG_SYS_BOOTCOUNT_EXT_INTERFACE	"mmc"
#define CONFIG_SYS_BOOTCOUNT_EXT_DEVPART	"1:5"
#define CONFIG_SYS_BOOTCOUNT_EXT_NAME		"/boot/failures"
#define CONFIG_SYS_BOOTCOUNT_ADDR		0x7000A000

#endif	/* __GE_BX50V3_CONFIG_H */
