#
# (C) Copyright 2000-2013
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

VERSION = 2014
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

export	HOSTARCH HOSTOS

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
# U-boot build supports generating object files in a separate external
# directory. Two use cases are supported:
#
# 1) Add O= to the make command line
# 'make O=/tmp/build all'
#
# 2) Set environment variable BUILD_DIR to point to the desired location
# 'export BUILD_DIR=/tmp/build'
# 'make'
#
# The second approach can also be used with a MAKEALL script
# 'export BUILD_DIR=/tmp/build'
# './MAKEALL'
#
# Command line 'O=' setting overrides BUILD_DIR environment variable.
#
# When none of the above methods is used the local build is performed and
# the object files are placed in the source directory.
#

ifeq ("$(origin O)", "command line")
BUILD_DIR := $(O)
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
TPLTREE		:= $(OBJTREE)/tpl
SRCTREE		:= $(CURDIR)
TOPDIR		:= $(SRCTREE)
LNDIR		:= $(OBJTREE)
export	TOPDIR SRCTREE OBJTREE SPLTREE TPLTREE

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
SUBDIRS = $(SUBDIR_TOOLS)

.PHONY : $(SUBDIRS) $(VERSION_FILE) $(TIMESTAMP_FILE)

ifeq ($(obj)include/config.mk,$(wildcard $(obj)include/config.mk))

# Include autoconf.mk before config.mk so that the config options are available
# to all top level build files.  We need the dummy all: target to prevent the
# dependency target in autoconf.mk.dep from being the default.
all:
sinclude $(obj)include/autoconf.mk.dep
sinclude $(obj)include/autoconf.mk

SUBDIR_EXAMPLES-y := examples/standalone
SUBDIR_EXAMPLES-$(CONFIG_API) += examples/api
ifndef CONFIG_SANDBOX
SUBDIRS += $(SUBDIR_EXAMPLES-y)
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

# Targets which don't build the source code
NON_BUILD_TARGETS = backup clean clobber distclean mkproper tidy unconfig

# Only do the generic board check when actually building, not configuring
ifeq ($(filter $(NON_BUILD_TARGETS),$(MAKECMDGOALS)),)
ifeq ($(findstring _config,$(MAKECMDGOALS)),)
$(CHECK_GENERIC_BOARD)
endif
endif

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
ifeq ($(CPU),ppc4xx)
OBJS += $(CPUDIR)/resetvec.o
endif
ifeq ($(CPU),mpc85xx)
OBJS += $(CPUDIR)/resetvec.o
endif

OBJS := $(addprefix $(obj),$(OBJS))

HAVE_VENDOR_COMMON_LIB = $(if $(wildcard board/$(VENDOR)/common/Makefile),y,n)

LIBS-y += lib/
LIBS-$(HAVE_VENDOR_COMMON_LIB) += board/$(VENDOR)/common/
LIBS-y += $(CPUDIR)/
ifdef SOC
LIBS-y += $(CPUDIR)/$(SOC)/
endif
LIBS-$(CONFIG_IXP4XX_NPE) += drivers/net/npe/
LIBS-$(CONFIG_OF_EMBED) += dts/
LIBS-y += arch/$(ARCH)/lib/
LIBS-y += fs/
LIBS-y += net/
LIBS-y += disk/
LIBS-y += drivers/
LIBS-y += drivers/dma/
LIBS-y += drivers/gpio/
LIBS-y += drivers/i2c/
LIBS-y += drivers/input/
LIBS-y += drivers/mmc/
LIBS-y += drivers/mtd/
LIBS-y += drivers/mtd/nand/
LIBS-y += drivers/mtd/onenand/
LIBS-y += drivers/mtd/ubi/
LIBS-y += drivers/mtd/spi/
LIBS-y += drivers/net/
LIBS-y += drivers/net/phy/
LIBS-y += drivers/pci/
LIBS-y += drivers/power/ \
	drivers/power/fuel_gauge/ \
	drivers/power/mfd/ \
	drivers/power/pmic/ \
	drivers/power/battery/
LIBS-y += drivers/spi/
LIBS-$(CONFIG_FMAN_ENET) += drivers/net/fm/
LIBS-$(CONFIG_SYS_FSL_DDR) += drivers/ddr/fsl/
LIBS-y += drivers/serial/
LIBS-y += drivers/usb/eth/
LIBS-y += drivers/usb/gadget/
LIBS-y += drivers/usb/host/
LIBS-y += drivers/usb/musb/
LIBS-y += drivers/usb/musb-new/
LIBS-y += drivers/usb/phy/
LIBS-y += drivers/usb/ulpi/
LIBS-y += common/
LIBS-y += lib/libfdt/
LIBS-$(CONFIG_API) += api/
LIBS-y += post/
LIBS-y += test/

ifneq (,$(filter $(SOC), mx25 mx27 mx5 mx6 mx31 mx35 mxs vf610))
LIBS-y += arch/$(ARCH)/imx-common/
endif

LIBS-$(CONFIG_ARM) += arch/arm/cpu/
LIBS-$(CONFIG_PPC) += arch/powerpc/cpu/

LIBS-y += board/$(BOARDDIR)/

LIBS-y := $(patsubst %/, %/built-in.o, $(LIBS-y))
LIBS := $(addprefix $(obj),$(sort $(LIBS-y)))
.PHONY : $(LIBS)

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
__LIBS := $(subst $(obj),,$(LIBS))

#########################################################################
#########################################################################

ifneq ($(CONFIG_BOARD_SIZE_LIMIT),)
BOARD_SIZE_CHECK = \
	@actual=`wc -c $@ | awk '{print $$1}'`; \
	limit=`printf "%d" $(CONFIG_BOARD_SIZE_LIMIT)`; \
	if test $$actual -gt $$limit; then \
		echo "$@ exceeds file size limit:" >&2 ; \
		echo "  limit:  $$limit bytes" >&2 ; \
		echo "  actual: $$actual bytes" >&2 ; \
		echo "  excess: $$((actual - limit)) bytes" >&2; \
		exit 1; \
	fi
else
BOARD_SIZE_CHECK =
endif

# Statically apply RELA-style relocations (currently arm64 only)
ifneq ($(CONFIG_STATIC_RELA),)
# $(1) is u-boot ELF, $(2) is u-boot bin, $(3) is text base
DO_STATIC_RELA = \
	start=$$($(NM) $(1) | grep __rel_dyn_start | cut -f 1 -d ' '); \
	end=$$($(NM) $(1) | grep __rel_dyn_end | cut -f 1 -d ' '); \
	$(obj)tools/relocate-rela $(2) $(3) $$start $$end
else
DO_STATIC_RELA =
endif

# Always append ALL so that arch config.mk's can add custom ones
ALL-y += $(obj)u-boot.srec $(obj)u-boot.bin $(obj)System.map

ALL-$(CONFIG_NAND_U_BOOT) += $(obj)u-boot-nand.bin
ALL-$(CONFIG_ONENAND_U_BOOT) += $(obj)u-boot-onenand.bin
ALL-$(CONFIG_RAMBOOT_PBL) += $(obj)u-boot.pbl
ALL-$(CONFIG_SPL) += $(obj)spl/u-boot-spl.bin
ALL-$(CONFIG_SPL_FRAMEWORK) += $(obj)u-boot.img
ALL-$(CONFIG_TPL) += $(obj)tpl/u-boot-tpl.bin
ALL-$(CONFIG_OF_SEPARATE) += $(obj)u-boot.dtb $(obj)u-boot-dtb.bin
ifneq ($(CONFIG_SPL_TARGET),)
ALL-$(CONFIG_SPL) += $(obj)$(subst ",,$(CONFIG_SPL_TARGET))
endif
ALL-$(CONFIG_REMAKE_ELF) += $(obj)u-boot.elf

# enable combined SPL/u-boot/dtb rules for tegra
ifneq ($(CONFIG_TEGRA),)
ifeq ($(CONFIG_SPL),y)
ifeq ($(CONFIG_OF_SEPARATE),y)
ALL-y += $(obj)u-boot-dtb-tegra.bin
else
ALL-y += $(obj)u-boot-nodtb-tegra.bin
endif
endif
endif

build := -f $(TOPDIR)/scripts/Makefile.build -C

all:		$(ALL-y) $(SUBDIR_EXAMPLES-y)

$(obj)u-boot.dtb:	checkdtc $(obj)u-boot
		$(MAKE) $(build) dts binary
		mv $(obj)dts/dt.dtb $@

$(obj)u-boot-dtb.bin:	$(obj)u-boot.bin $(obj)u-boot.dtb
		cat $^ >$@

$(obj)u-boot.hex:	$(obj)u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@

$(obj)u-boot.srec:	$(obj)u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O srec $< $@

$(obj)u-boot.bin:	$(obj)u-boot
		$(OBJCOPY) ${OBJCFLAGS} -O binary $< $@
		$(call DO_STATIC_RELA,$<,$@,$(CONFIG_SYS_TEXT_BASE))
		$(BOARD_SIZE_CHECK)

$(obj)u-boot.ldr:	$(obj)u-boot
		$(CREATE_LDR_ENV)
		$(LDR) -T $(CONFIG_BFIN_CPU) -c $@ $< $(LDR_FLAGS)
		$(BOARD_SIZE_CHECK)

$(obj)u-boot.ldr.hex:	$(obj)u-boot.ldr
		$(OBJCOPY) ${OBJCFLAGS} -O ihex $< $@ -I binary

$(obj)u-boot.ldr.srec:	$(obj)u-boot.ldr
		$(OBJCOPY) ${OBJCFLAGS} -O srec $< $@ -I binary

#
# U-Boot entry point, needed for booting of full-blown U-Boot
# from the SPL U-Boot version.
#
ifndef CONFIG_SYS_UBOOT_START
CONFIG_SYS_UBOOT_START := 0
endif

$(obj)u-boot.img:	$(obj)u-boot.bin
		$(obj)tools/mkimage -A $(ARCH) -T firmware -C none \
		-O u-boot -a $(CONFIG_SYS_TEXT_BASE) \
		-e $(CONFIG_SYS_UBOOT_START) \
		-n $(shell sed -n -e 's/.*U_BOOT_VERSION//p' $(VERSION_FILE) | \
			sed -e 's/"[	 ]*$$/ for $(BOARD) board"/') \
		-d $< $@

$(obj)u-boot.imx: $(obj)u-boot.bin depend
		$(MAKE) $(build) $(SRCTREE)/arch/arm/imx-common $(OBJTREE)/u-boot.imx

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

# $@ is output, $(1) and $(2) are inputs, $(3) is padded intermediate,
# $(4) is pad-to
SPL_PAD_APPEND = \
		$(OBJCOPY) ${OBJCFLAGS} --pad-to=$(4) -I binary -O binary \
		$(1) $(obj)$(3); \
		cat $(obj)$(3) $(2) > $@; \
		rm $(obj)$(3)

ifdef CONFIG_TPL
SPL_PAYLOAD := $(obj)tpl/u-boot-with-tpl.bin
else
SPL_PAYLOAD := $(obj)u-boot.bin
endif

$(obj)u-boot-with-spl.bin: $(obj)spl/u-boot-spl.bin $(SPL_PAYLOAD)
		$(call SPL_PAD_APPEND,$<,$(SPL_PAYLOAD),spl/u-boot-spl-pad.bin,$(CONFIG_SPL_PAD_TO))

$(obj)tpl/u-boot-with-tpl.bin: $(obj)tpl/u-boot-tpl.bin $(obj)u-boot.bin
		$(call SPL_PAD_APPEND,$<,$(obj)u-boot.bin,tpl/u-boot-tpl-pad.bin,$(CONFIG_TPL_PAD_TO))

$(obj)u-boot-with-spl.imx: $(obj)spl/u-boot-spl.bin $(obj)u-boot.bin
		$(MAKE) $(build) $(SRCTREE)/arch/arm/imx-common \
			$(OBJTREE)/u-boot-with-spl.imx

$(obj)u-boot-with-nand-spl.imx: $(obj)spl/u-boot-spl.bin $(obj)u-boot.bin
		$(MAKE) $(build) $(SRCTREE)/arch/arm/imx-common \
			$(OBJTREE)/u-boot-with-nand-spl.imx

$(obj)u-boot.ubl:       $(obj)u-boot-with-spl.bin
		$(obj)tools/mkimage -n $(UBL_CONFIG) -T ublimage \
		-e $(CONFIG_SYS_TEXT_BASE) -d $< $(obj)u-boot.ubl

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


$(obj)u-boot.sb:       $(obj)u-boot.bin $(obj)spl/u-boot-spl.bin
		$(MAKE) $(build) $(SRCTREE)/$(CPUDIR)/$(SOC)/ $(OBJTREE)/u-boot.sb

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

ifneq ($(CONFIG_TEGRA),)
$(obj)u-boot-nodtb-tegra.bin: $(obj)spl/u-boot-spl.bin $(obj)u-boot.bin
		$(OBJCOPY) ${OBJCFLAGS} --pad-to=$(CONFIG_SYS_TEXT_BASE) -O binary $(obj)spl/u-boot-spl $(obj)spl/u-boot-spl-pad.bin
		cat $(obj)spl/u-boot-spl-pad.bin $(obj)u-boot.bin > $@
		rm $(obj)spl/u-boot-spl-pad.bin

ifeq ($(CONFIG_OF_SEPARATE),y)
$(obj)u-boot-dtb-tegra.bin: $(obj)u-boot-nodtb-tegra.bin $(obj)u-boot.dtb
		cat $(obj)u-boot-nodtb-tegra.bin $(obj)u-boot.dtb > $@
endif
endif

$(obj)u-boot-img.bin: $(obj)spl/u-boot-spl.bin $(obj)u-boot.img
		cat $(obj)spl/u-boot-spl.bin $(obj)u-boot.img > $@

# PPC4xx needs the SPL at the end of the image, since the reset vector
# is located at 0xfffffffc. So we can't use the "u-boot-img.bin" target
# and need to introduce a new build target with the full blown U-Boot
# at the start padded up to the start of the SPL image. And then concat
# the SPL image to the end.
$(obj)u-boot-img-spl-at-end.bin: $(obj)spl/u-boot-spl.bin $(obj)u-boot.img
		tr "\000" "\377" < /dev/zero | dd ibs=1 count=$(CONFIG_UBOOT_PAD_TO) \
			of=$(obj)u-boot-pad.img 2>/dev/null
		dd if=$(obj)u-boot.img of=$(obj)u-boot-pad.img \
			conv=notrunc 2>/dev/null
		cat $(obj)u-boot-pad.img $(obj)spl/u-boot-spl.bin > $@

# Create a new ELF from a raw binary file.  This is useful for arm64
# where static relocation needs to be performed on the raw binary,
# but certain simulators only accept an ELF file (but don't do the
# relocation).
# FIXME refactor dts/Makefile to share target/arch detection
$(obj)u-boot.elf: $(obj)u-boot.bin
	@$(OBJCOPY)  -B aarch64 -I binary -O elf64-littleaarch64 \
		$< $(obj)u-boot-elf.o
	@$(LD) $(obj)u-boot-elf.o -o $@ \
		--defsym=_start=$(CONFIG_SYS_TEXT_BASE) \
		-Ttext=$(CONFIG_SYS_TEXT_BASE)

ifeq ($(CONFIG_SANDBOX),y)
GEN_UBOOT = \
		cd $(LNDIR) && $(CC) $(SYMS) -T $(obj)u-boot.lds \
			-Wl,--start-group $(__LIBS) -Wl,--end-group \
			$(PLATFORM_LIBS) -Wl,-Map -Wl,u-boot.map -o u-boot
else
GEN_UBOOT = \
		cd $(LNDIR) && $(LD) $(LDFLAGS) $(LDFLAGS_$(@F)) \
			$(__OBJS) \
			--start-group $(__LIBS) --end-group $(PLATFORM_LIBS) \
			-Map u-boot.map -o u-boot
endif

$(obj)u-boot:	depend \
		$(SUBDIR_TOOLS) $(OBJS) $(LIBS) $(LDSCRIPT) $(obj)u-boot.lds
		$(GEN_UBOOT)
ifeq ($(CONFIG_KALLSYMS),y)
		smap=`$(call SYSTEM_MAP,$(obj)u-boot) | \
			awk '$$2 ~ /[tTwW]/ {printf $$1 $$3 "\\\\000"}'` ; \
		$(CC) $(CFLAGS) -DSYSTEM_MAP="\"$${smap}\"" \
			-c common/system_map.c -o $(obj)common/system_map.o
		$(GEN_UBOOT) $(obj)common/system_map.o
endif

$(OBJS):
	@:

$(LIBS):	depend $(SUBDIR_TOOLS)
		$(MAKE) $(build) $(dir $(subst $(obj),,$@))

$(SUBDIRS):	depend
		$(MAKE) -C $@ all

$(SUBDIR_EXAMPLES-y): $(obj)u-boot

$(LDSCRIPT):	depend
		$(MAKE) -C $(dir $@) $(notdir $@)

$(obj)u-boot.lds: $(LDSCRIPT)
		$(CPP) $(CPPFLAGS) $(LDPPFLAGS) -ansi -D__ASSEMBLY__ -P - <$< >$@

nand_spl:	$(TIMESTAMP_FILE) $(VERSION_FILE) depend
		$(MAKE) -C nand_spl/board/$(BOARDDIR) all

$(obj)u-boot-nand.bin:	nand_spl $(obj)u-boot.bin
		cat $(obj)nand_spl/u-boot-spl-16k.bin $(obj)u-boot.bin > $(obj)u-boot-nand.bin

$(obj)spl/u-boot-spl.bin:	$(SUBDIR_TOOLS) depend
		$(MAKE) -C spl all

$(obj)tpl/u-boot-tpl.bin:	$(SUBDIR_TOOLS) depend
		$(MAKE) -C spl all CONFIG_TPL_BUILD=y

# Explicitly make _depend in subdirs containing multiple targets to prevent
# parallel sub-makes creating .depend files simultaneously.
depend dep:	$(TIMESTAMP_FILE) $(VERSION_FILE) \
		$(obj)include/spl-autoconf.mk \
		$(obj)include/tpl-autoconf.mk \
		$(obj)include/autoconf.mk \
		$(obj)include/generated/generic-asm-offsets.h \
		$(obj)include/generated/asm-offsets.h

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
		@$(call SYSTEM_MAP,$<) > $@

checkthumb:
	@if test $(call cc-version) -lt 0404; then \
		echo -n '*** Your GCC does not produce working '; \
		echo 'binaries in THUMB mode.'; \
		echo '*** Your board is configured for THUMB mode.'; \
		false; \
	fi

# GCC 3.x is reported to have problems generating the type of relocation
# that U-Boot wants.
# See http://lists.denx.de/pipermail/u-boot/2012-September/135156.html
checkgcc4:
	@if test $(call cc-version) -lt 0400; then \
		echo -n '*** Your GCC is too old, please upgrade to GCC 4.x or newer'; \
		false; \
	fi

checkdtc:
	@if test $(call dtc-version) -lt 0104; then \
		echo '*** Your dtc is too old, please upgrade to dtc 1.4 or newer'; \
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

# Auto-generate the spl-autoconf.mk file (which is included by all makefiles for SPL)
$(obj)include/tpl-autoconf.mk: $(obj)include/config.h
	@$(XECHO) Generating $@ ; \
	set -e ; \
	: Extract the config macros ; \
	$(CPP) $(CFLAGS) -DCONFIG_TPL_BUILD  -DCONFIG_SPL_BUILD\
			-DDO_DEPS_ONLY -dM include/common.h | \
	sed -n -f tools/scripts/define2mk.sed > $@.tmp && \
	mv $@.tmp $@

$(obj)include/spl-autoconf.mk: $(obj)include/config.h
	@$(XECHO) Generating $@ ; \
	set -e ; \
	: Extract the config macros ; \
	$(CPP) $(CFLAGS) -DCONFIG_SPL_BUILD -DDO_DEPS_ONLY -dM include/common.h | \
	sed -n -f tools/scripts/define2mk.sed > $@.tmp && \
	mv $@.tmp $@

$(obj)include/generated/generic-asm-offsets.h:	$(obj)include/autoconf.mk.dep \
	$(obj)include/spl-autoconf.mk \
	$(obj)include/tpl-autoconf.mk \
	$(obj)lib/asm-offsets.s
	@$(XECHO) Generating $@
	tools/scripts/make-asm-offsets $(obj)lib/asm-offsets.s $@

$(obj)lib/asm-offsets.s:	$(obj)include/autoconf.mk.dep \
	$(obj)include/spl-autoconf.mk \
	$(obj)include/tpl-autoconf.mk \
	$(src)lib/asm-offsets.c
	@mkdir -p $(obj)lib
	$(CC) -DDO_DEPS_ONLY \
		$(CFLAGS) $(CFLAGS_$(BCURDIR)/$(@F)) $(CFLAGS_$(BCURDIR)) \
		-o $@ $(src)lib/asm-offsets.c -c -S

$(obj)include/generated/asm-offsets.h:	$(obj)include/autoconf.mk.dep \
	$(obj)include/spl-autoconf.mk \
	$(obj)include/tpl-autoconf.mk \
	$(obj)$(CPUDIR)/$(SOC)/asm-offsets.s
	@$(XECHO) Generating $@
	tools/scripts/make-asm-offsets $(obj)$(CPUDIR)/$(SOC)/asm-offsets.s $@

$(obj)$(CPUDIR)/$(SOC)/asm-offsets.s:	$(obj)include/autoconf.mk.dep \
	$(obj)include/spl-autoconf.mk \
	$(obj)include/tpl-autoconf.mk
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
depend dep tags ctags etags cscope $(obj)System.map:
	@echo "System not configured - see README" >&2
	@ exit 1

tools: $(VERSION_FILE) $(TIMESTAMP_FILE)
	$(MAKE) -C $@ all
endif	# config.mk

# ARM relocations should all be R_ARM_RELATIVE.
checkarmreloc: $(obj)u-boot
	@if test "R_ARM_RELATIVE" != \
		"`$(CROSS_COMPILE)readelf -r $< | cut -d ' ' -f 4 | grep R_ARM | sort -u`"; \
		then echo "$< contains relocations other than \
		R_ARM_RELATIVE"; false; fi

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
		$(obj)include/autoconf.mk $(obj)include/autoconf.mk.dep \
		$(obj)include/spl-autoconf.mk \
		$(obj)include/tpl-autoconf.mk

%_config::	unconfig
	@$(MKCONFIG) -A $(@:_config=)

sinclude $(obj).boards.depend
$(obj).boards.depend:	boards.cfg
	@awk '(NF && $$1 !~ /^#/) { print $$7 ": " $$7 "_config; $$(MAKE)" }' $< > $@

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
	       $(obj)tools/mk{$(BOARD),}spl				  \
	       $(obj)tools/mxsboot					  \
	       $(obj)tools/ncb		   $(obj)tools/ubsha1		  \
	       $(obj)tools/kernel-doc/docproc				  \
	       $(obj)tools/proftool
	@rm -f $(obj)board/cray/L1/{bootscript.c,bootscript.image}	  \
	       $(obj)board/matrix_vision/*/bootscript.img		  \
	       $(obj)board/voiceblue/eeprom 				  \
	       $(obj)u-boot.lds						  \
	       $(obj)arch/blackfin/cpu/init.{lds,elf}
	@rm -f $(obj)include/bmp_logo.h
	@rm -f $(obj)include/bmp_logo_data.h
	@rm -f $(obj)lib/asm-offsets.s
	@rm -f $(obj)include/generated/asm-offsets.h
	@rm -f $(obj)$(CPUDIR)/$(SOC)/asm-offsets.s
	@rm -f $(TIMESTAMP_FILE) $(VERSION_FILE)
	@$(MAKE) -s -C doc/DocBook/ cleandocs
	@find $(OBJTREE) -type f \
		\( -name 'core' -o -name '*.bak' -o -name '*~' -o -name '*.su' \
		-o -name '*.o'	-o -name '*.a' -o -name '*.exe' \
		-o -name '*.cfgtmp' \) -print \
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
	@rm -f $(obj)u-boot-with-spl.imx
	@rm -f $(obj)u-boot-with-nand-spl.imx
	@rm -f $(obj)u-boot.ubl
	@rm -f $(obj)u-boot.ais
	@rm -f $(obj)u-boot.dtb
	@rm -f $(obj)u-boot.sb
	@rm -f $(obj)u-boot.bd
	@rm -f $(obj)u-boot.spr
	@rm -f $(obj)nand_spl/{u-boot.{lds,lst},System.map}
	@rm -f $(obj)nand_spl/{u-boot-nand_spl.lds,u-boot-spl,u-boot-spl.map}
	@rm -f $(obj)spl/{u-boot-spl,u-boot-spl.bin,u-boot-spl.map}
	@rm -f $(obj)spl/u-boot-spl.lds
	@rm -f $(obj)tpl/{u-boot-tpl,u-boot-tpl.bin,u-boot-tpl.map}
	@rm -f $(obj)tpl/u-boot-spl.lds
	@rm -f $(obj)MLO MLO.byteswap
	@rm -f $(obj)SPL
	@rm -f $(obj)tools/xway-swap-bytes
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
