/*
 * (C) Copyright 2000-2014
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
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

#define CONFIG_MPC866		1	/* This is a MPC866 CPU		*/
#define CONFIG_TQM866M		1	/* ...on a TQM8xxM module	*/

#define	CONFIG_SYS_TEXT_BASE	0x40000000

#define CONFIG_8xx_OSCLK		10000000	/*  10 MHz - PLL input clock	*/
#define CONFIG_SYS_8xx_CPUCLK_MIN		15000000	/*  15 MHz - CPU minimum clock	*/
#define CONFIG_SYS_8xx_CPUCLK_MAX		133000000	/* 133 MHz - CPU maximum clock	*/
#define CONFIG_8xx_CPUCLK_DEFAULT	50000000	/*  50 MHz - CPU default clock	*/
						/* (it will be used if there is no	*/
						/* 'cpuclk' variable with valid value)	*/

#undef CONFIG_SYS_MEASURE_CPUCLK			/* Measure real cpu clock	*/
						/* (function measure_gclk()	*/
						/* will be called)		*/
#ifdef CONFIG_SYS_MEASURE_CPUCLK
#define CONFIG_SYS_8XX_XIN		10000000	/* measure_gclk() needs this	*/
#endif

#define CONFIG_8xx_CONS_SMC1	1	/* Console is on SMC1		*/
#define CONFIG_SYS_SMC_RXBUFLEN	128
#define CONFIG_SYS_MAXIDLE	10

#define CONFIG_BOOTCOUNT_LIMIT


#define CONFIG_BOARD_TYPES	1	/* support board types		*/

#define CONFIG_PREBOOT	"echo;" \
	"echo Type \\\"run flash_nfs\\\" to mount root filesystem over NFS;" \
	"echo"

#undef	CONFIG_BOOTARGS

#define CONFIG_EXTRA_ENV_SETTINGS					\
	"netdev=eth0\0"							\
	"nfsargs=setenv bootargs root=/dev/nfs rw "			\
		"nfsroot=${serverip}:${rootpath}\0"			\
	"ramargs=setenv bootargs root=/dev/ram rw\0"			\
	"addip=setenv bootargs ${bootargs} "				\
		"ip=${ipaddr}:${serverip}:${gatewayip}:${netmask}"	\
		":${hostname}:${netdev}:off panic=1\0"			\
	"flash_nfs=run nfsargs addip;"					\
		"bootm ${kernel_addr}\0"				\
	"flash_self=run ramargs addip;"					\
		"bootm ${kernel_addr} ${ramdisk_addr}\0"		\
	"net_nfs=tftp 200000 ${bootfile};run nfsargs addip;bootm\0"	\
	"rootpath=/opt/eldk/ppc_8xx\0"					\
	"hostname=TQM866M\0"						\
	"bootfile=TQM866M/uImage\0"					\
	"fdt_addr=400C0000\0"						\
	"kernel_addr=40100000\0"					\
	"ramdisk_addr=40280000\0"					\
	"u-boot=TQM866M/u-image.bin\0"					\
	"load=tftp 200000 ${u-boot}\0"					\
	"update=prot off 40000000 +${filesize};"			\
		"era 40000000 +${filesize};"				\
		"cp.b 200000 40000000 ${filesize};"			\
		"sete filesize;save\0"					\
	""
#define CONFIG_BOOTCOMMAND	"run flash_self"

#define CONFIG_LOADS_ECHO	1	/* echo on for serial download	*/
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE		/* don't allow baudrate change	*/

#undef	CONFIG_WATCHDOG			/* watchdog disabled		*/

#undef	CONFIG_CAN_DRIVER		/* CAN Driver support disabled	*/

/* enable I2C and select the hardware/software driver */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_SOFT			/* I2C bit-banged */
#define CONFIG_SYS_I2C_SOFT_SPEED	93000	/* 93 kHz is supposed to work */
#define CONFIG_SYS_I2C_SOFT_SLAVE	0xFE

/*
 * Software (bit-bang) I2C driver configuration
 */
#define PB_SCL		0x00000020	/* PB 26 */
#define PB_SDA		0x00000010	/* PB 27 */

#define I2C_INIT	(immr->im_cpm.cp_pbdir |=  PB_SCL)
#define I2C_ACTIVE	(immr->im_cpm.cp_pbdir |=  PB_SDA)
#define I2C_TRISTATE	(immr->im_cpm.cp_pbdir &= ~PB_SDA)
#define I2C_READ	((immr->im_cpm.cp_pbdat & PB_SDA) != 0)
#define I2C_SDA(bit)	if(bit) immr->im_cpm.cp_pbdat |=  PB_SDA; \
			else	immr->im_cpm.cp_pbdat &= ~PB_SDA
#define I2C_SCL(bit)	if(bit) immr->im_cpm.cp_pbdat |=  PB_SCL; \
			else	immr->im_cpm.cp_pbdat &= ~PB_SCL
#define I2C_DELAY	udelay(2)	/* 1/4 I2C clock duration */

#define CONFIG_SYS_I2C_EEPROM_ADDR	0x50		/* EEPROM AT24C256	*/
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2		/* two byte address	*/
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	4
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10	/* and takes up to 10 msec */

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE

#undef CONFIG_RTC_MPC8xx		/* MPC866 does not support RTC	*/

#define	CONFIG_TIMESTAMP		/* but print image timestmps	*/

/*
 * Command line configuration.
 */
#define CONFIG_CMD_IDE
#define CONFIG_CMD_JFFS2

#define CONFIG_NETCONSOLE

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP			/* undef to save memory		*/

#define CONFIG_CMDLINE_EDITING	1	/* add command line history	*/

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size	*/
#else
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size	*/
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16) /* Print Buffer Size */
#define CONFIG_SYS_MAXARGS		16	/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x0400000	/* memtest works on	*/
#define CONFIG_SYS_MEMTEST_END		0x0C00000	/* 4 ... 12 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x100000	/* default load address */

/*
 * Low Level Configuration Settings
 * (address mappings, register initial values, etc.)
 * You should know what you are doing if you make changes here.
 */
/*-----------------------------------------------------------------------
 * Internal Memory Mapped Register
 */
#define CONFIG_SYS_IMMR		0xFFF00000

/*-----------------------------------------------------------------------
 * Definitions for initial stack pointer and data area (in DPRAM)
 */
#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_SIZE	0x2F00	/* Size of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

/*-----------------------------------------------------------------------
 * Start addresses for the final memory configuration
 * (Set up by the startup code)
 * Please note that CONFIG_SYS_SDRAM_BASE _must_ start at 0
 */
#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0x40000000
#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_MALLOC_LEN		(256 << 10)	/* Reserve 256 kB for malloc()	*/

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 8 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

/*-----------------------------------------------------------------------
 * FLASH organization
 */
/* use CFI flash driver */
#define CONFIG_SYS_FLASH_CFI		1	/* Flash is CFI conformant */
#define CONFIG_FLASH_CFI_DRIVER	1	/* Use the common driver */
#define CONFIG_SYS_FLASH_BANKS_LIST	{ CONFIG_SYS_FLASH_BASE }
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE	1
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max number of memory banks */
#define CONFIG_SYS_MAX_FLASH_SECT	256	/* max number of sectors on one chip */

#define CONFIG_ENV_IS_IN_FLASH	1
#define CONFIG_ENV_OFFSET		0x40000 /*   Offset   of Environment Sector	*/
#define CONFIG_ENV_SIZE		0x08000 /* Total Size of Environment Sector	*/
#define CONFIG_ENV_SECT_SIZE	0x40000 /* Total Size of Environment Sector	*/

/* Address and size of Redundant Environment Sector	*/
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET+CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE_REDUND	(CONFIG_ENV_SIZE)

#define	CONFIG_SYS_USE_PPCENV			/* Environment embedded in sect .ppcenv */

#define CONFIG_MISC_INIT_R		/* Make sure to remap flashes correctly */

/*-----------------------------------------------------------------------
 * Dynamic MTD partition support
 */
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE		/* needed for mtdparts commands */
#define CONFIG_FLASH_CFI_MTD
#define MTDIDS_DEFAULT		"nor0=TQM8xxM-0"

#define MTDPARTS_DEFAULT	"mtdparts=TQM8xxM-0:512k(u-boot),"	\
						"128k(dtb),"		\
						"1920k(kernel),"	\
						"5632(rootfs),"		\
						"4m(data)"

/*-----------------------------------------------------------------------
 * Hardware Information Block
 */
#define CONFIG_SYS_HWINFO_OFFSET	0x0003FFC0	/* offset of HW Info block */
#define CONFIG_SYS_HWINFO_SIZE		0x00000040	/* size	  of HW Info block */
#define CONFIG_SYS_HWINFO_MAGIC	0x54514D38	/* 'TQM8' */

/*-----------------------------------------------------------------------
 * Cache Configuration
 */
#define CONFIG_SYS_CACHELINE_SIZE	16	/* For all MPC8xx CPUs			*/
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CACHELINE_SHIFT	4	/* log base 2 of the above value	*/
#endif

/*-----------------------------------------------------------------------
 * SYPCR - System Protection Control				11-9
 * SYPCR can only be written once after reset!
 *-----------------------------------------------------------------------
 * Software & Bus Monitor Timer max, Bus Monitor enable, SW Watchdog freeze
 */
#if defined(CONFIG_WATCHDOG)
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | \
			 SYPCR_SWE  | SYPCR_SWRI| SYPCR_SWP)
#else
#define CONFIG_SYS_SYPCR	(SYPCR_SWTC | SYPCR_BMT | SYPCR_BME | SYPCR_SWF | SYPCR_SWP)
#endif

/*-----------------------------------------------------------------------
 * SIUMCR - SIU Module Configuration				11-6
 *-----------------------------------------------------------------------
 * PCMCIA config., multi-function pin tri-state
 */
#ifndef CONFIG_CAN_DRIVER
#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC00 | SIUMCR_DBPC00 | SIUMCR_MLRC01)
#else	/* we must activate GPL5 in the SIUMCR for CAN */
#define CONFIG_SYS_SIUMCR	(SIUMCR_DBGC11 | SIUMCR_DBPC00 | SIUMCR_MLRC01)
#endif	/* CONFIG_CAN_DRIVER */

/*-----------------------------------------------------------------------
 * TBSCR - Time Base Status and Control				11-26
 *-----------------------------------------------------------------------
 * Clear Reference Interrupt Status, Timebase freezing enabled
 */
#define CONFIG_SYS_TBSCR	(TBSCR_REFA | TBSCR_REFB | TBSCR_TBF)

/*-----------------------------------------------------------------------
 * PISCR - Periodic Interrupt Status and Control		11-31
 *-----------------------------------------------------------------------
 * Clear Periodic Interrupt Status, Interrupt Timer freezing enabled
 */
#define CONFIG_SYS_PISCR	(PISCR_PS | PISCR_PITF)

/*-----------------------------------------------------------------------
 * SCCR - System Clock and reset Control Register		15-27
 *-----------------------------------------------------------------------
 * Set clock output, timebase and RTC source and divider,
 * power management and some other internal clocks
 */
#define SCCR_MASK	SCCR_EBDF11
#define CONFIG_SYS_SCCR	(SCCR_COM00   | SCCR_DFSYNC00 | SCCR_DFBRG00  | \
			 SCCR_DFNL000 | SCCR_DFNH000  | SCCR_DFLCD000 | \
			 SCCR_DFALCD00)

/*-----------------------------------------------------------------------
 * PCMCIA stuff
 *-----------------------------------------------------------------------
 *
 */
#define CONFIG_SYS_PCMCIA_MEM_ADDR	(0xE0000000)
#define CONFIG_SYS_PCMCIA_MEM_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_DMA_ADDR	(0xE4000000)
#define CONFIG_SYS_PCMCIA_DMA_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_ATTRB_ADDR	(0xE8000000)
#define CONFIG_SYS_PCMCIA_ATTRB_SIZE	( 64 << 20 )
#define CONFIG_SYS_PCMCIA_IO_ADDR	(0xEC000000)
#define CONFIG_SYS_PCMCIA_IO_SIZE	( 64 << 20 )

/*-----------------------------------------------------------------------
 * IDE/ATA stuff (Supports IDE harddisk on PCMCIA Adapter)
 *-----------------------------------------------------------------------
 */

#define CONFIG_IDE_PREINIT	1	/* Use preinit IDE hook */
#define CONFIG_IDE_8xx_PCCARD	1	/* Use IDE with PC Card Adapter */

#undef	CONFIG_IDE_8xx_DIRECT		/* Direct IDE	 not supported	*/
#undef	CONFIG_IDE_LED			/* LED	 for ide not supported	*/
#undef	CONFIG_IDE_RESET		/* reset for ide not supported	*/

#define CONFIG_SYS_IDE_MAXBUS		1	/* max. 1 IDE bus		*/
#define CONFIG_SYS_IDE_MAXDEVICE	1	/* max. 1 drive per IDE bus	*/

#define CONFIG_SYS_ATA_IDE0_OFFSET	0x0000

#define CONFIG_SYS_ATA_BASE_ADDR	CONFIG_SYS_PCMCIA_MEM_ADDR

/* Offset for data I/O			*/
#define CONFIG_SYS_ATA_DATA_OFFSET	(CONFIG_SYS_PCMCIA_MEM_SIZE + 0x320)

/* Offset for normal register accesses	*/
#define CONFIG_SYS_ATA_REG_OFFSET	(2 * CONFIG_SYS_PCMCIA_MEM_SIZE + 0x320)

/* Offset for alternate registers	*/
#define CONFIG_SYS_ATA_ALT_OFFSET	0x0100

/*-----------------------------------------------------------------------
 *
 *-----------------------------------------------------------------------
 *
 */
#define CONFIG_SYS_DER 0

/*
 * Init Memory Controller:
 *
 * BR0/1 and OR0/1 (FLASH)
 */

#define FLASH_BASE0_PRELIM	0x40000000	/* FLASH bank #0	*/
#define FLASH_BASE1_PRELIM	0x60000000	/* FLASH bank #0	*/

/* used to re-map FLASH both when starting from SRAM or FLASH:
 * restrict access enough to keep SRAM working (if any)
 * but not too much to meddle with FLASH accesses
 */
#define CONFIG_SYS_REMAP_OR_AM		0x80000000	/* OR addr mask */
#define CONFIG_SYS_PRELIM_OR_AM	0xE0000000	/* OR addr mask */

/*
 * FLASH timing: Default value of OR0 after reset
 */
#define CONFIG_SYS_OR_TIMING_FLASH	(OR_CSNT_SAM | OR_ACS_MSK | OR_BI | \
				 OR_SCY_15_CLK | OR_TRLX)

#define CONFIG_SYS_OR0_REMAP	(CONFIG_SYS_REMAP_OR_AM  | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_OR0_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_FLASH)
#define CONFIG_SYS_BR0_PRELIM	((FLASH_BASE0_PRELIM & BR_BA_MSK) | BR_V )

#define CONFIG_SYS_OR1_REMAP	CONFIG_SYS_OR0_REMAP
#define CONFIG_SYS_OR1_PRELIM	CONFIG_SYS_OR0_PRELIM
#define CONFIG_SYS_BR1_PRELIM	((FLASH_BASE1_PRELIM & BR_BA_MSK) | BR_V )

/*
 * BR2/3 and OR2/3 (SDRAM)
 *
 */
#define SDRAM_BASE2_PRELIM	0x00000000	/* SDRAM bank #0	*/
#define SDRAM_BASE3_PRELIM	0x20000000	/* SDRAM bank #1	*/
#define SDRAM_MAX_SIZE		(256 << 20)	/* max 256 MB per bank	*/

/* SDRAM timing: Multiplexed addresses, GPL5 output to GPL5_A (don't care)	*/
#define CONFIG_SYS_OR_TIMING_SDRAM	0x00000A00

#define CONFIG_SYS_OR2_PRELIM	(CONFIG_SYS_PRELIM_OR_AM | CONFIG_SYS_OR_TIMING_SDRAM )
#define CONFIG_SYS_BR2_PRELIM	((SDRAM_BASE2_PRELIM & BR_BA_MSK) | BR_MS_UPMA | BR_V )

#ifndef CONFIG_CAN_DRIVER
#define CONFIG_SYS_OR3_PRELIM	CONFIG_SYS_OR2_PRELIM
#define CONFIG_SYS_BR3_PRELIM	((SDRAM_BASE3_PRELIM & BR_BA_MSK) | BR_MS_UPMA | BR_V )
#else	/* CAN uses CS3#, so we can have only one SDRAM bank anyway */
#define CONFIG_SYS_CAN_BASE		0xC0000000	/* CAN mapped at 0xC0000000	*/
#define CONFIG_SYS_CAN_OR_AM		0xFFFF8000	/* 32 kB address mask		*/
#define CONFIG_SYS_OR3_CAN		(CONFIG_SYS_CAN_OR_AM | OR_G5LA | OR_BI)
#define CONFIG_SYS_BR3_CAN		((CONFIG_SYS_CAN_BASE & BR_BA_MSK) | \
					BR_PS_8 | BR_MS_UPMB | BR_V )
#endif	/* CONFIG_CAN_DRIVER */

/*
 * 4096	Rows from SDRAM example configuration
 * 1000	factor s -> ms
 * 64	PTP (pre-divider from MPTPR) from SDRAM example configuration
 * 4	Number of refresh cycles per period
 * 64	Refresh cycle in ms per number of rows
 */
#define CONFIG_SYS_PTA_PER_CLK	((4096 * 64 * 1000) / (4 * 64))

/*
 * Periodic timer (MAMR[PTx]) for 4 * 7.8 us refresh (= 31.2 us per quad)
 *
 *                        CPUclock(MHz) * 31.2
 * CONFIG_SYS_MAMR_PTA = -----------------------------------     with DFBRG = 0
 *                2^(2*SCCR[DFBRG]) * MPTPR_PTP_DIV16
 *
 * CPU clock =  15 MHz:  CONFIG_SYS_MAMR_PTA =  29   ->  4 * 7.73 us
 * CPU clock =  50 MHz:  CONFIG_SYS_MAMR_PTA =  97   ->  4 * 7.76 us
 * CPU clock =  66 MHz:  CONFIG_SYS_MAMR_PTA = 128   ->  4 * 7.75 us
 * CPU clock = 133 MHz:  CONFIG_SYS_MAMR_PTA = 255   ->  4 * 7.67 us
 *
 * Value 97 is for 4 * 7.8 us at 50 MHz. So the refresh cycle requirement will
 * be met also in the default configuration, i.e. if environment variable
 * 'cpuclk' is not set.
 */
#define CONFIG_SYS_MAMR_PTA		97

/*
 * Memory Periodic Timer Prescaler Register (MPTPR) values.
 */
/* 4 * 7.8 us refresh (= 31.2 us per quad) at 50 MHz and PTA = 97 */
#define CONFIG_SYS_MPTPR_2BK_4K	MPTPR_PTP_DIV16
/* 4 * 3.9 us refresh (= 15.6 us per quad) at 50 MHz and PTA = 97 */
#define CONFIG_SYS_MPTPR_2BK_8K	MPTPR_PTP_DIV8

/*
 * MAMR settings for SDRAM
 */

/* 8 column SDRAM */
#define CONFIG_SYS_MAMR_8COL	((CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)  | MAMR_PTAE	    |	\
			 MAMR_AMA_TYPE_0 | MAMR_DSA_1_CYCL | MAMR_G0CLA_A11 |	\
			 MAMR_RLFA_1X	 | MAMR_WLFA_1X	   | MAMR_TLFA_4X)
/* 9 column SDRAM */
#define CONFIG_SYS_MAMR_9COL	((CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)  | MAMR_PTAE	    |	\
			 MAMR_AMA_TYPE_1 | MAMR_DSA_1_CYCL | MAMR_G0CLA_A10 |	\
			 MAMR_RLFA_1X	 | MAMR_WLFA_1X	   | MAMR_TLFA_4X)
/* 10 column SDRAM */
#define CONFIG_SYS_MAMR_10COL	((CONFIG_SYS_MAMR_PTA << MAMR_PTA_SHIFT)  | MAMR_PTAE	    |	\
			 MAMR_AMA_TYPE_2 | MAMR_DSA_1_CYCL | MAMR_G0CLA_A9  |	\
			 MAMR_RLFA_1X	 | MAMR_WLFA_1X	   | MAMR_TLFA_4X)

#define CONFIG_SCC1_ENET
#define CONFIG_FEC_ENET
#define CONFIG_ETHPRIME		"SCC"

#define CONFIG_HWCONFIG		1

#endif	/* __CONFIG_H */
