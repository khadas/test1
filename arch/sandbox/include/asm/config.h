/*
 * Copyright (c) 2011 The Chromium OS Authors.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ASM_CONFIG_H_
#define _ASM_CONFIG_H_

#define CONFIG_SYS_GENERIC_GLOBAL_DATA
#define CONFIG_SANDBOX_ARCH

/* Used by drivers/spi/sandbox_spi.c and arch/sandbox/include/asm/state.h */
#ifndef CONFIG_SANDBOX_SPI_MAX_BUS
#define CONFIG_SANDBOX_SPI_MAX_BUS 1
#endif
#ifndef CONFIG_SANDBOX_SPI_MAX_CS
#define CONFIG_SANDBOX_SPI_MAX_CS 10
#endif

#endif
