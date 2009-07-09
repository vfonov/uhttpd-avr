###############################################################################
# Makefile for the project uhttpd-avr
###############################################################################

# MCU name
#MCU = at90usb162
MCU = atmega32u4
#MCU = at90usb647
#MCU = at90usb1287

# Target board (see library "Board Types" documentation, USER or blank for projects not requiring
# LUFA board drivers). If USER is selected, put custom board drivers in a directory called 
# "Board" inside the application directory.
BOARD  = USER

# Processor frequency.
#     This will define a symbol, F_CPU, in all source code files equal to the 
#     processor frequency. You can then use this symbol in your source code to 
#     calculate timings. Do NOT tack on a 'UL' at the end, this will be done
#     automatically to create a 32-bit value in your source code.
#     Typical values are:
#         F_CPU =  1000000
#         F_CPU =  1843200
#         F_CPU =  2000000
#         F_CPU =  3686400
#         F_CPU =  4000000
#         F_CPU =  7372800
#         F_CPU =  8000000
#         F_CPU = 11059200
#         F_CPU = 14745600
#         F_CPU = 16000000
#         F_CPU = 18432000
#         F_CPU = 20000000
F_CPU = 8000000


# Input clock frequency.
#     This will define a symbol, F_CLOCK, in all source code files equal to the 
#     input clock frequency (before any prescaling is performed). This value may
#     differ from F_CPU if prescaling is used on the latter, and is required as the
#     raw input clock is fed directly to the PLL sections of the AVR for high speed
#     clock generation for the USB and other AVR subsections. Do NOT tack on a 'UL'
#     at the end, this will be done automatically to create a 32-bit value in your
#     source code.
#
#     If no clock division is performed on the input clock inside the AVR (via the
#     CPU clock adjust registers or the clock division fuses), this will be equal to F_CPU.
F_CLOCK = 8000000


# path to LUFA installation
LUFA_PATH = ../LUFA_090605


## General Flags
PROJECT = uhttpd-avr
TARGET = $(PROJECT).hex
ELF = $(PROJECT).elf
CC = avr-gcc
DFU = dfu-programmer
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AVRDUDE = avrdude
SIZE = avr-size

MSG_COFF = Converting to AVR COFF:
MSG_EXTENDED_COFF = Converting to AVR Extended COFF:

## optimization flags 
OPTIMIZATION = -Os

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU) -DF_CPU=$(F_CPU)UL -DF_CLOCK=$(F_CLOCK)UL -DBOARD=BOARD_$(BOARD)

## Compiler flags to generate dependency files
GENDEPFLAGS = -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## LUFA configuration

LUFADEFS = -DUSE_NONSTANDARD_DESCRIPTOR_NAMES -DNO_STREAM_CALLBACKS -DUSB_DEVICE_ONLY
LUFADEFS += -DFIXED_CONTROL_ENDPOINT_SIZE=8 -DUSE_SINGLE_DEVICE_CONFIGURATION
LUFADEFS += -DUSE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED | USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"


## Compile options common for all C compilation units.
CFLAGS = $(COMMON) $(GENDEPFLAGS) $(LUFADEFS)
CFLAGS += -Inet -Ijtag -Inet_app -I. -Iserial #-I$(LUFA_PATH)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 $(OPTIMIZATION) -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += $(GENDEPFLAGS)


#---------------- Library Options ----------------
# Minimalistic printf version
PRINTF_LIB_MIN = -Wl,-u,vfprintf -lprintf_min

# Floating point printf version (requires MATH_LIB = -lm below)
PRINTF_LIB_FLOAT = -Wl,-u,vfprintf -lprintf_flt

# If this is left blank, then it will use the Standard printf version.
#PRINTF_LIB = 
PRINTF_LIB = $(PRINTF_LIB_MIN)
#PRINTF_LIB = $(PRINTF_LIB_FLOAT)


# Minimalistic scanf version
SCANF_LIB_MIN = -Wl,-u,vfscanf -lscanf_min

# Floating point + %[ scanf version (requires MATH_LIB = -lm below)
SCANF_LIB_FLOAT = -Wl,-u,vfscanf -lscanf_flt

# If this is left blank, then it will use the Standard scanf version.
#SCANF_LIB = 
SCANF_LIB = $(SCANF_LIB_MIN)
#SCANF_LIB = $(SCANF_LIB_FLOAT)

#MATH_LIB = -lm
MATH_LIB =

#---------------- External Memory Options ----------------

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# used for variables (.data/.bss) and heap (malloc()).
#EXTMEMOPTS = -Wl,-Tdata=0x802100,--defsym=__heap_end=0x80f000

# 64 KB of external RAM, starting after internal RAM (ATmega128!),
# only used for heap (malloc()).
#EXTMEMOPTS = -Wl,--section-start,.data=0x802100,--defsym=__heap_end=0x80f000

EXTMEMOPTS =


## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

#---------------- Assembler Options ----------------
#  -Wa,...:   tell GCC to pass this to the assembler.
#  -adhlns:   create listing
#  -gstabs:   have the assembler create line number information; note that
#             for use in COFF files, additional information about filenames
#             and function names needs to be present in the assembler source
#             files -- see avr-libc docs [FIXME: not yet described there]
#  -listing-cont-lines: Sets the maximum number of continuation lines of hex 
#       dump that will be displayed for a given single line of source input.
#ASMFLAGS = $(ADEFS) -Wa,-adhlns=$(<:%.S=$(OBJDIR)/%.lst),-gstabs,--listing-cont-lines=100

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS += -Wl,-Map=$(PROJECT).map
LDFLAGS += -Wl,--relax 
LDFLAGS += -Wl,--gc-sections
LDFLAGS += $(EXTMEMOPTS)
LDFLAGS += $(PRINTF_LIB) $(SCANF_LIB) $(MATH_LIB)

## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES =  #-I$(LUFA_PATH) 

## Sources network
SRC =   net/uip_arp.c \
			  net/enc28j60.c \
				net/nic.c \
				net/uip.c \
				net/psock.c \
				net/timer.c \
        net/uip-split.c \
        net/uip-empty-packet.c 

## DHCP client
SRC +=  net_app/dhcpc.c 

## sofisticated webserver
SRC +=  webserver/httpd.c \
        webserver/http-strings.c \
        webserver/httpd-fs.c \
        webserver/httpd-cgi.c

SRC +=  serial/SerialStream.c

# LUFA sources
#SRC +=  $(LUFA_PATH)/LUFA/Scheduler/Scheduler.c                     \
#				$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/DevChapter9.c        \
#				$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/Endpoint.c           \
#				$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/LowLevel.c           \
#				$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/Pipe.c               \
#				$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/Events.c            \
#				$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/USBInterrupt.c      \
#				$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/USBTask.c           \
#				$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/ConfigDescriptor.c  \
#				$(LUFA_PATH)/LUFA/Drivers/USB/Class/HIDParser.c
             
#SRC +=  $(LUFA_PATH)/LUFA/Scheduler/Scheduler.c                     \
#				$(LUFA_PATH)/LUFA/Drivers/Peripheral/SerialStream.c         \
#				$(LUFA_PATH)/LUFA/Drivers/Peripheral/Serial.c         

## main function
SRC +=  main.c 

## Objects that must be built in order to link
COBJ      = $(SRC:.c=.o)  
AOBJ      = $(ASRC:.S=.o)

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) $(PROJECT).hex $(PROJECT).eep $(PROJECT).lss size

## Compile
$(COBJ) : %.o : %.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $< -o $@ 

## Compile
$(AOBJ) : %.o : %.S
	$(CC) $(INCLUDES) $(ASMFLAGS) -c  $< -o $@ 


##Link
$(ELF): $(COBJ) $(AOBJ)
	 $(CC) $(LDFLAGS) $(COBJ) $(AOBJ) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(ELF)


dfu: $(TARGET) $(PROJECT).eep  size
	 -$(DFU) $(MCU) erase --debug 5 
	 -$(DFU) $(MCU) flash --debug 5 $(TARGET)
	 -$(DFU) $(MCU) flash-eeprom --debug 5 $(PROJECT).eep --suppress-bootloader-mem
	 -$(DFU) $(MCU) reset

flash: $(TARGET)
	 $(AVRDUDE) -p $(MCU) -P usb -c jtag2 -U flash:w:$(TARGET)


%.hex: $(ELF)
	 $(OBJCOPY)  -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(ELF)
	 $(OBJCOPY)  $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(ELF)
	$(OBJDUMP) -h -S $< > $@


# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(TARGET)
ELFSIZE = $(SIZE) $(MCU_FLAG) $(FORMAT_FLAG) $(ELF)
MCU_FLAG = $(shell $(SIZE) --help | grep -- --mcu > /dev/null && echo --mcu=$(MCU) )
FORMAT_FLAG = $(shell $(SIZE) --help | grep -- --format=.*avr > /dev/null && echo --format=avr )

size: ${ELF}
	@if test -f $(TARGET); then echo; $(ELFSIZE); \
	2>/dev/null; echo; fi


# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT = $(OBJCOPY) --debugging
COFFCONVERT += --change-section-address .data-0x800000
COFFCONVERT += --change-section-address .bss-0x800000
COFFCONVERT += --change-section-address .noinit-0x800000
COFFCONVERT += --change-section-address .eeprom-0x810000

coff: $(elf)
	@echo
	@echo $(MSG_COFF) $(PROJECT).cof
	$(COFFCONVERT) -O coff-avr $< $(PROJECT).cof


extcoff: $(elf)
	@echo
	@echo $(MSG_EXTENDED_COFF) $(PROJECT).cof
	$(COFFCONVERT) -O coff-ext-avr $< $(PROJECT).cof


## Clean target
.PHONY: clean
clean:
	-rm -rf $(COBJ) dep/* $(PROJECT).elf $(PROJECT).hex $(PROJECT).eep $(PROJECT).lss $(PROJECT).map $(PROJECT).cof


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

# web server dependency
webserver/httpd-fs.c: webserver/httpd-fsdata.c
	touch webserver/httpd-fs.c 
