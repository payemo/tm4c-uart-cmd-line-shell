
# EK-TM4C123GXL bare-metal firmware

TARGET   := firmware
BUILD    := build
FIRMWARE := $(BUILD)/$(TARGET).elf

PREFIX   := arm-none-eabi-
CC       := $(PREFIX)gcc
OBJCOPY  := $(PREFIX)objcopy
SIZE     := $(PREFIX)size

SRCS     := $(shell find src -name '*.c')
OBJS     := $(patsubst src/%.c,$(BUILD)/%.o,$(SRCS))
DEPS     := $(OBJS:.o=.d)

CPUFLAGS := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

CFLAGS   := $(CPUFLAGS) -std=c11 -Og -g3 -Wall -Wextra \
            -ffunction-sections -fdata-sections -MMD -MP \
	    -Iinc

LDFLAGS  := $(CPUFLAGS) -T linker.ld -nostdlib \
            -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(TARGET).map

LDLIBS   := -lgcc

.PHONY: all bin size clean flash

all: $(BUILD)/$(TARGET).elf

bin: $(BUILD)/$(TARGET).bin

$(BUILD)/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/$(TARGET).elf: $(OBJS) linker.ld
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@
	$(SIZE) $@

$(BUILD)/$(TARGET).bin: $(BUILD)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $@

size: $(BUILD)/$(TARGET).elf
	$(SIZE) $<

clean:
	rm -rf $(BUILD)

flash: $(FIRMWARE)
	openocd \
		-f board/ti_ek-tm4c123gxl.cfg \
		-c "reset_config none" \
		-c "program $(FIRMWARE) verify reset exit"

-include $(DEPS)
