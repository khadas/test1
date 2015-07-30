/*
 * (C) Copyright 2015 Linaro
 * Peter Griffin <peter.griffin@linaro.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __HI6553_PMIC_H__
#define __HI6553_PMIC_H__

/* Registers */
enum {
	HI6553_VERSION_REG = 0x000,
	HI6553_ENABLE2_LDO1_8 = 0x029,
	HI6553_DISABLE2_LDO1_8,
	HI6553_ONOFF_STATUS2_LDO1_8,
	HI6553_ENABLE3_LDO9_16,
	HI6553_DISABLE3_LDO9_16,
	HI6553_ONOFF_STATUS3_LDO9_16,

	HI6553_DISABLE6_XO_CLK = 0x036,
	HI6553_PERI_EN_MARK = 0x040,
	HI6553_BUCK2_REG1 = 0x04a,
	HI6553_BUCK2_REG5 = 0x04e,
	HI6553_BUCK2_REG6,

	HI6553_BUCK3_REG3 = 0x054,
	HI6553_BUCK3_REG5 = 0x056,
	HI6553_BUCK3_REG6,
	HI6553_BUCK4_REG2 = 0x05b,
	HI6553_BUCK4_REG5 = 0x05e,
	HI6553_BUCK4_REG6,

	HI6553_CLK_TOP0 = 0x063,
	HI6553_CLK_TOP3 = 0x066,
	HI6553_CLK_TOP4,
	HI6553_VSET_BUCK2_ADJ = 0x06d,
	HI6553_VSET_BUCK3_ADJ,
	HI6553_LDO7_REG_ADJ = 0x078,
	HI6553_LDO10_REG_ADJ = 0x07b,
	HI6553_LDO19_REG_ADJ = 0x084,
	HI6553_LDO20_REG_ADJ,
	HI6553_DR_LED_CTRL = 0x098,
	HI6553_DR_OUT_CTRL,
	HI6553_DR3_ISET,
	HI6553_DR3_START_DEL,
	HI6553_DR4_ISET,
	HI6553_DR4_START_DEL,
	HI6553_DR345_TIM_CONF0 = 0x0a0,
	HI6553_NP_REG_ADJ1 = 0x0be,
	HI6553_NP_REG_CHG = 0x0c0,
	HI6553_BUCK01_CTRL2 = 0x0d9,
	HI6553_BUCK0_CTRL1 = 0x0dd,
	HI6553_BUCK0_CTRL5 = 0x0e1,
	HI6553_BUCK0_CTRL7 = 0x0e3,
	HI6553_BUCK1_CTRL1 = 0x0e8,
	HI6553_BUCK1_CTRL5 = 0x0ec,
	HI6553_BUCK1_CTRL7 = 0x0ef,
	HI6553_CLK19M2_600_586_EN = 0x0fe,
};

#define HI6553_DISABLE6_XO_CLK_BB		(1 << 0)
#define HI6553_DISABLE6_XO_CLK_CONN		(1 << 1)
#define HI6553_DISABLE6_XO_CLK_NFC		(1 << 2)
#define HI6553_DISABLE6_XO_CLK_RF1		(1 << 3)
#define HI6553_DISABLE6_XO_CLK_RF2		(1 << 4)

#define HI6553_LED_START_DELAY_TIME		0x00
#define HI6553_LED_ELEC_VALUE			0x07
#define HI6553_LED_LIGHT_TIME			0xf0
#define HI6553_LED_GREEN_ENABLE			(1 << 1)
#define HI6553_LED_OUT_CTRL			0x00

#define HI6553_PMU_V300				0x30
#define HI6553_PMU_V310				0x31

int power_hi6553_init(u8 *base);

#endif	/* __HI6553_PMIC_H__ */
