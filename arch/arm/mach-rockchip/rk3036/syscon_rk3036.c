// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2015 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <syscon.h>
#include <asm/arch/clock.h>

static const struct udevice_id rk3036_syscon_ids[] = {
	{ .compatible = "rockchip,rk3036-grf", .data = ROCKCHIP_SYSCON_GRF },
	{ }
};

U_BOOT_DRIVER(syscon_rk3036) = {
	.name = "rk3036_syscon",
	.id = UCLASS_SYSCON,
	.of_match = rk3036_syscon_ids,
};
