#ifndef _DIGOUT_H_
#define _DIGOUT_H_

#include <stdint.h>

#define DIGOUT_OUT      0
#define DIGOUT_IN       1
#define DIGOUT_PWM      2
#define DIGOUT_SERVO    3

typedef struct {
    union {
        struct {
            volatile uint16_t OCM : 3;
            volatile uint16_t TRIGMODE : 1;
            volatile uint16_t OCFLT0 : 1;
            volatile uint16_t OCFLT1 : 1;
            volatile uint16_t OCFLT2 : 1;
            volatile uint16_t ENFLT0 : 1;
            volatile uint16_t ENFLT1 : 1;
            volatile uint16_t ENFLT2 : 1;
            volatile uint16_t OCTSEL : 3;
            volatile uint16_t OCSIDL : 1;
            uint16_t : 2;
        } OCxCON1bits;
        volatile uint16_t OCxCON1;
    };
    union {
        struct {
            volatile uint16_t SYNCSEL : 5;
            volatile uint16_t OCTRIS : 1;
            volatile uint16_t TRIGSTAT : 1;
            volatile uint16_t OCTRIG : 1;
            volatile uint16_t OC32 : 1;
            volatile uint16_t DCB : 2;
            uint16_t : 1;
            volatile uint16_t OCINV : 1;
            volatile uint16_t FLTTRIEN : 1;
            volatile uint16_t FLTOUT : 1;
            volatile uint16_t FLTMD : 1;
        } OCxCON2bits;
        volatile uint16_t OCxCON2;
    };
    volatile uint16_t OCxRS;
    volatile uint16_t OCxR;
    volatile uint16_t OCxTMR;
} OCx_T;

void digout_set(uint16_t pin);
void digout_clear(uint16_t pin);
void digout_toggle(uint16_t pin);
void digout_write(uint16_t pin, uint16_t val);
uint16_t digout_read(uint16_t pin);
void digout_set_od(uint16_t pin, uint16_t val);
uint16_t digout_get_od(uint16_t pin);
void digout_set_duty(uint16_t pin, uint16_t duty);
uint16_t digout_get_duty(uint16_t pin);
void digout_set_period(uint16_t pin, uint16_t period);
uint16_t digout_get_period(uint16_t pin);
void digout_set_width(uint16_t pin, uint16_t width);
uint16_t digout_get_width(uint16_t pin);
void digout_set_timer1_period(uint16_t value1, uint16_t value2);
void digout_set_mode(uint16_t pin, uint16_t mode);
uint16_t digout_get_mode(uint16_t pin);
#endif

