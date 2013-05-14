/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 *
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

#include <common.h>
#include <command.h>
#include <netdev.h>
#include <asm/mmu.h>
#include <asm/processor.h>
#include <asm/cache.h>
#include <asm/immap_85xx.h>
#include <asm/fsl_law.h>
#include <asm/fsl_ddr_sdram.h>
#include <asm/fsl_serdes.h>
#include <asm/fsl_portals.h>
#include <asm/fsl_liodn.h>
#include <malloc.h>
#include <fm_eth.h>
#include <fsl_mdio.h>
#include <miiphy.h>
#include <phy.h>
#include <asm/fsl_dtsec.h>
#include <asm/fsl_serdes.h>
#include "../common/qixis.h"
#include "../common/fman.h"

#include "t4240qds_qixis.h"

#define EMI_NONE	0xFFFFFFFF
#define EMI1_RGMII	0
#define EMI1_SLOT1	1
#define EMI1_SLOT2	2
#define EMI1_SLOT3	3
#define EMI1_SLOT4	4
#define EMI1_SLOT5	5
#define EMI1_SLOT7	7
#define EMI2		8
/* Slot6 and Slot8 do not have EMI connections */

static int mdio_mux[NUM_FM_PORTS];

static const char *mdio_names[] = {
	"T4240QDS_MDIO0",
	"T4240QDS_MDIO1",
	"T4240QDS_MDIO2",
	"T4240QDS_MDIO3",
	"T4240QDS_MDIO4",
	"T4240QDS_MDIO5",
	"NULL",
	"T4240QDS_MDIO7",
	"T4240QDS_10GC",
};

static u8 lane_to_slot_fsm1[] = {1, 1, 1, 1, 2, 2, 2, 2};
static u8 lane_to_slot_fsm2[] = {3, 3, 3, 3, 4, 4, 4, 4};
static u8 slot_qsgmii_phyaddr[5][4] = {
	{0, 0, 0, 0},/* not used, to make index match slot No. */
	{0, 1, 2, 3},
	{4, 5, 6, 7},
	{8, 9, 0xa, 0xb},
	{0xc, 0xd, 0xe, 0xf},
};
static u8 qsgmiiphy_fix[NUM_FM_PORTS] = {0};

static const char *t4240qds_mdio_name_for_muxval(u8 muxval)
{
	return mdio_names[muxval];
}

struct mii_dev *mii_dev_for_muxval(u8 muxval)
{
	struct mii_dev *bus;
	const char *name = t4240qds_mdio_name_for_muxval(muxval);

	if (!name) {
		printf("No bus for muxval %x\n", muxval);
		return NULL;
	}

	bus = miiphy_get_dev_by_name(name);

	if (!bus) {
		printf("No bus by name %s\n", name);
		return NULL;
	}

	return bus;
}

struct t4240qds_mdio {
	u8 muxval;
	struct mii_dev *realbus;
};

static void t4240qds_mux_mdio(u8 muxval)
{
	u8 brdcfg4;
	if ((muxval < 6) || (muxval == 7)) {
		brdcfg4 = QIXIS_READ(brdcfg[4]);
		brdcfg4 &= ~BRDCFG4_EMISEL_MASK;
		brdcfg4 |= (muxval << BRDCFG4_EMISEL_SHIFT);
		QIXIS_WRITE(brdcfg[4], brdcfg4);
	}
}

static int t4240qds_mdio_read(struct mii_dev *bus, int addr, int devad,
				int regnum)
{
	struct t4240qds_mdio *priv = bus->priv;

	t4240qds_mux_mdio(priv->muxval);

	return priv->realbus->read(priv->realbus, addr, devad, regnum);
}

static int t4240qds_mdio_write(struct mii_dev *bus, int addr, int devad,
				int regnum, u16 value)
{
	struct t4240qds_mdio *priv = bus->priv;

	t4240qds_mux_mdio(priv->muxval);

	return priv->realbus->write(priv->realbus, addr, devad, regnum, value);
}

static int t4240qds_mdio_reset(struct mii_dev *bus)
{
	struct t4240qds_mdio *priv = bus->priv;

	return priv->realbus->reset(priv->realbus);
}

static int t4240qds_mdio_init(char *realbusname, u8 muxval)
{
	struct t4240qds_mdio *pmdio;
	struct mii_dev *bus = mdio_alloc();

	if (!bus) {
		printf("Failed to allocate T4240QDS MDIO bus\n");
		return -1;
	}

	pmdio = malloc(sizeof(*pmdio));
	if (!pmdio) {
		printf("Failed to allocate T4240QDS private data\n");
		free(bus);
		return -1;
	}

	bus->read = t4240qds_mdio_read;
	bus->write = t4240qds_mdio_write;
	bus->reset = t4240qds_mdio_reset;
	sprintf(bus->name, t4240qds_mdio_name_for_muxval(muxval));

	pmdio->realbus = miiphy_get_dev_by_name(realbusname);

	if (!pmdio->realbus) {
		printf("No bus with name %s\n", realbusname);
		free(bus);
		free(pmdio);
		return -1;
	}

	pmdio->muxval = muxval;
	bus->priv = pmdio;

	return mdio_register(bus);
}

void board_ft_fman_fixup_port(void *blob, char * prop, phys_addr_t pa,
				enum fm_port port, int offset)
{
	if (fm_info_get_enet_if(port) == PHY_INTERFACE_MODE_SGMII) {
		switch (port) {
		case FM1_DTSEC1:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy21");
			break;
		case FM1_DTSEC2:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy22");
			break;
		case FM1_DTSEC3:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy23");
			break;
		case FM1_DTSEC4:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy24");
			break;
		case FM1_DTSEC6:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy12");
			break;
		case FM1_DTSEC9:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy14");
			else
				fdt_set_phy_handle(blob, prop, pa,
						   "phy_sgmii4");
			break;
		case FM1_DTSEC10:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy13");
			else
				fdt_set_phy_handle(blob, prop, pa,
						   "phy_sgmii3");
			break;
		case FM2_DTSEC1:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy41");
			break;
		case FM2_DTSEC2:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy42");
			break;
		case FM2_DTSEC3:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy43");
			break;
		case FM2_DTSEC4:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy44");
			break;
		case FM2_DTSEC6:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy32");
			break;
		case FM2_DTSEC9:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy34");
			else
				fdt_set_phy_handle(blob, prop, pa,
						   "phy_sgmii12");
			break;
		case FM2_DTSEC10:
			if (qsgmiiphy_fix[port])
				fdt_set_phy_handle(blob, prop, pa,
						   "sgmii_phy33");
			else
				fdt_set_phy_handle(blob, prop, pa,
						   "phy_sgmii11");
			break;
		default:
			break;
		}
	}
}

void fdt_fixup_board_enet(void *fdt)
{
	int i;
	ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
	u32 prtcl2 = in_be32(&gur->rcwsr[4]) & FSL_CORENET2_RCWSR4_SRDS2_PRTCL;

	prtcl2 >>= FSL_CORENET2_RCWSR4_SRDS2_PRTCL_SHIFT;
	for (i = FM1_DTSEC1; i < NUM_FM_PORTS; i++) {
		switch (fm_info_get_enet_if(i)) {
		case PHY_INTERFACE_MODE_SGMII:
			switch (mdio_mux[i]) {
			case EMI1_SLOT1:
				fdt_status_okay_by_alias(fdt, "emi1_slot1");
				break;
			case EMI1_SLOT2:
				fdt_status_okay_by_alias(fdt, "emi1_slot2");
				break;
			case EMI1_SLOT3:
				fdt_status_okay_by_alias(fdt, "emi1_slot3");
				break;
			case EMI1_SLOT4:
				fdt_status_okay_by_alias(fdt, "emi1_slot4");
				break;
			default:
				break;
			}
			break;
		case PHY_INTERFACE_MODE_XGMII:
			/* check if it's XFI interface for 10g */
			if ((prtcl2 == 56) || (prtcl2 == 57)) {
				fdt_status_okay_by_alias(fdt, "emi2_xfislot3");
				break;
			}
			switch (i) {
			case FM1_10GEC1:
				fdt_status_okay_by_alias(fdt, "emi2_xauislot1");
				break;
			case FM1_10GEC2:
				fdt_status_okay_by_alias(fdt, "emi2_xauislot2");
				break;
			case FM2_10GEC1:
				fdt_status_okay_by_alias(fdt, "emi2_xauislot3");
				break;
			case FM2_10GEC2:
				fdt_status_okay_by_alias(fdt, "emi2_xauislot4");
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

static void initialize_qsgmiiphy_fix(void)
{
	int i;
	unsigned short reg;

	for (i = 1; i <= 4; i++) {
		/*
		 * Try to read if a SGMII card is used, we do it slot by slot.
		 * if a SGMII PHY address is valid on a slot, then we mark
		 * all ports on the slot, then fix the PHY address for the
		 * marked port when doing dtb fixup.
		 */
		if (miiphy_read(mdio_names[i],
				SGMII_CARD_PORT1_PHY_ADDR, MII_PHYSID2, &reg) != 0) {
			debug("Slot%d PHY ID register 2 read failed\n", i);
			continue;
		}

		debug("Slot%d MII_PHYSID2 @ 0x1c= 0x%04x\n", i, reg);

		if (reg == 0xFFFF) {
			/* No physical device present at this address */
			continue;
		}

		switch (i) {
		case 1:
			qsgmiiphy_fix[FM1_DTSEC5] = 1;
			qsgmiiphy_fix[FM1_DTSEC6] = 1;
			qsgmiiphy_fix[FM1_DTSEC9] = 1;
			qsgmiiphy_fix[FM1_DTSEC10] = 1;
			break;
		case 2:
			qsgmiiphy_fix[FM1_DTSEC1] = 1;
			qsgmiiphy_fix[FM1_DTSEC2] = 1;
			qsgmiiphy_fix[FM1_DTSEC3] = 1;
			qsgmiiphy_fix[FM1_DTSEC4] = 1;
			break;
		case 3:
			qsgmiiphy_fix[FM2_DTSEC5] = 1;
			qsgmiiphy_fix[FM2_DTSEC6] = 1;
			qsgmiiphy_fix[FM2_DTSEC9] = 1;
			qsgmiiphy_fix[FM2_DTSEC10] = 1;
			break;
		case 4:
			qsgmiiphy_fix[FM2_DTSEC1] = 1;
			qsgmiiphy_fix[FM2_DTSEC2] = 1;
			qsgmiiphy_fix[FM2_DTSEC3] = 1;
			qsgmiiphy_fix[FM2_DTSEC4] = 1;
			break;
		default:
			break;
		}
	}
}

int board_eth_init(bd_t *bis)
{
#if defined(CONFIG_FMAN_ENET)
	int i, idx, lane, slot;
	struct memac_mdio_info dtsec_mdio_info;
	struct memac_mdio_info tgec_mdio_info;
	ccsr_gur_t *gur = (void *)(CONFIG_SYS_MPC85xx_GUTS_ADDR);
	u32 srds_prtcl_s1, srds_prtcl_s2;

	srds_prtcl_s1 = in_be32(&gur->rcwsr[4]) &
					FSL_CORENET2_RCWSR4_SRDS1_PRTCL;
	srds_prtcl_s1 >>= FSL_CORENET2_RCWSR4_SRDS1_PRTCL_SHIFT;
	srds_prtcl_s2 = in_be32(&gur->rcwsr[4]) &
					FSL_CORENET2_RCWSR4_SRDS2_PRTCL;
	srds_prtcl_s2 >>= FSL_CORENET2_RCWSR4_SRDS2_PRTCL_SHIFT;

	/* Initialize the mdio_mux array so we can recognize empty elements */
	for (i = 0; i < NUM_FM_PORTS; i++)
		mdio_mux[i] = EMI_NONE;

	dtsec_mdio_info.regs =
		(struct memac_mdio_controller *)CONFIG_SYS_FM2_DTSEC_MDIO_ADDR;

	dtsec_mdio_info.name = DEFAULT_FM_MDIO_NAME;

	/* Register the 1G MDIO bus */
	fm_memac_mdio_init(bis, &dtsec_mdio_info);

	tgec_mdio_info.regs =
		(struct memac_mdio_controller *)CONFIG_SYS_FM2_TGEC_MDIO_ADDR;
	tgec_mdio_info.name = DEFAULT_FM_TGEC_MDIO_NAME;

	/* Register the 10G MDIO bus */
	fm_memac_mdio_init(bis, &tgec_mdio_info);

	/* Register the muxing front-ends to the MDIO buses */
	t4240qds_mdio_init(DEFAULT_FM_MDIO_NAME, EMI1_RGMII);
	t4240qds_mdio_init(DEFAULT_FM_MDIO_NAME, EMI1_SLOT1);
	t4240qds_mdio_init(DEFAULT_FM_MDIO_NAME, EMI1_SLOT2);
	t4240qds_mdio_init(DEFAULT_FM_MDIO_NAME, EMI1_SLOT3);
	t4240qds_mdio_init(DEFAULT_FM_MDIO_NAME, EMI1_SLOT4);
	t4240qds_mdio_init(DEFAULT_FM_MDIO_NAME, EMI1_SLOT5);
	t4240qds_mdio_init(DEFAULT_FM_MDIO_NAME, EMI1_SLOT7);
	t4240qds_mdio_init(DEFAULT_FM_TGEC_MDIO_NAME, EMI2);


	switch (srds_prtcl_s1) {
	case 1:
	case 2:
	case 4:
		/* XAUI/HiGig in Slot1 and Slot2 */
		fm_info_set_phy_address(FM1_10GEC1, FM1_10GEC1_PHY_ADDR);
		fm_info_set_phy_address(FM1_10GEC2, FM1_10GEC2_PHY_ADDR);
		break;
	case 28:
	case 36:
		/* SGMII in Slot1 and Slot2 */
		fm_info_set_phy_address(FM1_DTSEC1, slot_qsgmii_phyaddr[2][0]);
		fm_info_set_phy_address(FM1_DTSEC2, slot_qsgmii_phyaddr[2][1]);
		fm_info_set_phy_address(FM1_DTSEC3, slot_qsgmii_phyaddr[2][2]);
		fm_info_set_phy_address(FM1_DTSEC4, slot_qsgmii_phyaddr[2][3]);
		fm_info_set_phy_address(FM1_DTSEC5, slot_qsgmii_phyaddr[1][0]);
		fm_info_set_phy_address(FM1_DTSEC6, slot_qsgmii_phyaddr[1][1]);
		if ((srds_prtcl_s2 != 56) && (srds_prtcl_s2 != 57)) {
			fm_info_set_phy_address(FM1_DTSEC9,
						slot_qsgmii_phyaddr[1][3]);
			fm_info_set_phy_address(FM1_DTSEC10,
						slot_qsgmii_phyaddr[1][2]);
		}
		break;
	case 38:
		fm_info_set_phy_address(FM1_DTSEC1, slot_qsgmii_phyaddr[2][0]);
		fm_info_set_phy_address(FM1_DTSEC2, slot_qsgmii_phyaddr[2][1]);
		fm_info_set_phy_address(FM1_DTSEC3, slot_qsgmii_phyaddr[2][2]);
		fm_info_set_phy_address(FM1_DTSEC4, slot_qsgmii_phyaddr[2][3]);
		fm_info_set_phy_address(FM1_DTSEC5, slot_qsgmii_phyaddr[1][0]);
		fm_info_set_phy_address(FM1_DTSEC6, slot_qsgmii_phyaddr[1][1]);
		if ((srds_prtcl_s2 != 56) && (srds_prtcl_s2 != 57)) {
			fm_info_set_phy_address(FM1_DTSEC9,
						slot_qsgmii_phyaddr[1][3]);
			fm_info_set_phy_address(FM1_DTSEC10,
						slot_qsgmii_phyaddr[1][2]);
		}
		break;
	case 40:
	case 46:
	case 48:
		fm_info_set_phy_address(FM1_DTSEC5, slot_qsgmii_phyaddr[1][0]);
		fm_info_set_phy_address(FM1_DTSEC6, slot_qsgmii_phyaddr[1][1]);
		if ((srds_prtcl_s2 != 56) && (srds_prtcl_s2 != 57)) {
			fm_info_set_phy_address(FM1_DTSEC10,
						slot_qsgmii_phyaddr[1][3]);
			fm_info_set_phy_address(FM1_DTSEC9,
						slot_qsgmii_phyaddr[1][2]);
		}
		fm_info_set_phy_address(FM1_DTSEC1, slot_qsgmii_phyaddr[2][0]);
		fm_info_set_phy_address(FM1_DTSEC2, slot_qsgmii_phyaddr[2][1]);
		fm_info_set_phy_address(FM1_DTSEC3, slot_qsgmii_phyaddr[2][2]);
		fm_info_set_phy_address(FM1_DTSEC4, slot_qsgmii_phyaddr[2][3]);
		break;
	default:
		puts("Invalid SerDes1 protocol for T4240QDS\n");
		break;
	}

	for (i = FM1_DTSEC1; i < FM1_DTSEC1 + CONFIG_SYS_NUM_FM1_DTSEC; i++) {
		idx = i - FM1_DTSEC1;
		switch (fm_info_get_enet_if(i)) {
		case PHY_INTERFACE_MODE_SGMII:
			lane = serdes_get_first_lane(FSL_SRDS_1,
						SGMII_FM1_DTSEC1 + idx);
			if (lane < 0)
				break;
			slot = lane_to_slot_fsm1[lane];
			debug("FM1@DTSEC%u expects SGMII in slot %u\n",
				idx + 1, slot);
			if (QIXIS_READ(present2) & (1 << (slot - 1)))
				fm_disable_port(i);
			switch (slot) {
			case 1:
				mdio_mux[i] = EMI1_SLOT1;
				fm_info_set_mdio(i,
					mii_dev_for_muxval(mdio_mux[i]));
				break;
			case 2:
				mdio_mux[i] = EMI1_SLOT2;
				fm_info_set_mdio(i,
					mii_dev_for_muxval(mdio_mux[i]));
				break;
			};
			break;
		case PHY_INTERFACE_MODE_RGMII:
			/* FM1 DTSEC5 routes to RGMII with EC2 */
			debug("FM1@DTSEC%u is RGMII at address %u\n",
				idx + 1, 2);
			if (i == FM1_DTSEC5)
				fm_info_set_phy_address(i, 2);
			mdio_mux[i] = EMI1_RGMII;
			fm_info_set_mdio(i,
				mii_dev_for_muxval(mdio_mux[i]));
			break;
		default:
			break;
		}
	}

	for (i = FM1_10GEC1; i < FM1_10GEC1 + CONFIG_SYS_NUM_FM1_10GEC; i++) {
		idx = i - FM1_10GEC1;
		switch (fm_info_get_enet_if(i)) {
		case PHY_INTERFACE_MODE_XGMII:
			lane = serdes_get_first_lane(FSL_SRDS_1,
						XAUI_FM1_MAC9 + idx);
			if (lane < 0)
				break;
			slot = lane_to_slot_fsm1[lane];
			if (QIXIS_READ(present2) & (1 << (slot - 1)))
				fm_disable_port(i);
			mdio_mux[i] = EMI2;
			fm_info_set_mdio(i, mii_dev_for_muxval(mdio_mux[i]));
			break;
		default:
			break;
		}
	}

#if (CONFIG_SYS_NUM_FMAN == 2)
	switch (srds_prtcl_s2) {
	case 1:
	case 2:
	case 4:
		/* XAUI/HiGig in Slot3 and Slot4 */
		fm_info_set_phy_address(FM2_10GEC1, FM2_10GEC1_PHY_ADDR);
		fm_info_set_phy_address(FM2_10GEC2, FM2_10GEC2_PHY_ADDR);
		break;
	case 7:
	case 13:
	case 14:
	case 16:
	case 22:
	case 23:
	case 25:
	case 26:
		/* XAUI/HiGig in Slot3, SGMII in Slot4 */
		fm_info_set_phy_address(FM2_10GEC1, FM2_10GEC1_PHY_ADDR);
		fm_info_set_phy_address(FM2_DTSEC1, slot_qsgmii_phyaddr[4][0]);
		fm_info_set_phy_address(FM2_DTSEC2, slot_qsgmii_phyaddr[4][1]);
		fm_info_set_phy_address(FM2_DTSEC3, slot_qsgmii_phyaddr[4][2]);
		fm_info_set_phy_address(FM2_DTSEC4, slot_qsgmii_phyaddr[4][3]);
		break;
	case 28:
	case 36:
		/* SGMII in Slot3 and Slot4 */
		fm_info_set_phy_address(FM2_DTSEC1, slot_qsgmii_phyaddr[4][0]);
		fm_info_set_phy_address(FM2_DTSEC2, slot_qsgmii_phyaddr[4][1]);
		fm_info_set_phy_address(FM2_DTSEC3, slot_qsgmii_phyaddr[4][2]);
		fm_info_set_phy_address(FM2_DTSEC4, slot_qsgmii_phyaddr[4][3]);
		fm_info_set_phy_address(FM2_DTSEC5, slot_qsgmii_phyaddr[3][0]);
		fm_info_set_phy_address(FM2_DTSEC6, slot_qsgmii_phyaddr[3][1]);
		fm_info_set_phy_address(FM2_DTSEC9, slot_qsgmii_phyaddr[3][3]);
		fm_info_set_phy_address(FM2_DTSEC10, slot_qsgmii_phyaddr[3][2]);
		break;
	case 38:
		/* QSGMII in Slot3 and Slot4 */
		fm_info_set_phy_address(FM2_DTSEC1, slot_qsgmii_phyaddr[4][0]);
		fm_info_set_phy_address(FM2_DTSEC2, slot_qsgmii_phyaddr[4][1]);
		fm_info_set_phy_address(FM2_DTSEC3, slot_qsgmii_phyaddr[4][2]);
		fm_info_set_phy_address(FM2_DTSEC4, slot_qsgmii_phyaddr[4][3]);
		fm_info_set_phy_address(FM2_DTSEC5, slot_qsgmii_phyaddr[3][0]);
		fm_info_set_phy_address(FM2_DTSEC6, slot_qsgmii_phyaddr[3][1]);
		fm_info_set_phy_address(FM2_DTSEC9, slot_qsgmii_phyaddr[3][3]);
		fm_info_set_phy_address(FM2_DTSEC10, slot_qsgmii_phyaddr[3][2]);
		break;
	case 40:
	case 46:
	case 48:
		/* SGMII in Slot3 */
		fm_info_set_phy_address(FM2_DTSEC5, slot_qsgmii_phyaddr[3][0]);
		fm_info_set_phy_address(FM2_DTSEC6, slot_qsgmii_phyaddr[3][1]);
		fm_info_set_phy_address(FM2_DTSEC9, slot_qsgmii_phyaddr[3][3]);
		fm_info_set_phy_address(FM2_DTSEC10, slot_qsgmii_phyaddr[3][2]);
		/* QSGMII in Slot4 */
		fm_info_set_phy_address(FM2_DTSEC1, slot_qsgmii_phyaddr[4][0]);
		fm_info_set_phy_address(FM2_DTSEC2, slot_qsgmii_phyaddr[4][1]);
		fm_info_set_phy_address(FM2_DTSEC3, slot_qsgmii_phyaddr[4][2]);
		fm_info_set_phy_address(FM2_DTSEC4, slot_qsgmii_phyaddr[4][3]);
		break;
	case 50:
	case 52:
	case 54:
		fm_info_set_phy_address(FM2_10GEC1, FM2_10GEC1_PHY_ADDR);
		fm_info_set_phy_address(FM2_DTSEC1, slot_qsgmii_phyaddr[4][0]);
		fm_info_set_phy_address(FM2_DTSEC2, slot_qsgmii_phyaddr[4][1]);
		fm_info_set_phy_address(FM2_DTSEC3, slot_qsgmii_phyaddr[4][2]);
		fm_info_set_phy_address(FM2_DTSEC4, slot_qsgmii_phyaddr[4][3]);
		break;
	case 56:
	case 57:
		/* XFI in Slot3, SGMII in Slot4 */
		fm_info_set_phy_address(FM2_DTSEC1, slot_qsgmii_phyaddr[4][0]);
		fm_info_set_phy_address(FM2_DTSEC2, slot_qsgmii_phyaddr[4][1]);
		fm_info_set_phy_address(FM2_DTSEC3, slot_qsgmii_phyaddr[4][2]);
		fm_info_set_phy_address(FM2_DTSEC4, slot_qsgmii_phyaddr[4][3]);
		break;
	default:
		puts("Invalid SerDes2 protocol for T4240QDS\n");
		break;
	}

	for (i = FM2_DTSEC1; i < FM2_DTSEC1 + CONFIG_SYS_NUM_FM2_DTSEC; i++) {
		idx = i - FM2_DTSEC1;
		switch (fm_info_get_enet_if(i)) {
		case PHY_INTERFACE_MODE_SGMII:
			lane = serdes_get_first_lane(FSL_SRDS_2,
						SGMII_FM2_DTSEC1 + idx);
			if (lane < 0)
				break;
			slot = lane_to_slot_fsm2[lane];
			debug("FM2@DTSEC%u expects SGMII in slot %u\n",
				idx + 1, slot);
			if (QIXIS_READ(present2) & (1 << (slot - 1)))
				fm_disable_port(i);
			switch (slot) {
			case 3:
				mdio_mux[i] = EMI1_SLOT3;
				fm_info_set_mdio(i,
					mii_dev_for_muxval(mdio_mux[i]));
				break;
			case 4:
				mdio_mux[i] = EMI1_SLOT4;
				fm_info_set_mdio(i,
					mii_dev_for_muxval(mdio_mux[i]));
				break;
			};
			break;
		case PHY_INTERFACE_MODE_RGMII:
			/*
			 * If DTSEC5 is RGMII, then it's routed via via EC1 to
			 * the first on-board RGMII port.  If DTSEC6 is RGMII,
			 * then it's routed via via EC2 to the second on-board
			 * RGMII port.
			 */
			debug("FM2@DTSEC%u is RGMII at address %u\n",
				idx + 1, i == FM2_DTSEC5 ? 1 : 2);
			fm_info_set_phy_address(i, i == FM2_DTSEC5 ? 1 : 2);
			mdio_mux[i] = EMI1_RGMII;
			fm_info_set_mdio(i, mii_dev_for_muxval(mdio_mux[i]));
			break;
		default:
			break;
		}
	}

	for (i = FM2_10GEC1; i < FM2_10GEC1 + CONFIG_SYS_NUM_FM2_10GEC; i++) {
		idx = i - FM2_10GEC1;
		switch (fm_info_get_enet_if(i)) {
		case PHY_INTERFACE_MODE_XGMII:
			lane = serdes_get_first_lane(FSL_SRDS_2,
						XAUI_FM2_MAC9 + idx);
			if (lane < 0)
				break;
			slot = lane_to_slot_fsm2[lane];
			if (QIXIS_READ(present2) & (1 << (slot - 1)))
				fm_disable_port(i);
			mdio_mux[i] = EMI2;
			fm_info_set_mdio(i, mii_dev_for_muxval(mdio_mux[i]));
			break;
		default:
			break;
		}
	}
#endif /* CONFIG_SYS_NUM_FMAN */

	initialize_qsgmiiphy_fix();

	cpu_eth_init(bis);
#endif /* CONFIG_FMAN_ENET */

	return pci_eth_init(bis);
}
