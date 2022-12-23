#include "oscope.h"
#include "scope.h"
#include "config.h"

extern void trigger_sweep_at_4MSps(void);

TRIGGER_SWEEP_T trigger_sweep;
uint16_t scope_buffer[SCOPE_BUFFER_SIZE];
uint16_t sweep_in_progress, samples_left;

uint16_t ch1val, ch2val;
uint16_t num_avg, max_avg;
uint16_t T2ISRoffset;
uint16_t T2ISRoffset_vals[5] = { 0x0000, 0x0000, 0x000E, 0x0024, 0x004A };
uint16_t ADL0CONL_vals[5] = { 0x0581, 0x0083, 0x0087, 0x008F, 0x009F };
uint16_t avg_Tcy_thresholds[5] = { 0, 42, 50, 66, 98 };

void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void) {
    disable_interrupts();
    ADL0CONLbits.SAMP = 0;
    IFS0bits.T2IF = 0;
    __asm__("push.s");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("nop");
    __asm__("mov _T2ISRoffset, W0");
    __asm__("bra W0");

    __asm__("T2ISR_AVG2: mov #_ADRES0, W0");
    __asm__("mov [W0++], W1");
    __asm__("nop");
    __asm__("mov [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("mov W1, _ch1val");
    __asm__("add W2, [W0], W2");
    __asm__("mov W2, _ch2val");
    ADL0CONLbits.SAMP = 1;
    __asm__("pop.s");
    enable_interrupts();
    __asm__("ulnk");
    __asm__("retfie");

    __asm__("T2ISR_AVG4: mov #_ADRES0, W0");
    __asm__("mov [W0++], W1");
    __asm__("nop");
    __asm__("mov [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("mov W1, _ch1val");
    __asm__("add W2, [W0], W2");
    __asm__("mov W2, _ch2val");
    ADL0CONLbits.SAMP = 1;
    __asm__("pop.s");
    enable_interrupts();
    __asm__("ulnk");
    __asm__("retfie");

    __asm__("T2ISR_AVG8: mov #_ADRES0, W0");
    __asm__("mov [W0++], W1");
    __asm__("nop");
    __asm__("mov [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("mov W1, _ch1val");
    __asm__("add W2, [W0], W2");
    __asm__("mov W2, _ch2val");
    ADL0CONLbits.SAMP = 1;
    __asm__("pop.s");
    enable_interrupts();
    __asm__("ulnk");
    __asm__("retfie");

    __asm__("T2ISR_AVG16: mov #_ADRES0, W0");
    __asm__("mov [W0++], W1");
    __asm__("nop");
    __asm__("mov [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("nop");
    __asm__("add W2, [W0++], W2");
    __asm__("nop");
    __asm__("add W1, [W0++], W1");
    __asm__("mov W1, _ch1val");
    __asm__("add W2, [W0], W2");
    __asm__("mov W2, _ch2val");
    ADL0CONLbits.SAMP = 1;
    __asm__("pop.s");
    enable_interrupts();
    __asm__("ulnk");
    __asm__("retfie");
}

void __attribute__((interrupt, no_auto_psv)) _DMA1Interrupt(void) {
    sweep_in_progress = FALSE;
    T2CONbits.TON = 0;
    IFS0bits.DMA1IF = 0;
}

void trigger_sweep_lt_4MSps(void) {
    if (sweep_in_progress == FALSE) {
        IFS0bits.AD1IF = 0;
        IFS0bits.DMA0IF = 0;
        IFS0bits.DMA1IF = 0;
        IFS0bits.T2IF = 0;
        TMR2 = 0;
        DMACH0bits.CHEN = 1;
        DMACH1bits.CHEN = 1;
        T2CONbits.TON = 1;
        sweep_in_progress = TRUE;
        if (((T2CON & 0x0030) == 0) && (PR2 < 1600)) {
            while (sweep_in_progress) {}
        }
    }
}

void cancel_sweep(void) {
    T2CONbits.TON = 0;

    DMACH0bits.CHEN = 0;
    DMACH1bits.CHEN = 0;
    DMADST0 = (uint16_t)&scope_buffer[0];
    DMACNT0 = SCOPE_BUFFER_SIZE / 2;
    DMADST1 = (uint16_t)&scope_buffer[SCOPE_BUFFER_SIZE / 2];
    DMACNT1 = SCOPE_BUFFER_SIZE / 2;
    sweep_in_progress = FALSE;
}

void update_acquire_mode(void) {
    T2CONbits.TON = 0;
    if (sweep_in_progress == TRUE)
        cancel_sweep();

    if ((T2CON & 0x0030) == 0) {
        for (num_avg = max_avg; num_avg > 0; num_avg--)
            if (PR2 >= avg_Tcy_thresholds[num_avg])
                break;
    } else
        num_avg = max_avg;

    if (num_avg == 0) {
        DMASRC0 = (uint16_t)&ADRES0;
        DMASRC1 = (uint16_t)&ADRES1;
        T2ISRoffset = 0;
        IEC0bits.T2IE = 0;
        if (((T2CON & 0x0030) == 0) && (PR2 < 7)) {
            PR2 = 3;
            DMACH0bits.CHEN = 0;
            DMACH1bits.CHEN = 0;
            ADCON3bits.SLEN0 = 0;
            ADL0CONLbits.SLEN = 0;
            while (ADL0STATbits.LBUSY == 1) {}
            ADL0CONL = 0x0281;      //     SLENCLR = 0 (SLEN cleared by software), 
                                    //     SLTSRC = 00010 (manual trigger event), 
                                    //     THSRC = 1 (thresh comp from samp list thresh reg),
                                    //     SLSIZE = 00001 (samp list size = 2)
            ADL0PTR = 0;
            ADL0CONLbits.SAMP = 1;
            trigger_sweep = trigger_sweep_at_4MSps;
        } else {
            ADCON3bits.SLEN0 = 0;
            ADL0CONLbits.SLEN = 0;
            while (ADL0STATbits.LBUSY == 1) {}
            ADL0CONL = 0x0581;      //     SLENCLR = 0 (SLEN cleared by software), 
                                    //     SLTSRC = 00101 (trigger on Timer2), 
                                    //     THSRC = 1 (thresh comp from samp list thresh reg),
                                    //     SLSIZE = 00001 (samp list size = 2)
            ADL0PTR = 0;
            ADL0CONLbits.SAMP = 1;
            ADCON3bits.SLEN0 = 1;
            ADL0CONLbits.SLEN = 1;
            trigger_sweep = trigger_sweep_lt_4MSps;
        }
    } else {
        DMASRC0 = (uint16_t)&ch1val;
        DMASRC1 = (uint16_t)&ch2val;
        T2ISRoffset = T2ISRoffset_vals[num_avg];
        IFS0bits.T2IF = 0;
        IEC0bits.T2IE = 1;
        ADCON3bits.SLEN0 = 0;
        ADL0CONLbits.SLEN = 0;
        while (ADL0STATbits.LBUSY == 1) {}
        ADL0CONL = ADL0CONL_vals[num_avg];
        ADL0PTR = 0;
        ADL0CONLbits.SAMP = 1;
        ADCON3bits.SLEN0 = 1;
        ADL0CONLbits.SLEN = 1;
        trigger_sweep = trigger_sweep_lt_4MSps;
    }
}

void clear_scope_buffer(void) {
    uint16_t i;

    for (i = 0; i < SCOPE_BUFFER_SIZE; i++)
        scope_buffer[i] = 0;
}

void set_period(uint16_t value1, uint16_t value2) {
    T2CONbits.TON = 0;
    PR2 = value1;
    T2CON = value2;
    TMR2 = 0;
    update_acquire_mode();
}

void set_sweep_in_progress(uint16_t value) {
    sweep_in_progress = value;
}

uint16_t get_sweep_in_progress(void) {
    return sweep_in_progress;
}

void set_samples_left(uint16_t value) {
    samples_left = value;
}

uint16_t get_samples_left(void) {
    return samples_left;
}

void set_max_avg(uint16_t value) {
    max_avg = value;
    update_acquire_mode();
}

uint16_t get_max_avg(void) {
    return max_avg;
}

void set_num_avg(uint16_t value) {
    num_avg = value;
}

uint16_t get_num_avg(void) {
    return num_avg;
}

