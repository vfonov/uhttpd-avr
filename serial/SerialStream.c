//this code is slimmed down implementation of serial output, based on the code
//from LUFA library ( by Dean Camera (dean [at] fourwalledcubicle [dot] com) )
//  Vladimir S. Fonov ~ vladimir.fonov <at> gmail.com
#include "uNetConfigure.h"
#include "SerialStream.h"

#include <avr/io.h>

#if DEBUG_SERIAL && !LUFA_SERIAL

/** Macro for calculating the baud value from a given baud rate when the U2X (double speed) bit is
 *  set.
 */

#define SERIAL_UBBRVAL(baud)    (((F_CPU / 16) / baud) - 1)
#define SERIAL_2X_UBBRVAL(baud) (((F_CPU / 8) / baud) - 1)
#define Serial_IsCharReceived() ((UCSR1A & (1 << RXC1)) ? true : false)


int SerialStream_TxByte(char DataByte, FILE *Stream)
{
	if(DataByte=='\n') 
		SerialStream_TxByte('\r',Stream);
	while (!(UCSR1A & (1 << UDRE1)));
	UDR1 = DataByte;

	return 0;
}

static void Serial_Init(uint32_t BaudRate, uint8_t DoubleSpeed)
{
	UCSR1A = (DoubleSpeed ? (1 << U2X1) : 0);
	UCSR1B = ((1 << TXEN1)  | (1 << RXEN1));
	UCSR1C = ((1 << UCSZ11) | (1 << UCSZ10));
	
	DDRD  |= (1 << 3);	
	PORTD |= (1 << 2);
	
	UBRR1  = (DoubleSpeed ? SERIAL_2X_UBBRVAL(BaudRate) : SERIAL_UBBRVAL(BaudRate));
}

void SerialStream_Init(uint32_t BaudRate, uint8_t DoubleSpeed)
{
	Serial_Init(BaudRate, DoubleSpeed);
	
	stdout = &USARTStream;
}

FILE USARTStream = FDEV_SETUP_STREAM(SerialStream_TxByte, NULL, _FDEV_SETUP_WRITE);
#endif //DEBUG_SERIAL
