/*
 *  Copyright (C) 2012 Samsung Electronics
 *  Lukasz Majewski <l.majewski@samsung.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __MAX17042_FG_H_
#define __MAX17042_FG_H_

/* MAX 17042 registers */
enum {
	MAX17042_STATUS         = 0x00,
	MAX17042_SOCREP         = 0x06,
	MAX17042_VCELL          = 0x09,
	MAX17042_CURRENT        = 0x0A,
	MAX17042_AVG_CURRENT	= 0x0B,
	MAX17042_SOCMIX	= 0x0D,
	MAX17042_SOCAV		= 0x0E,
	MAX17042_DESIGN_CAP	= 0x18,
	MAX17042_AVG_VCELL	= 0x19,
	MAX17042_CONFIG	= 0x1D,
	MAX17042_VERSION	= 0x21,
	MAX17042_LEARNCFG       = 0x28,
	MAX17042_FILTERCFG	= 0x29,
	MAX17042_RELAXCFG	= 0x2A,
	MAX17042_MISCCFG	= 0x2B,
	MAX17042_CGAIN		= 0x2E,
	MAX17042_COFF		= 0x2F,
	MAX17042_RCOMP0	= 0x38,
	MAX17042_TEMPCO	= 0x39,
	MAX17042_FSTAT		= 0x3D,
	MAX17042_MLOCKReg1	= 0x62,
	MAX17042_MLOCKReg2	= 0x63,
	MAX17042_MODEL1         = 0x80,
	MAX17042_MODEL2         = 0x90,
	MAX17042_MODEL3         = 0xA0,
	MAX17042_VFOCV		= 0xFB,
	MAX17042_VFSOC		= 0xFF,

	FG_NUM_OF_REGS = 0x100,
};

#define RCOMP0			0x0060
#define TempCo			0x1015


#define MAX17042_POR (1 << 1)

#define MODEL_UNLOCK1		0x0059
#define MODEL_UNLOCK2		0x00c4
#define MODEL_LOCK1		0x0000
#define MODEL_LOCK2		0x0000

#define MAX17042_I2C_ADDR	(0x6C >> 1)

int power_fg_init(unsigned char bus);
#endif /* __MAX17042_FG_H_ */
