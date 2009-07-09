/************************************************************
*
*	This is the general driver for the ENC28J60
*	I changed some things to make it work with uIP
*	Some files of uIP have changes too.
*
*								edi87 [at] fibertel.com.ar
*								Jonathan Granade
*
************************************************************/
#ifndef ENC28J60_H
#define ENC28J60_H

#ifdef UIP_CONF_BUFFER_SIZE
#define ENC28J60_MAX_FRAMELEN	(UIP_CONF_BUFFER_SIZE+18)	// maximum ethernet frame length
#endif //UIP_CONF_BUFFER_SIZE

// ENC28J60 PINS CONFIGURATION
#define ENC28J60_CONTROL_PORT	PORTB
#define ENC28J60_CONTROL_DDR	DDRB

#define ENC28J60_CONTROL_CS		0

#define ENC28J60_SCK_PIN	  1
#define ENC28J60_MISO_PIN	  3
#define ENC28J60_MOSI_PIN	  2
#define ENC28J60_SS_PIN		  0
#define ENC28J60_RESET_PIN	6
#define ENC28J60_INT_PIN	  7

//#undef  ENC28J60_ENABLE_RESET
//#define  ENC28J60_ENABLE_INT

#define ENC28J60_ERRATA_B7

//! perform software reset
void enc28j60SoftwareReset(void);
//! do a ENC28J60 read operation
u8 enc28j60ReadOp(u8 op, u8 address);
//! do a ENC28J60 write operation
void enc28j60WriteOp(u8 op, u8 address, u8 data);
//! read the packet buffer memory
void enc28j60ReadBuffer(u16 len, u8* data);
//! write the packet buffer memory
void enc28j60WriteBuffer(u16 len, u8* data);
//! set the register bank for register at address
void enc28j60SetBank(u8 address);
//! read ENC28J60 register 8bit
u8 enc28j60Read(u8 address);
//! write ENC28J60 register 8bit
void enc28j60Write(u8 address, u8 data);
//! read ENC28J60 register 8bit
u16 enc28j60Read16(u8 address);
//! write ENC28J60 register 8bit
void enc28j60Write16(u8 address, u16 data);
//! read a PHY register
u16 enc28j60PhyRead(u8 address);
//! write a PHY register
void enc28j60PhyWrite(u8 address, u16 data);

//! initialize the ethernet interface for transmit/receive
void enc28j60Init(uint8_t *eth_addr,u8 DuplexState);

//dummy ?
void enc28j60BeginPacketSend(u16 packetLength);
void enc28j60EndPacketSend(void);
u8   enc28j60PollPacketSending(void);
//

//! Packet transmit function.
/// Sends a packet on the network.  It is assumed that the packet is headed by a valid ethernet header.
/// \param len		Length of packet in bytes.
/// \param packet	Pointer to packet data.
void enc28j60PacketSend(u8* packet, u16 len);
//void enc28j60PacketSend2(unsigned int len1, unsigned char* packet1, unsigned int len2, unsigned char* packet2);

//! Packet receive function.
/// Gets a packet from the network receive buffer, if one is available.
/// The packet will by headed by an ethernet header.
/// \param	maxlen	The maximum acceptable length of a retrieved packet.
/// \param	packet	Pointer where packet data should be stored.
/// \return Packet length in bytes if a packet was retrieved, zero otherwise.
u16 enc28j60BeginPacketReceive(void);
void enc28j60EndPacketReceive(void);
void enc28j60PacketReceive(unsigned char* packet, u16 maxlen);

//! execute procedure for recovering from a receive overflow
/// this should be done when the receive memory fills up with packets
void enc28j60ReceiveOverflowRecover(void);

u8 enc28j60getrev(void);
u8 enc28j60linkup(void);

//! formatted print of important ENC28J60 registers
void enc28j60RegDump(void);

#endif
