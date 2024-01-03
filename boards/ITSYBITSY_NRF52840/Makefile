BOARD ?= ITSYBITSY_NRF52840
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

uf2: $(BUILD)/firmware.uf2

$(BUILD)/firmware.hex: firmware

$(BUILD)/firmware.uf2: $(BUILD)/firmware.hex
	$(Q)$(PYTHON) $(TOP)/tools/uf2conv.py -c -o $(BUILD)/firmware.uf2 -f 0xADA52840 $(BUILD)/firmware.hex

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

.PHONY: firmware uf2 port-submodules
