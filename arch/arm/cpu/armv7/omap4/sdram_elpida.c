/*
 * Timing and Organization details of the Elpida parts used in OMAP4
 * SDPs and Panda
 *
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 *
 * Aneesh V <aneesh@ti.com>
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

#include <asm/arch/emif.h>
#include <asm/arch/sys_proto.h>

/*
 * This file provides details of the LPDDR2 SDRAM parts used on OMAP4430
 * SDP and Panda. Since the parts used and geometry are identical for
 * SDP and Panda for a given OMAP4 revision, this information is kept
 * here instead of being in board directory. However the key functions
 * exported are weakly linked so that they can be over-ridden in the board
 * directory if there is a OMAP4 board in the future that uses a different
 * memory device or geometry.
 *
 * For any new board with different memory devices over-ride one or more
 * of the following functions as per the CONFIG flags you intend to enable:
 * - emif_get_reg_dump()
 * - emif_get_dmm_regs()
 * - emif_get_device_details()
 * - emif_get_device_timings()
 */

static const struct emif_regs emif_regs_elpida_200_mhz_2cs = {
	.sdram_config_init		= 0x80000eb9,
	.sdram_config			= 0x80001ab9,
	.ref_ctrl			= 0x0000030c,
	.sdram_tim1			= 0x08648311,
	.sdram_tim2			= 0x101b06ca,
	.sdram_tim3			= 0x0048a19f,
	.read_idle_ctrl			= 0x000501ff,
	.zq_config			= 0x500b3214,
	.temp_alert_config		= 0xd8016893,
	.emif_ddr_phy_ctlr_1_init	= 0x049ffff5,
	.emif_ddr_phy_ctlr_1		= 0x049ff808
};

static const struct emif_regs emif_regs_elpida_380_mhz_1cs = {
	.sdram_config_init		= 0x80000eb1,
	.sdram_config			= 0x80001ab1,
	.ref_ctrl			= 0x000005cd,
	.sdram_tim1			= 0x10cb0622,
	.sdram_tim2			= 0x20350d52,
	.sdram_tim3			= 0x00b1431f,
	.read_idle_ctrl			= 0x000501ff,
	.zq_config			= 0x500b3214,
	.temp_alert_config		= 0x58016893,
	.emif_ddr_phy_ctlr_1_init	= 0x049ffff5,
	.emif_ddr_phy_ctlr_1		= 0x049ff418
};

const struct emif_regs emif_regs_elpida_400_mhz_2cs = {
	.sdram_config_init		= 0x80000eb9,
	.sdram_config			= 0x80001ab9,
	.ref_ctrl			= 0x00000618,
	.sdram_tim1			= 0x10eb0662,
	.sdram_tim2			= 0x20370dd2,
	.sdram_tim3			= 0x00b1c33f,
	.read_idle_ctrl			= 0x000501ff,
	.zq_config			= 0xd00b3214,
	.temp_alert_config		= 0xd8016893,
	.emif_ddr_phy_ctlr_1_init	= 0x049ffff5,
	.emif_ddr_phy_ctlr_1		= 0x049ff418
};
const struct dmm_lisa_map_regs lisa_map_2G_x_1_x_2 = {
	.dmm_lisa_map_0 = 0xFF020100,
	.dmm_lisa_map_1 = 0,
	.dmm_lisa_map_2 = 0,
	.dmm_lisa_map_3 = 0x80540300
};

const struct dmm_lisa_map_regs lisa_map_2G_x_2_x_2 = {
	.dmm_lisa_map_0 = 0xFF020100,
	.dmm_lisa_map_1 = 0,
	.dmm_lisa_map_2 = 0,
	.dmm_lisa_map_3 = 0x80640300
};

static void emif_get_reg_dump_sdp(u32 emif_nr, const struct emif_regs **regs)
{
	u32 omap4_rev = omap_revision();

	/* Same devices and geometry on both EMIFs */
	if (omap4_rev == OMAP4430_ES1_0)
		*regs = &emif_regs_elpida_380_mhz_1cs;
	else if (omap4_rev == OMAP4430_ES2_0)
		*regs = &emif_regs_elpida_200_mhz_2cs;
	else
		*regs = &emif_regs_elpida_400_mhz_2cs;
}
void emif_get_reg_dump(u32 emif_nr, const struct emif_regs **regs)
	__attribute__((weak, alias("emif_get_reg_dump_sdp")));

static void emif_get_dmm_regs_sdp(const struct dmm_lisa_map_regs
						**dmm_lisa_regs)
{
	u32 omap_rev = omap_revision();

	if (omap_rev == OMAP4430_ES1_0)
		*dmm_lisa_regs = &lisa_map_2G_x_1_x_2;
	else
		*dmm_lisa_regs = &lisa_map_2G_x_2_x_2;
}

void emif_get_dmm_regs(const struct dmm_lisa_map_regs **dmm_lisa_regs)
	__attribute__((weak, alias("emif_get_dmm_regs_sdp")));
