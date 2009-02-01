/*
 * (C) Copyright 2006-2008
 * Texas Instruments, <www.ti.com>
 * Richard Woodruff <r-woodruff2@ti.com>
 * Syed Mohammed Khasim <x0khasim@ti.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _OMAP3_H_
#define _OMAP3_H_

/* Stuff on L3 Interconnect */
#define SMX_APE_BASE			0x68000000

/* GPMC */
#define OMAP34XX_GPMC_BASE		0x6E000000

/* SMS */
#define OMAP34XX_SMS_BASE		0x6C000000

/* SDRC */
#define OMAP34XX_SDRC_BASE		0x6D000000

/*
 * L4 Peripherals - L4 Wakeup and L4 Core now
 */
#define OMAP34XX_CORE_L4_IO_BASE	0x48000000
#define OMAP34XX_WAKEUP_L4_IO_BASE	0x48300000
#define OMAP34XX_L4_PER			0x49000000
#define OMAP34XX_L4_IO_BASE		OMAP34XX_CORE_L4_IO_BASE

/* CONTROL */
#define OMAP34XX_CTRL_BASE		(OMAP34XX_L4_IO_BASE + 0x2000)

/* UART */
#define OMAP34XX_UART1			(OMAP34XX_L4_IO_BASE + 0x6a000)
#define OMAP34XX_UART2			(OMAP34XX_L4_IO_BASE + 0x6c000)
#define OMAP34XX_UART3			(OMAP34XX_L4_PER + 0x20000)

/* General Purpose Timers */
#define OMAP34XX_GPT1			0x48318000
#define OMAP34XX_GPT2			0x49032000
#define OMAP34XX_GPT3			0x49034000
#define OMAP34XX_GPT4			0x49036000
#define OMAP34XX_GPT5			0x49038000
#define OMAP34XX_GPT6			0x4903A000
#define OMAP34XX_GPT7			0x4903C000
#define OMAP34XX_GPT8			0x4903E000
#define OMAP34XX_GPT9			0x49040000
#define OMAP34XX_GPT10			0x48086000
#define OMAP34XX_GPT11			0x48088000
#define OMAP34XX_GPT12			0x48304000

/* WatchDog Timers (1 secure, 3 GP) */
#define WD1_BASE			0x4830C000
#define WD2_BASE			0x48314000
#define WD3_BASE			0x49030000

/* 32KTIMER */
#define SYNC_32KTIMER_BASE		0x48320000

#ifndef __ASSEMBLY__

typedef struct s32ktimer {
	unsigned char res[0x10];
	unsigned int s32k_cr;		/* 0x10 */
} s32ktimer_t;

#endif /* __ASSEMBLY__ */

/* OMAP3 GPIO registers */
#define OMAP34XX_GPIO1_BASE		0x48310000
#define OMAP34XX_GPIO2_BASE		0x49050000
#define OMAP34XX_GPIO3_BASE		0x49052000
#define OMAP34XX_GPIO4_BASE		0x49054000
#define OMAP34XX_GPIO5_BASE		0x49056000
#define OMAP34XX_GPIO6_BASE		0x49058000

#ifndef __ASSEMBLY__
typedef struct gpio {
	unsigned char res1[0x34];
	unsigned int oe;		/* 0x34 */
	unsigned char res2[0x58];
	unsigned int cleardataout;	/* 0x90 */
	unsigned int setdataout;	/* 0x94 */
} gpio_t;
#endif /* __ASSEMBLY__ */

#define GPIO0				(0x1 << 0)
#define GPIO1				(0x1 << 1)
#define GPIO2				(0x1 << 2)
#define GPIO3				(0x1 << 3)
#define GPIO4				(0x1 << 4)
#define GPIO5				(0x1 << 5)
#define GPIO6				(0x1 << 6)
#define GPIO7				(0x1 << 7)
#define GPIO8				(0x1 << 8)
#define GPIO9				(0x1 << 9)
#define GPIO10				(0x1 << 10)
#define GPIO11				(0x1 << 11)
#define GPIO12				(0x1 << 12)
#define GPIO13				(0x1 << 13)
#define GPIO14				(0x1 << 14)
#define GPIO15				(0x1 << 15)
#define GPIO16				(0x1 << 16)
#define GPIO17				(0x1 << 17)
#define GPIO18				(0x1 << 18)
#define GPIO19				(0x1 << 19)
#define GPIO20				(0x1 << 20)
#define GPIO21				(0x1 << 21)
#define GPIO22				(0x1 << 22)
#define GPIO23				(0x1 << 23)
#define GPIO24				(0x1 << 24)
#define GPIO25				(0x1 << 25)
#define GPIO26				(0x1 << 26)
#define GPIO27				(0x1 << 27)
#define GPIO28				(0x1 << 28)
#define GPIO29				(0x1 << 29)
#define GPIO30				(0x1 << 30)
#define GPIO31				(0x1 << 31)

/* base address for indirect vectors (internal boot mode) */
#define SRAM_OFFSET0			0x40000000
#define SRAM_OFFSET1			0x00200000
#define SRAM_OFFSET2			0x0000F800
#define SRAM_VECT_CODE			(SRAM_OFFSET0 | SRAM_OFFSET1 | \
					 SRAM_OFFSET2)

#define LOW_LEVEL_SRAM_STACK		0x4020FFFC

#define DEBUG_LED1			149	/* gpio */
#define DEBUG_LED2			150	/* gpio */

#define XDR_POP		5	/* package on package part */
#define SDR_DISCRETE	4	/* 128M memory SDR module */
#define DDR_STACKED	3	/* stacked part on 2422 */
#define DDR_COMBO	2	/* combo part on cpu daughter card */
#define DDR_DISCRETE	1	/* 2x16 parts on daughter card */

#define DDR_100		100	/* type found on most mem d-boards */
#define DDR_111		111	/* some combo parts */
#define DDR_133		133	/* most combo, some mem d-boards */
#define DDR_165		165	/* future parts */

#define CPU_3430	0x3430

/*
 * 343x real hardware:
 *  ES1     = rev 0
 *
 * 343x code defines:
 * ES1     = 0+1 = 1
 * ES1     = 1+1 = 1
 */
#define CPU_3430_ES1		1
#define CPU_3430_ES2		2

#define WIDTH_8BIT		0x0000
#define WIDTH_16BIT		0x1000	/* bit pos for 16 bit in gpmc */

/* SDP definitions according to FPGA Rev. Is this OK?? */
#define SDP_3430_V1		0x1
#define SDP_3430_V2		0x2

/* EVM definitions */
#define OMAP3EVM_V1		0x1
#define OMAP3EVM_V2		0x2

/* I2C power management companion definitions */
#define PWRMGT_ADDR_ID1		0x48
#define PWRMGT_ADDR_ID2		0x49
#define PWRMGT_ADDR_ID3		0x4A
#define PWRMGT_ADDR_ID4		0x4B

/* I2C ID3 (slave3) register */
#define LEDEN			0xEE

#define LEDAON			(0x1 << 0)
#define LEDBON			(0x1 << 1)
#define LEDAPWM			(0x1 << 4)
#define LEDBPWM			(0x1 << 5)

/* I2C ID4 (slave4) register */
#define VAUX2_DEV_GRP		0x76
#define VAUX2_DEDICATED		0x79
#define VAUX3_DEV_GRP		0x7A
#define VAUX3_DEDICATED		0x7D
#define VPLL2_DEV_GRP		0x8E
#define VPLL2_DEDICATED		0x91
#define VDAC_DEV_GRP		0x96
#define VDAC_DEDICATED		0x99

#define DEV_GRP_P1		0x20
#define DEV_GRP_ALL		0xE0

#define VAUX2_VSEL_28		0x09
#define VAUX3_VSEL_28		0x03
#define VPLL2_VSEL_18		0x05
#define VDAC_VSEL_18		0x03

#endif
