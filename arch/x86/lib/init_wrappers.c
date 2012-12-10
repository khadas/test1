/*
 * (C) Copyright 2011
 * Graeme Russ, <graeme.russ@gmail.com>
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
#include <environment.h>
#include <serial.h>
#include <kgdb.h>
#include <scsi.h>
#include <post.h>
#include <miiphy.h>

#include <asm/init_wrappers.h>

int serial_initialize_r(void)
{
	serial_initialize();

	return 0;
}

/*
 * Tell if it's OK to load the environment early in boot.
 *
 * If CONFIG_OF_CONFIG is defined, we'll check with the FDT to see
 * if this is OK (defaulting to saying it's not OK).
 *
 * NOTE: Loading the environment early can be a bad idea if security is
 *       important, since no verification is done on the environment.
 *
 * @return 0 if environment should not be loaded, !=0 if it is ok to load
 */
static int should_load_env(void)
{
#ifdef CONFIG_OF_CONTROL
	return fdtdec_get_config_int(gd->fdt_blob, "load-environment", 0);
#elif defined CONFIG_DELAY_ENVIRONMENT
	return 0;
#else
	return 1;
#endif
}

int env_relocate_r(void)
{
	/* initialize environment */
	if (should_load_env())
		env_relocate();
	else
		set_default_env(NULL);

	return 0;
}


int pci_init_r(void)
{
	/* Do pci configuration */
	pci_init();

	return 0;
}

int jumptable_init_r(void)
{
	jumptable_init();

	return 0;
}

int pcmcia_init_r(void)
{
	puts("PCMCIA:");
	pcmcia_init();

	return 0;
}

int kgdb_init_r(void)
{
	puts("KGDB:  ");
	kgdb_init();

	return 0;
}

int enable_interrupts_r(void)
{
	/* enable exceptions */
	enable_interrupts();

	return 0;
}

int eth_initialize_r(void)
{
	puts("Net:   ");
	eth_initialize(gd->bd);

	return 0;
}

int reset_phy_r(void)
{
#ifdef DEBUG
	puts("Reset Ethernet PHY\n");
#endif
	reset_phy();

	return 0;
}

int ide_init_r(void)
{
	puts("IDE:   ");
	ide_init();

	return 0;
}

int scsi_init_r(void)
{
	puts("SCSI:  ");
	scsi_init();

	return 0;
}

#ifdef CONFIG_BITBANGMII
int bb_miiphy_init_r(void)
{
	bb_miiphy_init();

	return 0;
}
#endif

#ifdef CONFIG_POST
int post_run_r(void)
{
	post_run(NULL, POST_RAM | post_bootmode_get(0));

	return 0;
}
#endif
