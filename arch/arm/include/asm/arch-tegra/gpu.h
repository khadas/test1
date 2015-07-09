/*
 *  (C) Copyright 2015
 *  NVIDIA Corporation <www.nvidia.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ASM_ARCH_TEGRA_GPU_H
#define __ASM_ARCH_TEGRA_GPU_H

#if defined(CONFIG_TEGRA_GPU)

void config_gpu(void);
bool gpu_configured(void);

#else /* CONFIG_TEGRA_GPU */

static inline void config_gpu(void)
{
}

static inline bool gpu_configured(void)
{
	return false;
}

#endif /* CONFIG_TEGRA_GPU */
