/*
 *  EFI application loader
 *
 *  Copyright (c) 2017 Heinrich Schuchardt
 *
 *  SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _EFI_DRIVER_H
#define _EFI_DRIVER_H 1

#include <common.h>
#include <dm.h>
#include <efi_loader.h>

struct efi_driver_ops {
	const efi_guid_t *protocol;
	const efi_guid_t *child_protocol;
	int (*bind)(efi_handle_t handle, void *interface);
};

/*
 * This structure adds internal fields to the driver binding protocol.
 */
struct efi_driver_binding_extended_protocol {
	struct efi_driver_binding_protocol bp;
	const struct efi_driver_ops *ops;
};

#endif /* _EFI_DRIVER_H */
