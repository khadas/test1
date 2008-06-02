/*
 * (C) Copyright 2001-2004
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
#include "ar405.h"
#include <asm/processor.h>
#include <command.h>

DECLARE_GLOBAL_DATA_PTR;

/*cmd_boot.c*/
extern int do_reset (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
extern void lxt971_no_sleep(void);

/* ------------------------------------------------------------------------- */

#if 0
#define FPGA_DEBUG
#endif

/* fpga configuration data - generated by bin2cc */
const unsigned char fpgadata[] = {
#include "fpgadata.c"
};

const unsigned char fpgadata_xl30[] = {
#include "fpgadata_xl30.c"
};

/*
 * include common fpga code (for esd boards)
 */
#include "../common/fpga.c"


int board_early_init_f (void)
{
	int index, len, i;
	int status;

#ifdef FPGA_DEBUG
	/* set up serial port with default baudrate */
	(void) get_clocks ();
	gd->baudrate = CONFIG_BAUDRATE;
	serial_init ();
	console_init_f ();
#endif

	/*
	 * Boot onboard FPGA
	 */
	/* first try 40er image */
	gd->board_type = 40;
	status = fpga_boot ((unsigned char *) fpgadata, sizeof (fpgadata));
	if (status != 0) {
		/* try xl30er image */
		gd->board_type = 30;
		status = fpga_boot ((unsigned char *) fpgadata_xl30, sizeof (fpgadata_xl30));
		if (status != 0) {
			/* booting FPGA failed */
#ifndef FPGA_DEBUG
			/* set up serial port with default baudrate */
			(void) get_clocks ();
			gd->baudrate = CONFIG_BAUDRATE;
			serial_init ();
			console_init_f ();
#endif
			printf ("\nFPGA: Booting failed ");
			switch (status) {
			case ERROR_FPGA_PRG_INIT_LOW:
				printf ("(Timeout: INIT not low after asserting PROGRAM*)\n ");
				break;
			case ERROR_FPGA_PRG_INIT_HIGH:
				printf ("(Timeout: INIT not high after deasserting PROGRAM*)\n ");
				break;
			case ERROR_FPGA_PRG_DONE:
				printf ("(Timeout: DONE not high after programming FPGA)\n ");
				break;
			}

			/* display infos on fpgaimage */
			index = 15;
			for (i = 0; i < 4; i++) {
				len = fpgadata[index];
				printf ("FPGA: %s\n", &(fpgadata[index + 1]));
				index += len + 3;
			}
			putc ('\n');
			/* delayed reboot */
			for (i = 20; i > 0; i--) {
				printf ("Rebooting in %2d seconds \r", i);
				for (index = 0; index < 1000; index++)
					udelay (1000);
			}
			putc ('\n');
			do_reset (NULL, 0, 0, NULL);
		}
	}

	/*
	 * IRQ 0-15  405GP internally generated; active high; level sensitive
	 * IRQ 16    405GP internally generated; active low; level sensitive
	 * IRQ 17-24 RESERVED
	 * IRQ 25 (EXT IRQ 0) CAN0; active low; level sensitive
	 * IRQ 26 (EXT IRQ 1) CAN1; active low; level sensitive
	 * IRQ 27 (EXT IRQ 2) PCI SLOT 0; active low; level sensitive
	 * IRQ 28 (EXT IRQ 3) PCI SLOT 1; active low; level sensitive
	 * IRQ 29 (EXT IRQ 4) PCI SLOT 2; active low; level sensitive
	 * IRQ 30 (EXT IRQ 5) PCI SLOT 3; active low; level sensitive
	 * IRQ 31 (EXT IRQ 6) COMPACT FLASH; active high; level sensitive
	 */
	mtdcr (uicsr, 0xFFFFFFFF);	/* clear all ints */
	mtdcr (uicer, 0x00000000);	/* disable all ints */
	mtdcr (uiccr, 0x00000000);	/* set all to be non-critical */
	mtdcr (uicpr, 0xFFFFFF81);	/* set int polarities */
	mtdcr (uictr, 0x10000000);	/* set int trigger levels */
	mtdcr (uicvcr, 0x00000001);	/* set vect base=0,INT0 highest priority */
	mtdcr (uicsr, 0xFFFFFFFF);	/* clear all ints */

	*(ushort *) 0xf03000ec = 0x0fff;	/* enable all interrupts in fpga */

	return 0;
}


/* ------------------------------------------------------------------------- */

/*
 * Check Board Identity:
 */

int checkboard (void)
{
	int index;
	int len;
	char str[64];
	int i = getenv_r ("serial#", str, sizeof (str));
	const unsigned char *fpga;

	puts ("Board: ");

	if (i == -1) {
		puts ("### No HW ID - assuming AR405");
	} else {
		puts(str);
	}

	puts ("\nFPGA:  ");

	/* display infos on fpgaimage */
	if (gd->board_type == 30) {
		fpga = fpgadata_xl30;
	} else {
		fpga = fpgadata;
	}
	index = 15;
	for (i = 0; i < 4; i++) {
		len = fpga[index];
		printf ("%s ", &(fpga[index + 1]));
		index += len + 3;
	}

	putc ('\n');

	/*
	 * Disable sleep mode in LXT971
	 */
	lxt971_no_sleep();

	return 0;
}


#if 1 /* test-only: some internal test routines... */
/*
 * Some test routines
 */
int do_digtest(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	volatile uchar *digen = (volatile uchar *)0xf03000b4;
	volatile ushort *digout = (volatile ushort *)0xf03000b0;
	volatile ushort *digin = (volatile ushort *)0xf03000a0;
	int i;
	int k;
	int start;
	int end;

	if (argc != 3) {
		puts("Usage: digtest n_start n_end (digtest 0 7)\n");
		return 0;
	}

	start = simple_strtol (argv[1], NULL, 10);
	end = simple_strtol (argv[2], NULL, 10);

	/*
	 * Enable digital outputs
	 */
	*digen = 0x08;

	printf("\nStarting digital In-/Out Test from I/O %d to %d (Cntrl-C to abort)...\n",
	       start, end);

	/*
	 * Set outputs one by one
	 */
	for (;;) {
		for (i=start; i<=end; i++) {
			*digout = 0x0001 << i;
			for (k=0; k<200; k++)
				udelay(1000);

			if (*digin != (0x0001 << i)) {
				printf("ERROR: OUT=0x%04X, IN=0x%04X\n", 0x0001 << i, *digin);
				return 0;
			}

			/* Abort if ctrl-c was pressed */
			if (ctrlc()) {
				puts("\nAbort\n");
				return 0;
			}
		}
	}

	return 0;
}
U_BOOT_CMD(
	digtest,	3,	1,	do_digtest,
	"digtest - Test digital in-/output\n",
	NULL
	);


#define ERROR_DELTA     256

struct io {
	volatile short val;
	short dummy;
};

int do_anatest(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	volatile short val;
	int i;
	int volt;
	struct io *out;
	struct io *in;

	out = (struct io *)0xf0300090;
	in = (struct io *)0xf0300000;

	i = simple_strtol (argv[1], NULL, 10);

	volt = 0;
	printf("Setting Channel %d to %dV...\n", i, volt);
	out[i].val = (volt * 0x7fff) / 10;
	udelay(10000);
	val = in[i*2].val;
	printf("-> InChannel %d: 0x%04x=%dV\n", i*2, val, (val * 4000) / 0x7fff);
	if ((val < ((volt * 0x7fff) / 40) - ERROR_DELTA) ||
	    (val > ((volt * 0x7fff) / 40) + ERROR_DELTA)) {
		printf("ERROR! (min=0x%04x max=0x%04x)\n", ((volt * 0x7fff) / 40) - ERROR_DELTA,
		       ((volt * 0x7fff) / 40) + ERROR_DELTA);
		return -1;
	}
	val = in[i*2+1].val;
	printf("-> InChannel %d: 0x%04x=%dV\n", i*2+1, val, (val * 4000) / 0x7fff);
	if ((val < ((volt * 0x7fff) / 40) - ERROR_DELTA) ||
	    (val > ((volt * 0x7fff) / 40) + ERROR_DELTA)) {
		printf("ERROR! (min=0x%04x max=0x%04x)\n", ((volt * 0x7fff) / 40) - ERROR_DELTA,
		       ((volt * 0x7fff) / 40) + ERROR_DELTA);
		return -1;
	}

	volt = 5;
	printf("Setting Channel %d to %dV...\n", i, volt);
	out[i].val = (volt * 0x7fff) / 10;
	udelay(10000);
	val = in[i*2].val;
	printf("-> InChannel %d: 0x%04x=%dV\n", i*2, val, (val * 4000) / 0x7fff);
	if ((val < ((volt * 0x7fff) / 40) - ERROR_DELTA) ||
	    (val > ((volt * 0x7fff) / 40) + ERROR_DELTA)) {
		printf("ERROR! (min=0x%04x max=0x%04x)\n", ((volt * 0x7fff) / 40) - ERROR_DELTA,
		       ((volt * 0x7fff) / 40) + ERROR_DELTA);
		return -1;
	}
	val = in[i*2+1].val;
	printf("-> InChannel %d: 0x%04x=%dV\n", i*2+1, val, (val * 4000) / 0x7fff);
	if ((val < ((volt * 0x7fff) / 40) - ERROR_DELTA) ||
	    (val > ((volt * 0x7fff) / 40) + ERROR_DELTA)) {
		printf("ERROR! (min=0x%04x max=0x%04x)\n", ((volt * 0x7fff) / 40) - ERROR_DELTA,
		       ((volt * 0x7fff) / 40) + ERROR_DELTA);
		return -1;
	}

	volt = 10;
	printf("Setting Channel %d to %dV...\n", i, volt);
	out[i].val = (volt * 0x7fff) / 10;
	udelay(10000);
	val = in[i*2].val;
	printf("-> InChannel %d: 0x%04x=%dV\n", i*2, val, (val * 4000) / 0x7fff);
	if ((val < ((volt * 0x7fff) / 40) - ERROR_DELTA) ||
	    (val > ((volt * 0x7fff) / 40) + ERROR_DELTA)) {
		printf("ERROR! (min=0x%04x max=0x%04x)\n", ((volt * 0x7fff) / 40) - ERROR_DELTA,
		       ((volt * 0x7fff) / 40) + ERROR_DELTA);
		return -1;
	}
	val = in[i*2+1].val;
	printf("-> InChannel %d: 0x%04x=%dV\n", i*2+1, val, (val * 4000) / 0x7fff);
	if ((val < ((volt * 0x7fff) / 40) - ERROR_DELTA) ||
	    (val > ((volt * 0x7fff) / 40) + ERROR_DELTA)) {
		printf("ERROR! (min=0x%04x max=0x%04x)\n", ((volt * 0x7fff) / 40) - ERROR_DELTA,
		       ((volt * 0x7fff) / 40) + ERROR_DELTA);
		return -1;
	}

	printf("Channel %d OK!\n", i);

	return 0;
}
U_BOOT_CMD(
	anatest,	2,	1,	do_anatest,
	"anatest - Test analog in-/output\n",
	NULL
	);


int counter = 0;

void cyclicInt(void *ptr)
{
	*(ushort *)0xf03000e8 = 0x0800; /* ack int */
	counter++;
}


int do_inctest(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	volatile uchar *digout = (volatile uchar *)0xf03000b4;
	volatile ulong *incin;
	int i;

	incin = (volatile ulong *)0xf0300040;

	/*
	 * Clear inc counter
	 */
	incin[0] = 0;
	incin[1] = 0;
	incin[2] = 0;
	incin[3] = 0;

	incin = (volatile ulong *)0xf0300050;

	/*
	 * Inc a little
	 */
	for (i=0; i<10000; i++) {
		switch (i & 0x03) {
		case 0:
			*digout = 0x02;
			break;
		case 1:
			*digout = 0x03;
			break;
		case 2:
			*digout = 0x01;
			break;
		case 3:
			*digout = 0x00;
			break;
		}
		udelay(10);
	}

	printf("Inc 0 = %ld\n", incin[0]);
	printf("Inc 1 = %ld\n", incin[1]);
	printf("Inc 2 = %ld\n", incin[2]);
	printf("Inc 3 = %ld\n", incin[3]);

	*(ushort *)0xf03000e0 = 0x0c80-1; /* set counter */
	*(ushort *)0xf03000ec |= 0x0800; /* enable int */
	irq_install_handler (30, (interrupt_handler_t *) cyclicInt, NULL);
	printf("counter=%d\n", counter);

	return 0;
}
U_BOOT_CMD(
	inctest,	3,	1,	do_inctest,
	"inctest - Test incremental encoder inputs\n",
	NULL
	);
#endif
