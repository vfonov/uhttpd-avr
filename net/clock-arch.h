#ifndef __CLOCK_ARCH_H__
#define __CLOCK_ARCH_H__


#define TIMER_PRESCALE    1024
//#define TIMERCOUNTER_PERIODIC_TIMEOUT (F_CPU / TIMER_PRESCALE / 256)

typedef unsigned short clock_time_t;
#define CLOCK_CONF_SECOND (F_CPU / TIMER_PRESCALE / 256)


#endif /* __CLOCK_ARCH_H__ */
