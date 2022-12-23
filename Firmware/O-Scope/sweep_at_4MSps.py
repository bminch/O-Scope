#!/usr/env/python

file = open('sweep_at_4MSps.c', 'w')
file.write('''#include "pic24fj.h"
#include "oscope.h"

extern uint16_t scope_buffer[];

uint16_t *ch1ptr, *ch2ptr;

void trigger_sweep_at_4MSps(void) {

    ch1ptr = &scope_buffer[0];
    ch2ptr = &scope_buffer[SCOPE_BUFFER_SIZE / 2];

    disable_interrupts();
    ADCON3bits.SLEN0 = 1;           // enable sample list 0 in ADCON3
    ADL0CONLbits.SLEN = 1;          // enable sample list 0
    ADL0CONLbits.SAMP = 0;
    __asm__("mov _ch1ptr, W0");
    __asm__("mov _ch2ptr, W1");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
''')

for i in range(1500):
    file.write('''    __asm__("mov _ADRES0, W2");
    __asm__("mov W2, [W0++]");
    __asm__("mov _ADRES1, W2");
    __asm__("mov W2, [W1++]");
''')

file.write('''    ADL0CONLbits.SAMP = 1;
    ADCON3bits.SLEN0 = 0;           // disable sample list 0 in ADCON3
    ADL0CONLbits.SLEN = 0;          // disable sample list 0
    enable_interrupts();
}
''')

