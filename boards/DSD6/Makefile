BOARD ?= DSD6
MICROPY_TOP ?= $(abspath ../../lib/micropython)

all: firmware

BOARD_DIR = $(abspath .)
BUILD = $(abspath build)

include $(MICROPY_TOP)/py/mkenv.mk
include $(MICROPY_TOP)/py/mkrules.mk

firmware:
	$(Q)$(MAKE) -C $(MICROPY_TOP)/ports/nrf \
		PROJECT_TOP=$(abspath ../..) \
		BOARD=$(BOARD) \
		BOARD_DIR=$(BOARD_DIR) \
		BUILD=$(BUILD)

zip: $(BUILD)/firmware.zip

$(BUILD)/firmware.hex: firmware

$(BUILD)/firmware.zip: $(BUILD)/firmware.hex
	$(Q)adafruit-nrfutil dfu genpkg --dev-type 0x52 --dev-revision 0xadaf --application $(BUILD)/firmware.hex $(BUILD)/firmware.zip

deploy: $(BUILD)/firmware.zip
	$(Q)if ! [ -n "$(NRFUTIL_PORT)" ]; then echo "Serial port not set. Use make NRFUTIL_PORT=/dev/... deploy"; false; fi
	$(Q)adafruit-nrfutil dfu serial -p $(NRFUTIL_PORT) -b 115200 -pkg $(BUILD)/firmware.zip

# mkrules.mk will tell you to "Run 'make submodules'" so it would be nicer if
# this rule were named "submodules", but that would generate a "warning:
# overriding commands for target `submodules'".
port-submodules:
	$(Q)$(MAKE) -C $(MICROPY_TOP)/ports/nrf \
		PROJECT_TOP=$(abspath ../..) \
		BOARD=$(BOARD) \
		BOARD_DIR=$(BOARD_DIR) \
		BUILD=$(BUILD) \
		submodules

.PHONY: firmware zip deploy port-submodules
