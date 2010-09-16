/*
 * Copyright 2010 Freescale Semiconductor, Inc.
 * Authors: Timur Tabi <timur@freescale.com>
 *
 * FSL DIU Framebuffer driver
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <common.h>
#include <command.h>
#include <asm/io.h>
#include <stdio_dev.h>
#include <video_fb.h>
#include "../common/ngpixis.h"
#include <fsl_diu_fb.h>

/* The CTL register is called 'csr' in the ngpixis_t structure */
#define PX_CTL_ALTACC		0x80

#define PX_BRDCFG0_ELBC_SPI_MASK	0xc0
#define PX_BRDCFG0_ELBC_SPI_ELBC	0x00
#define PX_BRDCFG0_ELBC_SPI_NULL	0xc0
#define PX_BRDCFG0_ELBC_DIU		0x02

#define PX_BRDCFG1_DVIEN	0x80
#define PX_BRDCFG1_DFPEN	0x40
#define PX_BRDCFG1_BACKLIGHT	0x20

#define PMUXCR_ELBCDIU_MASK	0xc0000000
#define PMUXCR_ELBCDIU_NOR16	0x80000000

/*
 * DIU Area Descriptor
 *
 * Note that we need to byte-swap the value before it's written to the AD
 * register.  So even though the registers don't look like they're in the same
 * bit positions as they are on the MPC8610, the same value is written to the
 * AD register on the MPC8610 and on the P1022.
 */
#define AD_BYTE_F		0x10000000
#define AD_ALPHA_C_SHIFT	25
#define AD_BLUE_C_SHIFT		23
#define AD_GREEN_C_SHIFT	21
#define AD_RED_C_SHIFT		19
#define AD_PIXEL_S_SHIFT	16
#define AD_COMP_3_SHIFT		12
#define AD_COMP_2_SHIFT		8
#define AD_COMP_1_SHIFT		4
#define AD_COMP_0_SHIFT		0

/*
 * Variables used by the DIU/LBC switching code.  It's safe to makes these
 * global, because the DIU requires DDR, so we'll only run this code after
 * relocation.
 */
static u8 px_brdcfg0;
static u32 pmuxcr;
static void *lbc_lcs0_ba;
static void *lbc_lcs1_ba;

void diu_set_pixel_clock(unsigned int pixclock)
{
	ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
	unsigned long speed_ccb, temp;
	u32 pixval;

	speed_ccb = get_bus_freq(0);
	temp = 1000000000 / pixclock;
	temp *= 1000;
	pixval = speed_ccb / temp;
	debug("DIU pixval = %lu\n", pixval);

	/* Modify PXCLK in GUTS CLKDVDR */
	temp = in_be32(&gur->clkdvdr) & 0x2000FFFF;
	out_be32(&gur->clkdvdr, temp);			/* turn off clock */
	out_be32(&gur->clkdvdr, temp | 0x80000000 | ((pixval & 0x1F) << 16));
}

int platform_diu_init(unsigned int *xres, unsigned int *yres)
{
	ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
	char *monitor_port;
	u32 pixel_format;
	u8 temp;

	/* Save the LBC LCS0 and LCS1 addresses for the DIU mux functions */
	lbc_lcs0_ba = (void *)(get_lbc_br(0) & get_lbc_or(0) & 0xFFFF8000);
	lbc_lcs1_ba = (void *)(get_lbc_br(1) & get_lbc_or(1) & 0xFFFF8000);

	pixel_format = cpu_to_le32(AD_BYTE_F | (3 << AD_ALPHA_C_SHIFT) |
		(0 << AD_BLUE_C_SHIFT) | (1 << AD_GREEN_C_SHIFT) |
		(2 << AD_RED_C_SHIFT) | (8 << AD_COMP_3_SHIFT) |
		(8 << AD_COMP_2_SHIFT) | (8 << AD_COMP_1_SHIFT) |
		(8 << AD_COMP_0_SHIFT) | (3 << AD_PIXEL_S_SHIFT));

	temp = in_8(&pixis->brdcfg1);

	monitor_port = getenv("monitor");
	if (!strncmp(monitor_port, "1", 1)) { /* 1 - Single link LVDS */
		*xres = 1024;
		*yres = 768;
		/* Enable the DFP port, disable the DVI and the backlight */
		temp &= ~(PX_BRDCFG1_DVIEN | PX_BRDCFG1_BACKLIGHT);
		temp |= PX_BRDCFG1_DFPEN;
	} else {	/* DVI */
		*xres = 1280;
		*yres = 1024;
		/* Enable the DVI port, disable the DFP and the backlight */
		temp &= ~(PX_BRDCFG1_DFPEN | PX_BRDCFG1_BACKLIGHT);
		temp |= PX_BRDCFG1_DVIEN;
	}

	out_8(&pixis->brdcfg1, temp);

	/*
	 * Enable PIXIS indirect access mode.  This is a hack that allows us to
	 * access PIXIS registers even when the LBC pins have been muxed to the
	 * DIU.
	 */
	setbits_8(&pixis->csr, PX_CTL_ALTACC);

	/*
	 * Route the LAD pins to the DIU.  This will disable access to the eLBC,
	 * which means we won't be able to read/write any NOR flash addresses!
	 */
	out_8(lbc_lcs0_ba, offsetof(ngpixis_t, brdcfg0));
	px_brdcfg0 = in_8(lbc_lcs1_ba);
	out_8(lbc_lcs1_ba, px_brdcfg0 | PX_BRDCFG0_ELBC_DIU);

	/* Setting PMUXCR to switch to DVI from ELBC */
	clrsetbits_be32(&gur->pmuxcr,
		PMUXCR_ELBCDIU_MASK, PMUXCR_ELBCDIU_NOR16);
	pmuxcr = in_be32(&gur->pmuxcr);

	return fsl_diu_init(*xres, pixel_format, 0);
}

#ifdef CONFIG_CFI_FLASH_USE_WEAK_ACCESSORS

/*
 * set_mux_to_lbc - disable the DIU so that we can read/write to elbc
 *
 * On the Freescale P1022, the DIU video signal and the LBC address/data lines
 * share the same pins, which means that when the DIU is active (e.g. the
 * console is on the DVI display), NOR flash cannot be accessed.  So we use the
 * weak accessor feature of the CFI flash code to temporarily switch the pin
 * mux from DIU to LBC whenever we want to read or write flash.  This has a
 * significant performance penalty, but it's the only way to make it work.
 *
 * There are two muxes: one on the chip, and one on the board. The chip mux
 * controls whether the pins are used for the DIU or the LBC, and it is
 * set via PMUXCR.  The board mux controls whether those signals go to
 * the video connector or the NOR flash chips, and it is set via the ngPIXIS.
 */
static int set_mux_to_lbc(void)
{
	ccsr_gur_t *gur = (void *)CONFIG_SYS_MPC85xx_GUTS_ADDR;

	/* Switch the muxes only if they're currently set to DIU mode */
	if ((in_be32(&gur->pmuxcr) & PMUXCR_ELBCDIU_MASK) ==
	    PMUXCR_ELBCDIU_NOR16) {
		/*
		 * In DIU mode, the PIXIS can only be accessed indirectly
		 * since we can't read/write the LBC directly.
		 */

		/* Set the board mux to LBC.  This will disable the display. */
		out_8(lbc_lcs0_ba, offsetof(ngpixis_t, brdcfg0));
		px_brdcfg0 = in_8(lbc_lcs1_ba);
		out_8(lbc_lcs1_ba, (px_brdcfg0 & ~(PX_BRDCFG0_ELBC_SPI_MASK
			| PX_BRDCFG0_ELBC_DIU)) | PX_BRDCFG0_ELBC_SPI_ELBC);

		/* Disable indirect PIXIS mode */
		out_8(lbc_lcs0_ba, offsetof(ngpixis_t, csr));
		clrbits_8(lbc_lcs1_ba, PX_CTL_ALTACC);

		/* Set the chip mux to LBC mode, so that writes go to flash. */
		out_be32(&gur->pmuxcr, (pmuxcr & ~PMUXCR_ELBCDIU_MASK) |
			 PMUXCR_ELBCDIU_NOR16);
		in_be32(&gur->pmuxcr);

		return 1;
	}

	return 0;
}

/*
 * set_mux_to_diu - re-enable the DIU muxing
 *
 * This function restores the chip and board muxing to point to the DIU.
 */
static void set_mux_to_diu(void)
{
	ccsr_gur_t *gur = (void *)CONFIG_SYS_MPC85xx_GUTS_ADDR;

	/* Enable indirect PIXIS mode */
	setbits_8(&pixis->csr, PX_CTL_ALTACC);

	/* Set the board mux to DIU.  This will enable the display. */
	out_8(lbc_lcs0_ba, offsetof(ngpixis_t, brdcfg0));
	out_8(lbc_lcs1_ba, px_brdcfg0);
	in_8(lbc_lcs1_ba);

	/* Set the chip mux to DIU mode. */
	out_be32(&gur->pmuxcr, pmuxcr);
	in_be32(&gur->pmuxcr);
}

void flash_write8(u8 value, void *addr)
{
	int sw = set_mux_to_lbc();

	__raw_writeb(value, addr);
	if (sw)
		set_mux_to_diu();
}

void flash_write16(u16 value, void *addr)
{
	int sw = set_mux_to_lbc();

	__raw_writew(value, addr);
	if (sw)
		set_mux_to_diu();
}

void flash_write32(u32 value, void *addr)
{
	int sw = set_mux_to_lbc();

	__raw_writel(value, addr);
	if (sw)
		set_mux_to_diu();
}

void flash_write64(u64 value, void *addr)
{
	int sw = set_mux_to_lbc();

	/* There is no __raw_writeq(), so do the write manually */
	*(volatile u64 *)addr = value;
	if (sw)
		set_mux_to_diu();
}

u8 flash_read8(void *addr)
{
	u8 ret;

	int sw = set_mux_to_lbc();

	ret = __raw_readb(addr);
	if (sw)
		set_mux_to_diu();

	return ret;
}

u16 flash_read16(void *addr)
{
	u16 ret;

	int sw = set_mux_to_lbc();

	ret = __raw_readw(addr);
	if (sw)
		set_mux_to_diu();

	return ret;
}

u32 flash_read32(void *addr)
{
	u32 ret;

	int sw = set_mux_to_lbc();

	ret = __raw_readl(addr);
	if (sw)
		set_mux_to_diu();

	return ret;
}

u64 flash_read64(void *addr)
{
	u64 ret;

	int sw = set_mux_to_lbc();

	/* There is no __raw_readq(), so do the read manually */
	ret = *(volatile u64 *)addr;
	if (sw)
		set_mux_to_diu();

	return ret;
}

#endif
