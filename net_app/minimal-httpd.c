#include "minimal-httpd.h"
#include "uip.h"
#include <string.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include "compiler.h"
#include "clock.h"

/*
 * Declaration of the protosocket function that handles the connection
 * (defined at the end of the code).
 */
static int handle_connection(struct minimal_httpd_state *s);
/*
 * The initialization function. We must explicitly call this function
 * from the system initialization code, some time after uip_init() is
 * called.
 */
void
hello_world_init(void)
{
  /* We start to listen for connections on TCP port 80. */
  uip_listen(HTONS(80));
}

/*
 * In minimal-httpd.h we have defined the UIP_APPCALL macro to
 * minimal_httpd_appcall so that this funcion is uIP's application
 * function. This function is called whenever an uIP event occurs
 * (e.g. when a new connection is established, new data arrives, sent
 * data is acknowledged, data needs to be retransmitted, etc.).
 */
void
minimal_httpd_appcall(void)
{
  /*
   * The uip_conn structure has a field called "appstate" that holds
   * the application state of the connection. We make a pointer to
   * this to access it easier.
   */
  struct minimal_httpd_state *s = &(uip_conn->appstate);

  /*
   * If a new connection was just established, we should initialize
   * the protosocket in our applications' state structure.
   */
  if(uip_connected()) {
    PSOCK_INIT(&s->p, s->inputbuffer, sizeof(s->inputbuffer));
    s->sent=0;
  }

  /*
   * Finally, we run the protosocket function that actually handles
   * the communication. We pass it a pointer to the application state
   * of the current connection.
   */
  handle_connection(s);
}

static u16 generate_http_responce(void *state)
{
  u16 code=(u16)state;

  return sprintf_P(uip_appdata,PSTR("HTTP/1.0 %d OK\r\nContent-Type: text/html\r\nContent-Type: text/html\r\nPragma: no-cache\r\n\r\n"),code);
}

static u16 send_P(void *state)
{
  PGM_P p=(PGM_P)state;
  u8 *end=strcpy_P(uip_appdata,p);
  return (u8 *)end-(u8 *)uip_appdata;
}

static u16 send_index(void *state)
{
  return sprintf_P(uip_appdata,PSTR("Current time:%ld\n"),(u32)clock_time());
}

static u16 send_unsupported(void *state)
{
  return sprintf_P(uip_appdata,PSTR("<HTML><BODY>Request unsupported!</BODY></HTML>"),(u32)clock_time());
}


/*
 * This is the protosocket function that handles the communication. A
 * protosocket function must always return an int, but must never
 * explicitly return - all return statements are hidden in the PSOCK
 * macros.
 */

static int handle_connection(struct hello_world_state *s)
{
  PSOCK_BEGIN(&s->p);
  //1. get HTTP request
  PSOCK_READTO(&s->p,' '); //GET the first word
  //printf("Command:%s\r\n",s->inputbuffer);
  if(!strncmp_P(s->inputbuffer,PSTR("GET"),3)) //Got Get request
  {
    //read the url
    PSOCK_READTO(&s->p,' '); //GET the url
    //printf("Requested:%s\r\n",s->inputbuffer);
    if(!strncmp_P(s->inputbuffer,PSTR("/"),1) || !strncmp_P(s->inputbuffer,PSTR("/index.html"),11) ) 
    {
      PSOCK_GENERATOR_SEND(&s->p, generate_http_responce, (void*)200);
      PSOCK_GENERATOR_SEND(&s->p, send_index,(void*)0);
    } else {
      PSOCK_GENERATOR_SEND(&s->p, generate_http_responce, (void*)200);
      PSOCK_GENERATOR_SEND(&s->p, send_unsupported,(void*)0);
    }
  } else {
    PSOCK_GENERATOR_SEND(&s->p, generate_http_responce, (void*)200);
    PSOCK_GENERATOR_SEND(&s->p, send_unsupported, (void*)0);
  }
  PSOCK_CLOSE(&s->p);
  PSOCK_END(&s->p);
}
