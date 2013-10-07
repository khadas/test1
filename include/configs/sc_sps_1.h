/*
 * SchulerControl GmbH, SC_SPS_1 module config
 *
 * Copyright (C) 2012 Marek Vasut <marex@denx.de>
 * on behalf of DENX Software Engineering GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIGS_SC_SPS_1_H__
#define __CONFIGS_SC_SPS_1_H__

/* System configuration */
#define CONFIG_MX28				/* i.MX28 SoC */
#define MACH_TYPE_SC_SPS_1	4172
#define CONFIG_MACH_TYPE	MACH_TYPE_SC_SPS_1

/* U-Boot Commands */
#define CONFIG_SYS_NO_FLASH
#include <config_cmd_default.h>
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DOS_PARTITION

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_CMD_GPIO
#define CONFIG_CMD_MII
#define CONFIG_CMD_MMC
#define CONFIG_CMD_NET
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PING
#define CONFIG_CMD_SETEXPR
#define CONFIG_CMD_USB

/* Memory configuration */
#define CONFIG_NR_DRAM_BANKS		1		/* 1 bank of DRAM */
#define PHYS_SDRAM_1			0x40000000	/* Base address */
#define PHYS_SDRAM_1_SIZE		0x40000000	/* Max 1 GB RAM */
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

/* Environment */
#define CONFIG_ENV_SIZE			(16 * 1024)
#define CONFIG_ENV_IS_IN_MMC

/* Environment is in MMC */
#if defined(CONFIG_CMD_MMC) && defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(256 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV		0
#else
#define CONFIG_ENV_IS_NOWHERE
#endif

/* FEC Ethernet on SoC */
#ifdef CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_PHYLIB
#define CONFIG_PHY_SMSC
#endif

/* USB */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_MXS_PORT0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_USB_STORAGE
#endif

/* Booting Linux */
#define CONFIG_BOOTDELAY	3
#define CONFIG_BOOTFILE		"uImage"
#define CONFIG_BOOTARGS		"console=ttyAMA0,115200"
#define CONFIG_BOOTCOMMAND	"bootm"
#define CONFIG_LOADADDR		0x42000000
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

/* Extra Environment */
#define CONFIG_EXTRA_ENV_SETTINGS					\
	"update_sd_firmware_filename=u-boot.sd\0"			\
	"update_sd_firmware="		/* Update the SD firmware partition */ \
		"if mmc rescan ; then "					\
		"if tftp ${update_sd_firmware_filename} ; then "	\
		"setexpr fw_sz ${filesize} / 0x200 ; "	/* SD block size */ \
		"setexpr fw_sz ${fw_sz} + 1 ; "				\
		"mmc write ${loadaddr} 0x800 ${fw_sz} ; "		\
		"fi ; "							\
		"fi\0"

/* The rest of the configuration is shared */
#include <configs/mxs.h>

#endif /* __CONFIGS_SC_SPS_1_H__ */
