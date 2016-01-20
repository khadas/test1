/*
 * Copyright 2015 Freescale Semiconductor, Inc.
 *
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <netdev.h>
#include <malloc.h>
#include <fsl_mdio.h>
#include <miiphy.h>
#include <phy.h>
#include <fm_eth.h>
#include <asm/io.h>
#include <exports.h>
#include <asm/arch/fsl_serdes.h>
#include <fsl-mc/ldpaa_wriop.h>

DECLARE_GLOBAL_DATA_PTR;

#define MC_BOOT_ENV_VAR "mcinitcmd"
int board_eth_init(bd_t *bis)
{
#if defined(CONFIG_FSL_MC_ENET)
	char *mc_boot_env_var;
	int i, interface;
	struct memac_mdio_info mdio_info;
	struct mii_dev *dev;
	struct ccsr_gur *gur = (void *)(CONFIG_SYS_FSL_GUTS_ADDR);
	u32 srds_s1;
	struct memac_mdio_controller *reg;

	srds_s1 = in_le32(&gur->rcwsr[28]) &
				FSL_CHASSIS3_RCWSR28_SRDS1_PRTCL_MASK;
	srds_s1 >>= FSL_CHASSIS3_RCWSR28_SRDS1_PRTCL_SHIFT;

	reg = (struct memac_mdio_controller *)CONFIG_SYS_FSL_WRIOP1_MDIO1;
	mdio_info.regs = reg;
	mdio_info.name = DEFAULT_WRIOP_MDIO1_NAME;

	/* Register the EMI 1 */
	fm_memac_mdio_init(bis, &mdio_info);

	reg = (struct memac_mdio_controller *)CONFIG_SYS_FSL_WRIOP1_MDIO2;
	mdio_info.regs = reg;
	mdio_info.name = DEFAULT_WRIOP_MDIO2_NAME;

	/* Register the EMI 2 */
	fm_memac_mdio_init(bis, &mdio_info);

	switch (srds_s1) {
	case 0x2A:
		wriop_set_phy_address(WRIOP1_DPMAC1, CORTINA_PHY_ADDR1);
		wriop_set_phy_address(WRIOP1_DPMAC2, CORTINA_PHY_ADDR2);
		wriop_set_phy_address(WRIOP1_DPMAC3, CORTINA_PHY_ADDR3);
		wriop_set_phy_address(WRIOP1_DPMAC4, CORTINA_PHY_ADDR4);
		wriop_set_phy_address(WRIOP1_DPMAC5, AQ_PHY_ADDR1);
		wriop_set_phy_address(WRIOP1_DPMAC6, AQ_PHY_ADDR2);
		wriop_set_phy_address(WRIOP1_DPMAC7, AQ_PHY_ADDR3);
		wriop_set_phy_address(WRIOP1_DPMAC8, AQ_PHY_ADDR4);

		break;
	default:
		printf("SerDes1 protocol 0x%x is not supported on LS2080aRDB\n",
		       srds_s1);
		break;
	}

	for (i = WRIOP1_DPMAC1; i <= WRIOP1_DPMAC4; i++) {
		interface = wriop_get_enet_if(i);
		switch (interface) {
		case PHY_INTERFACE_MODE_XGMII:
			dev = miiphy_get_dev_by_name(DEFAULT_WRIOP_MDIO1_NAME);
			wriop_set_mdio(i, dev);
			break;
		default:
			break;
		}
	}

	for (i = WRIOP1_DPMAC5; i <= WRIOP1_DPMAC8; i++) {
		switch (wriop_get_enet_if(i)) {
		case PHY_INTERFACE_MODE_XGMII:
			dev = miiphy_get_dev_by_name(DEFAULT_WRIOP_MDIO2_NAME);
			wriop_set_mdio(i, dev);
			break;
		default:
			break;
		}
	}

	mc_boot_env_var = getenv(MC_BOOT_ENV_VAR);
	if (mc_boot_env_var)
		run_command_list(mc_boot_env_var, -1, 0);
	cpu_eth_init(bis);
#endif /* CONFIG_FMAN_ENET */

#ifdef CONFIG_PHY_AQUANTIA
	/*
	 * Export functions to be used by AQ firmware
	 * upload application
	 */
	gd->jt->strcpy = strcpy;
	gd->jt->mdelay = mdelay;
	gd->jt->mdio_get_current_dev = mdio_get_current_dev;
	gd->jt->phy_find_by_mask = phy_find_by_mask;
	gd->jt->mdio_phydev_for_ethname = mdio_phydev_for_ethname;
	gd->jt->miiphy_set_current_dev = miiphy_set_current_dev;
#endif
	return pci_eth_init(bis);
}
