
/*
 * drivers/amlogic/media/common/vpu/vpu_power_init.c
 *
 * Copyright (C) 2015 Amlogic, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include <config.h>
#include <linux/kernel.h>
#include <amlogic/media/vpu/vpu.h>
#include "vpu_reg.h"
#include "vpu.h"

void vpu_mem_pd_init_off(void)
{
	return;
#ifdef VPU_DEBUG_PRINT
	VPUPR("%s\n", __func__);
#endif
}

void vpu_module_init_config(void)
{
	struct vpu_ctrl_s *ctrl_table;
	unsigned int _reg, _val, _bit, _len;
	int i = 0, cnt;

	/* vpu clk gate init off */
	cnt = vpu_conf.data->module_init_table_cnt;
	ctrl_table = vpu_conf.data->module_init_table;
	if (ctrl_table) {
		while (i < cnt) {
			if (ctrl_table[i].reg == VPU_REG_END)
				break;
			_reg = ctrl_table[i].reg;
			_val = ctrl_table[i].val;
			_bit = ctrl_table[i].bit;
			_len = ctrl_table[i].len;
			vpu_vcbus_setb(_reg, _val, _bit, _len);
			i++;
		}
	}
	vpu_hiu_setb(vpu_conf.data->vid_clk_reg, 0, 0, 8);

	/* dmc_arb_config */
	vpu_vcbus_write(VPU_RDARB_MODE_L1C1, 0x0); //0x210000
	vpu_vcbus_write(VPU_RDARB_MODE_L1C2, 0x10000);
	vpu_vcbus_write(VPU_RDARB_MODE_L2C1, 0x900000);
	vpu_vcbus_write(VPU_WRARB_MODE_L2C1, 0x20000);

	VPUPR("%s\n", __func__);
}

void vpu_power_on(void)
{
	struct vpu_ctrl_s *ctrl_table;
	struct vpu_reset_s *reset_table;
	unsigned int _reg, _val, _start, _end, _len, mask;
	int i, j;

	/* power on VPU_HDMI */
	ctrl_table = vpu_conf.data->power_table;
	if (ctrl_table) {
		i = 0;
		while (i < VPU_PWR_CNT_MAX) {
			if (ctrl_table[i].reg == VPU_REG_END)
				break;
			_reg = ctrl_table[i].reg;
			_val = 0;
			_start = ctrl_table[i].bit;
			_len = ctrl_table[i].len;
			vpu_ao_setb(_reg, _val, _start, _len);
			i++;
		}
	}
	udelay(20);

	/* power up memories */
	ctrl_table = vpu_conf.data->mem_pd_table;
	i = 0;
	while (i < VPU_MEM_PD_CNT_MAX) {
		if (ctrl_table[i].reg == VPU_REG_END)
			break;
		_reg = ctrl_table[i].reg;
		_start = ctrl_table[i].bit;
		_end = ctrl_table[i].len + ctrl_table[i].bit;
		for (j = _start; j < _end; j+=2) {
			vpu_hiu_setb(_reg, 0, j, 2);
			udelay(5);
		}
		i++;
	}
	for (i = 8; i < 16; i++) {
		vpu_hiu_setb(HHI_MEM_PD_REG0, 0, i, 1);
		udelay(5);
	}
	udelay(20);

	/* Reset VIU + VENC */
	/* Reset VENCI + VENCP + VADC + VENCL */
	/* Reset HDMI-APB + HDMI-SYS + HDMI-TX + HDMI-CEC */
	reset_table = vpu_conf.data->reset_table;
	i = 0;
	while (i < VPU_RESET_CNT_MAX) {
		if (reset_table[i].reg == VPU_REG_END)
			break;
		_reg = reset_table[i].reg;
		mask = reset_table[i].mask;
		vpu_cbus_clr_mask(_reg, mask);
		i++;
	}
	udelay(5);
	/* release Reset */
	i = 0;
	while (i < VPU_RESET_CNT_MAX) {
		if (reset_table[i].reg == VPU_REG_END)
			break;
		_reg = reset_table[i].reg;
		mask = reset_table[i].mask;
		vpu_cbus_set_mask(_reg, mask);
		i++;
	}

	/* Remove VPU_HDMI ISO */
	ctrl_table = vpu_conf.data->iso_table;
	if (ctrl_table) {
		i = 0;
		while (i < VPU_ISO_CNT_MAX) {
			if (ctrl_table[i].reg == VPU_REG_END)
				break;
			_reg = ctrl_table[i].reg;
			_val = 0;
			_start = ctrl_table[i].bit;
			_len = ctrl_table[i].len;
			vpu_ao_setb(_reg, _val, _start, _len);
			i++;
		}
	}

	VPUPR("%s\n", __func__);
}

void vpu_power_off(void)
{
	struct vpu_ctrl_s *ctrl_table;
	unsigned int _reg, _start, _end, _len, _val;
	int i, j;

	/* Enable Isolation */
	ctrl_table = vpu_conf.data->iso_table;
	i = 0;
	while (i < VPU_ISO_CNT_MAX) {
		if (ctrl_table[i].reg == VPU_REG_END)
			break;
		_reg = ctrl_table[i].reg;
		_val = 1;
		_start = ctrl_table[i].bit;
		_len = ctrl_table[i].len;
		vpu_ao_setb(_reg, _val, _start, _len);
		i++;
	}
	udelay(20);

	/* power down memories */
	ctrl_table = vpu_conf.data->mem_pd_table;
	i = 0;
	while (i < VPU_MEM_PD_CNT_MAX) {
		if (ctrl_table[i].reg == VPU_REG_END)
			break;
		_reg = ctrl_table[i].reg;
		_start = ctrl_table[i].bit;
		_end = ctrl_table[i].len + ctrl_table[i].bit;
		for (j = _start; j < _end; j+=2) {
			vpu_hiu_setb(_reg, 0x3, j, 2);
			udelay(5);
		}
		i++;
	}
	for (i = 8; i < 16; i++) {
		vpu_hiu_setb(HHI_MEM_PD_REG0, 0x1, i, 1);
		udelay(5);
	}
	udelay(20);

	/* Power down VPU domain */
	ctrl_table = vpu_conf.data->power_table;
	if (ctrl_table) {
		i = 0;
		while (i < VPU_PWR_CNT_MAX) {
			if (ctrl_table[i].reg == VPU_REG_END)
				break;
			_reg = ctrl_table[i].reg;
			_val = 1;
			_start = ctrl_table[i].bit;
			_len = ctrl_table[i].len;
			vpu_ao_setb(_reg, _val, _start, _len);
			i++;
		}
	}

	vpu_hiu_setb(vpu_conf.data->vapb_clk_reg, 0, 8, 1);
	vpu_hiu_setb(vpu_conf.data->vpu_clk_reg, 0, 8, 1);

	VPUPR("%s\n", __func__);
}

void vpu_power_on_new(void)
{
#ifdef CONFIG_SECURE_POWER_CONTROL
	if (vpu_conf.data->pwrctrl_id < VPU_PWR_ID_INVALID)
		pwr_ctrl_psci_smc(vpu_conf.data->pwrctrl_id, 1);
	VPUPR("%s\n", __func__);
#else
	VPUERR("%s: no CONFIG_SECURE_POWER_CONTROL\n", __func__);
#endif
}

void vpu_power_off_new(void)
{
#ifdef CONFIG_SECURE_POWER_CONTROL
	VPUPR("%s\n", __func__);
	if (vpu_conf.data->pwrctrl_id < VPU_PWR_ID_INVALID)
		pwr_ctrl_psci_smc(vpu_conf.data->pwrctrl_id, 0);
#else
	VPUERR("%s: no CONFIG_SECURE_POWER_CONTROL\n", __func__);
#endif

	vpu_hiu_setb(vpu_conf.data->vapb_clk_reg, 0, 8, 1);
	vpu_hiu_setb(vpu_conf.data->vpu_clk_reg, 0, 8, 1);
}
