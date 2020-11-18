/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#define PWR_ON    1
#define PWR_OFF   0

enum pm_e {
	PM_DSPA,
	PM_DSPB,
	PM_DOS_HCODEC,
	PM_DOS_HEVC,
	PM_DOS_VDEC,
	PM_DOS_WAVE,
	PM_VPU_HDMI,
	PM_USB_COMB,
	PM_PCIE,
	PM_GE2D,
	PM_SRAMA,
	PM_SRAMB,
	PM_HDMIRX,
	PM_VI_CLK1,
	PM_VI_CLK2,
	PM_ETH,
	PM_ISP,
	PM_MIPI_ISP,
	PM_GDC,
	PM_DEWARP,
	PM_SDIO_A,
	PM_SDIO_B,
	PM_EMMC,
	PM_MALI_SC0,
	PM_MALI_SC1,
	PM_MALI_SC2,
	PM_MALI_SC3,
	PM_MALI_TOP,
	PM_NNA_CORE0,
	PM_NNA_CORE1,
	PM_NNA_CORE2,
	PM_NNA_CORE3,
	PM_NNA_TOP,
	PM_DDR0,
	PM_DDR1,
	PM_DMC0,
	PM_DMC1,
	PM_NOC,
	PM_NIC2,
	PM_NIC3,
	PM_CCI,
	PM_MIPI_DSI0,
	PM_SPICC0,
	PM_SPICC1,
	PM_SPICC2,
	PM_SPICC3,
	PM_SPICC4,
	PM_SPICC5,
	PM_EDP0,
	PM_EDP1,
	PM_MIPI_DSI1
};

unsigned long pwr_ctrl_psci_smc(enum pm_e power_domain, bool power_control);
unsigned long pwr_ctrl_status_psci_smc(enum pm_e power_domain);
