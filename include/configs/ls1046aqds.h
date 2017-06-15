/*
 * Copyright 2016 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __LS1046AQDS_H__
#define __LS1046AQDS_H__

#include "ls1046a_common.h"

#if defined(CONFIG_NAND_BOOT) || defined(CONFIG_SD_BOOT)
#define CONFIG_SYS_TEXT_BASE		0x82000000
#elif defined(CONFIG_QSPI_BOOT)
#define CONFIG_SYS_TEXT_BASE		0x40100000
#else
#define CONFIG_SYS_TEXT_BASE		0x60100000
#endif

#ifndef __ASSEMBLY__
unsigned long get_board_sys_clk(void);
unsigned long get_board_ddr_clk(void);
#endif

#define CONFIG_SYS_CLK_FREQ		get_board_sys_clk()
#define CONFIG_DDR_CLK_FREQ		get_board_ddr_clk()

#define CONFIG_SKIP_LOWLEVEL_INIT

#define CONFIG_LAYERSCAPE_NS_ACCESS

#define CONFIG_DIMM_SLOTS_PER_CTLR	1
/* Physical Memory Map */
#define CONFIG_CHIP_SELECTS_PER_CTRL	4
#define CONFIG_NR_DRAM_BANKS		2

#define CONFIG_DDR_SPD
#define SPD_EEPROM_ADDRESS		0x51
#define CONFIG_SYS_SPD_BUS_NUM		0

#ifndef CONFIG_SPL
#define CONFIG_FSL_DDR_INTERACTIVE	/* Interactive debugging */
#endif

#define CONFIG_DDR_ECC
#ifdef CONFIG_DDR_ECC
#define CONFIG_ECC_INIT_VIA_DDRCONTROLLER
#define CONFIG_MEM_INIT_VALUE           0xdeadbeef
#endif

/* DSPI */
#ifdef CONFIG_FSL_DSPI
#define CONFIG_SPI_FLASH_STMICRO	/* cs0 */
#define CONFIG_SPI_FLASH_SST		/* cs1 */
#define CONFIG_SPI_FLASH_EON		/* cs2 */
#if !defined(CONFIG_QSPI_BOOT) && !defined(CONFIG_SD_BOOT_QSPI)
#define CONFIG_SF_DEFAULT_BUS		1
#define CONFIG_SF_DEFAULT_CS		0
#endif
#endif

/* QSPI */
#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
#ifdef CONFIG_FSL_QSPI
#define CONFIG_SPI_FLASH_SPANSION
#define FSL_QSPI_FLASH_SIZE		(1 << 24)
#define FSL_QSPI_FLASH_NUM		2
#endif
#endif

#ifdef CONFIG_SYS_DPAA_FMAN
#define CONFIG_FMAN_ENET
#define CONFIG_PHYLIB
#define CONFIG_PHY_VITESSE
#define CONFIG_PHY_REALTEK
#define CONFIG_PHYLIB_10G
#define RGMII_PHY1_ADDR		0x1
#define RGMII_PHY2_ADDR		0x2
#define SGMII_CARD_PORT1_PHY_ADDR 0x1C
#define SGMII_CARD_PORT2_PHY_ADDR 0x1D
#define SGMII_CARD_PORT3_PHY_ADDR 0x1E
#define SGMII_CARD_PORT4_PHY_ADDR 0x1F
/* PHY address on QSGMII riser card on slot 2 */
#define QSGMII_CARD_PORT1_PHY_ADDR_S2 0x8
#define QSGMII_CARD_PORT2_PHY_ADDR_S2 0x9
#define QSGMII_CARD_PORT3_PHY_ADDR_S2 0xA
#define QSGMII_CARD_PORT4_PHY_ADDR_S2 0xB
#endif

#ifdef CONFIG_RAMBOOT_PBL
#define CONFIG_SYS_FSL_PBL_PBI \
	board/freescale/ls1046aqds/ls1046aqds_pbi.cfg
#endif

#ifdef CONFIG_NAND_BOOT
#define CONFIG_SYS_FSL_PBL_RCW \
	board/freescale/ls1046aqds/ls1046aqds_rcw_nand.cfg
#endif

#ifdef CONFIG_SD_BOOT
#ifdef CONFIG_SD_BOOT_QSPI
#define CONFIG_SYS_FSL_PBL_RCW \
	board/freescale/ls1046aqds/ls1046aqds_rcw_sd_qspi.cfg
#else
#define CONFIG_SYS_FSL_PBL_RCW \
	board/freescale/ls1046aqds/ls1046aqds_rcw_sd_ifc.cfg
#endif
#endif

/* IFC */
#if !defined(CONFIG_QSPI_BOOT) && !defined(CONFIG_SD_BOOT_QSPI)
#define	CONFIG_FSL_IFC
/*
 * CONFIG_SYS_FLASH_BASE has the final address (core view)
 * CONFIG_SYS_FLASH_BASE_PHYS has the final address (IFC view)
 * CONFIG_SYS_FLASH_BASE_PHYS_EARLY has the temporary IFC address
 * CONFIG_SYS_TEXT_BASE is linked to 0x60000000 for booting
 */
#define CONFIG_SYS_FLASH_BASE			0x60000000
#define CONFIG_SYS_FLASH_BASE_PHYS		CONFIG_SYS_FLASH_BASE
#define CONFIG_SYS_FLASH_BASE_PHYS_EARLY	0x00000000

#ifdef CONFIG_MTD_NOR_FLASH
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_CFI
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#define CONFIG_SYS_FLASH_QUIET_TEST
#define CONFIG_FLASH_SHOW_PROGRESS	45	/* count down from 45/5: 9..1 */
#endif
#endif

/* LPUART */
#ifdef CONFIG_LPUART
#define CONFIG_LPUART_32B_REG
#define CFG_UART_MUX_MASK	0x6
#define CFG_UART_MUX_SHIFT	1
#define CFG_LPUART_EN		0x2
#endif

/* USB */
#define CONFIG_HAS_FSL_XHCI_USB
#ifdef CONFIG_HAS_FSL_XHCI_USB
#define CONFIG_USB_XHCI_HCD
#define CONFIG_USB_XHCI_FSL
#define CONFIG_USB_XHCI_DWC3
#define CONFIG_USB_MAX_CONTROLLER_COUNT         3
#define CONFIG_SYS_USB_XHCI_MAX_ROOT_PORTS      2
#define CONFIG_USB_STORAGE
#endif

/* SATA */
#define CONFIG_LIBATA
#define CONFIG_SCSI_AHCI
#define CONFIG_SCSI_AHCI_PLAT

/* EEPROM */
#define CONFIG_ID_EEPROM
#define CONFIG_SYS_I2C_EEPROM_NXID
#define CONFIG_SYS_EEPROM_BUS_NUM		0
#define CONFIG_SYS_I2C_EEPROM_ADDR		0x57
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	3
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	5

#define CONFIG_SYS_SATA				AHCI_BASE_ADDR

#define CONFIG_SYS_SCSI_MAX_SCSI_ID		1
#define CONFIG_SYS_SCSI_MAX_LUN			1
#define CONFIG_SYS_SCSI_MAX_DEVICE		(CONFIG_SYS_SCSI_MAX_SCSI_ID * \
						CONFIG_SYS_SCSI_MAX_LUN)

/*
 * IFC Definitions
 */
#if !defined(CONFIG_QSPI_BOOT) && !defined(CONFIG_SD_BOOT_QSPI)
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

#define CONFIG_SYS_MAX_FLASH_BANKS	2	/* number of banks */
#define CONFIG_SYS_MAX_FLASH_SECT	1024	/* sectors per device */
#define CONFIG_SYS_FLASH_ERASE_TOUT	60000	/* Flash Erase Timeout (ms) */
#define CONFIG_SYS_FLASH_WRITE_TOUT	500	/* Flash Write Timeout (ms) */

#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_BANKS_LIST	{CONFIG_SYS_FLASH_BASE_PHYS, \
					CONFIG_SYS_FLASH_BASE_PHYS + 0x8000000}

#define CONFIG_CFI_FLASH_USE_WEAK_ACCESSORS
#define CONFIG_SYS_WRITE_SWAPPED_DATA

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
				| CSOR_NAND_ECC_MODE_8	/* 8-bit ECC */ \
				| CSOR_NAND_RAL_3	/* RAL = 3 Bytes */ \
				| CSOR_NAND_PGS_4K	/* Page Size = 4K */ \
				| CSOR_NAND_SPRZ_224	/* Spare size = 224 */ \
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
#define CONFIG_MTD_NAND_VERIFY_WRITE
#define CONFIG_CMD_NAND

#define CONFIG_SYS_NAND_BLOCK_SIZE	(256 * 1024)
#endif

#ifdef CONFIG_NAND_BOOT
#define CONFIG_SPL_PAD_TO		0x40000		/* block aligned */
#define CONFIG_SYS_NAND_U_BOOT_OFFS	CONFIG_SPL_PAD_TO
#define CONFIG_SYS_NAND_U_BOOT_SIZE	(768 << 10)
#endif

#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
#define CONFIG_QIXIS_I2C_ACCESS
#define CONFIG_SYS_I2C_EARLY_INIT
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
#define QIXIS_LBMAP_NAND		0x09
#define QIXIS_LBMAP_SD			0x00
#define QIXIS_LBMAP_SD_QSPI		0xff
#define QIXIS_LBMAP_QSPI		0xff
#define QIXIS_RCW_SRC_NAND		0x110
#define QIXIS_RCW_SRC_SD		0x040
#define QIXIS_RCW_SRC_QSPI		0x045
#define QIXIS_RST_CTL_RESET		0x41
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
#define CONFIG_SYS_FPGA_FTIM0		(FTIM0_GPCM_TACSE(0xc) | \
					FTIM0_GPCM_TEADC(0x20) | \
					FTIM0_GPCM_TEAHC(0x10))
#define CONFIG_SYS_FPGA_FTIM1		(FTIM1_GPCM_TACO(0x50) | \
					FTIM1_GPCM_TRAD(0x1f))
#define CONFIG_SYS_FPGA_FTIM2		(FTIM2_GPCM_TCS(0x8) | \
					FTIM2_GPCM_TCH(0x8) | \
					FTIM2_GPCM_TWP(0xf0))
#define CONFIG_SYS_FPGA_FTIM3		0x0
#endif

#ifdef CONFIG_NAND_BOOT
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
 * I2C bus multiplexer
 */
#define I2C_MUX_PCA_ADDR_PRI		0x77
#define I2C_MUX_PCA_ADDR_SEC		0x76 /* Secondary multiplexer */
#define I2C_RETIMER_ADDR		0x18
#define I2C_MUX_CH_DEFAULT		0x8
#define I2C_MUX_CH_CH7301		0xC
#define I2C_MUX_CH5			0xD
#define I2C_MUX_CH6			0xE
#define I2C_MUX_CH7			0xF

#define I2C_MUX_CH_VOL_MONITOR 0xa

/* Voltage monitor on channel 2*/
#define I2C_VOL_MONITOR_ADDR           0x40
#define I2C_VOL_MONITOR_BUS_V_OFFSET   0x2
#define I2C_VOL_MONITOR_BUS_V_OVF      0x1
#define I2C_VOL_MONITOR_BUS_V_SHIFT    3

#define CONFIG_VID_FLS_ENV		"ls1046aqds_vdd_mv"
#ifndef CONFIG_SPL_BUILD
#define CONFIG_VID
#endif
#define CONFIG_VOL_MONITOR_IR36021_SET
#define CONFIG_VOL_MONITOR_INA220
/* The lowest and highest voltage allowed for LS1046AQDS */
#define VDD_MV_MIN			819
#define VDD_MV_MAX			1212

/*
 * Miscellaneous configurable options
 */
#define CONFIG_MISC_INIT_R
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_AUTO_COMPLETE
#define CONFIG_SYS_PBSIZE		\
		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		0x9fffffff

#define CONFIG_SYS_HZ			1000

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)

#define CONFIG_SYS_MONITOR_BASE CONFIG_SYS_TEXT_BASE    /* start of monitor */

/*
 * Environment
 */
#define CONFIG_ENV_OVERWRITE

#ifdef CONFIG_NAND_BOOT
#define CONFIG_ENV_SIZE			0x2000
#define CONFIG_ENV_OFFSET		(24 * CONFIG_SYS_NAND_BLOCK_SIZE)
#elif defined(CONFIG_SD_BOOT)
#define CONFIG_ENV_OFFSET		(3 * 1024 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV		0
#define CONFIG_ENV_SIZE			0x2000
#elif defined(CONFIG_QSPI_BOOT)
#define CONFIG_ENV_SIZE			0x2000          /* 8KB */
#define CONFIG_ENV_OFFSET		0x300000        /* 3MB */
#define CONFIG_ENV_SECT_SIZE		0x10000
#else
#define CONFIG_ENV_ADDR			(CONFIG_SYS_FLASH_BASE + 0x300000)
#define CONFIG_ENV_SECT_SIZE		0x20000
#define CONFIG_ENV_SIZE			0x20000
#endif

#define CONFIG_CMDLINE_TAG

#undef CONFIG_BOOTCOMMAND
#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
#define CONFIG_BOOTCOMMAND		"sf probe && sf read $kernel_load "    \
					"e0000 f00000 && bootm $kernel_load"
#else
#define CONFIG_BOOTCOMMAND		"cp.b $kernel_start $kernel_load "     \
					"$kernel_size && bootm $kernel_load"
#endif

#if defined(CONFIG_QSPI_BOOT) || defined(CONFIG_SD_BOOT_QSPI)
#define MTDPARTS_DEFAULT "mtdparts=1550000.quadspi:2m(uboot)," \
			"14m(free)"
#else
#define MTDPARTS_DEFAULT "mtdparts=60000000.nor:" \
			"2m@0x100000(nor_bank0_uboot),"\
			"40m@0x1100000(nor_bank0_fit)," \
			"7m(nor_bank0_user)," \
			"2m@0x4100000(nor_bank4_uboot)," \
			"40m@0x5100000(nor_bank4_fit),"\
			"-(nor_bank4_user);" \
			"7e800000.flash:" \
			"4m(nand_uboot),36m(nand_kernel)," \
			"472m(nand_free);spi0.0:2m(uboot)," \
			"14m(free)"
#endif

#include <asm/fsl_secure_boot.h>

#endif /* __LS1046AQDS_H__ */
