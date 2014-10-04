/*
 * (C) Copyright 2014
 * Chen-Yu Tsai <wens@csie.org>
 *
 * Watchdog register definitions
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _SUNXI_WATCHDOG_H_
#define _SUNXI_WATCHDOG_H_

#define WDT_CTRL_RESTART	(0x1 << 0)
#define WDT_CTRL_KEY		(0x0a57 << 1)
#define WDT_MODE_EN		(0x1 << 0)
#define WDT_MODE_RESET_EN	(0x1 << 1)

struct sunxi_wdog {
	u32 ctl;		/* 0x00 */
	u32 mode;		/* 0x04 */
	u32 res[2];
};

#endif /* _SUNXI_WATCHDOG_H_ */
