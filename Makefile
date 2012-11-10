#
# (C) Copyright 2000-2012
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# See file CREDITS for list of people who contributed to this
# project.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundatio; either version 2 of
# the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston,
# MA 02111-1307 USA
#

VERSION = 2013
PATCHLEVEL = 01
SUBLEVEL =
EXTRAVERSION = -rc1
ifneq "$(SUBLEVEL)" ""
U_BOOT_VERSION = $(VERSION).$(PATCHLEVEL).$(SUBLEVEL)$(EXTRAVERSION)
else
U_BOOT_VERSION = $(VERSION).$(PATCHLEVEL)$(EXTRAVERSION)
endif
TIMESTAMP_FILE = $(obj)include/generated/timestamp_autogenerated.h
VERSION_FILE = $(obj)include/generated/version_autogenerated.h

HOSTARCH := $(shell uname -m | \
	sed -e s/i.86/x86/ \
	    -e s/sun4u/sparc64/ \
	    -e s/arm.*/arm/ \
	    -e s/sa110/arm/ \
	    -e s/ppc64/powerpc/ \
	    -e s/ppc/powerpc/ \
	    -e s/macppc/powerpc/\
	    -e s/sh.*/sh/)

HOSTOS := $(shell uname -s | tr '[:upper:]' '[:lower:]' | \
	    sed -e 's/\(cygwin\).*/cygwin/')

# Set shell to bash if possible, otherwise fall back to sh
SHELL := $(shell if [ -x "$$BASH" ]; then echo $$BASH; \
	else if [ -x /bin/bash ]; then echo /bin/bash; \
	else echo sh; fi; fi)

export	HOSTARCH HOSTOS SHELL

# Deal with colliding definitions from tcsh etc.
VENDOR=

#########################################################################
# Allow for silent builds
ifeq (,$(findstring s,$(MAKEFLAGS)))
XECHO = echo
else
XECHO = :
endif

#########################################################################
#
# U-boot build supports producing a object files to the separate external
# directory. Two use cases are supported:
#
# 1) Add O= to the make command line
# 'make O=/tmp/build all'
#
# 2) Set environement variable BUILD_DIR to point to the desired location
# 'export BUILD_DIR=/tmp/build'
# 'make'
#
# The second approach can also be used with a MAKEALL script
# 'export BUILD_DIR=/tmp/build'
# './MAKEALL'
#
# Command line 'O=' setting overrides BUILD_DIR environent variable.
#
# When none of the above methods is used the local build is performed and
# the object files are placed in the source directory.
#

ifdef O
ifeq ("$(origin O)", "command line")
BUILD_DIR := $(O)
endif
endif

# Call a source code checker (by default, "sparse") as part of the
# C compilation.
#
# Use 'make C=1' to enable checking of re-compiled files.
#
# See the linux kernel file "Documentation/sparse.txt" for more details,
# including where to get the "sparse" utility.

ifdef C
ifeq ("$(origin C)", "command line")
CHECKSRC := $(C)
endif
endif
ifndef CHECKSRC
  CHECKSRC = 0
endif
export CHECKSRC

ifneq ($(BUILD_DIR),)
saved-output := $(BUILD_DIR)

# Attempt to create a output directory.
$(shell [ -d ${BUILD_DIR} ] || mkdir -p ${BUILD_DIR})

# Verify if it was successful.
BUILD_DIR := $(shell cd $(BUILD_DIR) && /bin/pwd)
$(if $(BUILD_DIR),,$(error output directory "$(saved-output)" does not exist))
endif # ifneq ($(BUILD_DIR),)

OBJTREE		:= $(if $(BUILD_DIR),$(BUILD_DIR),$(CURDIR))
SPLTREE		:= $(OBJTREE)/spl
SRCTREE		:= $(CURDIR)
TOPDIR		:= $(SRCTREE)
LNDIR		:= $(OBJTREE)
export	TOPDIR SRCTREE OBJTREE SPLTREE

MKCONFIG	:= $(SRCTREE)/mkconfig
export MKCONFIG

ifneq ($(OBJTREE),$(SRCTREE))
REMOTE_BUILD	:= 1
export REMOTE_BUILD
endif

# $(obj) and (src) are defined in config.mk but here in main Makefile
# we also need them before config.mk is included which is the case for
# some targets like unconfig, clean, clobber, distclean, etc.
ifneq ($(OBJTREE),$(SRCTREE))
obj := $(OBJTREE)/
src := $(SRCTREE)/
else
obj :=
src :=
endif
export obj src

# Make sure CDPATH settings don't interfere
unexport CDPATH

#########################################################################

# The "tools" are needed early, so put this first
# Don't include stuff already done in $(LIBS)
# The "examples" conditionally depend on U-Boot (say, when USE_PRIVATE_LIBGCC
# is "yes"), so compile examples after U-Boot is compiled.
SUBDIR_TOOLS = tools
SUBDIR_EXAMPLES = examples/standalone examples/api
SUBDIRS = $(SUBDIR_TOOLS)

.PHONY : $(SUBDIRS) $(VERSION_FILE) $(TIMESTAMP_FILE)

ifeq ($(obj)include/config.mk,$(wildcard $(obj)include/config.mk))

# Include autoconf.mk before config.mk so that the config options are available
# to all top level build files.  We need the dummy all: target to prevent the
# dependency target in autoconf.mk.dep from being the default.
all:
sinclude $(obj)include/autoconf.mk.dep
sinclude $(obj)include/autoconf.mk

ifndef CONFIG_SANDBOX
SUBDIRS += $(SUBDIR_EXAMPLES)
endif

# load ARCH, BOARD, and CPU configuration
include $(obj)include/config.mk
export	ARCH CPU BOARD VENDOR SOC

# set default to nothing for native builds
ifeq ($(HOSTARCH),$(ARCH))
CROSS_COMPILE ?=
endif

# load other configuration
include $(TOPDIR)/config.mk

# If board code explicitly specified LDSCRIPT or CONFIG_SYS_LDSCRIPT, use
# that (or fail if absent).  Otherwise, search for a linker script in a
# standard location.

LDSCRIPT_MAKEFILE_DIR = $(dir $(LDSCRIPT))

ifndef LDSCRIPT
	#LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds.debug
	ifdef CONFIG_SYS_LDSCRIPT
		# need to strip off double quotes
		LDSCRIPT := $(subst ",,$(CONFIG_SYS_LDSCRIPT))
	endif
endif

# If there is no specified link script, we look in a number of places for it
ifndef LDSCRIPT
	ifeq ($(CONFIG_NAND_U_BOOT),y)
		LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot-nand.lds
		ifeq ($(wildcard $(LDSCRIPT)),)
			LDSCRIPT := $(TOPDIR)/$(CPUDIR)/u-boot-nand.lds
		endif
	endif
	ifeq ($(wildcard $(LDSCRIPT)),)
		LDSCRIPT := $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds
	endif
	ifeq ($(wildcard $(LDSCRIPT)),)
		LDSCRIPT := $(TOPDIR)/$(CPUDIR)/u-boot.lds
	endif
	ifeq ($(wildcard $(LDSCRIPT)),)
		LDSCRIPT := $(TOPDIR)/arch/$(ARCH)/cpu/u-boot.lds
		# We don't expect a Makefile here
		LDSCRIPT_MAKEFILE_DIR =
	endif
	ifeq ($(wildcard $(LDSCRIPT)),)
$(error could not find linker script)
	endif
endif

#########################################################################
# U-Boot objects....order is important (i.e. start must be first)

OBJS  = $(CPUDIR)/start.o
ifeq ($(CPU),x86)
OBJS += $(CPUDIR)/start16.o
OBJS += $(CPUDIR)/resetvec.o
endif
ifeq ($(CPU),ppc4xx)
OBJS += $(CPUDIR)/resetvec.o
endif
ifeq ($(CPU),mpc85xx)
OBJS += $(CPUDIR)/resetvec.o
endif

OBJS := $(addprefix $(obj),$(OBJS))

HAVE_VENDOR_COMMON_LIB = $(if $(wildcard board/$(VENDOR)/common/Makefile),y,n)

LIBS-y += lib/libgeneric.o
LIBS-y += lib/lzma/liblzma.o
LIBS-y += lib/lzo/liblzo.o
LIBS-y += lib/zlib/libz.o
LIBS-$(CONFIG_TIZEN) += lib/tizen/libtizen.o
LIBS-$(HAVE_VENDOR_COMMON_LIB) += board/$(VENDOR)/common/lib$(VENDOR).o
LIBS-y += $(CPUDIR)/lib$(CPU).o
ifdef SOC
LIBS-y += $(CPUDIR)/$(SOC)/lib$(SOC).o
endif
ifeq ($(CPU),ixp)
LIBS-y += drivers/net/npe/libnpe.o
endif
LIBS-$(CONFIG_OF_EMBED) += dts/libdts.o
LIBS-y += arch/$(ARCH)/lib/lib$(ARCH).o
LIBS-y += fs/libfs.o \
	fs/cbfs/libcbfs.o \
	fs/cramfs/libcramfs.o \
	fs/ext4/libext4fs.o \
	fs/fat/libfat.o \
	fs/fdos/libfdos.o \
	fs/jffs2/libjffs2.o \
	fs/reiserfs/libreiserfs.o \
	fs/ubifs/libubifs.o \
	fs/yaffs2/libyaffs2.o \
	fs/zfs/libzfs.o
LIBS-y += net/libnet.o
LIBS-y += disk/libdisk.o
LIBS-y += drivers/bios_emulator/libatibiosemu.o
LIBS-y += drivers/block/libblock.o
LIBS-$(CONFIG_BOOTCOUNT_LIMIT) += drivers/bootcount/libbootcount.o
LIBS-y += drivers/dma/libdma.o
LIBS-y += drivers/fpga/libfpga.o
LIBS-y += drivers/gpio/libgpio.o
LIBS-y += drivers/hwmon/libhwmon.o
LIBS-y += drivers/i2c/libi2c.o
LIBS-y += drivers/input/libinput.o
LIBS-y += drivers/misc/libmisc.o
LIBS-y += drivers/mmc/libmmc.o
LIBS-y += drivers/mtd/libmtd.o
LIBS-y += drivers/mtd/nand/libnand.o
LIBS-y += drivers/mtd/onenand/libonenand.o
LIBS-y += drivers/mtd/ubi/libubi.o
LIBS-y += drivers/mtd/spi/libspi_flash.o
LIBS-y += drivers/net/libnet.o
LIBS-y += drivers/net/phy/libphy.o
LIBS-y += drivers/pci/libpci.o
LIBS-y += drivers/pcmcia/libpcmcia.o
LIBS-y += drivers/power/libpower.o
LIBS-y += drivers/spi/libspi.o
LIBS-y += drivers/dfu/libdfu.o
ifeq ($(CPU),mpc83xx)
LIBS-y += drivers/qe/libqe.o
LIBS-y += arch/powerpc/cpu/mpc8xxx/ddr/libddr.o
LIBS-y += arch/powerpc/cpu/mpc8xxx/lib8xxx.o
endif
ifeq ($(CPU),mpc85xx)
LIBS-y += drivers/qe/libqe.o
LIBS-y += drivers/net/fm/libfm.o
LIBS-y += arch/powerpc/cpu/mpc8xxx/ddr/libddr.o
LIBS-y += arch/powerpc/cpu/mpc8xxx/lib8xxx.o
endif
ifeq ($(CPU),mpc86xx)
LIBS-y += arch/powerpc/cpu/mpc8xxx/ddr/libddr.o
LIBS-y += arch/powerpc/cpu/mpc8xxx/lib8xxx.o
endif
LIBS-y += drivers/rtc/librtc.o
LIBS-y += drivers/serial/libserial.o
LIBS-$(CONFIG_GENERIC_LPC_TPM) += drivers/tpm/libtpm.o
LIBS-y += drivers/twserial/libtws.o
LIBS-y += drivers/usb/eth/libusb_eth.o
LIBS-y += drivers/usb/gadget/libusb_gadget.o
LIBS-y += drivers/usb/host/libusb_host.o
LIBS-y += drivers/usb/musb/libusb_musb.o
LIBS-y += drivers/usb/phy/libusb_phy.o
LIBS-y += drivers/usb/ulpi/libusb_ulpi.o
LIBS-y += drivers/video/libvideo.o
LIBS-y += drivers/watchdog/libwatchdog.o
LIBS-y += common/libcommon.o
LIBS-y += lib/libfdt/libfdt.o
LIBS-y += api/libapi.o
LIBS-y += post/libpost.o
LIBS-y += test/libtest.o

ifneq ($(CONFIG_AM33XX)$(CONFIG_OMAP34XX)$(CONFIG_OMAP44XX)$(CONFIG_OMAP54XX),)
LIBS-y += $(CPUDIR)/omap-common/libomap-common.o
endif

ifneq (,$(filter $(SOC), mx25 mx27 mx5 mx6 mx31 mx35))
LIBS-y += arch/$(ARCH)/imx-common/libimx-common.o
endif

ifeq ($(SOC),s5pc1xx)
LIBS-y += $(CPUDIR)/s5p-common/libs5p-common.o
endif
ifeq ($(SOC),exynos)
LIBS-y += $(CPUDIR)/s5p-common/libs5p-common.o
endif
ifeq ($(SOC),tegra20)
LIBS-y += arch/$(ARCH)/cpu/$(SOC)-common/lib$(SOC)-common.o
LIBS-y += arch/$(ARCH)/cpu/tegra-common/libcputegra-common.o
LIBS-y += $(CPUDIR)/tegra-common/libtegra-common.o
endif

LIBS := $(addprefix $(obj),$(sort $(LIBS-y)))
.PHONY : $(LIBS)

LIBBOARD = board/$(BOARDDIR)/lib$(BOARD).o
LIBBOARD := $(addprefix $(obj),$(LIBBOARD))

# Add GCC lib
ifdef USE_PRIVATE_LIBGCC
ifeq ("$(USE_PRIVATE_LIBGCC)", "yes")
PLATFORM_LIBGCC = $(OBJTREE)/arch/$(ARCH)/lib/libgcc.o
else
PLATFORM_LIBGCC = -L $(USE_PRIVATE_LIBGCC) -lgcc
endif
else
PLATFORM_LIBGCC := -L $(shell dirname `$(CC) $(CFLAGS) -print-libgcc-file-name`) -lgcc
endif
PLATFORM_LIBS += $(PLATFORM_LIBGCC)
export PLATFORM_LIBS

# Special flags for CPP when processing the linker script.
# Pass the version down so we can handle backwards compatibility
# on the fly.
LDPPFLAGS += \
	-include $(TOPDIR)/include/u-boot/u-boot.lds.h \
	-DCPUDIR=$(CPUDIR) \
	$(shell $(LD) --version | \
	  sed -ne 's/GNU ld version \([0-9][0-9]*\)\.\([0-9][0-9]*\).*/-DLD_MAJOR=\1 -DLD_MINOR=\2/p')

__OBJS := $(subst $(obj),,$(OBJS))
__LIBS := $(subst $(obj),,$(LIBS)) $(subst $(obj),,$(LIBBOARD))

#########################################################################
#########################################################################

ifneq ($(CONFIG_BOARD_SIZE_LIMIT),)
BOARD_SIZE_CHECK = \
	@actual=`wc -c $@ | awk '{print $$1}'`; \
	limit=$(CONFIG_BOARD_SIZE_LIMIT); \
	if test $$actual -gt $$limit; then \
		echo "$@ exceeds file size limit:"; \
		echo "  limit:  $$limit bytes"; \
		echo "  actual: $$actual bytes"; \
		echo "  excess: $$((actual - limit)) bytes"; \
		exit 1; \
	fi
else
BOARD_SIZE_CHECK =
endif

# Always append ALL so that arch config.mk's can add custom ones
ALL-y += $(obj)u-boot.srec $(obj)u-boot.bin $(obj)System.map

ALL-$(CONFIG_NAND_U_BOOT) += $(obj)u-boot-nand.bin
ALL-$(CONFIG_ONENAND_U_BOOT) += $(obj)u-boot-onenand.bin
ALL-$(CONFIG_SPL) += $(obj)spl/u-boot-spl.bin
ALL-$(CONFIG_OF_SEPARATE) += $(obj)u-boot.dtb $(obj)u-boot-dtb.bin

# enable combined SPL/u-boot/dtb rules for tegra
ifeq ($(SOC),tegra20)
ifeq ($(CONFIG_OF_SEPARATE),y)
ALL-y += $(obj)u-boot-dtb-tegra.bin
else
ALL-y += $(obj)u-boot-nodtb-tegra.bin
endif
endif

all:		$(ALL-y) $(SUBDIR_EXAMPLES)

$(obj)u-boot.dtb:	$(obj)u-boot
		$(MAKE) -C dts binary
		mv $(obj)dts/dt.dtb $@

$(obj)u-boot-dtb.bin:	$(obj)u-boot.bin $(obj)u-boot.dtb
		cat $^ >$@

$(obj)u-boot.hex:	$(obj)u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@

$(obj)u-boot.srec:	$(obj)u-boot
		$(OBJCOPY) -O srec $< $@

$(obj)u-boot.bin:	$(obj)u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O binary $< $@
		$(BOARD_SIZE_CHECK)

$(obj)u-boot.ldr:	$(obj)u-boot
		$(CREATE_LDR_ENV)
		$(LDR) -T $(CONFIG_BFIN_CPU) -c $@ $< $(LDR_FLAGS)
		$(BOARD_SIZE_CHECK)

$(obj)u-boot.ldr.hex:	$(obj)u-boot.ldr
		$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@ -I binary

$(obj)u-boot.ldr.srec:	$(obj)u-boot.ldr
		$(OBJCOPY) ${OBJCFLAGS} -O srec $< $@ -I binary

$(obj)u-boot.img:	$(obj)u-boot.bin
		$(obj)tools/mkimage -A $(ARCH) -T firmware -C none \
		-O u-boot -a $(CONFIG_SYS_TEXT_BASE) -e 0 \
		-n $(shell sed -n -e 's/.*U_BOOT_VERSION//p' $(VERSION_FILE) | \
			sed -e 's/"[	 ]*$$/ for $(BOARD) board"/') \
		-d $< $@

$(obj)u-boot.imx:       $(obj)u-boot.bin
		$(obj)tools/mkimage -n  $(CONFIG_IMX_CONFIG) -T imximage \
		-e $(CONFIG_SYS_TEXT_BASE) -d $< $@

$(obj)u-boot.kwb:       $(obj)u-boot.bin
		$(obj)tools/mkimage -n $(CONFIG_SYS_KWD_CONFIG) -T kwbimage \
		-a $(CONFIG_SYS_TEXT_BASE) -e $(CONFIG_SYS_TEXT_BASE) -d $< $@

$(obj)u-boot.pbl:	$(obj)u-boot.bin
		$(obj)tools/mkimage -n $(CONFIG_PBLRCW_CONFIG) \
		-R $(CONFIG_PBLPBI_CONFIG) -T pblimage \
		-d $< $@

$(obj)u-boot.sha1:	$(obj)u-boot.bin
		$(obj)tools/ubsha1 $(obj)u-boot.bin

$(obj)u-boot.dis:	$(obj)u-boot
		$(OBJDUMP) -d $< > $@

$(obj)u-boot.ubl:       $(obj)spl/u-boot-spl.bin $(obj)u-boot.bin
		$(OBJCOPY) ${OBJCFLAGS} --pad-to=$(PAD_TO) -O binary $(obj)spl/u-boot-spl $(obj)spl/u-boot-spl-pad.bin
		cat $(obj)spl/u-boot-spl-pad.bin $(obj)u-boot.bin > $(obj)u-boot-ubl.bin
		$(obj)tools/mkimage -n $(UBL_CONFIG) -T ublimage \
		-e $(CONFIG_SYS_TEXT_BASE) -d $(obj)u-boot-ubl.bin $(obj)u-boot.ubl
		rm $(obj)u-boot-ubl.bin
		rm $(obj)spl/u-boot-spl-pad.bin

$(obj)u-boot.ais:       $(obj)spl/u-boot-spl.bin $(obj)u-boot.img
		$(obj)tools/mkimage -s -n $(if $(CONFIG_AIS_CONFIG_FILE),$(CONFIG_AIS_CONFIG_FILE),"/dev/null") \
			-T aisimage \
			-e $(CONFIG_SPL_TEXT_BASE) \
			-d $(obj)spl/u-boot-spl.bin \
			$(obj)spl/u-boot-spl.ais
		$(OBJCOPY) ${OBJCFLAGS} -I binary \
			--pad-to=$(CONFIG_SPL_MAX_SIZE) -O binary \
			$(obj)spl/u-boot-spl.ais $(obj)spl/u-boot-spl-pad.ais
		cat $(obj)spl/u-boot-spl-pad.ais $(obj)u-boot.img > \
			$(obj)u-boot.ais

# Specify the target for use in elftosb call
ELFTOSB_TARGET-$(CONFIG_MX28) = imx28

$(obj)u-boot.sb:       $(obj)u-boot.bin $(obj)spl/u-boot-spl.bin
		elftosb -zdf $(ELFTOSB_TARGET-y) -c $(TOPDIR)/$(CPUDIR)/$(SOC)/u-boot-$(ELFTOSB_TARGET-y).bd \
			-o $(obj)u-boot.sb

# On x600 (SPEAr600) U-Boot is appended to U-Boot SPL.
# Both images are created using mkimage (crc etc), so that the ROM
# bootloader can check its integrity. Padding needs to be done to the
# SPL image (with mkimage header) and not the binary. Otherwise the resulting image
# which is loaded/copied by the ROM bootloader to SRAM doesn't fit.
# The resulting image containing both U-Boot images is called u-boot.spr
$(obj)u-boot.spr:	$(obj)u-boot.img $(obj)spl/u-boot-spl.bin
		$(obj)tools/mkimage -A $(ARCH) -T firmware -C none \
		-a $(CONFIG_SPL_TEXT_BASE) -e $(CONFIG_SPL_TEXT_BASE) -n XLOADER \
		-d $(obj)spl/u-boot-spl.bin $(obj)spl/u-boot-spl.img
		tr "\000" "\377" < /dev/zero | dd ibs=1 count=$(CONFIG_SPL_PAD_TO) \
			of=$(obj)spl/u-boot-spl-pad.img 2>/dev/null
		dd if=$(obj)spl/u-boot-spl.img of=$(obj)spl/u-boot-spl-pad.img \
			conv=notrunc 2>/dev/null
		cat $(obj)spl/u-boot-spl-pad.img $(obj)u-boot.img > $@

ifeq ($(SOC),tegra20)
ifeq ($(CONFIG_OF_SEPARATE),y)
nodtb=dtb
dtbfile=$(obj)u-boot.dtb
else
nodtb=nodtb
dtbfile=
endif

$(obj)u-boot-$(nodtb)-tegra.bin: $(obj)spl/u-boot-spl.bin $(obj)u-boot.bin $(dtbfile)
		$(OBJCOPY) ${OBJCFLAGS} --pad-to=$(CONFIG_SYS_TEXT_BASE) -O binary $(obj)spl/u-boot-spl $(obj)spl/u-boot-spl-pad.bin
		cat $(obj)spl/u-boot-spl-pad.bin $(obj)u-boot.bin $(dtbfile) > $@
		rm $(obj)spl/u-boot-spl-pad.bin
endif

ifeq ($(CONFIG_SANDBOX),y)
GEN_UBOOT = \
		cd $(LNDIR) && $(CC) $(SYMS) -T $(obj)u-boot.lds \
			-Wl,--start-group $(__LIBS) -Wl,--end-group \
			$(PLATFORM_LIBS) -Wl,-Map -Wl,u-boot.map -o u-boot
else
GEN_UBOOT = \
		UNDEF_LST=`$(OBJDUMP) -x $(LIBBOARD) $(LIBS) | \
		sed  -n -e 's/.*\($(SYM_PREFIX)_u_boot_list_.*\)/-u\1/p'|sort|uniq`;\
		cd $(LNDIR) && $(LD) $(LDFLAGS) $(LDFLAGS_$(@F)) \
			$$UNDEF_LST $(__OBJS) \
			--start-group $(__LIBS) --end-group $(PLATFORM_LIBS) \
			-Map u-boot.map -o u-boot
endif

$(obj)u-boot:	depend \
		$(SUBDIR_TOOLS) $(OBJS) $(LIBBOARD) $(LIBS) $(LDSCRIPT) $(obj)u-boot.lds
		$(GEN_UBOOT)
ifeq ($(CONFIG_KALLSYMS),y)
		smap=`$(call SYSTEM_MAP,$(obj)u-boot) | \
			awk '$$2 ~ /[tTwW]/ {printf $$1 $$3 "\\\\000"}'` ; \
		$(CC) $(CFLAGS) -DSYSTEM_MAP="\"$${smap}\"" \
			-c common/system_map.c -o $(obj)common/system_map.o
		$(GEN_UBOOT) $(obj)common/system_map.o
endif

$(OBJS):	depend
		$(MAKE) -C $(CPUDIR) $(if $(REMOTE_BUILD),$@,$(notdir $@))

$(LIBS):	depend $(SUBDIR_TOOLS)
		$(MAKE) -C $(dir $(subst $(obj),,$@))

$(LIBBOARD):	depend $(LIBS)
		$(MAKE) -C $(dir $(subst $(obj),,$@))

$(SUBDIRS):	depend
		$(MAKE) -C $@ all

$(SUBDIR_EXAMPLES): $(obj)u-boot

$(LDSCRIPT):	depend
		$(MAKE) -C $(dir $@) $(notdir $@)

# The following line expands into whole rule which generates u-boot.lst,
# the file containing u-boots LG-array linker section. This is included into
# $(LDSCRIPT). The function make_u_boot_list is defined in helper.mk file.
$(eval $(call make_u_boot_list, $(obj)include/u-boot.lst, $(LIBBOARD) $(LIBS)))
$(obj)u-boot.lds: $(LDSCRIPT) $(obj)include/u-boot.lst
		$(CPP) $(CPPFLAGS) $(LDPPFLAGS) -ansi -D__ASSEMBLY__ -P - <$< >$@

nand_spl:	$(TIMESTAMP_FILE) $(VERSION_FILE) depend
		$(MAKE) -C nand_spl/board/$(BOARDDIR) all

$(obj)u-boot-nand.bin:	nand_spl $(obj)u-boot.bin
		cat $(obj)nand_spl/u-boot-spl-16k.bin $(obj)u-boot.bin > $(obj)u-boot-nand.bin

$(obj)spl/u-boot-spl.bin:	$(SUBDIR_TOOLS) depend
		$(MAKE) -C spl all

updater:
		$(MAKE) -C tools/updater all

# Explicitly make _depend in subdirs containing multiple targets to prevent
# parallel sub-makes creating .depend files simultaneously.
depend dep:	$(TIMESTAMP_FILE) $(VERSION_FILE) \
		$(obj)include/autoconf.mk \
		$(obj)include/generated/generic-asm-offsets.h \
		$(obj)include/generated/asm-offsets.h
		for dir in $(SUBDIRS) $(CPUDIR) $(LDSCRIPT_MAKEFILE_DIR) ; do \
			$(MAKE) -C $$dir _depend ; done

TAG_SUBDIRS = $(SUBDIRS)
TAG_SUBDIRS += $(dir $(__LIBS))
TAG_SUBDIRS += include

FIND := find
FINDFLAGS := -L

checkstack:
		$(CROSS_COMPILE)objdump -d $(obj)u-boot \
			`$(FIND) $(obj) -name u-boot-spl -print` | \
			perl $(src)tools/checkstack.pl $(ARCH)

tags ctags:
		ctags -w -o $(obj)ctags `$(FIND) $(FINDFLAGS) $(TAG_SUBDIRS) \
						-name '*.[chS]' -print`

etags:
		etags -a -o $(obj)etags `$(FIND) $(FINDFLAGS) $(TAG_SUBDIRS) \
						-name '*.[chS]' -print`
cscope:
		$(FIND) $(FINDFLAGS) $(TAG_SUBDIRS) -name '*.[chS]' -print > \
						cscope.files
		cscope -b -q -k

SYSTEM_MAP = \
		$(NM) $1 | \
		grep -v '\(compiled\)\|\(\.o$$\)\|\( [aUw] \)\|\(\.\.ng$$\)\|\(LASH[RL]DI\)' | \
		LC_ALL=C sort
$(obj)System.map:	$(obj)u-boot
		@$(call SYSTEM_MAP,$<) > $(obj)System.map

checkthumb:
	@if test $(call cc-version) -lt 0404; then \
		echo -n '*** Your GCC does not produce working '; \
		echo 'binaries in THUMB mode.'; \
		echo '*** Your board is configured for THUMB mode.'; \
		false; \
	fi
#
# Auto-generate the autoconf.mk file (which is included by all makefiles)
#
# This target actually generates 2 files; autoconf.mk and autoconf.mk.dep.
# the dep file is only include in this top level makefile to determine when
# to regenerate the autoconf.mk file.
$(obj)include/autoconf.mk.dep: $(obj)include/config.h include/common.h
	@$(XECHO) Generating $@ ; \
	set -e ; \
	: Generate the dependancies ; \
	$(CC) -x c -DDO_DEPS_ONLY -M $(CFLAGS) $(CPPFLAGS) \
		-MQ $(obj)include/autoconf.mk include/common.h > $@

$(obj)include/autoconf.mk: $(obj)include/config.h
	@$(XECHO) Generating $@ ; \
	set -e ; \
	: Extract the config macros ; \
	$(CPP) $(CFLAGS) -DDO_DEPS_ONLY -dM include/common.h | \
		sed -n -f tools/scripts/define2mk.sed > $@.tmp && \
	mv $@.tmp $@

$(obj)include/generated/generic-asm-offsets.h:	$(obj)include/autoconf.mk.dep \
	$(obj)lib/asm-offsets.s
	@$(XECHO) Generating $@
	tools/scripts/make-asm-offsets $(obj)lib/asm-offsets.s $@

$(obj)lib/asm-offsets.s:	$(obj)include/autoconf.mk.dep \
	$(src)lib/asm-offsets.c
	@mkdir -p $(obj)lib
	$(CC) -DDO_DEPS_ONLY \
		$(CFLAGS) $(CFLAGS_$(BCURDIR)/$(@F)) $(CFLAGS_$(BCURDIR)) \
		-o $@ $(src)lib/asm-offsets.c -c -S

$(obj)include/generated/asm-offsets.h:	$(obj)include/autoconf.mk.dep \
	$(obj)$(CPUDIR)/$(SOC)/asm-offsets.s
	@$(XECHO) Generating $@
	tools/scripts/make-asm-offsets $(obj)$(CPUDIR)/$(SOC)/asm-offsets.s $@

$(obj)$(CPUDIR)/$(SOC)/asm-offsets.s:	$(obj)include/autoconf.mk.dep
	@mkdir -p $(obj)$(CPUDIR)/$(SOC)
	if [ -f $(src)$(CPUDIR)/$(SOC)/asm-offsets.c ];then \
		$(CC) -DDO_DEPS_ONLY \
		$(CFLAGS) $(CFLAGS_$(BCURDIR)/$(@F)) $(CFLAGS_$(BCURDIR)) \
			-o $@ $(src)$(CPUDIR)/$(SOC)/asm-offsets.c -c -S; \
	else \
		touch $@; \
	fi

#########################################################################
else	# !config.mk
all $(obj)u-boot.hex $(obj)u-boot.srec $(obj)u-boot.bin \
$(obj)u-boot.img $(obj)u-boot.dis $(obj)u-boot \
$(filter-out tools,$(SUBDIRS)) \
updater depend dep tags ctags etags cscope $(obj)System.map:
	@echo "System not configured - see README" >&2
	@ exit 1

tools: $(VERSION_FILE) $(TIMESTAMP_FILE)
	$(MAKE) -C $@ all
endif	# config.mk

$(VERSION_FILE):
		@mkdir -p $(dir $(VERSION_FILE))
		@( localvers='$(shell $(TOPDIR)/tools/setlocalversion $(TOPDIR))' ; \
		   printf '#define PLAIN_VERSION "%s%s"\n' \
			"$(U_BOOT_VERSION)" "$${localvers}" ; \
		   printf '#define U_BOOT_VERSION "U-Boot %s%s"\n' \
			"$(U_BOOT_VERSION)" "$${localvers}" ; \
		) > $@.tmp
		@( printf '#define CC_VERSION_STRING "%s"\n' \
		 '$(shell $(CC) --version | head -n 1)' )>>  $@.tmp
		@( printf '#define LD_VERSION_STRING "%s"\n' \
		 '$(shell $(LD) -v | head -n 1)' )>>  $@.tmp
		@cmp -s $@ $@.tmp && rm -f $@.tmp || mv -f $@.tmp $@

$(TIMESTAMP_FILE):
		@mkdir -p $(dir $(TIMESTAMP_FILE))
		@LC_ALL=C date +'#define U_BOOT_DATE "%b %d %C%y"' > $@.tmp
		@LC_ALL=C date +'#define U_BOOT_TIME "%T"' >> $@.tmp
		@cmp -s $@ $@.tmp && rm -f $@.tmp || mv -f $@.tmp $@

easylogo env gdb:
	$(MAKE) -C tools/$@ all MTD_VERSION=${MTD_VERSION}
gdbtools: gdb

xmldocs pdfdocs psdocs htmldocs mandocs: tools/kernel-doc/docproc
	$(MAKE) U_BOOT_VERSION=$(U_BOOT_VERSION) -C doc/DocBook/ $@

tools-all: easylogo env gdb $(VERSION_FILE) $(TIMESTAMP_FILE)
	$(MAKE) -C tools HOST_TOOLS_ALL=y

.PHONY : CHANGELOG
CHANGELOG:
	git log --no-merges U-Boot-1_1_5.. | \
	unexpand -a | sed -e 's/\s\s*$$//' > $@

include/license.h: tools/bin2header COPYING
	cat COPYING | gzip -9 -c | ./tools/bin2header license_gzip > include/license.h
#########################################################################

unconfig:
	@rm -f $(obj)include/config.h $(obj)include/config.mk \
		$(obj)board/*/config.tmp $(obj)board/*/*/config.tmp \
		$(obj)include/autoconf.mk $(obj)include/autoconf.mk.dep

%_config::	unconfig
	@$(MKCONFIG) -A $(@:_config=)

sinclude $(obj).boards.depend
$(obj).boards.depend:	boards.cfg
	@awk '(NF && $$1 !~ /^#/) { print $$1 ": " $$1 "_config; $$(MAKE)" }' $< > $@

#
# Functions to generate common board directory names
#
lcname	= $(shell echo $(1) | sed -e 's/\(.*\)_config/\L\1/')
ucname	= $(shell echo $(1) | sed -e 's/\(.*\)_config/\U\1/')

#########################################################################
## ARM1176 Systems
#########################################################################
smdk6400_noUSB_config	\
smdk6400_config	:	unconfig
	@mkdir -p $(obj)include $(obj)board/samsung/smdk6400
	@mkdir -p $(obj)nand_spl/board/samsung/smdk6400
	@echo "#define CONFIG_NAND_U_BOOT" > $(obj)include/config.h
	@echo "CONFIG_NAND_U_BOOT = y" >> $(obj)include/config.mk
	@if [ -z "$(findstring smdk6400_noUSB_config,$@)" ]; then			\
		echo "RAM_TEXT = 0x57e00000" >> $(obj)board/samsung/smdk6400/config.tmp;\
	else										\
		echo "RAM_TEXT = 0xc7e00000" >> $(obj)board/samsung/smdk6400/config.tmp;\
	fi
	@$(MKCONFIG) smdk6400 arm arm1176 smdk6400 samsung s3c64xx
	@echo "CONFIG_NAND_U_BOOT = y" >> $(obj)include/config.mk

#########################################################################
#########################################################################

clean:
	@rm -f $(obj)examples/standalone/82559_eeprom			  \
	       $(obj)examples/standalone/atmel_df_pow2			  \
	       $(obj)examples/standalone/eepro100_eeprom		  \
	       $(obj)examples/standalone/hello_world			  \
	       $(obj)examples/standalone/interrupt			  \
	       $(obj)examples/standalone/mem_to_mem_idma2intr		  \
	       $(obj)examples/standalone/sched				  \
	       $(obj)examples/standalone/smc911{11,x}_eeprom		  \
	       $(obj)examples/standalone/test_burst			  \
	       $(obj)examples/standalone/timer
	@rm -f $(obj)examples/api/demo{,.bin}
	@rm -f $(obj)tools/bmp_logo	   $(obj)tools/easylogo/easylogo  \
	       $(obj)tools/env/{fw_printenv,fw_setenv}			  \
	       $(obj)tools/envcrc					  \
	       $(obj)tools/gdb/{astest,gdbcont,gdbsend}			  \
	       $(obj)tools/gen_eth_addr    $(obj)tools/img2srec		  \
	       $(obj)tools/mk{env,}image   $(obj)tools/mpc86x_clk	  \
	       $(obj)tools/mk{smdk5250,}spl				  \
	       $(obj)tools/mxsboot					  \
	       $(obj)tools/ncb		   $(obj)tools/ubsha1		  \
	       $(obj)tools/kernel-doc/docproc
	@rm -f $(obj)board/cray/L1/{bootscript.c,bootscript.image}	  \
	       $(obj)board/matrix_vision/*/bootscript.img		  \
	       $(obj)board/voiceblue/eeprom 				  \
	       $(obj)u-boot.lds						  \
	       $(obj)include/u-boot.lst			  		  \
	       $(obj)arch/blackfin/cpu/bootrom-asm-offsets.[chs]	  \
	       $(obj)arch/blackfin/cpu/init.{lds,elf}
	@rm -f $(obj)include/bmp_logo.h
	@rm -f $(obj)include/bmp_logo_data.h
	@rm -f $(obj)lib/asm-offsets.s
	@rm -f $(obj)include/generated/asm-offsets.h
	@rm -f $(obj)$(CPUDIR)/$(SOC)/asm-offsets.s
	@rm -f $(TIMESTAMP_FILE) $(VERSION_FILE)
	@$(MAKE) -C doc/DocBook/ cleandocs
	@find $(OBJTREE) -type f \
		\( -name 'core' -o -name '*.bak' -o -name '*~' -o -name '*.su' \
		-o -name '*.o'	-o -name '*.a' -o -name '*.exe'	\) -print \
		| xargs rm -f

# Removes everything not needed for testing u-boot
tidy:	clean
	@find $(OBJTREE) -type f \( -name '*.depend*' \) -print | xargs rm -f

clobber:	tidy
	@find $(OBJTREE) -type f \( -name '*.srec' \
		-o -name '*.bin' -o -name u-boot.img \) \
		-print0 | xargs -0 rm -f
	@rm -f $(OBJS) $(obj)*.bak $(obj)ctags $(obj)etags $(obj)TAGS \
		$(obj)cscope.* $(obj)*.*~
	@rm -f $(obj)u-boot $(obj)u-boot.map $(obj)u-boot.hex $(ALL-y)
	@rm -f $(obj)u-boot.kwb
	@rm -f $(obj)u-boot.pbl
	@rm -f $(obj)u-boot.imx
	@rm -f $(obj)u-boot.ubl
	@rm -f $(obj)u-boot.ais
	@rm -f $(obj)u-boot.dtb
	@rm -f $(obj)u-boot.sb
	@rm -f $(obj)u-boot.spr
	@rm -f $(obj)nand_spl/{u-boot.{lds,lst},System.map}
	@rm -f $(obj)nand_spl/{u-boot-nand_spl.lds,u-boot-spl,u-boot-spl.map}
	@rm -f $(obj)spl/{u-boot-spl,u-boot-spl.bin,u-boot-spl.map}
	@rm -f $(obj)spl/{u-boot-spl.lds,u-boot.lst}
	@rm -f $(obj)MLO
	@rm -f $(obj)SPL
	@rm -f $(obj)tools/xway-swap-bytes
	@rm -f $(obj)arch/powerpc/cpu/mpc824x/bedbug_603e.c
	@rm -f $(obj)arch/powerpc/cpu/mpc83xx/ddr-gen?.c
	@rm -fr $(obj)include/asm/proc $(obj)include/asm/arch $(obj)include/asm
	@rm -fr $(obj)include/generated
	@[ ! -d $(obj)nand_spl ] || find $(obj)nand_spl -name "*" -type l -print | xargs rm -f
	@rm -f $(obj)dts/*.tmp
	@rm -f $(obj)spl/u-boot-spl{,-pad}.ais

mrproper \
distclean:	clobber unconfig
ifneq ($(OBJTREE),$(SRCTREE))
	rm -rf $(obj)*
endif

backup:
	F=`basename $(TOPDIR)` ; cd .. ; \
	gtar --force-local -zcvf `LC_ALL=C date "+$$F-%Y-%m-%d-%T.tar.gz"` $$F

#########################################################################
