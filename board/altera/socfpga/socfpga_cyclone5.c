/*
 *  Copyright (C) 2012 Altera Corporation <www.altera.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/arch/reset_manager.h>
#include <asm/io.h>

#include <usb.h>
#include <usb/s3c_udc.h>
#include <usb_mass_storage.h>

#include <netdev.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Print Board information
 */
int checkboard(void)
{
	puts("BOARD: Altera SoCFPGA Cyclone5 Board\n");
	return 0;
}

/*
 * Initialization function which happen at early stage of c code
 */
int board_early_init_f(void)
{
	return 0;
}

/*
 * Miscellaneous platform dependent initialisations
 */
int board_init(void)
{
	/* Address of boot parameters for ATAG (if ATAG is used) */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	return 0;
}

#ifdef CONFIG_USB_GADGET
struct s3c_plat_otg_data socfpga_otg_data = {
	.regs_otg	= CONFIG_USB_DWC2_REG_ADDR,
	.usb_gusbcfg	= 0x1417,
};

int board_usb_init(int index, enum usb_init_type init)
{
	return s3c_udc_probe(&socfpga_otg_data);
}

int g_dnl_board_usb_cable_connected(void)
{
	return 1;
}
#endif
