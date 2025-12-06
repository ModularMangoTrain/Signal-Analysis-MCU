MCU = atmega644p
F_CPU = 12000000UL
PROGRAMMER = usbasp

TARGET = signal_analysis
SRC_DIR = src
INC_DIR = inc
BUILD_DIR = build

SOURCES = main.c $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(SOURCES)))

CC = avr-gcc
OBJCOPY = avr-objcopy
SIZE = avr-size
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -I$(INC_DIR)
CFLAGS += -Os -Wall -Wextra
CFLAGS += -std=gnu99
CFLAGS += -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -ffunction-sections -fdata-sections
LDFLAGS = -mmcu=$(MCU) -Wl,--gc-sections -Wl,--relax

all: $(BUILD_DIR) $(BUILD_DIR)/$(TARGET).hex size

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/$(TARGET).hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

size: $(BUILD_DIR)/$(TARGET).elf
	$(SIZE) --format=avr --mcu=$(MCU) $<

flash: $(BUILD_DIR)/$(TARGET).hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -U flash:w:$<:i

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean flash size
