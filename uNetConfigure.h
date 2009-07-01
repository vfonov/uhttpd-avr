#ifndef __UNETCONFIGURE_H__
#define __UNETCONFIGURE_H__

// ethernet configuration

#define ENC28J60_ENABLE_DUPLEX  1


/**
 * uIP buffer size (maximum packat size, DHCP needs at least 400bytes)
 */

#define UIP_CONF_BUFFER_SIZE    500


// Ethernet mac address, have to be unique on the net

#define UIP_ETHADDR0    0x00  /**< The first octet of the Ethernet
				 address */
#define UIP_ETHADDR1    0xbd  /**< The second octet of the Ethernet
				 address  */
#define UIP_ETHADDR2    0x3b  /**< The third octet of the Ethernet
				 address  */
#define UIP_ETHADDR3    0x33  /**< The fourth octet of the Ethernet
				 address */
#define UIP_ETHADDR4    0x05  /**< The fifth octet of the Ethernet
				 address  */
#define UIP_ETHADDR5    0x71  /**< The sixth octet of the Ethernet
				 address */


// TCP configuration
//Use DHCP for TCP configuration (see warning above about buffer size)
#define USE_DHCP 0


#define UIP_IPADDR0     192 /**< The first octet of the IP address of
			       this uIP node  */
#define UIP_IPADDR1     168 /**< The second octet of the IP address of
			       this uIP node */
#define UIP_IPADDR2     0   /**< The third octet of the IP address of
			       this uIP node */
#define UIP_IPADDR3     31   /**< The fourth octet of the IP address of
			       this uIP node */

#define UIP_NETMASK0    255 /**< The first octet of the netmask of
			       this uIP node */
#define UIP_NETMASK1    255 /**< The second octet of the netmask of
			       this uIP node */
#define UIP_NETMASK2    255 /**< The third octet of the netmask of
			       this uIP node */
#define UIP_NETMASK3    0   /**< The fourth octet of the netmask of
			       this uIP node */

#define UIP_DRIPADDR0   192 /**< The first octet of the IP address of
			       the default router */
#define UIP_DRIPADDR1   168 /**< The second octet of the IP address of
			       the default router */
#define UIP_DRIPADDR2   0   /**< The third octet of the IP address of
			       the default router */
#define UIP_DRIPADDR3   1   /**< The fourth octet of the IP address of
			       the default router */

// Serial Debug configuration
#define DEBUG_SERIAL 0


// which mechanism to use for protothreads
//#define LC_CONF_INCLUDE "lc-addrlabels.h" // using special GCC feature (uses sligtly less program memory)
#define LC_CONF_INCLUDE "lc-switch.h" // using switch statements (standard)

// UIP debug messages 
#define DEBUG_PRINTF(...) /*printf(__VA_ARGS__)*/

#endif //__UNETCONFIGURE_H__
