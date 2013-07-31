/*
 * Copyright 2008 Freescale Semiconductor, Inc.
 *
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/fsl_law.h>
#include <asm/mmu.h>

/*
 * LAW(Local Access Window) configuration:
 *
 * 0x0000_0000     0x7fff_ffff     DDR                     2G
 * 0x8000_0000     0x9fff_ffff     PCI1 MEM                512M
 * 0xc000_0000     0xdfff_ffff     RapidIO                 512M
 * 0xe000_0000     0xe000_ffff     CCSR                    1M
 * 0xe200_0000     0xe2ff_ffff     PCI1 IO                 16M
 * 0xf000_0000     0xf7ff_ffff     SDRAM                   128M
 * 0xf800_0000     0xf80f_ffff     BCSR                    1M
 * 0xff00_0000     0xffff_ffff     FLASH (boot bank)       16M
 *
 * Notes:
 *    CCSRBAR and L2-as-SRAM don't need a configured Local Access Window.
 *    If flash is 8M at default position (last 8M), no LAW needed.
 */

struct law_entry law_table[] = {
#ifndef CONFIG_SPD_EEPROM
	SET_LAW(CONFIG_SYS_DDR_SDRAM_BASE, LAW_SIZE_128M, LAW_TRGT_IF_DDR),
#endif
	SET_LAW(CONFIG_SYS_PCI1_MEM_PHYS, LAW_SIZE_512M, LAW_TRGT_IF_PCI),
	/* This is not so much the SDRAM map as it is the whole localbus map. */
	SET_LAW(CONFIG_SYS_LBC_SDRAM_BASE, LAW_SIZE_256M, LAW_TRGT_IF_LBC),
	SET_LAW(CONFIG_SYS_PCI1_IO_PHYS, LAW_SIZE_1M, LAW_TRGT_IF_PCI),
	SET_LAW(CONFIG_SYS_RIO_MEM_PHYS, LAW_SIZE_512M, LAW_TRGT_IF_RIO),
};

int num_law_entries = ARRAY_SIZE(law_table);
