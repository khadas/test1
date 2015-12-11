/*
 * Copyright (C) 2015, Bin Meng <bmeng.cn@gmail.com>
 *
 * SPDX-License-Identifier:	Intel
 */

#ifndef __FSP_CONFIGS_H__
#define __FSP_CONFIGS_H__

struct fsp_config_data {
	struct fsp_cfg_common	common;
	struct upd_region	fsp_upd;
};

#endif /* __FSP_CONFIGS_H__ */
