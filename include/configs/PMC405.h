/*
 * (C) Copyright 2001-2003
 * Stefan Roese, esd gmbh germany, stefan.roese@esd-electronics.com
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * board/config.h - configuration options, board specific
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */

#define CONFIG_405GP		1	/* This is a PPC405 CPU		*/
#define CONFIG_4xx		1	/* ...member of PPC4xx family   */
#define CONFIG_PMC405		1	/* ...on a PMC405 board 	*/

#define CONFIG_BOARD_PRE_INIT   1       /* call board_pre_init()        */
#define CONFIG_MISC_INIT_R      1       /* call misc_init_r()           */

#define CONFIG_SYS_CLK_FREQ     33333333 /* external frequency to pll   */

#define CONFIG_BAUDRATE		9600
#define CONFIG_BOOTDELAY	3	/* autoboot after 3 seconds	*/

#undef	CONFIG_BOOTARGS
#define CONFIG_RAMBOOTCOMMAND							\
	"setenv bootargs root=/dev/ram rw nfsroot=$(serverip):$(rootpath) "	\
	"ip=$(ipaddr):$(serverip):$(gatewayip):$(netmask):$(hostname)::off;"	\
	"bootm ffc00000 ffca0000"
#define CONFIG_NFSBOOTCOMMAND							\
	"setenv bootargs root=/dev/nfs rw nfsroot=$(serverip):$(rootpath) "	\
	"ip=$(ipaddr):$(serverip):$(gatewayip):$(netmask):$(hostname)::off;"	\
	"bootm ffc00000"
#define CONFIG_BOOTCOMMAND CONFIG_RAMBOOTCOMMAND

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#define CFG_LOADS_BAUD_CHANGE	1	/* allow baudrate change	*/

#define CONFIG_MII		1	/* MII PHY management		*/
#define	CONFIG_PHY_ADDR		0	/* PHY address			*/

#define CONFIG_COMMANDS	      ( CONFIG_CMD_DFL	| \
				CFG_CMD_PCI	| \
				CFG_CMD_IRQ	| \
				CFG_CMD_ELF	| \
				CFG_CMD_DATE	| \
				CFG_CMD_JFFS2	| \
				CFG_CMD_MII	| \
				CFG_CMD_I2C	| \
				CFG_CMD_EEPROM  )

#define CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION

/* this must be included AFTER the definition of CONFIG_COMMANDS (if any) */
#include <cmd_confdefs.h>

#undef  CONFIG_WATCHDOG			/* watchdog disabled		*/

#define CONFIG_RTC_MC146818             /* DS1685 is MC146818 compatible*/
#define CFG_RTC_REG_BASE_ADDR	 0xF0000300 /* RTC Base Address         */

#define	CONFIG_SDRAM_BANK0	1	/* init onboard SDRAM bank 0	*/

/*
 * Miscellaneous configurable options
 */
#define CFG_LONGHELP			/* undef to save memory		*/
#define CFG_PROMPT	"=> "		/* Monitor Command Prompt	*/

#undef	CFG_HUSH_PARSER			/* use "hush" command parser	*/
#ifdef	CFG_HUSH_PARSER
#define	CFG_PROMPT_HUSH_PS2	"> "
#endif

#if (CONFIG_COMMANDS & CFG_CMD_KGDB)
#define	CFG_CBSIZE	1024		/* Console I/O Buffer Size	*/
#else
#define	CFG_CBSIZE	256		/* Console I/O Buffer Size	*/
#endif
#define CFG_PBSIZE (CFG_CBSIZE+sizeof(CFG_PROMPT)+16) /* Print Buffer Size */
#define CFG_MAXARGS	16		/* max number of command args	*/
#define CFG_BARGSIZE	CFG_CBSIZE	/* Boot Argument Buffer Size	*/

#define CFG_DEVICE_NULLDEV      1       /* include nulldev device       */

#define CFG_CONSOLE_INFO_QUIET  1       /* don't print console @ startup*/

#define CFG_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CFG_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#undef  CFG_EXT_SERIAL_CLOCK           /* no external serial clock used */
#define CFG_IGNORE_405_UART_ERRATA_59   /* ignore ppc405gp errata #59   */
#define CFG_BASE_BAUD       691200

/* The following table includes the supported baudrates */
#define CFG_BAUDRATE_TABLE      \
        { 300, 600, 1200, 2400, 4800, 9600, 19200, 38400,     \
         57600, 115200, 230400, 460800, 921600 }

#define CFG_LOAD_ADDR	0x100000	/* default load address */
#define CFG_EXTBDINFO	1		/* To use extended board_into (bd_t) */

#define	CFG_HZ		1000		/* decrementer freq: 1 ms ticks	*/

#define CONFIG_ZERO_BOOTDELAY_CHECK	/* check for keypress on bootdelay==0 */

/*-----------------------------------------------------------------------
 * PCI stuff
 *-----------------------------------------------------------------------
 */
#define PCI_HOST_ADAPTER 0              /* configure as pci adapter     */
#define PCI_HOST_FORCE  1               /* configure as pci host        */
#define PCI_HOST_AUTO   2               /* detected via arbiter enable  */

#define CONFIG_PCI			/* include pci support	        */
#define CONFIG_PCI_HOST	PCI_HOST_FORCE  /* select pci host function     */
#define CONFIG_PCI_PNP			/* do pci plug-and-play         */
                                        /* resource configuration       */

#undef CONFIG_PCI_SCAN_SHOW             /* print pci devices @ startup  */

#define CFG_PCI_SUBSYS_VENDORID 0x12FE  /* PCI Vendor ID: esd gmbh      */
#define CFG_PCI_SUBSYS_DEVICEID 0x0408  /* PCI Device ID: PMC-405       */
#define CFG_PCI_CLASSCODE       0x0b20  /* PCI Class Code: Processor/PPC*/
#define CFG_PCI_PTM1LA  0x00000000      /* point to sdram               */
#define CFG_PCI_PTM1MS  0xfc000001      /* 64MB, enable hard-wired to 1 */
#define CFG_PCI_PTM1PCI 0x00000000      /* Host: use this pci address   */
#define CFG_PCI_PTM2LA  0xffc00000      /* point to flash               */
#define CFG_PCI_PTM2MS  0xffc00001      /* 4MB, enable                  */
#define CFG_PCI_PTM2PCI 0x04000000      /* Host: use this pci address   */

/*-----------------------------------------------------------------------
 * Start addresses for the final memory configuration
 * (Set up by the startup code)
 * Please note that CFG_SDRAM_BASE _must_ start at 0
 */
#define CFG_SDRAM_BASE		0x00000000
#define CFG_MONITOR_BASE	0xFFFC0000
#define CFG_MONITOR_LEN		(256 * 1024)	/* Reserve 256 kB for Monitor	*/
#define CFG_MALLOC_LEN		(128 * 1024)	/* Reserve 128 kB for malloc()	*/

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CFG_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

/*-----------------------------------------------------------------------
 * FLASH organization
 */
#define CFG_FLASH_CFI		1	/* Flash is CFI conformant		*/
#define CFG_MAX_FLASH_SECT	128	/* max number of sectors on one chip	*/
#define CFG_MAX_FLASH_BANKS	2	/* max number of memory banks		*/
#undef CFG_FLASH_PROTECTION		/* don't use hardware protection	*/
#define CFG_FLASH_USE_BUFFER_WRITE 1	/* use buffered writes (20x faster)	*/
#define CFG_FLASH_BASE		0xFE000000
#define CFG_FLASH_INCREMENT	0x01000000

#define CFG_FLASH_EMPTY_INFO            /* print 'E' for empty sector on flinfo */

#define CFG_JFFS2_FIRST_BANK    0           /* use for JFFS2 */
#define CFG_JFFS2_NUM_BANKS     1           /* ! second bank contains u-boot    */

/*-----------------------------------------------------------------------
 * Environment Variable setup
 */
#define CFG_ENV_IS_IN_EEPROM    1       /* use EEPROM for environment vars */
#define CFG_ENV_OFFSET          0x000   /* environment starts at the beginning of the EEPROM */
#define CFG_ENV_SIZE            0x800   /* 2048 bytes may be used for env vars*/
                                   /* total size of a CAT24WC16 is 2048 bytes */

#define CFG_NVRAM_BASE_ADDR	0xF0000500		/* NVRAM base address	*/
#define CFG_NVRAM_SIZE		242		        /* NVRAM size		*/

/*-----------------------------------------------------------------------
 * I2C EEPROM (CAT24WC16) for environment
 */
#define CONFIG_HARD_I2C			/* I2c with hardware support */
#define CFG_I2C_SPEED		400000	/* I2C speed and slave address */
#define CFG_I2C_SLAVE		0x7F

#define CFG_I2C_EEPROM_ADDR	0x50	/* EEPROM CAT28WC08		*/
#define CFG_I2C_EEPROM_ADDR_LEN	1	/* Bytes of address		*/
/* mask of address bits that overflow into the "EEPROM chip address"    */
#define CFG_I2C_EEPROM_ADDR_OVERFLOW	0x07
#define CFG_EEPROM_PAGE_WRITE_BITS 4	/* The Catalyst CAT24WC08 has	*/
					/* 16 byte page write mode using*/
					/* last	4 bits of the address	*/
#define CFG_EEPROM_PAGE_WRITE_DELAY_MS	10   /* and takes up to 10 msec */
#define CFG_EEPROM_PAGE_WRITE_ENABLE

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CFG_DCACHE_SIZE		16384	/* For IBM 405 CPUs, older 405 ppc's    */
                                        /* have only 8kB, 16kB is save here     */
#define CFG_CACHELINE_SIZE	32	/* ...			*/
#if (CONFIG_COMMANDS & CFG_CMD_KGDB)
#define CFG_CACHELINE_SHIFT	5	/* log base 2 of the above value	*/
#endif

/*-----------------------------------------------------------------------
 * External Bus Controller (EBC) Setup
 */
#define FLASH0_BA       0xFF000000          /* FLASH 0 Base Address             */
#define FLASH1_BA       0xFE000000          /* FLASH 1 Base Address             */
#define CAN_BA          0xF0000000          /* CAN Base Address                 */
#define RTC_BA          0xF0000500          /* RTC Base Address                 */
#define CF_BA           0xF0100000          /* CompactFlash Base Address        */

/* Memory Bank 0 (Flash Bank 0) initialization                                  */
#define CFG_EBC_PB0AP   0x92015480
#define CFG_EBC_PB0CR   FLASH0_BA | 0x9A000 /* BAS=0xFF0,BS=16MB,BU=R/W,BW=16bit*/

/* Memory Bank 1 (Flash Bank 1) initialization                                  */
#define CFG_EBC_PB1AP   0x92015480
#define CFG_EBC_PB1CR   FLASH1_BA | 0x9A000 /* BAS=0xFE0,BS=16MB,BU=R/W,BW=16bit*/

/* Memory Bank 2 (CAN0, 1, RTC) initialization                                  */
#define CFG_EBC_PB2AP   0x03000040   /* TWT=6,TH=0,CSN=0,OEN=0,WBN=0,WBF=0      */
#define CFG_EBC_PB2CR   CAN_BA | 0x18000    /* BAS=0xF00,BS=1MB,BU=R/W,BW=8bit  */

/* Memory Bank 3 (CompactFlash IDE, FPGA internal) initialization               */
#define CFG_EBC_PB3AP   0x010059C0   /* BWT=2,WBN=1,WBF=1,TH=1,RE=1,SOR=1,BEM=1 */
#define CFG_EBC_PB3CR   CF_BA | 0x1A000     /* BAS=0xF01,BS=1MB,BU=R/W,BW=16bit */

/*-----------------------------------------------------------------------
 * Definitions for initial stack pointer and data area (in data cache)
 */

/* use on chip memory ( OCM ) for temperary stack until sdram is tested */
#define CFG_TEMP_STACK_OCM      1

/* On Chip Memory location */
#define CFG_OCM_DATA_ADDR	0xF8000000
#define CFG_OCM_DATA_SIZE	0x1000

#define CFG_INIT_RAM_ADDR	CFG_OCM_DATA_ADDR /* inside of SDRAM		*/
#define CFG_INIT_RAM_END	CFG_OCM_DATA_SIZE /* End of used area in RAM	*/
#define CFG_GBL_DATA_SIZE      128  /* size in bytes reserved for initial data */
#define CFG_GBL_DATA_OFFSET    (CFG_INIT_RAM_END - CFG_GBL_DATA_SIZE)
#define CFG_INIT_SP_OFFSET      CFG_GBL_DATA_OFFSET

/*
 * Internal Definitions
 *
 * Boot Flags
 */
#define BOOTFLAG_COLD	0x01		/* Normal Power-On: Boot from FLASH	*/
#define BOOTFLAG_WARM	0x02		/* Software reboot			*/

#endif	/* __CONFIG_H */
