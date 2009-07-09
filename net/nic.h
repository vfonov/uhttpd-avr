//NIC abstraction code, based on work by Louis Beaudoin 
#ifndef __NIC_H__
#define __NIC_H__

#include "uip.h"
#include "compiler.h"

void nic_init(uint8_t *eth_addr);

void nic_send(void);

uint16_t nic_poll(void);

uint8_t nic_sending(void);

#endif /* __NIC_H__ */
