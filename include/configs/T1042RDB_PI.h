/*
 * Copyright 2013 Freescale Semiconductor, Inc.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * T1042RDB_PI board configuration file
 */
#define CONFIG_T104xRDB
#define CONFIG_T1042RDB_PI
#define CONFIG_PHYS_64BIT

#ifdef CONFIG_RAMBOOT_PBL
#define CONFIG_RAMBOOT_TEXT_BASE	CONFIG_SYS_TEXT_BASE
#define CONFIG_RESET_VECTOR_ADDRESS	0xfffffffc
#endif

/* High Level Configuration Options */
#define CONFIG_BOOKE
#define CONFIG_E500			/* BOOKE e500 family */
#define CONFIG_E500MC			/* BOOKE e500mc family */
#define CONFIG_SYS_BOOK3E_HV		/* Category E.HV supported */
#define CONFIG_MPC85xx			/* MPC85xx/PQ3 platform */
#define CONFIG_MP			/* support multiple processors */

#ifndef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE	0xeff40000
#endif

#ifndef CONFIG_RESET_VECTOR_ADDRESS
#define CONFIG_RESET_VECTOR_ADDRESS	0xeffffffc
#endif

#define CONFIG_SYS_FSL_CPC		/* Corenet Platform Cache */
#define CONFIG_SYS_NUM_CPC		CONFIG_NUM_DDR_CONTROLLERS
#define CONFIG_FSL_IFC			/* Enable IFC Support */
#define CONFIG_PCI			/* Enable PCI/PCIE */
#define CONFIG_PCI_INDIRECT_BRIDGE
#define CONFIG_PCIE1			/* PCIE controler 1 */
#define CONFIG_PCIE2			/* PCIE controler 2 */
#define CONFIG_PCIE3			/* PCIE controler 3 */
#define CONFIG_PCIE4			/* PCIE controler 4 */

#define CONFIG_FSL_PCI_INIT		/* Use common FSL init code */
#define CONFIG_SYS_PCI_64BIT		/* enable 64-bit PCI resources */

#define CONFIG_FSL_LAW			/* Use common FSL init code */

#define CONFIG_ENV_OVERWRITE

#ifdef CONFIG_SYS_NO_FLASH
#define CONFIG_ENV_IS_NOWHERE
#else
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#endif

#ifndef CONFIG_SYS_NO_FLASH
#if defined(CONFIG_SPIFLASH)
#define CONFIG_SYS_EXTRA_ENV_RELOC
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SPI_BUS              0
#define CONFIG_ENV_SPI_CS               0
#define CONFIG_ENV_SPI_MAX_HZ           10000000
#define CONFIG_ENV_SPI_MODE             0
#define CONFIG_ENV_SIZE                 0x2000          /* 8KB */
#define CONFIG_ENV_OFFSET               0x100000        /* 1MB */
#define CONFIG_ENV_SECT_SIZE            0x10000
#elif defined(CONFIG_SDCARD)
#define CONFIG_SYS_EXTRA_ENV_RELOC
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV          0
#define CONFIG_ENV_SIZE			0x2000
#define CONFIG_ENV_OFFSET		(512 * 1658)
#elif defined(CONFIG_NAND)
#define CONFIG_SYS_EXTRA_ENV_RELOC
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_SIZE			CONFIG_SYS_NAND_BLOCK_SIZE
#define CONFIG_ENV_OFFSET		(3 * CONFIG_SYS_NAND_BLOCK_SIZE)
#else
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_ENV_SECT_SIZE	0x20000 /* 128K (one sector) */
#endif
#else /* CONFIG_SYS_NO_FLASH */
#define CONFIG_ENV_SIZE                0x2000
#define CONFIG_ENV_SECT_SIZE   0x20000 /* 128K (one sector) */
#endif

#define CONFIG_SYS_CLK_FREQ	100000000
#define CONFIG_DDR_CLK_FREQ	66666666

/*
 * These can be toggled for performance analysis, otherwise use default.
 */
#define CONFIG_SYS_CACHE_STASHING
#define CONFIG_BACKSIDE_L2_CACHE
#define CONFIG_SYS_INIT_L2CSR0		L2CSR0_L2E
#define CONFIG_BTB			/* toggle branch predition */
#define CONFIG_DDR_ECC
#ifdef CONFIG_DDR_ECC
#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER
#define CONFIG_MEM_INIT_VALUE		0xdeadbeef
#endif

#define CONFIG_ENABLE_36BIT_PHYS

#define CONFIG_ADDR_MAP
#define CONFIG_SYS_NUM_ADDR_MAP		64	/* number of TLB1 entries */

#define CONFIG_SYS_MEMTEST_START	0x00200000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x00400000
#define CONFIG_SYS_ALT_MEMTEST
#define CONFIG_PANIC_HANG	/* do not reset board on panic */

/*
 *  Config the L3 Cache as L3 SRAM
 */
#define CONFIG_SYS_INIT_L3_ADDR		0xFFFC0000

#define CONFIG_SYS_DCSRBAR		0xf0000000
#define CONFIG_SYS_DCSRBAR_PHYS		0xf00000000ull

/*
 * DDR Setup
 */
#define CONFIG_VERY_BIG_RAM
#define CONFIG_SYS_DDR_SDRAM_BASE	0x00000000
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE

/* CONFIG_NUM_DDR_CONTROLLERS is defined in include/asm/config_mpc85xx.h */
#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	(4 * CONFIG_DIMM_SLOTS_PER_CTLR)

#define CONFIG_DDR_SPD
#define CONFIG_SYS_DDR_RAW_TIMING
#define CONFIG_SYS_FSL_DDR3

#define CONFIG_SYS_SPD_BUS_NUM	0
#define SPD_EEPROM_ADDRESS	0x51

#define CONFIG_SYS_SDRAM_SIZE	4096	/* for fixed parameter use */

/*
 * IFC Definitions
 */
#define CONFIG_SYS_FLASH_BASE	0xe8000000
#define CONFIG_SYS_FLASH_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_FLASH_BASE)

#define CONFIG_SYS_NOR_CSPR_EXT	(0xf)
#define CONFIG_SYS_NOR_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE) | \
				CSPR_PORT_SIZE_16 | \
				CSPR_MSEL_NOR | \
				CSPR_V)
#define CONFIG_SYS_NOR_AMASK	IFC_AMASK(128*1024*1024)
/* NOR Flash Timing Params */
#define CONFIG_SYS_NOR_CSOR	CSOR_NAND_TRHZ_80
#define CONFIG_SYS_NOR_FTIM0	(FTIM0_NOR_TACSE(0x4) | \
				FTIM0_NOR_TEADC(0x5) | \
				FTIM0_NOR_TEAHC(0x5))
#define CONFIG_SYS_NOR_FTIM1	(FTIM1_NOR_TACO(0x35) | \
				FTIM1_NOR_TRAD_NOR(0x1A) |\
				FTIM1_NOR_TSEQRAD_NOR(0x13))
#define CONFIG_SYS_NOR_FTIM2	(FTIM2_NOR_TCS(0x4) | \
				FTIM2_NOR_TCH(0x4) | \
				FTIM2_NOR_TWPH(0x0E) | \
				FTIM2_NOR_TWP(0x1c))
#define CONFIG_SYS_NOR_FTIM3	0x0

#define CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_FLASH_SHOW_PROGRESS	45 /* count down from 45/5: 9..1 */

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* number of banks */
#define CONFIG_SYS_MAX_FLASH_SECT	1024	/* sectors per device */
#define CONFIG_SYS_FLASH_ERASE_TOUT	60000	/* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (ms) */

#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_BANKS_LIST	{CONFIG_SYS_FLASH_BASE_PHYS}

/* CPLD on IFC */
#define CONFIG_SYS_CPLD_BASE	0xffdf0000
#define CONFIG_SYS_CPLD_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_CPLD_BASE)
#define CONFIG_SYS_CSPR2	(CSPR_PHYS_ADDR(CONFIG_SYS_CPLD_BASE_PHYS) \
				| CSPR_PORT_SIZE_8 \
				| CSPR_MSEL_GPCM \
				| CSPR_V)
#define CONFIG_SYS_AMASK2	IFC_AMASK(64*1024)
#define CONFIG_SYS_CSOR2	0x0
/* CPLD Timing parameters for IFC CS2 */
#define CONFIG_SYS_CS2_FTIM0		(FTIM0_GPCM_TACSE(0x0e) | \
					FTIM0_GPCM_TEADC(0x0e) | \
					FTIM0_GPCM_TEAHC(0x0e))
#define CONFIG_SYS_CS2_FTIM1		(FTIM1_GPCM_TACO(0x0e) | \
					FTIM1_GPCM_TRAD(0x1f))
#define CONFIG_SYS_CS2_FTIM2		(FTIM2_GPCM_TCS(0x0e) | \
					FTIM2_GPCM_TCH(0x0) | \
					FTIM2_GPCM_TWP(0x1f))
#define CONFIG_SYS_CS2_FTIM3		0x0

/* NAND Flash on IFC */
#define CONFIG_NAND_FSL_IFC
#define CONFIG_SYS_NAND_BASE		0xff800000
#define CONFIG_SYS_NAND_BASE_PHYS	(0xf00000000ull | CONFIG_SYS_NAND_BASE)

#define CONFIG_SYS_NAND_CSPR_EXT	(0xf)
#define CONFIG_SYS_NAND_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS) \
				| CSPR_PORT_SIZE_8 /* Port Size = 8 bit */ \
				| CSPR_MSEL_NAND	/* MSEL = NAND */ \
				| CSPR_V)
#define CONFIG_SYS_NAND_AMASK	IFC_AMASK(64*1024)

#define CONFIG_SYS_NAND_CSOR    (CSOR_NAND_ECC_ENC_EN   /* ECC on encode */ \
				| CSOR_NAND_ECC_DEC_EN  /* ECC on decode */ \
				| CSOR_NAND_ECC_MODE_4  /* 4-bit ECC */ \
				| CSOR_NAND_RAL_3	/* RAL = 3Byes */ \
				| CSOR_NAND_PGS_4K	/* Page Size = 4K */ \
				| CSOR_NAND_SPRZ_224/* Spare size = 224 */ \
				| CSOR_NAND_PB(64))	/*Pages Per Block = 64*/

#define CONFIG_SYS_NAND_ONFI_DETECTION

/* ONFI NAND Flash mode0 Timing Params */
#define CONFIG_SYS_NAND_FTIM0		(FTIM0_NAND_TCCST(0x07) | \
					FTIM0_NAND_TWP(0x18)   | \
					FTIM0_NAND_TWCHT(0x07) | \
					FTIM0_NAND_TWH(0x0a))
#define CONFIG_SYS_NAND_FTIM1		(FTIM1_NAND_TADLE(0x32) | \
					FTIM1_NAND_TWBE(0x39)  | \
					FTIM1_NAND_TRR(0x0e)   | \
					FTIM1_NAND_TRP(0x18))
#define CONFIG_SYS_NAND_FTIM2		(FTIM2_NAND_TRAD(0x0f) | \
					FTIM2_NAND_TREH(0x0a) | \
					FTIM2_NAND_TWHRE(0x1e))
#define CONFIG_SYS_NAND_FTIM3		0x0

#define CONFIG_SYS_NAND_DDR_LAW		11
#define CONFIG_SYS_NAND_BASE_LIST	{ CONFIG_SYS_NAND_BASE }
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_MTD_NAND_VERIFY_WRITE
#define CONFIG_CMD_NAND

#define CONFIG_SYS_NAND_BLOCK_SIZE	(512 * 1024)

#if defined(CONFIG_NAND)
#define CONFIG_SYS_CSPR0_EXT		CONFIG_SYS_NAND_CSPR_EXT
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NAND_FTIM3
#define CONFIG_SYS_CSPR1_EXT		CONFIG_SYS_NOR_CSPR_EXT
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NOR_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NOR_FTIM3
#else
#define CONFIG_SYS_CSPR0_EXT		CONFIG_SYS_NOR_CSPR_EXT
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NOR_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NOR_FTIM3
#define CONFIG_SYS_CSPR1_EXT		CONFIG_SYS_NAND_CSPR_EXT
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NAND_FTIM3
#endif

#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE

#if defined(CONFIG_RAMBOOT_PBL)
#define CONFIG_SYS_RAMBOOT
#endif

#define CONFIG_BOARD_EARLY_INIT_R
#define CONFIG_MISC_INIT_R

#define CONFIG_HWCONFIG

/* define to use L1 as initial stack */
#define CONFIG_L1_INIT_RAM
#define CONFIG_SYS_INIT_RAM_LOCK
#define CONFIG_SYS_INIT_RAM_ADDR	0xfdd00000	/* Initial L1 address */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH	0xf
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW	0xfe0ec000
/* The assembler doesn't like typecast */
#define CONFIG_SYS_INIT_RAM_ADDR_PHYS \
	((CONFIG_SYS_INIT_RAM_ADDR_PHYS_HIGH * 1ull << 32) | \
	  CONFIG_SYS_INIT_RAM_ADDR_PHYS_LOW)
#define CONFIG_SYS_INIT_RAM_SIZE		0x00004000

#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - \
					GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#define CONFIG_SYS_MONITOR_LEN		(512 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(4 * 1024 * 1024)

/* Serial Port - controlled on board with jumper J8
 * open - index 2
 * shorted - index 1
 */
#define CONFIG_CONS_INDEX	1
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	1
#define CONFIG_SYS_NS16550_CLK		(get_bus_freq(0)/2)

#define CONFIG_SYS_BAUDRATE_TABLE	\
	{300, 600, 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200}

#define CONFIG_SYS_NS16550_COM1	(CONFIG_SYS_CCSRBAR+0x11C500)
#define CONFIG_SYS_NS16550_COM2	(CONFIG_SYS_CCSRBAR+0x11C600)
#define CONFIG_SYS_NS16550_COM3	(CONFIG_SYS_CCSRBAR+0x11D500)
#define CONFIG_SYS_NS16550_COM4	(CONFIG_SYS_CCSRBAR+0x11D600)
#define CONFIG_SERIAL_MULTI		/* Enable both serial ports */
#define CONFIG_SYS_CONSOLE_IS_IN_ENV	/* determine from environment */

/* Use the HUSH parser */
#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_SYS_PROMPT_HUSH_PS2 "> "

/* pass open firmware flat tree */
#define CONFIG_OF_LIBFDT
#define CONFIG_OF_BOARD_SETUP
#define CONFIG_OF_STDOUT_VIA_ALIAS

/* new uImage format support */
#define CONFIG_FIT
#define CONFIG_FIT_VERBOSE	/* enable fit_format_{error,warning}() */

/* I2C */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_FSL		/* Use FSL common I2C driver */
#define CONFIG_SYS_FSL_I2C_SPEED	400000	/* I2C speed in Hz */
#define CONFIG_SYS_FSL_I2C_SLAVE	0x7F
#define CONFIG_SYS_FSL_I2C2_SPEED	400000	/* I2C speed in Hz */
#define CONFIG_SYS_FSL_I2C2_SLAVE	0x7F
#define CONFIG_SYS_FSL_I2C_OFFSET	0x118000
#define CONFIG_SYS_FSL_I2C2_OFFSET	0x119000

/* I2C bus multiplexer */
#define I2C_MUX_PCA_ADDR                0x70

/*
 * RTC configuration
 */
#define RTC
#define CONFIG_RTC_DS1337               1
#define CONFIG_SYS_I2C_RTC_ADDR         0x68

/*DVI encoder*/
#define CONFIG_HDMI_ENCODER_I2C_ADDR  0x75

/*
 * eSPI - Enhanced SPI
 */
#define CONFIG_FSL_ESPI
#define CONFIG_SPI_FLASH
#define CONFIG_SPI_FLASH_STMICRO
#define CONFIG_CMD_SF
#define CONFIG_SF_DEFAULT_SPEED         10000000
#define CONFIG_SF_DEFAULT_MODE          0

/*
 * General PCI
 * Memory space is mapped 1-1, but I/O space must start from 0.
 */

#ifdef CONFIG_PCI
/* controller 1, direct to uli, tgtid 3, Base address 20000 */
#ifdef CONFIG_PCIE1
#define	CONFIG_SYS_PCIE1_MEM_VIRT	0x80000000
#define	CONFIG_SYS_PCIE1_MEM_BUS	0xe0000000
#define	CONFIG_SYS_PCIE1_MEM_PHYS	0xc00000000ull
#define CONFIG_SYS_PCIE1_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE1_IO_VIRT	0xf8000000
#define CONFIG_SYS_PCIE1_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE1_IO_PHYS	0xff8000000ull
#define CONFIG_SYS_PCIE1_IO_SIZE	0x00010000	/* 64k */
#endif

/* controller 2, Slot 2, tgtid 2, Base address 201000 */
#ifdef CONFIG_PCIE2
#define CONFIG_SYS_PCIE2_MEM_VIRT	0x90000000
#define CONFIG_SYS_PCIE2_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE2_MEM_PHYS	0xc10000000ull
#define CONFIG_SYS_PCIE2_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE2_IO_VIRT	0xf8010000
#define CONFIG_SYS_PCIE2_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE2_IO_PHYS	0xff8010000ull
#define CONFIG_SYS_PCIE2_IO_SIZE	0x00010000	/* 64k */
#endif

/* controller 3, Slot 1, tgtid 1, Base address 202000 */
#ifdef CONFIG_PCIE3
#define CONFIG_SYS_PCIE3_MEM_VIRT	0xa0000000
#define CONFIG_SYS_PCIE3_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE3_MEM_PHYS	0xc20000000ull
#define CONFIG_SYS_PCIE3_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE3_IO_VIRT	0xf8020000
#define CONFIG_SYS_PCIE3_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE3_IO_PHYS	0xff8020000ull
#define CONFIG_SYS_PCIE3_IO_SIZE	0x00010000	/* 64k */
#endif

/* controller 4, Base address 203000 */
#ifdef CONFIG_PCIE4
#define CONFIG_SYS_PCIE4_MEM_VIRT	0xb0000000
#define CONFIG_SYS_PCIE4_MEM_BUS	0xe0000000
#define CONFIG_SYS_PCIE4_MEM_PHYS	0xc30000000ull
#define CONFIG_SYS_PCIE4_MEM_SIZE	0x10000000	/* 256M */
#define CONFIG_SYS_PCIE4_IO_VIRT	0xf8030000
#define CONFIG_SYS_PCIE4_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE4_IO_PHYS	0xff8030000ull
#define CONFIG_SYS_PCIE4_IO_SIZE	0x00010000	/* 64k */
#endif

#define CONFIG_PCI_PNP			/* do pci plug-and-play */
#define CONFIG_E1000

#define CONFIG_PCI_SCAN_SHOW		/* show pci devices on startup */
#define CONFIG_DOS_PARTITION
#endif	/* CONFIG_PCI */

/* SATA */
#define CONFIG_FSL_SATA_V2
#ifdef CONFIG_FSL_SATA_V2
#define CONFIG_LIBATA
#define CONFIG_FSL_SATA

#define CONFIG_SYS_SATA_MAX_DEVICE	1
#define CONFIG_SATA1
#define CONFIG_SYS_SATA1		CONFIG_SYS_MPC85xx_SATA1_ADDR
#define CONFIG_SYS_SATA1_FLAGS		FLAGS_DMA

#define CONFIG_LBA48
#define CONFIG_CMD_SATA
#define CONFIG_DOS_PARTITION
#define CONFIG_CMD_EXT2
#endif

/*
* USB
*/
#define CONFIG_HAS_FSL_DR_USB

#ifdef CONFIG_HAS_FSL_DR_USB
#define CONFIG_USB_EHCI

#ifdef CONFIG_USB_EHCI
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI_FSL
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_CMD_EXT2
#endif
#endif

#define CONFIG_MMC

#ifdef CONFIG_MMC
#define CONFIG_FSL_ESDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR       CONFIG_SYS_MPC85xx_ESDHC_ADDR
#define CONFIG_CMD_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#endif

/* Qman/Bman */
#ifndef CONFIG_NOBQFMAN
#define CONFIG_SYS_DPAA_QBMAN		/* Support Q/Bman */
#define CONFIG_SYS_BMAN_NUM_PORTALS	25
#define CONFIG_SYS_BMAN_MEM_BASE	0xf4000000
#define CONFIG_SYS_BMAN_MEM_PHYS	0xff4000000ull
#define CONFIG_SYS_BMAN_MEM_SIZE	0x02000000
#define CONFIG_SYS_QMAN_NUM_PORTALS	25
#define CONFIG_SYS_QMAN_MEM_BASE	0xf6000000
#define CONFIG_SYS_QMAN_MEM_PHYS	0xff6000000ull
#define CONFIG_SYS_QMAN_MEM_SIZE	0x02000000

#define CONFIG_SYS_DPAA_FMAN
#define CONFIG_SYS_DPAA_PME

/* Default address of microcode for the Linux Fman driver */
#if defined(CONFIG_SPIFLASH)
/*
 * env is stored at 0x100000, sector size is 0x10000, ucode is stored after
 * env, so we got 0x110000.
 */
#define CONFIG_SYS_QE_FW_IN_SPIFLASH
#define CONFIG_SYS_QE_FMAN_FW_ADDR	0x110000
#elif defined(CONFIG_SDCARD)
/*
 * PBL SD boot image should stored at 0x1000(8 blocks), the size of the image is
 * about 825KB (1650 blocks), Env is stored after the image, and the env size is
 * 0x2000 (16 blocks), 8 + 1650 + 16 = 1674, enlarge it to 1680.
 */
#define CONFIG_SYS_QE_FMAN_FW_IN_MMC
#define CONFIG_SYS_QE_FMAN_FW_ADDR	(512 * 1680)
#elif defined(CONFIG_NAND)
#define CONFIG_SYS_QE_FMAN_FW_IN_NAND
#define CONFIG_SYS_QE_FMAN_FW_ADDR	(4 * CONFIG_SYS_NAND_BLOCK_SIZE)
#else
#define CONFIG_SYS_QE_FMAN_FW_IN_NOR
#define CONFIG_SYS_QE_FMAN_FW_ADDR		0xEFF00000
#endif
#define CONFIG_SYS_QE_FMAN_FW_LENGTH	0x10000
#define CONFIG_SYS_FDT_PAD		(0x3000 + CONFIG_SYS_QE_FMAN_FW_LENGTH)
#endif /* CONFIG_NOBQFMAN */

#ifdef CONFIG_SYS_DPAA_FMAN
#define CONFIG_FMAN_ENET
#define CONFIG_PHY_VITESSE
#define CONFIG_PHY_REALTEK
#endif

#ifdef CONFIG_FMAN_ENET
#define CONFIG_MII		/* MII PHY management */
#define CONFIG_ETHPRIME		"FM1@DTSEC1"
#define CONFIG_PHY_GIGE		/* Include GbE speed/duplex detection */
#endif

/*
 * Environment
 */
#define CONFIG_LOADS_ECHO		/* echo on for serial download */
#define CONFIG_SYS_LOADS_BAUD_CHANGE	/* allow baudrate change */

/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_ELF
#define CONFIG_CMD_ERRATA
#define CONFIG_CMD_GREPENV
#define CONFIG_CMD_IRQ
#define CONFIG_CMD_I2C
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING
#define CONFIG_CMD_REGINFO
#define CONFIG_CMD_SETEXPR

#ifdef CONFIG_PCI
#define CONFIG_CMD_PCI
#define CONFIG_CMD_NET
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP			/* undef to save memory	*/
#define CONFIG_CMDLINE_EDITING			/* Command-line editing */
#define CONFIG_AUTO_COMPLETE			/* add autocompletion support */
#define CONFIG_SYS_LOAD_ADDR	0x2000000	/* default load address */
#define CONFIG_SYS_PROMPT	"=> "		/* Monitor Command Prompt */
#ifdef CONFIG_CMD_KGDB
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size */
#else
#define CONFIG_SYS_CBSIZE	256		/* Console I/O Buffer Size */
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16		/* max number of command args */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE/* Boot Argument Buffer Size */
#define CONFIG_SYS_HZ		1000		/* decrementer freq: 1ms ticks*/

/*
 * For booting Linux, the board info and command line data
 * have to be in the first 64 MB of memory, since this is
 * the maximum mapped by the Linux kernel during initialization.
 */
#define CONFIG_SYS_BOOTMAPSZ	(64 << 20)	/* Initial map for Linux*/
#define CONFIG_SYS_BOOTM_LEN	(64 << 20)	/* Increase max gunzip size */

#ifdef CONFIG_CMD_KGDB
#define CONFIG_KGDB_BAUDRATE	230400	/* speed to run kgdb serial port */
#endif

/*
 * Environment Configuration
 */
#define CONFIG_ROOTPATH		"/opt/nfsroot"
#define CONFIG_BOOTFILE		"uImage"
#define CONFIG_UBOOTPATH	"u-boot.bin"	/* U-Boot image on TFTP server*/

/* default location for tftp and bootm */
#define CONFIG_LOADADDR		1000000

#define CONFIG_BOOTDELAY	10	/*-1 disables auto-boot*/

#define CONFIG_BAUDRATE	115200

#define __USB_PHY_TYPE	utmi

#define	CONFIG_EXTRA_ENV_SETTINGS				\
	"hwconfig=fsl_ddr:ctlr_intlv=cacheline,"		\
	"bank_intlv=cs0_cs1;"					\
	"usb1:dr_mode=host,phy_type=" __stringify(__USB_PHY_TYPE) "\0"\
	"netdev=eth0\0"						\
	"uboot=" __stringify(CONFIG_UBOOTPATH) "\0"		\
	"ubootaddr=" __stringify(CONFIG_SYS_TEXT_BASE) "\0"	\
	"tftpflash=tftpboot $loadaddr $uboot && "		\
	"protect off $ubootaddr +$filesize && "			\
	"erase $ubootaddr +$filesize && "			\
	"cp.b $loadaddr $ubootaddr $filesize && "		\
	"protect on $ubootaddr +$filesize && "			\
	"cmp.b $loadaddr $ubootaddr $filesize\0"		\
	"consoledev=ttyS0\0"					\
	"ramdiskaddr=2000000\0"					\
	"ramdiskfile=t1040rdb_pi/ramdisk.uboot\0"			\
	"fdtaddr=c00000\0"					\
	"fdtfile=t1040rdb_pi/t1040rdb_pi.dtb\0"				\
	"bdev=sda3\0"						\
	"c=ffe\0"

#define CONFIG_LINUX                       \
	"setenv bootargs root=/dev/ram rw "            \
	"console=$consoledev,$baudrate $othbootargs;"  \
	"setenv ramdiskaddr 0x02000000;"               \
	"setenv fdtaddr 0x00c00000;"		       \
	"setenv loadaddr 0x1000000;"		       \
	"bootm $loadaddr $ramdiskaddr $fdtaddr"

#define CONFIG_HDBOOT					\
	"setenv bootargs root=/dev/$bdev rw "		\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"tftp $loadaddr $bootfile;"			\
	"tftp $fdtaddr $fdtfile;"			\
	"bootm $loadaddr - $fdtaddr"

#define CONFIG_NFSBOOTCOMMAND			\
	"setenv bootargs root=/dev/nfs rw "	\
	"nfsroot=$serverip:$rootpath "		\
	"ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname:$netdev:off " \
	"console=$consoledev,$baudrate $othbootargs;"	\
	"tftp $loadaddr $bootfile;"		\
	"tftp $fdtaddr $fdtfile;"		\
	"bootm $loadaddr - $fdtaddr"

#define CONFIG_RAMBOOTCOMMAND				\
	"setenv bootargs root=/dev/ram rw "		\
	"console=$consoledev,$baudrate $othbootargs;"	\
	"tftp $ramdiskaddr $ramdiskfile;"		\
	"tftp $loadaddr $bootfile;"			\
	"tftp $fdtaddr $fdtfile;"			\
	"bootm $loadaddr $ramdiskaddr $fdtaddr"

#define CONFIG_BOOTCOMMAND		CONFIG_LINUX

#ifdef CONFIG_SECURE_BOOT
#include <asm/fsl_secure_boot.h>
#endif

#endif	/* __CONFIG_H */
