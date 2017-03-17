/*
 * (C) Copyright 2015-2016 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Configuration settings for the Freescale S32V234 EVB board.
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#ifndef CONFIG_SPL_BUILD
#include <config_distro_defaults.h>
#endif

#include <asm/arch/imx-regs.h>

#define CONFIG_S32V234
#define CONFIG_DM

/* Config GIC */
#define CONFIG_GICV2
#define GICD_BASE 0x7D001000
#define GICC_BASE 0x7D002000

#define CONFIG_REMAKE_ELF
#undef CONFIG_RUN_FROM_IRAM_ONLY

#define CONFIG_RUN_FROM_DDR1
#undef CONFIG_RUN_FROM_DDR0

/* Run by default from DDR1  */
#ifdef CONFIG_RUN_FROM_DDR0
#define DDR_BASE_ADDR		0x80000000
#else
#define DDR_BASE_ADDR		0xC0000000
#endif

#define CONFIG_MACH_TYPE		4146

#define CONFIG_SKIP_LOWLEVEL_INIT

/* Config CACHE */
#define CONFIG_CMD_CACHE

#define CONFIG_SYS_FULL_VA

/* Enable passing of ATAGs */
#define CONFIG_CMDLINE_TAG

/* SMP Spin Table Definitions */
#define CPU_RELEASE_ADDR                (CONFIG_SYS_SDRAM_BASE + 0x7fff0)

/* Generic Timer Definitions */
#define COUNTER_FREQUENCY               (1000000000)	/* 1000MHz */
#define CONFIG_SYS_FSL_ERRATUM_A008585

/* Size of malloc() pool */
#ifdef CONFIG_RUN_FROM_IRAM_ONLY
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 1 * 1024 * 1024)
#else
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 2 * 1024 * 1024)
#endif

#define CONFIG_DM_SERIAL
#define CONFIG_FSL_LINFLEXUART
#define LINFLEXUART_BASE		LINFLEXD0_BASE_ADDR

#define CONFIG_DEBUG_UART_LINFLEXUART
#define CONFIG_DEBUG_UART_BASE		LINFLEXUART_BASE

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_SYS_UART_PORT		(1)

#undef CONFIG_CMD_IMLS

#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC_BASE_ADDR
#define CONFIG_SYS_FSL_ESDHC_NUM	1

#define CONFIG_CMD_MMC
/* #define CONFIG_CMD_EXT2 EXT2 Support */

#if 0

/* Ethernet config */
#define CONFIG_CMD_PING
#define CONFIG_CMD_MII
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE            ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE     RMII
#define CONFIG_FEC_MXC_PHYADDR  0
#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#endif

#if 0				/* Disable until the I2C driver will be updated */

/* I2C Configs */
#define CONFIG_CMD_I2C
#define CONFIG_HARD_I2C
#define CONFIG_I2C_MXC
#define CONFIG_SYS_I2C_BASE		I2C0_BASE_ADDR
#define CONFIG_SYS_I2C_SPEED		100000
#endif

#if 0				/* Disable until the FLASH will be implemented */
#define CONFIG_SYS_USE_NAND
#endif

#ifdef CONFIG_SYS_USE_NAND
/* Nand Flash Configs */
#define	CONFIG_CMD_NAND
#define CONFIG_JFFS2_NAND
#define MTD_NAND_FSL_NFC_SWECC 1
#define CONFIG_NAND_FSL_NFC
#define CONFIG_SYS_NAND_BASE		0x400E0000
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define NAND_MAX_CHIPS			CONFIG_SYS_MAX_NAND_DEVICE
#define CONFIG_SYS_NAND_SELECT_DEVICE
#define CONFIG_SYS_64BIT_VSPRINTF	/* needed for nand_util.c */
#endif

#define CONFIG_LOADADDR			0xC307FFC0
#define CONFIG_BOOTARGS			"console=ttyLF0 root=/dev/ram rw"

#define CONFIG_CMD_ENV
#define CONFIG_EXTRA_ENV_SETTINGS \
	"boot_scripts=boot.scr.uimg boot.scr\0" \
	"scriptaddr=" __stringify(CONFIG_LOADADDR) "\0" \
	"console=ttyLF0,115200\0" \
	"fdt_file=s32v234-evb.dtb\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_addr_r=0xC2000000\0" \
	"kernel_addr_r=0xC307FFC0\0" \
	"ramdisk_addr_r=0xC4000000\0" \
	"ramdisk=rootfs.uimg\0"\
	"ip_dyn=yes\0" \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"update_sd_firmware_filename=u-boot.imx\0" \
	"update_sd_firmware=" \
		"if test ${ip_dyn} = yes; then " \
			"setenv get_cmd dhcp; " \
		"else " \
			"setenv get_cmd tftp; " \
		"fi; " \
		"if mmc dev ${mmcdev}; then "	\
			"if ${get_cmd} ${update_sd_firmware_filename}; then " \
				"setexpr fw_sz ${filesize} / 0x200; " \
				"setexpr fw_sz ${fw_sz} + 1; "	\
				"mmc write ${loadaddr} 0x2 ${fw_sz}; " \
			"fi; "	\
		"fi\0" \
	"loadramdisk=fatload mmc ${mmcdev}:${mmcpart} ${ramdisk_addr} ${ramdisk}\0" \
	"jtagboot=echo Booting using jtag...; " \
		"bootm ${kernel_addr} ${ramdisk_addr} ${fdt_addr}\0" \
	"jtagsdboot=echo Booting loading Linux with ramdisk from SD...; " \
		"run loaduimage; run loadramdisk; run loadfdt;"\
		"bootm ${kernel_addr} ${ramdisk_addr} ${fdt_addr}\0" \
	"boot_net_usb_start=true\0" \
	BOOTENV

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 1) \
	func(MMC, mmc, 0) \
	func(DHCP, dhcp, na)

#define CONFIG_BOOTCOMMAND \
	"run distro_bootcmd"

#include <config_distro_bootcmd.h>

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP	/* undef to save memory */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_SYS_PROMPT		"=> "
#undef CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		\
			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_CMDLINE_EDITING

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	(DDR_BASE_ADDR)
#define CONFIG_SYS_MEMTEST_END		(DDR_BASE_ADDR + 0x7C00000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ				1000

#define CONFIG_SYS_TEXT_BASE		0x3E800000	/* SDRAM */

#ifdef CONFIG_RUN_FROM_IRAM_ONLY
#define CONFIG_SYS_MALLOC_BASE		(DDR_BASE_ADDR)
#endif

/*
 * Stack sizes
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE		(128 * 1024)	/* regular stack */

#if 0
/* Configure PXE */
#define CONFIG_BOOTP_PXE
#define CONFIG_BOOTP_PXE_CLIENTARCH	0x100
#endif

/* Physical memory map */
/* EVB board has 2x256 MB DDR chips, DDR0 and DDR1, u-boot is using just one */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			(DDR_BASE_ADDR)
#define PHYS_SDRAM_SIZE			(256 * 1024 * 1024)

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* environment organization */
#define CONFIG_ENV_SIZE			(8 * 1024)
#define CONFIG_ENV_IS_IN_MMC

#define CONFIG_ENV_OFFSET		(12 * 64 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV		0


#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

#endif
