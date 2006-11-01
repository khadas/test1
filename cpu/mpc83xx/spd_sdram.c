/*
 * (C) Copyright 2006 Freescale Semiconductor, Inc.
 *
 * (C) Copyright 2006
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copyright 2004 Freescale Semiconductor.
 * (C) Copyright 2003 Motorola Inc.
 * Xianghua Xiao (X.Xiao@motorola.com)
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Change log:
 *
 * 20050101: Eran Liberty (liberty@freescale.com)
 *           Initial file creating (porting from 85XX & 8260)
 * 20060601: Dave Liu (daveliu@freescale.com)
 *           DDR ECC support
 *           unify variable names for 83xx
 *           code cleanup
 */

#include <common.h>
#include <asm/processor.h>
#include <i2c.h>
#include <spd.h>
#include <asm/mmu.h>
#include <spd_sdram.h>

#ifdef CONFIG_SPD_EEPROM

#if defined(CONFIG_DDR_ECC) && !defined(CONFIG_ECC_INIT_VIA_DDRC)
extern void dma_init(void);
extern uint dma_check(void);
extern int dma_xfer(void *dest, uint count, void *src);
#endif

#ifndef	CFG_READ_SPD
#define CFG_READ_SPD	i2c_read
#endif

/*
 * Convert picoseconds into clock cycles (rounding up if needed).
 */
extern ulong get_ddr_clk(ulong dummy);

int
picos_to_clk(int picos)
{
	unsigned int ddr_bus_clk;
	int clks;

	ddr_bus_clk = get_ddr_clk(0) >> 1;
	clks = picos / ((1000000000 / ddr_bus_clk) * 1000);
	if (picos % ((1000000000 / ddr_bus_clk) * 1000) !=0) {
		clks++;
	}

	return clks;
}

unsigned int banksize(unsigned char row_dens)
{
	return ((row_dens >> 2) | ((row_dens & 3) << 6)) << 24;
}

int read_spd(uint addr)
{
	return ((int) addr);
}

#undef SPD_DEBUG
#ifdef SPD_DEBUG
static void spd_debug(spd_eeprom_t *spd)
{
	printf ("\nDIMM type:       %-18.18s\n", spd->mpart);
	printf ("SPD size:        %d\n", spd->info_size);
	printf ("EEPROM size:     %d\n", 1 << spd->chip_size);
	printf ("Memory type:     %d\n", spd->mem_type);
	printf ("Row addr:        %d\n", spd->nrow_addr);
	printf ("Column addr:     %d\n", spd->ncol_addr);
	printf ("# of rows:       %d\n", spd->nrows);
	printf ("Row density:     %d\n", spd->row_dens);
	printf ("# of banks:      %d\n", spd->nbanks);
	printf ("Data width:      %d\n",
			256 * spd->dataw_msb + spd->dataw_lsb);
	printf ("Chip width:      %d\n", spd->primw);
	printf ("Refresh rate:    %02X\n", spd->refresh);
	printf ("CAS latencies:   %02X\n", spd->cas_lat);
	printf ("Write latencies: %02X\n", spd->write_lat);
	printf ("tRP:             %d\n", spd->trp);
	printf ("tRCD:            %d\n", spd->trcd);
	printf ("\n");
}
#endif /* SPD_DEBUG */

long int spd_sdram()
{
#ifdef CONFIG_MPC834X
	int caslat_83xx;  /* For Errata DDR6 */
#endif
	volatile immap_t *immap = (immap_t *)CFG_IMMRBAR;
	volatile ddr83xx_t *ddr = &immap->ddr;
	volatile law83xx_t *ecm = &immap->sysconf.ddrlaw[0];
	spd_eeprom_t spd;
	unsigned int tmp, tmp1;
	unsigned int memsize;
	unsigned int law_size;
	unsigned char caslat, caslat_ctrl;
	unsigned char burstlen;
	unsigned int max_bus_clk;
	unsigned int max_data_rate, effective_data_rate;
	unsigned int ddrc_clk;
	unsigned int refresh_clk;
	unsigned sdram_cfg;
	unsigned int ddrc_ecc_enable;


        /* Read SPD parameters with I2C */
	CFG_READ_SPD(SPD_EEPROM_ADDRESS, 0, 1, (uchar *) & spd, sizeof (spd));
#ifdef SPD_DEBUG
	spd_debug(&spd);
#endif
	/* Check the memory type */
	if (spd.mem_type != SPD_MEMTYPE_DDR) {
		printf("DDR: Module mem type is %02X\n", spd.mem_type);
		return 0;
	}

	/* Check the number of physical bank */
	if (spd.nrows > 2) {
		printf("DDR: The number of physical bank is %02X\n", spd.nrows);
		return 0;
	}

	/* Check if the number of row of the module is in the range of DDRC */
	if (spd.nrow_addr < 12 || spd.nrow_addr > 14) {
		printf("DDR: Row number is out of range of DDRC, row=%02X\n",
							 spd.nrow_addr);
		return 0;
	}

	/* Check if the number of col of the module is in the range of DDRC */
	if (spd.ncol_addr < 8 || spd.ncol_addr > 11) {
		printf("DDR: Col number is out of range of DDRC, col=%02X\n",
							 spd.ncol_addr);
		return 0;
	}
        /* Setup DDR chip select register */
	ddr->csbnds[2].csbnds = (banksize(spd.row_dens) >> 24) - 1;
	ddr->cs_config[2] = ( 1 << 31
			    | (spd.nrow_addr - 12) << 8
			    | (spd.ncol_addr - 8) );
	debug("\n");
	debug("cs2_bnds = 0x%08x\n",ddr->csbnds[2].csbnds);
	debug("cs2_config = 0x%08x\n",ddr->cs_config[2]);

	if (spd.nrows == 2) {
		ddr->csbnds[3].csbnds = ( (banksize(spd.row_dens) >> 8)
				  | ((banksize(spd.row_dens) >> 23) - 1) );
		ddr->cs_config[3] = ( 1<<31
				    | (spd.nrow_addr-12) << 8
				    | (spd.ncol_addr-8) );
		debug("cs3_bnds = 0x%08x\n",ddr->csbnds[3].csbnds);
		debug("cs3_config = 0x%08x\n",ddr->cs_config[3]);
	}

	if (spd.mem_type != 0x07) {
		puts("No DDR module found!\n");
		return 0;
	}

	/*
	 * Figure out memory size in Megabytes.
	 */
	memsize = spd.nrows * banksize(spd.row_dens) / 0x100000;

	/*
	 * First supported LAW size is 16M, at LAWAR_SIZE_16M == 23.
	 */
	law_size = 19 + __ilog2(memsize);

	/*
	 * Set up LAWBAR for all of DDR.
	 */
	ecm->bar = ((CFG_DDR_SDRAM_BASE>>12) & 0xfffff);
	ecm->ar  = (LAWAR_EN | LAWAR_TRGT_IF_DDR | (LAWAR_SIZE & law_size));
	debug("DDR:bar=0x%08x\n", ecm->bar);
	debug("DDR:ar=0x%08x\n", ecm->ar);

	/*
	 * Find the largest CAS by locating the highest 1 bit
	 * in the spd.cas_lat field.  Translate it to a DDR
	 * controller field value:
	 *
	 *	CAS Lat	 DDR I	   Ctrl
	 *	Clocks	 SPD Bit   Value
	 *	-------+--------+---------
	 *	1.0        0        001
	 *	1.5        1        010
	 *	2.0        2        011
	 *	2.5        3        100
	 *	3.0        4        101
	 *	3.5        5        110
	 *	4.0        6        111
	 */
	caslat = __ilog2(spd.cas_lat);

	if (caslat > 4 ) {
		printf("DDR: Invalid SPD CAS Latency, caslat=%02X\n", caslat);
		return 0;
	}
	max_bus_clk = 1000 *10 / (((spd.clk_cycle & 0xF0) >> 4) * 10
			+ (spd.clk_cycle & 0x0f));
	max_data_rate = max_bus_clk * 2;

	debug("DDR:Module maximum data rate is: %dMhz\n", max_data_rate);

	ddrc_clk = get_ddr_clk(0) / 1000000;

	if (max_data_rate >= 390) { /* it is DDR 400 */
		printf("DDR: platform not support DDR 400\n");
		return 0;
	} else if (max_data_rate >= 323) { /* it is DDR 333 */
		if (ddrc_clk <= 350 && ddrc_clk > 280) {
			/* DDRC clk at 280~350 */
			effective_data_rate = 333; /* 6ns */
			caslat = caslat;
		} else if (ddrc_clk <= 280 && ddrc_clk > 230) {
			/* DDRC clk at 230~280 */
			if (spd.clk_cycle2 == 0x75) {
				effective_data_rate = 266; /* 7.5ns */
				caslat = caslat - 1;
			}
		} else if (ddrc_clk <= 230 && ddrc_clk > 90) {
			/* DDRC clk at 90~230 */
			if (spd.clk_cycle3 == 0xa0) {
				effective_data_rate = 200; /* 10ns */
				caslat = caslat - 2;
			}
		}
	} else if (max_data_rate >= 256) { /* it is DDR 266 */
		if (ddrc_clk <= 350 && ddrc_clk > 280) {
			/* DDRC clk at 280~350 */
			printf("DDR: DDR controller freq is more than "
				"max data rate of the module\n");
			return 0;
		} else if (ddrc_clk <= 280 && ddrc_clk > 230) {
			/* DDRC clk at 230~280 */
			effective_data_rate = 266; /* 7.5ns */
			caslat = caslat;
		} else if (ddrc_clk <= 230 && ddrc_clk > 90) {
			/* DDRC clk at 90~230 */
			if (spd.clk_cycle2 == 0xa0) {
				effective_data_rate = 200; /* 10ns */
				caslat = caslat - 1;
			}
		}
	} else if (max_data_rate >= 190) { /* it is DDR 200 */
		if (ddrc_clk <= 350 && ddrc_clk > 230) {
			/* DDRC clk at 230~350 */
			printf("DDR: DDR controller freq is more than "
				"max data rate of the module\n");
			return 0;
		} else if (ddrc_clk <= 230 && ddrc_clk > 90) {
			/* DDRC clk at 90~230 */
			effective_data_rate = 200; /* 10ns */
			caslat = caslat;
		}
	}

#ifdef CONFIG_MPC834X
/* Errata DDR6
   This errata affects all MPC8349E, MPC8343E and MPC8347E processors.
*/
	if ((tmp1 >= 280) && (tmp1 < 350)) /* CSB=333 */
	{
		if (spd.mid[0] == 0x2c) {
			/* Micron memory running at 333 MHz */
			/* Chances are, U-Boot will crash before we get here,
			   but just in case, display a message and return error. */
			printf("Micron DDR not supported at 333MHz CSB\n");
			return 0;
		} else if (spd.mid[0] == 0xad) {
			printf("Hynix DDR does not require Errata DDR6\n");
		} else {
			/* enable 2 cycle Earlier for CL=2.5 or 3 */
			ddr->debug_reg = 0x202c0000;
			printf("Errata DDR6 (debug_reg=0x%x)\n", ddr->debug_reg);
		}
		caslat_83xx = caslat;
	}

	if ((tmp1 >= 230) && (tmp1 < 280)) {  /* CSB=266 */
		if (spd.mid[0] != 0x2c) /* non-Micron */
			caslat_83xx = caslat - 1;

	}

	if ((tmp1 >= 90) && (tmp1 < 230)) {  /* CSB=200 */
		caslat = 3;
		caslat_83xx = 2;
	}
#endif

	/*
	 * note: caslat must also be programmed into ddr->sdram_mode
	 * register.
	 *
	 * note: WRREC(Twr) and WRTORD(Twtr) are not in SPD,
	 * use conservative value here.
	 */
	caslat_ctrl = (caslat + 1) & 0x07; /* see as above */

	ddr->timing_cfg_1 =
	    (((picos_to_clk(spd.trp * 250) & 0x07) << 28 ) |
	     ((picos_to_clk(spd.tras * 1000) & 0x0f ) << 24 ) |
	     ((picos_to_clk(spd.trcd * 250) & 0x07) << 20 ) |
#ifdef CONFIG_MPC834x
	     ((caslat_83xx & 0x07) << 16 ) |
#else
	     ((caslat_ctrl & 0x07) << 16 ) |
#endif
	     (((picos_to_clk(spd.trfc * 1000) - 8) & 0x0f) << 12 ) |
	     ( 0x300 ) |
	     ((picos_to_clk(spd.trrd * 250) & 0x07) << 4) | 1);

	ddr->timing_cfg_2 = 0x00000800;

	debug("DDR:timing_cfg_1=0x%08x\n", ddr->timing_cfg_1);
	debug("DDR:timing_cfg_2=0x%08x\n", ddr->timing_cfg_2);
	/* Setup init value, but not enable */
	ddr->sdram_cfg = 0x42000000;

	/* Check DIMM data bus width */
	if (spd.dataw_lsb == 0x20)
	{
		burstlen = 0x03; /* 32 bit data bus, burst len is 8 */
		printf("\n   DDR DIMM: data bus width is 32 bit");
	}
	else
	{
		burstlen = 0x02; /* Others act as 64 bit bus, burst len is 4 */
		printf("\n   DDR DIMM: data bus width is 64 bit");
	}

	/* Is this an ECC DDR chip? */
	if (spd.config == 0x02) {
		printf(" with ECC\n");
	}
	else
		printf(" without ECC\n");

	/* Burst length is always 4 for 64 bit data bus, 8 for 32 bit data bus,
	   Burst type is sequential
	 */
	switch(caslat) {
	case 1:
		ddr->sdram_mode = 0x50 | burstlen; /* CL=1.5 */
		break;
	case 2:
		ddr->sdram_mode = 0x20 | burstlen; /* CL=2.0 */
		break;
	case 3:
		ddr->sdram_mode = 0x60 | burstlen; /* CL=2.5 */
		break;
	case 4:
		ddr->sdram_mode = 0x30 | burstlen; /* CL=3.0 */
		break;
	default:
		printf("DDR:only CAS Latency 1.5, 2.0, 2.5, 3.0 "
					"is supported.\n");
		return 0;
	}
	debug("DDR:sdram_mode=0x%08x\n", ddr->sdram_mode);

	switch(spd.refresh) {
	case 0x00:
	case 0x80:
		tmp = picos_to_clk(15625000);
		break;
	case 0x01:
	case 0x81:
		tmp = picos_to_clk(3900000);
		break;
	case 0x02:
	case 0x82:
		tmp = picos_to_clk(7800000);
		break;
	case 0x03:
	case 0x83:
		tmp = picos_to_clk(31300000);
		break;
	case 0x04:
	case 0x84:
		tmp = picos_to_clk(62500000);
		break;
	case 0x05:
	case 0x85:
		tmp = picos_to_clk(125000000);
		break;
	default:
		tmp = 0x512;
		break;
	}

	/*
	 * Set BSTOPRE to 0x100 for page mode
	 * If auto-charge is used, set BSTOPRE = 0
	 */
	ddr->sdram_interval = ((tmp & 0x3fff) << 16) | 0x100;
	debug("DDR:sdram_interval=0x%08x\n", ddr->sdram_interval);

	/* SS_EN = 0, source synchronous disable
	 * CLK_ADJST = 0, MCK/MCK# is launched aligned with addr/cmd
         */
	ddr->sdram_clk_cntl = 0x00000000;
	debug("DDR:sdram_clk_cntl=0x%08x\n", ddr->sdram_clk_cntl);

	asm("sync;isync");

	udelay(600);

	/*
	 * Figure out the settings for the sdram_cfg register.  Build up
	 * the entire register in 'tmp' before writing since the write into
	 * the register will actually enable the memory controller, and all
	 * settings must be done before enabling.
	 *
	 * sdram_cfg[0]   = 1 (ddr sdram logic enable)
	 * sdram_cfg[1]   = 1 (self-refresh-enable)
	 * sdram_cfg[6:7] = 2 (SDRAM type = DDR SDRAM)
	 * sdram_cfg[12] = 0 (32_BE =0 , 64 bit bus mode)
	 * sdram_cfg[13] = 0 (8_BE =0, 4-beat bursts)
	 */
	sdram_cfg = 0xC2000000;

	/* sdram_cfg[3] = RD_EN - registered DIMM enable */
	if (spd.mod_attr & 0x02) {
		sdram_cfg |= 0x10000000;
	}

	/* The DIMM is 32bit width */
	if (spd.dataw_lsb == 0x20) {
		sdram_cfg |= 0x000C0000;
	}
	ddrc_ecc_enable = 0;

#if defined(CONFIG_DDR_ECC)
	/* Enable ECC with sdram_cfg[2] */
	if (spd.config == 0x02) {
		sdram_cfg |= 0x20000000;
		ddrc_ecc_enable = 1;
		/* disable error detection */
		ddr->err_disable = ~ECC_ERROR_ENABLE;
		/* set single bit error threshold to maximum value,
		 * reset counter to zero */
		ddr->err_sbe = (255 << ECC_ERROR_MAN_SBET_SHIFT) |
			(0 << ECC_ERROR_MAN_SBEC_SHIFT);
	}

	debug("DDR:err_disable=0x%08x\n", ddr->err_disable);
	debug("DDR:err_sbe=0x%08x\n", ddr->err_sbe);
#endif
	printf("   DDRC ECC mode: %s", ddrc_ecc_enable ? "ON":"OFF");

#if defined(CONFIG_DDR_2T_TIMING)
	/*
	 * Enable 2T timing by setting sdram_cfg[16].
	 */
	sdram_cfg |= SDRAM_CFG_2T_EN;
#endif
	/* Enable controller, and GO! */
	ddr->sdram_cfg = sdram_cfg;
	asm("sync;isync");
	udelay(500);

	debug("DDR:sdram_cfg=0x%08x\n", ddr->sdram_cfg);
	return memsize; /*in MBytes*/
}
#endif /* CONFIG_SPD_EEPROM */


#if defined(CONFIG_DDR_ECC) && !defined(CONFIG_ECC_INIT_VIA_DDRC)
/*
 * Use timebase counter, get_timer() is not availabe
 * at this point of initialization yet.
 */
static __inline__ unsigned long get_tbms (void)
{
	unsigned long tbl;
	unsigned long tbu1, tbu2;
	unsigned long ms;
	unsigned long long tmp;

	ulong tbclk = get_tbclk();

	/* get the timebase ticks */
	do {
		asm volatile ("mftbu %0":"=r" (tbu1):);
		asm volatile ("mftb %0":"=r" (tbl):);
		asm volatile ("mftbu %0":"=r" (tbu2):);
	} while (tbu1 != tbu2);

	/* convert ticks to ms */
	tmp = (unsigned long long)(tbu1);
	tmp = (tmp << 32);
	tmp += (unsigned long long)(tbl);
	ms = tmp/(tbclk/1000);

	return ms;
}

/*
 * Initialize all of memory for ECC, then enable errors.
 */
/* #define CONFIG_DDR_ECC_INIT_VIA_DMA */
void ddr_enable_ecc(unsigned int dram_size)
{
	uint *p;
	volatile immap_t *immap = (immap_t *)CFG_IMMRBAR;
	volatile ddr83xx_t *ddr= &immap->ddr;
	unsigned long t_start, t_end;
#if defined(CONFIG_DDR_ECC_INIT_VIA_DMA)
	uint i;
#endif

	debug("Initialize a Cachline in DRAM\n");
	icache_enable();

#if defined(CONFIG_DDR_ECC_INIT_VIA_DMA)
	/* Initialise DMA for direct Transfers */
	dma_init();
#endif

	t_start = get_tbms();

#if !defined(CONFIG_DDR_ECC_INIT_VIA_DMA)
	debug("DDR init: Cache flush method\n");
	for (p = 0; p < (uint *)(dram_size); p++) {
		if (((unsigned int)p & 0x1f) == 0) {
			ppcDcbz((unsigned long) p);
		}

		/* write pattern to cache and flush */
		*p = (unsigned int)0xdeadbeef;

		if (((unsigned int)p & 0x1c) == 0x1c) {
			ppcDcbf((unsigned long) p);
		}
	}
#else
	printf("DDR init: DMA method\n");
	for (p = 0; p < (uint *)(8 * 1024); p++) {
		/* zero one data cache line */
		if (((unsigned int)p & 0x1f) == 0) {
			ppcDcbz((unsigned long)p);
		}

		/* write pattern to it and flush */
		*p = (unsigned int)0xdeadbeef;

		if (((unsigned int)p & 0x1c) == 0x1c) {
			ppcDcbf((unsigned long)p);
		}
	}

	/* 8K */
	dma_xfer((uint *)0x2000, 0x2000, (uint *)0);
	/* 16K */
	dma_xfer((uint *)0x4000, 0x4000, (uint *)0);
	/* 32K */
	dma_xfer((uint *)0x8000, 0x8000, (uint *)0);
	/* 64K */
	dma_xfer((uint *)0x10000, 0x10000, (uint *)0);
	/* 128k */
	dma_xfer((uint *)0x20000, 0x20000, (uint *)0);
	/* 256k */
	dma_xfer((uint *)0x40000, 0x40000, (uint *)0);
	/* 512k */
	dma_xfer((uint *)0x80000, 0x80000, (uint *)0);
	/* 1M */
	dma_xfer((uint *)0x100000, 0x100000, (uint *)0);
	/* 2M */
	dma_xfer((uint *)0x200000, 0x200000, (uint *)0);
	/* 4M */
	dma_xfer((uint *)0x400000, 0x400000, (uint *)0);

	for (i = 1; i < dram_size / 0x800000; i++) {
		dma_xfer((uint *)(0x800000*i), 0x800000, (uint *)0);
	}
#endif

	t_end = get_tbms();
	icache_disable();

	debug("\nREADY!!\n");
	debug("ddr init duration: %ld ms\n", t_end - t_start);

	/* Clear All ECC Errors */
	if ((ddr->err_detect & ECC_ERROR_DETECT_MME) == ECC_ERROR_DETECT_MME)
		ddr->err_detect |= ECC_ERROR_DETECT_MME;
	if ((ddr->err_detect & ECC_ERROR_DETECT_MBE) == ECC_ERROR_DETECT_MBE)
		ddr->err_detect |= ECC_ERROR_DETECT_MBE;
	if ((ddr->err_detect & ECC_ERROR_DETECT_SBE) == ECC_ERROR_DETECT_SBE)
		ddr->err_detect |= ECC_ERROR_DETECT_SBE;
	if ((ddr->err_detect & ECC_ERROR_DETECT_MSE) == ECC_ERROR_DETECT_MSE)
		ddr->err_detect |= ECC_ERROR_DETECT_MSE;

	/* Disable ECC-Interrupts */
	ddr->err_int_en &= ECC_ERR_INT_DISABLE;

	/* Enable errors for ECC */
	ddr->err_disable &= ECC_ERROR_ENABLE;

	__asm__ __volatile__ ("sync");
	__asm__ __volatile__ ("isync");
}
#endif	/* CONFIG_DDR_ECC */
