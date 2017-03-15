/*
 * Copyright (c) 2011 The Chromium OS Authors.
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#ifdef FTRACE
#define CONFIG_TRACE
#define CONFIG_CMD_TRACE
#define CONFIG_TRACE_BUFFER_SIZE	(16 << 20)
#define CONFIG_TRACE_EARLY_SIZE		(8 << 20)
#define CONFIG_TRACE_EARLY
#define CONFIG_TRACE_EARLY_ADDR		0x00100000

#endif

#ifndef CONFIG_SPL_BUILD
#define CONFIG_IO_TRACE
#define CONFIG_CMD_IOTRACE
#endif

#ifndef CONFIG_TIMER
#define CONFIG_SYS_TIMER_RATE		1000000
#endif

/*
 * Number of bits in a C 'long' on this architecture. Set this to 32 when
 * building on a 32-bit machine.
 */
#define CONFIG_SANDBOX_BITS_PER_LONG	64

#define CONFIG_LMB
#define CONFIG_ANDROID_BOOT_IMAGE

#define CONFIG_CMD_PCI
#define CONFIG_CMD_IO

#define CONFIG_FS_FAT
#define CONFIG_FAT_WRITE
#define CONFIG_FS_EXT4
#define CONFIG_EXT4_WRITE
#define CONFIG_CMD_CBFS
#define CONFIG_CMD_CRAMFS
#define CONFIG_HOST_MAX_DEVICES 4

/*
 * Size of malloc() pool, before and after relocation
 */
#define CONFIG_MALLOC_F_ADDR		0x0010000
#define CONFIG_SYS_MALLOC_LEN		(32 << 20)	/* 32MB  */

#define CONFIG_SYS_LONGHELP			/* #undef to save memory */
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size */

/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS	16

/* turn on command-line edit/c/auto */
#define CONFIG_CMDLINE_EDITING
#define CONFIG_COMMAND_HISTORY
#define CONFIG_AUTO_COMPLETE

#define CONFIG_ENV_SIZE		8192
#define CONFIG_ENV_IS_NOWHERE

/* SPI - enable all SPI flash types for testing purposes */
#define CONFIG_CMD_SF_TEST

#define CONFIG_I2C_EDID

/* Memory things - we don't really want a memory test */
#define CONFIG_SYS_LOAD_ADDR		0x00000000
#define CONFIG_SYS_MEMTEST_START	0x00100000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x1000)
#define CONFIG_SYS_FDT_LOAD_ADDR	        0x100

#define CONFIG_PHYSMEM

/* Size of our emulated memory */
#define CONFIG_SYS_SDRAM_BASE		0
#define CONFIG_SYS_SDRAM_SIZE		(128 << 20)
#define CONFIG_SYS_TEXT_BASE		0
#define CONFIG_SYS_MONITOR_BASE	0
#define CONFIG_NR_DRAM_BANKS		1

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600,\
					115200}

/* include default commands */
#include <config_distro_defaults.h>

#define BOOT_TARGET_DEVICES(func) \
	func(HOST, host, 1) \
	func(HOST, host, 0)

#define CONFIG_BOOTCOMMAND ""

#include <config_distro_bootcmd.h>

#define CONFIG_KEEP_SERVERADDR
#define CONFIG_UDP_CHECKSUM
#define CONFIG_TIMESTAMP
#define CONFIG_BOOTP_DNS
#define CONFIG_BOOTP_DNS2
#define CONFIG_BOOTP_SEND_HOSTNAME
#define CONFIG_BOOTP_SERVERIP
#define CONFIG_IP_DEFRAG

/* Can't boot elf images */

#define CONFIG_CMD_HASH
#define CONFIG_HASH_VERIFY
#define CONFIG_SHA1
#define CONFIG_SHA256

#define CONFIG_CMD_SANDBOX

#define CONFIG_CMD_ENV_FLAGS
#define CONFIG_CMD_ENV_CALLBACK

#define CONFIG_BOOTARGS ""

#ifndef SANDBOX_NO_SDL
#define CONFIG_SANDBOX_SDL
#endif

/* LCD and keyboard require SDL support */
#ifdef CONFIG_SANDBOX_SDL
#define CONFIG_CMD_BMP
#define LCD_BPP			LCD_COLOR16
#define CONFIG_LCD_BMP_RLE8
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_SPLASH_SCREEN_ALIGN

#define CONFIG_KEYBOARD

#define SANDBOX_SERIAL_SETTINGS		"stdin=serial,cros-ec-keyb,usbkbd\0" \
					"stdout=serial,vidconsole\0" \
					"stderr=serial,vidconsole\0"
#else
#define SANDBOX_SERIAL_SETTINGS		"stdin=serial\0" \
					"stdout=serial,vidconsole\0" \
					"stderr=serial,vidconsole\0"
#endif

#define SANDBOX_ETH_SETTINGS		"ethaddr=00:00:11:22:33:44\0" \
					"eth1addr=00:00:11:22:33:45\0" \
					"eth3addr=00:00:11:22:33:46\0" \
					"eth5addr=00:00:11:22:33:47\0" \
					"ipaddr=1.2.3.4\0"

#define MEM_LAYOUT_ENV_SETTINGS \
	"bootm_size=0x10000000\0" \
	"kernel_addr_r=0x1000000\0" \
	"fdt_addr_r=0xc00000\0" \
	"ramdisk_addr_r=0x2000000\0" \
	"scriptaddr=0x1000\0" \
	"pxefile_addr_r=0x2000\0"

#define CONFIG_EXTRA_ENV_SETTINGS \
	SANDBOX_SERIAL_SETTINGS \
	SANDBOX_ETH_SETTINGS \
	BOOTENV \
	MEM_LAYOUT_ENV_SETTINGS

#define CONFIG_GZIP_COMPRESSED
#define CONFIG_BZIP2
#define CONFIG_LZO
#define CONFIG_LZMA

#define CONFIG_CMD_LZMADEC
#define CONFIG_CMD_DATE

#ifndef CONFIG_SPL_BUILD
#define CONFIG_CMD_IDE
#define CONFIG_SYS_IDE_MAXBUS		1
#define CONFIG_SYS_ATA_IDE0_OFFSET	0
#define CONFIG_SYS_IDE_MAXDEVICE	2
#define CONFIG_SYS_ATA_BASE_ADDR	0x100
#define CONFIG_SYS_ATA_DATA_OFFSET	0
#define CONFIG_SYS_ATA_REG_OFFSET	1
#define CONFIG_SYS_ATA_ALT_OFFSET	2
#define CONFIG_SYS_ATA_STRIDE		4
#endif

#define CONFIG_SCSI
#define CONFIG_SCSI_AHCI_PLAT
#define CONFIG_SYS_SCSI_MAX_DEVICE	2
#define CONFIG_SYS_SCSI_MAX_SCSI_ID	8
#define CONFIG_SYS_SCSI_MAX_LUN		4

#define CONFIG_CMD_SATA
#define CONFIG_SYS_SATA_MAX_DEVICE	2

#define CONFIG_SYSTEMACE
#define CONFIG_SYS_SYSTEMACE_WIDTH	16
#define CONFIG_SYS_SYSTEMACE_BASE	0

#endif
