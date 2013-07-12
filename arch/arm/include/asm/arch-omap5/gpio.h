/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 * Tom Rix <Tom.Rix@windriver.com>
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
 *
 * This work is derived from the linux 2.6.27 kernel source
 * To fetch, use the kernel repository
 * git://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux-2.6.git
 * Use the v2.6.27 tag.
 *
 * Below is the original's header including its copyright
 *
 *  linux/arch/arm/plat-omap/gpio.c
 *
 * Support functions for OMAP GPIO
 *
 * Copyright (C) 2003-2005 Nokia Corporation
 * Written by Juha Yrjölä <juha.yrjola@nokia.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef _GPIO_OMAP5_H
#define _GPIO_OMAP5_H

#include <asm/omap_gpio.h>

#define OMAP_MAX_GPIO			256

#define OMAP54XX_GPIO1_BASE		0x4Ae10000
#define OMAP54XX_GPIO2_BASE		0x48055000
#define OMAP54XX_GPIO3_BASE		0x48057000
#define OMAP54XX_GPIO4_BASE		0x48059000
#define OMAP54XX_GPIO5_BASE		0x4805B000
#define OMAP54XX_GPIO6_BASE		0x4805D000
#define OMAP54XX_GPIO7_BASE		0x48051000
#define OMAP54XX_GPIO8_BASE		0x48053000

#endif /* _GPIO_OMAP5_H */
