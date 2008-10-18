/*
 * (C) Copyright 2007
 * Nobobuhiro Iwamatsu <iwamatsu@nigauri.org>
 *
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
#include <asm/processor.h>

#define TMU_MAX_COUNTER (~0UL)

static void tmu_timer_start (unsigned int timer)
{
	if (timer > 2)
		return;

	*((volatile unsigned char *) TSTR) |= (1 << timer);
}

static void tmu_timer_stop (unsigned int timer)
{
	u8 val = *((volatile u8 *)TSTR);
	if (timer > 2)
		return;
	*((volatile unsigned char *)TSTR) = val &~(1 << timer);
}

int timer_init (void)
{
	/* Divide clock by 4 */
	*(volatile u16 *)TCR0 = 0;

	tmu_timer_stop(0);
	tmu_timer_start(0);
	return 0;
}

/*
   In theory we should return a true 64bit value (ie something that doesn't
   overflow). However, we don't. Therefore if TMU runs at fastest rate of
   6.75 MHz this value will wrap after u-boot has been running for approx
   10 minutes.
*/
unsigned long long get_ticks (void)
{
	return (0 - *((volatile u32 *) TCNT0));
}

unsigned long get_timer (unsigned long base)
{
	return ((0 - *((volatile u32 *) TCNT0)) - base);
}

void set_timer (unsigned long t)
{
	*((volatile unsigned int *) TCNT0) = (0 - t);
}

void reset_timer (void)
{
	tmu_timer_stop(0);
	set_timer (0);
	tmu_timer_start(0);
}

void udelay (unsigned long usec)
{
	unsigned int start = get_timer (0);
	unsigned int end = start + (usec * ((CONFIG_SYS_HZ + 500000) / 1000000));

	while (get_timer (0) < end)
		continue;
}

unsigned long get_tbclk (void)
{
	return CONFIG_SYS_HZ;
}
