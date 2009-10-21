/*
 * Copyright 2004,2007-2010 Freescale Semiconductor, Inc.
 * (C) Copyright 2002, 2003 Motorola Inc.
 * Xianghua Xiao (X.Xiao@motorola.com)
 *
 * (C) Copyright 2000
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

#include <config.h>
#include <common.h>
#include <watchdog.h>
#include <command.h>
#include <fsl_esdhc.h>
#include <asm/cache.h>
#include <asm/io.h>
#include <asm/mmu.h>
#include <asm/fsl_law.h>

DECLARE_GLOBAL_DATA_PTR;

int checkcpu (void)
{
	sys_info_t sysinfo;
	uint pvr, svr;
	uint fam;
	uint ver;
	uint major, minor;
	struct cpu_type *cpu;
	char buf1[32], buf2[32];
#if defined(CONFIG_DDR_CLK_FREQ) || defined(CONFIG_FSL_CORENET)
	volatile ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
#endif /* CONFIG_FSL_CORENET */
#ifdef CONFIG_DDR_CLK_FREQ
	u32 ddr_ratio = ((gur->porpllsr) & MPC85xx_PORPLLSR_DDR_RATIO)
		>> MPC85xx_PORPLLSR_DDR_RATIO_SHIFT;
#else
#ifdef CONFIG_FSL_CORENET
	u32 ddr_sync = ((gur->rcwsr[5]) & FSL_CORENET_RCWSR5_DDR_SYNC)
		>> FSL_CORENET_RCWSR5_DDR_SYNC_SHIFT;
#else
	u32 ddr_ratio = 0;
#endif /* CONFIG_FSL_CORENET */
#endif /* CONFIG_DDR_CLK_FREQ */
	int i;

	svr = get_svr();
	major = SVR_MAJ(svr);
#ifdef CONFIG_MPC8536
	major &= 0x7; /* the msb of this nibble is a mfg code */
#endif
	minor = SVR_MIN(svr);

	if (cpu_numcores() > 1) {
#ifndef CONFIG_MP
		puts("Unicore software on multiprocessor system!!\n"
		     "To enable mutlticore build define CONFIG_MP\n");
#endif
		volatile ccsr_pic_t *pic = (void *)(CONFIG_SYS_MPC85xx_PIC_ADDR);
		printf("CPU%d:  ", pic->whoami);
	} else {
		puts("CPU:   ");
	}

	cpu = gd->cpu;

	puts(cpu->name);
	if (IS_E_PROCESSOR(svr))
		puts("E");

	printf(", Version: %d.%d, (0x%08x)\n", major, minor, svr);

	pvr = get_pvr();
	fam = PVR_FAM(pvr);
	ver = PVR_VER(pvr);
	major = PVR_MAJ(pvr);
	minor = PVR_MIN(pvr);

	printf("Core:  ");
	if (PVR_FAM(PVR_85xx)) {
		switch(PVR_MEM(pvr)) {
		case 0x1:
		case 0x2:
			puts("E500");
			break;
		case 0x3:
			puts("E500MC");
			break;
		case 0x4:
			puts("E5500");
			break;
		default:
			puts("Unknown");
			break;
		}
	} else {
		puts("Unknown");
	}

	printf(", Version: %d.%d, (0x%08x)\n", major, minor, pvr);

	get_sys_info(&sysinfo);

	puts("Clock Configuration:");
	for (i = 0; i < cpu_numcores(); i++) {
		if (!(i & 3))
			printf ("\n       ");
		printf("CPU%d:%-4s MHz, ",
				i,strmhz(buf1, sysinfo.freqProcessor[i]));
	}
	printf("\n       CCB:%-4s MHz,\n", strmhz(buf1, sysinfo.freqSystemBus));

#ifdef CONFIG_FSL_CORENET
	if (ddr_sync == 1) {
		printf("       DDR:%-4s MHz (%s MT/s data rate) "
			"(Synchronous), ",
			strmhz(buf1, sysinfo.freqDDRBus/2),
			strmhz(buf2, sysinfo.freqDDRBus));
	} else {
		printf("       DDR:%-4s MHz (%s MT/s data rate) "
			"(Asynchronous), ",
			strmhz(buf1, sysinfo.freqDDRBus/2),
			strmhz(buf2, sysinfo.freqDDRBus));
	}
#else
	switch (ddr_ratio) {
	case 0x0:
		printf("       DDR:%-4s MHz (%s MT/s data rate), ",
			strmhz(buf1, sysinfo.freqDDRBus/2),
			strmhz(buf2, sysinfo.freqDDRBus));
		break;
	case 0x7:
		printf("       DDR:%-4s MHz (%s MT/s data rate) "
			"(Synchronous), ",
			strmhz(buf1, sysinfo.freqDDRBus/2),
			strmhz(buf2, sysinfo.freqDDRBus));
		break;
	default:
		printf("       DDR:%-4s MHz (%s MT/s data rate) "
			"(Asynchronous), ",
			strmhz(buf1, sysinfo.freqDDRBus/2),
			strmhz(buf2, sysinfo.freqDDRBus));
		break;
	}
#endif

	if (sysinfo.freqLocalBus > LCRR_CLKDIV) {
		printf("LBC:%-4s MHz\n", strmhz(buf1, sysinfo.freqLocalBus));
	} else {
		printf("LBC: unknown (LCRR[CLKDIV] = 0x%02lx)\n",
		       sysinfo.freqLocalBus);
	}

#ifdef CONFIG_CPM2
	printf("CPM:   %s MHz\n", strmhz(buf1, sysinfo.freqSystemBus));
#endif

#ifdef CONFIG_QE
	printf("       QE:%-4s MHz\n", strmhz(buf1, sysinfo.freqQE));
#endif

#ifdef CONFIG_SYS_DPAA_FMAN
	for (i = 0; i < CONFIG_SYS_NUM_FMAN; i++) {
		printf("       FMAN%d: %s MHz\n", i,
			strmhz(buf1, sysinfo.freqFMan[i]));
	}
#endif

#ifdef CONFIG_SYS_DPAA_PME
	printf("       PME:   %s MHz\n", strmhz(buf1, sysinfo.freqPME));
#endif

	puts("L1:    D-cache 32 kB enabled\n       I-cache 32 kB enabled\n");

	return 0;
}


/* ------------------------------------------------------------------------- */

int do_reset (cmd_tbl_t *cmdtp, bd_t *bd, int flag, int argc, char * const argv[])
{
/* Everything after the first generation of PQ3 parts has RSTCR */
#if defined(CONFIG_MPC8540) || defined(CONFIG_MPC8541) || \
    defined(CONFIG_MPC8555) || defined(CONFIG_MPC8560)
	unsigned long val, msr;

	/*
	 * Initiate hard reset in debug control register DBCR0
	 * Make sure MSR[DE] = 1.  This only resets the core.
	 */
	msr = mfmsr ();
	msr |= MSR_DE;
	mtmsr (msr);

	val = mfspr(DBCR0);
	val |= 0x70000000;
	mtspr(DBCR0,val);
#else
	volatile ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
	out_be32(&gur->rstcr, 0x2);	/* HRESET_REQ */
	udelay(100);
#endif

	return 1;
}


/*
 * Get timebase clock frequency
 */
unsigned long get_tbclk (void)
{
#ifdef CONFIG_FSL_CORENET
	return (gd->bus_clk + 8) / 16;
#else
	return (gd->bus_clk + 4UL)/8UL;
#endif
}


#if defined(CONFIG_WATCHDOG)
void
watchdog_reset(void)
{
	int re_enable = disable_interrupts();
	reset_85xx_watchdog();
	if (re_enable) enable_interrupts();
}

void
reset_85xx_watchdog(void)
{
	/*
	 * Clear TSR(WIS) bit by writing 1
	 */
	unsigned long val;
	val = mfspr(SPRN_TSR);
	val |= TSR_WIS;
	mtspr(SPRN_TSR, val);
}
#endif	/* CONFIG_WATCHDOG */

/*
 * Initializes on-chip MMC controllers.
 * to override, implement board_mmc_init()
 */
int cpu_mmc_init(bd_t *bis)
{
#ifdef CONFIG_FSL_ESDHC
	return fsl_esdhc_mmc_init(bis);
#else
	return 0;
#endif
}

/*
 * Print out the state of various machine registers.
 * Currently prints out LAWs, BR0/OR0, and TLBs
 */
void mpc85xx_reginfo(void)
{
	print_tlbcam();
	print_laws();
	print_lbc_regs();
}
