#
# Copyright 2009 Freescale Semiconductor, Inc.
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
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

#
# p1_p2rdb board
#

ifndef NAND_SPL
ifeq ($(CONFIG_NAND), y)
LDSCRIPT := $(TOPDIR)/$(CPUDIR)/u-boot-nand.lds
endif
endif

ifeq ($(CONFIG_SDCARD), y)
RESET_VECTOR_ADDRESS = 0xf8fffffc
endif

ifeq ($(CONFIG_SPIFLASH), y)
RESET_VECTOR_ADDRESS = 0xf8fffffc
endif

ifndef RESET_VECTOR_ADDRESS
RESET_VECTOR_ADDRESS = 0xeffffffc
endif
