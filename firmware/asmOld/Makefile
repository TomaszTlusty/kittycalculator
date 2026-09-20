# ---- config ----
MCU    = atmega328p
PART   = m328p
PORT   = /dev/ttyACM1
BAUD   = 115200
TARGET = main

# --------
all: $(TARGET).hex

$(TARGET).elf: $(TARGET).S
	avr-gcc -mmcu=$(MCU) -Os -o $@ $<

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $< $@

flash: $(TARGET).hex
	avrdude -c arduino -p $(PART) -P $(PORT) -b $(BAUD) -U flash:w:$<:i

size: $(TARGET).elf
	avr-size $(TARGET).elf

dump: $(TARGET).elf
	avr-objdump -d $(TARGET).elf

clean:
	rm -f *.elf *.hex
