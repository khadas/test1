/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2016, Bin Meng <bmeng.cn@gmail.com>
 */

/* Power Button */
Device (PWRB)
{
	Name(_HID, EISAID("PNP0C0C"))
}

/* TODO: Need add Winbond SuperIO chipset W83627 ASL codes */
