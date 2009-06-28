/*
 * Copyright (c) 2009 Wind River Systems, Inc.
 * Tom Rix <Tom.Rix at windriver.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Derived from code on omapzoom, git://git.omapzoom.com/repo/u-boot.git
 *
 * Copyright (C) 2007-2009 Texas Instruments, Inc.
 */

#ifndef TWL4030_H
#define TWL4030_H

#include <common.h>
#include <i2c.h>

/* I2C chip addresses */

/* USB */
#define TWL4030_CHIP_USB				0x48
/* AUD */
#define TWL4030_CHIP_AUDIO_VOICE			0x49
#define TWL4030_CHIP_GPIO				0x49
#define TWL4030_CHIP_INTBR				0x49
#define TWL4030_CHIP_PIH				0x49
#define TWL4030_CHIP_TEST				0x49
/* AUX */
#define TWL4030_CHIP_KEYPAD				0x4a
#define TWL4030_CHIP_MADC				0x4a
#define TWL4030_CHIP_INTERRUPTS				0x4a
#define TWL4030_CHIP_LED				0x4a
#define TWL4030_CHIP_MAIN_CHARGE			0x4a
#define TWL4030_CHIP_PRECHARGE				0x4a
#define TWL4030_CHIP_PWM0				0x4a
#define TWL4030_CHIP_PWM1				0x4a
#define TWL4030_CHIP_PWMA				0x4a
#define TWL4030_CHIP_PWMB				0x4a
/* POWER */
#define TWL4030_CHIP_BACKUP				0x4b
#define TWL4030_CHIP_INT				0x4b
#define TWL4030_CHIP_PM_MASTER				0x4b
#define TWL4030_CHIP_PM_RECEIVER			0x4b
#define TWL4030_CHIP_RTC				0x4b
#define TWL4030_CHIP_SECURED_REG			0x4b

/* Register base addresses */

/* USB */
#define TWL4030_BASEADD_USB				0x0000
/* AUD */
#define TWL4030_BASEADD_AUDIO_VOICE			0x0000
#define TWL4030_BASEADD_GPIO				0x0098
#define TWL4030_BASEADD_INTBR				0x0085
#define TWL4030_BASEADD_PIH				0x0080
#define TWL4030_BASEADD_TEST				0x004C
/* AUX */
#define TWL4030_BASEADD_INTERRUPTS			0x00B9
#define TWL4030_BASEADD_LED				0x00EE
#define TWL4030_BASEADD_MADC				0x0000
#define TWL4030_BASEADD_MAIN_CHARGE			0x0074
#define TWL4030_BASEADD_PRECHARGE			0x00AA
#define TWL4030_BASEADD_PWM0				0x00F8
#define TWL4030_BASEADD_PWM1				0x00FB
#define TWL4030_BASEADD_PWMA				0x00EF
#define TWL4030_BASEADD_PWMB				0x00F1
#define TWL4030_BASEADD_KEYPAD				0x00D2
/* POWER */
#define TWL4030_BASEADD_BACKUP				0x0014
#define TWL4030_BASEADD_INT				0x002E
#define TWL4030_BASEADD_PM_MASTER			0x0036
#define TWL4030_BASEADD_PM_RECIEVER			0x005B
#define TWL4030_BASEADD_RTC				0x001C
#define TWL4030_BASEADD_SECURED_REG			0x0000

/*
 * Power Management Master
 */
#define TWL4030_PM_MASTER_CFG_P1_TRANSITION		0x36
#define TWL4030_PM_MASTER_CFG_P2_TRANSITION		0x37
#define TWL4030_PM_MASTER_CFG_P3_TRANSITION		0x38
#define TWL4030_PM_MASTER_CFG_P123_TRANSITION		0x39
#define TWL4030_PM_MASTER_STS_BOOT			0x3A
#define TWL4030_PM_MASTER_CFG_BOOT			0x3B
#define TWL4030_PM_MASTER_SHUNDAN			0x3C
#define TWL4030_PM_MASTER_BOOT_BCI			0x3D
#define TWL4030_PM_MASTER_CFG_PWRANA1			0x3E
#define TWL4030_PM_MASTER_CFG_PWRANA2			0x3F
#define TWL4030_PM_MASTER_BGAP_TRIM			0x40
#define TWL4030_PM_MASTER_BACKUP_MISC_STS		0x41
#define TWL4030_PM_MASTER_BACKUP_MISC_CFG		0x42
#define TWL4030_PM_MASTER_BACKUP_MISC_TST		0x43
#define TWL4030_PM_MASTER_PROTECT_KEY			0x44
#define TWL4030_PM_MASTER_STS_HW_CONDITIONS		0x45
#define TWL4030_PM_MASTER_P1_SW_EVENTS			0x46
#define TWL4030_PM_MASTER_P2_SW_EVENTS			0x47
#define TWL4030_PM_MASTER_P3_SW_EVENTS			0x48
#define TWL4030_PM_MASTER_STS_P123_STATE		0x49
#define TWL4030_PM_MASTER_PB_CFG			0x4A
#define TWL4030_PM_MASTER_PB_WORD_MSB			0x4B
#define TWL4030_PM_MASTER_PB_WORD_LSB			0x4C
#define TWL4030_PM_MASTER_SEQ_ADD_W2P			0x52
#define TWL4030_PM_MASTER_SEQ_ADD_P2A			0x53
#define TWL4030_PM_MASTER_SEQ_ADD_A2W			0x54
#define TWL4030_PM_MASTER_SEQ_ADD_A2S			0x55
#define TWL4030_PM_MASTER_SEQ_ADD_S2A12			0x56
#define TWL4030_PM_MASTER_SEQ_ADD_S2A3			0x57
#define TWL4030_PM_MASTER_SEQ_ADD_WARM			0x58
#define TWL4030_PM_MASTER_MEMORY_ADDRESS		0x59
#define TWL4030_PM_MASTER_MEMORY_DATA			0x5A
#define TWL4030_PM_MASTER_SC_CONFIG			0x5B
#define TWL4030_PM_MASTER_SC_DETECT1			0x5C
#define TWL4030_PM_MASTER_SC_DETECT2			0x5D
#define TWL4030_PM_MASTER_WATCHDOG_CFG			0x5E
#define TWL4030_PM_MASTER_IT_CHECK_CFG			0x5F
#define TWL4030_PM_MASTER_VIBRATOR_CFG			0x60
#define TWL4030_PM_MASTER_DCDC_GLOBAL_CFG		0x61
#define TWL4030_PM_MASTER_VDD1_TRIM1			0x62
#define TWL4030_PM_MASTER_VDD1_TRIM2			0x63
#define TWL4030_PM_MASTER_VDD2_TRIM1			0x64
#define TWL4030_PM_MASTER_VDD2_TRIM2			0x65
#define TWL4030_PM_MASTER_VIO_TRIM1			0x66
#define TWL4030_PM_MASTER_VIO_TRIM2			0x67
#define TWL4030_PM_MASTER_MISC_CFG			0x68
#define TWL4030_PM_MASTER_LS_TST_A			0x69
#define TWL4030_PM_MASTER_LS_TST_B			0x6A
#define TWL4030_PM_MASTER_LS_TST_C			0x6B
#define TWL4030_PM_MASTER_LS_TST_D			0x6C
#define TWL4030_PM_MASTER_BB_CFG			0x6D
#define TWL4030_PM_MASTER_MISC_TST			0x6E
#define TWL4030_PM_MASTER_TRIM1				0x6F
/* P[1-3]_SW_EVENTS */
#define TWL4030_PM_MASTER_SW_EVENTS_STOPON_PWRON	(1 << 6)
#define TWL4030_PM_MASTER_SW_EVENTS_STOPON_SYSEN	(1 << 5)
#define TWL4030_PM_MASTER_SW_EVENTS_ENABLE_WARMRESET	(1 << 4)
#define TWL4030_PM_MASTER_SW_EVENTS_LVL_WAKEUP		(1 << 3)
#define TWL4030_PM_MASTER_SW_EVENTS_DEVACT		(1 << 2)
#define TWL4030_PM_MASTER_SW_EVENTS_DEVSLP		(1 << 1)
#define TWL4030_PM_MASTER_SW_EVENTS_DEVOFF		(1 << 0)

/* Power Managment Receiver */
#define TWL4030_PM_RECEIVER_VUSB1V5_DEV_GRP		0xCC
#define TWL4030_PM_RECEIVER_VUSB1V5_TYPE		0xCD
#define TWL4030_PM_RECEIVER_VUSB1V5_REMAP		0xCE
#define TWL4030_PM_RECEIVER_VUSB1V8_DEV_GRP		0xCF
#define TWL4030_PM_RECEIVER_VUSB1V8_TYPE		0xD0
#define TWL4030_PM_RECEIVER_VUSB1V8_REMAP		0xD1
#define TWL4030_PM_RECEIVER_VUSB3V1_DEV_GRP		0xD2
#define TWL4030_PM_RECEIVER_VUSB3V1_TYPE		0xD3
#define TWL4030_PM_RECEIVER_VUSB3V1_REMAP		0xD4
#define TWL4030_PM_RECEIVER_VUSBCP_DEV_GRP		0xD5
#define TWL4030_PM_RECEIVER_VUSBCP_DEV_TYPE		0xD6
#define TWL4030_PM_RECEIVER_VUSBCP_DEV_REMAP		0xD7
#define TWL4030_PM_RECEIVER_VUSB_DEDICATED1		0xD8
#define TWL4030_PM_RECEIVER_VUSB_DEDICATED2		0xD9

/* Keypad */
#define TWL4030_KEYPAD_KEYP_CTRL_REG			0xD2
#define TWL4030_KEYPAD_KEY_DEB_REG			0xD3
#define TWL4030_KEYPAD_LONG_KEY_REG1			0xD4
#define TWL4030_KEYPAD_LK_PTV_REG			0xD5
#define TWL4030_KEYPAD_TIME_OUT_REG1			0xD6
#define TWL4030_KEYPAD_TIME_OUT_REG2			0xD7
#define TWL4030_KEYPAD_KBC_REG				0xD8
#define TWL4030_KEYPAD_KBR_REG				0xD9
#define TWL4030_KEYPAD_KEYP_SMS				0xDA
#define TWL4030_KEYPAD_FULL_CODE_7_0			0xDB
#define TWL4030_KEYPAD_FULL_CODE_15_8			0xDC
#define TWL4030_KEYPAD_FULL_CODE_23_16			0xDD
#define TWL4030_KEYPAD_FULL_CODE_31_24			0xDE
#define TWL4030_KEYPAD_FULL_CODE_39_32			0xDF
#define TWL4030_KEYPAD_FULL_CODE_47_40			0xE0
#define TWL4030_KEYPAD_FULL_CODE_55_48			0xE1
#define TWL4030_KEYPAD_FULL_CODE_63_56			0xE2
#define TWL4030_KEYPAD_KEYP_ISR1			0xE3
#define TWL4030_KEYPAD_KEYP_IMR1			0xE4
#define TWL4030_KEYPAD_KEYP_ISR2			0xE5
#define TWL4030_KEYPAD_KEYP_IMR2			0xE6
#define TWL4030_KEYPAD_KEYP_SIR				0xE7
#define TWL4030_KEYPAD_KEYP_EDR				0xE8
#define TWL4030_KEYPAD_KEYP_SIH_CTRL			0xE9

#define TWL4030_KEYPAD_CTRL_KBD_ON			(1 << 6)
#define TWL4030_KEYPAD_CTRL_RP_EN			(1 << 5)
#define TWL4030_KEYPAD_CTRL_TOLE_EN			(1 << 4)
#define TWL4030_KEYPAD_CTRL_TOE_EN			(1 << 3)
#define TWL4030_KEYPAD_CTRL_LK_EN			(1 << 2)
#define TWL4030_KEYPAD_CTRL_SOFTMODEN			(1 << 1)
#define TWL4030_KEYPAD_CTRL_SOFT_NRST			(1 << 0)

/* USB */
#define TWL4030_USB_FUNC_CTRL				(0x04)
#define TWL4030_USB_OPMODE_MASK				(3 << 3)
#define TWL4030_USB_XCVRSELECT_MASK			(3 << 0)
#define TWL4030_USB_IFC_CTRL				(0x07)
#define TWL4030_USB_CARKITMODE				(1 << 2)
#define TWL4030_USB_POWER_CTRL				(0xAC)
#define TWL4030_USB_OTG_ENAB				(1 << 5)
#define TWL4030_USB_PHY_PWR_CTRL			(0xFD)
#define TWL4030_USB_PHYPWD				(1 << 0)
#define TWL4030_USB_PHY_CLK_CTRL			(0xFE)
#define TWL4030_USB_CLOCKGATING_EN			(1 << 2)
#define TWL4030_USB_CLK32K_EN				(1 << 1)
#define TWL4030_USB_REQ_PHY_DPLL_CLK			(1 << 0)
#define TWL4030_USB_PHY_CLK_CTRL_STS			(0xFF)
#define TWL4030_USB_PHY_DPLL_CLK			(1 << 0)

/*
 * Convience functions to read and write from TWL4030
 *
 * chip_no is the i2c address, it must be one of the chip addresses
 *   defined at the top of this file with the prefix TWL4030_CHIP_
 *   examples are TWL4030_CHIP_PM_RECEIVER and TWL4030_CHIP_KEYPAD
 *
 * val is the data either written to or read from the twl4030
 *
 * reg is the register to act on, it must be one of the defines
 *   above and with the format TWL4030_<chip suffix>_<register name>
 *   examples are TWL4030_PM_RECEIVER_VMMC1_DEV_GRP and
 *   TWL4030_LED_LEDEN.
 */
static inline int twl4030_i2c_write_u8(u8 chip_no, u8 val, u8 reg)
{
	return i2c_write(chip_no, reg, 1, &val, 1);
}

static inline int twl4030_i2c_read_u8(u8 chip_no, u8 *val, u8 reg)
{
	return i2c_read(chip_no, reg, 1, val, 1);
}

/* For hardware resetting */
void twl4030_power_reset_init(void);

#endif /* TWL4030_H */
