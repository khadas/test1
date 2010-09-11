/*----------------------------------------------------------------------------+
|       This source code is dual-licensed.  You may use it under the terms of
|       the GNU General Public License version 2, or under the license below.
|
|       This source code has been made available to you by IBM on an AS-IS
|       basis.  Anyone receiving this source is licensed under IBM
|       copyrights to use it in any way he or she deems fit, including
|       copying it, modifying it, compiling it, and redistributing it either
|       with or without modifications.  No license under IBM patents or
|       patent applications is to be implied by the copyright license.
|
|       Any user of this software should understand that IBM cannot provide
|       technical support for this software and will not be responsible for
|       any consequences resulting from the use of this software.
|
|       Any person who transfers this source code or any derivative work
|       must include the IBM copyright notice, this paragraph, and the
|       preceding two paragraphs in the transferred software.
|
|       COPYRIGHT   I B M   CORPORATION 1999
|       LICENSED MATERIAL  -  PROGRAM PROPERTY OF I B M
+----------------------------------------------------------------------------*/

#ifndef	__PPC4XX_H__
#define __PPC4XX_H__

/*
 * Include SoC specific headers
 */
#if defined(CONFIG_405CR)
#include <asm/ppc405cr.h>
#endif

#if defined(CONFIG_405EP)
#include <asm/ppc405ep.h>
#endif

#if defined(CONFIG_405EX)
#include <asm/ppc405ex.h>
#endif

#if defined(CONFIG_405EZ)
#include <asm/ppc405ez.h>
#endif

#if defined(CONFIG_405GP)
#include <asm/ppc405gp.h>
#endif

#if defined(CONFIG_440EP) || defined(CONFIG_440GR)
#include <asm/ppc440ep_gr.h>
#endif

#if defined(CONFIG_440EPX) || defined(CONFIG_440GRX)
#include <asm/ppc440epx_grx.h>
#endif

#if defined(CONFIG_440GP)
#include <asm/ppc440gp.h>
#endif

#if defined(CONFIG_440GX)
#include <asm/ppc440gx.h>
#endif

#if defined(CONFIG_440SP)
#include <asm/ppc440sp.h>
#endif

#if defined(CONFIG_440SPE)
#include <asm/ppc440spe.h>
#endif

#if defined(CONFIG_460EX) || defined(CONFIG_460GT)
#include <asm/ppc460ex_gt.h>
#endif

#if defined(CONFIG_460SX)
#include <asm/ppc460sx.h>
#endif

/*
 * Configure which SDRAM/DDR/DDR2 controller is equipped
 */
// test-only: what to do with these???
#if defined(CONFIG_AP1000) || defined(CONFIG_ML2)
#define CONFIG_SDRAM_PPC4xx_IBM_SDRAM	/* IBM SDRAM controller */
#endif

/*
 * Common registers for all SoC's
 */
/* DCR registers */
#define PLB3A0_ACR	0x0077
#define PLB4A0_ACR	0x0081
#define PLB4A1_ACR	0x0089

#define PLB4Ax_ACR_PPM_MASK		0xf0000000
#define PLB4Ax_ACR_PPM_FIXED		0x00000000
#define PLB4Ax_ACR_PPM_FAIR		0xd0000000
#define PLB4Ax_ACR_HBU_MASK		0x08000000
#define PLB4Ax_ACR_HBU_DISABLED		0x00000000
#define PLB4Ax_ACR_HBU_ENABLED		0x08000000
#define PLB4Ax_ACR_RDP_MASK		0x06000000
#define PLB4Ax_ACR_RDP_DISABLED		0x00000000
#define PLB4Ax_ACR_RDP_2DEEP		0x02000000
#define PLB4Ax_ACR_RDP_3DEEP		0x04000000
#define PLB4Ax_ACR_RDP_4DEEP		0x06000000
#define PLB4Ax_ACR_WRP_MASK		0x01000000
#define PLB4Ax_ACR_WRP_DISABLED		0x00000000
#define PLB4Ax_ACR_WRP_2DEEP		0x01000000

/* General Purpose Timer (GPT) Register Offsets */
#define GPT0_TBC		0x00000000
#define GPT0_IM			0x00000018
#define GPT0_ISS		0x0000001C
#define GPT0_ISC		0x00000020
#define GPT0_IE			0x00000024
#define GPT0_COMP0		0x00000080
#define GPT0_COMP1		0x00000084
#define GPT0_COMP2		0x00000088
#define GPT0_COMP3		0x0000008C
#define GPT0_COMP4		0x00000090
#define GPT0_COMP5		0x00000094
#define GPT0_COMP6		0x00000098
#define GPT0_MASK0		0x000000C0
#define GPT0_MASK1		0x000000C4
#define GPT0_MASK2		0x000000C8
#define GPT0_MASK3		0x000000CC
#define GPT0_MASK4		0x000000D0
#define GPT0_MASK5		0x000000D4
#define GPT0_MASK6		0x000000D8
#define GPT0_DCT0		0x00000110
#define GPT0_DCIS		0x0000011C

#if defined(CONFIG_440)
#include <asm/ppc440.h>
#else
#include <asm/ppc405.h>
#endif

#include <asm/ppc4xx-sdram.h>
#include <asm/ppc4xx-ebc.h>
#if !defined(CONFIG_XILINX_440)
#include <asm/ppc4xx-uic.h>
#endif

/*
 * Macro for generating register field mnemonics
 */
#define	PPC_REG_BITS		32
#define	PPC_REG_VAL(bit, value)	((value) << ((PPC_REG_BITS - 1) - (bit)))

/*
 * Elide casts when assembling register mnemonics
 */
#ifndef __ASSEMBLY__
#define	static_cast(type, val)	(type)(val)
#else
#define	static_cast(type, val)	(val)
#endif

/*
 * Common stuff for 4xx (405 and 440)
 */

#define EXC_OFF_SYS_RESET	0x0100	/* System reset			*/
#define _START_OFFSET		(EXC_OFF_SYS_RESET + 0x2000)

#define RESET_VECTOR	0xfffffffc
#define CACHELINE_MASK	(CONFIG_SYS_CACHELINE_SIZE - 1) /* Address mask for
						cache line aligned data. */

#define CPR0_DCR_BASE	0x0C
#define CPR0_CFGADDR	(CPR0_DCR_BASE + 0x0)
#define CPR0_CFGDATA	(CPR0_DCR_BASE + 0x1)

#define SDR_DCR_BASE	0x0E
#define SDR0_CFGADDR	(SDR_DCR_BASE + 0x0)
#define SDR0_CFGDATA	(SDR_DCR_BASE + 0x1)

#define SDRAM_DCR_BASE	0x10
#define SDRAM0_CFGADDR	(SDRAM_DCR_BASE + 0x0)
#define SDRAM0_CFGDATA	(SDRAM_DCR_BASE + 0x1)

#define EBC_DCR_BASE	0x12
#define EBC0_CFGADDR	(EBC_DCR_BASE + 0x0)
#define EBC0_CFGDATA	(EBC_DCR_BASE + 0x1)

/*
 * Macros for indirect DCR access
 */
#define mtcpr(reg, d)	\
  do { mtdcr(CPR0_CFGADDR, reg); mtdcr(CPR0_CFGDATA, d); } while (0)
#define mfcpr(reg, d)	\
  do { mtdcr(CPR0_CFGADDR, reg); d = mfdcr(CPR0_CFGDATA); } while (0)

#define mtebc(reg, d)	\
  do { mtdcr(EBC0_CFGADDR, reg); mtdcr(EBC0_CFGDATA, d); } while (0)
#define mfebc(reg, d)	\
  do { mtdcr(EBC0_CFGADDR, reg); d = mfdcr(EBC0_CFGDATA); } while (0)

#define mtsdram(reg, d)	\
  do { mtdcr(SDRAM0_CFGADDR, reg); mtdcr(SDRAM0_CFGDATA, d); } while (0)
#define mfsdram(reg, d)	\
  do { mtdcr(SDRAM0_CFGADDR, reg); d = mfdcr(SDRAM0_CFGDATA); } while (0)

#define mtsdr(reg, d)	\
  do { mtdcr(SDR0_CFGADDR, reg); mtdcr(SDR0_CFGDATA, d); } while (0)
#define mfsdr(reg, d)	\
  do { mtdcr(SDR0_CFGADDR, reg); d = mfdcr(SDR0_CFGDATA); } while (0)

#ifndef __ASSEMBLY__

typedef struct
{
	unsigned long freqDDR;
	unsigned long freqEBC;
	unsigned long freqOPB;
	unsigned long freqPCI;
	unsigned long freqPLB;
	unsigned long freqTmrClk;
	unsigned long freqUART;
	unsigned long freqProcessor;
	unsigned long freqVCOHz;
	unsigned long freqVCOMhz;	/* in MHz                          */
	unsigned long pciClkSync;	/* PCI clock is synchronous        */
	unsigned long pciIntArbEn;	/* Internal PCI arbiter is enabled */
	unsigned long pllExtBusDiv;
	unsigned long pllFbkDiv;
	unsigned long pllFwdDiv;
	unsigned long pllFwdDivA;
	unsigned long pllFwdDivB;
	unsigned long pllOpbDiv;
	unsigned long pllPciDiv;
	unsigned long pllPlbDiv;
} PPC4xx_SYS_INFO;

static inline u32 get_mcsr(void)
{
	u32 val;

	asm volatile("mfspr %0, 0x23c" : "=r" (val) :);
	return val;
}

static inline void set_mcsr(u32 val)
{
	asm volatile("mtspr 0x23c, %0" : "=r" (val) :);
}

int ppc4xx_pci_sync_clock_config(u32 async);

#endif	/* __ASSEMBLY__ */

/* for multi-cpu support */
#define NA_OR_UNKNOWN_CPU	-1

#endif	/* __PPC4XX_H__ */
