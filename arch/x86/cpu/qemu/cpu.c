/*
 * Copyright (C) 2015, Miao Yan <yanmiaobest@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <cpu.h>
#include <dm.h>
#include <errno.h>
#include <asm/cpu.h>
#include <asm/fw_cfg.h>

DECLARE_GLOBAL_DATA_PTR;

int cpu_qemu_bind(struct udevice *dev)
{
	struct cpu_platdata *plat = dev_get_parent_platdata(dev);

	plat->cpu_id = fdtdec_get_int(gd->fdt_blob, dev->of_offset,
				      "intel,apic-id", -1);

	return 0;
}

int cpu_qemu_get_desc(struct udevice *dev, char *buf, int size)
{
	if (size < CPU_MAX_NAME_LEN)
		return -ENOSPC;

	cpu_get_name(buf);

	return 0;
}

static int cpu_qemu_get_count(struct udevice *dev)
{
	return qemu_fwcfg_online_cpus();
}

static const struct cpu_ops cpu_qemu_ops = {
	.get_desc	= cpu_qemu_get_desc,
	.get_count	= cpu_qemu_get_count,
};

static const struct udevice_id cpu_qemu_ids[] = {
	{ .compatible = "cpu-qemu" },
	{ }
};

U_BOOT_DRIVER(cpu_qemu_drv) = {
	.name		= "cpu_qemu",
	.id		= UCLASS_CPU,
	.of_match	= cpu_qemu_ids,
	.bind		= cpu_qemu_bind,
	.ops		= &cpu_qemu_ops,
};
