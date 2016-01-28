/*
 * (C) Copyright 2001-2015
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 * Joe Hershberger, National Instruments
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <miiphy.h>
#include <net.h>
#include "eth_internal.h"

void eth_parse_enetaddr(const char *addr, uchar *enetaddr)
{
	char *end;
	int i;

	for (i = 0; i < 6; ++i) {
		enetaddr[i] = addr ? simple_strtoul(addr, &end, 16) : 0;
		if (addr)
			addr = (*end) ? end + 1 : end;
	}
}

int eth_getenv_enetaddr(const char *name, uchar *enetaddr)
{
	eth_parse_enetaddr(getenv(name), enetaddr);
	return is_valid_ethaddr(enetaddr);
}

int eth_setenv_enetaddr(const char *name, const uchar *enetaddr)
{
	char buf[20];

	sprintf(buf, "%pM", enetaddr);

	return setenv(name, buf);
}

int eth_getenv_enetaddr_by_index(const char *base_name, int index,
				 uchar *enetaddr)
{
	char enetvar[32];
	sprintf(enetvar, index ? "%s%daddr" : "%saddr", base_name, index);
	return eth_getenv_enetaddr(enetvar, enetaddr);
}

int eth_setenv_enetaddr_by_index(const char *base_name, int index,
				 uchar *enetaddr)
{
	char enetvar[32];
	sprintf(enetvar, index ? "%s%daddr" : "%saddr", base_name, index);
	return eth_setenv_enetaddr(enetvar, enetaddr);
}

void eth_common_init(void)
{
	bootstage_mark(BOOTSTAGE_ID_NET_ETH_START);
#if defined(CONFIG_MII) || defined(CONFIG_CMD_MII) || defined(CONFIG_PHYLIB)
	miiphy_init();
#endif

#ifdef CONFIG_PHYLIB
	phy_init();
#endif
}

int eth_mac_skip(int index)
{
	char enetvar[15];
	char *skip_state;

	sprintf(enetvar, index ? "eth%dmacskip" : "ethmacskip", index);
	skip_state = getenv(enetvar);
	return skip_state != NULL;
}

void eth_current_changed(void)
{
	char *act = getenv("ethact");
	char *ethrotate;

	/*
	 * The call to eth_get_dev() below has a side effect of rotating
	 * ethernet device if uc_priv->current == NULL. This is not what
	 * we want when 'ethrotate' variable is 'no'.
	 */
	ethrotate = getenv("ethrotate");
	if ((ethrotate != NULL) && (strcmp(ethrotate, "no") == 0))
		return;

	/* update current ethernet name */
	if (eth_get_dev()) {
		if (act == NULL || strcmp(act, eth_get_name()) != 0)
			setenv("ethact", eth_get_name());
	}
	/*
	 * remove the variable completely if there is no active
	 * interface
	 */
	else if (act != NULL)
		setenv("ethact", NULL);
}

void eth_try_another(int first_restart)
{
	static void *first_failed;
	char *ethrotate;

	/*
	 * Do not rotate between network interfaces when
	 * 'ethrotate' variable is set to 'no'.
	 */
	ethrotate = getenv("ethrotate");
	if ((ethrotate != NULL) && (strcmp(ethrotate, "no") == 0))
		return;

	if (!eth_get_dev())
		return;

	if (first_restart)
		first_failed = eth_get_dev();

	eth_set_current_to_next();

	eth_current_changed();

	if (first_failed == eth_get_dev())
		net_restart_wrap = 1;
}

void eth_set_current(void)
{
	static char *act;
	static int  env_changed_id;
	int	env_id;

	env_id = get_env_id();
	if ((act == NULL) || (env_changed_id != env_id)) {
		act = getenv("ethact");
		env_changed_id = env_id;
	}

	if (act == NULL) {
		char *ethprime = getenv("ethprime");
		void *dev = NULL;

		if (ethprime)
			dev = eth_get_dev_by_name(ethprime);
		if (dev)
			eth_set_dev(dev);
		else
			eth_set_dev(NULL);
	} else {
		eth_set_dev(eth_get_dev_by_name(act));
	}

	eth_current_changed();
}

const char *eth_get_name(void)
{
	return eth_get_dev() ? eth_get_dev()->name : "unknown";
}
