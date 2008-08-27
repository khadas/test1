/*
 *
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * Copyright (C) 2004-2007 Freescale Semiconductor, Inc.
 * TsiChung Liew (Tsi-Chung.Liew@freescale.com)
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

#include <asm/immap.h>

DECLARE_GLOBAL_DATA_PTR;

int do_reset(cmd_tbl_t * cmdtp, bd_t * bd, int flag, int argc, char *argv[])
{
	volatile rcm_t *rcm = (rcm_t *) (MMAP_RCM);
	udelay(1000);
	rcm->rcr |= RCM_RCR_SOFTRST;

	/* we don't return! */
	return 0;
};

int checkcpu(void)
{
	volatile ccm_t *ccm = (ccm_t *) MMAP_CCM;
	u16 msk;
	u16 id = 0;
	u8 ver;

	puts("CPU:   ");
	msk = (ccm->cir >> 6);
	ver = (ccm->cir & 0x003f);
	switch (msk) {
	case 0x48:
		id = 54455;
		break;
	case 0x49:
		id = 54454;
		break;
	case 0x4a:
		id = 54453;
		break;
	case 0x4b:
		id = 54452;
		break;
	case 0x4d:
		id = 54451;
		break;
	case 0x4f:
		id = 54450;
		break;
	}

	if (id) {
		printf("Freescale MCF%d (Mask:%01x Version:%x)\n", id, msk,
		       ver);
		printf("       CPU CLK %d Mhz BUS CLK %d Mhz FLB CLK %d Mhz\n",
		       (int)(gd->cpu_clk / 1000000),
		       (int)(gd->bus_clk / 1000000),
		       (int)(gd->flb_clk / 1000000));
#ifdef CONFIG_PCI
		printf("       PCI CLK %d Mhz INP CLK %d Mhz VCO CLK %d Mhz\n",
		       (int)(gd->pci_clk / 1000000),
		       (int)(gd->inp_clk / 1000000),
		       (int)(gd->vco_clk / 1000000));
#else
		printf("       INP CLK %d Mhz VCO CLK %d Mhz\n",
		       (int)(gd->inp_clk / 1000000),
		       (int)(gd->vco_clk / 1000000));
#endif
	}

	return 0;
}

#if defined(CONFIG_MCFFEC)
/* Default initializations for MCFFEC controllers.  To override,
 * create a board-specific function called:
 * 	int board_eth_init(bd_t *bis)
 */

extern int mcffec_initialize(bd_t*);

int cpu_eth_init(bd_t *bis)
{
	return mcffec_initialize(bis);
}
#endif
