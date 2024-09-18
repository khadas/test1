
### Variables ###
BASEDIR_TOP := $(BASEDIR_RUN)/..

GEN_BOOT_BLOBS := $(BASEDIR_TOP)/bin/gen-boot-blobs.sh
GEN_DDR_FIP := $(BASEDIR_TOP)/bin/gen-ddr-fip.sh
GEN_DEVICE_FIP := $(BASEDIR_TOP)/bin/gen-device-fip.sh

#
# Rules
#

.PHONY:

boot_blobs:
	#@-mkdir -p output
	env BASEDIR_TOP=$(BASEDIR_TOP) \
	    BASEDIR_RUN=$(BASEDIR_RUN) \
	    BASEDIR_ROOTRSA_X=$(BASEDIR_ROOTRSA_X) \
	    DEVICE_ROOTRSA_INDEX=$(DEVICE_ROOTRSA_INDEX) \
	    BASEDIR_ROOT=$(DEVICE_SCS_KEY_TOP) \
	    PROJECT=$(PROJECT) \
	    DEVICE_VARIANT_SUFFIX=${DEVICE_VARIANT_SUFFIX} \
	    DEVICE_STORAGE_SUFFIX=${DEVICE_STORAGE_SUFFIX} \
		$(GEN_BOOT_BLOBS) $(DEVICE_INPUT_PATH) $(DEVICE_OUTPUT_PATH)

ddr_fip:
	#@-mkdir -p output
	env BASEDIR_TOP=$(BASEDIR_TOP) \
	    BASEDIR_RUN=$(BASEDIR_RUN) \
	    BASEDIR_ROOTRSA_X=$(BASEDIR_ROOTRSA_X) \
	    DEVICE_ROOTRSA_INDEX=$(DEVICE_ROOTRSA_INDEX) \
	    BASEDIR_ROOT=$(DEVICE_SCS_KEY_TOP) \
	    PROJECT=$(PROJECT) \
	    DEVICE_VARIANT_SUFFIX=${DEVICE_VARIANT_SUFFIX} \
	    DEVICE_STORAGE_SUFFIX=${DEVICE_STORAGE_SUFFIX} \
		$(GEN_DDR_FIP) $(DEVICE_INPUT_PATH) $(DEVICE_OUTPUT_PATH)

device_fip:
	#@-mkdir -p output
	env BASEDIR_TOP=$(BASEDIR_TOP) \
	    BASEDIR_RUN=$(BASEDIR_RUN) \
	    BASEDIR_ROOTRSA_X=$(BASEDIR_ROOTRSA_X) \
	    DEVICE_ROOTRSA_INDEX=$(DEVICE_ROOTRSA_INDEX) \
	    BASEDIR_ROOT=$(DEVICE_SCS_KEY_TOP) \
	    PROJECT=$(PROJECT) \
		$(GEN_DEVICE_FIP) $(DEVICE_INPUT_PATH) $(DEVICE_INPUT_PATH) $(DEVICE_OUTPUT_PATH)

clean:
	@-rm -fr output
