/*
 * drivers/amlogic/media/vout/lcd/lcd_extern/mipi_ST7701.c
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
#include <asm/arch/gpio.h>
#include <fdtdec.h>
#include <amlogic/media/vout/lcd/aml_lcd.h>
#include <amlogic/media/vout/lcd/lcd_extern.h>
#include "lcd_extern.h"

#define LCD_EXTERN_NAME			"mipi_ST7701"
#define LCD_EXTERN_TYPE			LCD_EXTERN_MIPI

/******************** mipi command ********************/
/* format:  data_type, cmd_size, data.... */
/* 	data_type=0xff,
 *		0 < cmd_size < 0xff means delay ms,
 *		cmd_size=0 or 0xff means ending.
 *	data_type=0xf0, for gpio control
 *		data0=gpio_index, data1=gpio_value.
 *		data0=gpio_index, data1=gpio_value, data2=delay.
 *	data_type=0xfd, for delay ms
 *		data0=delay, data_1=delay, ..., data_n=delay.
 */
//******************************************************//
static unsigned char mipi_init_on_table[] = {
	0x13, 1, 0x11,
	//0x13, 1, 0x21,
	//0x23, 2, 0x36, 0x00,
	0xfd, 1, 200,     /* delay(ms) */
	0x29, 6, 0xff, 0x77, 0x01, 0x00, 0x00, 0x10,
	0x29, 3, 0xc0, 0xe9, 0x03,
	0x29, 3, 0xc1, 0x11, 0x02,
	0x29, 3, 0xc2, 0x31, 0x08,
	0x29, 17, 0xb0, 0x00, 0x06, 0x11, 0x12, 0x18, 0x0a, 0x0a, 0x09, 0x09, 0x1d, 0x09, 0x14, 0x10, 0x0e, 0x11, 0x19,
	0x29, 17, 0xb1, 0x00, 0x06, 0x11, 0x11, 0x15, 0x09, 0x0b, 0x09, 0x09, 0x23, 0x09, 0x17, 0x14, 0x18, 0x1e, 0x19,
	0x29, 6, 0xff, 0x77, 0x01, 0x00, 0x00, 0x11,
	0x23, 2, 0xb0, 0x4d,

	//-------------------------------------------Vcom Setting----------------
	0x23, 2, 0xb1, 0x3a,

	//-----------------------------------------End Vcom Setting--------------
	0x23, 2, 0xb2, 0x07,
	0x23, 2, 0xb3, 0x80,
	0x23, 2, 0xb5, 0x47,
	0x23, 2, 0xb7, 0x8a,
	0x23, 2, 0xb8, 0x21,
	0x23, 2, 0xc1, 0x78,
	0x23, 2, 0xc2, 0x78,
	0x23, 2, 0xd0, 0x88,

	//---------------------------------End Power Control Registers Initial --
	0xfd, 1, 100,     /* delay(ms) */

	//---------------------------------------------GIP Setting---------------
	0x29, 4, 0xe0, 0x00, 0x00, 0x02,
	0x29, 12, 0xe1, 0x08, 0x00, 0x0a, 0x00, 0x07, 0x00, 0x09, 0x00, 0x00, 0x33, 0x33,
	0x29, 14, 0xe2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x29, 5, 0xe3, 0x00, 0x00, 0x33, 0x33,
	0x29, 3, 0xe4, 0x44, 0x44,
	0x29, 17, 0xe5, 0x0e, 0x60, 0xaf, 0xaf, 0x10, 0x60, 0xaf, 0xaf, 0x0a, 0x60, 0xaf, 0xaf, 0x0c, 0x60, 0xaf, 0xaf,
	0x29, 5, 0xe6, 0x00, 0x00, 0x33, 0x33,
	0x29, 3, 0xe7, 0x44, 0x44,
	0x29, 17, 0xe8, 0x0d, 0x60, 0xa0, 0xa0, 0x0f, 0x60, 0xaf, 0xaf, 0x09, 0x60, 0xaf, 0xaf, 0x0b, 0x60, 0xaf, 0xaf,
	0x29, 8, 0xeb, 0x02, 0x01, 0xe4, 0xe4, 0x44, 0x00, 0x40,
	0x29, 3, 0xec, 0x02, 0x01,
	0x29, 17, 0xed, 0xab, 0x89, 0x76, 0x54, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10, 0x45, 0x67, 0x98, 0xba,

	//------------------------------ Power Control Registers Initial End-----
	0xfd, 1, 10,     /* delay(ms) */
	0x29, 6, 0xff, 0x77, 0x01, 0x00, 0x00, 0x00,
	0x13, 1, 0x29,
	//0x13, 1, 0x2c,
	0xfd, 1, 200,    /* delay(ms) */
	0xff, 0,   /* ending */
};

static unsigned char mipi_init_off_table[] = {
	0x05, 1, 0x28, /* display off */
	0xfd, 1, 10,   /* delay 10ms */
	0x05, 1, 0x10, /* sleep in */
	0xfd, 1, 150,  /* delay 150ms */
	0xff, 0,   /* ending */
};

static int lcd_extern_driver_update(struct aml_lcd_extern_driver_s *ext_drv)
{
	if (ext_drv == NULL) {
		EXTERR("%s driver is null\n", LCD_EXTERN_NAME);
		return -1;
	}

	ext_drv->config->cmd_size = LCD_EXT_CMD_SIZE_DYNAMIC;
	ext_drv->config->table_init_on  = &mipi_init_on_table[0];
	ext_drv->config->table_init_on_cnt  = sizeof(mipi_init_on_table);
	ext_drv->config->table_init_off = &mipi_init_off_table[0];
	ext_drv->config->table_init_off_cnt  = sizeof(mipi_init_off_table);

	return 0;
}

int lcd_extern_mipi_st7701_probe(struct aml_lcd_extern_driver_s *ext_drv)
{
	int ret = 0;

	ret = lcd_extern_driver_update(ext_drv);

	if (lcd_debug_print_flag)
		EXTPR("%s: %d\n", __func__, ret);
	return ret;
}
