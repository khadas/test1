/*
 * Copyright (c) 2005 Cisco Systems.  All rights reserved.
 * Roland Dreier <rolandd@cisco.com>
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#include <ppc4xx.h>
#ifndef __4XX_PCIE_H
#define __4XX_PCIE_H

#define DCRN_SDR0_CFGADDR	0x00e
#define DCRN_SDR0_CFGDATA	0x00f

#if defined(CONFIG_440SPE)
#define DCRN_PCIE0_BASE		0x100
#define DCRN_PCIE1_BASE		0x120
#define DCRN_PCIE2_BASE		0x140
#endif

#if defined(CONFIG_405EX)
#define	DCRN_PCIE0_BASE		0x040
#define	DCRN_PCIE1_BASE		0x060
#endif

#define PCIE0			DCRN_PCIE0_BASE
#define PCIE1			DCRN_PCIE1_BASE
#define PCIE2			DCRN_PCIE2_BASE

#define DCRN_PEGPL_CFGBAH(base)		(base + 0x00)
#define DCRN_PEGPL_CFGBAL(base)		(base + 0x01)
#define DCRN_PEGPL_CFGMSK(base)		(base + 0x02)
#define DCRN_PEGPL_MSGBAH(base)		(base + 0x03)
#define DCRN_PEGPL_MSGBAL(base)		(base + 0x04)
#define DCRN_PEGPL_MSGMSK(base)		(base + 0x05)
#define DCRN_PEGPL_OMR1BAH(base)	(base + 0x06)
#define DCRN_PEGPL_OMR1BAL(base)	(base + 0x07)
#define DCRN_PEGPL_OMR1MSKH(base)	(base + 0x08)
#define DCRN_PEGPL_OMR1MSKL(base)	(base + 0x09)
#define DCRN_PEGPL_REGBAH(base)		(base + 0x12)
#define DCRN_PEGPL_REGBAL(base)		(base + 0x13)
#define DCRN_PEGPL_REGMSK(base)		(base + 0x14)
#define DCRN_PEGPL_SPECIAL(base)	(base + 0x15)
#define DCRN_PEGPL_CFG(base)		(base + 0x16)

/*
 * System DCRs (SDRs)
 */
#define PESDR0_PLLLCT1		0x03a0
#define PESDR0_PLLLCT2		0x03a1
#define PESDR0_PLLLCT3		0x03a2

#if defined(CONFIG_440SPE)
#define PCIE0_SDR		0x300
#define PCIE1_SDR		0x340
#define PCIE2_SDR		0x370
#endif

#if defined(CONFIG_405EX)
#define PCIE0_SDR		0x400
#define PCIE1_SDR		0x440
#endif

/* common regs, at least for 405EX and 440SPe */
#define SDRN_PESDR_UTLSET1(n)		(sdr_base(n) + 0x00)
#define SDRN_PESDR_UTLSET2(n)		(sdr_base(n) + 0x01)
#define SDRN_PESDR_DLPSET(n)		(sdr_base(n) + 0x02)
#define SDRN_PESDR_LOOP(n)		(sdr_base(n) + 0x03)
#define SDRN_PESDR_RCSSET(n)		(sdr_base(n) + 0x04)
#define SDRN_PESDR_RCSSTS(n)		(sdr_base(n) + 0x05)

#if defined(CONFIG_440SPE)
#define SDRN_PESDR_HSSL0SET1(n)		(sdr_base(n) + 0x06)
#define SDRN_PESDR_HSSL0SET2(n)		(sdr_base(n) + 0x07)
#define SDRN_PESDR_HSSL0STS(n)		(sdr_base(n) + 0x08)
#define SDRN_PESDR_HSSL1SET1(n)		(sdr_base(n) + 0x09)
#define SDRN_PESDR_HSSL1SET2(n)		(sdr_base(n) + 0x0a)
#define SDRN_PESDR_HSSL1STS(n)		(sdr_base(n) + 0x0b)
#define SDRN_PESDR_HSSL2SET1(n)		(sdr_base(n) + 0x0c)
#define SDRN_PESDR_HSSL2SET2(n)		(sdr_base(n) + 0x0d)
#define SDRN_PESDR_HSSL2STS(n)		(sdr_base(n) + 0x0e)
#define SDRN_PESDR_HSSL3SET1(n)		(sdr_base(n) + 0x0f)
#define SDRN_PESDR_HSSL3SET2(n)		(sdr_base(n) + 0x10)
#define SDRN_PESDR_HSSL3STS(n)		(sdr_base(n) + 0x11)

#define PESDR0_UTLSET1		0x0300
#define PESDR0_UTLSET2		0x0301
#define PESDR0_DLPSET		0x0302
#define PESDR0_LOOP		0x0303
#define PESDR0_RCSSET		0x0304
#define PESDR0_RCSSTS		0x0305
#define PESDR0_HSSL0SET1	0x0306
#define PESDR0_HSSL0SET2	0x0307
#define PESDR0_HSSL0STS		0x0308
#define PESDR0_HSSL1SET1	0x0309
#define PESDR0_HSSL1SET2	0x030a
#define PESDR0_HSSL1STS		0x030b
#define PESDR0_HSSL2SET1	0x030c
#define PESDR0_HSSL2SET2	0x030d
#define PESDR0_HSSL2STS		0x030e
#define PESDR0_HSSL3SET1	0x030f
#define PESDR0_HSSL3SET2	0x0310
#define PESDR0_HSSL3STS		0x0311
#define PESDR0_HSSL4SET1	0x0312
#define PESDR0_HSSL4SET2	0x0313
#define PESDR0_HSSL4STS		0x0314
#define PESDR0_HSSL5SET1	0x0315
#define PESDR0_HSSL5SET2	0x0316
#define PESDR0_HSSL5STS		0x0317
#define PESDR0_HSSL6SET1	0x0318
#define PESDR0_HSSL6SET2	0x0319
#define PESDR0_HSSL6STS		0x031a
#define PESDR0_HSSL7SET1	0x031b
#define PESDR0_HSSL7SET2	0x031c
#define PESDR0_HSSL7STS		0x031d
#define PESDR0_HSSCTLSET	0x031e
#define PESDR0_LANE_ABCD	0x031f
#define PESDR0_LANE_EFGH	0x0320

#define PESDR1_UTLSET1		0x0340
#define PESDR1_UTLSET2		0x0341
#define PESDR1_DLPSET		0x0342
#define PESDR1_LOOP		0x0343
#define PESDR1_RCSSET		0x0344
#define PESDR1_RCSSTS		0x0345
#define PESDR1_HSSL0SET1	0x0346
#define PESDR1_HSSL0SET2	0x0347
#define PESDR1_HSSL0STS		0x0348
#define PESDR1_HSSL1SET1	0x0349
#define PESDR1_HSSL1SET2	0x034a
#define PESDR1_HSSL1STS		0x034b
#define PESDR1_HSSL2SET1	0x034c
#define PESDR1_HSSL2SET2	0x034d
#define PESDR1_HSSL2STS		0x034e
#define PESDR1_HSSL3SET1	0x034f
#define PESDR1_HSSL3SET2	0x0350
#define PESDR1_HSSL3STS		0x0351
#define PESDR1_HSSCTLSET	0x0352
#define PESDR1_LANE_ABCD	0x0353

#define PESDR2_UTLSET1		0x0370
#define PESDR2_UTLSET2		0x0371
#define PESDR2_DLPSET		0x0372
#define PESDR2_LOOP		0x0373
#define PESDR2_RCSSET		0x0374
#define PESDR2_RCSSTS		0x0375
#define PESDR2_HSSL0SET1	0x0376
#define PESDR2_HSSL0SET2	0x0377
#define PESDR2_HSSL0STS		0x0378
#define PESDR2_HSSL1SET1	0x0379
#define PESDR2_HSSL1SET2	0x037a
#define PESDR2_HSSL1STS		0x037b
#define PESDR2_HSSL2SET1	0x037c
#define PESDR2_HSSL2SET2	0x037d
#define PESDR2_HSSL2STS		0x037e
#define PESDR2_HSSL3SET1	0x037f
#define PESDR2_HSSL3SET2	0x0380
#define PESDR2_HSSL3STS		0x0381
#define PESDR2_HSSCTLSET	0x0382
#define PESDR2_LANE_ABCD	0x0383

#elif defined(CONFIG_405EX)

#define SDRN_PESDR_PHYSET1(n)		(sdr_base(n) + 0x06)
#define SDRN_PESDR_PHYSET2(n)		(sdr_base(n) + 0x07)
#define SDRN_PESDR_BIST(n)		(sdr_base(n) + 0x08)
#define SDRN_PESDR_LPB(n)		(sdr_base(n) + 0x0b)
#define SDRN_PESDR_PHYSTA(n)		(sdr_base(n) + 0x0c)

#define PESDR0_UTLSET1		0x0400
#define PESDR0_UTLSET2		0x0401
#define PESDR0_DLPSET		0x0402
#define PESDR0_LOOP		0x0403
#define PESDR0_RCSSET		0x0404
#define PESDR0_RCSSTS		0x0405
#define PESDR0_PHYSET1		0x0406
#define PESDR0_PHYSET2		0x0407
#define PESDR0_BIST		0x0408
#define PESDR0_LPB		0x040B
#define PESDR0_PHYSTA		0x040C

#define PESDR1_UTLSET1		0x0440
#define PESDR1_UTLSET2		0x0441
#define PESDR1_DLPSET		0x0442
#define PESDR1_LOOP		0x0443
#define PESDR1_RCSSET		0x0444
#define PESDR1_RCSSTS		0x0445
#define PESDR1_PHYSET1		0x0446
#define PESDR1_PHYSET2		0x0447
#define PESDR1_BIST		0x0448
#define PESDR1_LPB		0x044B
#define PESDR1_PHYSTA		0x044C

#endif

/*
 * UTL register offsets
 */
#define PEUTL_PBBSZ		0x20
#define PEUTL_OPDBSZ		0x68
#define PEUTL_IPHBSZ		0x70
#define PEUTL_IPDBSZ		0x78
#define PEUTL_OUTTR		0x90
#define PEUTL_INTR		0x98
#define PEUTL_PCTL		0xa0
#define PEUTL_RCIRQEN		0xb8

/*
 * Config space register offsets
 */
#define PECFG_BAR0LMPA		0x210
#define PECFG_BAR0HMPA		0x214
#define PECFG_BAR1MPA		0x218
#define PECFG_BAR2MPA		0x220

#define PECFG_PIMEN		0x33c
#define PECFG_PIM0LAL		0x340
#define PECFG_PIM0LAH		0x344
#define PECFG_PIM1LAL		0x348
#define PECFG_PIM1LAH		0x34c
#define PECFG_PIM01SAL		0x350
#define PECFG_PIM01SAH		0x354

#define PECFG_POM0LAL		0x380
#define PECFG_POM0LAH		0x384

#define SDR_READ(offset) ({\
	mtdcr(DCRN_SDR0_CFGADDR, offset); \
	mfdcr(DCRN_SDR0_CFGDATA);})

#define SDR_WRITE(offset, data) ({\
	mtdcr(DCRN_SDR0_CFGADDR, offset); \
	mtdcr(DCRN_SDR0_CFGDATA,data);})

#define GPL_DMER_MASK_DISA	0x02000000

int ppc4xx_init_pcie(void);
int ppc4xx_init_pcie_rootport(int port);
int ppc4xx_init_pcie_endport(int port);
void ppc4xx_setup_pcie_rootpoint(struct pci_controller *hose, int port);
int ppc4xx_setup_pcie_endpoint(struct pci_controller *hose, int port);
int pcie_hose_scan(struct pci_controller *hose, int bus);

static inline void mdelay(int n)
{
	u32 ms = n;

	while (ms--)
		udelay(1000);
}

static inline u32 sdr_base(int port)
{
	switch (port) {
	default:	/* to satisfy compiler */
	case 0:
		return PCIE0_SDR;
	case 1:
		return PCIE1_SDR;
#if defined(PCIE2_SDR)
	case 2:
		return PCIE2_SDR;
#endif
	}
}

#endif /* __4XX_PCIE_H */
