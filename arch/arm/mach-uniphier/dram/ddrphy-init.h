/*
 * Copyright (C) 2016 Socionext Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef ARCH_DDRPHY_INIT_H
#define ARCH_DDRPHY_INTT_H

#include <linux/compiler.h>
#include <linux/types.h>

/* for LD4, Pro4, sLD8 */
#define NR_DATX8_PER_DDRPHY	2

int uniphier_ld4_ddrphy_init(void __iomem *phy_base, int freq, bool ddr3plus);
void ddrphy_prepare_training(void __iomem *phy_base, int rank);
int ddrphy_training(void __iomem *phy_base);

#endif /* ARCH_DDRPHY_INT_H */
