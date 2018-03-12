/*
 * Copyright (C) 2018, STMicroelectronics - All Rights Reserved
 *
 * SPDX-License-Identifier:	GPL-2.0+	BSD-3-Clause
 */

#ifndef __PMIC_STPMU1_H_
#define __PMIC_STPMU1_H_

#define STPMU1_MASK_RESET_BUCK		0x18
#define STPMU1_BUCKX_CTRL_REG(buck)	(0x20 + (buck))
#define STPMU1_VREF_CTRL_REG		0x24
#define STPMU1_LDOX_CTRL_REG(ldo)	(0x25 + (ldo))
#define STPMU1_USB_CTRL_REG		0x40
#define STPMU1_NVM_USER_STATUS_REG	0xb8
#define STPMU1_NVM_USER_CONTROL_REG	0xb9

#define STPMU1_MASK_RESET_BUCK3		BIT(2)

#define STPMU1_BUCK_EN			BIT(0)
#define STPMU1_BUCK_MODE		BIT(1)
#define STPMU1_BUCK_OUTPUT_MASK		GENMASK(7, 2)
#define STPMU1_BUCK_OUTPUT_SHIFT	2
#define STPMU1_BUCK2_1200000V		(24 << STPMU1_BUCK_OUTPUT_SHIFT)
#define STPMU1_BUCK2_1350000V		(30 << STPMU1_BUCK_OUTPUT_SHIFT)
#define STPMU1_BUCK3_1800000V		(39 << STPMU1_BUCK_OUTPUT_SHIFT)

#define STPMU1_VREF_EN			BIT(0)

#define STPMU1_LDO_EN			BIT(0)
#define STPMU1_LDO12356_OUTPUT_MASK	GENMASK(6, 2)
#define STPMU1_LDO12356_OUTPUT_SHIFT	2
#define STPMU1_LDO3_MODE		BIT(7)
#define STPMU1_LDO3_DDR_SEL		31
#define STPMU1_LDO3_1800000		(9 << STPMU1_LDO12356_OUTPUT_SHIFT)
#define STPMU1_LDO4_UV			3300000

#define STPMU1_USB_BOOST_EN		BIT(0)
#define STPMU1_USB_PWR_SW_EN		GENMASK(2, 1)

#define STPMU1_NVM_USER_CONTROL_PROGRAM	BIT(0)
#define STPMU1_NVM_USER_CONTROL_READ	BIT(1)

#define STPMU1_NVM_USER_STATUS_BUSY	BIT(0)
#define STPMU1_NVM_USER_STATUS_ERROR	BIT(1)

#define STPMU1_DEFAULT_START_UP_DELAY_MS	1
#define STPMU1_USB_BOOST_START_UP_DELAY_MS	10

enum {
	STPMU1_BUCK1,
	STPMU1_BUCK2,
	STPMU1_BUCK3,
	STPMU1_BUCK4,
	STPMU1_MAX_BUCK,
};

enum {
	STPMU1_BUCK_MODE_HP,
	STPMU1_BUCK_MODE_LP,
};

enum {
	STPMU1_LDO1,
	STPMU1_LDO2,
	STPMU1_LDO3,
	STPMU1_LDO4,
	STPMU1_LDO5,
	STPMU1_LDO6,
	STPMU1_MAX_LDO,
};

enum {
	STPMU1_LDO_MODE_NORMAL,
	STPMU1_LDO_MODE_BYPASS,
	STPMU1_LDO_MODE_SINK_SOURCE,
};

enum {
	STPMU1_PWR_SW1,
	STPMU1_PWR_SW2,
	STPMU1_MAX_PWR_SW,
};

#endif
