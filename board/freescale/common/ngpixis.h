/**
 * Copyright 2010 Freescale Semiconductor
 * Author: Timur Tabi <timur@freescale.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This file provides support for the ngPIXIS, a board-specific FPGA used on
 * some Freescale reference boards.
 */

/* ngPIXIS register set. Hopefully, this won't change too much over time.
 * Feel free to add board-specific #ifdefs where necessary.
 */
typedef struct ngpixis {
	u8 id;
	u8 arch;
	u8 scver;
	u8 csr;
	u8 rst;
	u8 res1;
	u8 aux;
	u8 spd;
	u8 brdcfg0;
	u8 dma;
	u8 addr;
	u8 res2[2];
	u8 data;
	u8 led;
	u8 res3;
	u8 vctl;
	u8 vstat;
	u8 vcfgen0;
	u8 res4;
	u8 ocmcsr;
	u8 ocmmsg;
	u8 gmdbg;
	u8 res5[2];
	u8 sclk[3];
	u8 dclk[3];
	u8 watch;
	struct {
		u8 sw;
		u8 en;
	} s[8];
} ngpixis_t  __attribute__ ((aligned(1)));

/* Pointer to the PIXIS register set */
#define pixis ((ngpixis_t *)PIXIS_BASE)

/* The PIXIS SW register that corresponds to board switch X, where x >= 1 */
#define PIXIS_SW(x)		(pixis->s[(x) - 1].sw)

/* The PIXIS EN register that corresponds to board switch X, where x >= 1 */
#define PIXIS_EN(x)		(pixis->s[(x) - 1].en)
