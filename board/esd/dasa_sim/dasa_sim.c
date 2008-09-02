/*
 * (C) Copyright 2001
 * Stefan Roese, esd gmbh germany, stefan.roese@esd-electronics.com
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include "dasa_sim.h"

/* ------------------------------------------------------------------------- */

#undef FPGA_DEBUG

#define	_NOT_USED_	0xFFFFFFFF

/* ------------------------------------------------------------------------- */

/* fpga configuration data - generated by bit2inc */
static unsigned char fpgadata[] = {
#include "fpgadata.c"
};

#define FPGA_PRG_SLEEP         32	/* fpga program sleep-time */
#define LOAD_LONG(a)           a


/******************************************************************************
 *
 * sysFpgaBoot - Load fpga-image into fpga
 *
 */
static int fpgaBoot (void)
{
	int i, j, index, len;
	unsigned char b;
	int imageSize;

	imageSize = sizeof (fpgadata);

	/* display infos on fpgaimage */
	index = 15;
	for (i = 0; i < 4; i++) {
		len = fpgadata[index];
		index += len + 3;
	}

	/* search for preamble 0xFF2X */
	for (index = 0; index < imageSize - 1; index++) {
		if ((fpgadata[index] == 0xff)
			&& ((fpgadata[index + 1] & 0xf0) == 0x20))
			break;
	}

	/* enable cs1 instead of user0... */
	*(unsigned long *) 0x50000084 &= ~0x00000002;

#ifdef FPGA_DEBUG
	printf ("%s\n",
			((in32 (0x50000084) & 0x00010000) == 0) ? "NOT DONE" : "DONE");
#endif

	/* init fpga by asserting and deasserting PROGRAM* (USER2)... */
	*(unsigned long *) 0x50000084 &= ~0x00000400;
	udelay (FPGA_PRG_SLEEP * 1000);

	*(unsigned long *) 0x50000084 |= 0x00000400;
	udelay (FPGA_PRG_SLEEP * 1000);

#ifdef FPGA_DEBUG
	printf ("%s\n",
			((in32 (0x50000084) & 0x00010000) == 0) ? "NOT DONE" : "DONE");
#endif

	/* cs1: disable burst, disable ready */
	*(unsigned long *) 0x50000114 &= ~0x00000300;

	/* cs1: set write timing */
	*(unsigned long *) 0x50000118 |= 0x00010900;

	/* write configuration-data into fpga... */
	for (i = index; i < imageSize; i++) {
		b = fpgadata[i];
		for (j = 0; j < 8; j++) {
			*(unsigned long *) 0x30000000 =
				((b & 0x80) == 0x80)
				? LOAD_LONG (0x03030101)
				: LOAD_LONG (0x02020000);
			b <<= 1;
		}
	}

#ifdef FPGA_DEBUG
	printf ("%s\n",
			((in32 (0x50000084) & 0x00010000) == 0) ? "NOT DONE" : "DONE");
#endif

	/* set cs1 to 32 bit data-width, disable burst, enable ready */
	*(unsigned long *) 0x50000114 |= 0x00000202;
	*(unsigned long *) 0x50000114 &= ~0x00000100;

	/* cs1: set iop access to little endian */
	*(unsigned long *) 0x50000114 &= ~0x00000010;

	/* cs1: set read and write timing */
	*(unsigned long *) 0x50000118 = 0x00010000;
	*(unsigned long *) 0x5000011c = 0x00010001;

#ifdef FPGA_DEBUG
	printf ("%s\n",
			((in32 (0x50000084) & 0x00010000) == 0) ? "NOT DONE" : "DONE");
#endif

	/* wait for 30 ms... */
	udelay (30 * 1000);
	/* check if fpga's DONE signal - correctly booted ? */
	if ((*(unsigned long *) 0x50000084 & 0x00010000) == 0)
		return -1;

	return 0;
}


int board_early_init_f (void)
{
	/*
	 * Init pci regs
	 */
	*(unsigned long *) 0x50000304 = 0x02900007;	/* enable mem/io/master bits */
	*(unsigned long *) 0x500001b4 = 0x00000000;	/* disable pci interrupt output enable */
	*(unsigned long *) 0x50000354 = 0x00c05800;	/* disable emun interrupt output enable */
	*(unsigned long *) 0x50000344 = 0x00000000;	/* disable pme interrupt output enable */
	*(unsigned long *) 0x50000310 = 0x00000000;	/* pcibar0 */
	*(unsigned long *) 0x50000314 = 0x00000000;	/* pcibar1 */
	*(unsigned long *) 0x50000318 = 0x00000000;	/* pcibar2 */

	return 0;
}


/*
 * Check Board Identity:
 */

int checkboard (void)
{
	int index;
	int len;
	char str[64];
	int i = getenv_r ("serial#", str, sizeof (str));
	int fpga;
	unsigned short val;

	puts ("Board: ");

	/*
	 * Boot onboard FPGA
	 */
	fpga = fpgaBoot ();

	if (!i || strncmp (str, "DASA_SIM", 8)) {
		puts ("### No HW ID - assuming DASA_SIM");
	}

	puts (str);

	if (fpga == 0) {
		val = *(unsigned short *) 0x30000202;
		printf (" (Id=%d Version=%d Revision=%d)",
			(val & 0x07f8) >> 3, val & 0x0001, (val & 0x0006) >> 1);

		puts ("\nFPGA:  ");

		/* display infos on fpgaimage */
		index = 15;
		for (i = 0; i < 4; i++) {
			len = fpgadata[index];
			printf ("%s ", &(fpgadata[index + 1]));
			index += len + 3;
		}
	} else {
		puts ("\nFPGA:  Booting failed!");
	}

	putc ('\n');

	return 0;
}
