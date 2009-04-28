/*
 * Copyright (C) 2007 Sergey Kubushyn <ksi@koi8.net>
 *
 * Parts shamelesly stolen from Linux Kernel source tree.
 *
 * ------------------------------------------------------------
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
#ifndef _NAND_DEFS_H_
#define _NAND_DEFS_H_

#include <asm/arch/hardware.h>

#define	MASK_CLE	0x10
#define	MASK_ALE	0x0a

#define NAND_READ_START		0x00
#define NAND_READ_END		0x30
#define NAND_STATUS		0x70

#ifdef CONFIG_SYS_NAND_HW_ECC
#define NAND_Ecc_P1e		(1 << 0)
#define NAND_Ecc_P2e		(1 << 1)
#define NAND_Ecc_P4e		(1 << 2)
#define NAND_Ecc_P8e		(1 << 3)
#define NAND_Ecc_P16e		(1 << 4)
#define NAND_Ecc_P32e		(1 << 5)
#define NAND_Ecc_P64e		(1 << 6)
#define NAND_Ecc_P128e		(1 << 7)
#define NAND_Ecc_P256e		(1 << 8)
#define NAND_Ecc_P512e		(1 << 9)
#define NAND_Ecc_P1024e		(1 << 10)
#define NAND_Ecc_P2048e		(1 << 11)

#define NAND_Ecc_P1o		(1 << 16)
#define NAND_Ecc_P2o		(1 << 17)
#define NAND_Ecc_P4o		(1 << 18)
#define NAND_Ecc_P8o		(1 << 19)
#define NAND_Ecc_P16o		(1 << 20)
#define NAND_Ecc_P32o		(1 << 21)
#define NAND_Ecc_P64o		(1 << 22)
#define NAND_Ecc_P128o		(1 << 23)
#define NAND_Ecc_P256o		(1 << 24)
#define NAND_Ecc_P512o		(1 << 25)
#define NAND_Ecc_P1024o		(1 << 26)
#define NAND_Ecc_P2048o		(1 << 27)

#define TF(v)			(v ? 1 : 0)

#define P2048e(a)		(TF(a & NAND_Ecc_P2048e) << 0)
#define P2048o(a)		(TF(a & NAND_Ecc_P2048o) << 1)
#define P1e(a)			(TF(a & NAND_Ecc_P1e) << 2)
#define P1o(a)			(TF(a & NAND_Ecc_P1o) << 3)
#define P2e(a)			(TF(a & NAND_Ecc_P2e) << 4)
#define P2o(a)			(TF(a & NAND_Ecc_P2o) << 5)
#define P4e(a)			(TF(a & NAND_Ecc_P4e) << 6)
#define P4o(a)			(TF(a & NAND_Ecc_P4o) << 7)

#define P8e(a)			(TF(a & NAND_Ecc_P8e) << 0)
#define P8o(a)			(TF(a & NAND_Ecc_P8o) << 1)
#define P16e(a)			(TF(a & NAND_Ecc_P16e) << 2)
#define P16o(a)			(TF(a & NAND_Ecc_P16o) << 3)
#define P32e(a)			(TF(a & NAND_Ecc_P32e) << 4)
#define P32o(a)			(TF(a & NAND_Ecc_P32o) << 5)
#define P64e(a)			(TF(a & NAND_Ecc_P64e) << 6)
#define P64o(a)			(TF(a & NAND_Ecc_P64o) << 7)

#define P128e(a)		(TF(a & NAND_Ecc_P128e) << 0)
#define P128o(a)		(TF(a & NAND_Ecc_P128o) << 1)
#define P256e(a)		(TF(a & NAND_Ecc_P256e) << 2)
#define P256o(a)		(TF(a & NAND_Ecc_P256o) << 3)
#define P512e(a)		(TF(a & NAND_Ecc_P512e) << 4)
#define P512o(a)		(TF(a & NAND_Ecc_P512o) << 5)
#define P1024e(a)		(TF(a & NAND_Ecc_P1024e) << 6)
#define P1024o(a)		(TF(a & NAND_Ecc_P1024o) << 7)

#define P8e_s(a)		(TF(a & NAND_Ecc_P8e) << 0)
#define P8o_s(a)		(TF(a & NAND_Ecc_P8o) << 1)
#define P16e_s(a)		(TF(a & NAND_Ecc_P16e) << 2)
#define P16o_s(a)		(TF(a & NAND_Ecc_P16o) << 3)
#define P1e_s(a)		(TF(a & NAND_Ecc_P1e) << 4)
#define P1o_s(a)		(TF(a & NAND_Ecc_P1o) << 5)
#define P2e_s(a)		(TF(a & NAND_Ecc_P2e) << 6)
#define P2o_s(a)		(TF(a & NAND_Ecc_P2o) << 7)

#define P4e_s(a)		(TF(a & NAND_Ecc_P4e) << 0)
#define P4o_s(a)		(TF(a & NAND_Ecc_P4o) << 1)
#endif

#endif
