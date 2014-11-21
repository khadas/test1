/*
 * Copyright (c) 2014 The Chromium OS Authors.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <environment.h>
#include <errno.h>
#include <fdtdec.h>
#include <os.h>
#include <serial.h>
#include <stdio_dev.h>
#include <watchdog.h>
#include <dm/lists.h>
#include <dm/device-internal.h>

#include <ns16550.h>

DECLARE_GLOBAL_DATA_PTR;

/*
 * Table with supported baudrates (defined in config_xyz.h)
 */
static const unsigned long baudrate_table[] = CONFIG_SYS_BAUDRATE_TABLE;

#ifndef CONFIG_SYS_MALLOC_F_LEN
#error "Serial is required before relocation - define CONFIG_SYS_MALLOC_F_LEN to make this work"
#endif

static void serial_find_console_or_panic(void)
{
	struct udevice *dev;

#ifdef CONFIG_OF_CONTROL
	int node;

	/* Check for a chosen console */
	node = fdtdec_get_chosen_node(gd->fdt_blob, "stdout-path");
	if (node < 0)
		node = fdt_path_offset(gd->fdt_blob, "console");
	if (!uclass_get_device_by_of_offset(UCLASS_SERIAL, node, &dev)) {
		gd->cur_serial_dev = dev;
		return;
	}

	/*
	 * If the console is not marked to be bound before relocation, bind
	 * it anyway.
	 */
	if (node > 0 &&
	    !lists_bind_fdt(gd->dm_root, gd->fdt_blob, node, &dev)) {
		if (!device_probe(dev)) {
			gd->cur_serial_dev = dev;
			return;
		}
	}
#endif
	/*
	 * Try to use CONFIG_CONS_INDEX if available (it is numbered from 1!).
	 *
	 * Failing that, get the device with sequence number 0, or in extremis
	 * just the first serial device we can find. But we insist on having
	 * a console (even if it is silent).
	 */
#ifdef CONFIG_CONS_INDEX
#define INDEX (CONFIG_CONS_INDEX - 1)
#else
#define INDEX 0
#endif
	if (uclass_get_device_by_seq(UCLASS_SERIAL, INDEX, &dev) &&
	    uclass_get_device(UCLASS_SERIAL, INDEX, &dev) &&
	    (uclass_first_device(UCLASS_SERIAL, &dev) || !dev))
		panic("No serial driver found");
#undef INDEX
	gd->cur_serial_dev = dev;
}

/* Called prior to relocation */
int serial_init(void)
{
	serial_find_console_or_panic();
	gd->flags |= GD_FLG_SERIAL_READY;

	return 0;
}

/* Called after relocation */
void serial_initialize(void)
{
	serial_find_console_or_panic();
}

static void _serial_putc(struct udevice *dev, char ch)
{
	struct dm_serial_ops *ops = serial_get_ops(dev);
	int err;

	do {
		err = ops->putc(dev, ch);
	} while (err == -EAGAIN);
	if (ch == '\n')
		_serial_putc(dev, '\r');
}

static void _serial_puts(struct udevice *dev, const char *str)
{
	while (*str)
		_serial_putc(dev, *str++);
}

static int _serial_getc(struct udevice *dev)
{
	struct dm_serial_ops *ops = serial_get_ops(dev);
	int err;

	do {
		err = ops->getc(dev);
		if (err == -EAGAIN)
			WATCHDOG_RESET();
	} while (err == -EAGAIN);

	return err >= 0 ? err : 0;
}

static int _serial_tstc(struct udevice *dev)
{
	struct dm_serial_ops *ops = serial_get_ops(dev);

	if (ops->pending)
		return ops->pending(dev, true);

	return 1;
}

void serial_putc(char ch)
{
	_serial_putc(gd->cur_serial_dev, ch);
}

void serial_puts(const char *str)
{
	_serial_puts(gd->cur_serial_dev, str);
}

int serial_getc(void)
{
	return _serial_getc(gd->cur_serial_dev);
}

int serial_tstc(void)
{
	return _serial_tstc(gd->cur_serial_dev);
}

void serial_setbrg(void)
{
	struct dm_serial_ops *ops = serial_get_ops(gd->cur_serial_dev);

	if (ops->setbrg)
		ops->setbrg(gd->cur_serial_dev, gd->baudrate);
}

void serial_stdio_init(void)
{
}

#ifdef CONFIG_DM_STDIO
static void serial_stub_putc(struct stdio_dev *sdev, const char ch)
{
	_serial_putc(sdev->priv, ch);
}
#endif

void serial_stub_puts(struct stdio_dev *sdev, const char *str)
{
	_serial_puts(sdev->priv, str);
}

int serial_stub_getc(struct stdio_dev *sdev)
{
	return _serial_getc(sdev->priv);
}

int serial_stub_tstc(struct stdio_dev *sdev)
{
	return _serial_tstc(sdev->priv);
}

/**
 * on_baudrate() - Update the actual baudrate when the env var changes
 *
 * This will check for a valid baudrate and only apply it if valid.
 */
static int on_baudrate(const char *name, const char *value, enum env_op op,
	int flags)
{
	int i;
	int baudrate;

	switch (op) {
	case env_op_create:
	case env_op_overwrite:
		/*
		 * Switch to new baudrate if new baudrate is supported
		 */
		baudrate = simple_strtoul(value, NULL, 10);

		/* Not actually changing */
		if (gd->baudrate == baudrate)
			return 0;

		for (i = 0; i < ARRAY_SIZE(baudrate_table); ++i) {
			if (baudrate == baudrate_table[i])
				break;
		}
		if (i == ARRAY_SIZE(baudrate_table)) {
			if ((flags & H_FORCE) == 0)
				printf("## Baudrate %d bps not supported\n",
				       baudrate);
			return 1;
		}
		if ((flags & H_INTERACTIVE) != 0) {
			printf("## Switch baudrate to %d bps and press ENTER ...\n",
			       baudrate);
			udelay(50000);
		}

		gd->baudrate = baudrate;

		serial_setbrg();

		udelay(50000);

		if ((flags & H_INTERACTIVE) != 0)
			while (1) {
				if (getc() == '\r')
					break;
			}

		return 0;
	case env_op_delete:
		printf("## Baudrate may not be deleted\n");
		return 1;
	default:
		return 0;
	}
}
U_BOOT_ENV_CALLBACK(baudrate, on_baudrate);

static int serial_post_probe(struct udevice *dev)
{
	struct dm_serial_ops *ops = serial_get_ops(dev);
#ifdef CONFIG_DM_STDIO
	struct serial_dev_priv *upriv = dev->uclass_priv;
	struct stdio_dev sdev;
#endif
	int ret;

	/* Set the baud rate */
	if (ops->setbrg) {
		ret = ops->setbrg(dev, gd->baudrate);
		if (ret)
			return ret;
	}

#ifdef CONFIG_DM_STDIO
	if (!(gd->flags & GD_FLG_RELOC))
		return 0;
	memset(&sdev, '\0', sizeof(sdev));

	strncpy(sdev.name, dev->name, sizeof(sdev.name));
	sdev.flags = DEV_FLAGS_OUTPUT | DEV_FLAGS_INPUT;
	sdev.priv = dev;
	sdev.putc = serial_stub_putc;
	sdev.puts = serial_stub_puts;
	sdev.getc = serial_stub_getc;
	sdev.tstc = serial_stub_tstc;
	stdio_register_dev(&sdev, &upriv->sdev);
#endif
	return 0;
}

static int serial_pre_remove(struct udevice *dev)
{
#ifdef CONFIG_SYS_STDIO_DEREGISTER
	struct serial_dev_priv *upriv = dev->uclass_priv;

	if (stdio_deregister_dev(upriv->sdev, 0))
		return -EPERM;
#endif

	return 0;
}

UCLASS_DRIVER(serial) = {
	.id		= UCLASS_SERIAL,
	.name		= "serial",
	.post_probe	= serial_post_probe,
	.pre_remove	= serial_pre_remove,
	.per_device_auto_alloc_size = sizeof(struct serial_dev_priv),
};
