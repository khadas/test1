/*
 * MUSB OTG driver u-boot specific functions
 *
 * Copyright © 2015 Hans de Goede <hdegoede@redhat.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __MUSB_UBOOT_H__
#define __MUSB_UBOOT_H__

#include <usb.h>
#include "linux-compat.h"
#include "usb-compat.h"
#include "musb_core.h"

struct musb_host_data {
	struct musb *host;
	struct usb_hcd hcd;
	enum usb_device_speed host_speed;
	struct usb_host_endpoint hep;
	struct urb urb;
};

#endif
