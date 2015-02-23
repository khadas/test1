/* include/dwc3_omap_uboot.h
 *
 * Copyright (c) 2015 Texas Instruments Incorporated - http://www.ti.com
 *
 * Designware SuperSpeed OMAP Glue uboot init
 *
 * SPDX-License-Identifier:     GPL-2.0
 */

#ifndef __DWC3_OMAP_UBOOT_H_
#define __DWC3_OMAP_UBOOT_H_

#include <linux/usb/dwc3-omap.h>

enum omap_dwc3_vbus_id_status {
	OMAP_DWC3_ID_FLOAT,
	OMAP_DWC3_ID_GROUND,
	OMAP_DWC3_VBUS_OFF,
	OMAP_DWC3_VBUS_VALID,
};

struct dwc3_omap_device {
	void *base;
	enum dwc3_omap_utmi_mode utmi_mode;
	enum omap_dwc3_vbus_id_status vbus_id_status;
};
#endif /* __DWC3_OMAP_UBOOT_H_ */
