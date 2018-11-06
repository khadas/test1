/*
 * drivers/amlogic/media/vout/lcd/lcd_extern/lcd_extern.c
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <common.h>
#include <malloc.h>
#include <dm.h>
#include <asm/gpio.h>
#include <fdtdec.h>
#include <amlogic/media/vout/lcd/aml_lcd.h>
#include <amlogic/media/vout/lcd/lcd_extern.h>
#include "lcd_extern.h"
#include "../lcd_common.h"
#include "../lcd_reg.h"


static const void *ext_dt_blob = NULL;

static struct aml_lcd_extern_driver_s *lcd_ext_driver;

struct aml_lcd_extern_driver_s *aml_lcd_extern_get_driver(void)
{
	if (lcd_ext_driver == NULL)
		EXTERR("invalid driver\n");
	return lcd_ext_driver;
}

static void lcd_extern_init_table_dynamic_size_print(
		struct lcd_extern_config_s *econf, int flag)
{
	int i, j, max_len;
	unsigned char cmd_size;
	unsigned char *table;

	if (flag) {
		printf("power on:\n");
		table = econf->table_init_on;
		max_len = econf->table_init_on_cnt;
	} else {
		printf("power off:\n");
		table = econf->table_init_off;
		max_len = econf->table_init_off_cnt;
	}
	if (table == NULL) {
		EXTERR("init_table %d is NULL\n", flag);
		return;
	}
	i = 0;
	switch (econf->type) {
	case LCD_EXTERN_I2C:
	case LCD_EXTERN_SPI:
		while ((i + 1) < max_len) {
			if (table[i] == LCD_EXT_CMD_TYPE_END) {
				printf("  0x%02x,%d,\n", table[i], table[i+1]);
				break;
			}
			cmd_size = table[i+1];
			printf("  0x%02x,%d,", table[i], cmd_size);
			if (cmd_size == 0)
				goto init_table_dynamic_print_i2c_spi_next;
			if (i + 2 + cmd_size > max_len) {
				printf("cmd_size out of support\n");
				break;
			}

			if ((table[i] == LCD_EXT_CMD_TYPE_GPIO) ||
				(table[i] == LCD_EXT_CMD_TYPE_DELAY)) {
				for (j = 0; j < cmd_size; j++)
					printf("%d,", table[i+2+j]);
			} else if ((table[i] == LCD_EXT_CMD_TYPE_CMD) ||
				(table[i] == LCD_EXT_CMD_TYPE_CMD2)) {
				for (j = 0; j < cmd_size; j++)
					printf("0x%02x,", table[i+2+j]);
			} else if ((table[i] == LCD_EXT_CMD_TYPE_CMD_DELAY) ||
				(table[i] == LCD_EXT_CMD_TYPE_CMD2_DELAY)) {
				for (j = 0; j < (cmd_size - 1); j++)
					printf("0x%02x,", table[i+2+j]);
				printf("%d,", table[i+cmd_size+1]);
			} else {
				for (j = 0; j < cmd_size; j++)
					printf("0x%02x,", table[i+2+j]);
			}
init_table_dynamic_print_i2c_spi_next:
			printf("\n");
			i += (cmd_size + 2);
		}
		break;
	case LCD_EXTERN_MIPI:
		while ((i + 1) < max_len) {
			cmd_size = table[i+1];
			if (table[i] == LCD_EXT_CMD_TYPE_END) {
				if (cmd_size == 0xff) {
					printf("  0x%02x,0x%02x,\n",
						table[i], table[i+1]);
					break;
				}
				if (cmd_size == 0) {
					printf("  0x%02x,%d,\n",
						table[i], table[i+1]);
					break;
				}
				cmd_size = 0;
			}

			printf("  0x%02x,%d,", table[i], table[i+1]);
			if (cmd_size == 0)
				goto init_table_dynamic_print_mipi_next;
			if (i + 2 + cmd_size > max_len) {
				printf("cmd_size out of support\n");
				break;
			}

			if ((table[i] == LCD_EXT_CMD_TYPE_GPIO) ||
				(table[i] == LCD_EXT_CMD_TYPE_DELAY)) {
				for (j = 0; j < cmd_size; j++)
					printf("%d,", table[i+2+j]);
			} else if ((table[i] & 0xf) == 0x0) {
				printf("  init_%s wrong data_type: 0x%02x\n",
					flag ? "on" : "off", table[i]);
				break;
			} else {
				for (j = 0; j < cmd_size; j++)
					printf("0x%02x,", table[i+2+j]);
			}
init_table_dynamic_print_mipi_next:
			printf("\n");
			i += (cmd_size + 2);
		}
		break;
	default:
		break;
	}
}

static void lcd_extern_init_table_fixed_size_print(
		struct lcd_extern_config_s *econf, int flag)
{
	int i, j, max_len;
	unsigned char cmd_size;
	unsigned char *table;

	cmd_size = econf->cmd_size;
	if (flag) {
		printf("power on:\n");
		table = econf->table_init_on;
		max_len = econf->table_init_on_cnt;
	} else {
		printf("power off:\n");
		table = econf->table_init_off;
		max_len = econf->table_init_off_cnt;
	}
	if (table == NULL) {
		EXTERR("init_table %d is NULL\n", flag);
		return;
	}

	i = 0;
	while ((i + cmd_size) <= max_len) {
		printf("  ");
		for (j = 0; j < cmd_size; j++)
			printf("0x%02x,", table[i+j]);
		printf("\n");

		if (table[i] == LCD_EXT_CMD_TYPE_END)
			break;
		i += cmd_size;
	}
}

static void lcd_extern_info_print(void)
{
	struct lcd_extern_config_s *econf;
	struct lcd_extern_common_s *ecommon;

	if (lcd_ext_driver == NULL) {
		EXTERR("no lcd_extern driver\n");
		return;
	}
	econf = lcd_ext_driver->config;
	ecommon = lcd_ext_driver->common;

	LCDPR("lcd_extern info:\n");
	printf("name:             %s\n"
		"index:            %d\n"
		"type:             %d\n"
		"status:           %d\n",
		econf->name, econf->index,
		econf->type, econf->status);

	switch (econf->type) {
	case LCD_EXTERN_I2C:
		printf("i2c_addr:         0x%02x\n"
			"i2c_addr2:        0x%02x\n"
			"i2c_bus:          %d\n"
			"i2c_gpio_sck:     %d\n"
			"i2c_gpio_sda:     %d\n"
			"table_loaded:     %d\n",
			econf->i2c_addr, econf->i2c_addr2,
			ecommon->i2c_bus,
			ecommon->i2c_gpio_sck,
			ecommon->i2c_gpio_sda,
			econf->table_init_loaded);
		if (econf->cmd_size == 0)
			break;
		printf("init_loaded           = %d\n"
			"cmd_size              = %d\n"
			"table_init_on_cnt:    = %d\n"
			"table_init_off_cnt:   = %d\n",
			econf->table_init_loaded,
			econf->cmd_size,
			econf->table_init_on_cnt,
			econf->table_init_off_cnt);
		if (econf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			lcd_extern_init_table_dynamic_size_print(econf, 1);
			lcd_extern_init_table_dynamic_size_print(econf, 0);
		} else {
			lcd_extern_init_table_fixed_size_print(econf, 1);
			lcd_extern_init_table_fixed_size_print(econf, 0);
		}
		break;
	case LCD_EXTERN_SPI:
		printf("spi_gpio_cs:      %d\n"
			"spi_gpio_clk:     %d\n"
			"spi_gpio_data:    %d\n"
			"spi_clk_freq:     %d\n"
			"spi_clk_pol:      %d\n"
			"table_loaded:     %d\n",
			ecommon->spi_gpio_cs,
			ecommon->spi_gpio_clk, ecommon->spi_gpio_data,
			econf->spi_clk_freq, econf->spi_clk_pol,
			econf->table_init_loaded);
		if (econf->cmd_size == 0)
			break;
		printf("init_loaded           = %d\n"
			"cmd_size              = %d\n"
			"table_init_on_cnt:    = %d\n"
			"table_init_off_cnt:   = %d\n",
			econf->table_init_loaded,
			econf->cmd_size,
			econf->table_init_on_cnt,
			econf->table_init_off_cnt);
		if (econf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			lcd_extern_init_table_dynamic_size_print(econf, 1);
			lcd_extern_init_table_dynamic_size_print(econf, 0);
		} else {
			lcd_extern_init_table_fixed_size_print(econf, 1);
			lcd_extern_init_table_fixed_size_print(econf, 0);
		}
		break;
	case LCD_EXTERN_MIPI:
		if (econf->cmd_size != LCD_EXT_CMD_SIZE_DYNAMIC)
			break;
		printf("init_loaded           = %d\n"
			"cmd_size              = %d\n"
			"table_init_on_cnt:    = %d\n"
			"table_init_off_cnt:   = %d\n",
			econf->table_init_loaded,
			econf->cmd_size,
			econf->table_init_on_cnt,
			econf->table_init_off_cnt);
		lcd_extern_init_table_dynamic_size_print(econf, 1);
		lcd_extern_init_table_dynamic_size_print(econf, 0);
		break;
	default:
		printf("not support extern_type\n");
		break;
	}
}

/* ***************************************
 *     lcd_extern gpio
 * *************************************** */
static struct lcd_cpu_gpio_s lcd_ext_gpio[LCD_EXTERN_GPIO_NUM_MAX] = {
	{.name = "invalid", .probe_flag = 0, .register_flag = 0,},
	{.name = "invalid", .probe_flag = 0, .register_flag = 0,},
	{.name = "invalid", .probe_flag = 0, .register_flag = 0,},
	{.name = "invalid", .probe_flag = 0, .register_flag = 0,},
	{.name = "invalid", .probe_flag = 0, .register_flag = 0,},
	{.name = "invalid", .probe_flag = 0, .register_flag = 0,},
};

static int lcd_ext_gpio_probe(const char *name, unsigned char index)
{
	if (name == NULL) {
		LCDERR("bl: %s: gpio name is null\n", __func__);
		return -1;
	}
	if (index >= LCD_EXTERN_GPIO_NUM_MAX) {
		LCDERR("bl: %s: invalid gpio: %d\n", __func__, index);
		return -1;
	}
	if (lcd_ext_gpio[index].probe_flag == 1) {
		if (lcd_debug_print_flag) {
			LCDPR("bl: gpio %s(%d) is already probed\n",
				lcd_ext_gpio[index].name, index);
		}
		return 0;
	}

	if (lcd_debug_print_flag)
		LCDPR("bl: probe gpio: %s(%d)\n", name, index);
	strcpy(lcd_ext_gpio[index].name, name);
	/* init gpio flag */
	lcd_ext_gpio[index].probe_flag = 1;
	lcd_ext_gpio[index].register_flag = 0;

	return 0;
}

static int lcd_ext_gpio_request(unsigned char index)
{
	int ret = 0;

	if (index >= LCD_EXTERN_GPIO_NUM_MAX) {
		LCDERR("bl: %s: invalid gpio: %d\n", __func__, index);
		return -1;
	}
	if (lcd_ext_gpio[index].probe_flag == 0) {
		LCDERR("bl: gpio %d is not probed\n", index);
		return -1;
	}
	if (lcd_ext_gpio[index].register_flag == 1) {
		if (lcd_debug_print_flag) {
			LCDPR("bl: gpio %s(%d) is already registered\n",
				lcd_ext_gpio[index].name, index);
		}
		return 0;
	}

	ret = dm_gpio_lookup_name(lcd_ext_gpio[index].name, &lcd_ext_gpio[index].gpio);
	if (ret) {
		LCDERR("bl: lookup gpio: wrong name %s\n", lcd_ext_gpio[index].name);
		return -1;
	}

	ret = dm_gpio_request(&lcd_ext_gpio[index].gpio, "aml_lcd_bl");
	if (ret) {
		LCDERR("bl: request gpio %s(%d) failed\n", lcd_ext_gpio[index].name, index);
		return -1;
	}

	if (lcd_debug_print_flag)
		LCDPR("bl: request gpio: %s(%d)\n", lcd_ext_gpio[index].name, index);
	lcd_ext_gpio[index].register_flag = 1;

	return 0;
}

int lcd_ext_gpio_set(unsigned char index, int value)
{
	int ret = 0;

	if (index >= LCD_EXTERN_GPIO_NUM_MAX) {
		LCDERR("bl: %s: invalid gpio: %d\n", __func__, index);
		return -1;
	}
	if (lcd_ext_gpio[index].register_flag == 0) {
		ret = lcd_ext_gpio_request(index);
		if (ret)
			return -1;
	}

	switch (value) {
	case LCD_GPIO_OUTPUT_LOW:
		ret = dm_gpio_set_dir_flags(&lcd_ext_gpio[index].gpio, GPIOD_IS_OUT);
		if (ret) {
			LCDERR("bl: set gpio %s(%d) direction failed\n",
				lcd_ext_gpio[index].name, index);
			return ret;
		}
		dm_gpio_set_value(&lcd_ext_gpio[index].gpio, 0);
		break;
	case LCD_GPIO_OUTPUT_HIGH:
		ret = dm_gpio_set_dir_flags(&lcd_ext_gpio[index].gpio, GPIOD_IS_OUT);
		if (ret) {
			LCDERR("bl: set gpio %s(%d) direction failed\n",
				lcd_ext_gpio[index].name, index);
			return ret;
		}
		dm_gpio_set_value(&lcd_ext_gpio[index].gpio, 1);
		break;
	case LCD_GPIO_INPUT:
	default:
		ret = dm_gpio_set_dir_flags(&lcd_ext_gpio[index].gpio, GPIOD_IS_IN);
		if (ret) {
			LCDERR("bl: set gpio %s(%d) direction failed\n",
				lcd_ext_gpio[index].name, index);
			return ret;
		}
		break;
	}
	if (lcd_debug_print_flag) {
		LCDPR("bl: gpio: %s(%d), value: %d\n",
			lcd_ext_gpio[index].name, index, value);
	}

	return 0;
}

unsigned int lcd_ext_gpio_input_get(unsigned char index)
{
	int ret;
	unsigned int value;

	if (index >= LCD_EXTERN_GPIO_NUM_MAX) {
		LCDERR("%s: invalid gpio: %d\n", __func__, index);
		return 0;
	}
	if (lcd_ext_gpio[index].register_flag == 0) {
		ret = lcd_ext_gpio_request(index);
		if (ret)
			return 0;
	}

	value = dm_gpio_get_value(&lcd_ext_gpio[index].gpio);

	return value;
}
/* *************************************** */

void lcd_extern_pinmux_set(int status)
{
	int i;
	struct lcd_extern_common_s *extcommon = lcd_ext_driver->common;

	if (extcommon->pinmux_valid == 0)
		return;

	if (lcd_debug_print_flag)
		EXTPR("%s: %d\n", __func__, status);

	if (status) {
		i = 0;
		while (i < LCD_PINMUX_NUM) {
			if (extcommon->pinmux_clr[i][0] == LCD_PINMUX_END)
				break;
			if (lcd_debug_print_flag) {
				EXTPR("pinmux_clr: %d, 0x%08x\n",
					extcommon->pinmux_clr[i][0],
					extcommon->pinmux_clr[i][1]);
			}
			lcd_pinmux_clr_mask(extcommon->pinmux_clr[i][0],
				extcommon->pinmux_clr[i][1]);
			i++;
		}
		i = 0;
		while (i < LCD_PINMUX_NUM) {
			if (extcommon->pinmux_set[i][0] == LCD_PINMUX_END)
				break;
			if (lcd_debug_print_flag) {
				EXTPR("pinmux_set: %d, 0x%08x\n",
					extcommon->pinmux_set[i][0],
					extcommon->pinmux_set[i][1]);
			}
			lcd_pinmux_set_mask(extcommon->pinmux_set[i][0],
				extcommon->pinmux_set[i][1]);
			i++;
		}
	} else {
		i = 0;
		while (i < LCD_PINMUX_NUM) {
			if (extcommon->pinmux_set[i][0] == LCD_PINMUX_END)
				break;
			if (lcd_debug_print_flag) {
				EXTPR("pinmux_clr: %d, 0x%08x\n",
					extcommon->pinmux_set[i][0],
					extcommon->pinmux_set[i][1]);
			}
			lcd_pinmux_clr_mask(extcommon->pinmux_set[i][0],
				extcommon->pinmux_set[i][1]);
			i++;
		}
		/* set gpio */
		switch (lcd_ext_driver->config->type) {
		case LCD_EXTERN_I2C:
			if (extcommon->i2c_gpio_sck < LCD_EXTERN_GPIO_NUM_MAX) {
				lcd_ext_gpio_set(extcommon->i2c_gpio_sck,
					extcommon->pinmux_gpio_off);
			}
			if (extcommon->i2c_gpio_sda < LCD_EXTERN_GPIO_NUM_MAX) {
				lcd_ext_gpio_set(extcommon->i2c_gpio_sda,
					extcommon->pinmux_gpio_off);
			}
			break;
		case LCD_EXTERN_SPI:
			if (extcommon->spi_gpio_cs < LCD_EXTERN_GPIO_NUM_MAX) {
				lcd_ext_gpio_set(extcommon->spi_gpio_cs,
					extcommon->pinmux_gpio_off);
			}
			if (extcommon->spi_gpio_clk < LCD_EXTERN_GPIO_NUM_MAX) {
				lcd_ext_gpio_set(extcommon->spi_gpio_clk,
					extcommon->pinmux_gpio_off);
			}
			if (extcommon->spi_gpio_data < LCD_EXTERN_GPIO_NUM_MAX) {
				lcd_ext_gpio_set(extcommon->spi_gpio_data,
					extcommon->pinmux_gpio_off);
			}
			break;
		default:
			break;
		}
	}
}

static unsigned char lcd_extern_get_i2c_bus_str(const char *str)
{
	unsigned char i2c_bus;

	if (strncmp(str, "i2c_bus_ao", 10) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_4;
	else if (strncmp(str, "i2c_bus_a", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_0;
	else if (strncmp(str, "i2c_bus_b", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_1;
	else if (strncmp(str, "i2c_bus_c", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_2;
	else if (strncmp(str, "i2c_bus_d", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_3;
	else if (strncmp(str, "i2c_bus_0", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_0;
	else if (strncmp(str, "i2c_bus_1", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_1;
	else if (strncmp(str, "i2c_bus_2", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_2;
	else if (strncmp(str, "i2c_bus_3", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_3;
	else if (strncmp(str, "i2c_bus_4", 9) == 0)
		i2c_bus = LCD_EXTERN_I2C_BUS_4;
	else {
		i2c_bus = LCD_EXTERN_I2C_BUS_MAX;
		EXTERR("invalid i2c_bus: %s\n", str);
	}

	return i2c_bus;
}

char *lcd_extern_get_dts_prop(int nodeoffset, char *propname)
{
	char *propdata;

	propdata = (char *)fdt_getprop(ext_dt_blob, nodeoffset, propname, NULL);
	return propdata;
}

int lcd_extern_get_dts_child(int index)
{
	int nodeoffset;
	char chlid_node[30];
	char *propdata;

	sprintf(chlid_node, "/lcd_extern/extern_%d", index);
	nodeoffset = fdt_path_offset(ext_dt_blob, chlid_node);
	if (nodeoffset < 0) {
		EXTERR("dts: not find  node %s\n", chlid_node);
		return nodeoffset;
	}

	propdata = (char *)fdt_getprop(ext_dt_blob, nodeoffset, "index", NULL);
	if (propdata == NULL) {
		EXTERR("get index failed, exit\n");
		return -1;
	} else {
		if (be32_to_cpup((u32*)propdata) != index) {
			EXTERR("index not match, exit\n");
			return -1;
		}
	}
	return nodeoffset;
}

static int lcd_extern_pinmux_load_from_bsp(struct lcd_extern_common_s *extcommon)
{
	struct lcd_pinmux_ctrl_s *pinmux;
	unsigned int i, j;
	int set_cnt = 0, clr_cnt = 0;

	if (lcd_debug_print_flag)
		EXTPR("%s\n", __func__);

	extcommon->pinmux_valid = 0;
	if (extcommon->lcd_ext_pinmux == NULL) {
		if (lcd_debug_print_flag)
			LCDPR("%s: lcd_ext_pinmux is NULL for lcd.c\n", __func__);
		return -1;
	}

	pinmux = extcommon->lcd_ext_pinmux;
	for (i = 0; i < LCD_PINMX_MAX; i++) {
		pinmux += i;
		if (strcmp(pinmux->name, "invalid") == 0)
			break;
		if (strcmp(pinmux->name, "extern_on") == 0) {
			for (j = 0; j < LCD_PINMUX_NUM; j++ ) {
				if (pinmux->pinmux_set[j][0] == LCD_PINMUX_END)
					break;
				extcommon->pinmux_set[j][0] = pinmux->pinmux_set[j][0];
				extcommon->pinmux_set[j][1] = pinmux->pinmux_set[j][1];
				set_cnt++;
			}
			for (j = 0; j < LCD_PINMUX_NUM; j++ ) {
				if (pinmux->pinmux_clr[j][0] == LCD_PINMUX_END)
					break;
				extcommon->pinmux_clr[j][0] = pinmux->pinmux_clr[j][0];
				extcommon->pinmux_clr[j][1] = pinmux->pinmux_clr[j][1];
				clr_cnt++;
			}
			if (set_cnt < LCD_PINMUX_NUM) {
				extcommon->pinmux_set[set_cnt][0] = LCD_PINMUX_END;
				extcommon->pinmux_set[set_cnt][1] = 0x0;
			}
			if (clr_cnt < LCD_PINMUX_NUM) {
				extcommon->pinmux_clr[clr_cnt][0] = LCD_PINMUX_END;
				extcommon->pinmux_clr[clr_cnt][1] = 0x0;
			}
			extcommon->pinmux_valid = 1;
			break;
		}
	}

	return 0;
}

static int lcd_extern_get_init_dts(const void *dt_blob, struct lcd_extern_common_s *extcommon)
{
	int parent_offset;
	char *propdata, *p;
	const char *str;
	int i;

	parent_offset = fdt_path_offset(dt_blob, "/lcd_extern");
	if (parent_offset < 0) {
		EXTERR("not find /lcd_extern node: %s\n", fdt_strerror(parent_offset));
		return -1;
	}

	propdata = (char *)fdt_getprop(dt_blob, parent_offset, "key_valid", NULL);
	if (propdata == NULL) {
		if (lcd_debug_print_flag)
			EXTPR("failed to get key_valid\n");
		extcommon->lcd_ext_key_valid = 0;
	} else {
		extcommon->lcd_ext_key_valid = (unsigned char)(be32_to_cpup((u32*)propdata));
	}

	propdata = (char *)fdt_getprop(dt_blob, parent_offset, "i2c_bus", NULL);
	if (propdata == NULL)
		extcommon->i2c_bus = LCD_EXTERN_I2C_BUS_MAX;
	else
		extcommon->i2c_bus = lcd_extern_get_i2c_bus_str(propdata);

	i = 0;
	propdata = (char *)fdt_getprop(dt_blob, parent_offset, "extern_gpio_names", NULL);
	if (propdata == NULL) {
		if (lcd_debug_print_flag)
			EXTPR("failed to get extern_gpio_names\n");
	} else {
		p = propdata;
		while (i < LCD_EXTERN_GPIO_NUM_MAX) {
			if (i > 0)
				p += strlen(p) + 1;
			str = p;
			if (strlen(str) == 0)
				break;
			lcd_ext_gpio_probe(str, i);
			i++;
		}
	}

	propdata = (char *)fdt_getprop(dt_blob, parent_offset, "i2c_gpio", NULL);
	if (propdata == NULL) {
		extcommon->i2c_gpio_sck = LCD_EXT_GPIO_INVALID;
		extcommon->i2c_gpio_sda = LCD_EXT_GPIO_INVALID;
	} else {
		extcommon->i2c_gpio_sck = (unsigned char)be32_to_cpup((u32*)propdata);
		extcommon->i2c_gpio_sda = (unsigned char)be32_to_cpup((((u32*)propdata)+1));
	}

	propdata = (char *)fdt_getprop(dt_blob, parent_offset, "spi_gpio", NULL);
	if (propdata == NULL) {
		extcommon->spi_gpio_cs = LCD_EXT_GPIO_INVALID;
		extcommon->spi_gpio_clk = LCD_EXT_GPIO_INVALID;
		extcommon->spi_gpio_data = LCD_EXT_GPIO_INVALID;
	} else {
		extcommon->spi_gpio_cs = (unsigned char)be32_to_cpup((u32*)propdata);
		extcommon->spi_gpio_clk = (unsigned char)be32_to_cpup((((u32*)propdata)+1));
		extcommon->spi_gpio_data = (unsigned char)be32_to_cpup((((u32*)propdata)+2));
	}

	propdata = (char *)fdt_getprop(dt_blob, parent_offset, "pinmux_gpio_off", NULL);
	if (propdata == NULL)
		extcommon->pinmux_gpio_off = 2;
	else
		extcommon->pinmux_gpio_off = be32_to_cpup((u32*)propdata);

	lcd_extern_pinmux_load_from_bsp(extcommon);
	if (lcd_debug_print_flag) {
		i = 0;
		while (i < LCD_PINMUX_NUM) {
			if (extcommon->pinmux_set[i][0] == LCD_PINMUX_END)
				break;
			EXTPR("pinmux_set: %d, 0x%08x\n",
				extcommon->pinmux_set[i][0],
				extcommon->pinmux_set[i][1]);
			i++;
		}
		i = 0;
		while (i < LCD_PINMUX_NUM) {
			if (extcommon->pinmux_clr[i][0] == LCD_PINMUX_END)
				break;
			EXTPR("pinmux_clr: %d, 0x%08x\n",
				extcommon->pinmux_clr[i][0],
				extcommon->pinmux_clr[i][1]);
			i++;
		}
	}

	return 0;
}

static int lcd_extern_init_table_dynamic_size_load_dts(const void *dt_blob,
		int nodeoffset, struct lcd_extern_config_s *extconf, int flag)
{
	unsigned char cmd_size, type;
	int i = 0, j, max_len;
	unsigned char *table;
	char propname[20];
	char *propdata;

	if (flag) {
		table = extconf->table_init_on;
		max_len = LCD_EXTERN_INIT_ON_MAX;
		sprintf(propname, "init_on");
	} else {
		table = extconf->table_init_off;
		max_len = LCD_EXTERN_INIT_OFF_MAX;
		sprintf(propname, "init_off");
	}
	if (table == NULL) {
		EXTERR("%s init_table is null\n", propname);
		return 0;
	}

	propdata = (char *)fdt_getprop(dt_blob, nodeoffset, propname, NULL);
	if (propdata == NULL) {
		EXTERR("%s: get %s failed\n", extconf->name, propname);
		table[0] = LCD_EXT_CMD_TYPE_END;
		table[1] = 0;
		return -1;
	}

	switch (extconf->type) {
	case LCD_EXTERN_I2C:
	case LCD_EXTERN_SPI:
		while ((i + 1) < max_len) {
			table[i] = (unsigned char)(be32_to_cpup((((u32*)propdata)+i)));
			table[i+1] = (unsigned char)(be32_to_cpup((((u32*)propdata)+i+1)));
			type = table[i];
			cmd_size = table[i+1];
			if (type == LCD_EXT_CMD_TYPE_END)
				break;
			if (cmd_size == 0)
				goto init_table_dynamic_i2c_spi_dts_next;
			if ((i + 2 + cmd_size) > max_len) {
				EXTERR("%s: %s cmd_size out of support\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			for (j = 0; j < cmd_size; j++)
				table[i+2+j] = (unsigned char)(be32_to_cpup((((u32*)propdata)+i+2+j)));

init_table_dynamic_i2c_spi_dts_next:
			i += (cmd_size + 2);
		}
		if (flag)
			extconf->table_init_on_cnt = i + 2;
		else
			extconf->table_init_off_cnt = i + 2;
		break;
	case LCD_EXTERN_MIPI:
		while ((i + 1) < max_len) {
			table[i] = (unsigned char)(be32_to_cpup((((u32*)propdata)+i)));
			table[i+1] = (unsigned char)(be32_to_cpup((((u32*)propdata)+i+1)));
			type = table[i];
			cmd_size = table[i+1];
			if (type == LCD_EXT_CMD_TYPE_END) {
				if ((cmd_size == 0xff) || (cmd_size == 0))
					break;
				cmd_size = 0;
			}
			if (cmd_size == 0)
				goto init_table_dynamic_mipi_dts_next;
			if ((i + 2 + cmd_size) > max_len) {
				EXTERR("%s: %s cmd_size out of support\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			for (j = 0; j < cmd_size; j++)
				table[i+2+j] = (unsigned char)(be32_to_cpup((((u32*)propdata)+i+2+j)));

init_table_dynamic_mipi_dts_next:
			i += (cmd_size + 2);
		}
		if (flag)
			extconf->table_init_on_cnt = i + 2;
		else
			extconf->table_init_off_cnt = i + 2;
		break;
	default:
		break;
	}

	return 0;
}

static int lcd_extern_init_table_fixed_size_load_dts(const void *dt_blob,
		int nodeoffset, struct lcd_extern_config_s *extconf, int flag)
{
	unsigned char cmd_size;
	int i = 0, j, max_len;
	unsigned char *table;
	char propname[20];
	char *propdata;

	cmd_size = extconf->cmd_size;
	if (flag) {
		table = extconf->table_init_on;
		max_len = LCD_EXTERN_INIT_ON_MAX;
		sprintf(propname, "init_on");
	} else {
		table = extconf->table_init_off;
		max_len = LCD_EXTERN_INIT_OFF_MAX;
		sprintf(propname, "init_off");
	}
	if (table == NULL) {
		EXTPR("%s init_table is null\n", propname);
		return 0;
	}

	propdata = (char *)fdt_getprop(dt_blob, nodeoffset, propname, NULL);
	if (propdata == NULL) {
		EXTERR("%s: get %s failed\n", extconf->name, propname);
		table[0] = LCD_EXT_CMD_TYPE_END;
		table[1] = 0;
		return -1;
	}

	while (i < max_len) {
		if ((i + cmd_size) > max_len) {
			EXTERR("%s: %s cmd_size out of support\n", extconf->name, propname);
			table[i] = LCD_EXT_CMD_TYPE_END;
			return -1;
		}
		for (j = 0; j < cmd_size; j++)
			table[i+j] = (unsigned char)(be32_to_cpup((((u32*)propdata)+i+j)));

		if (table[i] == LCD_EXT_CMD_TYPE_END)
			break;

		i += cmd_size;
	}
	if (flag)
		extconf->table_init_on_cnt = i + cmd_size;
	else
		extconf->table_init_off_cnt = i + cmd_size;

	return 0;
}

static int lcd_extern_get_config_dts(const void *dt_blob, int index,
		struct lcd_extern_config_s *extconf,
		struct lcd_extern_common_s *extcommon)
{
	int nodeoffset;
	char *propdata;
	const char *str;
	int ret = 0;

	extconf->table_init_loaded = 0;
	nodeoffset = lcd_extern_get_dts_child(index);
	if (nodeoffset < 0)
		return -1;

	propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "index", NULL);
	if (propdata == NULL) {
		extconf->index = LCD_EXTERN_INDEX_INVALID;
		EXTERR("get index failed, exit\n");
		return -1;
	} else {
		extconf->index = (unsigned char)(be32_to_cpup((u32*)propdata));
	}
	if (lcd_debug_print_flag)
		EXTPR("index = %d\n", extconf->index);

	propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "extern_name", NULL);
	if (propdata == NULL) {
		str = "invalid_name";
		strcpy(extconf->name, str);
		EXTERR("get extern_name failed\n");
	} else {
		memset(extconf->name, 0, LCD_EXTERN_NAME_LEN_MAX);
		strcpy(extconf->name, propdata);
	}

	propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "status", NULL);
	if (propdata == NULL) {
		EXTERR("get status failed, default to disabled\n");
		extconf->status = 0;
	} else {
		if (strncmp(propdata, "okay", 2) == 0)
			extconf->status = 1;
		else
			extconf->status = 0;
	}
	if (lcd_debug_print_flag)
		EXTPR("%s: status = %d\n", extconf->name, extconf->status);

	propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "type", NULL);
	if (propdata == NULL) {
		extconf->type = LCD_EXTERN_MAX;
		EXTERR("get type failed, exit\n");
		return -1;
	} else {
		extconf->type = be32_to_cpup((u32*)propdata);
	}
	if (lcd_debug_print_flag)
		EXTPR("%s: type = %d\n", extconf->name, extconf->type);

	switch (extconf->type) {
	case LCD_EXTERN_I2C:
		propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "i2c_address", NULL);
		if (propdata == NULL) {
			EXTERR("%s: get i2c_address failed, exit\n", extconf->name);
			extconf->i2c_addr = 0xff;
			return -1;
		} else {
			extconf->i2c_addr = (unsigned char)(be32_to_cpup((u32*)propdata));
		}
		if (lcd_debug_print_flag)
			EXTPR("%s: i2c_address=0x%02x\n", extconf->name, extconf->i2c_addr);
		propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "i2c_address2", NULL);
		if (propdata == NULL) {
			propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "i2c_second_address", NULL);
			if (propdata == NULL) {
				if (lcd_debug_print_flag)
					EXTPR("%s no i2c_address2 exist\n", extconf->name);
				extconf->i2c_addr2 = 0xff;
			} else {
				extconf->i2c_addr2 = (unsigned char)(be32_to_cpup((u32*)propdata));
			}
		} else {
			extconf->i2c_addr2 = (unsigned char)(be32_to_cpup((u32*)propdata));
		}
		if (lcd_debug_print_flag)
			EXTPR("%s: i2c_address2=0x%02x\n", extconf->name, extconf->i2c_addr2);

		extconf->i2c_bus = extcommon->i2c_bus;
		if (lcd_debug_print_flag)
			lcd_extern_i2c_bus_print(extconf->i2c_bus);
		if ((extcommon->i2c_gpio_sck < LCD_EXTERN_GPIO_NUM_MAX) &&
			(extcommon->i2c_gpio_sda < LCD_EXTERN_GPIO_NUM_MAX)) {
			EXTPR("%s: find spi_gpio config: sck=%d, sda=%d\n",
				extconf->name,
				extcommon->i2c_gpio_sck, extcommon->i2c_gpio_sda);
		}

		propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "cmd_size", NULL);
		if (propdata == NULL) {
			EXTPR("%s: no cmd_size\n", extconf->name);
			extconf->cmd_size = 0;
		} else {
			extconf->cmd_size = (unsigned char)(be32_to_cpup((u32*)propdata));
		}
		if (lcd_debug_print_flag)
			EXTPR("%s: cmd_size=%d\n", extconf->name, extconf->cmd_size);
		if (extconf->cmd_size == 0)
			break;

		if (extconf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			ret = lcd_extern_init_table_dynamic_size_load_dts(
				dt_blob, nodeoffset, extconf, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_dynamic_size_load_dts(
				dt_blob, nodeoffset, extconf, 0);
		} else {
			ret = lcd_extern_init_table_fixed_size_load_dts(
				dt_blob, nodeoffset, extconf, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_fixed_size_load_dts(
				dt_blob, nodeoffset, extconf, 0);
		}
		if (ret == 0)
			extconf->table_init_loaded = 1;
		break;
	case LCD_EXTERN_SPI:
		if ((extcommon->spi_gpio_cs < LCD_EXTERN_GPIO_NUM_MAX) &&
			(extcommon->spi_gpio_clk < LCD_EXTERN_GPIO_NUM_MAX) &&
			(extcommon->spi_gpio_data < LCD_EXTERN_GPIO_NUM_MAX)) {
			EXTPR("%s: find spi_gpio config: cs=%d, clk=%d, data=%d\n",
				extconf->name, extcommon->spi_gpio_cs,
				extcommon->spi_gpio_clk, extcommon->spi_gpio_data);
		} else {
			EXTERR("%s: get spi_gpio failed\n", extconf->name);
		}

		propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "spi_clk_freq", NULL);
		if (propdata == NULL) {
			EXTERR("%s: get spi_clk_freq failed, default to %dKHz\n",
				extconf->name, LCD_EXT_SPI_CLK_FREQ_DFT);
			extconf->spi_clk_freq = LCD_EXT_SPI_CLK_FREQ_DFT;
		} else {
			extconf->spi_clk_freq = be32_to_cpup((u32*)propdata);
		}
		propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "spi_clk_pol", NULL);
		if (propdata == NULL) {
			EXTERR("%s: get spi_clk_pol failed, default to 1\n", extconf->name);
			extconf->spi_clk_pol = 1;
		} else {
			extconf->spi_clk_pol = (unsigned char)(be32_to_cpup((u32*)propdata));
		}
		if (lcd_debug_print_flag) {
			EXTPR("%s: spi clk=%dKHz, clk_pol=%d\n",
				extconf->name, extconf->spi_clk_freq, extconf->spi_clk_pol);
		}

		propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "cmd_size", NULL);
		if (propdata == NULL) {
			EXTPR("%s: no cmd_size\n", extconf->name);
			extconf->cmd_size = 0;
		} else {
			extconf->cmd_size = (unsigned char)(be32_to_cpup((u32*)propdata));
		}
		if (lcd_debug_print_flag)
			EXTPR("%s: cmd_size=%d\n", extconf->name, extconf->cmd_size);
		if (extconf->cmd_size == 0)
			break;

		if (extconf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			ret = lcd_extern_init_table_dynamic_size_load_dts(
				dt_blob, nodeoffset, extconf, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_dynamic_size_load_dts(
				dt_blob, nodeoffset, extconf, 0);
		} else {
			ret = lcd_extern_init_table_fixed_size_load_dts(
				dt_blob, nodeoffset, extconf, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_fixed_size_load_dts(
				dt_blob, nodeoffset, extconf, 0);
		}
		if (ret == 0)
			extconf->table_init_loaded = 1;
		break;
	case LCD_EXTERN_MIPI:
		propdata = (char *)fdt_getprop(dt_blob, nodeoffset, "cmd_size", NULL);
		if (propdata == NULL) {
			EXTPR("%s: no cmd_size\n", extconf->name);
			extconf->cmd_size = 0;
		} else {
			extconf->cmd_size = (unsigned char)(be32_to_cpup((u32*)propdata));
		}
		if (lcd_debug_print_flag)
			EXTPR("%s: cmd_size=%d\n", extconf->name, extconf->cmd_size);
		if (extconf->cmd_size == 0)
			break;

		if (extconf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			ret = lcd_extern_init_table_dynamic_size_load_dts(
				dt_blob, nodeoffset, extconf, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_dynamic_size_load_dts(
				dt_blob, nodeoffset, extconf, 0);
			if (ret == 0)
				extconf->table_init_loaded = 1;
		}
		break;
	default:
		break;
	}

	return 0;
}

static int lcd_extern_init_table_dynamic_size_load_unifykey(
		struct lcd_extern_config_s *extconf, unsigned char *p,
		int key_len, int len, int flag)
{
	unsigned char cmd_size = 0;
	int i = 0, j, max_len, ret = 0;
	unsigned char *table, *buf;
	char propname[20];

	if (flag) {
		table = extconf->table_init_on;
		max_len = LCD_EXTERN_INIT_ON_MAX;
		sprintf(propname, "init_on");
		buf = p;
	} else {
		table = extconf->table_init_off;
		max_len = LCD_EXTERN_INIT_OFF_MAX;
		sprintf(propname, "init_off");
		buf = p + extconf->table_init_on_cnt;
	}
	if (table == NULL) {
		EXTPR("%s init_table is null\n", propname);
		return 0;
	}

	switch (extconf->type) {
	case LCD_EXTERN_I2C:
	case LCD_EXTERN_SPI:
		while ((i + 1) < max_len) {
			/* type */
			len += 1;
			ret = aml_lcd_unifykey_len_check(key_len, len);
			if (ret) {
				EXTERR("%s: get %s failed\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			table[i] = *(buf + LCD_UKEY_EXT_INIT + i);
			/* cmd_size */
			len += 1;
			ret = aml_lcd_unifykey_len_check(key_len, len);
			if (ret) {
				EXTERR("%s: get %s failed\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			table[i+1] = *(buf + LCD_UKEY_EXT_INIT + i + 1);
			cmd_size = table[i+1];

			if (table[i] == LCD_EXT_CMD_TYPE_END)
				break;
			if (cmd_size == 0)
				goto init_table_dynamic_i2c_spi_ukey_next;
			if ((i + 2 + cmd_size) > max_len) {
				EXTERR("%s: %s cmd_size out of support\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}

			/* data */
			len += cmd_size;
			ret = aml_lcd_unifykey_len_check(key_len, len);
			if (ret) {
				EXTERR("%s: get %s failed\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			for (j = 0; j < cmd_size; j++)
				table[i+2+j] = *(buf + LCD_UKEY_EXT_INIT + i + 2 + j);

init_table_dynamic_i2c_spi_ukey_next:
			i += (cmd_size + 2);
		}
		if (flag)
			extconf->table_init_on_cnt = i + 2;
		else
			extconf->table_init_off_cnt = i + 2;
		break;
	case LCD_EXTERN_MIPI:
		while ((i + 1) < max_len) { /* type & cmd_size detect */
			/* type */
			len += 1;
			ret = aml_lcd_unifykey_len_check(key_len, len);
			if (ret) {
				EXTERR("%s: get %s failed\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			table[i] = *(buf + LCD_UKEY_EXT_INIT + i);
			/* type */
			len += 1;
			ret = aml_lcd_unifykey_len_check(key_len, len);
			if (ret) {
				EXTERR("%s: get %s failed\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			table[i+1] = *(buf + LCD_UKEY_EXT_INIT + i + 1);
			cmd_size = table[i+1];

			if (table[i] == LCD_EXT_CMD_TYPE_END) {
				if ((cmd_size == 0xff) || (cmd_size == 0))
					break;
				cmd_size = 0;
			}
			if (cmd_size == 0)
				goto init_table_dynamic_mipi_ukey_next;
			if ((i + 2 + cmd_size) > max_len) {
				EXTERR("%s: %s cmd_size out of support\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				break;
			}

			len += cmd_size;
			ret = aml_lcd_unifykey_len_check(key_len, len);
			if (ret) {
				EXTERR("%s: get %s failed\n", extconf->name, propname);
				table[i] = LCD_EXT_CMD_TYPE_END;
				table[i+1] = 0;
				return -1;
			}
			for (j = 0; j < cmd_size; j++)
				table[i+2+j] = *(buf + LCD_UKEY_EXT_INIT + i + 2 + j);

init_table_dynamic_mipi_ukey_next:
			i += (cmd_size + 2);
		}
		if (flag)
			extconf->table_init_on_cnt = i + 2;
		else
			extconf->table_init_off_cnt = i + 2;
		break;
	default:
		break;
	}

	return 0;
}

static int lcd_extern_init_table_fixed_size_load_unifykey(
		struct lcd_extern_config_s *extconf, unsigned char *p,
		int key_len, int len, int flag)
{
	unsigned char cmd_size;
	int i = 0, j, max_len, ret = 0;
	unsigned char *table, *buf;
	char propname[20];

	cmd_size = extconf->cmd_size;
	if (flag) {
		table = extconf->table_init_on;
		max_len = LCD_EXTERN_INIT_ON_MAX;
		sprintf(propname, "init_on");
		buf = p;
	} else {
		table = extconf->table_init_off;
		max_len = LCD_EXTERN_INIT_OFF_MAX;
		sprintf(propname, "init_off");
		buf = p + extconf->table_init_on_cnt;
	}
	if (table == NULL) {
		EXTPR("%s init_table is null\n", propname);
		return 0;
	}

	while (i < max_len) {
		if ((i + cmd_size) > max_len) {
			EXTERR("%s: %s cmd_size out of support\n", extconf->name, propname);
			table[i] = LCD_EXT_CMD_TYPE_END;
			return -1;
		}
		len += cmd_size;
		ret = aml_lcd_unifykey_len_check(key_len, len);
		if (ret) {
			EXTERR("%s: get %s failed\n", extconf->name, propname);
			table[i] = LCD_EXT_CMD_TYPE_END;
			return -1;
		}
		for (j = 0; j < cmd_size; j++)
			table[i+j] = *(buf + LCD_UKEY_EXT_INIT + i + j);

		if (table[i] == LCD_EXT_CMD_TYPE_END)
			break;

		i += cmd_size;
	}

	if (flag)
		extconf->table_init_on_cnt = i + cmd_size;
	else
		extconf->table_init_off_cnt = i + cmd_size;

	return 0;
}

static int lcd_extern_get_config_unifykey(int index,
		struct lcd_extern_config_s *extconf,
		struct lcd_extern_common_s *extcommon)
{
	unsigned char *para, *p;
	int key_len, len;
	const char *str;
	struct aml_lcd_unifykey_header_s ext_header;
	int ret;

	extconf->table_init_loaded = 0;
	para = (unsigned char *)malloc(sizeof(unsigned char) * LCD_UKEY_LCD_EXT_SIZE);
	if (!para) {
		EXTERR("%s: Not enough memory\n", __func__);
		return -1;
	}
	key_len = LCD_UKEY_LCD_EXT_SIZE;
	memset(para, 0, (sizeof(unsigned char) * key_len));
	ret = aml_lcd_unifykey_get("lcd_extern", para, &key_len);
	if (ret) {
		free(para);
		return -1;
	}

	/* check lcd_extern unifykey length */
	len = 10 + 33 + 10;
	ret = aml_lcd_unifykey_len_check(key_len, len);
	if (ret) {
		EXTERR("unifykey length is not correct\n");
		free(para);
		return -1;
	}

	/* header: 10byte */
	aml_lcd_unifykey_header_check(para, &ext_header);
	if (lcd_debug_print_flag) {
		EXTPR("unifykey header:\n");
		EXTPR("crc32             = 0x%08x\n", ext_header.crc32);
		EXTPR("data_len          = %d\n", ext_header.data_len);
		EXTPR("version           = 0x%04x\n", ext_header.version);
		EXTPR("reserved          = 0x%04x\n", ext_header.reserved);
	}

	/* basic: 33byte */
	p = para;
	*(p + LCD_UKEY_EXT_NAME - 1) = '\0'; /* ensure string ending */
	str = (const char *)(p + LCD_UKEY_HEAD_SIZE);
	strcpy(extconf->name, str);
	extconf->index = *(p + LCD_UKEY_EXT_INDEX);
	extconf->type = *(p + LCD_UKEY_EXT_TYPE);
	extconf->status = *(p + LCD_UKEY_EXT_STATUS);

	if (index != extconf->index) {
		EXTERR("index %d err, unifykey config index %d\n", index, extconf->index);
		free(para);
		return -1;
	}

	/* type: 10byte */
	switch (extconf->type) {
	case LCD_EXTERN_I2C:
		extconf->i2c_addr = *(p + LCD_UKEY_EXT_TYPE_VAL_0);
		extconf->i2c_addr2 = *(p + LCD_UKEY_EXT_TYPE_VAL_1);
		extconf->i2c_bus = extcommon->i2c_bus;
		if (lcd_debug_print_flag)
			lcd_extern_i2c_bus_print(extconf->i2c_bus);
		if ((extcommon->i2c_gpio_sck < LCD_EXTERN_GPIO_NUM_MAX) &&
			(extcommon->i2c_gpio_sda < LCD_EXTERN_GPIO_NUM_MAX)) {
			EXTPR("%s: find spi_gpio config: sck=%d, sda=%d\n",
				extconf->name,
				extcommon->i2c_gpio_sck, extcommon->i2c_gpio_sda);
		}
		extconf->cmd_size = *(p + LCD_UKEY_EXT_TYPE_VAL_3);
		if (lcd_debug_print_flag) {
			EXTPR("%s: cmd_size = %d\n",
				extconf->name, extconf->cmd_size);
		}

		/* init */
		if (extconf->cmd_size == 0)
			break;
		if (extconf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			ret = lcd_extern_init_table_dynamic_size_load_unifykey(
				extconf, p, key_len, len, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_dynamic_size_load_unifykey(
				extconf, p, key_len, len, 0);
		} else {
			ret = lcd_extern_init_table_fixed_size_load_unifykey(
				extconf, p, key_len, len, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_fixed_size_load_unifykey(
				extconf, p, key_len, len, 0);
		}
		if (ret == 0)
			extconf->table_init_loaded = 1;
		break;
	case LCD_EXTERN_SPI:
		if ((extcommon->spi_gpio_cs < LCD_EXTERN_GPIO_NUM_MAX) &&
			(extcommon->spi_gpio_clk < LCD_EXTERN_GPIO_NUM_MAX) &&
			(extcommon->spi_gpio_data < LCD_EXTERN_GPIO_NUM_MAX)) {
			EXTPR("%s: find spi_gpio config: cs=%d, clk=%d, data=%d\n",
				extconf->name, extcommon->spi_gpio_cs,
				extcommon->spi_gpio_clk, extcommon->spi_gpio_data);
		} else {
			EXTERR("%s: get spi_gpio failed\n", extconf->name);
		}
		extconf->spi_clk_freq = (*(p + LCD_UKEY_EXT_TYPE_VAL_3) |
			((*(p + LCD_UKEY_EXT_TYPE_VAL_4)) << 8));
		extconf->spi_clk_pol = *(p + LCD_UKEY_EXT_TYPE_VAL_5);
		extconf->cmd_size = *(p + LCD_UKEY_EXT_TYPE_VAL_6);
		if (lcd_debug_print_flag) {
			EXTPR("%s: cmd_size = %d\n",
				extconf->name, extconf->cmd_size);
		}

		/* init */
		if (extconf->cmd_size == 0)
			break;
		if (extconf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			ret = lcd_extern_init_table_dynamic_size_load_unifykey(
				extconf, p, key_len, len, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_dynamic_size_load_unifykey(
				extconf, p, key_len, len, 0);
		} else {
			ret = lcd_extern_init_table_fixed_size_load_unifykey(
				extconf, p, key_len, len, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_fixed_size_load_unifykey(
				extconf, p, key_len, len, 0);
		}
		if (ret == 0)
			extconf->table_init_loaded = 1;
		break;
	case LCD_EXTERN_MIPI:
		extconf->cmd_size = *(p + LCD_UKEY_EXT_TYPE_VAL_0);
		if (lcd_debug_print_flag) {
			EXTPR("%s: cmd_size = %d\n",
				extconf->name, extconf->cmd_size);
		}

		if (extconf->cmd_size == 0)
			break;
		if (extconf->cmd_size == LCD_EXT_CMD_SIZE_DYNAMIC) {
			ret = lcd_extern_init_table_dynamic_size_load_unifykey(
				extconf, p, key_len, len, 1);
			if (ret)
				break;
			ret = lcd_extern_init_table_dynamic_size_load_unifykey(
				extconf, p, key_len, len, 0);
		}
		if (ret == 0)
			extconf->table_init_loaded = 1;
		break;
	default:
		break;
	}

	free(para);
	return 0;
}

static int lcd_extern_get_init_default(const void *dt_blob,
		struct lcd_extern_common_s *extcommon)
{
	int i = 0;

	while (i < LCD_EXTERN_GPIO_NUM_MAX) {
		if (strcmp(extcommon->gpio_name[i], "invalid") == 0)
			break;
		lcd_ext_gpio_probe(extcommon->gpio_name[i], i);
		i++;
	}

	return 0;
}

static int lcd_extern_add_i2c(struct aml_lcd_extern_driver_s *ext_drv)
{
	int ret = -1;

	if (strcmp(ext_drv->config->name, "ext_default") == 0) {
		if (ext_drv->config->cmd_size < 2) {
			EXTERR("%s: cmd_size %d is invalid\n",
				ext_drv->config->name, ext_drv->config->cmd_size);
		} else {
			ret = lcd_extern_default_probe(ext_drv);
		}
	} else if (strcmp(ext_drv->config->name, "i2c_T5800Q") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_T5800Q
		ret = lcd_extern_i2c_T5800Q_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "i2c_DLPC3439") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_DLPC3439
		ret = lcd_extern_i2c_DLPC3439_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "i2c_RT6947") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_RT6947
		ret = lcd_extern_i2c_RT6947_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "i2c_ANX6862_7911") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_ANX6862_7911
		ret = lcd_extern_i2c_ANX6862_7911_probe(ext_drv);
#endif
	} else {
		EXTERR("invalid driver name: %s\n", ext_drv->config->name);
	}

	return ret;
}

static int lcd_extern_add_spi(struct aml_lcd_extern_driver_s *ext_drv)
{
	int ret = -1;

	if (strcmp(ext_drv->config->name, "ext_default") == 0) {
		if (ext_drv->config->cmd_size < 2) {
			EXTERR("%s: cmd_size %d is invalid\n",
				ext_drv->config->name, ext_drv->config->cmd_size);
		} else {
			ret = lcd_extern_default_probe(ext_drv);
		}
	} else if (strcmp(ext_drv->config->name, "spi_LD070WS2") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_SPI_LD070WS2
		ret = lcd_extern_spi_LD070WS2_probe(ext_drv);
#endif
	} else {
		EXTERR("invalid driver name: %s\n", ext_drv->config->name);
	}

	return ret;
}

static int lcd_extern_add_mipi(struct aml_lcd_extern_driver_s *ext_drv)
{
	int ret = -1;

	if ((strcmp(ext_drv->config->name, "mipi_default") == 0) ||
		strcmp(ext_drv->config->name, "ext_default") == 0) {
		if (ext_drv->config->cmd_size != LCD_EXT_CMD_SIZE_DYNAMIC) {
			EXTERR("%s: cmd_size %d is invalid\n",
				ext_drv->config->name, ext_drv->config->cmd_size);
		} else {
			ret = lcd_extern_mipi_default_probe(ext_drv);
		}
	} else if (strcmp(ext_drv->config->name, "mipi_TV070WSM") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_TV070WSM
		ret = lcd_extern_mipi_TV070WSM_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "mipi_P070ACB") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_P070ACB
		ret = lcd_extern_mipi_p070acb_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "mipi_ST7701") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_ST7701
		ret = lcd_extern_mipi_st7701_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "mipi_TL050FHV02CT") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_TL050FHV02CT
		ret = lcd_extern_mipi_tl050fhv02ct_probe(ext_drv);
#endif
	} else {
		EXTERR("invalid driver name: %s\n", ext_drv->config->name);
	}

	return ret;
}

static int lcd_extern_add_driver(struct lcd_extern_config_s *extconf,
		struct lcd_extern_common_s *extcommon)
{
	struct aml_lcd_extern_driver_s *ext_drv;
	int ret = -1;

	if (extconf->status == 0) {
		EXTERR("%s(%d) is disabled\n", extconf->name, extconf->index);
		return -1;
	}
	lcd_ext_driver = (struct aml_lcd_extern_driver_s *)malloc(
		sizeof(struct aml_lcd_extern_driver_s));
	if (lcd_ext_driver == NULL) {
		EXTERR("failed to alloc driver %s[%d], not enough memory\n",
			extconf->name, extconf->index);
		return -1;
	}

	/* fill config parameters */
	ext_drv = lcd_ext_driver;
	ext_drv->config = extconf;
	ext_drv->common = extcommon;
	ext_drv->info_print = lcd_extern_info_print;
	ext_drv->reg_read  = NULL;
	ext_drv->reg_write = NULL;
	ext_drv->power_on  = NULL;
	ext_drv->power_off = NULL;

	/* fill config parameters by different type */
	switch (ext_drv->config->type) {
	case LCD_EXTERN_I2C:
		ret = lcd_extern_add_i2c(ext_drv);
		break;
	case LCD_EXTERN_SPI:
		ret = lcd_extern_add_spi(ext_drv);
		break;
	case LCD_EXTERN_MIPI:
		ret = lcd_extern_add_mipi(ext_drv);
		break;
	default:
		ret = -1;
		EXTERR("don't support type %d\n", ext_drv->config->type);
		break;
	}
	if (ret) {
		EXTERR("add driver failed\n");
		free(lcd_ext_driver);
		lcd_ext_driver = NULL;
		return -1;
	}

	EXTPR("add driver %s(%d)\n", ext_drv->config->name, ext_drv->config->index);
	return ret;
}

static int lcd_extern_add_driver_default(int index,
		struct lcd_extern_config_s *extconf,
		struct lcd_extern_common_s *extcommon)
{
	int drv_index = extconf->index;
	int ret = -1;
	struct aml_lcd_extern_driver_s *ext_drv;

	if (index != drv_index) {
		EXTERR("index %d err, default config index %d\n", index, drv_index);
		return -1;
	}

	if (extconf->status == 0) {
		EXTERR("%s(%d) is disabled\n", extconf->name, drv_index);
		return -1;
	}

	lcd_ext_driver = (struct aml_lcd_extern_driver_s *)malloc(
		sizeof(struct aml_lcd_extern_driver_s));
	if (lcd_ext_driver == NULL) {
		EXTERR("failed to alloc driver %d, not enough memory\n", index);
		return -1;
	}

	ext_drv = lcd_ext_driver;
	ext_drv->config = extconf;
	ext_drv->common = extcommon;
	ext_drv->config->table_init_loaded = 1;
	ext_drv->info_print  = lcd_extern_info_print;
	ext_drv->reg_read  = NULL;
	ext_drv->reg_write = NULL;
	ext_drv->power_on  = NULL;
	ext_drv->power_off = NULL;

	/* add ext_default driver */
	if (strcmp(ext_drv->config->name, "ext_default") == 0) {
		ret = lcd_extern_default_probe(ext_drv);
	} else if ((strcmp(ext_drv->config->name, "mipi_default") == 0) ||
		(strcmp(ext_drv->config->name, "ext_default") == 0)) {
		ret = lcd_extern_mipi_default_probe(ext_drv);
	} else if (strcmp(ext_drv->config->name, "i2c_T5800Q") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_T5800Q
		ret = lcd_extern_i2c_T5800Q_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "i2c_DLPC3439") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_DLPC3439
		ret = lcd_extern_i2c_DLPC3439_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "i2c_RT6947") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_RT6947
		ret = lcd_extern_i2c_RT6947_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "i2c_ANX6862_7911") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_I2C_ANX6862_7911
		ret = lcd_extern_i2c_ANX6862_7911_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "spi_LD070WS2") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_SPI_LD070WS2
		ret = lcd_extern_spi_LD070WS2_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "mipi_TV070WSM") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_TV070WSM
		ret = lcd_extern_mipi_TV070WSM_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "mipi_P070ACB") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_P070ACB
		ret = lcd_extern_mipi_p070acb_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "mipi_ST7701") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_ST7701
		ret = lcd_extern_mipi_st7701_probe(ext_drv);
#endif
	} else if (strcmp(ext_drv->config->name, "mipi_TL050FHV02CT") == 0) {
#ifdef CONFIG_AML_LCD_EXTERN_MIPI_TL050FHV02CT
		ret = lcd_extern_mipi_tl050fhv02ct_probe(ext_drv);
#endif
	} else {
		EXTERR("invalid driver name: %s\n", ext_drv->config->name);
	}

	if (ret) {
		EXTERR("add default driver failed: %s(%d)\n", ext_drv->config->name, index);
		free(lcd_ext_driver);
		lcd_ext_driver = NULL;
		return -1;
	}
	EXTPR("add default driver: %s(%d)\n", ext_drv->config->name, index);
	return ret;
}

int aml_lcd_extern_probe(const void *dt_blob, int index)
{
	struct aml_lcd_drv_s *lcd_drv = aml_lcd_get_driver();
	struct lcd_extern_config_s *ext_config;
	struct lcd_extern_common_s *ext_common;
	int ret, load_id = 0;

	if (index >= LCD_EXTERN_INDEX_INVALID) {
		EXTERR("invalid index, %s exit\n", __func__);
		return -1;
	}

	ext_dt_blob = NULL;
	ext_common = &ext_common_dft;
	ext_config = &ext_config_dtf;

	/* check dts config */
	if (dt_blob)
		ext_dt_blob = dt_blob;
	ret = fdt_check_header(ext_dt_blob);
	if (ret) {
		EXTERR("check dts: %s, use default parameters\n",
			fdt_strerror(ret));
	} else {
		load_id = 1;
	}

	if (lcd_debug_load_flag)
		load_id = 0;

	switch (load_id) {
	case 1: /* dts */
		ext_config->table_init_on_cnt = 0;
		ext_config->table_init_off_cnt = 0;
		ext_config->table_init_loaded = 0;

		lcd_extern_get_init_dts(ext_dt_blob, ext_common);
		if (lcd_drv->unifykey_test_flag) {
			ext_common->lcd_ext_key_valid = 1;
			LCDPR("force lcd_ext_key_valid to 1\n");
		}
		/* check unifykey config */
		if (ext_common->lcd_ext_key_valid) {
			ret = aml_lcd_unifykey_check("lcd_extern");
			if (ret == 0) {
				EXTPR("load config from unifykey\n");
				ret = lcd_extern_get_config_unifykey(index,
					ext_config, ext_common);
			}
		} else {
			EXTPR("load config from dts\n");
			ret = lcd_extern_get_config_dts(ext_dt_blob, index,
				ext_config, ext_common);
		}
		if (ret == 0)
			ret = lcd_extern_add_driver(ext_config, ext_common);
		break;
	default: /* default */
		ext_config->table_init_loaded = 0;
		ext_config->i2c_bus = ext_common->i2c_bus;

		lcd_extern_get_init_default(ext_dt_blob, ext_common);
		if (lcd_drv->unifykey_test_flag) {
			ext_common->lcd_ext_key_valid = 1;
			LCDPR("force lcd_ext_key_valid to 1\n");
		}
		if (ext_common->lcd_ext_key_valid) {
			ret = aml_lcd_unifykey_check("lcd_extern");
			if (ret == 0) {
				EXTPR("load config from unifykey\n");
				ret = lcd_extern_get_config_unifykey(index,
					ext_config, ext_common);
				if (ret == 0)
					ret = lcd_extern_add_driver(ext_config, ext_common);
			}
		} else {
			EXTPR("load config from bsp\n");
			ret = lcd_extern_add_driver_default(index, ext_config, ext_common);
		}
		break;
	}

	EXTPR("%s %s\n", __func__, (ret ? "failed" : "ok"));
	return ret;
}

int aml_lcd_extern_remove(void)
{
	if (lcd_ext_driver)
		free(lcd_ext_driver);
	lcd_ext_driver = NULL;
	return 0;
}

