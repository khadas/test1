/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * Shengzhou Liu <Shengzhou.Liu@freescale.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <asm/fsl_serdes.h>
#include <asm/processor.h>
#include "fsl_corenet2_serdes.h"

struct serdes_config {
	u32 protocol;
	u8 lanes[SRDS_MAX_LANES];
};

static const struct serdes_config serdes1_cfg_tbl[] = {
	/* SerDes 1 */
	{0x6E, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xBC, {PCIE3, PCIE3, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, PCIE4, PCIE4, PCIE4} },
	{0xC8, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, PCIE4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xD6, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, PCIE4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xDE, {PCIE3, PCIE3, PCIE3, PCIE3,
		PCIE4, PCIE1, PCIE2, SGMII_FM1_DTSEC6} },
	{0xE0, {PCIE3, PCIE3, PCIE3, PCIE3, PCIE4,
		PCIE1, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xF2, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, PCIE1, PCIE2, SGMII_FM1_DTSEC6} },
	{0xF8, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, PCIE1, PCIE2, SGMII_FM1_DTSEC6} },
	{0xFA, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, PCIE1,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x6C, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0x1B, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x1C, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x95, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xA2, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x94, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x50, {XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x51, {XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x5E, {HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x5F, {HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x64, {HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x65, {HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x6A, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		XFI_FM1_MAC1, XFI_FM1_MAC2,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x6B, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		XFI_FM1_MAC1, XFI_FM1_MAC2,
		PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x6D, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0x71, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2, PCIE4,
		SGMII_FM1_DTSEC4, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xA6, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2, PCIE4,
		PCIE4, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x8E, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2, PCIE4,
		PCIE4, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x8F, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2, PCIE4,
		PCIE4, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x82, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x83, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xA4, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0x96, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0x8A, {SGMII_FM1_DTSEC9, SGMII_FM1_DTSEC10,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0x67, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		XFI_FM1_MAC1, XFI_FM1_MAC2,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0xAB, {PCIE3, PCIE3, PCIE3, PCIE3,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0xDA, {PCIE3, PCIE3, PCIE3, PCIE3,
		PCIE3, PCIE3, PCIE3, PCIE3} },
	{0xD9, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xD2, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xD3, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xCB, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0xD8, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x66, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		XFI_FM1_MAC1, XFI_FM1_MAC2,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0xAA, {PCIE3, PCIE3, PCIE3, PCIE3,
		PCIE4, PCIE4, PCIE4, PCIE4} },
	{0xCA, {PCIE3, SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{0x70, {XFI_FM1_MAC9, XFI_FM1_MAC10, SGMII_FM1_DTSEC1,
		SGMII_FM1_DTSEC2, PCIE4, SGMII_FM1_DTSEC4,
		SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6} },
	{}
};

#ifndef CONFIG_PPC_T2081
static const struct serdes_config serdes2_cfg_tbl[] = {
	/* SerDes 2 */
	{0x1F, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2} },
	{0x16, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, SATA1, SATA2} },
	{0x01, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1} },
	{0x29, {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1} },
	{0x2D, {SRIO2, SRIO2, SRIO2, SRIO2, SRIO1, SRIO1, SRIO1, SRIO1} },
	{0x15, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, SATA1, SATA2} },
	{0x27, {PCIE1, PCIE1, PCIE1, PCIE1, NONE,  NONE,  SATA1, SATA2} },
	{0x18, {PCIE1, PCIE1, PCIE1, PCIE1, AURORA, AURORA, SATA1, SATA2} },
	{0x02, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1} },
	{0x36, {SRIO2, SRIO2, SRIO2, SRIO2, AURORA, AURORA, SATA1, SATA2} },
	{}
};
#endif

static const struct serdes_config *serdes_cfg_tbl[] = {
	serdes1_cfg_tbl,
#ifndef CONFIG_PPC_T2081
	serdes2_cfg_tbl,
#endif
};

enum srds_prtcl serdes_get_prtcl(int serdes, int cfg, int lane)
{
	const struct serdes_config *ptr;

	if (serdes >= ARRAY_SIZE(serdes_cfg_tbl))
		return 0;

	ptr = serdes_cfg_tbl[serdes];
	while (ptr->protocol) {
		if (ptr->protocol == cfg)
			return ptr->lanes[lane];
		ptr++;
	}
	return 0;
}

int is_serdes_prtcl_valid(int serdes, u32 prtcl)
{
	int i;
	const struct serdes_config *ptr;

	if (serdes >= ARRAY_SIZE(serdes_cfg_tbl))
		return 0;

	ptr = serdes_cfg_tbl[serdes];
	while (ptr->protocol) {
		if (ptr->protocol == prtcl)
			break;
		ptr++;
	}

	if (!ptr->protocol)
		return 0;

	for (i = 0; i < SRDS_MAX_LANES; i++) {
		if (ptr->lanes[i] != NONE)
			return 1;
	}

	return 0;
}
