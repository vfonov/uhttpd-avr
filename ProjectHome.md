micro HTTPD server based on modified uIP-1.0 stack, running on 8bit AVR processor and ENC28J60

Project is using parts from the following open source projects:
  * [uIP-1.0](http://www.sics.se/~adam/uip) minimalistic TCP/IP stack for embedded projects by Adam Dunkels
  * [uIP version 0.9 port to AVR ATmega32 with ENC28J60](http://www.avrfreaks.net/index.php?module=Freaks%20Academy&func=viewItem&item_type=project&item_id=1408) by Jonathan Granade edi87 at fibertel.com.ar
  * [AVRopendous](http://code.google.com/p/micropendous) hardware to run this project (AVRopendous2-DIP based on Atmel ATmega32U4), donated by [opendous](http://code.google.com/p/opendous/)
  * [Z28J60](http://www.mdfly.com/newmdfly/products/ENC28J60module/Z28J60.pdf) Board from [MdFLY](http://www.mdfly.com/) with Microchip ENC28J60

A similar project, aiming for a more general nic/avr approach is [avr-uip](http://code.google.com/p/avr-uip/)

## Features: ##
  * Webserver have network configuration page, which allows network parameter change without flashing the mCU
  * The whole project fits into ATMega32U4 device, including standard boot loader
  * Simple CGI scripiting with url parameters decoding have been added to the webserver from uIP-1.0
  * uIP-1.0 modified to store data in program memory
  * TCP/IP configuration is stored in EEPROM
  * DHCP client is included in standard configuration

## Compiling ##
  * Setup [Windows or Linux](http://code.google.com/p/micropendous/wiki/QuickStart)
  * run `make`
  * Switch the board into bootloader mode  by pressing and releasing Reset button while holding HW button
  * run `make dfu` or copy  uhttpd-avr.eep to uhttpd-avr\_eep.hex, and then run [Flip](http://www.atmel.com/dyn/products/tools_card.asp?tool_id=3886) first flash the uhttpd-avr.hex into main flash memory, and then uhttpd-avr\_eep.hex into EEPROM memory, click reset.
  * Setup the LAN to use 192.168.0. subnet, and then use your favorite web browser to access http://192.168.0.2 ( NOTE: it is possible to change default network settings by editing uNetConfigure.h file, parameters UIP\_IPADDR  - desired IP adress , UIP\_NETMASK - network mask and UIP\_DRIPADDR - default gateway).

## Memory usage ##

DHCP+uHTTPD+DFU Bootloader compiled using avr-gcc 4.3.2 and avr-libc 1.6.6:
```
AVR Memory Usage
----------------
Device: atmega32u4

Program:   25496 bytes (77.8% Full)
(.text + .data + .bootloader)

Data:       2225 bytes (86.9% Full)
(.data + .bss + .noinit)

EEPROM:       19 bytes (1.9% Full)
(.eeprom)
```

## Project ##

Project on a solderless breadboard, Note: JTAG header and USB-Serial is only needed for debugging:

![http://uhttpd-avr.googlecode.com/svn/trunk/docs/overview.jpeg](http://uhttpd-avr.googlecode.com/svn/trunk/docs/overview.jpeg)

## Screenshots: ##

![http://uhttpd-avr.googlecode.com/svn/trunk/docs/screenshot_01.png](http://uhttpd-avr.googlecode.com/svn/trunk/docs/screenshot_01.png)

Network configuration:

![http://uhttpd-avr.googlecode.com/svn/trunk/docs/screenshot_02.png](http://uhttpd-avr.googlecode.com/svn/trunk/docs/screenshot_02.png)