/*
 * Copyright (C) 2011 Michal Simek <monstr@monstr.eu>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_MICROBLAZE_PROCESSOR_H
#define __ASM_MICROBLAZE_PROCESSOR_H

/* References to section boundaries */

extern char __end[];
extern char __text_start[];

/* Microblaze board initialization function */
void board_init(void);

/* Watchdog functions */
extern int hw_watchdog_init(void);
extern void hw_watchdog_disable(void);

#endif /* __ASM_MICROBLAZE_PROCESSOR_H */
