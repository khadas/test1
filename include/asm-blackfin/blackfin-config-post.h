/*
 * blackfin-config-post.h - setup common defines for Blackfin boards based on config.h
 *
 * Copyright (c) 2007-2008 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#ifndef __ASM_BLACKFIN_CONFIG_POST_H__
#define __ASM_BLACKFIN_CONFIG_POST_H__

/* Sanity check CONFIG_BFIN_CPU */
#ifndef CONFIG_BFIN_CPU
# error CONFIG_BFIN_CPU: your board config needs to define this
#endif

/* Make sure the structure is properly aligned */
#if ((CONFIG_SYS_GBL_DATA_ADDR & -4) != CONFIG_SYS_GBL_DATA_ADDR)
# error CONFIG_SYS_GBL_DATA_ADDR: must be 4 byte aligned
#endif

/* Set default CONFIG_VCO_HZ if need be */
#if !defined(CONFIG_VCO_HZ)
# if (CONFIG_CLKIN_HALF == 0)
#  define CONFIG_VCO_HZ (CONFIG_CLKIN_HZ * CONFIG_VCO_MULT)
# else
#  define CONFIG_VCO_HZ ((CONFIG_CLKIN_HZ * CONFIG_VCO_MULT) / 2)
# endif
#endif

/* Set default CONFIG_CCLK_HZ if need be */
#if !defined(CONFIG_CCLK_HZ)
# if (CONFIG_PLL_BYPASS == 0)
#  define CONFIG_CCLK_HZ (CONFIG_VCO_HZ / CONFIG_CCLK_DIV)
# else
#  define CONFIG_CCLK_HZ CONFIG_CLKIN_HZ
# endif
#endif

/* Set default CONFIG_SCLK_HZ if need be */
#if !defined(CONFIG_SCLK_HZ)
# if (CONFIG_PLL_BYPASS == 0)
#  define CONFIG_SCLK_HZ (CONFIG_VCO_HZ / CONFIG_SCLK_DIV)
# else
#  define CONFIG_SCLK_HZ CONFIG_CLKIN_HZ
# endif
#endif

/* Since we use these to program PLL registers directly,
 * make sure the values are sane and won't screw us up.
 */
#if (CONFIG_VCO_MULT & 0x3F) != CONFIG_VCO_MULT
# error CONFIG_VCO_MULT: Invalid value: must fit in 6 bits (0 - 63)
#endif
#if (CONFIG_CLKIN_HALF & 0x1) != CONFIG_CLKIN_HALF
# error CONFIG_CLKIN_HALF: Invalid value: must be 0 or 1
#endif
#if (CONFIG_PLL_BYPASS & 0x1) != CONFIG_PLL_BYPASS
# error CONFIG_PLL_BYPASS: Invalid value: must be 0 or 1
#endif

/* Using L1 scratch pad makes sense for everyone by default. */
#ifndef CONFIG_LINUX_CMDLINE_ADDR
# define CONFIG_LINUX_CMDLINE_ADDR L1_SRAM_SCRATCH
#endif
#ifndef CONFIG_LINUX_CMDLINE_SIZE
# define CONFIG_LINUX_CMDLINE_SIZE L1_SRAM_SCRATCH_SIZE
#endif

/* Set default SPI flash CS to the one we boot from */
#if defined(CONFIG_ENV_IS_IN_SPI_FLASH) && !defined(CONFIG_ENV_SPI_CS)
# define CONFIG_ENV_SPI_CS BFIN_BOOT_SPI_SSEL
#endif

/* Default/common Blackfin memory layout */
#ifndef CONFIG_SYS_SDRAM_BASE
# define CONFIG_SYS_SDRAM_BASE 0
#endif
#ifndef CONFIG_SYS_MAX_RAM_SIZE
# define CONFIG_SYS_MAX_RAM_SIZE (CONFIG_MEM_SIZE * 1024 * 1024)
#endif
#ifndef CONFIG_SYS_MONITOR_BASE
# define CONFIG_SYS_MONITOR_BASE (CONFIG_SYS_MAX_RAM_SIZE - CONFIG_SYS_MONITOR_LEN)
#endif
#ifndef CONFIG_SYS_MALLOC_BASE
# define CONFIG_SYS_MALLOC_BASE (CONFIG_SYS_MONITOR_BASE - CONFIG_SYS_MALLOC_LEN)
#endif
#ifndef CONFIG_SYS_GBL_DATA_SIZE
# define CONFIG_SYS_GBL_DATA_SIZE (128)
#endif
#ifndef CONFIG_SYS_GBL_DATA_ADDR
# define CONFIG_SYS_GBL_DATA_ADDR (CONFIG_SYS_MALLOC_BASE - CONFIG_SYS_GBL_DATA_SIZE)
#endif
#ifndef CONFIG_STACKBASE
# define CONFIG_STACKBASE (CONFIG_SYS_GBL_DATA_ADDR - 4)
#endif
#ifndef CONFIG_SYS_MEMTEST_START
# define CONFIG_SYS_MEMTEST_START 0
#endif
#ifndef CONFIG_SYS_MEMTEST_END
# define CONFIG_SYS_MEMTEST_END (CONFIG_STACKBASE - 8192 + 4)
#endif

/* Check to make sure everything fits in external RAM */
#if ((CONFIG_SYS_MONITOR_BASE + CONFIG_SYS_MONITOR_LEN) > CONFIG_SYS_MAX_RAM_SIZE)
# error Memory Map does not fit into configuration
#endif

/* Default/common Blackfin environment settings */
#ifndef CONFIG_LOADADDR
# define CONFIG_LOADADDR 0x1000000
#endif
#ifndef CONFIG_SYS_LOAD_ADDR
# define CONFIG_SYS_LOAD_ADDR CONFIG_LOADADDR
#endif
#ifndef CONFIG_SYS_BOOTM_LEN
# define CONFIG_SYS_BOOTM_LEN 0x4000000
#endif
#ifndef CONFIG_SYS_PROMPT
# define CONFIG_SYS_PROMPT "bfin> "
#endif
#ifndef CONFIG_SYS_CBSIZE
# ifdef CONFIG_CMD_KGDB
#  define CONFIG_SYS_CBSIZE 1024
# else
#  define CONFIG_SYS_CBSIZE 256
# endif
#endif
#ifndef CONFIG_SYS_BARGSIZE
# define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE
#endif
#ifndef CONFIG_SYS_PBSIZE
# define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#endif
#ifndef CONFIG_SYS_MAXARGS
# define CONFIG_SYS_MAXARGS 16
#endif
#if defined(CONFIG_SYS_HZ)
# if (CONFIG_SYS_HZ != 1000)
#  warning "CONFIG_SYS_HZ must always be 1000"
# endif
# undef CONFIG_SYS_HZ
#endif
#define CONFIG_SYS_HZ 1000
#ifndef CONFIG_SYS_BAUDRATE_TABLE
# define CONFIG_SYS_BAUDRATE_TABLE { 9600, 19200, 38400, 57600, 115200 }
#endif

#endif
