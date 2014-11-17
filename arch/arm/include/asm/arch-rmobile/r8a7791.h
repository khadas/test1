/*
 * arch/arm/include/asm/arch-rmobile/r8a7791.h
 *
 * Copyright (C) 2013,2014 Renesas Electronics Corporation
 *
 * SPDX-License-Identifier: GPL-2.0
*/

#ifndef __ASM_ARCH_R8A7791_H
#define __ASM_ARCH_R8A7791_H

#include "rcar-base.h"
/*
 * R-Car (R8A7791) I/O Addresses
 */

/* SH-I2C */
#define CONFIG_SYS_I2C_SH_BASE2	0xE60B0000

#define DBSC3_1_QOS_R0_BASE	0xE67A1000
#define DBSC3_1_QOS_R1_BASE	0xE67A1100
#define DBSC3_1_QOS_R2_BASE	0xE67A1200
#define DBSC3_1_QOS_R3_BASE	0xE67A1300
#define DBSC3_1_QOS_R4_BASE	0xE67A1400
#define DBSC3_1_QOS_R5_BASE	0xE67A1500
#define DBSC3_1_QOS_R6_BASE	0xE67A1600
#define DBSC3_1_QOS_R7_BASE	0xE67A1700
#define DBSC3_1_QOS_R8_BASE	0xE67A1800
#define DBSC3_1_QOS_R9_BASE	0xE67A1900
#define DBSC3_1_QOS_R10_BASE	0xE67A1A00
#define DBSC3_1_QOS_R11_BASE	0xE67A1B00
#define DBSC3_1_QOS_R12_BASE	0xE67A1C00
#define DBSC3_1_QOS_R13_BASE	0xE67A1D00
#define DBSC3_1_QOS_R14_BASE	0xE67A1E00
#define DBSC3_1_QOS_R15_BASE	0xE67A1F00
#define DBSC3_1_QOS_W0_BASE	0xE67A2000
#define DBSC3_1_QOS_W1_BASE	0xE67A2100
#define DBSC3_1_QOS_W2_BASE	0xE67A2200
#define DBSC3_1_QOS_W3_BASE	0xE67A2300
#define DBSC3_1_QOS_W4_BASE	0xE67A2400
#define DBSC3_1_QOS_W5_BASE	0xE67A2500
#define DBSC3_1_QOS_W6_BASE	0xE67A2600
#define DBSC3_1_QOS_W7_BASE	0xE67A2700
#define DBSC3_1_QOS_W8_BASE	0xE67A2800
#define DBSC3_1_QOS_W9_BASE	0xE67A2900
#define DBSC3_1_QOS_W10_BASE	0xE67A2A00
#define DBSC3_1_QOS_W11_BASE	0xE67A2B00
#define DBSC3_1_QOS_W12_BASE	0xE67A2C00
#define DBSC3_1_QOS_W13_BASE	0xE67A2D00
#define DBSC3_1_QOS_W14_BASE	0xE67A2E00
#define DBSC3_1_QOS_W15_BASE	0xE67A2F00
#define DBSC3_1_DBADJ2		0xE67A00C8

#define R8A7791_CUT_ES2X	2
#define IS_R8A7791_ES2()	\
	(rmobile_get_cpu_rev_integer() == R8A7791_CUT_ES2X)

#endif /* __ASM_ARCH_R8A7791_H */
