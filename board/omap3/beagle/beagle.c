/*
 * (C) Copyright 2004-2008
 * Texas Instruments, <www.ti.com>
 *
 * Author :
 *	Sunil Kumar <sunilsaini05@gmail.com>
 *	Shashi Ranjan <shashiranjanmca05@gmail.com>
 *
 * Derived from Beagle Board and 3430 SDP code by
 *	Richard Woodruff <r-woodruff2@ti.com>
 *	Syed Mohammed Khasim <khasim@ti.com>
 *
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
#include <asm/io.h>
#include <asm/arch/mux.h>
#include <asm/arch/sys_proto.h>
#include <asm/mach-types.h>
#include "beagle.h"

static int beagle_revision_c;

/******************************************************************************
 * Routine: board_init
 * Description: Early hardware init.
 *****************************************************************************/
int board_init(void)
{
	DECLARE_GLOBAL_DATA_PTR;

	gpmc_init(); /* in SRAM or SDRAM, finish GPMC */
	/* board id for Linux */
	gd->bd->bi_arch_number = MACH_TYPE_OMAP3_BEAGLE;
	/* boot param addr */
	gd->bd->bi_boot_params = (OMAP34XX_SDRC_CS0 + 0x100);

	return 0;
}

/******************************************************************************
 * Routine: beagle_get_revision
 * Description: Return revision of the BeagleBoard this code is running on.
 *              If it is a revision Ax/Bx board, this function returns 0,
 *              on a revision C board you will get a 1.
 *****************************************************************************/
int beagle_get_revision(void)
{
	return beagle_revision_c;
}

/******************************************************************************
 * Routine: beagle_identify
 * Description: Detect if we are running on a Beagle revision Ax/Bx or
 *              Cx. This can be done by GPIO_171. If this is low, we are
 *              running on a revision C board.
 *****************************************************************************/
void beagle_identify(void)
{
	gpio_t *gpio6_base = (gpio_t *)OMAP34XX_GPIO6_BASE;

	/* Configure GPIO 171 as input */
	writel(readl(&gpio6_base->oe) | GPIO11, &gpio6_base->oe);

	/* Get value of GPIO 171 */
	beagle_revision_c = readl(&gpio6_base->datain) & BOARD_REVISION_MASK;

	printf("Board revision ");
	if (beagle_revision_c) {
		printf("Ax/Bx\n");
		beagle_revision_c = 0;
	} else {
		printf("C\n");
		beagle_revision_c = 1;
	}
}

/******************************************************************************
 * Routine: misc_init_r
 * Description: Configure board specific parts
 *****************************************************************************/
int misc_init_r(void)
{
	gpio_t *gpio5_base = (gpio_t *)OMAP34XX_GPIO5_BASE;
	gpio_t *gpio6_base = (gpio_t *)OMAP34XX_GPIO6_BASE;

	power_init_r();

	/* Configure GPIOs to output */
	writel(~(GPIO23 | GPIO10 | GPIO8 | GPIO2 | GPIO1), &gpio6_base->oe);
	writel(~(GPIO31 | GPIO30 | GPIO29 | GPIO28 | GPIO22 | GPIO21 |
		GPIO15 | GPIO14 | GPIO13 | GPIO12), &gpio5_base->oe);

	/* Set GPIOs */
	writel(GPIO23 | GPIO10 | GPIO8 | GPIO2 | GPIO1,
		&gpio6_base->setdataout);
	writel(GPIO31 | GPIO30 | GPIO29 | GPIO28 | GPIO22 | GPIO21 |
		GPIO15 | GPIO14 | GPIO13 | GPIO12, &gpio5_base->setdataout);

	beagle_identify();

	dieid_num_r();

	return 0;
}

/******************************************************************************
 * Routine: set_muxconf_regs
 * Description: Setting up the configuration Mux registers specific to the
 *		hardware. Many pins need to be moved from protect to primary
 *		mode.
 *****************************************************************************/
void set_muxconf_regs(void)
{
	MUX_BEAGLE();
}
