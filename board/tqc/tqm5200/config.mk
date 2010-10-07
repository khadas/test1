#
# (C) Copyright 2004
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
# TQM5200 board:
#
#	Valid values for CONFIG_SYS_TEXT_BASE are:
#
#	0xFC000000   boot low (standard configuration with room for max 64 MByte
#		     Flash ROM)
#	0xFFF00000   boot high (for a backup copy of U-Boot)
#	0x00100000   boot from RAM (for testing only)
#

sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

ifndef CONFIG_SYS_TEXT_BASE
## Standard: boot low
CONFIG_SYS_TEXT_BASE = 0xFC000000
## For a backup copy of U-Boot at the end of flash: boot high
# CONFIG_SYS_TEXT_BASE = 0xFFF00000
## For testing: boot from RAM
# CONFIG_SYS_TEXT_BASE = 0x00100000
endif

PLATFORM_CPPFLAGS += -DCONFIG_SYS_TEXT_BASE=$(CONFIG_SYS_TEXT_BASE) \
	-I$(TOPDIR)/board
