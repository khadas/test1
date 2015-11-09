/*
 * (C) Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONSOLE_H
#define __CONSOLE_H

extern char console_buffer[];

/* common/console.c */
int console_init_f(void);	/* Before relocation; uses the serial  stuff */
int console_init_r(void);	/* After  relocation; uses the console stuff */
int console_assign(int file, const char *devname);	/* Assign the console */
int ctrlc(void);
int had_ctrlc(void);	/* have we had a Control-C since last clear? */
void clear_ctrlc(void);	/* clear the Control-C condition */
int disable_ctrlc(int);	/* 1 to disable, 0 to enable Control-C detect */
int confirm_yesno(void);        /*  1 if input is "y", "Y", "yes" or "YES" */

/*
 * CONSOLE multiplexing.
 */
#ifdef CONFIG_CONSOLE_MUX
#include <iomux.h>
#endif

#endif
