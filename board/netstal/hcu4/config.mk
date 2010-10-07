#
# (C) Copyright 2005 Netstal Maschinen AG
#     Niklaus Giger (ng@netstal.com)
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
# Netstal Maschinen AG: HCU4 boards
#

CONFIG_SYS_TEXT_BASE = 0xFFFB0000

ifeq ($(debug),1)
PLATFORM_CPPFLAGS += -DDEBUG -g
endif
