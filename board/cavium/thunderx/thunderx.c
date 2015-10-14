/**
 * (C) Copyright 2014, Cavium Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
**/

#include <common.h>
#include <malloc.h>
#include <errno.h>
#include <linux/compiler.h>

#if !CONFIG_IS_ENABLED(OF_CONTROL)
#include <dm/platdata.h>
#include <dm/platform_data/serial_pl01x.h>

static const struct pl01x_serial_platdata serial0 = {
	.base = CONFIG_SYS_SERIAL0,
	.type = TYPE_PL011,
	.clock = 0,
	.skip_init = true,
};

U_BOOT_DEVICE(thunderx_serial0) = {
	.name = "serial_pl01x",
	.platdata = &serial0,
};

static const struct pl01x_serial_platdata serial1 = {
	.base = CONFIG_SYS_SERIAL1,
	.type = TYPE_PL011,
	.clock = 0,
	.skip_init = true,
};

U_BOOT_DEVICE(thunderx_serial1) = {
	.name = "serial_pl01x",
	.platdata = &serial1,
};
#endif

DECLARE_GLOBAL_DATA_PTR;

int board_init(void)
{
	return 0;
}

int timer_init(void)
{
	return 0;
}

/*
 * Board specific reset that is system reset.
 */
void reset_cpu(ulong addr)
{
}

/*
 * Board specific ethernet initialization routine.
 */
int board_eth_init(bd_t *bis)
{
	int rc = 0;

	return rc;
}

#ifdef CONFIG_PCI
void pci_init_board(void)
{
	printf("DEBUG: PCI Init TODO *****\n");
}
#endif
