/*
 * (C) Copyright 2013
 * Heiko Schocher, DENX Software Engineering, hs@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <environment.h>

void bootcount_store(ulong a)
{
	int upgrade_available = getenv_ulong("upgrade_available", 10, 0);

	if (upgrade_available) {
		env_set_ulong("bootcount", a);
		env_save();
	}
}

ulong bootcount_load(void)
{
	int upgrade_available = getenv_ulong("upgrade_available", 10, 0);
	ulong val = 0;

	if (upgrade_available)
		val = getenv_ulong("bootcount", 10, 0);

	return val;
}
