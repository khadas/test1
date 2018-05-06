/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2012 The Chromium OS Authors.
 */

#ifndef __ASM_MIPS_SECTIONS_H
#define __ASM_MIPS_SECTIONS_H

#include <asm-generic/sections.h>

/**
 * __rel_start: Relocation data generated by the mips-relocs tool
 *
 * See arch/mips/lib/reloc.c for details on the format & use of this data.
 */
extern uint8_t __rel_start[];

#endif
