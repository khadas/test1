/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/fsl_serdes.h>
#include <asm/processor.h>
#include <asm/io.h>
#include "fsl_corenet2_serdes.h"

struct serdes_config {
	u32 protocol;
	u8 lanes[SRDS_MAX_LANES];
};

#ifdef CONFIG_PPC_T4240
static const struct serdes_config serdes1_cfg_tbl[] = {
	/* SerDes 1 */
	{1, {XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		XAUI_FM1_MAC9, XAUI_FM1_MAC9,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10}},
	{2, {HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10}},
	{4, {HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC9, HIGIG_FM1_MAC9,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10}},
	{27, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4} },
	{28, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4}},
	{35, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4} },
	{36, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4}},
	{37, {NONE, NONE, QSGMII_FM1_B, NONE,
		NONE, NONE, QSGMII_FM1_A, NONE} },
	{38, {NONE, NONE, QSGMII_FM1_B, NONE,
		NONE, NONE, QSGMII_FM1_A, NONE}},
	{39, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		NONE, NONE, QSGMII_FM1_A, NONE} },
	{40, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		NONE, NONE, QSGMII_FM1_A, NONE}},
	{45, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		NONE, NONE, QSGMII_FM1_A, NONE} },
	{46, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		NONE, NONE, QSGMII_FM1_A, NONE}},
	{47, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		NONE, NONE, QSGMII_FM1_A, NONE} },
	{48, {SGMII_FM1_DTSEC5, SGMII_FM1_DTSEC6,
		SGMII_FM1_DTSEC10, SGMII_FM1_DTSEC9,
		NONE, NONE, QSGMII_FM1_A, NONE}},
	{}
};
static const struct serdes_config serdes2_cfg_tbl[] = {
	/* SerDes 2 */
	{1, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC10, XAUI_FM2_MAC10,
		XAUI_FM2_MAC10, XAUI_FM2_MAC10}},
	{2, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC10, HIGIG_FM2_MAC10,
		HIGIG_FM2_MAC10, HIGIG_FM2_MAC10}},
	{4, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC10, HIGIG_FM2_MAC10,
		HIGIG_FM2_MAC10, HIGIG_FM2_MAC10}},
	{6, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{7, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{12, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{13, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{14, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{15, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{16, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{21, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{22, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{23, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{24, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{25, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{26, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{27, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{28, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{35, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{36, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{37, {NONE, NONE, QSGMII_FM2_B, NONE,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{38, {NONE, NONE, QSGMII_FM2_B, NONE,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{39, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{40, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{45, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{46, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{47, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{48, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{49, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{50, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{51, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{52, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{53, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{54, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{55, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		XFI_FM2_MAC10, XFI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{56, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		XFI_FM2_MAC10, XFI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{57, {XFI_FM1_MAC9, XFI_FM1_MAC10,
		XFI_FM2_MAC10, XFI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4}},
	{}
};
static const struct serdes_config serdes3_cfg_tbl[] = {
	/* SerDes 3 */
	{1, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1} },
	{2, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1}},
	{3, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2} },
	{4, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2}},
	{5, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1} },
	{6, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1}},
	{7, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1} },
	{8, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1} },
	{9, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN}},
	{10, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN}},
	{11, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		PCIE2, PCIE2, PCIE2, PCIE2} },
	{12, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		PCIE2, PCIE2, PCIE2, PCIE2}},
	{13, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		PCIE2, PCIE2, PCIE2, PCIE2} },
	{14, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		PCIE2, PCIE2, PCIE2, PCIE2}},
	{15, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{16, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{17, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{18, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{19, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{20, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1}},
	{}
};
static const struct serdes_config serdes4_cfg_tbl[] = {
	/* SerDes 4 */
	{1, {PCIE3, PCIE3, PCIE3, PCIE3, PCIE3, PCIE3, PCIE3, PCIE3} },
	{2, {PCIE3, PCIE3, PCIE3, PCIE3, PCIE3, PCIE3, PCIE3, PCIE3}},
	{3, {PCIE3, PCIE3, PCIE3, PCIE3, PCIE4, PCIE4, PCIE4, PCIE4} },
	{4, {PCIE3, PCIE3, PCIE3, PCIE3, PCIE4, PCIE4, PCIE4, PCIE4}},
	{5, {PCIE3, PCIE3, PCIE3, PCIE3, SRIO2, SRIO2, SRIO2, SRIO2} },
	{6, {PCIE3, PCIE3, PCIE3, PCIE3, SRIO2, SRIO2, SRIO2, SRIO2}},
	{7, {PCIE3, PCIE3, PCIE3, PCIE3, SRIO2, SRIO2, SRIO2, SRIO2} },
	{8, {PCIE3, PCIE3, PCIE3, PCIE3, SRIO2, SRIO2, SRIO2, SRIO2}},
	{9, {PCIE3, PCIE3, PCIE3, PCIE3, PCIE4, PCIE4, SATA1, SATA2} },
	{10, {PCIE3, PCIE3, PCIE3, PCIE3, PCIE4, PCIE4, SATA1, SATA2} },
	{11, {PCIE3, PCIE3, PCIE3, PCIE3, AURORA, AURORA, SATA1, SATA2} },
	{12, {PCIE3, PCIE3, PCIE3, PCIE3, AURORA, AURORA, SATA1, SATA2} },
	{13, {PCIE3, PCIE3, PCIE3, PCIE3, AURORA, AURORA, SRIO2, SRIO2} },
	{14, {PCIE3, PCIE3, PCIE3, PCIE3, AURORA, AURORA, SRIO2, SRIO2}},
	{15, {PCIE3, PCIE3, PCIE3, PCIE3, AURORA, AURORA, SRIO2, SRIO2} },
	{16, {PCIE3, PCIE3, PCIE3, PCIE3, AURORA, AURORA, SRIO2, SRIO2}},
	{18, {PCIE3, PCIE3, PCIE3, PCIE3, AURORA, AURORA, AURORA, AURORA}},
	{}
};
#elif defined(CONFIG_ARCH_T4160) || defined(CONFIG_PPC_T4080)
static const struct serdes_config serdes1_cfg_tbl[] = {
	/* SerDes 1 */
	{1, {NONE, NONE, NONE, NONE,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10,
		XAUI_FM1_MAC10, XAUI_FM1_MAC10} },
	{2, {NONE, NONE, NONE, NONE,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10} },
	{4, {NONE, NONE, NONE, NONE,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10,
		HIGIG_FM1_MAC10, HIGIG_FM1_MAC10} },
	{27, {NONE, NONE, NONE, NONE,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4} },
	{28, {NONE, NONE, NONE, NONE,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4} },
	{35, {NONE, NONE, NONE, NONE,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4} },
	{36, {NONE, NONE, NONE, NONE,
		SGMII_FM1_DTSEC1, SGMII_FM1_DTSEC2,
		SGMII_FM1_DTSEC3, SGMII_FM1_DTSEC4} },
	{37, {NONE, NONE, NONE, NONE,
		NONE, NONE, QSGMII_FM1_A, NONE} },
	{38, {NONE, NONE, NONE, NONE,
		NONE, NONE, QSGMII_FM1_A, NONE} },
	{}
};
static const struct serdes_config serdes2_cfg_tbl[] = {
	/* SerDes 2 */
	{6, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{7, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{12, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{13, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{15, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{16, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{21, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{22, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{24, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{25, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{26, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		NONE, NONE} },
	{27, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{28, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{35, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{36, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{37, {NONE, NONE, QSGMII_FM2_B, NONE,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{38, {NONE, NONE, QSGMII_FM2_B, NONE,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{39, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{40, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{45, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{46, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{47, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{48, {SGMII_FM2_DTSEC5, SGMII_FM2_DTSEC6,
		SGMII_FM2_DTSEC10, SGMII_FM2_DTSEC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{49, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{50, {XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		XAUI_FM2_MAC9, XAUI_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{51, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{52, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{53, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{54, {HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		HIGIG_FM2_MAC9, HIGIG_FM2_MAC9,
		NONE, NONE, QSGMII_FM2_A, NONE} },
	{55, {NONE, XFI_FM1_MAC10,
		XFI_FM2_MAC10, NONE,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{56, {NONE, XFI_FM1_MAC10,
		XFI_FM2_MAC10, NONE,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		SGMII_FM2_DTSEC3, SGMII_FM2_DTSEC4} },
	{57, {NONE, XFI_FM1_MAC10,
		XFI_FM2_MAC10, NONE,
		SGMII_FM2_DTSEC1, SGMII_FM2_DTSEC2,
		NONE, NONE} },
	{}
};
static const struct serdes_config serdes3_cfg_tbl[] = {
	/* SerDes 3 */
	{1, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1} },
	{2, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1, PCIE1} },
	{3, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2} },
	{4, {PCIE1, PCIE1, PCIE1, PCIE1, PCIE2, PCIE2, PCIE2, PCIE2} },
	{5, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1} },
	{6, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1} },
	{7, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1} },
	{8, {PCIE1, PCIE1, PCIE1, PCIE1, SRIO1, SRIO1, SRIO1, SRIO1} },
	{9, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN} },
	{10, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN} },
	{11, {NONE, NONE, NONE, NONE,
		PCIE2, PCIE2, PCIE2, PCIE2} },
	{12, {NONE, NONE, NONE, NONE,
		PCIE2, PCIE2, PCIE2, PCIE2} },
	{13, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		PCIE2, PCIE2, PCIE2, PCIE2} },
	{14, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		PCIE2, PCIE2, PCIE2, PCIE2} },
	{15, {NONE, NONE, NONE, NONE,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{16, {NONE, NONE, NONE, NONE,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{17, {NONE, NONE, NONE, NONE,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{18, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{19, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{20, {INTERLAKEN, INTERLAKEN, INTERLAKEN, INTERLAKEN,
		SRIO1, SRIO1, SRIO1, SRIO1} },
	{}
};
static const struct serdes_config serdes4_cfg_tbl[] = {
	/* SerDes 4 */
	{3, {NONE, NONE, NONE, NONE, PCIE4, PCIE4, PCIE4, PCIE4} },
	{4, {NONE, NONE, NONE, NONE, PCIE4, PCIE4, PCIE4, PCIE4} },
	{5, {NONE, NONE, NONE, NONE, SRIO2, SRIO2, SRIO2, SRIO2} },
	{6, {NONE, NONE, NONE, NONE, SRIO2, SRIO2, SRIO2, SRIO2} },
	{7, {NONE, NONE, NONE, NONE, SRIO2, SRIO2, SRIO2, SRIO2} },
	{8, {NONE, NONE, NONE, NONE, SRIO2, SRIO2, SRIO2, SRIO2} },
	{9, {NONE, NONE, NONE, NONE, PCIE4, PCIE4, SATA1, SATA2} },
	{10, {NONE, NONE, NONE, NONE, PCIE4, PCIE4, SATA1, SATA2} },
	{11, {NONE, NONE, NONE, NONE, AURORA, AURORA, SATA1, SATA2} },
	{12, {NONE, NONE, NONE, NONE, AURORA, AURORA, SATA1, SATA2} },
	{13, {NONE, NONE, NONE, NONE, AURORA, AURORA, SRIO2, SRIO2} },
	{14, {NONE, NONE, NONE, NONE, AURORA, AURORA, SRIO2, SRIO2} },
	{15, {NONE, NONE, NONE, NONE, AURORA, AURORA, SRIO2, SRIO2} },
	{16, {NONE, NONE, NONE, NONE, AURORA, AURORA, SRIO2, SRIO2} },
	{18, {NONE, NONE, NONE, NONE, AURORA, AURORA, AURORA, AURORA} },
	{}
}
;
#else
#error "Need to define SerDes protocol"
#endif
static const struct serdes_config *serdes_cfg_tbl[] = {
	serdes1_cfg_tbl,
	serdes2_cfg_tbl,
	serdes3_cfg_tbl,
	serdes4_cfg_tbl,
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
