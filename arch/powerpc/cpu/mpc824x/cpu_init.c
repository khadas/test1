/*
 * (C) Copyright 2000
 * Rob Taylor. Flying Pig Systems. robt@flyingpig.com.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/processor.h>
#include <mpc824x.h>

#ifndef CONFIG_SYS_BANK0_ROW
#define CONFIG_SYS_BANK0_ROW 0
#endif
#ifndef CONFIG_SYS_BANK1_ROW
#define CONFIG_SYS_BANK1_ROW 0
#endif
#ifndef CONFIG_SYS_BANK2_ROW
#define CONFIG_SYS_BANK2_ROW 0
#endif
#ifndef CONFIG_SYS_BANK3_ROW
#define CONFIG_SYS_BANK3_ROW 0
#endif
#ifndef CONFIG_SYS_BANK4_ROW
#define CONFIG_SYS_BANK4_ROW 0
#endif
#ifndef CONFIG_SYS_BANK5_ROW
#define CONFIG_SYS_BANK5_ROW 0
#endif
#ifndef CONFIG_SYS_BANK6_ROW
#define CONFIG_SYS_BANK6_ROW 0
#endif
#ifndef CONFIG_SYS_BANK7_ROW
#define CONFIG_SYS_BANK7_ROW 0
#endif
#ifndef CONFIG_SYS_DBUS_SIZE2
#define CONFIG_SYS_DBUS_SIZE2 0
#endif

/*
 * Breath some life into the CPU...
 *
 * Set up the memory map,
 * initialize a bunch of registers,
 */
void
cpu_init_f (void)
{
    register unsigned long val;
    CONFIG_WRITE_HALFWORD(PCICR, 0x06); /* Bus Master, respond to PCI memory space acesses*/
/*    CONFIG_WRITE_HALFWORD(PCISR, 0xffff); */ /*reset PCISR*/

#if defined(CONFIG_MUSENKI)
/* Why is this here, you ask?  Try, just try setting 0x8000
 * in PCIACR with CONFIG_WRITE_HALFWORD()
 * this one was a stumper, and we are annoyed
 */

#define M_CONFIG_WRITE_HALFWORD( addr, data ) \
	__asm__ __volatile__("		\
		stw  %2,0(%0)\n		\
		sync\n			\
		sth  %3,2(%1)\n		\
		sync\n			\
		"			\
		: /* no output */	\
		: "r" (CONFIG_ADDR), "r" (CONFIG_DATA),			\
		"r" (PCISWAP(addr & ~3)), "r" (PCISWAP(data << 16))	\
	);

	M_CONFIG_WRITE_HALFWORD(PCIACR, 0x8000);
#endif

	CONFIG_WRITE_BYTE(PCLSR, 0x8);	/* set PCI cache line size */
	CONFIG_WRITE_BYTE (PLTR, 0x40); /* set PCI latency timer */
	/*
	* Note that although this bit is cleared after a hard reset, it
	* must be explicitly set and then cleared by software during
	* initialization in order to guarantee correct operation of the
	* DLL and the SDRAM_CLK[0:3] signals (if they are used).
	*/
	CONFIG_READ_BYTE (AMBOR, val);
	CONFIG_WRITE_BYTE(AMBOR, val & 0xDF);
	CONFIG_WRITE_BYTE(AMBOR, val | 0x20);
	CONFIG_WRITE_BYTE(AMBOR, val & 0xDF);
#ifdef CONFIG_MPC8245
	/* silicon bug 28 MPC8245 */
	CONFIG_READ_BYTE(AMBOR,val);
	CONFIG_WRITE_BYTE(AMBOR,val|0x1);

#if 0
	/*
	 * The following bug only affects older (XPC8245) processors.
	 * DMA transfers initiated by external devices get corrupted due
	 * to a hardware scheduling problem.
	 *
	 * The effect is:
	 * when transferring X words, the first 32 words are transferred
	 * OK, the next 3 x 32 words are 'old' data (from previous DMA)
	 * while the rest of the X words is xferred fine.
	 *
	 * Disabling 3 of the 4 32 word hardware buffers solves the problem
	 * with no significant performance loss.
	 */

	CONFIG_READ_BYTE(PCMBCR,val);
	/* in order not to corrupt data which is being read over the PCI bus
	* with the PPC as slave, we need to reduce the number of PCMRBs to 1,
	* 4.11 in the  processor user manual
	* */

#if 1
	CONFIG_WRITE_BYTE(PCMBCR,(val|0xC0)); /* 1 PCMRB */
#else
	CONFIG_WRITE_BYTE(PCMBCR,(val|0x80)); /* 2 PCMRBs */
	CONFIG_WRITE_BYTE(PCMBCR,(val|0x40)); /* 3 PCMRBs */
	/* default, 4 PCMRBs are used */
#endif
#endif
#endif

	CONFIG_READ_WORD(PICR1, val);
#if defined(CONFIG_MPC8240)
	CONFIG_WRITE_WORD( PICR1,
		(val & (PICR1_ADDRESS_MAP | PICR1_RCS0)) |
		       PIRC1_MSK | PICR1_PROC_TYPE_603E |
		       PICR1_FLASH_WR_EN | PICR1_MCP_EN |
		       PICR1_CF_DPARK | PICR1_EN_PCS |
		       PICR1_CF_APARK );
#elif defined(CONFIG_MPC8245)
	CONFIG_WRITE_WORD( PICR1,
		(val & (PICR1_RCS0)) |
		       PICR1_PROC_TYPE_603E |
		       PICR1_FLASH_WR_EN | PICR1_MCP_EN |
		       PICR1_CF_DPARK | PICR1_NO_BUSW_CK |
		       PICR1_DEC| PICR1_CF_APARK | 0x10); /* 8245 UM says bit 4 must be set */
#else
#error Specific type of MPC824x must be defined (i.e. CONFIG_MPC8240)
#endif

	CONFIG_READ_WORD(PICR2, val);
	val= val & ~ (PICR2_CF_SNOOP_WS_MASK | PICR2_CF_APHASE_WS_MASK); /*mask off waitstate bits*/
	val |= PICR2_CF_SNOOP_WS_1WS | PICR2_CF_APHASE_WS_1WS; /*1 wait state*/
	CONFIG_WRITE_WORD(PICR2, val);

	CONFIG_WRITE_WORD(EUMBBAR, CONFIG_SYS_EUMB_ADDR);
#ifndef CONFIG_SYS_RAMBOOT
	CONFIG_WRITE_WORD(MCCR1, (CONFIG_SYS_ROMNAL << MCCR1_ROMNAL_SHIFT) |
				 (CONFIG_SYS_BANK0_ROW) |
				 (CONFIG_SYS_BANK1_ROW << MCCR1_BANK1ROW_SHIFT) |
				 (CONFIG_SYS_BANK2_ROW << MCCR1_BANK2ROW_SHIFT) |
				 (CONFIG_SYS_BANK3_ROW << MCCR1_BANK3ROW_SHIFT) |
				 (CONFIG_SYS_BANK4_ROW << MCCR1_BANK4ROW_SHIFT) |
				 (CONFIG_SYS_BANK5_ROW << MCCR1_BANK5ROW_SHIFT) |
				 (CONFIG_SYS_BANK6_ROW << MCCR1_BANK6ROW_SHIFT) |
				 (CONFIG_SYS_BANK7_ROW << MCCR1_BANK7ROW_SHIFT) |
				 (CONFIG_SYS_ROMFAL << MCCR1_ROMFAL_SHIFT));
#endif

#if defined(CONFIG_SYS_ASRISE) && defined(CONFIG_SYS_ASFALL)
	CONFIG_WRITE_WORD(MCCR2, CONFIG_SYS_REFINT << MCCR2_REFINT_SHIFT |
				 CONFIG_SYS_ASRISE << MCCR2_ASRISE_SHIFT |
				 CONFIG_SYS_ASFALL << MCCR2_ASFALL_SHIFT);
#else
	CONFIG_WRITE_WORD(MCCR2, CONFIG_SYS_REFINT << MCCR2_REFINT_SHIFT);
#endif

#if defined(CONFIG_MPC8240)
	CONFIG_WRITE_WORD(MCCR3,
		(((CONFIG_SYS_BSTOPRE & 0x003c) >> 2) << MCCR3_BSTOPRE2TO5_SHIFT) |
		(CONFIG_SYS_REFREC << MCCR3_REFREC_SHIFT) |
		(CONFIG_SYS_RDLAT  << MCCR3_RDLAT_SHIFT));
#elif defined(CONFIG_MPC8245)
	CONFIG_WRITE_WORD(MCCR3,
		(((CONFIG_SYS_BSTOPRE & 0x003c) >> 2) << MCCR3_BSTOPRE2TO5_SHIFT) |
		(CONFIG_SYS_REFREC << MCCR3_REFREC_SHIFT));
#else
#error Specific type of MPC824x must be defined (i.e. CONFIG_MPC8240)
#endif

/* this is gross.  We think these should all be the same, and various boards
 *  should define CONFIG_SYS_ACTORW to 0 if they don't want to set it, or even, if
 *  its not set, we define it to zero in this file
 */
#if defined(CONFIG_CU824)
	CONFIG_WRITE_WORD(MCCR4,
	(CONFIG_SYS_PRETOACT << MCCR4_PRETOACT_SHIFT) |
	(CONFIG_SYS_ACTTOPRE << MCCR4_ACTTOPRE_SHIFT) |
	MCCR4_BIT21 |
	(CONFIG_SYS_REGISTERD_TYPE_BUFFER ? MCCR4_REGISTERED: 0) |
	((CONFIG_SYS_BSTOPRE & 0x0003) <<MCCR4_BSTOPRE0TO1_SHIFT ) |
	(((CONFIG_SYS_SDMODE_CAS_LAT <<4) | (CONFIG_SYS_SDMODE_WRAP <<3) |
		  CONFIG_SYS_SDMODE_BURSTLEN) << MCCR4_SDMODE_SHIFT) |
	(CONFIG_SYS_ACTORW << MCCR4_ACTTORW_SHIFT) |
	(((CONFIG_SYS_BSTOPRE & 0x03c0) >> 6) << MCCR4_BSTOPRE6TO9_SHIFT));
#elif defined(CONFIG_MPC8240)
	CONFIG_WRITE_WORD(MCCR4,
	(CONFIG_SYS_PRETOACT << MCCR4_PRETOACT_SHIFT) |
	(CONFIG_SYS_ACTTOPRE << MCCR4_ACTTOPRE_SHIFT) |
	MCCR4_BIT21 |
	(CONFIG_SYS_REGISTERD_TYPE_BUFFER ? MCCR4_REGISTERED: 0) |
	((CONFIG_SYS_BSTOPRE & 0x0003) <<MCCR4_BSTOPRE0TO1_SHIFT ) |
	(((CONFIG_SYS_SDMODE_CAS_LAT <<4) | (CONFIG_SYS_SDMODE_WRAP <<3) |
		  (CONFIG_SYS_SDMODE_BURSTLEN)) <<MCCR4_SDMODE_SHIFT) |
	(((CONFIG_SYS_BSTOPRE & 0x03c0) >> 6) <<MCCR4_BSTOPRE6TO9_SHIFT ));
#elif defined(CONFIG_MPC8245)
	CONFIG_READ_WORD(MCCR1, val);
	val &= MCCR1_DBUS_SIZE0;    /* test for 64-bit mem bus */

	CONFIG_WRITE_WORD(MCCR4,
		(CONFIG_SYS_PRETOACT << MCCR4_PRETOACT_SHIFT) |
		(CONFIG_SYS_ACTTOPRE << MCCR4_ACTTOPRE_SHIFT) |
		(CONFIG_SYS_EXTROM ? MCCR4_EXTROM : 0) |
		(CONFIG_SYS_REGDIMM ? MCCR4_REGDIMM : 0) |
		(CONFIG_SYS_REGISTERD_TYPE_BUFFER ? MCCR4_REGISTERED: 0) |
		((CONFIG_SYS_BSTOPRE & 0x0003) <<MCCR4_BSTOPRE0TO1_SHIFT ) |
		(CONFIG_SYS_DBUS_SIZE2 << MCCR4_DBUS_SIZE2_SHIFT) |
		(((CONFIG_SYS_SDMODE_CAS_LAT <<4) | (CONFIG_SYS_SDMODE_WRAP <<3) |
		      (val ? 2 : 3)) << MCCR4_SDMODE_SHIFT)  |
		(CONFIG_SYS_ACTORW << MCCR4_ACTTORW_SHIFT) |
		(((CONFIG_SYS_BSTOPRE & 0x03c0) >> 6) <<MCCR4_BSTOPRE6TO9_SHIFT ));
#else
#error Specific type of MPC824x must be defined (i.e. CONFIG_MPC8240)
#endif

	CONFIG_WRITE_WORD(MSAR1,
		( (CONFIG_SYS_BANK0_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) |
		(((CONFIG_SYS_BANK1_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK2_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK3_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 24));
	CONFIG_WRITE_WORD(EMSAR1,
		( (CONFIG_SYS_BANK0_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) |
		(((CONFIG_SYS_BANK1_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK2_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK3_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 24));
	CONFIG_WRITE_WORD(MSAR2,
		( (CONFIG_SYS_BANK4_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) |
		(((CONFIG_SYS_BANK5_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK6_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK7_START & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 24));
	CONFIG_WRITE_WORD(EMSAR2,
		( (CONFIG_SYS_BANK4_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) |
		(((CONFIG_SYS_BANK5_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK6_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK7_START & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 24));
	CONFIG_WRITE_WORD(MEAR1,
		( (CONFIG_SYS_BANK0_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) |
		(((CONFIG_SYS_BANK1_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK2_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK3_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 24));
	CONFIG_WRITE_WORD(EMEAR1,
		( (CONFIG_SYS_BANK0_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) |
		(((CONFIG_SYS_BANK1_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK2_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK3_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 24));
	CONFIG_WRITE_WORD(MEAR2,
		( (CONFIG_SYS_BANK4_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) |
		(((CONFIG_SYS_BANK5_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK6_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK7_END & MICR_ADDR_MASK) >> MICR_ADDR_SHIFT) << 24));
	CONFIG_WRITE_WORD(EMEAR2,
		( (CONFIG_SYS_BANK4_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) |
		(((CONFIG_SYS_BANK5_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 8) |
		(((CONFIG_SYS_BANK6_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 16) |
		(((CONFIG_SYS_BANK7_END & MICR_EADDR_MASK) >> MICR_EADDR_SHIFT) << 24));

	CONFIG_WRITE_BYTE(ODCR, CONFIG_SYS_ODCR);
#ifdef CONFIG_SYS_DLL_MAX_DELAY
	CONFIG_WRITE_BYTE(MIOCR1, CONFIG_SYS_DLL_MAX_DELAY);	/* needed to make DLL lock */
#endif
#if defined(CONFIG_SYS_DLL_EXTEND) && defined(CONFIG_SYS_PCI_HOLD_DEL)
	CONFIG_WRITE_BYTE(PMCR2, CONFIG_SYS_DLL_EXTEND | CONFIG_SYS_PCI_HOLD_DEL);
#endif
#if defined(MIOCR2) && defined(CONFIG_SYS_SDRAM_DSCD)
	CONFIG_WRITE_BYTE(MIOCR2, CONFIG_SYS_SDRAM_DSCD);	/* change memory input */
#endif /* setup & hold time */

	CONFIG_WRITE_BYTE(MBER,
		 CONFIG_SYS_BANK0_ENABLE |
		(CONFIG_SYS_BANK1_ENABLE << 1) |
		(CONFIG_SYS_BANK2_ENABLE << 2) |
		(CONFIG_SYS_BANK3_ENABLE << 3) |
		(CONFIG_SYS_BANK4_ENABLE << 4) |
		(CONFIG_SYS_BANK5_ENABLE << 5) |
		(CONFIG_SYS_BANK6_ENABLE << 6) |
		(CONFIG_SYS_BANK7_ENABLE << 7));

#ifdef CONFIG_SYS_PGMAX
	CONFIG_WRITE_BYTE(MPMR, CONFIG_SYS_PGMAX);
#endif

	/* ! Wait 200us before initialize other registers */
	/*FIXME: write a decent udelay wait */
	__asm__ __volatile__(
		" mtctr	%0 \n \
		0: bdnz	 0b\n"
		:
		: "r" (0x10000));

	CONFIG_READ_WORD(MCCR1, val);
	CONFIG_WRITE_WORD(MCCR1, val | MCCR1_MEMGO); /* set memory access going */
	__asm__ __volatile__("eieio");
}

/*
 * initialize higher level parts of CPU like time base and timers
 */
int cpu_init_r (void)
{
	return (0);
}
