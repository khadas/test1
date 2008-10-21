#
# (C) Copyright 2001-2005
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

#
# CPU87 board
#

# This should be equal to the CONFIG_SYS_FLASH_BASE define in configs/cpu87.h
# for the "final" configuration, with U-Boot in flash, or the address
# in RAM where U-Boot is loaded at for debugging.
#

ifeq ($(CONFIG_BOOT_ROM),y)
	TEXT_BASE := 0xFF800000
	PLATFORM_CPPFLAGS += -DCONFIG_BOOT_ROM
else
	TEXT_BASE := 0xFF000000
endif

PLATFORM_CPPFLAGS += -DTEXT_BASE=$(TEXT_BASE) -I$(TOPDIR)
