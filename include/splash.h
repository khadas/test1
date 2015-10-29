/*
 * Copyright (C) 2013, Boundary Devices <info@boundarydevices.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., http://www.fsf.org/about/contact/
 */

#ifndef _SPLASH_H_
#define _SPLASH_H_

#include <errno.h>

enum splash_storage {
	SPLASH_STORAGE_NAND,
	SPLASH_STORAGE_SF,
	SPLASH_STORAGE_MMC,
};

enum splash_flags {
	SPLASH_STORAGE_RAW,
	SPLASH_STORAGE_FS,
};

struct splash_location {
	char *name;
	enum splash_storage storage;
	enum splash_flags flags;
	u32 offset;	/* offset from start of storage */
	char *devpart;  /* Use the load command dev:part conventions */
};

int splash_source_load(struct splash_location *locations, uint size);
int splash_screen_prepare(void);

#ifdef CONFIG_SPLASH_SCREEN_ALIGN
void splash_get_pos(int *x, int *y);
#else
static inline void splash_get_pos(int *x, int *y) { }
#endif

#if defined(CONFIG_SPLASH_SCREEN) && defined(CONFIG_LCD)
int lcd_splash(ulong addr);
#else
static inline int lcd_splash(ulong addr)
{
	return -ENOSYS;
}
#endif

#define BMP_ALIGN_CENTER	0x7FFF

#endif
