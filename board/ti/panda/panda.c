/*
 * (C) Copyright 2010
 * Texas Instruments Incorporated, <www.ti.com>
 * Steve Sakoman  <steve@sakoman.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/arch/clock.h>
#include <asm/arch/gpio.h>
#include <asm/gpio.h>

#include "panda_mux_data.h"

#ifdef CONFIG_USB_EHCI
#include <usb.h>
#include <asm/arch/ehci.h>
#include <asm/ehci-omap.h>
#endif

#define PANDA_ULPI_PHY_TYPE_GPIO       182
#define PANDA_BOARD_ID_1_GPIO          101
#define PANDA_ES_BOARD_ID_1_GPIO        48
#define PANDA_BOARD_ID_2_GPIO          171
#define PANDA_ES_BOARD_ID_3_GPIO         3
#define PANDA_ES_BOARD_ID_4_GPIO         2

DECLARE_GLOBAL_DATA_PTR;

const struct omap_sysinfo sysinfo = {
	"Board: OMAP4 Panda\n"
};

struct omap4_scrm_regs *const scrm = (struct omap4_scrm_regs *)0x4a30a000;

/**
 * @brief board_init
 *
 * @return 0
 */
int board_init(void)
{
	gpmc_init();

	gd->bd->bi_arch_number = MACH_TYPE_OMAP4_PANDA;
	gd->bd->bi_boot_params = (0x80000000 + 0x100); /* boot param addr */

	return 0;
}

int board_eth_init(bd_t *bis)
{
	return 0;
}

/*
* Routine: get_board_revision
* Description: Detect if we are running on a panda revision A1-A6,
*              or an ES panda board. This can be done by reading
*              the level of GPIOs and checking the processor revisions.
*              This should result in:
*			Panda 4430:
*              GPIO171, GPIO101, GPIO182: 0 1 1 => A1-A5
*              GPIO171, GPIO101, GPIO182: 1 0 1 => A6
*			Panda ES:
*              GPIO2, GPIO3, GPIO171, GPIO48, GPIO182: 0 0 0 1 1 => B1/B2
*              GPIO2, GPIO3, GPIO171, GPIO48, GPIO182: 0 0 1 1 1 => B3
*/
int get_board_revision(void)
{
	int board_id0, board_id1, board_id2;
	int board_id3, board_id4;
	int board_id;

	int processor_rev = omap_revision();

	/* Setup the mux for the common board ID pins (gpio 171 and 182) */
	writew((IEN | M3), (*ctrl)->control_padconf_core_base + UNIPRO_TX0);
	writew((IEN | M3), (*ctrl)->control_padconf_core_base + FREF_CLK2_OUT);

	board_id0 = gpio_get_value(PANDA_ULPI_PHY_TYPE_GPIO);
	board_id2 = gpio_get_value(PANDA_BOARD_ID_2_GPIO);

	if ((processor_rev >= OMAP4460_ES1_0 &&
	     processor_rev <= OMAP4460_ES1_1)) {
		/*
		 * Setup the mux for the ES specific board ID pins (gpio 101,
		 * 2 and 3.
		 */
		writew((IEN | M3), (*ctrl)->control_padconf_core_base +
				GPMC_A24);
		writew((IEN | M3), (*ctrl)->control_padconf_core_base +
				UNIPRO_RY0);
		writew((IEN | M3), (*ctrl)->control_padconf_core_base +
				UNIPRO_RX1);

		board_id1 = gpio_get_value(PANDA_ES_BOARD_ID_1_GPIO);
		board_id3 = gpio_get_value(PANDA_ES_BOARD_ID_3_GPIO);
		board_id4 = gpio_get_value(PANDA_ES_BOARD_ID_4_GPIO);

#ifdef CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
		setenv("board_name", strcat(CONFIG_SYS_BOARD, "-es"));
#endif
		board_id = ((board_id4 << 4) | (board_id3 << 3) |
			(board_id2 << 2) | (board_id1 << 1) | (board_id0));
	} else {
		/* Setup the mux for the Ax specific board ID pins (gpio 101) */
		writew((IEN | M3), (*ctrl)->control_padconf_core_base +
				FREF_CLK2_OUT);

		board_id1 = gpio_get_value(PANDA_BOARD_ID_1_GPIO);
		board_id = ((board_id2 << 2) | (board_id1 << 1) | (board_id0));

#ifdef CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
		if ((board_id >= 0x3) && (processor_rev == OMAP4430_ES2_3))
			setenv("board_name", strcat(CONFIG_SYS_BOARD, "-a4"));
#endif
	}

	return board_id;
}

/**
 * @brief misc_init_r - Configure Panda board specific configurations
 * such as power configurations, ethernet initialization as phase2 of
 * boot sequence
 *
 * @return 0
 */
int misc_init_r(void)
{
	int phy_type;
	u32 auxclk, altclksrc;
	uint8_t device_mac[6];

	/* EHCI is not supported on ES1.0 */
	if (omap_revision() == OMAP4430_ES1_0)
		return 0;

	get_board_revision();

	gpio_direction_input(PANDA_ULPI_PHY_TYPE_GPIO);
	phy_type = gpio_get_value(PANDA_ULPI_PHY_TYPE_GPIO);

	if (phy_type == 1) {
		/* ULPI PHY supplied by auxclk3 derived from sys_clk */
		debug("ULPI PHY supplied by auxclk3\n");

		auxclk = readl(&scrm->auxclk3);
		/* Select sys_clk */
		auxclk &= ~AUXCLK_SRCSELECT_MASK;
		auxclk |=  AUXCLK_SRCSELECT_SYS_CLK << AUXCLK_SRCSELECT_SHIFT;
		/* Set the divisor to 2 */
		auxclk &= ~AUXCLK_CLKDIV_MASK;
		auxclk |= AUXCLK_CLKDIV_2 << AUXCLK_CLKDIV_SHIFT;
		/* Request auxilary clock #3 */
		auxclk |= AUXCLK_ENABLE_MASK;

		writel(auxclk, &scrm->auxclk3);
	} else {
		/* ULPI PHY supplied by auxclk1 derived from PER dpll */
		debug("ULPI PHY supplied by auxclk1\n");

		auxclk = readl(&scrm->auxclk1);
		/* Select per DPLL */
		auxclk &= ~AUXCLK_SRCSELECT_MASK;
		auxclk |=  AUXCLK_SRCSELECT_PER_DPLL << AUXCLK_SRCSELECT_SHIFT;
		/* Set the divisor to 16 */
		auxclk &= ~AUXCLK_CLKDIV_MASK;
		auxclk |= AUXCLK_CLKDIV_16 << AUXCLK_CLKDIV_SHIFT;
		/* Request auxilary clock #3 */
		auxclk |= AUXCLK_ENABLE_MASK;

		writel(auxclk, &scrm->auxclk1);
	}

	altclksrc = readl(&scrm->altclksrc);

	/* Activate alternate system clock supplier */
	altclksrc &= ~ALTCLKSRC_MODE_MASK;
	altclksrc |= ALTCLKSRC_MODE_ACTIVE;

	/* enable clocks */
	altclksrc |= ALTCLKSRC_ENABLE_INT_MASK | ALTCLKSRC_ENABLE_EXT_MASK;

	writel(altclksrc, &scrm->altclksrc);

	if (!getenv("usbethaddr")) {
		/*
		 * create a fake MAC address from the processor ID code.
		 * first byte is 0x02 to signify locally administered.
		 */
		device_mac[0] = 0x02;
		device_mac[1] = readl(STD_FUSE_DIE_ID_3) & 0xff;
		device_mac[2] = readl(STD_FUSE_DIE_ID_2) & 0xff;
		device_mac[3] = readl(STD_FUSE_DIE_ID_1) & 0xff;
		device_mac[4] = readl(STD_FUSE_DIE_ID_0) & 0xff;
		device_mac[5] = (readl(STD_FUSE_DIE_ID_0) >> 8) & 0xff;

		eth_setenv_enetaddr("usbethaddr", device_mac);
	}

	return 0;
}

void set_muxconf_regs_essential(void)
{
	do_set_mux((*ctrl)->control_padconf_core_base,
		   core_padconf_array_essential,
		   sizeof(core_padconf_array_essential) /
		   sizeof(struct pad_conf_entry));

	do_set_mux((*ctrl)->control_padconf_wkup_base,
		   wkup_padconf_array_essential,
		   sizeof(wkup_padconf_array_essential) /
		   sizeof(struct pad_conf_entry));

	if (omap_revision() >= OMAP4460_ES1_0)
		do_set_mux((*ctrl)->control_padconf_wkup_base,
			   wkup_padconf_array_essential_4460,
			   sizeof(wkup_padconf_array_essential_4460) /
			   sizeof(struct pad_conf_entry));
}

void set_muxconf_regs_non_essential(void)
{
	do_set_mux((*ctrl)->control_padconf_core_base,
		   core_padconf_array_non_essential,
		   sizeof(core_padconf_array_non_essential) /
		   sizeof(struct pad_conf_entry));

	if (omap_revision() < OMAP4460_ES1_0)
		do_set_mux((*ctrl)->control_padconf_core_base,
			   core_padconf_array_non_essential_4430,
			   sizeof(core_padconf_array_non_essential_4430) /
			   sizeof(struct pad_conf_entry));
	else
		do_set_mux((*ctrl)->control_padconf_core_base,
			   core_padconf_array_non_essential_4460,
			   sizeof(core_padconf_array_non_essential_4460) /
			   sizeof(struct pad_conf_entry));

	do_set_mux((*ctrl)->control_padconf_wkup_base,
		   wkup_padconf_array_non_essential,
		   sizeof(wkup_padconf_array_non_essential) /
		   sizeof(struct pad_conf_entry));

	if (omap_revision() < OMAP4460_ES1_0)
		do_set_mux((*ctrl)->control_padconf_wkup_base,
			   wkup_padconf_array_non_essential_4430,
			   sizeof(wkup_padconf_array_non_essential_4430) /
			   sizeof(struct pad_conf_entry));
}

#if !defined(CONFIG_SPL_BUILD) && defined(CONFIG_GENERIC_MMC)
int board_mmc_init(bd_t *bis)
{
	return omap_mmc_init(0, 0, 0, -1, -1);
}
#endif

#ifdef CONFIG_USB_EHCI

static struct omap_usbhs_board_data usbhs_bdata = {
	.port_mode[0] = OMAP_EHCI_PORT_MODE_PHY,
	.port_mode[1] = OMAP_USBHS_PORT_MODE_UNUSED,
	.port_mode[2] = OMAP_USBHS_PORT_MODE_UNUSED,
};

int ehci_hcd_init(int index, enum usb_init_type init,
		struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
	int ret;
	unsigned int utmi_clk;

	/* Now we can enable our port clocks */
	utmi_clk = readl((void *)CM_L3INIT_HSUSBHOST_CLKCTRL);
	utmi_clk |= HSUSBHOST_CLKCTRL_CLKSEL_UTMI_P1_MASK;
	sr32((void *)CM_L3INIT_HSUSBHOST_CLKCTRL, 0, 32, utmi_clk);

	ret = omap_ehci_hcd_init(index, &usbhs_bdata, hccr, hcor);
	if (ret < 0)
		return ret;

	return 0;
}

int ehci_hcd_stop(int index)
{
	return omap_ehci_hcd_stop();
}
#endif

/*
 * get_board_rev() - get board revision
 */
u32 get_board_rev(void)
{
	return 0x20;
}
