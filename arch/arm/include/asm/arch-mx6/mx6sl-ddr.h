/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 */

#ifndef __ASM_ARCH_MX6SL_DDR_H__
#define __ASM_ARCH_MX6SL_DDR_H__

#ifndef CONFIG_MX6SL
#error "wrong CPU"
#endif

#define MX6_IOM_DRAM_CAS_B	0x020e0300
#define MX6_IOM_DRAM_CS0_B	0x020e0304
#define MX6_IOM_DRAM_CS1_B	0x020e0308

#define MX6_IOM_DRAM_DQM0	0x020e030c
#define MX6_IOM_DRAM_DQM1	0x020e0310
#define MX6_IOM_DRAM_DQM2	0x020e0314
#define MX6_IOM_DRAM_DQM3	0x020e0318

#define MX6_IOM_DRAM_RAS_B	0x020e031c
#define MX6_IOM_DRAM_RESET	0x020e0320

#define MX6_IOM_DRAM_SDBA0	0x020e0324
#define MX6_IOM_DRAM_SDBA1	0x020e0328
#define MX6_IOM_DRAM_SDBA2	0x020e032c

#define MX6_IOM_DRAM_SDCKE0	0x020e0330
#define MX6_IOM_DRAM_SDCKE1	0x020e0334

#define MX6_IOM_DRAM_SDCLK0_P	0x020e0338

#define MX6_IOM_DRAM_ODT0	0x020e033c
#define MX6_IOM_DRAM_ODT1	0x020e0340

#define MX6_IOM_DRAM_SDQS0_P	0x020e0344
#define MX6_IOM_DRAM_SDQS1_P	0x020e0348
#define MX6_IOM_DRAM_SDQS2_P	0x020e034c
#define MX6_IOM_DRAM_SDQS3_P	0x020e0350

#define MX6_IOM_DRAM_SDWE_B	0x020e0354

#endif /*__ASM_ARCH_MX6SL_DDR_H__ */
