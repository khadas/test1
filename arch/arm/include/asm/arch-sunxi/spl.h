/*
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef	_ASM_ARCH_SPL_H_
#define	_ASM_ARCH_SPL_H_

#define BOOT0_MAGIC		"eGON.BT0"
#define SPL_SIGNATURE		"SPL" /* marks "sunxi" SPL header */
#define SPL_HEADER_VERSION	1

#if defined(CONFIG_MACH_SUN9I) || defined(CONFIG_MACH_SUN50I)
#define SPL_ADDR		0x10000
#else
#define SPL_ADDR		0x0
#endif

/* The low 8-bits of the 'boot_media' field in the SPL header */
#define SUNXI_BOOTED_FROM_MMC0	0
#define SUNXI_BOOTED_FROM_SPI	3

/* boot head definition from sun4i boot code */
struct boot_file_head {
	uint32_t b_instruction;	/* one intruction jumping to real code */
	uint8_t magic[8];	/* ="eGON.BT0" or "eGON.BT1", not C-style str */
	uint32_t check_sum;	/* generated by PC */
	uint32_t length;	/* generated by PC */
	/*
	 * We use a simplified header, only filling in what is needed
	 * by the boot ROM. To be compatible with Allwinner tools we
	 * would need to implement the proper fields here instead of
	 * padding.
	 *
	 * Actually we want the ability to recognize our "sunxi" variant
	 * of the SPL. To do so, let's place a special signature into the
	 * "pub_head_size" field. We can reasonably expect Allwinner's
	 * boot0 to always have the upper 16 bits of this set to 0 (after
	 * all the value shouldn't be larger than the limit imposed by
	 * SRAM size).
	 * If the signature is present (at 0x14), then we know it's safe
	 * to use the remaining 8 bytes (at 0x18) for our own purposes.
	 * (E.g. sunxi-tools "fel" utility can pass information there.)
	 */
	union {
		uint32_t pub_head_size;
		uint8_t spl_signature[4];
	};
	uint32_t fel_script_address;
	uint32_t reserved1[3];
	uint32_t boot_media;		/* written here by the boot ROM */
	uint32_t reserved2[5];		/* padding, align to 64 bytes */
};

#define is_boot0_magic(addr)	(memcmp((void *)addr, BOOT0_MAGIC, 8) == 0)

#endif
