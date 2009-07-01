#ifndef __SIMPLE_SERIAL_STREAM_H__
#define __SIMPLE_SERIAL_STREAM_H__

#if !LUFA_SERIAL
/* Includes: */
#include <stdio.h>
#include <stdint.h> 

/* External Variables: */
extern FILE USARTStream;

/* Public Interface - May be used in end-application: */
/* Inline Functions: */
	/** Initializes the serial stream (and regular USART driver) so that both the stream and regular
	 *  USART driver functions can be used. Must be called before any stream or regular USART functions.
	 *
	 *  \param BaudRate     Baud rate to configure the USART to
	 *  \param DoubleSpeed  Enables double speed mode when set, halving the sample time to double the baud rate
	 */
void SerialStream_Init(uint32_t BaudRate, uint8_t DoubleSpeed);

#else //LUFA_SERIAL
#include <LUFA/Drivers/Peripheral/SerialStream.h>
#endif //LUFA_SERIAL
#endif //__SIMPLE_SERIAL_STREAM_H__

