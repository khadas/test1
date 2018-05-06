// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) STMicroelectronics SA 2017
 * Author(s): Patrice CHOTARD, <patrice.chotard@st.com> for STMicroelectronics.
 */

#include <common.h>
#include <dm.h>

#include <asm/io.h>
#include <asm/arch/stm32.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
	int rv;
	struct udevice *dev;

	rv = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (rv) {
		debug("DRAM init failed: %d\n", rv);
		return rv;
	}

	if (fdtdec_setup_memory_size() != 0)
		rv = -EINVAL;

	return rv;
}

int dram_init_banksize(void)
{
	fdtdec_setup_memory_banksize();

	return 0;
}

u32 get_board_rev(void)
{
	return 0;
}

int board_early_init_f(void)
{
	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

	return 0;
}

#ifdef CONFIG_MISC_INIT_R
int misc_init_r(void)
{
	char serialno[25];
	u32 u_id_low, u_id_mid, u_id_high;

	if (!env_get("serial#")) {
		u_id_low  = readl(&STM32_U_ID->u_id_low);
		u_id_mid  = readl(&STM32_U_ID->u_id_mid);
		u_id_high = readl(&STM32_U_ID->u_id_high);
		sprintf(serialno, "%08x%08x%08x",
			u_id_high, u_id_mid, u_id_low);
		env_set("serial#", serialno);
	}

	return 0;
}
#endif
