/*
 * (C) Copyright 2004 Atmark Techno, Inc.
 *
 * Yasushi SHOJI <yashi@atmark-techno.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>

void flush_cache (ulong addr, ulong size)
{
	int i;
	for (i = 0; i < size; i += 4)
		asm volatile (
#ifdef CONFIG_ICACHE
				"wic	%0, r0;"
#endif
				"nop;"
#ifdef CONFIG_DCACHE
				"wdc.flush	%0, r0;"
#endif
				"nop;"
				:
				: "r" (addr + i)
				: "memory");
}
