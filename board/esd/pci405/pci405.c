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
#include <asm/processor.h>
#include <command.h>
#include <malloc.h>
#include <pci.h>
#include <asm/4xx_pci.h>
#include <asm/io.h>

#include "pci405.h"

DECLARE_GLOBAL_DATA_PTR;

/* Prototypes */
int do_reset (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[]);
unsigned long fpga_done_state(void);
unsigned long fpga_init_state(void);

#if 0
#define FPGA_DEBUG
#endif

/* predefine these here */
#define FPGA_DONE_STATE (fpga_done_state())
#define FPGA_INIT_STATE (fpga_init_state())

/* fpga configuration data - generated by bin2cc */
const unsigned char fpgadata[] =
{
#include "fpgadata.c"
};

/*
 * include common fpga code (for esd boards)
 */
#include "../common/fpga.c"

#define FPGA_DONE_STATE_V11 (in_be32((void*)GPIO0_IR) & CONFIG_SYS_FPGA_DONE)
#define FPGA_DONE_STATE_V12 (in_be32((void*)GPIO0_IR) & CONFIG_SYS_FPGA_DONE_V12)

#define FPGA_INIT_STATE_V11 (in_be32((void*)GPIO0_IR) & CONFIG_SYS_FPGA_INIT)
#define FPGA_INIT_STATE_V12 (in_be32((void*)GPIO0_IR) & CONFIG_SYS_FPGA_INIT_V12)


int board_revision(void)
{
	unsigned long CPC0_CR0Reg;
	unsigned long value;

	/*
	 * Get version of PCI405 board from GPIO's
	 */

	/*
	 * Setup GPIO pins (CS2/GPIO11 and CS3/GPIO12 as GPIO)
	 */
	CPC0_CR0Reg = mfdcr(CPC0_CR0);
	mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x03000000);
	out_be32((void*)GPIO0_ODR, in_be32((void*)GPIO0_ODR) & ~0x00100200);
	out_be32((void*)GPIO0_TCR, in_be32((void*)GPIO0_TCR) & ~0x00100200);
	udelay(1000);                   /* wait some time before reading input */
	value = in_be32((void*)GPIO0_IR) & 0x00100200;       /* get config bits */

	/*
	 * Restore GPIO settings
	 */
	mtdcr(CPC0_CR0, CPC0_CR0Reg);

	switch (value) {
	case 0x00100200:
		/* CS2==1 && IRQ5==1 -> version 1.0 and 1.1 */
		return 1;
	case 0x00000200:
		/* CS2==0 && IRQ5==1 -> version 1.2 */
		return 2;
	case 0x00000000:
		/* CS2==0 && IRQ5==0 -> version 1.3 */
		return 3;
#if 0 /* not yet manufactured ! */
	case 0x00100000:
		/* CS2==1 && IRQ5==0 -> version 1.4 */
		return 4;
#endif
	default:
		/* should not be reached! */
		return 0;
	}
}


unsigned long fpga_done_state(void)
{
	if (gd->board_type < 2) {
		return FPGA_DONE_STATE_V11;
	} else {
		return FPGA_DONE_STATE_V12;
	}
}


unsigned long fpga_init_state(void)
{
	if (gd->board_type < 2) {
		return FPGA_INIT_STATE_V11;
	} else {
		return FPGA_INIT_STATE_V12;
	}
}


int board_early_init_f (void)
{
	unsigned long CPC0_CR0Reg;

	/*
	 * First pull fpga-prg pin low, to disable fpga logic (on version 1.2 board)
	 */
	out_be32((void*)GPIO0_ODR, 0x00000000);        /* no open drain pins      */
	out_be32((void*)GPIO0_TCR, CONFIG_SYS_FPGA_PRG);      /* setup for output        */
	out_be32((void*)GPIO0_OR,  CONFIG_SYS_FPGA_PRG);      /* set output pins to high */
	out_be32((void*)GPIO0_OR, 0);                  /* pull prg low            */

	/*
	 * IRQ 0-15  405GP internally generated; active high; level sensitive
	 * IRQ 16    405GP internally generated; active low; level sensitive
	 * IRQ 17-24 RESERVED
	 * IRQ 25 (EXT IRQ 0) CAN0; active low; level sensitive
	 * IRQ 26 (EXT IRQ 1) CAN1; active low; level sensitive
	 * IRQ 27 (EXT IRQ 2) CAN2; active low; level sensitive
	 * IRQ 28 (EXT IRQ 3) CAN3; active low; level sensitive
	 * IRQ 29 (EXT IRQ 4) unused; active low; level sensitive
	 * IRQ 30 (EXT IRQ 5) FPGA Timestamp; active low; level sensitive
	 * IRQ 31 (EXT IRQ 6) PCI Reset; active low; level sensitive
	 */
	mtdcr(UIC0SR, 0xFFFFFFFF);        /* clear all ints */
	mtdcr(UIC0ER, 0x00000000);        /* disable all ints */
	mtdcr(UIC0CR, 0x00000000);        /* set all to be non-critical*/
	mtdcr(UIC0PR, 0xFFFFFF80);        /* set int polarities */
	mtdcr(UIC0TR, 0x10000000);        /* set int trigger levels */
	mtdcr(UIC0VCR, 0x00000001);       /* set vect base=0,INT0 highest priority*/
	mtdcr(UIC0SR, 0xFFFFFFFF);        /* clear all ints */

	/*
	 * Setup GPIO pins (IRQ4/GPIO21 as GPIO)
	 */
	CPC0_CR0Reg = mfdcr(CPC0_CR0);
	mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x00008000);

	/*
	 * Setup GPIO pins (CS6+CS7 as GPIO)
	 */
	mtdcr(CPC0_CR0, CPC0_CR0Reg | 0x00300000);

	/*
	 * EBC Configuration Register: set ready timeout to 512 ebc-clks -> ca. 25 us
	 */
	mtebc (EBC0_CFG, 0xa8400000); /* ebc always driven */

	return 0;
}

int misc_init_r (void)
{
	unsigned char *dst;
	ulong len = sizeof(fpgadata);
	int status;
	int index;
	int i;
	unsigned int *ptr;
	unsigned int *magic;

	/*
	 * On PCI-405 the environment is saved in eeprom!
	 * FPGA can be gzip compressed (malloc) and booted this late.
	 */

	dst = malloc(CONFIG_SYS_FPGA_MAX_SIZE);
	if (gunzip (dst, CONFIG_SYS_FPGA_MAX_SIZE, (uchar *)fpgadata, &len) != 0) {
		printf ("GUNZIP ERROR - must RESET board to recover\n");
		do_reset (NULL, 0, 0, NULL);
	}

	status = fpga_boot(dst, len);
	if (status != 0) {
		printf("\nFPGA: Booting failed ");
		switch (status) {
		case ERROR_FPGA_PRG_INIT_LOW:
			printf("(Timeout: INIT not low after asserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_INIT_HIGH:
			printf("(Timeout: INIT not high after deasserting PROGRAM*)\n ");
			break;
		case ERROR_FPGA_PRG_DONE:
			printf("(Timeout: DONE not high after programming FPGA)\n ");
			break;
		}

		/* display infos on fpgaimage */
		index = 15;
		for (i=0; i<4; i++) {
			len = dst[index];
			printf("FPGA: %s\n", &(dst[index+1]));
			index += len+3;
		}
		putc ('\n');
		/* delayed reboot */
		for (i=20; i>0; i--) {
			printf("Rebooting in %2d seconds \r",i);
			for (index=0;index<1000;index++)
				udelay(1000);
		}
		putc ('\n');
		do_reset(NULL, 0, 0, NULL);
	}

	puts("FPGA:  ");

	/* display infos on fpgaimage */
	index = 15;
	for (i=0; i<4; i++) {
		len = dst[index];
		printf("%s ", &(dst[index+1]));
		index += len+3;
	}
	putc ('\n');

	/*
	 * Reset FPGA via FPGA_DATA pin
	 */
	SET_FPGA(FPGA_PRG | FPGA_CLK);
	udelay(1000); /* wait 1ms */
	SET_FPGA(FPGA_PRG | FPGA_CLK | FPGA_DATA);
	udelay(1000); /* wait 1ms */

	/*
	 * Check if magic for pci reconfig is written
	 */
	magic = (unsigned int *)0x00000004;
	if (*magic == PCI_RECONFIG_MAGIC) {
		/*
		 * Rewrite pci config regs (only after soft-reset with magic set)
		 */
		ptr = (unsigned int *)PCI_REGS_ADDR;
		if (crc32(0, (uchar *)PCI_REGS_ADDR+4, PCI_REGS_LEN-4) == *ptr) {
			puts("Restoring PCI Configurations Regs!\n");
			ptr = (unsigned int *)PCI_REGS_ADDR + 1;
			for (i=0; i<0x40; i+=4) {
				pci_write_config_dword(PCIDEVID_405GP, i, *ptr++);
			}
		}
		mtdcr(UIC0SR, 0xFFFFFFFF);        /* clear all ints */

		*magic = 0;      /* clear pci reconfig magic again */
	}

	/*
	 * Decrease PLB latency timeout and reduce priority of the PCI bridge master
	 */
#define PCI0_BRDGOPT1 0x4a
	pci_write_config_word(PCIDEVID_405GP, PCI0_BRDGOPT1, 0x3f20);

	/*
	 * Enable fairness and high bus utilization
	 */
	mtdcr(PLB0_ACR, 0x98000000);

	free(dst);
	return (0);
}


/*
 * Check Board Identity:
 */
int checkboard (void)
{
	char str[64];
	int i = getenv_f("serial#", str, sizeof(str));

	puts ("Board: ");

	if (i == -1) {
		puts ("### No HW ID - assuming PCI405");
	} else {
		puts (str);
	}

	gd->board_type = board_revision();
	printf(" (Rev 1.%ld", gd->board_type);

	if (gd->board_type >= 2) {
		unsigned long CPC0_CR0Reg;
		unsigned long value;

		/*
		 * Setup GPIO pins (Trace/GPIO1 to GPIO)
		 */
		CPC0_CR0Reg = mfdcr(CPC0_CR0);
		mtdcr(CPC0_CR0, CPC0_CR0Reg & ~0x08000000);
		out_be32((void*)GPIO0_ODR, in_be32((void*)GPIO0_ODR) & ~0x40000000);
		out_be32((void*)GPIO0_TCR, in_be32((void*)GPIO0_TCR) & ~0x40000000);
		udelay(1000);                   /* wait some time before reading input */
		value = in_be32((void*)GPIO0_IR) & 0x40000000;       /* get config bits */
		if (value) {
			puts(", 33 MHz PCI");
		} else {
			puts(", 66 MHz PCI");
		}
	}

	puts(")\n");

	return 0;
}

/* ------------------------------------------------------------------------- */
#define UART1_MCR 0xef600404
int wpeeprom(int wp)
{
	int wp_state = wp;

	if (wp == 1) {
		out_8((void *)UART1_MCR, in_8((void *)UART1_MCR) & ~0x02);
	} else if (wp == 0) {
		out_8((void *)UART1_MCR, in_8((void *)UART1_MCR) | 0x02);
	} else {
		if (in_8((void *)UART1_MCR) & 0x02) {
			wp_state = 0;
		} else {
			wp_state = 1;
		}
	}
	return wp_state;
}

int do_wpeeprom(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int wp = -1;
	if (argc >= 2) {
		if (argv[1][0] == '1') {
			wp = 1;
		} else if (argv[1][0] == '0') {
			wp = 0;
		}
	}

	wp = wpeeprom(wp);
	printf("EEPROM write protection %s\n", wp ? "ENABLED" : "DISABLED");
	return 0;
}

U_BOOT_CMD(
	wpeeprom,	2,	1,	do_wpeeprom,
	"Check/Enable/Disable I2C EEPROM write protection",
	"wpeeprom\n"
	"    - check I2C EEPROM write protection state\n"
	"wpeeprom 1\n"
	"    - enable I2C EEPROM write protection\n"
	"wpeeprom 0\n"
	"    - disable I2C EEPROM write protection"
);
