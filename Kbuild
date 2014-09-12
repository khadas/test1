#
# Kbuild for top-level directory of U-Boot
# This file takes care of the following:
# 1) Generate generic-asm-offsets.h
# 2) Generate asm-offsets.h

#####
# 1) Generate generic-asm-offsets.h

generic-offsets-file := include/generated/generic-asm-offsets.h

always  := $(generic-offsets-file)
targets := $(generic-offsets-file) lib/asm-offsets.s

quiet_cmd_generic-offsets = GEN     $@
define cmd_generic-offsets
	(set -e; \
	 echo "#ifndef __GENERIC_ASM_OFFSETS_H__"; \
	 echo "#define __GENERIC_ASM_OFFSETS_H__"; \
	 echo "/*"; \
	 echo " * DO NOT MODIFY."; \
	 echo " *"; \
	 echo " * This file was generated by Kbuild"; \
	 echo " *"; \
	 echo " */"; \
	 echo ""; \
	 sed -ne $(sed-y) $<; \
	 echo ""; \
	 echo "#endif" ) > $@
endef

# We use internal kbuild rules to avoid the "is up to date" message from make
lib/asm-offsets.s: lib/asm-offsets.c FORCE
	$(Q)mkdir -p $(dir $@)
	$(call if_changed_dep,cc_s_c)

$(obj)/$(generic-offsets-file): lib/asm-offsets.s Kbuild
	$(Q)mkdir -p $(dir $@)
	$(call cmd,generic-offsets)

#####
# 2) Generate asm-offsets.h
#

ifneq ($(wildcard $(srctree)/arch/$(ARCH)/lib/asm-offsets.c),)
offsets-file := include/generated/asm-offsets.h
endif

always  += $(offsets-file)
targets += $(offsets-file)
targets += arch/$(ARCH)/lib/asm-offsets.s


# Default sed regexp - multiline due to syntax constraints
define sed-y
	"s:[[:space:]]*\.ascii[[:space:]]*\"\(.*\)\":\1:; \
	/^->/{s:->#\(.*\):/* \1 */:; \
	s:^->\([^ ]*\) [\$$#]*\([-0-9]*\) \(.*\):#define \1 \2 /* \3 */:; \
	s:^->\([^ ]*\) [\$$#]*\([^ ]*\) \(.*\):#define \1 \2 /* \3 */:; \
	s:->::; p;}"
endef

CFLAGS_asm-offsets.o := -DDO_DEPS_ONLY

quiet_cmd_offsets = GEN     $@
define cmd_offsets
	(set -e; \
	 echo "#ifndef __ASM_OFFSETS_H__"; \
	 echo "#define __ASM_OFFSETS_H__"; \
	 echo "/*"; \
	 echo " * DO NOT MODIFY."; \
	 echo " *"; \
	 echo " * This file was generated by Kbuild"; \
	 echo " *"; \
	 echo " */"; \
	 echo ""; \
	 sed -ne $(sed-y) $<; \
	 echo ""; \
	 echo "#endif" ) > $@
endef

# We use internal kbuild rules to avoid the "is up to date" message from make
arch/$(ARCH)/lib/asm-offsets.s: arch/$(ARCH)/lib/asm-offsets.c FORCE
	$(Q)mkdir -p $(dir $@)
	$(call if_changed_dep,cc_s_c)

$(obj)/$(offsets-file): arch/$(ARCH)/lib/asm-offsets.s Kbuild
	$(call cmd,offsets)
