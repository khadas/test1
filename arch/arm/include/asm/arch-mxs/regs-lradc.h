/*
 * Freescale i.MX28 LRADC Register Definitions
 *
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 *
 * Based on code from LTIB:
 * Copyright 2008-2009 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#ifndef __MX28_REGS_LRADC_H__
#define __MX28_REGS_LRADC_H__

#include <asm/imx-common/regs-common.h>

#ifndef	__ASSEMBLY__
struct mxs_lradc_regs {
	mxs_reg_32(hw_lradc_ctrl0);
	mxs_reg_32(hw_lradc_ctrl1);
	mxs_reg_32(hw_lradc_ctrl2);
	mxs_reg_32(hw_lradc_ctrl3);
	mxs_reg_32(hw_lradc_status);
	mxs_reg_32(hw_lradc_ch0);
	mxs_reg_32(hw_lradc_ch1);
	mxs_reg_32(hw_lradc_ch2);
	mxs_reg_32(hw_lradc_ch3);
	mxs_reg_32(hw_lradc_ch4);
	mxs_reg_32(hw_lradc_ch5);
	mxs_reg_32(hw_lradc_ch6);
	mxs_reg_32(hw_lradc_ch7);
	mxs_reg_32(hw_lradc_delay0);
	mxs_reg_32(hw_lradc_delay1);
	mxs_reg_32(hw_lradc_delay2);
	mxs_reg_32(hw_lradc_delay3);
	mxs_reg_32(hw_lradc_debug0);
	mxs_reg_32(hw_lradc_debug1);
	mxs_reg_32(hw_lradc_conversion);
	mxs_reg_32(hw_lradc_ctrl4);
	mxs_reg_32(hw_lradc_treshold0);
	mxs_reg_32(hw_lradc_treshold1);
	mxs_reg_32(hw_lradc_version);
};
#endif

#define	LRADC_CTRL0_SFTRST					(1 << 31)
#define	LRADC_CTRL0_CLKGATE					(1 << 30)
#define	LRADC_CTRL0_ONCHIP_GROUNDREF				(1 << 26)
#define	LRADC_CTRL0_BUTTON1_DETECT_ENABLE			(1 << 25)
#define	LRADC_CTRL0_BUTTON0_DETECT_ENABLE			(1 << 24)
#define	LRADC_CTRL0_TOUCH_DETECT_ENABLE				(1 << 23)
#define	LRADC_CTRL0_TOUCH_SCREEN_TYPE				(1 << 22)
#define	LRADC_CTRL0_YNLRSW					(1 << 21)
#define	LRADC_CTRL0_YPLLSW_MASK					(0x3 << 19)
#define	LRADC_CTRL0_YPLLSW_OFFSET				19
#define	LRADC_CTRL0_XNURSW_MASK					(0x3 << 17)
#define	LRADC_CTRL0_XNURSW_OFFSET				17
#define	LRADC_CTRL0_XPULSW					(1 << 16)
#define	LRADC_CTRL0_SCHEDULE_MASK				0xff
#define	LRADC_CTRL0_SCHEDULE_OFFSET				0

#define	LRADC_CTRL1_BUTTON1_DETECT_IRQ_EN			(1 << 28)
#define	LRADC_CTRL1_BUTTON0_DETECT_IRQ_EN			(1 << 27)
#define	LRADC_CTRL1_THRESHOLD1_DETECT_IRQ_EN			(1 << 26)
#define	LRADC_CTRL1_THRESHOLD0_DETECT_IRQ_EN			(1 << 25)
#define	LRADC_CTRL1_TOUCH_DETECT_IRQ_EN				(1 << 24)
#define	LRADC_CTRL1_LRADC7_IRQ_EN				(1 << 23)
#define	LRADC_CTRL1_LRADC6_IRQ_EN				(1 << 22)
#define	LRADC_CTRL1_LRADC5_IRQ_EN				(1 << 21)
#define	LRADC_CTRL1_LRADC4_IRQ_EN				(1 << 20)
#define	LRADC_CTRL1_LRADC3_IRQ_EN				(1 << 19)
#define	LRADC_CTRL1_LRADC2_IRQ_EN				(1 << 18)
#define	LRADC_CTRL1_LRADC1_IRQ_EN				(1 << 17)
#define	LRADC_CTRL1_LRADC0_IRQ_EN				(1 << 16)
#define	LRADC_CTRL1_BUTTON1_DETECT_IRQ				(1 << 12)
#define	LRADC_CTRL1_BUTTON0_DETECT_IRQ				(1 << 11)
#define	LRADC_CTRL1_THRESHOLD1_DETECT_IRQ			(1 << 10)
#define	LRADC_CTRL1_THRESHOLD0_DETECT_IRQ			(1 << 9)
#define	LRADC_CTRL1_TOUCH_DETECT_IRQ				(1 << 8)
#define	LRADC_CTRL1_LRADC7_IRQ					(1 << 7)
#define	LRADC_CTRL1_LRADC6_IRQ					(1 << 6)
#define	LRADC_CTRL1_LRADC5_IRQ					(1 << 5)
#define	LRADC_CTRL1_LRADC4_IRQ					(1 << 4)
#define	LRADC_CTRL1_LRADC3_IRQ					(1 << 3)
#define	LRADC_CTRL1_LRADC2_IRQ					(1 << 2)
#define	LRADC_CTRL1_LRADC1_IRQ					(1 << 1)
#define	LRADC_CTRL1_LRADC0_IRQ					(1 << 0)

#define	LRADC_CTRL2_DIVIDE_BY_TWO_MASK				(0xff << 24)
#define	LRADC_CTRL2_DIVIDE_BY_TWO_OFFSET			24
#define	LRADC_CTRL2_TEMPSENSE_PWD				(1 << 15)
#define	LRADC_CTRL2_VTHSENSE_MASK				(0x3 << 13)
#define	LRADC_CTRL2_VTHSENSE_OFFSET				13
#define	LRADC_CTRL2_DISABLE_MUXAMP_BYPASS			(1 << 12)
#define	LRADC_CTRL2_TEMP_SENSOR_IENABLE1			(1 << 9)
#define	LRADC_CTRL2_TEMP_SENSOR_IENABLE0			(1 << 8)
#define	LRADC_CTRL2_TEMP_ISRC1_MASK				(0xf << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_OFFSET				4
#define	LRADC_CTRL2_TEMP_ISRC1_300				(0xf << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_280				(0xe << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_260				(0xd << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_240				(0xc << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_220				(0xb << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_200				(0xa << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_180				(0x9 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_160				(0x8 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_140				(0x7 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_120				(0x6 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_100				(0x5 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_80				(0x4 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_60				(0x3 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_40				(0x2 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_20				(0x1 << 4)
#define	LRADC_CTRL2_TEMP_ISRC1_ZERO				(0x0 << 4)
#define	LRADC_CTRL2_TEMP_ISRC0_MASK				(0xf << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_OFFSET				0
#define	LRADC_CTRL2_TEMP_ISRC0_300				(0xf << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_280				(0xe << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_260				(0xd << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_240				(0xc << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_220				(0xb << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_200				(0xa << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_180				(0x9 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_160				(0x8 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_140				(0x7 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_120				(0x6 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_100				(0x5 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_80				(0x4 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_60				(0x3 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_40				(0x2 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_20				(0x1 << 0)
#define	LRADC_CTRL2_TEMP_ISRC0_ZERO				(0x0 << 0)

#define	LRADC_CTRL3_DISCARD_MASK				(0x3 << 24)
#define	LRADC_CTRL3_DISCARD_OFFSET				24
#define	LRADC_CTRL3_DISCARD_1_SAMPLE				(0x1 << 24)
#define	LRADC_CTRL3_DISCARD_2_SAMPLES				(0x2 << 24)
#define	LRADC_CTRL3_DISCARD_3_SAMPLES				(0x3 << 24)
#define	LRADC_CTRL3_FORCE_ANALOG_PWUP				(1 << 23)
#define	LRADC_CTRL3_FORCE_ANALOG_PWDN				(1 << 22)
#define	LRADC_CTRL3_CYCLE_TIME_MASK				(0x3 << 8)
#define	LRADC_CTRL3_CYCLE_TIME_OFFSET				8
#define	LRADC_CTRL3_CYCLE_TIME_6MHZ				(0x0 << 8)
#define	LRADC_CTRL3_CYCLE_TIME_4MHZ				(0x1 << 8)
#define	LRADC_CTRL3_CYCLE_TIME_3MHZ				(0x2 << 8)
#define	LRADC_CTRL3_CYCLE_TIME_2MHZ				(0x3 << 8)
#define	LRADC_CTRL3_HIGH_TIME_MASK				(0x3 << 4)
#define	LRADC_CTRL3_HIGH_TIME_OFFSET				4
#define	LRADC_CTRL3_HIGH_TIME_42NS				(0x0 << 4)
#define	LRADC_CTRL3_HIGH_TIME_83NS				(0x1 << 4)
#define	LRADC_CTRL3_HIGH_TIME_125NS				(0x2 << 4)
#define	LRADC_CTRL3_HIGH_TIME_250NS				(0x3 << 4)
#define	LRADC_CTRL3_DELAY_CLOCK					(1 << 1)
#define	LRADC_CTRL3_INVERT_CLOCK				(1 << 0)

#define	LRADC_STATUS_BUTTON1_PRESENT				(1 << 28)
#define	LRADC_STATUS_BUTTON0_PRESENT				(1 << 27)
#define	LRADC_STATUS_TEMP1_PRESENT				(1 << 26)
#define	LRADC_STATUS_TEMP0_PRESENT				(1 << 25)
#define	LRADC_STATUS_TOUCH_PANEL_PRESENT			(1 << 24)
#define	LRADC_STATUS_CHANNEL7_PRESENT				(1 << 23)
#define	LRADC_STATUS_CHANNEL6_PRESENT				(1 << 22)
#define	LRADC_STATUS_CHANNEL5_PRESENT				(1 << 21)
#define	LRADC_STATUS_CHANNEL4_PRESENT				(1 << 20)
#define	LRADC_STATUS_CHANNEL3_PRESENT				(1 << 19)
#define	LRADC_STATUS_CHANNEL2_PRESENT				(1 << 18)
#define	LRADC_STATUS_CHANNEL1_PRESENT				(1 << 17)
#define	LRADC_STATUS_CHANNEL0_PRESENT				(1 << 16)
#define	LRADC_STATUS_BUTTON1_DETECT_RAW				(1 << 2)
#define	LRADC_STATUS_BUTTON0_DETECT_RAW				(1 << 1)
#define	LRADC_STATUS_TOUCH_DETECT_RAW				(1 << 0)

#define	LRADC_CH_TOGGLE						(1 << 31)
#define	LRADC_CH7_TESTMODE_TOGGLE				(1 << 30)
#define	LRADC_CH_ACCUMULATE					(1 << 29)
#define	LRADC_CH_NUM_SAMPLES_MASK				(0x1f << 24)
#define	LRADC_CH_NUM_SAMPLES_OFFSET				24
#define	LRADC_CH_VALUE_MASK					0x3ffff
#define	LRADC_CH_VALUE_OFFSET					0

#define	LRADC_DELAY_TRIGGER_LRADCS_MASK				(0xff << 24)
#define	LRADC_DELAY_TRIGGER_LRADCS_OFFSET			24
#define	LRADC_DELAY_KICK					(1 << 20)
#define	LRADC_DELAY_TRIGGER_DELAYS_MASK				(0xf << 16)
#define	LRADC_DELAY_TRIGGER_DELAYS_OFFSET			16
#define	LRADC_DELAY_LOOP_COUNT_MASK				(0x1f << 11)
#define	LRADC_DELAY_LOOP_COUNT_OFFSET				11
#define	LRADC_DELAY_DELAY_MASK					0x7ff
#define	LRADC_DELAY_DELAY_OFFSET				0

#define	LRADC_DEBUG0_READONLY_MASK				(0xffff << 16)
#define	LRADC_DEBUG0_READONLY_OFFSET				16
#define	LRADC_DEBUG0_STATE_MASK					(0xfff << 0)
#define	LRADC_DEBUG0_STATE_OFFSET				0

#define	LRADC_DEBUG1_REQUEST_MASK				(0xff << 16)
#define	LRADC_DEBUG1_REQUEST_OFFSET				16
#define	LRADC_DEBUG1_TESTMODE_COUNT_MASK			(0x1f << 8)
#define	LRADC_DEBUG1_TESTMODE_COUNT_OFFSET			8
#define	LRADC_DEBUG1_TESTMODE6					(1 << 2)
#define	LRADC_DEBUG1_TESTMODE5					(1 << 1)
#define	LRADC_DEBUG1_TESTMODE					(1 << 0)

#define	LRADC_CONVERSION_AUTOMATIC				(1 << 20)
#define	LRADC_CONVERSION_SCALE_FACTOR_MASK			(0x3 << 16)
#define	LRADC_CONVERSION_SCALE_FACTOR_OFFSET			16
#define	LRADC_CONVERSION_SCALE_FACTOR_NIMH			(0x0 << 16)
#define	LRADC_CONVERSION_SCALE_FACTOR_DUAL_NIMH			(0x1 << 16)
#define	LRADC_CONVERSION_SCALE_FACTOR_LI_ION			(0x2 << 16)
#define	LRADC_CONVERSION_SCALE_FACTOR_ALT_LI_ION		(0x3 << 16)
#define	LRADC_CONVERSION_SCALED_BATT_VOLTAGE_MASK		0x3ff
#define	LRADC_CONVERSION_SCALED_BATT_VOLTAGE_OFFSET		0

#define	LRADC_CTRL4_LRADC7SELECT_MASK				(0xf << 28)
#define	LRADC_CTRL4_LRADC7SELECT_OFFSET				28
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL0			(0x0 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL1			(0x1 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL2			(0x2 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL3			(0x3 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL4			(0x4 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL5			(0x5 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL6			(0x6 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL7			(0x7 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL8			(0x8 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL9			(0x9 << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL10			(0xa << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL11			(0xb << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL12			(0xc << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL13			(0xd << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL14			(0xe << 28)
#define	LRADC_CTRL4_LRADC7SELECT_CHANNEL15			(0xf << 28)
#define	LRADC_CTRL4_LRADC6SELECT_MASK				(0xf << 24)
#define	LRADC_CTRL4_LRADC6SELECT_OFFSET				24
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL0			(0x0 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL1			(0x1 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL2			(0x2 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL3			(0x3 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL4			(0x4 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL5			(0x5 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL6			(0x6 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL7			(0x7 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL8			(0x8 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL9			(0x9 << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL10			(0xa << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL11			(0xb << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL12			(0xc << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL13			(0xd << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL14			(0xe << 24)
#define	LRADC_CTRL4_LRADC6SELECT_CHANNEL15			(0xf << 24)
#define	LRADC_CTRL4_LRADC5SELECT_MASK				(0xf << 20)
#define	LRADC_CTRL4_LRADC5SELECT_OFFSET				20
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL0			(0x0 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL1			(0x1 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL2			(0x2 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL3			(0x3 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL4			(0x4 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL5			(0x5 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL6			(0x6 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL7			(0x7 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL8			(0x8 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL9			(0x9 << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL10			(0xa << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL11			(0xb << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL12			(0xc << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL13			(0xd << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL14			(0xe << 20)
#define	LRADC_CTRL4_LRADC5SELECT_CHANNEL15			(0xf << 20)
#define	LRADC_CTRL4_LRADC4SELECT_MASK				(0xf << 16)
#define	LRADC_CTRL4_LRADC4SELECT_OFFSET				16
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL0			(0x0 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL1			(0x1 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL2			(0x2 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL3			(0x3 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL4			(0x4 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL5			(0x5 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL6			(0x6 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL7			(0x7 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL8			(0x8 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL9			(0x9 << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL10			(0xa << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL11			(0xb << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL12			(0xc << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL13			(0xd << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL14			(0xe << 16)
#define	LRADC_CTRL4_LRADC4SELECT_CHANNEL15			(0xf << 16)
#define	LRADC_CTRL4_LRADC3SELECT_MASK				(0xf << 12)
#define	LRADC_CTRL4_LRADC3SELECT_OFFSET				12
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL0			(0x0 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL1			(0x1 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL2			(0x2 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL3			(0x3 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL4			(0x4 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL5			(0x5 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL6			(0x6 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL7			(0x7 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL8			(0x8 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL9			(0x9 << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL10			(0xa << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL11			(0xb << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL12			(0xc << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL13			(0xd << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL14			(0xe << 12)
#define	LRADC_CTRL4_LRADC3SELECT_CHANNEL15			(0xf << 12)
#define	LRADC_CTRL4_LRADC2SELECT_MASK				(0xf << 8)
#define	LRADC_CTRL4_LRADC2SELECT_OFFSET				8
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL0			(0x0 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL1			(0x1 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL2			(0x2 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL3			(0x3 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL4			(0x4 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL5			(0x5 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL6			(0x6 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL7			(0x7 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL8			(0x8 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL9			(0x9 << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL10			(0xa << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL11			(0xb << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL12			(0xc << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL13			(0xd << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL14			(0xe << 8)
#define	LRADC_CTRL4_LRADC2SELECT_CHANNEL15			(0xf << 8)
#define	LRADC_CTRL4_LRADC1SELECT_MASK				(0xf << 4)
#define	LRADC_CTRL4_LRADC1SELECT_OFFSET				4
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL0			(0x0 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL1			(0x1 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL2			(0x2 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL3			(0x3 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL4			(0x4 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL5			(0x5 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL6			(0x6 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL7			(0x7 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL8			(0x8 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL9			(0x9 << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL10			(0xa << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL11			(0xb << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL12			(0xc << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL13			(0xd << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL14			(0xe << 4)
#define	LRADC_CTRL4_LRADC1SELECT_CHANNEL15			(0xf << 4)
#define	LRADC_CTRL4_LRADC0SELECT_MASK				0xf
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL0			(0x0 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL1			(0x1 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL2			(0x2 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL3			(0x3 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL4			(0x4 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL5			(0x5 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL6			(0x6 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL7			(0x7 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL8			(0x8 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL9			(0x9 << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL10			(0xa << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL11			(0xb << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL12			(0xc << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL13			(0xd << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL14			(0xe << 0)
#define	LRADC_CTRL4_LRADC0SELECT_CHANNEL15			(0xf << 0)

#define	LRADC_THRESHOLD_ENABLE					(1 << 24)
#define	LRADC_THRESHOLD_BATTCHRG_DISABLE			(1 << 23)
#define	LRADC_THRESHOLD_CHANNEL_SEL_MASK			(0x7 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_OFFSET			20
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL0			(0x0 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL1			(0x1 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL2			(0x2 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL3			(0x3 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL4			(0x4 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL5			(0x5 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL6			(0x6 << 20)
#define	LRADC_THRESHOLD_CHANNEL_SEL_CHANNEL7			(0x7 << 20)
#define	LRADC_THRESHOLD_SETTING_MASK				(0x3 << 18)
#define	LRADC_THRESHOLD_SETTING_OFFSET				18
#define	LRADC_THRESHOLD_SETTING_NO_COMPARE			(0x0 << 18)
#define	LRADC_THRESHOLD_SETTING_DETECT_LOW			(0x1 << 18)
#define	LRADC_THRESHOLD_SETTING_DETECT_HIGH			(0x2 << 18)
#define	LRADC_THRESHOLD_SETTING_RESERVED			(0x3 << 18)
#define	LRADC_THRESHOLD_VALUE_MASK				0x3ffff
#define	LRADC_THRESHOLD_VALUE_OFFSET				0

#define	LRADC_VERSION_MAJOR_MASK				(0xff << 24)
#define	LRADC_VERSION_MAJOR_OFFSET				24
#define	LRADC_VERSION_MINOR_MASK				(0xff << 16)
#define	LRADC_VERSION_MINOR_OFFSET				16
#define	LRADC_VERSION_STEP_MASK					0xffff
#define	LRADC_VERSION_STEP_OFFSET				0

#endif	/* __MX28_REGS_LRADC_H__ */
