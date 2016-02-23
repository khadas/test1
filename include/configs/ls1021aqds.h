/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_LS102XA

#define CONFIG_ARMV7_PSCI

#define CONFIG_SYS_FSL_CLK

#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_BOARD_EARLY_INIT_F

#define CONFIG_DEEP_SLEEP
#if defined(CONFIG_DEEP_SLEEP)
#define CONFIG_SILENT_CONSOLE
#endif

/*
 * Size of malloc() pool
 */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 16 * 1024 * 1024)

#define CONFIG_SYS_INIT_RAM_ADDR	OCRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	OCRAM_SIZE

/*
 * Generic Timer Definitions
 */
#define GENERIC_TIMER_CLK		12500000

#ifndef __ASSEMBLY__
unsigned long get_board_sys_clk(void);
unsigned long get_board_ddr_clk(void);
#endif

#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
#define CONFIG_SYS_CLK_FREQ		100000000
#define CONFIG_DDR_CLK_FREQ		100000000
#define CONFIG_QIXIS_I2C_ACCESS
#else
#define CONFIG_SYS_CLK_FREQ		get_board_sys_clk()
#define CONFIG_DDR_CLK_FREQ		get_board_ddr_clk()
#endif

#ifdef CONFIG_RAMBOOT_PBL
#define CONFIG_SYS_FSL_PBL_PBI	board/freescale/ls1021aqds/ls102xa_pbi.cfg
#endif

#ifdef CONFIG_SD_BOOT
#ifdef CONFIG_SD_BOOT_QSPI
#define CONFIG_SYS_FSL_PBL_RCW	\
	board/freescale/ls1021aqds/ls102xa_rcw_sd_qspi.cfg
#else
#define CONFIG_SYS_FSL_PBL_RCW	\
	board/freescale/ls1021aqds/ls102xa_rcw_sd_ifc.cfg
#endif
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_LDSCRIPT	"arch/$(ARCH)/cpu/u-boot-spl.lds"
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_MPC8XXX_INIT_DDR_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT
#define CONFIG_SPL_WATCHDOG_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_DRIVERS_MISC_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#define CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR		0xe8
#define CONFIG_SYS_U_BOOT_MAX_SIZE_SECTORS		0x600

#define CONFIG_SPL_TEXT_BASE		0x10000000
#define CONFIG_SPL_MAX_SIZE		0x1a000
#define CONFIG_SPL_STACK		0x1001d000
#define CONFIG_SPL_PAD_TO		0x1c000
#define CONFIG_SYS_TEXT_BASE		0x82000000

#define CONFIG_SYS_SPL_MALLOC_START	(CONFIG_SYS_TEXT_BASE + \
		CONFIG_SYS_MONITOR_LEN)
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x100000
#define CONFIG_SPL_BSS_START_ADDR	0x80100000
#define CONFIG_SPL_BSS_MAX_SIZE		0x80000
#define CONFIG_SYS_MONITOR_LEN		0xc0000
#endif

#ifdef CONFIG_QSPI_BOOT
#define CONFIG_SYS_TEXT_BASE		0x40010000
#endif

#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
#define CONFIG_SYS_NO_FLASH
#endif

#ifdef CONFIG_NAND_BOOT
#define CONFIG_SYS_FSL_PBL_RCW	board/freescale/ls1021aqds/ls102xa_rcw_nand.cfg
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_LDSCRIPT	"arch/$(ARCH)/cpu/u-boot-spl.lds"
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_MPC8XXX_INIT_DDR_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT
#define CONFIG_SPL_WATCHDOG_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_NAND_SUPPORT
#define CONFIG_SPL_DRIVERS_MISC_SUPPORT

#define CONFIG_SPL_TEXT_BASE		0x10000000
#define CONFIG_SPL_MAX_SIZE		0x1a000
#define CONFIG_SPL_STACK		0x1001d000
#define CONFIG_SPL_PAD_TO		0x1c000
#define CONFIG_SYS_TEXT_BASE		0x82000000

#define CONFIG_SYS_NAND_U_BOOT_SIZE	(400 << 10)
#define CONFIG_SYS_NAND_U_BOOT_OFFS	CONFIG_SPL_PAD_TO
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
#define CONFIG_SYS_NAND_U_BOOT_DST	CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_NAND_U_BOOT_START	CONFIG_SYS_TEXT_BASE

#define CONFIG_SYS_SPL_MALLOC_START	0x80200000
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x100000
#define CONFIG_SPL_BSS_START_ADDR	0x80100000
#define CONFIG_SPL_BSS_MAX_SIZE		0x80000
#define CONFIG_SYS_MONITOR_LEN		0x80000
#endif

#ifndef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE		0x60100000
#endif

#define CONFIG_NR_DRAM_BANKS		1

#define CONFIG_DDR_SPD
#define SPD_EEPROM_ADDRESS		0x51
#define CONFIG_SYS_SPD_BUS_NUM		0

#define CONFIG_FSL_DDR_INTERACTIVE	/* Interactive debugging */
#ifndef CONFIG_SYS_FSL_DDR4
#define CONFIG_SYS_FSL_DDR3		/* Use DDR3 memory */
#define CONFIG_SYS_DDR_RAW_TIMING
#endif
#define CONFIG_DIMM_SLOTS_PER_CTLR	1
#define CONFIG_CHIP_SELECTS_PER_CTRL	4

#define CONFIG_SYS_DDR_SDRAM_BASE	0x80000000UL
#define CONFIG_SYS_SDRAM_BASE		CONFIG_SYS_DDR_SDRAM_BASE

#define CONFIG_DDR_ECC
#ifdef CONFIG_DDR_ECC
#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER
#define CONFIG_MEM_INIT_VALUE           0xdeadbeef
#endif

#define CONFIG_SYS_HAS_SERDES

#define CONFIG_FSL_CAAM			/* Enable CAAM */

#if !defined(CONFIG_SD_BOOT) && !defined(CONFIG_NAND_BOOT) && \
	!defined(CONFIG_QSPI_BOOT)
#define CONFIG_U_QE
#endif

/*
 * IFC Definitions
 */
#if !defined(CONFIG_QSPI_BOOT) && !defined(CONFIG_SD_BOOT_QSPI)
#define CONFIG_FSL_IFC
#define CONFIG_SYS_FLASH_BASE		0x60000000
#define CONFIG_SYS_FLASH_BASE_PHYS	CONFIG_SYS_FLASH_BASE

#define CONFIG_SYS_NOR0_CSPR_EXT	(0x0)
#define CONFIG_SYS_NOR0_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE_PHYS) | \
				CSPR_PORT_SIZE_16 | \
				CSPR_MSEL_NOR | \
				CSPR_V)
#define CONFIG_SYS_NOR1_CSPR_EXT	(0x0)
#define CONFIG_SYS_NOR1_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_FLASH_BASE_PHYS \
				+ 0x8000000) | \
				CSPR_PORT_SIZE_16 | \
				CSPR_MSEL_NOR | \
				CSPR_V)
#define CONFIG_SYS_NOR_AMASK		IFC_AMASK(128 * 1024 * 1024)

#define CONFIG_SYS_NOR_CSOR		(CSOR_NOR_ADM_SHIFT(4) | \
					CSOR_NOR_TRHZ_80)
#define CONFIG_SYS_NOR_FTIM0		(FTIM0_NOR_TACSE(0x4) | \
					FTIM0_NOR_TEADC(0x5) | \
					FTIM0_NOR_TEAHC(0x5))
#define CONFIG_SYS_NOR_FTIM1		(FTIM1_NOR_TACO(0x35) | \
					FTIM1_NOR_TRAD_NOR(0x1a) | \
					FTIM1_NOR_TSEQRAD_NOR(0x13))
#define CONFIG_SYS_NOR_FTIM2		(FTIM2_NOR_TCS(0x4) | \
					FTIM2_NOR_TCH(0x4) | \
					FTIM2_NOR_TWPH(0xe) | \
					FTIM2_NOR_TWP(0x1c))
#define CONFIG_SYS_NOR_FTIM3		0

#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#define CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_FLASH_SHOW_PROGRESS	45
#define CONFIG_CFI_FLASH_USE_WEAK_ACCESSORS
#define CONFIG_SYS_WRITE_SWAPPED_DATA

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* number of banks */
#define CONFIG_SYS_MAX_FLASH_SECT	1024	/* sectors per device */
#define CONFIG_SYS_FLASH_ERASE_TOUT	60000	/* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (ms) */

#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_BANKS_LIST	{CONFIG_SYS_FLASH_BASE_PHYS, \
					CONFIG_SYS_FLASH_BASE_PHYS + 0x8000000}

/*
 * NAND Flash Definitions
 */
#define CONFIG_NAND_FSL_IFC

#define CONFIG_SYS_NAND_BASE		0x7e800000
#define CONFIG_SYS_NAND_BASE_PHYS	CONFIG_SYS_NAND_BASE

#define CONFIG_SYS_NAND_CSPR_EXT	(0x0)

#define CONFIG_SYS_NAND_CSPR	(CSPR_PHYS_ADDR(CONFIG_SYS_NAND_BASE_PHYS) \
				| CSPR_PORT_SIZE_8	\
				| CSPR_MSEL_NAND	\
				| CSPR_V)
#define CONFIG_SYS_NAND_AMASK	IFC_AMASK(64*1024)
#define CONFIG_SYS_NAND_CSOR	(CSOR_NAND_ECC_ENC_EN	/* ECC on encode */ \
				| CSOR_NAND_ECC_DEC_EN	/* ECC on decode */ \
				| CSOR_NAND_ECC_MODE_4	/* 4-bit ECC */ \
				| CSOR_NAND_RAL_3	/* RAL = 3 Bytes */ \
				| CSOR_NAND_PGS_2K	/* Page Size = 2K */ \
				| CSOR_NAND_SPRZ_64	/* Spare size = 64 */ \
				| CSOR_NAND_PB(64))	/* 64 Pages Per Block */

#define CONFIG_SYS_NAND_ONFI_DETECTION

#define CONFIG_SYS_NAND_FTIM0		(FTIM0_NAND_TCCST(0x7) | \
					FTIM0_NAND_TWP(0x18)   | \
					FTIM0_NAND_TWCHT(0x7) | \
					FTIM0_NAND_TWH(0xa))
#define CONFIG_SYS_NAND_FTIM1		(FTIM1_NAND_TADLE(0x32) | \
					FTIM1_NAND_TWBE(0x39)  | \
					FTIM1_NAND_TRR(0xe)   | \
					FTIM1_NAND_TRP(0x18))
#define CONFIG_SYS_NAND_FTIM2		(FTIM2_NAND_TRAD(0xf) | \
					FTIM2_NAND_TREH(0xa) | \
					FTIM2_NAND_TWHRE(0x1e))
#define CONFIG_SYS_NAND_FTIM3           0x0

#define CONFIG_SYS_NAND_BASE_LIST	{ CONFIG_SYS_NAND_BASE }
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_CMD_NAND

#define CONFIG_SYS_NAND_BLOCK_SIZE	(128 * 1024)
#endif

/*
 * QIXIS Definitions
 */
#define CONFIG_FSL_QIXIS

#ifdef CONFIG_FSL_QIXIS
#define QIXIS_BASE			0x7fb00000
#define QIXIS_BASE_PHYS			QIXIS_BASE
#define CONFIG_SYS_I2C_FPGA_ADDR	0x66
#define QIXIS_LBMAP_SWITCH		6
#define QIXIS_LBMAP_MASK		0x0f
#define QIXIS_LBMAP_SHIFT		0
#define QIXIS_LBMAP_DFLTBANK		0x00
#define QIXIS_LBMAP_ALTBANK		0x04
#define QIXIS_RST_CTL_RESET		0x44
#define QIXIS_RCFG_CTL_RECONFIG_IDLE	0x20
#define QIXIS_RCFG_CTL_RECONFIG_START	0x21
#define QIXIS_RCFG_CTL_WATCHDOG_ENBLE	0x08

#define CONFIG_SYS_FPGA_CSPR_EXT	(0x0)
#define CONFIG_SYS_FPGA_CSPR		(CSPR_PHYS_ADDR(QIXIS_BASE_PHYS) | \
					CSPR_PORT_SIZE_8 | \
					CSPR_MSEL_GPCM | \
					CSPR_V)
#define CONFIG_SYS_FPGA_AMASK		IFC_AMASK(64 * 1024)
#define CONFIG_SYS_FPGA_CSOR		(CSOR_NOR_ADM_SHIFT(4) | \
					CSOR_NOR_NOR_MODE_AVD_NOR | \
					CSOR_NOR_TRHZ_80)

/*
 * QIXIS Timing parameters for IFC GPCM
 */
#define CONFIG_SYS_FPGA_FTIM0		(FTIM0_GPCM_TACSE(0xe) | \
					FTIM0_GPCM_TEADC(0xe) | \
					FTIM0_GPCM_TEAHC(0xe))
#define CONFIG_SYS_FPGA_FTIM1		(FTIM1_GPCM_TACO(0xe) | \
					FTIM1_GPCM_TRAD(0x1f))
#define CONFIG_SYS_FPGA_FTIM2		(FTIM2_GPCM_TCS(0xe) | \
					FTIM2_GPCM_TCH(0xe) | \
					FTIM2_GPCM_TWP(0xf0))
#define CONFIG_SYS_FPGA_FTIM3		0x0
#endif

#if defined(CONFIG_NAND_BOOT)
#define CONFIG_SYS_CSPR0_EXT		CONFIG_SYS_NAND_CSPR_EXT
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NAND_FTIM3
#define CONFIG_SYS_CSPR1_EXT		CONFIG_SYS_NOR0_CSPR_EXT
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NOR0_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NOR_FTIM3
#define CONFIG_SYS_CSPR2_EXT		CONFIG_SYS_NOR1_CSPR_EXT
#define CONFIG_SYS_CSPR2		CONFIG_SYS_NOR1_CSPR
#define CONFIG_SYS_AMASK2		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR2		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS2_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS2_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS2_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS2_FTIM3		CONFIG_SYS_NOR_FTIM3
#define CONFIG_SYS_CSPR3_EXT		CONFIG_SYS_FPGA_CSPR_EXT
#define CONFIG_SYS_CSPR3		CONFIG_SYS_FPGA_CSPR
#define CONFIG_SYS_AMASK3		CONFIG_SYS_FPGA_AMASK
#define CONFIG_SYS_CSOR3		CONFIG_SYS_FPGA_CSOR
#define CONFIG_SYS_CS3_FTIM0		CONFIG_SYS_FPGA_FTIM0
#define CONFIG_SYS_CS3_FTIM1		CONFIG_SYS_FPGA_FTIM1
#define CONFIG_SYS_CS3_FTIM2		CONFIG_SYS_FPGA_FTIM2
#define CONFIG_SYS_CS3_FTIM3		CONFIG_SYS_FPGA_FTIM3
#else
#define CONFIG_SYS_CSPR0_EXT		CONFIG_SYS_NOR0_CSPR_EXT
#define CONFIG_SYS_CSPR0		CONFIG_SYS_NOR0_CSPR
#define CONFIG_SYS_AMASK0		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR0		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS0_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS0_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS0_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS0_FTIM3		CONFIG_SYS_NOR_FTIM3
#define CONFIG_SYS_CSPR1_EXT		CONFIG_SYS_NOR1_CSPR_EXT
#define CONFIG_SYS_CSPR1		CONFIG_SYS_NOR1_CSPR
#define CONFIG_SYS_AMASK1		CONFIG_SYS_NOR_AMASK
#define CONFIG_SYS_CSOR1		CONFIG_SYS_NOR_CSOR
#define CONFIG_SYS_CS1_FTIM0		CONFIG_SYS_NOR_FTIM0
#define CONFIG_SYS_CS1_FTIM1		CONFIG_SYS_NOR_FTIM1
#define CONFIG_SYS_CS1_FTIM2		CONFIG_SYS_NOR_FTIM2
#define CONFIG_SYS_CS1_FTIM3		CONFIG_SYS_NOR_FTIM3
#define CONFIG_SYS_CSPR2_EXT		CONFIG_SYS_NAND_CSPR_EXT
#define CONFIG_SYS_CSPR2		CONFIG_SYS_NAND_CSPR
#define CONFIG_SYS_AMASK2		CONFIG_SYS_NAND_AMASK
#define CONFIG_SYS_CSOR2		CONFIG_SYS_NAND_CSOR
#define CONFIG_SYS_CS2_FTIM0		CONFIG_SYS_NAND_FTIM0
#define CONFIG_SYS_CS2_FTIM1		CONFIG_SYS_NAND_FTIM1
#define CONFIG_SYS_CS2_FTIM2		CONFIG_SYS_NAND_FTIM2
#define CONFIG_SYS_CS2_FTIM3		CONFIG_SYS_NAND_FTIM3
#define CONFIG_SYS_CSPR3_EXT		CONFIG_SYS_FPGA_CSPR_EXT
#define CONFIG_SYS_CSPR3		CONFIG_SYS_FPGA_CSPR
#define CONFIG_SYS_AMASK3		CONFIG_SYS_FPGA_AMASK
#define CONFIG_SYS_CSOR3		CONFIG_SYS_FPGA_CSOR
#define CONFIG_SYS_CS3_FTIM0		CONFIG_SYS_FPGA_FTIM0
#define CONFIG_SYS_CS3_FTIM1		CONFIG_SYS_FPGA_FTIM1
#define CONFIG_SYS_CS3_FTIM2		CONFIG_SYS_FPGA_FTIM2
#define CONFIG_SYS_CS3_FTIM3		CONFIG_SYS_FPGA_FTIM3
#endif

/*
 * Serial Port
 */
#ifdef CONFIG_LPUART
#define CONFIG_LPUART_32B_REG
#else
#define CONFIG_CONS_INDEX		1
#define CONFIG_SYS_NS16550_SERIAL
#ifndef CONFIG_DM_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	1
#endif
#define CONFIG_SYS_NS16550_CLK		get_serial_clock()
#endif

#define CONFIG_BAUDRATE			115200

/*
 * I2C
 */
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3		/* enable I2C bus 3 */

/*
 * I2C bus multiplexer
 */
#define I2C_MUX_PCA_ADDR_PRI		0x77
#define I2C_MUX_CH_DEFAULT		0x8
#define I2C_MUX_CH_CH7301		0xC

/*
 * MMC
 */
#define CONFIG_MMC
#define CONFIG_CMD_MMC
#define CONFIG_FSL_ESDHC
#define CONFIG_GENERIC_MMC

#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION

/* SPI */
#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
/* QSPI */
#define QSPI0_AMBA_BASE			0x40000000
#define FSL_QSPI_FLASH_SIZE		(1 << 24)
#define FSL_QSPI_FLASH_NUM		2

/* DSPI */

/* DM SPI */
#if defined(CONFIG_FSL_DSPI) || defined(CONFIG_FSL_QSPI)
#define CONFIG_CMD_SF
#define CONFIG_DM_SPI_FLASH
#define CONFIG_SPI_FLASH_DATAFLASH
#endif
#endif

/*
 * USB
 */
/* EHCI Support - disbaled by default */
/*#define CONFIG_HAS_FSL_DR_USB*/

#ifdef CONFIG_HAS_FSL_DR_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_FSL
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#endif

/*XHCI Support - enabled by default*/
#define CONFIG_HAS_FSL_XHCI_USB

#ifdef CONFIG_HAS_FSL_XHCI_USB
#define CONFIG_USB_XHCI_FSL
#define CONFIG_USB_XHCI_DWC3
#define CONFIG_USB_XHCI
#define CONFIG_USB_MAX_CONTROLLER_COUNT		1
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS	2
#endif

#if defined(CONFIG_HAS_FSL_DR_USB) || defined(CONFIG_HAS_FSL_XHCI_USB)
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_CMD_EXT2
#endif

/*
 * Video
 */
#define CONFIG_FSL_DCU_FB

#ifdef CONFIG_FSL_DCU_FB
#define CONFIG_VIDEO
#define CONFIG_CMD_BMP
#define CONFIG_CFB_CONSOLE
#define CONFIG_VGA_AS_SINGLE_DEVICE
#define CONFIG_VIDEO_LOGO
#define CONFIG_VIDEO_BMP_LOGO

#define CONFIG_FSL_DIU_CH7301
#define CONFIG_SYS_I2C_DVI_BUS_NUM	0
#define CONFIG_SYS_I2C_QIXIS_ADDR	0x66
#define CONFIG_SYS_I2C_DVI_ADDR		0x75
#endif

/*
 * eTSEC
 */
#define CONFIG_TSEC_ENET

#ifdef CONFIG_TSEC_ENET
#define CONFIG_MII
#define CONFIG_MII_DEFAULT_TSEC		3
#define CONFIG_TSEC1			1
#define CONFIG_TSEC1_NAME		"eTSEC1"
#define CONFIG_TSEC2			1
#define CONFIG_TSEC2_NAME		"eTSEC2"
#define CONFIG_TSEC3			1
#define CONFIG_TSEC3_NAME		"eTSEC3"

#define TSEC1_PHY_ADDR			1
#define TSEC2_PHY_ADDR			2
#define TSEC3_PHY_ADDR			3

#define TSEC1_FLAGS			(TSEC_GIGABIT | TSEC_REDUCED)
#define TSEC2_FLAGS			(TSEC_GIGABIT | TSEC_REDUCED)
#define TSEC3_FLAGS			(TSEC_GIGABIT | TSEC_REDUCED)

#define TSEC1_PHYIDX			0
#define TSEC2_PHYIDX			0
#define TSEC3_PHYIDX			0

#define CONFIG_ETHPRIME			"eTSEC1"

#define CONFIG_PHY_GIGE
#define CONFIG_PHYLIB
#define CONFIG_PHY_REALTEK

#define CONFIG_HAS_ETH0
#define CONFIG_HAS_ETH1
#define CONFIG_HAS_ETH2

#define CONFIG_FSL_SGMII_RISER		1
#define SGMII_RISER_PHY_OFFSET		0x1b

#ifdef CONFIG_FSL_SGMII_RISER
#define CONFIG_SYS_TBIPA_VALUE		8
#endif

#endif

/* PCIe */
#define CONFIG_PCI		/* Enable PCI/PCIE */
#define CONFIG_PCIE1		/* PCIE controler 1 */
#define CONFIG_PCIE2		/* PCIE controler 2 */
#define CONFIG_PCIE_LAYERSCAPE	/* Use common FSL Layerscape PCIe code */
#define FSL_PCIE_COMPAT "fsl,ls1021a-pcie"

#define CONFIG_SYS_PCI_64BIT

#define CONFIG_SYS_PCIE_CFG0_PHYS_OFF	0x00000000
#define CONFIG_SYS_PCIE_CFG0_SIZE	0x00001000	/* 4k */
#define CONFIG_SYS_PCIE_CFG1_PHYS_OFF	0x00001000
#define CONFIG_SYS_PCIE_CFG1_SIZE	0x00001000	/* 4k */

#define CONFIG_SYS_PCIE_IO_BUS		0x00000000
#define CONFIG_SYS_PCIE_IO_PHYS_OFF	0x00010000
#define CONFIG_SYS_PCIE_IO_SIZE		0x00010000	/* 64k */

#define CONFIG_SYS_PCIE_MEM_BUS		0x08000000
#define CONFIG_SYS_PCIE_MEM_PHYS_OFF	0x04000000
#define CONFIG_SYS_PCIE_MEM_SIZE	0x08000000	/* 128M */

#ifdef CONFIG_PCI
#define CONFIG_PCI_PNP
#define CONFIG_PCI_SCAN_SHOW
#define CONFIG_CMD_PCI
#endif

#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII

#define CONFIG_CMDLINE_TAG
#define CONFIG_CMDLINE_EDITING

#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
#undef CONFIG_CMD_IMLS
#endif

#define CONFIG_ARMV7_NONSEC
#define CONFIG_ARMV7_VIRT
#define CONFIG_PEN_ADDR_BIG_ENDIAN
#define CONFIG_LAYERSCAPE_NS_ACCESS
#define CONFIG_SMP_PEN_ADDR		0x01ee0200
#define CONFIG_TIMER_CLK_FREQ		12500000

#define CONFIG_HWCONFIG
#define HWCONFIG_BUFFER_SIZE		256

#define CONFIG_FSL_DEVICE_DISABLE

#define CONFIG_BOOTDELAY		3

#define CONFIG_SYS_QE_FW_ADDR     0x600c0000

#ifdef CONFIG_LPUART
#define CONFIG_EXTRA_ENV_SETTINGS       \
	"bootargs=root=/dev/ram0 rw console=ttyLP0,115200\0" \
	"fdt_high=0xffffffff\0"         \
	"initrd_high=0xffffffff\0"      \
	"hwconfig=fsl_ddr:ctlr_intlv=null,bank_intlv=null\0"
#else
#define CONFIG_EXTRA_ENV_SETTINGS	\
	"bootargs=root=/dev/ram0 rw console=ttyS0,115200\0" \
	"fdt_high=0xffffffff\0"		\
	"initrd_high=0xffffffff\0"      \
	"hwconfig=fsl_ddr:ctlr_intlv=null,bank_intlv=null\0"
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER		/* use "hush" command parser */
#define CONFIG_SYS_PROMPT_HUSH_PS2	"> "
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		\
		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_CMD_GREPENV
#define CONFIG_CMD_MEMINFO
#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		0x9fffffff

#define CONFIG_SYS_LOAD_ADDR		0x82000000

#define CONFIG_LS102XA_STREAM_ID

/*
 * Stack sizes
 * The stack sizes are set up in start.S using the settings below
 */
#define CONFIG_STACKSIZE		(30 * 1024)

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_MONITOR_BASE CONFIG_SPL_TEXT_BASE
#else
#define CONFIG_SYS_MONITOR_BASE CONFIG_SYS_TEXT_BASE    /* start of monitor */
#endif

/*
 * Environment
 */
#define CONFIG_ENV_OVERWRITE

#if defined(CONFIG_SD_BOOT)
#define CONFIG_ENV_OFFSET		0x100000
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_SIZE			0x2000
#elif defined(CONFIG_QSPI_BOOT)
#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SIZE			0x2000          /* 8KB */
#define CONFIG_ENV_OFFSET		0x100000        /* 1MB */
#define CONFIG_ENV_SECT_SIZE		0x10000
#elif defined(CONFIG_NAND_BOOT)
#define CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_SIZE			0x2000
#define CONFIG_ENV_OFFSET		(10 * CONFIG_SYS_NAND_BLOCK_SIZE)
#else
#define CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SECT_SIZE)
#define CONFIG_ENV_SIZE			0x2000
#define CONFIG_ENV_SECT_SIZE		0x20000 /* 128K (one sector) */
#endif

#define CONFIG_CMD_BOOTZ

#define CONFIG_MISC_INIT_R

/* Hash command with SHA acceleration supported in hardware */
#ifdef CONFIG_FSL_CAAM
#define CONFIG_CMD_HASH
#define CONFIG_SHA_HW_ACCEL
#endif

#include <asm/fsl_secure_boot.h>
#define CONFIG_SYS_BOOTM_LEN	(64 << 20) /* Increase max gunzip size */

#endif
