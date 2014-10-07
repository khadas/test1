/*
 * Copyright 2014, Freescale Semiconductor
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ASM_ARMV7_LS102XA_CONFIG_
#define _ASM_ARMV7_LS102XA_CONFIG_

#define CONFIG_SYS_CACHELINE_SIZE		64

#define OCRAM_BASE_ADDR				0x10000000
#define OCRAM_SIZE				0x00020000

#define CONFIG_SYS_IMMR				0x01000000

#define CONFIG_SYS_FSL_DDR_ADDR			(CONFIG_SYS_IMMR + 0x00080000)
#define CONFIG_SYS_CCI400_ADDR			(CONFIG_SYS_IMMR + 0x00180000)
#define CONFIG_SYS_IFC_ADDR			(CONFIG_SYS_IMMR + 0x00530000)
#define CONFIG_SYS_FSL_ESDHC_ADDR		(CONFIG_SYS_IMMR + 0x00560000)
#define CONFIG_SYS_FSL_SCFG_ADDR		(CONFIG_SYS_IMMR + 0x00570000)
#define CONFIG_SYS_FSL_SERDES_ADDR		(CONFIG_SYS_IMMR + 0x00ea0000)
#define CONFIG_SYS_FSL_GUTS_ADDR		(CONFIG_SYS_IMMR + 0x00ee0000)
#define CONFIG_SYS_FSL_LS1_CLK_ADDR		(CONFIG_SYS_IMMR + 0x00ee1000)
#define CONFIG_SYS_NS16550_COM1			(CONFIG_SYS_IMMR + 0x011c0500)
#define CONFIG_SYS_NS16550_COM2			(CONFIG_SYS_IMMR + 0x011d0500)
#define CONFIG_SYS_DCU_ADDR			(CONFIG_SYS_IMMR + 0x01ce0000)

#define CONFIG_SYS_TSEC1_OFFSET			0x01d10000
#define CONFIG_SYS_TSEC2_OFFSET			0x01d50000
#define CONFIG_SYS_TSEC3_OFFSET			0x01d90000
#define CONFIG_SYS_MDIO1_OFFSET			0x01d24000

#define TSEC_BASE_ADDR	(CONFIG_SYS_IMMR + CONFIG_SYS_TSEC1_OFFSET)
#define MDIO_BASE_ADDR	(CONFIG_SYS_IMMR + CONFIG_SYS_MDIO1_OFFSET)

#define SCTR_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01b00000)

#define I2C1_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01180000)
#define I2C2_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01190000)
#define I2C3_BASE_ADDR				(CONFIG_SYS_IMMR + 0x011a0000)

#define WDOG1_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01ad0000)

#define QSPI0_BASE_ADDR				(CONFIG_SYS_IMMR + 0x00550000)
#define DSPI1_BASE_ADDR				(CONFIG_SYS_IMMR + 0x01100000)

#define LPUART_BASE				(CONFIG_SYS_IMMR + 0x01950000)

#ifdef CONFIG_DDR_SPD
#define CONFIG_SYS_FSL_DDR_BE
#define CONFIG_VERY_BIG_RAM
#ifdef CONFIG_SYS_FSL_DDR4
#define CONFIG_SYS_FSL_DDRC_GEN4
#else
#define CONFIG_SYS_FSL_DDRC_ARM_GEN3
#endif
#define CONFIG_SYS_FSL_DDR
#define CONFIG_SYS_LS1_DDR_BLOCK1_SIZE		((phys_size_t)2 << 30)
#define CONFIG_MAX_MEM_MAPPED			CONFIG_SYS_LS1_DDR_BLOCK1_SIZE
#endif

#define CONFIG_SYS_FSL_IFC_BE
#define CONFIG_SYS_FSL_ESDHC_BE
#define CONFIG_SYS_FSL_WDOG_BE
#define CONFIG_SYS_FSL_DSPI_BE
#define CONFIG_SYS_FSL_QSPI_BE
#define CONFIG_SYS_FSL_DCU_BE

#define DCU_LAYER_MAX_NUM			16

#define CONFIG_SYS_FSL_SRDS_1

#ifdef CONFIG_LS102XA
#define CONFIG_MAX_CPUS				2
#define CONFIG_SYS_FSL_IFC_BANK_COUNT		8
#define CONFIG_NUM_DDR_CONTROLLERS		1
#define CONFIG_SYS_FSL_DDR_VER			FSL_DDR_VER_5_0
#else
#error SoC not defined
#endif

#endif /* _ASM_ARMV7_LS102XA_CONFIG_ */
