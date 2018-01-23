/*
 * Wait for bit with timeout and ctrlc
 *
 * (C) Copyright 2015 Mateusz Kulikowski <mateusz.kulikowski@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __WAIT_BIT_H
#define __WAIT_BIT_H

#include <common.h>
#include <console.h>
#include <watchdog.h>
#include <linux/errno.h>
#include <asm/io.h>

/**
 * wait_for_bit()	waits for bit set/cleared in register
 *
 * Function polls register waiting for specific bit(s) change
 * (either 0->1 or 1->0). It can fail under two conditions:
 * - Timeout
 * - User interaction (CTRL-C)
 * Function succeeds only if all bits of masked register are set/cleared
 * (depending on set option).
 *
 * @param prefix	Prefix added to timeout messagge (message visible only
 *			with debug enabled)
 * @param reg		Register that will be read (using readl())
 * @param mask		Bit(s) of register that must be active
 * @param set		Selects wait condition (bit set or clear)
 * @param timeout_ms	Timeout (in miliseconds)
 * @param breakable	Enables CTRL-C interruption
 * @return		0 on success, -ETIMEDOUT or -EINTR on failure
 */
static inline int wait_for_bit(const char *prefix, const u32 *reg,
			       const u32 mask, const bool set,
			       const unsigned int timeout_ms,
			       const bool breakable)
{
	u32 val;
	unsigned long start = get_timer(0);

	while (1) {
		val = readl(reg);

		if (!set)
			val = ~val;

		if ((val & mask) == mask)
			return 0;

		if (get_timer(start) > timeout_ms)
			break;

		if (breakable && ctrlc()) {
			puts("Abort\n");
			return -EINTR;
		}

		udelay(1);
		WATCHDOG_RESET();
	}

	debug("%s: Timeout (reg=%p mask=%08x wait_set=%i)\n", prefix, reg, mask,
	      set);

	return -ETIMEDOUT;
}

/**
 * wait_for_bit_x()	waits for bit set/cleared in register
 *
 * Function polls register waiting for specific bit(s) change
 * (either 0->1 or 1->0). It can fail under two conditions:
 * - Timeout
 * - User interaction (CTRL-C)
 * Function succeeds only if all bits of masked register are set/cleared
 * (depending on set option).
 *
 * @param reg		Register that will be read (using read_x())
 * @param mask		Bit(s) of register that must be active
 * @param set		Selects wait condition (bit set or clear)
 * @param timeout_ms	Timeout (in milliseconds)
 * @param breakable	Enables CTRL-C interruption
 * @return		0 on success, -ETIMEDOUT or -EINTR on failure
 */

#define BUILD_WAIT_FOR_BIT(sfx, type, read)				\
									\
static inline int wait_for_bit_##sfx(const void *reg,			\
				     const type mask,			\
				     const bool set,			\
				     const unsigned int timeout_ms,	\
				     const bool breakable)		\
{									\
	type val;							\
	unsigned long start = get_timer(0);				\
									\
	while (1) {							\
		val = read(reg);					\
									\
		if (!set)						\
			val = ~val;					\
									\
		if ((val & mask) == mask)				\
			return 0;					\
									\
		if (get_timer(start) > timeout_ms)			\
			break;						\
									\
		if (breakable && ctrlc()) {				\
			puts("Abort\n");				\
			return -EINTR;					\
		}							\
									\
		udelay(1);						\
		WATCHDOG_RESET();					\
	}								\
									\
	debug("%s: Timeout (reg=%p mask=%x wait_set=%i)\n", __func__,	\
	      reg, mask, set);						\
									\
	return -ETIMEDOUT;						\
}

BUILD_WAIT_FOR_BIT(8, u8, readb)
BUILD_WAIT_FOR_BIT(le16, u16, readw)
#ifdef readw_be
BUILD_WAIT_FOR_BIT(be16, u16, readw_be)
#endif
BUILD_WAIT_FOR_BIT(le32, u32, readl)
#ifdef readl_be
BUILD_WAIT_FOR_BIT(be32, u32, readl_be)
#endif

#endif
