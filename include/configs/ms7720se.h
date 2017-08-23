/*
 * Configuation settings for the Hitachi Solution Engine 7720
 *
 * Copyright (C) 2007 Yoshihiro Shimoda <shimoda.yoshihiro@renesas.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MS7720SE_H
#define __MS7720SE_H

#define CONFIG_CPU_SH7720	1
#define CONFIG_MS7720SE		1

#define CONFIG_BOOTFILE		"/boot/zImage"
#define CONFIG_LOADADDR		0x8E000000

#define CONFIG_DISPLAY_BOARDINFO
#undef  CONFIG_SHOW_BOOT_PROGRESS

/* MEMORY */
#define MS7720SE_SDRAM_BASE		0x8C000000
#define MS7720SE_FLASH_BASE_1		0xA0000000
#define MS7720SE_FLASH_BANK_SIZE	(8 * 1024 * 1024)

#define CONFIG_SYS_TEXT_BASE	0x8FFC0000
#define CONFIG_SYS_LONGHELP		/* undef to save memory	*/
#define CONFIG_SYS_PBSIZE	256	/* Buffer size for Console output */
/* List of legal baudrate settings for this board */
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200 }

/* SCIF */
#define CONFIG_CONS_SCIF0	1

#define CONFIG_SYS_MEMTEST_START	MS7720SE_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + (60 * 1024 * 1024))

#define CONFIG_SYS_SDRAM_BASE		MS7720SE_SDRAM_BASE
#define CONFIG_SYS_SDRAM_SIZE		(64 * 1024 * 1024)

#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 32 * 1024 * 1024)
#define CONFIG_SYS_MONITOR_BASE	MS7720SE_FLASH_BASE_1
#define CONFIG_SYS_MONITOR_LEN		(128 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(256 * 1024)
#define CONFIG_SYS_BOOTMAPSZ		(8 * 1024 * 1024)

/* FLASH */
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#undef  CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_SYS_FLASH_EMPTY_INFO	/* print 'E' for empty sector on flinfo */

#define CONFIG_SYS_FLASH_BASE		MS7720SE_FLASH_BASE_1

#define CONFIG_SYS_MAX_FLASH_SECT	150
#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE }

#define CONFIG_ENV_SECT_SIZE	(64 * 1024)
#define CONFIG_ENV_SIZE		CONFIG_ENV_SECT_SIZE
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN)
#define CONFIG_SYS_FLASH_ERASE_TOUT	120000
#define CONFIG_SYS_FLASH_WRITE_TOUT	500

/* Board Clock */
#define CONFIG_SYS_CLK_FREQ	33333333
#define CONFIG_SH_TMU_CLK_FREQ CONFIG_SYS_CLK_FREQ
#define CONFIG_SH_SCIF_CLK_FREQ CONFIG_SYS_CLK_FREQ
#define CONFIG_SYS_TMU_CLK_DIV		4	/* 4 (default), 16, 64, 256 or 1024 */

/* PCMCIA */
#define CONFIG_IDE_PCMCIA	1
#define CONFIG_MARUBUN_PCCARD	1
#define CONFIG_PCMCIA_SLOT_A	1
#define CONFIG_SYS_IDE_MAXDEVICE	1
#define CONFIG_SYS_MARUBUN_MRSHPC	0xb83fffe0
#define CONFIG_SYS_MARUBUN_MW1		0xb8400000
#define CONFIG_SYS_MARUBUN_MW2		0xb8500000
#define CONFIG_SYS_MARUBUN_IO		0xb8600000

#define CONFIG_SYS_PIO_MODE		1
#define CONFIG_SYS_IDE_MAXBUS		1
#define CONFIG_SYS_ATA_BASE_ADDR	CONFIG_SYS_MARUBUN_IO	/* base address */
#define CONFIG_SYS_ATA_IDE0_OFFSET	0x01F0		/* ide0 offste */
#define CONFIG_SYS_ATA_DATA_OFFSET	0		/* data reg offset */
#define CONFIG_SYS_ATA_REG_OFFSET	0		/* reg offset */
#define CONFIG_SYS_ATA_ALT_OFFSET	0x200		/* alternate register offset */
#define CONFIG_IDE_SWAP_IO

#endif	/* __MS7720SE_H */
