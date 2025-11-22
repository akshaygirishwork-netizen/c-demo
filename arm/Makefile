# Makefile for LPC2129 LED Blink
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=arm7tdmi -marm -O2 -Wall -ffreestanding -nostartfiles

# Source files
SRCS = main.c startup.s
TARGET = blink

all: $(TARGET).hex

$(TARGET).elf: $(SRCS) linker_script.ld
	$(CC) $(CFLAGS) -T linker_script.ld -o $@ $(SRCS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex $< $@

clean:
	rm -f *.elf *.hex

