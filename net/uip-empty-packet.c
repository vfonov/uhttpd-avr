#include <string.h>

#include "uip-split.h"
#include "uip.h"
//#include "uip-fw.h"
#include "uip_arch.h"
#include "net/nic.h"
#include <util/delay_basic.h>

#define TCP_FIN 0x01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PSH 0x08
#define TCP_ACK 0x10
#define TCP_URG 0x20
#define TCP_CTL 0x3f

#define BUF ((struct uip_tcpip_hdr *)&uip_buf[UIP_LLH_LEN])

void uip_emtpy_packet_output(void)
{
  u16_t tcplen;

  /* We only try to hack TCP packets with some data */
  if(BUF->proto == UIP_PROTO_TCP && (uip_len > (UIP_TCPIP_HLEN + UIP_LLH_LEN + 10)) ) 
	{ 
		//send the main packet
		nic_send();

		while(nic_sending()) {asm("nop");}; //wait untill packet is sent away
    /* Create the second packet. This is done by setting the payload size to 0
      */
    uip_len = UIP_TCPIP_HLEN;
#if UIP_CONF_IPV6
    /* For IPv6, the IP length field does not include the IPv6 IP header
       length. */
    BUF->len[0] = ((uip_len - UIP_IPH_LEN) >> 8);
    BUF->len[1] = ((uip_len - UIP_IPH_LEN) & 0xff);
#else /* UIP_CONF_IPV6 */
    BUF->len[0] = uip_len >> 8;
    BUF->len[1] = uip_len & 0xff;
#endif /* UIP_CONF_IPV6 */ 


    /* Recalculate the TCP checksum. */
    BUF->tcpchksum = 0;
    BUF->tcpchksum = ~(uip_tcpchksum());

#if !UIP_CONF_IPV6
    /* Recalculate the IP checksum. */
    BUF->ipchksum = 0;
    BUF->ipchksum = ~(uip_ipchksum());
#endif /* UIP_CONF_IPV6 */

    /* Transmit the second packet. */
    /*    uip_fw_output();*/
		//_delay_loop_1(254);
		uip_len+=UIP_LLH_LEN;
    nic_send();
  } else {
    /*    uip_fw_output();*/
    nic_send();
  }
}
