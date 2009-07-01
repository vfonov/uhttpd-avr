###############################################################################
# Makefile for the project uIP10
###############################################################################

## General Flags
PROJECT = uIP10
MCU = at90usb1287
TARGET = uIP10.elf
CC = avr-gcc

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99        -DBOARD=BOARD_USBKEY               -DF_CLOCK=8000000  -DF_CPU=8000000UL -Os -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=uIP10.map
LDFLAGS += -Wl,-section-start=.text=0x802000


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"c:\vladimir\sg\AVRopendous\Firmware\uIP-1.0_ENC28J60\..\..\libs" 

## Objects that must be built in order to link
OBJECTS = uip_arp.o delay.o enc28j60.o main.o nic.o uip.o timer.o psock.o hello-world.o Serial_Stream.o Serial.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) uIP10.hex uIP10.eep uIP10.lss size

## Compile
uip_arp.o: ../uip_arp.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

delay.o: ../delay.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

enc28j60.o: ../enc28j60.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

nic.o: ../nic.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

uip.o: ../uip.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

psock.o: ../psock.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

hello-world.o: ../hello-world.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Serial_Stream.o: ../../../libs/LUFA/Drivers/AT90USBXXX/Serial_Stream.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Serial.o: ../../../libs/LUFA/Drivers/AT90USBXXX/Serial.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) uIP10.elf dep/* uIP10.hex uIP10.eep uIP10.lss uIP10.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

