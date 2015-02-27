/*
 * Copyright 2011-2012 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ASM_MPC85xx_CONFIG_H_
#define _ASM_MPC85xx_CONFIG_H_

/* SoC specific defines for Freescale MPC85xx (PQ3) and QorIQ processors */

#ifdef CONFIG_SYS_CCSRBAR_DEFAULT
#error "Do not define CONFIG_SYS_CCSRBAR_DEFAULT in the board header file."
#endif

/*
 * This macro should be removed when we no longer care about backwards
 * compatibility with older operating systems.
 */
#define CONFIG_PPC_SPINTABLE_COMPATIBLE

#include <fsl_ddrc_version.h>
#define CONFIG_SYS_FSL_DDR_BE

/* IP endianness */
#define CONFIG_SYS_FSL_IFC_BE
#define CONFIG_SYS_FSL_SEC_BE
#define CONFIG_SYS_FSL_SFP_BE

/* Number of TLB CAM entries we have on FSL Book-E chips */
#if defined(CONFIG_E500MC)
#define CONFIG_SYS_NUM_TLBCAMS		64
#elif defined(CONFIG_E500)
#define CONFIG_SYS_NUM_TLBCAMS		16
#endif

#if defined(CONFIG_MPC8536)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	1
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_MPC8540)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		8
#define CONFIG_SYS_FSL_DDRC_GEN1
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000

#elif defined(CONFIG_MPC8541)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		8
#define CONFIG_SYS_FSL_DDRC_GEN1
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000

#elif defined(CONFIG_MPC8544)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		10
#define CONFIG_SYS_FSL_DDRC_GEN2
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	0
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_MPC8548)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		10
#define CONFIG_SYS_FSL_DDRC_GEN2
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	0
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_NMG_DDR120
#define CONFIG_SYS_FSL_ERRATUM_NMG_LBC103
#define CONFIG_SYS_FSL_ERRATUM_NMG_ETSEC129
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	1
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_RMU
#define CONFIG_SYS_FSL_SRIO_MSG_UNIT_NUM	2
#define CONFIG_SYS_FSL_ERRATUM_A005125
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x00

#elif defined(CONFIG_MPC8555)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		8
#define CONFIG_SYS_FSL_DDRC_GEN1
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000

#elif defined(CONFIG_MPC8560)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		8
#define CONFIG_SYS_FSL_DDRC_GEN1
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000

#elif defined(CONFIG_MPC8568)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		10
#define CONFIG_SYS_FSL_DDRC_GEN2
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define QE_MURAM_SIZE			0x10000UL
#define MAX_QE_RISC			2
#define QE_NUM_OF_SNUM			28
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	1
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_RMU
#define CONFIG_SYS_FSL_SRIO_MSG_UNIT_NUM	2

#elif defined(CONFIG_MPC8569)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		10
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define QE_MURAM_SIZE			0x20000UL
#define MAX_QE_RISC			4
#define QE_NUM_OF_SNUM			46
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	1
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_RMU
#define CONFIG_SYS_FSL_SRIO_MSG_UNIT_NUM	2
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_MPC8572)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_DDR_115
#define CONFIG_SYS_FSL_ERRATUM_DDR111_DDR134
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_P1010)
#define CONFIG_MAX_CPUS			1
#define CONFIG_FSL_SDHC_V2_3
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	3
#define CONFIG_TSECV2
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	4
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.2"
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_IFC_A002769
#define CONFIG_SYS_FSL_ERRATUM_P1010_A003549
#define CONFIG_SYS_FSL_ERRATUM_SEC_A003571
#define CONFIG_SYS_FSL_ERRATUM_IFC_A003399
#define CONFIG_SYS_FSL_ERRATUM_A005125
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A007075
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x10
#define CONFIG_ESDHC_HC_BLK_ADDR

/* P1011 is single core version of P1020 */
#elif defined(CONFIG_P1011)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_FSL_PCIE_DISABLE_ASPM
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

/* P1012 is single core version of P1021 */
#elif defined(CONFIG_P1012)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_FSL_PCIE_DISABLE_ASPM
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define QE_MURAM_SIZE			0x6000UL
#define MAX_QE_RISC			1
#define QE_NUM_OF_SNUM			28
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

/* P1013 is single core version of P1022 */
#elif defined(CONFIG_P1013)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_FSL_SATA_ERRATUM_A001
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_P1014)
#define CONFIG_MAX_CPUS			1
#define CONFIG_FSL_SDHC_V2_3
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	3
#define CONFIG_TSECV2
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_IFC_A002769
#define CONFIG_SYS_FSL_ERRATUM_P1010_A003549
#define CONFIG_SYS_FSL_ERRATUM_IFC_A003399
#define CONFIG_SYS_FSL_ERRATUM_A004508

/* P1017 is single core version of P1023 */
#elif defined(CONFIG_P1017)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_NUM_FM1_DTSEC	2
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_QMAN_NUM_PORTALS	3
#define CONFIG_SYS_BMAN_NUM_PORTALS	3
#define CONFIG_SYS_FM_MURAM_SIZE	0x10000
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.2"
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff600000
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_P1020)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_FSL_PCIE_DISABLE_ASPM
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125
#ifndef CONFIG_USB_MAX_CONTROLLER_COUNT
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#endif

#elif defined(CONFIG_P1021)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_FSL_PCIE_DISABLE_ASPM
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define QE_MURAM_SIZE			0x6000UL
#define MAX_QE_RISC			1
#define QE_NUM_OF_SNUM			28
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1

#elif defined(CONFIG_P1022)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_FSL_SATA_ERRATUM_A001
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_P1023)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_NUM_FM1_DTSEC	2
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_QMAN_NUM_PORTALS	3
#define CONFIG_SYS_BMAN_NUM_PORTALS	3
#define CONFIG_SYS_FM_MURAM_SIZE	0x10000
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.2"
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff600000
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x11

/* P1024 is lower end variant of P1020 */
#elif defined(CONFIG_P1024)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_FSL_PCIE_DISABLE_ASPM
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

/* P1025 is lower end variant of P1021 */
#elif defined(CONFIG_P1025)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_TSECV2
#define CONFIG_FSL_PCIE_DISABLE_ASPM
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define QE_MURAM_SIZE			0x6000UL
#define MAX_QE_RISC			1
#define QE_NUM_OF_SNUM			28
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

/* P2010 is single core version of P2020 */
#elif defined(CONFIG_P2010)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_ESDHC_A001
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_P2020)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	2
#define CONFIG_SYS_FSL_SEC_COMPAT	2
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_ESDHC_A001
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_RMU
#define CONFIG_SYS_FSL_SRIO_MSG_UNIT_NUM	2
#define CONFIG_SYS_FSL_ERRATUM_A004508
#define CONFIG_SYS_FSL_ERRATUM_A005125
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1

#elif defined(CONFIG_PPC_P2041) /* also supports P2040 */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS1
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_MAX_CPUS			4
#define CONFIG_SYS_FSL_NUM_CC_PLLS	2
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_NUM_FM1_DTSEC	5
#define CONFIG_SYS_NUM_FM1_10GEC	1
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_FM_MURAM_SIZE	0x28000
#define CONFIG_SYS_FSL_TBCLK_DIV	32
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.2"
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_USB1_PHY_ENABLE
#define CONFIG_SYS_FSL_USB2_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_NMG_CPU_A011
#define CONFIG_SYS_FSL_ERRATUM_USB14
#define CONFIG_SYS_FSL_ERRATUM_CPU_A003999
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003474
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_ERRATUM_A004510
#define CONFIG_SYS_FSL_ERRATUM_A004510_SVR_REV	0x10
#define CONFIG_SYS_FSL_ERRATUM_A004510_SVR_REV2	0x11
#define CONFIG_SYS_FSL_CORENET_SNOOPVEC_COREONLY 0xf0000000
#define CONFIG_SYS_FSL_ERRATUM_SRIO_A004034
#define CONFIG_SYS_FSL_ERRATUM_A004849
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x11

#elif defined(CONFIG_PPC_P3041)
#define CONFIG_SYS_FSL_QORIQ_CHASSIS1
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_MAX_CPUS			4
#define CONFIG_SYS_FSL_NUM_CC_PLLS	2
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_NUM_FM1_DTSEC	5
#define CONFIG_SYS_NUM_FM1_10GEC	1
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_5
#define CONFIG_SYS_FM_MURAM_SIZE	0x28000
#define CONFIG_SYS_FSL_TBCLK_DIV	32
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.2"
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_USB1_PHY_ENABLE
#define CONFIG_SYS_FSL_USB2_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_NMG_CPU_A011
#define CONFIG_SYS_FSL_ERRATUM_USB14
#define CONFIG_SYS_FSL_ERRATUM_CPU_A003999
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003474
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_ERRATUM_A004510
#define CONFIG_SYS_FSL_ERRATUM_A004510_SVR_REV	0x10
#define CONFIG_SYS_FSL_ERRATUM_A004510_SVR_REV2	0x11
#define CONFIG_SYS_FSL_CORENET_SNOOPVEC_COREONLY 0xf0000000
#define CONFIG_SYS_FSL_ERRATUM_SRIO_A004034
#define CONFIG_SYS_FSL_ERRATUM_A004849
#define CONFIG_SYS_FSL_ERRATUM_A005812
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x20

#elif defined(CONFIG_PPC_P4080) /* also supports P4040 */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS1
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_MAX_CPUS			8
#define CONFIG_SYS_FSL_NUM_CC_PLLS	4
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		2
#define CONFIG_SYS_NUM_FM1_DTSEC	4
#define CONFIG_SYS_NUM_FM2_DTSEC	4
#define CONFIG_SYS_NUM_FM1_10GEC	1
#define CONFIG_SYS_NUM_FM2_10GEC	1
#define CONFIG_NUM_DDR_CONTROLLERS	2
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_4
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_FM_MURAM_SIZE	0x28000
#define CONFIG_SYS_FSL_TBCLK_DIV	16
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,p4080-pcie"
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_ERRATUM_CPC_A002
#define CONFIG_SYS_FSL_ERRATUM_CPC_A003
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003
#define CONFIG_SYS_FSL_ERRATUM_ELBC_A001
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_ESDHC135
#define CONFIG_SYS_FSL_ERRATUM_ESDHC13
#define CONFIG_SYS_P4080_ERRATUM_CPU22
#define CONFIG_SYS_FSL_ERRATUM_NMG_CPU_A011
#define CONFIG_SYS_P4080_ERRATUM_SERDES8
#define CONFIG_SYS_P4080_ERRATUM_SERDES9
#define CONFIG_SYS_P4080_ERRATUM_SERDES_A001
#define CONFIG_SYS_P4080_ERRATUM_SERDES_A005
#define CONFIG_SYS_FSL_ERRATUM_CPU_A003999
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003474
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_RMU
#define CONFIG_SYS_FSL_SRIO_MSG_UNIT_NUM	2
#define CONFIG_SYS_FSL_ERRATUM_A004510
#define CONFIG_SYS_FSL_ERRATUM_A004510_SVR_REV	0x20
#define CONFIG_SYS_FSL_CORENET_SNOOPVEC_COREONLY 0xff000000
#define CONFIG_SYS_FSL_ERRATUM_SRIO_A004034
#define CONFIG_SYS_FSL_ERRATUM_A004849
#define CONFIG_SYS_FSL_ERRATUM_A004580
#define CONFIG_SYS_P4080_ERRATUM_PCIE_A003
#define CONFIG_SYS_FSL_ERRATUM_A005812
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_ERRATUM_A007075
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x20

#elif defined(CONFIG_PPC_P5020) /* also supports P5010 */
#define CONFIG_SYS_PPC64		/* 64-bit core */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS1
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_FSL_NUM_CC_PLLS	2
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_NUM_FM1_DTSEC	5
#define CONFIG_SYS_NUM_FM1_10GEC	1
#define CONFIG_NUM_DDR_CONTROLLERS	2
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_4
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_FM_MURAM_SIZE	0x28000
#define CONFIG_SYS_FSL_TBCLK_DIV	32
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.2"
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_USB1_PHY_ENABLE
#define CONFIG_SYS_FSL_USB2_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_USB14
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003474
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_ERRATUM_A004510
#define CONFIG_SYS_FSL_ERRATUM_A004510_SVR_REV	0x10
#define CONFIG_SYS_FSL_CORENET_SNOOPVEC_COREONLY 0xc0000000
#define CONFIG_SYS_FSL_ERRATUM_SRIO_A004034
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x20

#elif defined(CONFIG_PPC_P5040)
#define CONFIG_SYS_PPC64
#define CONFIG_SYS_FSL_QORIQ_CHASSIS1
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_MAX_CPUS			4
#define CONFIG_SYS_FSL_NUM_CC_PLLS	3
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		2
#define CONFIG_SYS_NUM_FM1_DTSEC	5
#define CONFIG_SYS_NUM_FM1_10GEC	1
#define CONFIG_SYS_NUM_FM2_DTSEC	5
#define CONFIG_SYS_NUM_FM2_10GEC	1
#define CONFIG_NUM_DDR_CONTROLLERS	2
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_4
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_FM_MURAM_SIZE	0x28000
#define CONFIG_SYS_FSL_TBCLK_DIV	16
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.4"
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_USB1_PHY_ENABLE
#define CONFIG_SYS_FSL_USB2_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_USB14
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003
#define CONFIG_SYS_FSL_ERRATUM_DDR_A003474
#define CONFIG_SYS_FSL_ERRATUM_A004699
#define CONFIG_SYS_FSL_ERRATUM_A004510
#define CONFIG_SYS_FSL_ERRATUM_A004510_SVR_REV	0x10
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_FSL_CORENET_SNOOPVEC_COREONLY 0xf0000000
#define CONFIG_SYS_FSL_ERRATUM_A005812

#elif defined(CONFIG_BSC9131)
#define CONFIG_MAX_CPUS			1
#define CONFIG_FSL_SDHC_V2_3
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_TSECV2
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_4
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_FSL_DSP_M2_RAM_ADDR	0xb0000000
#define CONFIG_SYS_FSL_DSP_CCSRBAR_DEFAULT	0xff600000
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	3
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_NAND_FSL_IFC
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_A005125
#define CONFIG_ESDHC_HC_BLK_ADDR

#elif defined(CONFIG_BSC9132)
#define CONFIG_MAX_CPUS			2
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	3
#define CONFIG_FSL_SDHC_V2_3
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_TSECV2
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_NUM_DDR_CONTROLLERS	2
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_6
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_FSL_DSP_DDR_ADDR	0x40000000
#define CONFIG_SYS_FSL_DSP_M2_RAM_ADDR	0xb0000000
#define CONFIG_SYS_FSL_DSP_M3_RAM_ADDR	0xc0000000
#define CONFIG_SYS_FSL_DSP_CCSRBAR_DEFAULT	0xff600000
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	3
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_NAND_FSL_IFC
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ESDHC_P1010_BROKEN_SDCLK
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.2"
#define CONFIG_SYS_FSL_ERRATUM_A005125
#define CONFIG_SYS_FSL_ERRATUM_A005434
#define CONFIG_SYS_FSL_ERRATUM_I2C_A004447
#define CONFIG_SYS_FSL_A004447_SVR_REV	0x11
#define CONFIG_ESDHC_HC_BLK_ADDR

#elif defined(CONFIG_PPC_T4240) || defined(CONFIG_PPC_T4160) || \
	defined(CONFIG_PPC_T4080)
#define CONFIG_E6500
#define CONFIG_SYS_PPC64		/* 64-bit core */
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS2	/* Freescale Chassis generation 2 */
#define CONFIG_SYS_FSL_CORES_PER_CLUSTER 4
#define CONFIG_SYS_FSL_QMAN_V3		/* QMAN version 3 */
#ifdef CONFIG_PPC_T4240
#define CONFIG_MAX_CPUS			12
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS   { 1, 1, 4 }
#define CONFIG_SYS_NUM_FM1_DTSEC	8
#define CONFIG_SYS_NUM_FM1_10GEC	2
#define CONFIG_SYS_NUM_FM2_DTSEC	8
#define CONFIG_SYS_NUM_FM2_10GEC	2
#define CONFIG_NUM_DDR_CONTROLLERS	3
#else
#define CONFIG_SYS_NUM_FM1_DTSEC	6
#define CONFIG_SYS_NUM_FM1_10GEC	1
#define CONFIG_SYS_NUM_FM2_DTSEC	8
#define CONFIG_SYS_NUM_FM2_10GEC	1
#define CONFIG_NUM_DDR_CONTROLLERS	2
#if defined(CONFIG_PPC_T4160)
#define CONFIG_MAX_CPUS			8
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS	{ 1, 1 }
#elif defined(CONFIG_PPC_T4080)
#define CONFIG_MAX_CPUS			4
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS	{ 1 }
#endif
#endif
#define CONFIG_SYS_FSL_NUM_CC_PLLS	5
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SRDS_1
#define CONFIG_SYS_FSL_SRDS_2
#define CONFIG_SYS_FSL_SRDS_3
#define CONFIG_SYS_FSL_SRDS_4
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		2
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_PME_CLK		0
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_7
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	8
#define CONFIG_SYS_FMAN_V3
#define CONFIG_SYS_FM1_CLK		3
#define CONFIG_SYS_FM2_CLK		3
#define CONFIG_SYS_FM_MURAM_SIZE	0x60000
#define CONFIG_SYS_FSL_TBCLK_DIV	16
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v3.0"
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_SRIO_LIODN
#define CONFIG_SYS_FSL_USB_DUAL_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_A004468
#define CONFIG_SYS_FSL_ERRATUM_A_004934
#define CONFIG_SYS_FSL_ERRATUM_A005871
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_FSL_ERRATUM_A006379
#define CONFIG_SYS_FSL_ERRATUM_A007186
#define CONFIG_SYS_FSL_ERRATUM_A006593
#define CONFIG_SYS_FSL_ERRATUM_A007798
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_SFP_VER_3_0
#define CONFIG_SYS_FSL_PCI_VER_3_X

#elif defined(CONFIG_PPC_B4860) || defined(CONFIG_PPC_B4420)
#define CONFIG_E6500
#define CONFIG_SYS_PPC64		/* 64-bit core */
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS2	/* Freescale Chassis generation 2 */
#define CONFIG_SYS_FSL_QMAN_V3		/* QMAN version 3 */
#define CONFIG_HETROGENOUS_CLUSTERS     /* DSP/SC3900 core clusters */
#define CONFIG_PPC_CLUSTER_START	0 /*Start index of ppc clusters*/
#define CONFIG_DSP_CLUSTER_START	1 /*Start index of dsp clusters*/
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SRDS_1
#define CONFIG_SYS_FSL_SRDS_2
#define CONFIG_SYS_MAPLE
#define CONFIG_SYS_CPRI
#define CONFIG_SYS_FSL_NUM_CC_PLLS	5
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_FM1_CLK		0
#define CONFIG_SYS_CPRI_CLK		3
#define CONFIG_SYS_ULB_CLK		4
#define CONFIG_SYS_ETVPE_CLK		1
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_7
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	4
#define CONFIG_SYS_FMAN_V3
#define CONFIG_SYS_FM_MURAM_SIZE	0x60000
#define CONFIG_SYS_FSL_TBCLK_DIV	16
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.4"
#define CONFIG_SYS_FSL_USB1_PHY_ENABLE
#define CONFIG_SYS_FSL_ERRATUM_A_004934
#define CONFIG_SYS_FSL_ERRATUM_A005871
#define CONFIG_SYS_FSL_ERRATUM_A006379
#define CONFIG_SYS_FSL_ERRATUM_A007186
#define CONFIG_SYS_FSL_ERRATUM_A006593
#define CONFIG_SYS_FSL_ERRATUM_A007075
#define CONFIG_SYS_FSL_ERRATUM_A006475
#define CONFIG_SYS_FSL_ERRATUM_A006384
#define CONFIG_SYS_FSL_ERRATUM_A007212
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_SFP_VER_3_0

#ifdef CONFIG_PPC_B4860
#define CONFIG_SYS_FSL_CORES_PER_CLUSTER 4
#define CONFIG_MAX_CPUS			4
#define CONFIG_MAX_DSP_CPUS		12
#define CONFIG_NUM_DSP_CPUS		6
#define CONFIG_SYS_FSL_SRDS_NUM_PLLS	2
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS	{ 1, 4, 4, 4 }
#define CONFIG_SYS_NUM_FM1_DTSEC	6
#define CONFIG_SYS_NUM_FM1_10GEC	2
#define CONFIG_NUM_DDR_CONTROLLERS	2
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#define CONFIG_SYS_FSL_SRIO_LIODN
#else
#define CONFIG_MAX_CPUS			2
#define CONFIG_MAX_DSP_CPUS		2
#define CONFIG_SYS_FSL_SRDS_NUM_PLLS	1
#define CONFIG_SYS_FSL_CORES_PER_CLUSTER 2
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS	{ 1, 4 }
#define CONFIG_SYS_NUM_FM1_DTSEC	4
#define CONFIG_SYS_NUM_FM1_10GEC	0
#define CONFIG_NUM_DDR_CONTROLLERS	1
#endif

#elif defined(CONFIG_PPC_T1040) || defined(CONFIG_PPC_T1042) ||\
defined(CONFIG_PPC_T1020) || defined(CONFIG_PPC_T1022)
#define CONFIG_E5500
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS2	/* Freescale Chassis generation 2 */
#define CONFIG_SYS_FSL_CORES_PER_CLUSTER 1
#define CONFIG_SYS_FSL_QMAN_V3		/* QMAN version 3 */
#ifdef CONFIG_SYS_FSL_DDR4
#define CONFIG_SYS_FSL_DDRC_GEN4
#endif
#if defined(CONFIG_PPC_T1040) || defined(CONFIG_PPC_T1042)
#define CONFIG_MAX_CPUS			4
#elif defined(CONFIG_PPC_T1020) || defined(CONFIG_PPC_T1022)
#define CONFIG_MAX_CPUS			2
#endif
#define CONFIG_SYS_FSL_NUM_CC_PLLS	2
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS   { 1, 1, 1, 1 }
#define CONFIG_SYS_SDHC_CLOCK		0
#define CONFIG_SYS_FSL_NUM_LAWS		16
#define CONFIG_SYS_FSL_SRDS_1
#define CONFIG_SYS_FSL_SEC_COMPAT	5
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_NUM_FM1_DTSEC	5
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_PME_PLAT_CLK_DIV		2
#define CONFIG_SYS_PME_CLK		CONFIG_PME_PLAT_CLK_DIV
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_5_0
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	8
#define CONFIG_SYS_FSL_ERRATUM_A008044
#define CONFIG_SYS_FMAN_V3
#define CONFIG_FM_PLAT_CLK_DIV	1
#define CONFIG_SYS_FM1_CLK		CONFIG_FM_PLAT_CLK_DIV
#define CONFIG_SYS_FM_MURAM_SIZE	0x30000
#define CONFIG_SYS_FSL_SINGLE_SOURCE_CLK
#define CONFIG_SYS_FSL_TBCLK_DIV	16
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.4"
#define CONFIG_SYS_FSL_USB_DUAL_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define ESDHCI_QUIRK_BROKEN_TIMEOUT_VALUE
#define QE_MURAM_SIZE			0x6000UL
#define MAX_QE_RISC			1
#define QE_NUM_OF_SNUM			28

#elif defined(CONFIG_PPC_T1024) || defined(CONFIG_PPC_T1023) ||\
defined(CONFIG_PPC_T1014) || defined(CONFIG_PPC_T1013)
#define CONFIG_E5500
#define CONFIG_FSL_CORENET	     /* Freescale CoreNet platform */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS2  /* Freescale Chassis generation 2 */
#define CONFIG_SYS_FSL_CORES_PER_CLUSTER 1
#define CONFIG_SYS_FSL_QMAN_V3	 /* QMAN version 3 */
#define CONFIG_SYS_FMAN_V3
#ifdef CONFIG_SYS_FSL_DDR4
#define CONFIG_SYS_FSL_DDRC_GEN4
#endif
#if defined(CONFIG_PPC_T1024) || defined(CONFIG_PPC_T1023)
#define CONFIG_MAX_CPUS			2
#elif defined(CONFIG_PPC_T1014) || defined(CONFIG_PPC_T1013)
#define CONFIG_MAX_CPUS			1
#endif
#define CONFIG_SYS_FSL_NUM_CC_PLL	2
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS  { 1, 1, 1, 1 }
#define CONFIG_SYS_SDHC_CLOCK		0
#define CONFIG_SYS_FSL_NUM_LAWS		16
#define CONFIG_SYS_FSL_SRDS_1
#define CONFIG_SYS_FSL_SEC_COMPAT	5
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_NUM_FM1_DTSEC	4
#define CONFIG_SYS_NUM_FM1_10GEC	1
#define CONFIG_FSL_FM_10GEC_REGULAR_NOTATION
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_USB_MAX_CONTROLLER_COUNT	2
#define CONFIG_SYS_FSL_DDR_VER	 FSL_DDR_VER_5_0
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	8
#define CONFIG_SYS_FM1_CLK		0
#define CONFIG_QBMAN_CLK_DIV		1
#define CONFIG_SYS_FM_MURAM_SIZE	0x30000
#define CONFIG_SYS_FSL_SINGLE_SOURCE_CLK
#define CONFIG_SYS_FSL_TBCLK_DIV	16
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v2.4"
#define CONFIG_SYS_FSL_USB_DUAL_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define ESDHCI_QUIRK_BROKEN_TIMEOUT_VALUE
#define QE_MURAM_SIZE			0x6000UL
#define MAX_QE_RISC			1
#define QE_NUM_OF_SNUM			28
#define CONFIG_SYS_FSL_SFP_VER_3_0

#elif defined(CONFIG_PPC_T2080) || defined(CONFIG_PPC_T2081)
#define CONFIG_E6500
#define CONFIG_SYS_PPC64		/* 64-bit core */
#define CONFIG_FSL_CORENET		/* Freescale CoreNet platform */
#define CONFIG_SYS_FSL_QORIQ_CHASSIS2	/* Freescale Chassis generation 2 */
#define CONFIG_SYS_FSL_CORES_PER_CLUSTER 4
#define CONFIG_SYS_FSL_NUM_CC_PLLS	2
#define CONFIG_SYS_FSL_QMAN_V3
#define CONFIG_MAX_CPUS			4
#define CONFIG_SYS_FSL_NUM_LAWS		32
#define CONFIG_SYS_FSL_SEC_COMPAT	4
#define CONFIG_SYS_NUM_FMAN		1
#define CONFIG_SYS_FSL_CLUSTER_CLOCKS	{ 1, 4, 4, 4 }
#define CONFIG_SYS_FSL_SRDS_1
#define CONFIG_SYS_FSL_PCI_VER_3_X
#if defined(CONFIG_PPC_T2080)
#define CONFIG_SYS_NUM_FM1_DTSEC	8
#define CONFIG_SYS_NUM_FM1_10GEC	4
#define CONFIG_SYS_FSL_SRDS_2
#define CONFIG_SYS_FSL_SRIO_LIODN
#define CONFIG_SYS_FSL_SRIO_MAX_PORTS	2
#define CONFIG_SYS_FSL_SRIO_OB_WIN_NUM	9
#define CONFIG_SYS_FSL_SRIO_IB_WIN_NUM	5
#elif defined(CONFIG_PPC_T2081)
#define CONFIG_SYS_NUM_FM1_DTSEC	6
#define CONFIG_SYS_NUM_FM1_10GEC	2
#endif
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_PME_PLAT_CLK_DIV		1
#define CONFIG_SYS_PME_CLK		CONFIG_PME_PLAT_CLK_DIV
#define CONFIG_SYS_FM1_CLK		0
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_7
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	8
#define CONFIG_SYS_FMAN_V3
#define CONFIG_SYS_FM_MURAM_SIZE	0x28000
#define CONFIG_SYS_FSL_TBCLK_DIV	16
#define CONFIG_SYS_FSL_PCIE_COMPAT	"fsl,qoriq-pcie-v3.0"
#define CONFIG_SYS_FSL_USB_DUAL_PHY_ENABLE
#define CONFIG_SYS_FSL_USB_INTERNAL_UTMI_PHY
#define CONFIG_SYS_FSL_ERRATUM_A007212
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xfe000000
#define CONFIG_SYS_FSL_SFP_VER_3_0
#define CONFIG_SYS_FSL_ISBC_VER		2
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_SYS_FSL_ERRATUM_A006261
#define CONFIG_SYS_FSL_ERRATUM_A006593
#define CONFIG_SYS_FSL_ERRATUM_A007186
#define CONFIG_SYS_FSL_ERRATUM_A006379
#define ESDHCI_QUIRK_BROKEN_TIMEOUT_VALUE
#define CONFIG_SYS_FSL_SFP_VER_3_0


#elif defined(CONFIG_PPC_C29X)
#define CONFIG_MAX_CPUS			1
#define CONFIG_FSL_SDHC_V2_3
#define CONFIG_SYS_FSL_NUM_LAWS		12
#define CONFIG_SYS_PPC_E500_DEBUG_TLB	3
#define CONFIG_TSECV2_1
#define CONFIG_SYS_FSL_SEC_COMPAT	6
#define CONFIG_SYS_FSL_ERRATUM_ESDHC111
#define CONFIG_NUM_DDR_CONTROLLERS	1
#define CONFIG_SYS_FSL_DDR_VER		FSL_DDR_VER_4_6
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	8
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xff700000
#define CONFIG_SYS_FSL_ERRATUM_A005125

#elif defined(CONFIG_QEMU_E500)
#define CONFIG_MAX_CPUS			1
#define CONFIG_SYS_CCSRBAR_DEFAULT	0xe0000000

#else
#error Processor type not defined for this platform
#endif

#ifndef CONFIG_SYS_CCSRBAR_DEFAULT
#error "CONFIG_SYS_CCSRBAR_DEFAULT is not defined for this platform."
#endif

#ifdef CONFIG_E6500
#define CONFIG_SYS_FSL_THREADS_PER_CORE 2
#else
#define CONFIG_SYS_FSL_THREADS_PER_CORE 1
#endif

#if !defined(CONFIG_SYS_FSL_DDRC_GEN1) && \
	!defined(CONFIG_SYS_FSL_DDRC_GEN2) && \
	!defined(CONFIG_SYS_FSL_DDRC_GEN3) && \
	!defined(CONFIG_SYS_FSL_DDRC_GEN4)
#define CONFIG_SYS_FSL_DDRC_GEN3
#endif

#endif /* _ASM_MPC85xx_CONFIG_H_ */
