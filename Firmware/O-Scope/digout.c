#include "oscope.h"
#include "digout.h"

uint16_t pin_modes[4] = { DIGOUT_OUT, DIGOUT_OUT, DIGOUT_OUT, DIGOUT_OUT };

// Initial PWM frequency is 1 kHz and duty cycle is 50%
uint16_t pwm_OCxRS_save[4] = { 15999, 15999, 15999, 15999 };
uint16_t pwm_OCxR_save[4] = { 7999, 7999, 7999, 7999 };

// Initial servo pulse width is 1.5 ms
uint16_t servo_OCxRS_save[4] = { 23999, 23999, 23999, 23999 };
uint16_t servo_OCxR_save[4] = { 1, 1, 1, 1 };

void digout_set(uint16_t pin) {
    if (pin == 0)
        D0_LAT = 1;
    else if (pin == 1)
        D1_LAT = 1;
    else if (pin == 2)
        D2_LAT = 1;
    else if (pin == 3)
        D3_LAT = 1;
}

void digout_clear(uint16_t pin) {
    if (pin == 0)
        D0_LAT = 0;
    else if (pin == 1)
        D1_LAT = 0;
    else if (pin == 2)
        D2_LAT = 0;
    else if (pin == 3)
        D3_LAT = 0;
}

void digout_toggle(uint16_t pin) {
    if (pin == 0)
        D0_LAT = !D0_LAT;
    else if (pin == 1)
        D1_LAT = !D1_LAT;
    else if (pin == 2)
        D2_LAT = !D2_LAT;
    else if (pin == 3)
        D3_LAT = !D3_LAT;
}

void digout_write(uint16_t pin, uint16_t val) {
    if (pin == 0)
        D0_LAT = (val) ? 1 : 0;
    else if (pin == 1)
        D1_LAT = (val) ? 1 : 0;
    else if (pin == 2)
        D2_LAT = (val) ? 1 : 0;
    else if (pin == 3)
        D3_LAT = (val) ? 1 : 0;
}

uint16_t digout_read(uint16_t pin) {
    if (pin == 0)
        return D0;
    else if (pin == 1)
        return D1;
    else if (pin == 2)
        return D2;
    else if (pin == 3)
        return D3;
    else
        return 0xFFFF;
}

void digout_set_od(uint16_t pin, uint16_t val) {
    if (pin == 0)
        D0_OD = (val) ? 1 : 0;
    else if (pin == 1)
        D1_OD = (val) ? 1 : 0;
    else if (pin == 2)
        D2_OD = (val) ? 1 : 0;
    else if (pin == 3)
        D3_OD = (val) ? 1 : 0;
}

uint16_t digout_get_od(uint16_t pin) {
    if (pin == 0)
        return D0_OD;
    else if (pin == 1)
        return D1_OD;
    else if (pin == 2)
        return D2_OD;
    else if (pin == 3)
        return D3_OD;
    else
        return 0xFFFF;
}

void digout_set_duty(uint16_t pin, uint16_t duty) {
    OCx_T *oc;
    WORD32 temp;

    oc = (OCx_T *)&OC1CON1;
    if (pin < 4) {
        temp.ul = (uint32_t)duty * (uint32_t)(oc[pin].OCxRS);
        oc[pin].OCxR = temp.w[1];
    }
}

uint16_t digout_get_duty(uint16_t pin) {
    OCx_T *oc;
    WORD32 temp;

    oc = (OCx_T *)&OC1CON1;
    if (pin < 4) {
        temp.w[0] = 0;
        temp.w[1] = oc[pin].OCxR;
        return (uint16_t)(temp.ul / (uint32_t)(oc[pin].OCxRS));
    } else
        return 0xFFFF;
}

void digout_set_period(uint16_t pin, uint16_t period) {
    OCx_T *oc;
    WORD32 temp;
    uint16_t duty;

    oc = (OCx_T *)&OC1CON1;
    if (pin < 4) {
        temp.w[0] = 0;
        temp.w[1] = oc[pin].OCxR;
        duty = (uint16_t)(temp.ul / (uint32_t)(oc[pin].OCxRS));
        temp.ul = (uint32_t)duty * (uint32_t)period;
        oc[pin].OCxRS = period;
        oc[pin].OCxR = temp.w[1];
        oc[pin].OCxTMR = 0;
    }
}

uint16_t digout_get_period(uint16_t pin) {
    OCx_T *oc;

    oc = (OCx_T *)&OC1CON1;
    if (pin < 4)
        return oc[pin].OCxRS;
    else
        return 0xFFFF;
}

void digout_set_width(uint16_t pin, uint16_t width) {
    OCx_T *oc;

    oc = (OCx_T *)&OC1CON1;
    if (pin < 4){
        oc[pin].OCxRS = width;
        oc[pin].OCxR = 1;
        oc[pin].OCxTMR = 0;
    }
}

uint16_t digout_get_width(uint16_t pin) {
    OCx_T *oc;

    oc = (OCx_T *)&OC1CON1;
    if (pin < 4)
        return oc[pin].OCxRS;
    else
        return 0xFFFF;
}

void digout_set_timer1_period(uint16_t value1, uint16_t value2) {
    uint16_t pin;
    OCx_T *oc;

    T1CONbits.TON = 0;
    PR1 = value1;
    T1CON = value2;
    TMR1 = 0;

    oc = (OCx_T *)&OC1CON1;
    for (pin = 0; pin < 4; pin++) {
        if (pin_modes[pin] == DIGOUT_SERVO) {
            oc[pin].OCxTMR = 0;
        }
    }
    T1CONbits.TON = 1;
}

void digout_set_mode(uint16_t pin, uint16_t mode) {
    uint8_t *RPOR, *RPINR;
    OCx_T *oc;

    if ((pin > 3) || (mode > DIGOUT_SERVO))
        return;

    oc = (OCx_T *)&OC1CON1;
    RPOR = (uint8_t *)&RPOR0;
    RPINR = (uint8_t *)&RPINR0;

    if ((pin_modes[pin] == DIGOUT_PWM) || (pin_modes[pin] == DIGOUT_SERVO)) {
        oc[pin].OCxCON1 = 0;
        oc[pin].OCxCON2 = 0;
        __builtin_write_OSCCONL(OSCCON & 0xBF);
        if (pin == 0)
            RPOR[D0_RP] = 0;
        else if (pin == 1)
            RPOR[D1_RP] = 0;
        else if (pin == 2)
            RPOR[D2_RP] = 0;
        else if (pin == 3)
            RPOR[D3_RP] = 0;
        __builtin_write_OSCCONL(OSCCON | 0x40);
    }

    if (pin_modes[pin] == DIGOUT_PWM) {
        pwm_OCxRS_save[pin] = oc[pin].OCxRS;
        pwm_OCxR_save[pin] = oc[pin].OCxR;
    } else if (pin_modes[pin] == DIGOUT_SERVO) {
        servo_OCxRS_save[pin] = oc[pin].OCxRS;
        servo_OCxR_save[pin] = oc[pin].OCxR;
    }

    pin_modes[pin] = mode;
    if (mode == DIGOUT_OUT) {
        if (pin == 0)
            D0_DIR = OUT;
        else if (pin == 1)
            D1_DIR = OUT;
        else if (pin == 2)
            D2_DIR = OUT;
        else if (pin == 3)
            D3_DIR = OUT;
    } else if (mode == DIGOUT_IN) {
        if (pin == 0)
            D0_DIR = IN;
        else if (pin == 1)
            D1_DIR = IN;
        else if (pin == 2)
            D2_DIR = IN;
        else if (pin == 3)
            D3_DIR = IN;
    } else if (mode == DIGOUT_PWM) {
        __builtin_write_OSCCONL(OSCCON & 0xBF);
        if (pin == 0) {
            D0_DIR = OUT;
            RPOR[D0_RP] = OC1_RP;
        } else if (pin == 1) {
            D1_DIR = OUT;
            RPOR[D1_RP] = OC2_RP;
        } else if (pin == 2) {
            D2_DIR = OUT;
            RPOR[D2_RP] = OC3_RP;
        } else if (pin == 3) {
            D3_DIR = OUT;
            RPOR[D3_RP] = OC4_RP;
        }
        __builtin_write_OSCCONL(OSCCON | 0x40);
        oc[pin].OCxRS = pwm_OCxRS_save[pin];
        oc[pin].OCxR = pwm_OCxR_save[pin];
        oc[pin].OCxTMR = 0;
        oc[pin].OCxCON1 = 0x1C06;
        oc[pin].OCxCON2 = 0x001F;
    } else if (mode == DIGOUT_SERVO) {
        __builtin_write_OSCCONL(OSCCON & 0xBF);
        if (pin == 0) {
            D0_DIR = OUT;
            RPOR[D0_RP] = OC1_RP;
        } else if (pin == 1) {
            D1_DIR = OUT;
            RPOR[D1_RP] = OC2_RP;
        } else if (pin == 2) {
            D2_DIR = OUT;
            RPOR[D2_RP] = OC3_RP;
        } else if (pin == 3) {
            D3_DIR = OUT;
            RPOR[D3_RP] = OC4_RP;
        }
        __builtin_write_OSCCONL(OSCCON | 0x40);
        oc[pin].OCxRS = servo_OCxRS_save[pin];
        oc[pin].OCxR = servo_OCxR_save[pin];
        oc[pin].OCxTMR = 0;
        oc[pin].OCxCON1 = 0x1C0F;
        oc[pin].OCxCON2 = 0x008B;
    }
}

uint16_t digout_get_mode(uint16_t pin) {
    if (pin < 4)
        return pin_modes[pin];
    else
        return 0xFFFF;
}
