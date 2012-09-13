/*
 * (C) Copyright 2002
 * Peter De Schrijver (p2@mind.be), Mind Linux Solutions, NV.
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
 */

#include <common.h>
#include <asm/u-boot.h>
#include <asm/processor.h>
#include <command.h>
#include <config.h>
#include <serial.h>
#include <linux/compiler.h>

#include <ns16550.h>

DECLARE_GLOBAL_DATA_PTR;

const NS16550_t COM_PORTS[] =
	{ (NS16550_t) CONFIG_SYS_NS16550_COM1, (NS16550_t) CONFIG_SYS_NS16550_COM2 };

#undef CONFIG_SYS_DUART_CHAN
#define CONFIG_SYS_DUART_CHAN gComPort
static int gComPort = 0;

static int amirix_serial_init(void)
{
	int clock_divisor = CONFIG_SYS_NS16550_CLK / 16 / gd->baudrate;

	(void) NS16550_init (COM_PORTS[0], clock_divisor);
	gComPort = 0;

	return 0;
}

static void amirix_serial_putc(const char c)
{
	if (c == '\n') {
		NS16550_putc (COM_PORTS[CONFIG_SYS_DUART_CHAN], '\r');
	}

	NS16550_putc (COM_PORTS[CONFIG_SYS_DUART_CHAN], c);
}

static int amirix_serial_getc(void)
{
	return NS16550_getc (COM_PORTS[CONFIG_SYS_DUART_CHAN]);
}

static int amirix_serial_tstc(void)
{
	return NS16550_tstc (COM_PORTS[CONFIG_SYS_DUART_CHAN]);
}

static void amirix_serial_setbrg(void)
{
	int clock_divisor = CONFIG_SYS_NS16550_CLK / 16 / gd->baudrate;

#ifdef CONFIG_SYS_INIT_CHAN1
	NS16550_reinit (COM_PORTS[0], clock_divisor);
#endif
#ifdef CONFIG_SYS_INIT_CHAN2
	NS16550_reinit (COM_PORTS[1], clock_divisor);
#endif
}

static void amirix_serial_puts(const char *s)
{
	while (*s) {
		serial_putc (*s++);
	}
}

#ifdef CONFIG_SERIAL_MULTI
static struct serial_device amirix_serial_drv = {
	.name	= "amirix_serial",
	.start	= amirix_serial_init,
	.stop	= NULL,
	.setbrg	= amirix_serial_setbrg,
	.putc	= amirix_serial_putc,
	.puts	= amirix_serial_puts,
	.getc	= amirix_serial_getc,
	.tstc	= amirix_serial_tstc,
};

void amirix_serial_initialize(void)
{
	serial_register(&amirix_serial_drv);
}

__weak struct serial_device *default_serial_console(void)
{
	return &amirix_serial_drv;
}
#else
int serial_init(void)
{
	return amirix_serial_init();
}

void serial_setbrg(void)
{
	amirix_serial_setbrg();
}

void serial_putc(const char c)
{
	amirix_serial_putc(c);
}

void serial_puts(const char *s)
{
	amirix_serial_puts(s);
}

int serial_getc(void)
{
	return amirix_serial_getc();
}

int serial_tstc(void)
{
	return amirix_serial_tstc();
}
#endif
#if defined(CONFIG_CMD_KGDB)
void kgdb_serial_init (void)
{
}

void putDebugChar (int c)
{
	serial_putc (c);
}

void putDebugStr (const char *str)
{
	serial_puts (str);
}

int getDebugChar (void)
{
	return serial_getc ();
}

void kgdb_interruptible (int yes)
{
	return;
}
#endif
