/*
 * Copyright (C) 2016 Bin Meng <bmeng.cn@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/acpi/global_nvs.h>

OperationRegion(GNVS, SystemMemory, ACPI_GNVS_ADDR, ACPI_GNVS_SIZE)
Field(GNVS, ByteAcc, NoLock, Preserve)
{
	Offset (0x00),
	PCNT, 8,	/* processor count */
}
