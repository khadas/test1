/*
 * U-boot - main board file
 *
 * Copyright (c) 2005-2009 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <config.h>
#include <command.h>
#include <netdev.h>
#include <net.h>
#include <asm/blackfin.h>

DECLARE_GLOBAL_DATA_PTR;

int checkboard(void)
{
	printf("Board: Surveyor SRV1 board\n");
	printf("       Support: http://www.surveyor.com/\n");
	return 0;
}

#ifdef CONFIG_BFIN_MAC
static void board_init_enetaddr(uchar *mac_addr)
{
	puts("Warning: Generating 'random' MAC address\n");
	net_random_ethaddr(mac_addr);
	eth_setenv_enetaddr("ethaddr", mac_addr);
}

int board_eth_init(bd_t *bis)
{
	return bfin_EMAC_initialize(bis);
}
#endif

int misc_init_r(void)
{
#ifdef CONFIG_BFIN_MAC
	uchar enetaddr[6];
	if (!eth_getenv_enetaddr("ethaddr", enetaddr))
		board_init_enetaddr(enetaddr);
#endif

	return 0;
}
