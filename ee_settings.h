#ifndef __EE_SETTINGS_H__
#define __EE_SETTINGS_H__

#include <avr/eeprom.h>

extern uint8_t EEMEM ee_enable_dhcp;
extern uint8_t EEMEM ee_eth_addr[6]; 
extern uint8_t EEMEM ee_ip_addr[4]; 
extern uint8_t EEMEM ee_net_mask[4]; 
extern uint8_t EEMEM ee_gateway[4]; 


extern uint8_t _enable_dhcp;
extern uint8_t _eth_addr[6];
extern uint8_t _ip_addr[4];
extern uint8_t _net_mask[4];
extern uint8_t _gateway[4];

#endif //__EE_SETTINGS_H__
