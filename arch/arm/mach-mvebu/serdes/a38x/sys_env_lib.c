/*
 * Copyright (C) Marvell International Ltd. and its affiliates
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <i2c.h>
#include <spl.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/soc.h>

#include "seq_exec.h"
#include "sys_env_lib.h"

#include "../../../drivers/ddr/marvell/a38x/ddr3_a38x.h"

#ifdef CONFIG_ARMADA_38X
enum unit_id sys_env_soc_unit_nums[MAX_UNITS_ID][MAX_DEV_ID_NUM] = {
/*                     6820    6810     6811     6828     */
/* PEX_UNIT_ID      */ { 4,     3,       3,       4},
/* ETH_GIG_UNIT_ID  */ { 3,	2,       3,       3},
/* USB3H_UNIT_ID    */ { 2,     2,       2,       2},
/* USB3D_UNIT_ID    */ { 1,     1,       1,       1},
/* SATA_UNIT_ID     */ { 2,     2,       2,       4},
/* QSGMII_UNIT_ID   */ { 1,     0,       0,       1},
/* XAUI_UNIT_ID     */ { 0,     0,       0,       0},
/* RXAUI_UNIT_ID    */ { 0,     0,       0,       0}
};
#else  /* if (CONFIG_ARMADA_39X) */
enum unit_id sys_env_soc_unit_nums[MAX_UNITS_ID][MAX_DEV_ID_NUM] = {
/*                      6920     6928     */
/* PEX_UNIT_ID      */ { 4,       4},
/* ETH_GIG_UNIT_ID  */ { 3,       4},
/* USB3H_UNIT_ID    */ { 1,       2},
/* USB3D_UNIT_ID    */ { 0,       1},
/* SATA_UNIT_ID     */ { 0,       4},
/* QSGMII_UNIT_ID   */ { 0,       1},
/* XAUI_UNIT_ID     */ { 1,       1},
/* RXAUI_UNIT_ID    */ { 1,	  1}
};
#endif

u32 g_dev_id = -1;

u32 mv_board_id_get(void)
{
#if defined(CONFIG_DB_88F6820_GP)
	return DB_GP_68XX_ID;
#else
	/*
	 * Return 0 here for custom board as this should not be used
	 * for custom boards.
	 */
	return 0;
#endif
}

u32 mv_board_tclk_get(void)
{
	u32 value;

	value = (reg_read(DEVICE_SAMPLE_AT_RESET1_REG) >> 15) & 0x1;

	switch (value) {
	case (0x0):
		return 250000000;
	case (0x1):
		return 200000000;
	default:
		return 0xffffffff;
	}
}

u32 mv_board_id_index_get(u32 board_id)
{
	/*
	 * Marvell Boards use 0x10 as base for Board ID:
	 * mask MSB to receive index for board ID
	 */
	return board_id & (MARVELL_BOARD_ID_MASK - 1);
}

/*
 * sys_env_suspend_wakeup_check
 * DESCRIPTION:		Reads GPIO input for suspend-wakeup indication.
 * INPUT:		None.
 * OUTPUT:
 * RETURNS:		u32 indicating suspend wakeup status:
 * 0 - Not supported,
 * 1 - supported: read magic word detect wakeup,
 * 2 - detected wakeup from GPIO.
 */
enum suspend_wakeup_status sys_env_suspend_wakeup_check(void)
{
	u32 reg, board_id_index, gpio;
	struct board_wakeup_gpio board_gpio[] = MV_BOARD_WAKEUP_GPIO_INFO;

	board_id_index = mv_board_id_index_get(mv_board_id_get());
	if (!(sizeof(board_gpio) / sizeof(struct board_wakeup_gpio) >
	      board_id_index)) {
		printf("\n_failed loading Suspend-Wakeup information (invalid board ID)\n");
		return SUSPEND_WAKEUP_DISABLED;
	}

	/*
	 * - Detect if Suspend-Wakeup is supported on current board
	 * - Fetch the GPIO number for wakeup status input indication
	 */
	if (board_gpio[board_id_index].gpio_num == -1) {
		/* Suspend to RAM is not supported */
		return SUSPEND_WAKEUP_DISABLED;
	} else if (board_gpio[board_id_index].gpio_num == -2) {
		/*
		 * Suspend to RAM is supported but GPIO indication is
		 * not implemented - Skip
		 */
		return SUSPEND_WAKEUP_ENABLED;
	} else {
		gpio = board_gpio[board_id_index].gpio_num;
	}

	/* Initialize MPP for GPIO (set MPP = 0x0) */
	reg = reg_read(MPP_CONTROL_REG(MPP_REG_NUM(gpio)));
	/* reset MPP21 to 0x0, keep rest of MPP settings*/
	reg &= ~MPP_MASK(gpio);
	reg_write(MPP_CONTROL_REG(MPP_REG_NUM(gpio)), reg);

	/* Initialize GPIO as input */
	reg = reg_read(GPP_DATA_OUT_EN_REG(GPP_REG_NUM(gpio)));
	reg |= GPP_MASK(gpio);
	reg_write(GPP_DATA_OUT_EN_REG(GPP_REG_NUM(gpio)), reg);

	/*
	 * Check GPP for input status from PIC: 0 - regular init,
	 * 1 - suspend wakeup
	 */
	reg = reg_read(GPP_DATA_IN_REG(GPP_REG_NUM(gpio)));

	/* if GPIO is ON: wakeup from S2RAM indication detected */
	return (reg & GPP_MASK(gpio)) ? SUSPEND_WAKEUP_ENABLED_GPIO_DETECTED :
		SUSPEND_WAKEUP_DISABLED;
}

/*
 * mv_ctrl_dev_id_index_get
 *
 * DESCRIPTION: return SOC device index
 * INPUT: None
 * OUTPUT: None
 * RETURN:
 *        return SOC device index
 */
u32 sys_env_id_index_get(u32 ctrl_model)
{
	switch (ctrl_model) {
	case MV_6820_DEV_ID:
		return MV_6820_INDEX;
	case MV_6810_DEV_ID:
		return MV_6810_INDEX;
	case MV_6811_DEV_ID:
		return MV_6811_INDEX;
	case MV_6828_DEV_ID:
		return MV_6828_INDEX;
	case MV_6920_DEV_ID:
		return MV_6920_INDEX;
	case MV_6928_DEV_ID:
		return MV_6928_INDEX;
	default:
		return MV_6820_INDEX;
	}
}

u32 sys_env_unit_max_num_get(enum unit_id unit)
{
	u32 dev_id_index;

	if (unit >= MAX_UNITS_ID) {
		printf("%s: Error: Wrong unit type (%u)\n", __func__, unit);
		return 0;
	}

	dev_id_index = sys_env_id_index_get(sys_env_model_get());
	return sys_env_soc_unit_nums[unit][dev_id_index];
}

/*
 * sys_env_model_get
 * DESCRIPTION:	Returns 16bit describing the device model (ID) as defined
 *		in Vendor ID configuration register
 */
u16 sys_env_model_get(void)
{
	u32 default_ctrl_id, ctrl_id = reg_read(DEV_ID_REG);
	ctrl_id = (ctrl_id & (DEV_ID_REG_DEVICE_ID_MASK)) >>
		DEV_ID_REG_DEVICE_ID_OFFS;

	switch (ctrl_id) {
	case MV_6820_DEV_ID:
	case MV_6810_DEV_ID:
	case MV_6811_DEV_ID:
	case MV_6828_DEV_ID:
	case MV_6920_DEV_ID:
	case MV_6928_DEV_ID:
		return ctrl_id;
	default:
		/* Device ID Default for A38x: 6820 , for A39x: 6920 */
	#ifdef CONFIG_ARMADA_38X
		default_ctrl_id =  MV_6820_DEV_ID;
	#else
		default_ctrl_id = MV_6920_DEV_ID;
	#endif
		printf("%s: Error retrieving device ID (%x), using default ID = %x\n",
		       __func__, ctrl_id, default_ctrl_id);
		return default_ctrl_id;
	}
}

/*
 * sys_env_device_id_get
 * DESCRIPTION:	Returns enum (0..7) index of the device model (ID)
 */
u32 sys_env_device_id_get(void)
{
	char *device_id_str[7] = {
		"6810", "6820", "6811", "6828", "NONE", "6920", "6928"
	};

	if (g_dev_id != -1)
		return g_dev_id;

	g_dev_id = reg_read(DEVICE_SAMPLE_AT_RESET1_REG);
	g_dev_id = g_dev_id >> SAR_DEV_ID_OFFS & SAR_DEV_ID_MASK;
	printf("Detected Device ID %s\n", device_id_str[g_dev_id]);

	return g_dev_id;
}

#ifdef MV_DDR_TOPOLOGY_UPDATE_FROM_TWSI
/*
* sys_env_get_topology_update_info
* DESCRIPTION: Read TWSI fields to update DDR topology structure
* INPUT: None
* OUTPUT: None, 0 means no topology update
* RETURN:
*       Bit mask of changes topology features
*/
#ifdef CONFIG_ARMADA_39X
u32 sys_env_get_topology_update_info(
	struct topology_update_info *tui)
{
	/* Set 16/32 bit configuration*/
	tui->update_width = 1;
	tui->width = TOPOLOGY_UPDATE_WIDTH_32BIT;

#ifdef CONFIG_DDR3
	if (1 == sys_env_config_get(MV_CONFIG_DDR_BUSWIDTH)) {
		/* 16bit */
		tui->width = TOPOLOGY_UPDATE_WIDTH_16BIT;
	} else {
		/* 32bit */
		tui->width = TOPOLOGY_UPDATE_WIDTH_32BIT;
	}
#endif

	/* Set ECC/no ECC bit configuration */
	tui->update_ecc = 1;
	if (0 == sys_env_config_get(MV_CONFIG_DDR_ECC_EN)) {
		/* NO ECC */
		tui->ecc = TOPOLOGY_UPDATE_ECC_OFF;
	} else {
		/* ECC */
		tui->ecc = TOPOLOGY_UPDATE_ECC_ON;
	}

	tui->update_ecc_pup3_mode = 1;
	tui->ecc_pup_mode_offset = TOPOLOGY_UPDATE_ECC_OFFSET_PUP4;

	return MV_OK;
}
#else /*CONFIG_ARMADA_38X*/
u32 sys_env_get_topology_update_info(
	struct topology_update_info *tui)
{
	u8 config_val;
	u8 ecc_mode[A38X_MV_MAX_MARVELL_BOARD_ID -
		    A38X_MARVELL_BOARD_ID_BASE][5] = TOPOLOGY_UPDATE;
	u8 board_id = mv_board_id_get();
	int ret;

	board_id = mv_board_id_index_get(board_id);
	ret = i2c_read(EEPROM_I2C_ADDR, 0, 2, &config_val, 1);
	if (ret) {
		DEBUG_INIT_S("sys_env_get_topology_update_info: TWSI Read failed\n");
		return 0;
	}

	/* Set 16/32 bit configuration */
	if ((0 == (config_val & DDR_SATR_CONFIG_MASK_WIDTH)) ||
	    (ecc_mode[board_id][TOPOLOGY_UPDATE_32BIT] == 0)) {
		/* 16bit by SatR of 32bit mode not supported for the board */
		if ((ecc_mode[board_id][TOPOLOGY_UPDATE_16BIT] != 0)) {
			tui->update_width = 1;
			tui->width = TOPOLOGY_UPDATE_WIDTH_16BIT;
		}
	} else {
		/* 32bit */
		if ((ecc_mode[board_id][TOPOLOGY_UPDATE_32BIT] != 0)) {
			tui->update_width = 1;
			tui->width = TOPOLOGY_UPDATE_WIDTH_32BIT;
		}
	}

	/* Set ECC/no ECC bit configuration */
	if (0 == (config_val & DDR_SATR_CONFIG_MASK_ECC)) {
		/* NO ECC */
		tui->update_ecc = 1;
		tui->ecc = TOPOLOGY_UPDATE_ECC_OFF;
	} else {
		/* ECC */
		if ((ecc_mode[board_id][TOPOLOGY_UPDATE_32BIT_ECC] != 0) ||
		    (ecc_mode[board_id][TOPOLOGY_UPDATE_16BIT_ECC] != 0) ||
		    (ecc_mode[board_id][TOPOLOGY_UPDATE_16BIT_ECC_PUP3] != 0)) {
			tui->update_ecc = 1;
			tui->ecc = TOPOLOGY_UPDATE_ECC_ON;
		}
	}

	/* Set ECC pup bit configuration */
	if (0 == (config_val & DDR_SATR_CONFIG_MASK_ECC_PUP)) {
		/* PUP3 */
		/*
		 * Check if PUP3 configuration allowed, if not -
		 * force Pup4 with warning message
		 */
		if ((ecc_mode[board_id][TOPOLOGY_UPDATE_16BIT_ECC_PUP3] != 0)) {
			if (tui->width == TOPOLOGY_UPDATE_WIDTH_16BIT) {
				tui->update_ecc_pup3_mode = 1;
				tui->ecc_pup_mode_offset =
					TOPOLOGY_UPDATE_ECC_OFFSET_PUP3;
			} else {
				if ((ecc_mode[board_id][TOPOLOGY_UPDATE_32BIT_ECC] != 0)) {
					printf("DDR Topology Update: ECC PUP3 not valid for 32bit mode, force ECC in PUP4\n");
					tui->update_ecc_pup3_mode = 1;
					tui->ecc_pup_mode_offset =
						TOPOLOGY_UPDATE_ECC_OFFSET_PUP4;
				}
			}
		} else {
			if (ecc_mode[board_id][TOPOLOGY_UPDATE_16BIT_ECC] !=
			    0) {
				printf("DDR Topology Update: ECC on PUP3 not supported, force ECC on PUP4\n");
				tui->update_ecc_pup3_mode = 1;
				tui->ecc_pup_mode_offset =
					TOPOLOGY_UPDATE_ECC_OFFSET_PUP4;
			}
		}
	} else {
		/* PUP4 */
		if ((ecc_mode[board_id][TOPOLOGY_UPDATE_32BIT_ECC] != 0) ||
		    (ecc_mode[board_id][TOPOLOGY_UPDATE_16BIT_ECC] != 0)) {
			tui->update_ecc_pup3_mode = 1;
			tui->ecc_pup_mode_offset =
				TOPOLOGY_UPDATE_ECC_OFFSET_PUP4;
		}
	}

	/*
	 * Check for forbidden ECC mode,
	 * if by default width and pup selection set 32bit ECC mode and this
	 * mode not supported for the board - config 16bit with ECC on PUP3
	 */
	if ((tui->ecc == TOPOLOGY_UPDATE_ECC_ON) &&
	    (tui->width == TOPOLOGY_UPDATE_WIDTH_32BIT)) {
		if (ecc_mode[board_id][TOPOLOGY_UPDATE_32BIT_ECC] == 0) {
			printf("DDR Topology Update: 32bit mode with ECC not allowed on this board, forced  16bit with ECC on PUP3\n");
			tui->width = TOPOLOGY_UPDATE_WIDTH_16BIT;
			tui->update_ecc_pup3_mode = 1;
			tui->ecc_pup_mode_offset =
				TOPOLOGY_UPDATE_ECC_OFFSET_PUP3;
		}
	}

	return MV_OK;
}
#endif /* CONFIG_ARMADA_38X */
#endif /* MV_DDR_TOPOLOGY_UPDATE_FROM_TWSI */
