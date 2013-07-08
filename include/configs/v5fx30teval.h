/*
 * (C) Copyright 2008
 *  Ricado Ribalda-Universidad Autonoma de Madrid-ricardo.ribalda@uam.es
 *  This work has been supported by: QTechnology  http://qtec.com/
 * SPDX-License-Identifier:	GPL-2.0+
*/

#ifndef __CONFIG_H
#define __CONFIG_H

/*CPU*/
#define CONFIG_440		1
#define CONFIG_XILINX_ML507	1
#include "../board/avnet/v5fx30teval/xparameters.h"

/*Mem Map*/
#define CONFIG_SYS_SDRAM_SIZE_MB	64

/*Env*/
#define	CONFIG_ENV_IS_IN_FLASH	1
#define	CONFIG_ENV_SIZE		0x20000
#define	CONFIG_ENV_SECT_SIZE	0x20000
#define CONFIG_ENV_OFFSET		0x1A0000
#define CONFIG_ENV_ADDR		(XPAR_FLASH_MEM0_BASEADDR+CONFIG_ENV_OFFSET)

/*Misc*/
#define CONFIG_SYS_PROMPT		"v5fx30t:/# "	/* Monitor Command Prompt    */
#define CONFIG_PREBOOT		"echo U-Boot is up and runnining;"

/*Flash*/
#define	CONFIG_SYS_FLASH_SIZE		(16*1024*1024)
#define	CONFIG_SYS_MAX_FLASH_SECT	131
#define MTDIDS_DEFAULT		"nor0=v5fx30t-flash"
#define MTDPARTS_DEFAULT	"mtdparts=v5fx30t-flash:-(user)"

/*Generic Configs*/
#include <configs/xilinx-ppc440.h>

#endif						/* __CONFIG_H */
