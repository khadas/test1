/*
 * (C) Copyright 2017 Theobroma Systems Design und Consulting GmbH
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <ram.h>
#include <spl.h>
#include <asm/io.h>
#include <asm/arch/cru_rk3368.h>
#include <asm/arch/grf_rk3368.h>
#include <asm/arch/hardware.h>
#include <asm/arch/periph.h>
#include <asm/arch/timer.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * The ARMv8 generic timer uses the STIMER1 as its clock-source.
 * Set up the STIMER1 to free-running (i.e. auto-reload) to start
 * the generic timer counting (if we don't do this, udelay will not
 * work and block indefinitively).
 */
static void secure_timer_init(void)
{
	struct rk_timer * const stimer1 =
		(struct rk_timer * const)0xff830020;
	const u32 TIMER_EN = BIT(0);

	writel(~0u, &stimer1->timer_load_count0);
	writel(~0u, &stimer1->timer_load_count1);
	writel(TIMER_EN, &stimer1->timer_ctrl_reg);
}

void board_debug_uart_init(void)
{
}

void board_init_f(ulong dummy)
{
	struct udevice *pinctrl;
	struct udevice *dev;
	int ret;

	ret = spl_early_init();
	if (ret) {
		debug("spl_early_init() failed: %d\n", ret);
		hang();
	}

	/* Make sure the ARMv8 generic timer counts */
	secure_timer_init();

	/* Set up our preloader console */
	ret = uclass_get_device(UCLASS_PINCTRL, 0, &pinctrl);
	if (ret) {
		error("%s: pinctrl init failed: %d\n", __func__, ret);
		hang();
	}

	ret = pinctrl_request_noflags(pinctrl, PERIPH_ID_UART0);
	if (ret) {
		error("%s: failed to set up console UART\n", __func__);
		hang();
	}

	preloader_console_init();

	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret) {
		debug("DRAM init failed: %d\n", ret);
		return;
	}
}

u32 spl_boot_mode(const u32 boot_device)
{
	return MMCSD_MODE_RAW;
}

u32 spl_boot_device(void)
{
	return BOOT_DEVICE_MMC1;
}

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	/* Just empty function now - can't decide what to choose */
	debug("%s: %s\n", __func__, name);

	return 0;
}
#endif
