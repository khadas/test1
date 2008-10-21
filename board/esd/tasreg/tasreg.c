/*
 * (C) Copyright 2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
#include <command.h>
#include <malloc.h>
#include <asm/m5249.h>


/* Prototypes */
int gunzip(void *, int, unsigned char *, unsigned long *);
int do_reset (cmd_tbl_t *cmdtp, int flag, int argc, char *argv[]);
int i2c_write(uchar chip, uint addr, int alen, uchar *buffer, int len);
int i2c_read(uchar chip, uint addr, int alen, uchar *buffer, int len);


#if 0
#define FPGA_DEBUG
#endif

/* predefine these here for FPGA programming (before including fpga.c) */
#define SET_FPGA(data)  mbar2_writeLong(MCFSIM_GPIO1_OUT, data)
#define FPGA_DONE_STATE (mbar2_readLong(MCFSIM_GPIO1_READ) & CONFIG_SYS_FPGA_DONE)
#define FPGA_INIT_STATE (mbar2_readLong(MCFSIM_GPIO1_READ) & CONFIG_SYS_FPGA_INIT)
#define FPGA_PROG_ACTIVE_HIGH          /* on this platform is PROG active high!   */
#define out32(a,b)                     /* nothing to do (gpio already configured) */


/* fpga configuration data - generated by bin2cc */
const unsigned char fpgadata[] =
{
#include "fpgadata.c"
};

/*
 * include common fpga code (for esd boards)
 */
#include "../common/fpga.c"


int checkboard (void) {
	ulong val;
	uchar val8;

	puts ("Board: ");
	puts("esd TASREG");
	val8 = ((uchar)~((uchar)mbar2_readLong(MCFSIM_GPIO1_READ) >> 4)) & 0xf;
	printf(" (Switch=%1X)\n", val8);

	/*
	 * Set LED on
	 */
	val = mbar2_readLong(MCFSIM_GPIO1_OUT) & ~CONFIG_SYS_GPIO1_LED;
	mbar2_writeLong(MCFSIM_GPIO1_OUT, val);   /* Set LED on */

	return 0;
};


phys_size_t initdram (int board_type) {
	unsigned long	junk = 0xa5a59696;

	/*
	 *  Note:
	 *	RC = ([(RefreshTime/#rows) / (1/BusClk)] / 16) - 1
	 */

#ifdef CONFIG_SYS_FAST_CLK
	/*
	 * Busclk=70MHz, RefreshTime=64ms, #rows=4096 (4K)
	 * SO=1, NAM=0, COC=0, RTIM=01 (6clk refresh), RC=39
	 */
	mbar_writeShort(MCFSIM_DCR, 0x8239);
#elif CONFIG_SYS_PLL_BYPASS
	/*
	 * Busclk=5.6448MHz, RefreshTime=64ms, #rows=8192 (8K)
	 * SO=1, NAM=0, COC=0, RTIM=01 (6clk refresh), RC=02
	 */
	mbar_writeShort(MCFSIM_DCR, 0x8202);
#else
	/*
	 * Busclk=36MHz, RefreshTime=64ms, #rows=4096 (4K)
	 * SO=1, NAM=0, COC=0, RTIM=01 (6clk refresh), RC=22 (562 bus clock cycles)
	 */
	mbar_writeShort(MCFSIM_DCR, 0x8222);
#endif

	/*
	 * SDRAM starts at 0x0000_0000, CASL=10, CBM=010, PS=10 (16bit port),
	 * PM=1 (continuous page mode)
	 */

	/* RE=0 (keep auto-refresh disabled while setting up registers) */
	mbar_writeLong(MCFSIM_DACR0, 0x00003324);

	/* BAM=007c (bits 22,21 are bank selects; 256kB blocks) */
	mbar_writeLong(MCFSIM_DMR0, 0x01fc0001);

	/** Precharge sequence **/
	mbar_writeLong(MCFSIM_DACR0, 0x0000332c); /* Set DACR0[IP] (bit 3) */
	*((volatile unsigned long *) 0x00) = junk; /* write to a memory location to init. precharge */
	udelay(0x10); /* Allow several Precharge cycles */

	/** Refresh Sequence **/
	mbar_writeLong(MCFSIM_DACR0, 0x0000b324); /* Enable the refresh bit, DACR0[RE] (bit 15) */
	udelay(0x7d0); /* Allow gobs of refresh cycles */

	/** Mode Register initialization **/
	mbar_writeLong(MCFSIM_DACR0, 0x0000b364);  /* Enable DACR0[IMRS] (bit 6); RE remains enabled */
	*((volatile unsigned long *) 0x800) = junk; /* Access RAM to initialize the mode register */

	return CONFIG_SYS_SDRAM_SIZE * 1024 * 1024;
};


int testdram (void) {
	/* TODO: XXX XXX XXX */
	printf ("DRAM test not implemented!\n");

	return (0);
}


int misc_init_r (void)
{
	unsigned char *dst;
	ulong len = sizeof(fpgadata);
	int status;
	int index;
	int i;
	uchar buf[8];

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

	free(dst);

	/*
	 *
	 */
	buf[0] = 0x00;
	buf[1] = 0x32;
	buf[2] = 0x3f;
	i2c_write(0x38, 0, 0, buf, 3);

	return (0);
}


#if 1 /* test-only: board specific test commands */
int i2c_probe(uchar addr);

/*
 */
int do_iploop(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong addr;

	if (argc < 2) {
		puts("ERROR!\n");
		return -1;
	}

	addr = simple_strtol (argv[1], NULL, 16);

	printf("iprobe looping on addr 0x%lx (cntrl-c aborts)...\n", addr);

	for (;;) {
		i2c_probe(addr);

		/* Abort if ctrl-c was pressed */
		if (ctrlc()) {
			puts("\nAbort\n");
			return 0;
		}

		udelay(1000);
	}

	return 0;
}
U_BOOT_CMD(
	iploop,	2,	1,	do_iploop,
	"iploop - iprobe loop <addr>\n",
	NULL
	);

/*
 */
int do_codec(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	uchar buf[8];

	*(volatile ushort *)0xe0000000 = 0x4000;

	udelay(5000); /* wait for 5ms */

	buf[0] = 0x10;
	buf[1] = 0x07;
	buf[2] = 0x03;
	i2c_write(0x10, 0, 0, buf, 3);

	buf[0] = 0x10;
	buf[1] = 0x01;
	buf[2] = 0x80;
	i2c_write(0x10, 0, 0, buf, 3);

	buf[0] = 0x10;
	buf[1] = 0x02;
	buf[2] = 0x03;
	i2c_write(0x10, 0, 0, buf, 3);

	buf[0] = 0x10;
	buf[1] = 0x03;
	buf[2] = 0x29;
	i2c_write(0x10, 0, 0, buf, 3);

	buf[0] = 0x10;
	buf[1] = 0x04;
	buf[2] = 0x00;
	i2c_write(0x10, 0, 0, buf, 3);

	buf[0] = 0x10;
	buf[1] = 0x05;
	buf[2] = 0x00;
	i2c_write(0x10, 0, 0, buf, 3);

	buf[0] = 0x10;
	buf[1] = 0x07;
	buf[2] = 0x02;
	i2c_write(0x10, 0, 0, buf, 3);

	return 0;
}
U_BOOT_CMD(
	codec,	1,	1,	do_codec,
	"codec - Enable codec\n",
	NULL
	);

/*
 */
int do_saa(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong addr;
	ulong instr;
	ulong cntrl;
	ulong data;
	uchar buf[8];

	if (argc < 5) {
		puts("ERROR!\n");
		return -1;
	}

	addr = simple_strtol (argv[1], NULL, 16);
	instr = simple_strtol (argv[2], NULL, 16);
	cntrl = simple_strtol (argv[3], NULL, 16);
	data = simple_strtol (argv[4], NULL, 16);

	buf[0] = (uchar)instr;
	buf[1] = (uchar)cntrl;
	buf[2] = (uchar)data;
	i2c_write(addr, 0, 0, buf, 3);

	return 0;
}
U_BOOT_CMD(
	saa,	5,	1,	do_saa,
	"saa    - Write to SAA1064 <addr> <instr> <cntrl> <data>\n",
	NULL
	);

/*
 */
int do_iwrite(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong addr;
	ulong data0;
	ulong data1;
	ulong data2;
	ulong data3;
	uchar buf[8];
	int cnt;

	if (argc < 3) {
		puts("ERROR!\n");
		return -1;
	}

	addr = simple_strtol (argv[1], NULL, 16);
	cnt = simple_strtol (argv[2], NULL, 16);
	data0 = simple_strtol (argv[3], NULL, 16);
	data1 = simple_strtol (argv[4], NULL, 16);
	data2 = simple_strtol (argv[5], NULL, 16);
	data3 = simple_strtol (argv[6], NULL, 16);

	printf("Writing %d bytes to device %lx!\n", cnt, addr);
	buf[0] = (uchar)data0;
	buf[1] = (uchar)data1;
	buf[2] = (uchar)data2;
	buf[3] = (uchar)data3;
	i2c_write(addr, 0, 0, buf, cnt);

	return 0;
}
U_BOOT_CMD(
	iwrite,	6,	1,	do_iwrite,
	"iwrite - Write n bytes to I2C-device\n",
	"addr cnt data0 ... datan\n"
	);

/*
 */
int do_iread(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong addr;
	ulong cnt;
	uchar buf[32];
	int i;

	if (argc < 3) {
		puts("ERROR!\n");
		return -1;
	}

	addr = simple_strtol (argv[1], NULL, 16);
	cnt = simple_strtol (argv[2], NULL, 16);

	i2c_read(addr, 0, 0, buf, cnt);
	printf("I2C Data:");
	for (i=0; i<cnt; i++) {
		printf(" %02X", buf[i]);
	}
	printf("\n");

	return 0;
}
U_BOOT_CMD(
	iread,	3,	1,	do_iread,
	"iread  - Read from I2C <addr> <cnt>\n",
	NULL
	);

/*
 */
int do_ireadl(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	ulong addr;
	uchar buf[32];
	int cnt;

	if (argc < 2) {
		puts("ERROR!\n");
		return -1;
	}

	addr = simple_strtol (argv[1], NULL, 16);
	cnt = 1;

	printf("iread looping on addr 0x%lx (cntrl-c aborts)...\n", addr);

	for (;;) {
		i2c_read(addr, 0, 0, buf, cnt);

		/* Abort if ctrl-c was pressed */
		if (ctrlc()) {
			puts("\nAbort\n");
			return 0;
		}

		udelay(3000);
	}

	return 0;
}
U_BOOT_CMD(
	ireadl,	2,	1,	do_ireadl,
	"ireadl - Read-loop from I2C <addr>\n",
	NULL
	);
#endif
