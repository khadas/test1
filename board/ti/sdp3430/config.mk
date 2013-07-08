#
# (C) Copyright 2006-2009
# Texas Instruments Incorporated, <www.ti.com>
#
# OMAP 3430 SDP uses OMAP3 (ARM-CortexA8) cpu
# see http://www.ti.com/ for more information on Texas Instruments
#
# SPDX-License-Identifier:	GPL-2.0+
#
# Physical Address:
# 8000'0000 (bank0)
# A000/0000 (bank1)
# Linux-Kernel is expected to be at 8000'8000, entry 8000'8000
# (mem base + reserved)

# For use with external or internal boots.
CONFIG_SYS_TEXT_BASE = 0x80008000
