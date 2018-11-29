// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018 Jerome Brunet  <jbrunet@baylibre.com>
 * Copyright (C) 2017 Xingyu Chen <xingyu.chen@amlogic.com>
 */

#include <asm/gpio.h>
#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <linux/io.h>
#include "pinctrl-meson-axg.h"

static int meson_axg_pmx_get_bank(struct udevice *dev, unsigned int pin,
				  struct meson_pmx_bank **bank)
{
	int i;
	struct meson_pinctrl *priv = dev_get_priv(dev);
	struct meson_axg_pmx_data *pmx = priv->data->pmx_data;

	for (i = 0; i < pmx->num_pmx_banks; i++)
		if (pin >= pmx->pmx_banks[i].first &&
		    pin <= pmx->pmx_banks[i].last) {
			*bank = &pmx->pmx_banks[i];
			return 0;
		}

	return -EINVAL;
}

static int meson_axg_pmx_calc_reg_and_offset(struct meson_pmx_bank *bank,
					     unsigned int pin,
					     unsigned int *reg,
					     unsigned int *offset)
{
	int shift;

	shift = pin - bank->first;

	*reg = bank->reg + (bank->offset + (shift << 2)) / 32;
	*offset = (bank->offset + (shift << 2)) % 32;

	return 0;
}

static int meson_axg_pmx_update_function(struct udevice *dev,
					 unsigned int pin, unsigned int func)
{
	struct meson_pinctrl *priv = dev_get_priv(dev);
	struct meson_pmx_bank *bank;
	unsigned int offset;
	unsigned int reg;
	unsigned int tmp;
	int ret;

	ret = meson_axg_pmx_get_bank(dev, pin, &bank);
	if (ret)
		return ret;

	meson_axg_pmx_calc_reg_and_offset(bank, pin, &reg, &offset);

	tmp = readl(priv->reg_mux + (reg << 2));
	tmp &= ~(0xf << offset);
	tmp |= (func & 0xf) << offset;
	writel(tmp, priv->reg_mux + (reg << 2));

	return ret;
}

static int meson_axg_pinmux_group_set(struct udevice *dev,
				      unsigned int group_selector,
				      unsigned int func_selector)
{
	struct meson_pinctrl *priv = dev_get_priv(dev);
	const struct meson_pmx_group *group;
	const struct meson_pmx_func *func;
	struct meson_pmx_axg_data *pmx_data;
	int i, ret;

	group = &priv->data->groups[group_selector];
	pmx_data = (struct meson_pmx_axg_data *)group->data;
	func = &priv->data->funcs[func_selector];

	debug("pinmux: set group %s func %s\n", group->name, func->name);

	for (i = 0; i < group->num_pins; i++) {
		ret = meson_axg_pmx_update_function(dev, group->pins[i],
						    pmx_data->func);
		if (ret)
			return ret;
	}

	return 0;
}

const struct pinctrl_ops meson_axg_pinctrl_ops = {
	.get_groups_count = meson_pinctrl_get_groups_count,
	.get_group_name = meson_pinctrl_get_group_name,
	.get_functions_count = meson_pinmux_get_functions_count,
	.get_function_name = meson_pinmux_get_function_name,
	.pinmux_group_set = meson_axg_pinmux_group_set,
	.set_state = pinctrl_generic_set_state,
};

static int meson_axg_gpio_request(struct udevice *dev,
				  unsigned int offset, const char *label)
{
	return meson_axg_pmx_update_function(dev->parent, offset, 0);
}

static const struct dm_gpio_ops meson_axg_gpio_ops = {
	.request = meson_axg_gpio_request,
	.set_value = meson_gpio_set,
	.get_value = meson_gpio_get,
	.get_function = meson_gpio_get_direction,
	.direction_input = meson_gpio_direction_input,
	.direction_output = meson_gpio_direction_output,
};

const struct driver meson_axg_gpio_driver = {
	.name	= "meson-axg-gpio",
	.id	= UCLASS_GPIO,
	.probe	= meson_gpio_probe,
	.ops	= &meson_axg_gpio_ops,
};
