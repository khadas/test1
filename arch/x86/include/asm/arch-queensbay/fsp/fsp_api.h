/*
 * Copyright (C) 2013, Intel Corporation
 * Copyright (C) 2014, Bin Meng <bmeng.cn@gmail.com>
 *
 * SPDX-License-Identifier:	Intel
 */

#ifndef __FSP_API_H__
#define __FSP_API_H__

/*
 * FspInit continuation function prototype.
 * Control will be returned to this callback function after FspInit API call.
 */
typedef void (*fsp_continuation_f)(u32 status, void *hob_list);

struct fsp_init_params {
	/* Non-volatile storage buffer pointer */
	void			*nvs_buf;
	/* Runtime buffer pointer */
	void			*rt_buf;
	/* Continuation function address */
	fsp_continuation_f	continuation;
};

struct common_buf {
	/*
	 * Stack top pointer used by the bootloader. The new stack frame will be
	 * set up at this location after FspInit API call.
	 */
	u32	*stack_top;
	u32	boot_mode;	/* Current system boot mode */
	void	*upd_data;	/* User platform configuraiton data region */
	u32	reserved[7];	/* Reserved */
};

enum fsp_phase {
	/* Notification code for post PCI enuermation */
	INIT_PHASE_PCI	= 0x20,
	/* Notification code before transfering control to the payload */
	INIT_PHASE_BOOT	= 0x40
};

struct fsp_notify_params {
	/* Notification phase used for NotifyPhase API */
	enum fsp_phase	phase;
};

/* FspInit API function prototype */
typedef u32 (*fsp_init_f)(struct fsp_init_params *params);

/* FspNotify API function prototype */
typedef u32 (*fsp_notify_f)(struct fsp_notify_params *params);

#endif
