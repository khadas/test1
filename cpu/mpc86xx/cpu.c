/*
 * Copyright 2006 Freescale Semiconductor
 * Jeff Brown
 * Srikanth Srinivasan (srikanth.srinivasan@freescale.com)
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
#include <watchdog.h>
#include <command.h>
#include <asm/cache.h>
#include <asm/mmu.h>
#include <mpc86xx.h>
#include <tsec.h>
#include <asm/fsl_law.h>


/*
 * Default board reset function
 */
static void
__board_reset(void)
{
	/* Do nothing */
}
void board_reset(void) __attribute((weak, alias("__board_reset")));


int
checkcpu(void)
{
	sys_info_t sysinfo;
	uint pvr, svr;
	uint ver;
	uint major, minor;
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;
	volatile ccsr_gur_t *gur = &immap->im_gur;

	puts("Freescale PowerPC\n");

	pvr = get_pvr();
	ver = PVR_VER(pvr);
	major = PVR_MAJ(pvr);
	minor = PVR_MIN(pvr);

	puts("CPU:\n");
	puts("    Core: ");

	switch (ver) {
	case PVR_VER(PVR_86xx):
	{
		uint msscr0 = mfspr(MSSCR0);
		printf("E600 Core %d", (msscr0 & 0x20) ? 1 : 0 );
		if (gur->pordevsr & MPC86xx_PORDEVSR_CORE1TE)
			puts("\n    Core1Translation Enabled");
		debug(" (MSSCR0=%x, PORDEVSR=%x)", msscr0, gur->pordevsr);
	}
	break;
	default:
		puts("Unknown");
		break;
	}
	printf(", Version: %d.%d, (0x%08x)\n", major, minor, pvr);

	svr = get_svr();
	ver = SVR_SOC_VER(svr);
	major = SVR_MAJ(svr);
	minor = SVR_MIN(svr);

	puts("    System: ");
	switch (ver) {
	case SVR_8641:
	    if (SVR_SUBVER(svr) == 1) {
		puts("8641D");
	    } else {
		puts("8641");
	    }
	    break;
	case SVR_8610:
		puts("8610");
		break;
	default:
		puts("Unknown");
		break;
	}
	printf(", Version: %d.%d, (0x%08x)\n", major, minor, svr);

	get_sys_info(&sysinfo);

	puts("    Clocks: ");
	printf("CPU:%4lu MHz, ", sysinfo.freqProcessor / 1000000);
	printf("MPX:%4lu MHz, ", sysinfo.freqSystemBus / 1000000);
	printf("DDR:%4lu MHz, ", sysinfo.freqSystemBus / 2000000);

	if (sysinfo.freqLocalBus > LCRR_CLKDIV) {
		printf("LBC:%4lu MHz\n", sysinfo.freqLocalBus / 1000000);
	} else {
		printf("LBC: unknown (LCRR[CLKDIV] = 0x%02lx)\n",
		       sysinfo.freqLocalBus);
	}

	puts("    L2: ");
	if (get_l2cr() & 0x80000000)
		puts("Enabled\n");
	else
		puts("Disabled\n");

	return 0;
}


void
do_reset(cmd_tbl_t *cmdtp, int flag, int argc, char *argv[])
{
	volatile immap_t *immap = (immap_t *)CONFIG_SYS_IMMR;
	volatile ccsr_gur_t *gur = &immap->im_gur;

	/* Attempt board-specific reset */
	board_reset();

	/* Next try asserting HRESET_REQ */
	out_be32(&gur->rstcr, MPC86xx_RSTCR_HRST_REQ);

	while (1)
		;
}


/*
 * Get timebase clock frequency
 */
unsigned long
get_tbclk(void)
{
	sys_info_t sys_info;

	get_sys_info(&sys_info);
	return (sys_info.freqSystemBus + 3L) / 4L;
}


#if defined(CONFIG_WATCHDOG)
void
watchdog_reset(void)
{
#if defined(CONFIG_MPC8610)
	/*
	 * This actually feed the hard enabled watchdog.
	 */
	volatile immap_t *immap = (immap_t *)CONFIG_SYS_IMMR;
	volatile ccsr_wdt_t *wdt = &immap->im_wdt;
	volatile ccsr_gur_t *gur = &immap->im_gur;
	u32 tmp = gur->pordevsr;

	if (tmp & 0x4000) {
		wdt->swsrr = 0x556c;
		wdt->swsrr = 0xaa39;
	}
#endif
}
#endif	/* CONFIG_WATCHDOG */


#if defined(CONFIG_DDR_ECC)
void
dma_init(void)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;
	volatile ccsr_dma_t *dma = &immap->im_dma;

	dma->satr0 = 0x00040000;
	dma->datr0 = 0x00040000;
	asm("sync; isync");
}

uint
dma_check(void)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;
	volatile ccsr_dma_t *dma = &immap->im_dma;
	volatile uint status = dma->sr0;

	/* While the channel is busy, spin */
	while ((status & 4) == 4) {
		status = dma->sr0;
	}

	if (status != 0) {
		printf("DMA Error: status = %x\n", status);
	}
	return status;
}

int
dma_xfer(void *dest, uint count, void *src)
{
	volatile immap_t *immap = (immap_t *) CONFIG_SYS_IMMR;
	volatile ccsr_dma_t *dma = &immap->im_dma;

	dma->dar0 = (uint) dest;
	dma->sar0 = (uint) src;
	dma->bcr0 = count;
	dma->mr0 = 0xf000004;
	asm("sync;isync");
	dma->mr0 = 0xf000005;
	asm("sync;isync");
	return dma_check();
}

#endif	/* CONFIG_DDR_ECC */


/*
 * Print out the state of various machine registers.
 * Currently prints out LAWs, BR0/OR0, and BATs
 */
void mpc86xx_reginfo(void)
{
	immap_t *immap = (immap_t *)CONFIG_SYS_IMMR;
	ccsr_lbc_t *lbc = &immap->im_lbc;

	print_bats();
	print_laws();

	printf ("Local Bus Controller Registers\n"
		"\tBR0\t0x%08X\tOR0\t0x%08X \n", in_be32(&lbc->br0), in_be32(&lbc->or0));
	printf("\tBR1\t0x%08X\tOR1\t0x%08X \n", in_be32(&lbc->br1), in_be32(&lbc->or1));
	printf("\tBR2\t0x%08X\tOR2\t0x%08X \n", in_be32(&lbc->br2), in_be32(&lbc->or2));
	printf("\tBR3\t0x%08X\tOR3\t0x%08X \n", in_be32(&lbc->br3), in_be32(&lbc->or3));
	printf("\tBR4\t0x%08X\tOR4\t0x%08X \n", in_be32(&lbc->br4), in_be32(&lbc->or4));
	printf("\tBR5\t0x%08X\tOR5\t0x%08X \n", in_be32(&lbc->br5), in_be32(&lbc->or5));
	printf("\tBR6\t0x%08X\tOR6\t0x%08X \n", in_be32(&lbc->br6), in_be32(&lbc->or6));
	printf("\tBR7\t0x%08X\tOR7\t0x%08X \n", in_be32(&lbc->br7), in_be32(&lbc->or7));

}

/*
 * Initializes on-chip ethernet controllers.
 * to override, implement board_eth_init()
 */
int cpu_eth_init(bd_t *bis)
{
#if defined(CONFIG_TSEC_ENET)
	tsec_standard_init(bis);
#endif

	return 0;
}
