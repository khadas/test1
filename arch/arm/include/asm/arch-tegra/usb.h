/*
 * Copyright (c) 2011 The Chromium OS Authors.
 * Copyright (c) 2013 NVIDIA Corporation
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef _TEGRA_USB_H_
#define _TEGRA_USB_H_

/* USB1_LEGACY_CTRL */
#define USB1_NO_LEGACY_MODE		1

#define VBUS_SENSE_CTL_SHIFT			1
#define VBUS_SENSE_CTL_MASK			(3 << VBUS_SENSE_CTL_SHIFT)
#define VBUS_SENSE_CTL_VBUS_WAKEUP		0
#define VBUS_SENSE_CTL_AB_SESS_VLD_OR_VBUS_WAKEUP	1
#define VBUS_SENSE_CTL_AB_SESS_VLD		2
#define VBUS_SENSE_CTL_A_SESS_VLD		3

/* USBx_IF_USB_SUSP_CTRL_0 */
#define UTMIP_PHY_ENB			        (1 << 12)
#define UTMIP_RESET			        (1 << 11)
#define USB_PHY_CLK_VALID			(1 << 7)
#define USB_SUSP_CLR				(1 << 5)

/* USB2_IF_USB_SUSP_CTRL_0 */
#define ULPI_PHY_ENB				(1 << 13)

/* USBx_UTMIP_MISC_CFG0 */
#define UTMIP_SUSPEND_EXIT_ON_EDGE		(1 << 22)

/* USBx_UTMIP_MISC_CFG1 */
#define UTMIP_PLLU_STABLE_COUNT_SHIFT		6
#define UTMIP_PLLU_STABLE_COUNT_MASK		\
				(0xfff << UTMIP_PLLU_STABLE_COUNT_SHIFT)
#define UTMIP_PLL_ACTIVE_DLY_COUNT_SHIFT	18
#define UTMIP_PLL_ACTIVE_DLY_COUNT_MASK		\
				(0x1f << UTMIP_PLL_ACTIVE_DLY_COUNT_SHIFT)
#define UTMIP_PHY_XTAL_CLOCKEN			(1 << 30)

/* USBx_UTMIP_PLL_CFG1_0 */
#define UTMIP_PLLU_ENABLE_DLY_COUNT_SHIFT	27
#define UTMIP_PLLU_ENABLE_DLY_COUNT_MASK	\
				(0x1f << UTMIP_PLLU_ENABLE_DLY_COUNT_SHIFT)
#define UTMIP_XTAL_FREQ_COUNT_SHIFT		0
#define UTMIP_XTAL_FREQ_COUNT_MASK		0xfff

/* USBx_UTMIP_BIAS_CFG0_0 */
#define UTMIP_HSDISCON_LEVEL_MSB		(1 << 24)
#define UTMIP_OTGPD				(1 << 11)
#define UTMIP_BIASPD				(1 << 10)
#define UTMIP_HSDISCON_LEVEL_SHIFT		2
#define UTMIP_HSDISCON_LEVEL_MASK		\
				(0x3 << UTMIP_HSDISCON_LEVEL_SHIFT)
#define UTMIP_HSSQUELCH_LEVEL_SHIFT		0
#define UTMIP_HSSQUELCH_LEVEL_MASK		\
				(0x3 << UTMIP_HSSQUELCH_LEVEL_SHIFT)

/* USBx_UTMIP_BIAS_CFG1_0 */
#define UTMIP_FORCE_PDTRK_POWERDOWN		1
#define UTMIP_BIAS_PDTRK_COUNT_SHIFT		3
#define UTMIP_BIAS_PDTRK_COUNT_MASK		\
				(0x1f << UTMIP_BIAS_PDTRK_COUNT_SHIFT)

/* USBx_UTMIP_DEBOUNCE_CFG0_0 */
#define UTMIP_DEBOUNCE_CFG0_SHIFT		0
#define UTMIP_DEBOUNCE_CFG0_MASK		0xffff

/* USBx_UTMIP_TX_CFG0_0 */
#define UTMIP_FS_PREAMBLE_J			(1 << 19)

/* USBx_UTMIP_BAT_CHRG_CFG0_0 */
#define UTMIP_PD_CHRG				1

/* USBx_UTMIP_SPARE_CFG0_0 */
#define FUSE_SETUP_SEL				(1 << 3)

/* USBx_UTMIP_HSRX_CFG0_0 */
#define UTMIP_IDLE_WAIT_SHIFT			15
#define UTMIP_IDLE_WAIT_MASK			(0x1f << UTMIP_IDLE_WAIT_SHIFT)
#define UTMIP_ELASTIC_LIMIT_SHIFT		10
#define UTMIP_ELASTIC_LIMIT_MASK		\
				(0x1f << UTMIP_ELASTIC_LIMIT_SHIFT)

/* USBx_UTMIP_HSRX_CFG1_0 */
#define UTMIP_HS_SYNC_START_DLY_SHIFT		1
#define UTMIP_HS_SYNC_START_DLY_MASK		\
				(0x1f << UTMIP_HS_SYNC_START_DLY_SHIFT)

/* USBx_CONTROLLER_2_USB2D_ICUSB_CTRL_0 */
#define IC_ENB1					(1 << 3)

/* PORTSC1, USB1, defined for Tegra20 */
#define PTS1_SHIFT				31
#define PTS1_MASK				(1 << PTS1_SHIFT)
#define STS1					(1 << 30)

#define PTS_UTMI	0
#define PTS_RESERVED	1
#define PTS_ULPI	2
#define PTS_ICUSB_SER	3
#define PTS_HSIC	4

/* SB2_CONTROLLER_2_USB2D_PORTSC1_0 */
#define WKOC				(1 << 22)
#define WKDS				(1 << 21)
#define WKCN				(1 << 20)

/* USBx_UTMIP_XCVR_CFG0_0 */
#define UTMIP_FORCE_PD_POWERDOWN		(1 << 14)
#define UTMIP_FORCE_PD2_POWERDOWN		(1 << 16)
#define UTMIP_FORCE_PDZI_POWERDOWN		(1 << 18)
#define UTMIP_XCVR_LSBIAS_SE			(1 << 21)
#define UTMIP_XCVR_HSSLEW_MSB_SHIFT		25
#define UTMIP_XCVR_HSSLEW_MSB_MASK		\
			(0x7f << UTMIP_XCVR_HSSLEW_MSB_SHIFT)
#define UTMIP_XCVR_SETUP_MSB_SHIFT	22
#define UTMIP_XCVR_SETUP_MSB_MASK	(0x7 << UTMIP_XCVR_SETUP_MSB_SHIFT)
#define UTMIP_XCVR_SETUP_SHIFT		0
#define UTMIP_XCVR_SETUP_MASK		(0xf << UTMIP_XCVR_SETUP_SHIFT)

/* USBx_UTMIP_XCVR_CFG1_0 */
#define UTMIP_XCVR_TERM_RANGE_ADJ_SHIFT		18
#define UTMIP_XCVR_TERM_RANGE_ADJ_MASK		\
			(0xf << UTMIP_XCVR_TERM_RANGE_ADJ_SHIFT)
#define UTMIP_FORCE_PDDISC_POWERDOWN		(1 << 0)
#define UTMIP_FORCE_PDCHRP_POWERDOWN		(1 << 2)
#define UTMIP_FORCE_PDDR_POWERDOWN		(1 << 4)

/* USB3_IF_USB_PHY_VBUS_SENSORS_0 */
#define VBUS_VLD_STS			(1 << 26)


/* Setup USB on the board */
int board_usb_init(const void *blob);

#endif	/* _TEGRA_USB_H_ */
