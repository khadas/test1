/*
 * (C) Copyright 2016 Texas Instruments Incorporated, <www.ti.com>
 * Keerthy <j-keerthy@ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <fdtdec.h>
#include <errno.h>
#include <dm.h>
#include <i2c.h>
#include <power/pmic.h>
#include <power/regulator.h>
#include <power/palmas.h>
#include <dm/device.h>

DECLARE_GLOBAL_DATA_PTR;

static const struct pmic_child_info pmic_children_info[] = {
	{ .prefix = "ldo", .driver = PALMAS_LDO_DRIVER },
	{ .prefix = "smps", .driver = PALMAS_SMPS_DRIVER },
	{ },
};

static int palmas_write(struct udevice *dev, uint reg, const uint8_t *buff,
			  int len)
{
	if (dm_i2c_write(dev, reg, buff, len)) {
		error("write error to device: %p register: %#x!", dev, reg);
		return -EIO;
	}

	return 0;
}

static int palmas_read(struct udevice *dev, uint reg, uint8_t *buff, int len)
{
	if (dm_i2c_read(dev, reg, buff, len)) {
		error("read error from device: %p register: %#x!", dev, reg);
		return -EIO;
	}

	return 0;
}

static int palmas_bind(struct udevice *dev)
{
	int pmic_node = -1, regulators_node;
	const void *blob = gd->fdt_blob;
	int children;
	int node = dev->of_offset;
	int subnode, len;

	fdt_for_each_subnode(subnode, blob, node) {
		const char *name;
		char *temp;

		name = fdt_get_name(blob, subnode, &len);
		temp = strstr(name, "pmic");
		if (temp) {
			pmic_node = subnode;
			break;
		}
	}

	if (pmic_node <= 0) {
		debug("%s: %s pmic subnode not found!", __func__, dev->name);
		return -ENXIO;
	}

	regulators_node = fdt_subnode_offset(blob, pmic_node, "regulators");

	if (regulators_node <= 0) {
		debug("%s: %s reg subnode not found!", __func__, dev->name);
		return -ENXIO;
	}

	children = pmic_bind_children(dev, regulators_node, pmic_children_info);
	if (!children)
		debug("%s: %s - no child found\n", __func__, dev->name);

	/* Always return success for this device */
	return 0;
}

static struct dm_pmic_ops palmas_ops = {
	.read = palmas_read,
	.write = palmas_write,
};

static const struct udevice_id palmas_ids[] = {
	{ .compatible = "ti,tps659038", .data = TPS659038 },
	{ .compatible = "ti,tps65917" , .data = TPS65917 },
	{ }
};

U_BOOT_DRIVER(pmic_palmas) = {
	.name = "palmas_pmic",
	.id = UCLASS_PMIC,
	.of_match = palmas_ids,
	.bind = palmas_bind,
	.ops = &palmas_ops,
};
