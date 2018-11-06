/*
 * drivers/amlogic/media/vout/lcd/lcd_extern/mipi_TL050FHV02CT.c
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

#define LCD_EXTERN_NAME			"mipi_TL050FHV02CT"
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
	//LCD driver initialization
	0x23, 2, 0XFF, 0X05,
	0x23, 2, 0XFB, 0X01,
	0x23, 2, 0XC5, 0X01, //TURN ON
	0xfd, 1, 100,

	//AUO4.97+NT35596_intial
	0x23, 2, 0XFF, 0XEE, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0X1F, 0X45,
	0x23, 2, 0X24, 0X4F,
	0x23, 2, 0X38, 0XC8,
	0x23, 2, 0X39, 0X2C,
	0x23, 2, 0X1E, 0XBB,
	0x23, 2, 0X1D, 0X0F,
	0x23, 2, 0X7E, 0XB1,

	0x23, 2, 0XFF, 0X00, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0X35, 0X01,

	0x23, 2, 0XFF, 0X01, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0X00, 0X01,
	0x23, 2, 0X01, 0X55,
	0x23, 2, 0X02, 0X40,
	0x23, 2, 0X05, 0X40,
	0x23, 2, 0X06, 0X4A,
	0x23, 2, 0X07, 0X24,
	0x23, 2, 0X08, 0X0C,
	0x23, 2, 0X0B, 0X87,
	0x23, 2, 0X0C, 0X87,
	0x23, 2, 0X0E, 0XB0,
	0x23, 2, 0X0F, 0XB3,
	0x23, 2, 0X11, 0X10,
	0x23, 2, 0X12, 0X10,
	0x23, 2, 0X13, 0X05,
	0x23, 2, 0X14, 0X4A,
	0x23, 2, 0X15, 0X18,
	0x23, 2, 0X16, 0X18,
	0x23, 2, 0X18, 0X00,
	0x23, 2, 0X19, 0X77,
	0x23, 2, 0X1A, 0X55,
	0x23, 2, 0X1B, 0X13,
	0x23, 2, 0X1C, 0X00,
	0x23, 2, 0X1D, 0X00,
	0x23, 2, 0X1E, 0X13,
	0x23, 2, 0X1F, 0X00,
	0x23, 2, 0X23, 0X00,
	0x23, 2, 0X24, 0X00,
	0x23, 2, 0X25, 0X00,
	0x23, 2, 0X26, 0X00,
	0x23, 2, 0X27, 0X00,
	0x23, 2, 0X28, 0X00,
	0x23, 2, 0X35, 0X00,
	0x23, 2, 0X66, 0X00,
	0x23, 2, 0X58, 0X82,
	0x23, 2, 0X59, 0X02,
	0x23, 2, 0X5A, 0X02,
	0x23, 2, 0X5B, 0X02,
	0x23, 2, 0X5C, 0X82,
	0x23, 2, 0X5D, 0X82,
	0x23, 2, 0X5E, 0X02,
	0x23, 2, 0X5F, 0X02,
	0x23, 2, 0X72, 0X31,

	0x23, 2, 0XFF, 0X05, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0X00, 0X01,
	0x23, 2, 0X01, 0X0B,
	0x23, 2, 0X02, 0X0C,
	0x23, 2, 0X03, 0X09,
	0x23, 2, 0X04, 0X0A,
	0x23, 2, 0X05, 0X00,
	0x23, 2, 0X06, 0X0F,
	0x23, 2, 0X07, 0X10,
	0x23, 2, 0X08, 0X00,
	0x23, 2, 0X09, 0X00,
	0x23, 2, 0X0A, 0X00,
	0x23, 2, 0X0B, 0X00,
	0x23, 2, 0X0C, 0X00,
	0x23, 2, 0X0D, 0X13,
	0x23, 2, 0X0E, 0X15,
	0x23, 2, 0X0F, 0X17,
	0x23, 2, 0X10, 0X01,
	0x23, 2, 0X11, 0X0B,
	0x23, 2, 0X12, 0X0C,
	0x23, 2, 0X13, 0X09,
	0x23, 2, 0X14, 0X0A,
	0x23, 2, 0X15, 0X00,
	0x23, 2, 0X16, 0X0F,
	0x23, 2, 0X17, 0X10,
	0x23, 2, 0X18, 0X00,
	0x23, 2, 0X19, 0X00,
	0x23, 2, 0X1A, 0X00,
	0x23, 2, 0X1B, 0X00,
	0x23, 2, 0X1C, 0X00,
	0x23, 2, 0X1D, 0X13,
	0x23, 2, 0X1E, 0X15,
	0x23, 2, 0X1F, 0X17,
	0x23, 2, 0X20, 0X00,
	0x23, 2, 0X21, 0X03,
	0x23, 2, 0X22, 0X01,
	0x23, 2, 0X23, 0X40,
	0x23, 2, 0X24, 0X40,
	0x23, 2, 0X25, 0XED,
	0x23, 2, 0X29, 0X58,
	0x23, 2, 0X2A, 0X12,
	0x23, 2, 0X2B, 0X01,
	0x23, 2, 0X4B, 0X06,
	0x23, 2, 0X4C, 0X11,
	0x23, 2, 0X4D, 0X20,
	0x23, 2, 0X4E, 0X02,
	0x23, 2, 0X4F, 0X02,
	0x23, 2, 0X50, 0X20,
	0x23, 2, 0X51, 0X61,
	0x23, 2, 0X52, 0X01,
	0x23, 2, 0X53, 0X63,
	0x23, 2, 0X54, 0X77,
	0x23, 2, 0X55, 0XED,
	0x23, 2, 0X5B, 0X00,
	0x23, 2, 0X5C, 0X00,
	0x23, 2, 0X5D, 0X00,
	0x23, 2, 0X5E, 0X00,
	0x23, 2, 0X5F, 0X15,
	0x23, 2, 0X60, 0X75,
	0x23, 2, 0X61, 0X00,
	0x23, 2, 0X62, 0X00,
	0x23, 2, 0X63, 0X00,
	0x23, 2, 0X64, 0X00,
	0x23, 2, 0X65, 0X00,
	0x23, 2, 0X66, 0X00,
	0x23, 2, 0X67, 0X00,
	0x23, 2, 0X68, 0X04,
	0x23, 2, 0X69, 0X00,
	0x23, 2, 0X6A, 0X00,
	0x23, 2, 0X6C, 0X40,
	0x23, 2, 0X75, 0X01,
	0x23, 2, 0X76, 0X01,
	0x23, 2, 0X7A, 0X80,
	0x23, 2, 0X7B, 0XC5,
	0x23, 2, 0X7C, 0XD8,
	0x23, 2, 0X7D, 0X60,
	0x23, 2, 0X7F, 0X15,
	0x23, 2, 0X80, 0X81,
	0x23, 2, 0X83, 0X05,
	0x23, 2, 0X93, 0X08,
	0x23, 2, 0X94, 0X10,
	0x23, 2, 0X8A, 0X00,
	0x23, 2, 0X9B, 0X0F,
	0x23, 2, 0XEA, 0XFF,
	0x23, 2, 0XEC, 0X00,

	0x23, 2, 0XFF, 0X01, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0X75, 0X00, //Gamma R+
	0x23, 2, 0X76, 0X18,
	0x23, 2, 0X77, 0X00,
	0x23, 2, 0X78, 0X38,
	0x23, 2, 0X79, 0X00,
	0x23, 2, 0X7A, 0X65,
	0x23, 2, 0X7B, 0X00,
	0x23, 2, 0X7C, 0X84,
	0x23, 2, 0X7D, 0X00,
	0x23, 2, 0X7E, 0X9B,
	0x23, 2, 0X7F, 0X00,
	0x23, 2, 0X80, 0XAF,
	0x23, 2, 0X81, 0X00,
	0x23, 2, 0X82, 0XC1,
	0x23, 2, 0X83, 0X00,
	0x23, 2, 0X84, 0XD2,
	0x23, 2, 0X85, 0X00,
	0x23, 2, 0X86, 0XDF,
	0x23, 2, 0X87, 0X01,
	0x23, 2, 0X88, 0X11,
	0x23, 2, 0X89, 0X01,
	0x23, 2, 0X8A, 0X38,
	0x23, 2, 0X8B, 0X01,
	0x23, 2, 0X8C, 0X76,
	0x23, 2, 0X8D, 0X01,
	0x23, 2, 0X8E, 0XA7,
	0x23, 2, 0X8F, 0X01,
	0x23, 2, 0X90, 0XF3,
	0x23, 2, 0X91, 0X02,
	0x23, 2, 0X92, 0X2F,
	0x23, 2, 0X93, 0X02,
	0x23, 2, 0X94, 0X30,
	0x23, 2, 0X95, 0X02,
	0x23, 2, 0X96, 0X66,
	0x23, 2, 0X97, 0X02,
	0x23, 2, 0X98, 0XA0,
	0x23, 2, 0X99, 0X02,
	0x23, 2, 0X9A, 0XC5,
	0x23, 2, 0X9B, 0X02,
	0x23, 2, 0X9C, 0XF8,
	0x23, 2, 0X9D, 0X03,
	0x23, 2, 0X9E, 0X1B,
	0x23, 2, 0X9F, 0X03,
	0x23, 2, 0XA0, 0X46,
	0x23, 2, 0XA2, 0X03,
	0x23, 2, 0XA3, 0X52,
	0x23, 2, 0XA4, 0X03,
	0x23, 2, 0XA5, 0X62,
	0x23, 2, 0XA6, 0X03,
	0x23, 2, 0XA7, 0X71,
	0x23, 2, 0XA9, 0X03,
	0x23, 2, 0XAA, 0X83,
	0x23, 2, 0XAB, 0X03,
	0x23, 2, 0XAC, 0X94,
	0x23, 2, 0XAD, 0X03,
	0x23, 2, 0XAE, 0XA3,
	0x23, 2, 0XAF, 0X03,
	0x23, 2, 0XB0, 0XAD,
	0x23, 2, 0XB1, 0X03,
	0x23, 2, 0XB2, 0XCC,

	0x23, 2, 0XB3, 0X00, //Gamma R-
	0x23, 2, 0XB4, 0X18,
	0x23, 2, 0XB5, 0X00,
	0x23, 2, 0XB6, 0X38,
	0x23, 2, 0XB7, 0X00,
	0x23, 2, 0XB8, 0X65,
	0x23, 2, 0XB9, 0X00,
	0x23, 2, 0XBA, 0X84,
	0x23, 2, 0XBB, 0X00,
	0x23, 2, 0XBC, 0X9B,
	0x23, 2, 0XBD, 0X00,
	0x23, 2, 0XBE, 0XAF,
	0x23, 2, 0XBF, 0X00,
	0x23, 2, 0XC0, 0XC1,
	0x23, 2, 0XC1, 0X00,
	0x23, 2, 0XC2, 0XD2,
	0x23, 2, 0XC3, 0X00,
	0x23, 2, 0XC4, 0XDF,
	0x23, 2, 0XC5, 0X01,
	0x23, 2, 0XC6, 0X11,
	0x23, 2, 0XC7, 0X01,
	0x23, 2, 0XC8, 0X38,
	0x23, 2, 0XC9, 0X01,
	0x23, 2, 0XCA, 0X76,
	0x23, 2, 0XCB, 0X01,
	0x23, 2, 0XCC, 0XA7,
	0x23, 2, 0XCD, 0X01,
	0x23, 2, 0XCE, 0XF3,
	0x23, 2, 0XCF, 0X02,
	0x23, 2, 0XD0, 0X2F,
	0x23, 2, 0XD1, 0X02,
	0x23, 2, 0XD2, 0X30,
	0x23, 2, 0XD3, 0X02,
	0x23, 2, 0XD4, 0X66,
	0x23, 2, 0XD5, 0X02,
	0x23, 2, 0XD6, 0XA0,
	0x23, 2, 0XD7, 0X02,
	0x23, 2, 0XD8, 0XC5,
	0x23, 2, 0XD9, 0X02,
	0x23, 2, 0XDA, 0XF8,
	0x23, 2, 0XDB, 0X03,
	0x23, 2, 0XDC, 0X1B,
	0x23, 2, 0XDD, 0X03,
	0x23, 2, 0XDE, 0X46,
	0x23, 2, 0XDF, 0X03,
	0x23, 2, 0XE0, 0X52,
	0x23, 2, 0XE1, 0X03,
	0x23, 2, 0XE2, 0X62,
	0x23, 2, 0XE3, 0X03,
	0x23, 2, 0XE4, 0X71,
	0x23, 2, 0XE5, 0X03,
	0x23, 2, 0XE6, 0X83,
	0x23, 2, 0XE7, 0X03,
	0x23, 2, 0XE8, 0X94,
	0x23, 2, 0XE9, 0X03,
	0x23, 2, 0XEA, 0XA3,
	0x23, 2, 0XEB, 0X03,
	0x23, 2, 0XEC, 0XAD,
	0x23, 2, 0XED, 0X03,
	0x23, 2, 0XEE, 0XCC,

	0x23, 2, 0XEF, 0X00, //Gamma G+
	0x23, 2, 0XF0, 0X18,
	0x23, 2, 0XF1, 0X00,
	0x23, 2, 0XF2, 0X38,
	0x23, 2, 0XF3, 0X00,
	0x23, 2, 0XF4, 0X65,
	0x23, 2, 0XF5, 0X00,
	0x23, 2, 0XF6, 0X84,
	0x23, 2, 0XF7, 0X00,
	0x23, 2, 0XF8, 0X9B,
	0x23, 2, 0XF9, 0X00,
	0x23, 2, 0XFA, 0XAF,
	0x23, 2, 0XFF, 0X02, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0X00, 0X00,
	0x23, 2, 0X01, 0XC1,
	0x23, 2, 0X02, 0X00,
	0x23, 2, 0X03, 0XD2,
	0x23, 2, 0X04, 0X00,
	0x23, 2, 0X05, 0XDF,
	0x23, 2, 0X06, 0X01,
	0x23, 2, 0X07, 0X11,
	0x23, 2, 0X08, 0X01,
	0x23, 2, 0X09, 0X38,
	0x23, 2, 0X0A, 0X01,
	0x23, 2, 0X0B, 0X76,
	0x23, 2, 0X0C, 0X01,
	0x23, 2, 0X0D, 0XA7,
	0x23, 2, 0X0E, 0X01,
	0x23, 2, 0X0F, 0XF3,
	0x23, 2, 0X10, 0X02,
	0x23, 2, 0X11, 0X2F,
	0x23, 2, 0X12, 0X02,
	0x23, 2, 0X13, 0X30,
	0x23, 2, 0X14, 0X02,
	0x23, 2, 0X15, 0X66,
	0x23, 2, 0X16, 0X02,
	0x23, 2, 0X17, 0XA0,
	0x23, 2, 0X18, 0X02,
	0x23, 2, 0X19, 0XC5,
	0x23, 2, 0X1A, 0X02,
	0x23, 2, 0X1B, 0XF8,
	0x23, 2, 0X1C, 0X03,
	0x23, 2, 0X1D, 0X1B,
	0x23, 2, 0X1E, 0X03,
	0x23, 2, 0X1F, 0X46,
	0x23, 2, 0X20, 0X03,
	0x23, 2, 0X21, 0X52,
	0x23, 2, 0X22, 0X03,
	0x23, 2, 0X23, 0X62,
	0x23, 2, 0X24, 0X03,
	0x23, 2, 0X25, 0X71,
	0x23, 2, 0X26, 0X03,
	0x23, 2, 0X27, 0X83,
	0x23, 2, 0X28, 0X03,
	0x23, 2, 0X29, 0X94,
	0x23, 2, 0X2A, 0X03,
	0x23, 2, 0X2B, 0XA3,
	0x23, 2, 0X2D, 0X03,
	0x23, 2, 0X2F, 0XAD,
	0x23, 2, 0X30, 0X03,
	0x23, 2, 0X31, 0XCC,

	0x23, 2, 0X32, 0X00, //Gamma G-
	0x23, 2, 0X33, 0X18,
	0x23, 2, 0X34, 0X00,
	0x23, 2, 0X35, 0X38,
	0x23, 2, 0X36, 0X00,
	0x23, 2, 0X37, 0X65,
	0x23, 2, 0X38, 0X00,
	0x23, 2, 0X39, 0X84,
	0x23, 2, 0X3A, 0X00,
	0x23, 2, 0X3B, 0X9B,
	0x23, 2, 0X3D, 0X00,
	0x23, 2, 0X3F, 0XAF,
	0x23, 2, 0X40, 0X00,
	0x23, 2, 0X41, 0XC1,
	0x23, 2, 0X42, 0X00,
	0x23, 2, 0X43, 0XD2,
	0x23, 2, 0X44, 0X00,
	0x23, 2, 0X45, 0XDF,
	0x23, 2, 0X46, 0X01,
	0x23, 2, 0X47, 0X11,
	0x23, 2, 0X48, 0X01,
	0x23, 2, 0X49, 0X38,
	0x23, 2, 0X4A, 0X01,
	0x23, 2, 0X4B, 0X76,
	0x23, 2, 0X4C, 0X01,
	0x23, 2, 0X4D, 0XA7,
	0x23, 2, 0X4E, 0X01,
	0x23, 2, 0X4F, 0XF3,
	0x23, 2, 0X50, 0X02,
	0x23, 2, 0X51, 0X2F,
	0x23, 2, 0X52, 0X02,
	0x23, 2, 0X53, 0X30,
	0x23, 2, 0X54, 0X02,
	0x23, 2, 0X55, 0X66,
	0x23, 2, 0X56, 0X02,
	0x23, 2, 0X58, 0XA0,
	0x23, 2, 0X59, 0X02,
	0x23, 2, 0X5A, 0XC5,
	0x23, 2, 0X5B, 0X02,
	0x23, 2, 0X5C, 0XF8,
	0x23, 2, 0X5D, 0X03,
	0x23, 2, 0X5E, 0X1B,
	0x23, 2, 0X5F, 0X03,
	0x23, 2, 0X60, 0X46,
	0x23, 2, 0X61, 0X03,
	0x23, 2, 0X62, 0X52,
	0x23, 2, 0X63, 0X03,
	0x23, 2, 0X64, 0X62,
	0x23, 2, 0X65, 0X03,
	0x23, 2, 0X66, 0X71,
	0x23, 2, 0X67, 0X03,
	0x23, 2, 0X68, 0X83,
	0x23, 2, 0X69, 0X03,
	0x23, 2, 0X6A, 0X94,
	0x23, 2, 0X6B, 0X03,
	0x23, 2, 0X6C, 0XA3,
	0x23, 2, 0X6D, 0X03,
	0x23, 2, 0X6E, 0XAD,
	0x23, 2, 0X6F, 0X03,
	0x23, 2, 0X70, 0XCC,

	0x23, 2, 0X71, 0X00, //Gamma B+
	0x23, 2, 0X72, 0X18,
	0x23, 2, 0X73, 0X00,
	0x23, 2, 0X74, 0X38,
	0x23, 2, 0X75, 0X00,
	0x23, 2, 0X76, 0X65,
	0x23, 2, 0X77, 0X00,
	0x23, 2, 0X78, 0X84,
	0x23, 2, 0X79, 0X00,
	0x23, 2, 0X7A, 0X9B,
	0x23, 2, 0X7B, 0X00,
	0x23, 2, 0X7C, 0XAF,
	0x23, 2, 0X7D, 0X00,
	0x23, 2, 0X7E, 0XC1,
	0x23, 2, 0X7F, 0X00,
	0x23, 2, 0X80, 0XD2,
	0x23, 2, 0X81, 0X00,
	0x23, 2, 0X82, 0XDF,
	0x23, 2, 0X83, 0X01,
	0x23, 2, 0X84, 0X11,
	0x23, 2, 0X85, 0X01,
	0x23, 2, 0X86, 0X38,
	0x23, 2, 0X87, 0X01,
	0x23, 2, 0X88, 0X76,
	0x23, 2, 0X89, 0X01,
	0x23, 2, 0X8A, 0XA7,
	0x23, 2, 0X8B, 0X01,
	0x23, 2, 0X8C, 0XF3,
	0x23, 2, 0X8D, 0X02,
	0x23, 2, 0X8E, 0X2F,
	0x23, 2, 0X8F, 0X02,
	0x23, 2, 0X90, 0X30,
	0x23, 2, 0X91, 0X02,
	0x23, 2, 0X92, 0X66,
	0x23, 2, 0X93, 0X02,
	0x23, 2, 0X94, 0XA0,
	0x23, 2, 0X95, 0X02,
	0x23, 2, 0X96, 0XC5,
	0x23, 2, 0X97, 0X02,
	0x23, 2, 0X98, 0XF8,
	0x23, 2, 0X99, 0X03,
	0x23, 2, 0X9A, 0X1B,
	0x23, 2, 0X9B, 0X03,
	0x23, 2, 0X9C, 0X46,
	0x23, 2, 0X9D, 0X03,
	0x23, 2, 0X9E, 0X52,
	0x23, 2, 0X9F, 0X03,
	0x23, 2, 0XA0, 0X62,
	0x23, 2, 0XA2, 0X03,
	0x23, 2, 0XA3, 0X71,
	0x23, 2, 0XA4, 0X03,
	0x23, 2, 0XA5, 0X83,
	0x23, 2, 0XA6, 0X03,
	0x23, 2, 0XA7, 0X94,
	0x23, 2, 0XA9, 0X03,
	0x23, 2, 0XAA, 0XA3,
	0x23, 2, 0XAB, 0X03,
	0x23, 2, 0XAC, 0XAD,
	0x23, 2, 0XAD, 0X03,
	0x23, 2, 0XAE, 0XCC,

	0x23, 2, 0XAF, 0X00, //Gamma B-
	0x23, 2, 0XB0, 0X18,
	0x23, 2, 0XB1, 0X00,
	0x23, 2, 0XB2, 0X38,
	0x23, 2, 0XB3, 0X00,
	0x23, 2, 0XB4, 0X65,
	0x23, 2, 0XB5, 0X00,
	0x23, 2, 0XB6, 0X84,
	0x23, 2, 0XB7, 0X00,
	0x23, 2, 0XB8, 0X9B,
	0x23, 2, 0XB9, 0X00,
	0x23, 2, 0XBA, 0XAF,
	0x23, 2, 0XBB, 0X00,
	0x23, 2, 0XBC, 0XC1,
	0x23, 2, 0XBD, 0X00,
	0x23, 2, 0XBE, 0XD2,
	0x23, 2, 0XBF, 0X00,
	0x23, 2, 0XC0, 0XDF,
	0x23, 2, 0XC1, 0X01,
	0x23, 2, 0XC2, 0X11,
	0x23, 2, 0XC3, 0X01,
	0x23, 2, 0XC4, 0X38,
	0x23, 2, 0XC5, 0X01,
	0x23, 2, 0XC6, 0X76,
	0x23, 2, 0XC7, 0X01,
	0x23, 2, 0XC8, 0XA7,
	0x23, 2, 0XC9, 0X01,
	0x23, 2, 0XCA, 0XF3,
	0x23, 2, 0XCB, 0X02,
	0x23, 2, 0XCC, 0X2F,
	0x23, 2, 0XCD, 0X02,
	0x23, 2, 0XCE, 0X30,
	0x23, 2, 0XCF, 0X02,
	0x23, 2, 0XD0, 0X66,
	0x23, 2, 0XD1, 0X02,
	0x23, 2, 0XD2, 0XA0,
	0x23, 2, 0XD3, 0X02,
	0x23, 2, 0XD4, 0XC5,
	0x23, 2, 0XD5, 0X02,
	0x23, 2, 0XD6, 0XF8,
	0x23, 2, 0XD7, 0X03,
	0x23, 2, 0XD8, 0X1B,
	0x23, 2, 0XD9, 0X03,
	0x23, 2, 0XDA, 0X46,
	0x23, 2, 0XDB, 0X03,
	0x23, 2, 0XDC, 0X52,
	0x23, 2, 0XDD, 0X03,
	0x23, 2, 0XDE, 0X62,
	0x23, 2, 0XDF, 0X03,
	0x23, 2, 0XE0, 0X71,
	0x23, 2, 0XE1, 0X03,
	0x23, 2, 0XE2, 0X83,
	0x23, 2, 0XE3, 0X03,
	0x23, 2, 0XE4, 0X94,
	0x23, 2, 0XE5, 0X03,
	0x23, 2, 0XE6, 0XA3,
	0x23, 2, 0XE7, 0X03,
	0x23, 2, 0XE8, 0XAD,
	0x23, 2, 0XE9, 0X03,
	0x23, 2, 0XEA, 0XCC,

	0x23, 2, 0XFF, 0X01, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0XFF, 0X02, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0XFF, 0X04, //CMD page select
	0x23, 2, 0XFB, 0X01, //NON-RELOAD CMD
	0x23, 2, 0XFF, 0X00, //CMD page select

	0x23, 2, 0XD3, 0X05,
	0x23, 2, 0XD4, 0X04,

	0x23, 2, 0X11, 0X00, //Sleep out
	0xfd, 1, 100, //delay 100ms
	0x23, 2, 0XFF, 0X00,

	0x23, 2, 0X35, 0X00, //TE on

	0x23, 2, 0X29, 0X00, //Display on
	0xfd, 1, 100, //delay 100ms
	0xff, 0,   /* ending flag */
};

static unsigned char mipi_init_off_table[] = {
	0x05, 1, 0x28, /* display off */
	0xfd, 10,      /* delay 10ms */
	0x05, 1, 0x10, /* sleep in */
	0xfd, 150,     /* delay 150ms */
	0xff, 0,    /* ending flag */
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

int lcd_extern_mipi_tl050fhv02ct_probe(struct aml_lcd_extern_driver_s *ext_drv)
{
	int ret = 0;

	ret = lcd_extern_driver_update(ext_drv);

	if (lcd_debug_print_flag)
		EXTPR("%s: %d\n", __func__, ret);
	return ret;
}
