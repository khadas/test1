#
# (C) Copyright 2003
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
# galaxy5200 board:
#
#	Valid values for CONFIG_SYS_TEXT_BASE are:
#
#	0xFFF00000   boot high (standard configuration)
#	0xFE000000   boot low
#	0x00100000   boot from RAM (for testing only) does not work
#

sinclude $(TOPDIR)/board/$(BOARDDIR)/config.tmp

ifdef CONFIG_galaxy5200_LOWBOOT
CONFIG_SYS_TEXT_BASE = 0xFE000000
endif

ifndef CONFIG_SYS_TEXT_BASE
## Standard: boot high
CONFIG_SYS_TEXT_BASE = 0xFFF00000
endif

PLATFORM_CPPFLAGS += -DCONFIG_SYS_TEXT_BASE=$(CONFIG_SYS_TEXT_BASE) \
	-I$(TOPDIR)/board
