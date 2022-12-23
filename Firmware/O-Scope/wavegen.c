#include "oscope.h"
#include "wavegen.h"

uint16_t shape_val, freq_val_l, freq_val_h;
uint16_t phase_val, amplitude_val, offset_val;
uint16_t sq_offset_adj, nsq_offset_adj;
uint16_t AD9837_control_bits;

uint16_t wavegen_offset_mode, wavegen_offset_samples;
WORD32 wavegen_offset_address;

void __attribute__((interrupt, no_auto_psv)) _T3Interrupt(void) {
    IFS0bits.T3IF = 0;

    __asm__("push _TBLPAG");
    TBLPAG = wavegen_offset_address.w[1];
    DAC1DAT = __builtin_tblrdl(wavegen_offset_address.w[0]);
    __asm__("pop _TBLPAG");

    wavegen_offset_address.ul += 2;
    wavegen_offset_samples--;
    if (wavegen_offset_samples == 0) {
        if (wavegen_offset_mode) {
            wavegen_offset_address.ul = WAVEGEN_OFFSET_SAMPLE_MEM;
            __asm__("push _TBLPAG");
            TBLPAG = WAVEGEN_OFFSET_NUM_SAMPLES >> 16;
            wavegen_offset_samples = __builtin_tblrdl(WAVEGEN_OFFSET_NUM_SAMPLES & 0xFFFF);
            __asm__("pop _TBLPAG");
        } else {
            wavegen_offset_stop();
        }
    }
}

void init_wavegen(void) {
    uint8_t *RPOR, *RPINR;

    RPOR = (uint8_t *)&RPOR0;
    RPINR = (uint8_t *)&RPINR0;

    nCS_DDS_DIR = OUT; nCS_DDS = 1;
    SCK_DDS_DIR = OUT; SCK_DDS = 1;
    MOSI_DDS_DIR = OUT; MOSI_DDS_DIR = OUT;
    MCLK_DDS_DIR = OUT; MCLK_DDS = 0;

    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPINR[MISO1_RP] = MISO_DDS_RP;
    RPOR[MOSI_DDS_RP] = MOSI1_RP;
    RPOR[SCK_DDS_RP] = SCK1OUT_RP;
    __builtin_write_OSCCONL(OSCCON | 0x40);

    SPI1CON1 = 0x0172;              // SPI mode = 2, SCK freq = 1 MHz
    SPI1CON2 = 0;
    SPI1STAT = 0x8000;

    nCS_POT_DIR = OUT; nCS_POT = 1;
    SCK_POT_DIR = OUT; SCK_POT = 0;
    MOSI_POT_DIR = OUT; MOSI_POT = 0;

    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPINR[MISO2_RP] = MISO_POT_RP;
    RPOR[MOSI_POT_RP] = MOSI2_RP;
    RPOR[SCK_POT_RP] = SCK2OUT_RP;
    __builtin_write_OSCCONL(OSCCON | 0x40);

    SPI2CON1 = 0x0132;              // SPI mode = 0, SCK freq = 1 MHz
    SPI2CON2 = 0;
    SPI2STAT = 0x8000;

    __builtin_write_OSCCONL(OSCCON & 0xBF);
    RPOR[MCLK_DDS_RP] = OC5_RP;
    __builtin_write_OSCCONL(OSCCON | 0x40);

    OC5CON1 = 0x1C06;               // configure OC5 to produce a 4 MHz, 50% duty cycle PWM output
    OC5CON2 = 0x001F;
    OC5RS = 3;
    OC5R = 1;

    nSQUARE_DIR = OUT; nSQUARE = 1;
    WG_GAIN_DIR = OUT; WG_GAIN = 0;

    AD9837_control_bits = AD9837_B28 | AD9837_RESET;
    spi_out_dds(AD9837_CONTROL | AD9837_control_bits);

    sq_offset_adj = 580;
    nsq_offset_adj = 580;

    set_shape(0);                   // set initial shape to DC
    set_freq(1573, 4);              // set initial freq to 1 kHz
    set_phase(0);
    set_amplitude(0);               // set initial amplitude to 0 V
    set_offset(500);                // set initial offset to 2.5 V

    T3CON = 0x0010;                 // set Timer3 period to 30ms
    PR3 = 0xEA5F;
    TMR3 = 0;
    IFS0bits.T3IF = 0;

    wavegen_offset_set_mode(SINGLE);
    wavegen_offset_samples = 0;
    wavegen_offset_address.ul = WAVEGEN_OFFSET_SAMPLE_MEM;
}

void set_wg_gain(uint16_t value) {
    WG_GAIN = (value) ? 1 : 0;
}

uint16_t get_wg_gain(void) {
    return (WG_GAIN) ? 1 : 0;
}

void set_nsq(uint16_t value) {
    nSQUARE = (value) ? 1 : 0;
}

uint16_t get_nsq(void) {
    return (nSQUARE) ? 1 : 0;
}

void spi_out_dds(uint16_t value) {
    uint16_t ret;
    WORD temp;

    temp.w = value;
    nCS_DDS = 0;
    SPI1BUF = (uint16_t)temp.b[1];
    while (SPI1STATbits.SPIRBF == 0) {}
    ret = SPI1BUF;
    SPI1BUF = (uint16_t)temp.b[0];
    while (SPI1STATbits.SPIRBF == 0) {}
    ret = SPI1BUF;
    nCS_DDS = 1;
}

void spi_out_pot(uint8_t value) {
    uint16_t ret;

    nCS_POT = 0;
    SPI2BUF = (uint16_t)value;
    while (SPI2STATbits.SPIRBF == 0) {}
    ret = SPI2BUF;
    nCS_POT = 1;
}

void set_shape(uint16_t value) {
    if (value <= 3)
        shape_val = value;
    switch (shape_val) {
        case DC:
            AD9837_control_bits |= AD9837_RESET;
            AD9837_control_bits &= ~(AD9837_OPBITEN | AD9837_MODE | AD9837_DIV2);
            spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
            nSQUARE = 1;
            DAC2DAT = nsq_offset_adj;
            break;
        case SIN:
            AD9837_control_bits &= ~(AD9837_RESET | AD9837_OPBITEN | AD9837_MODE | AD9837_DIV2);
            spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
            nSQUARE = 1;
            DAC2DAT = nsq_offset_adj;
            break;
        case SQUARE:
            AD9837_control_bits |= (AD9837_OPBITEN | AD9837_DIV2);
            AD9837_control_bits &= ~(AD9837_RESET | AD9837_MODE);
            spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
            nSQUARE = 0;
            DAC2DAT = sq_offset_adj;
            break;
        case TRIANGLE:
            AD9837_control_bits |= AD9837_MODE;
            AD9837_control_bits &= ~(AD9837_RESET | AD9837_OPBITEN | AD9837_DIV2);
            spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
            nSQUARE = 1;
            DAC2DAT = nsq_offset_adj;
    }
}

uint16_t get_shape(void) {
    return shape_val;
}

void set_freq(uint16_t value_l, uint16_t value_h) {
    freq_val_l = value_l;
    freq_val_h = value_h;
    if ((AD9837_control_bits & AD9837_FSEL) != 0) {
        spi_out_dds(AD9837_14FREQ0 | freq_val_l);
        spi_out_dds(AD9837_14FREQ0 | freq_val_h);
        AD9837_control_bits &= ~AD9837_FSEL;
        spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
    } else {
        spi_out_dds(AD9837_14FREQ1 | freq_val_l);
        spi_out_dds(AD9837_14FREQ1 | freq_val_h);
        AD9837_control_bits |= AD9837_FSEL;
        spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
    }
}

uint16_t get_freq_l(void) {
    return freq_val_l;
}

uint16_t get_freq_h(void) {
    return freq_val_h;
}

void set_phase(uint16_t value) {
    phase_val = value;
    if ((AD9837_control_bits & AD9837_PSEL) != 0) {
        spi_out_dds(AD9837_12PHASE0 | (phase_val & 0x0FFF));
        AD9837_control_bits &= ~AD9837_PSEL;
        spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
    } else {
        spi_out_dds(AD9837_12PHASE1 | (phase_val & 0x0FFF));
        AD9837_control_bits |= AD9837_PSEL;
        spi_out_dds(AD9837_CONTROL | AD9837_control_bits);
    }
}

uint16_t get_phase(void) {
    return phase_val;
}

void set_amplitude(uint16_t value) {
    amplitude_val = value & 0xFF;
    spi_out_pot((uint8_t)amplitude_val);
}

uint16_t get_amplitude(void) {
    return amplitude_val;
}

void set_offset(uint16_t value) {
    offset_val = value & 0x03FF;
    if (T3CONbits.TON == 0)
        DAC1DAT = offset_val;
}

uint16_t get_offset(void) {
    return offset_val;
}

void set_sq_offset_adj(uint16_t value) {
    sq_offset_adj = value & 0x03FF;
    DAC2DAT = sq_offset_adj;
}

uint16_t get_sq_offset_adj(void) {
    return sq_offset_adj;
}

void set_nsq_offset_adj(uint16_t value) {
    nsq_offset_adj = value & 0x03FF;
    DAC2DAT = nsq_offset_adj;
}

uint16_t get_nsq_offset_adj(void) {
    return nsq_offset_adj;
}

void wavegen_offset_set_interval(uint16_t value1, uint16_t value2) {
    wavegen_offset_stop();
    PR3 = value1;
    T3CON = value2;
}

void wavegen_offset_set_mode(uint16_t value) {
    wavegen_offset_mode = (value) ? REPEAT : SINGLE;
}

uint16_t wavegen_offset_get_mode(void) {
    return wavegen_offset_mode;
}

void wavegen_offset_start(void) {
    uint16_t no_samples_present;

    wavegen_offset_address.ul = WAVEGEN_OFFSET_SAMPLE_MEM;
    __asm__("push _TBLPAG");
    TBLPAG = WAVEGEN_OFFSET_NUM_SAMPLES >> 16;
    wavegen_offset_samples = __builtin_tblrdl(WAVEGEN_OFFSET_NUM_SAMPLES & 0xFFFF);
    no_samples_present = __builtin_tblrdh(WAVEGEN_OFFSET_NUM_SAMPLES & 0xFFFF);
    __asm__("pop _TBLPAG");

    if (no_samples_present)
        return;

    IFS0bits.T3IF = 0;
    TMR3 = 0;
    IEC0bits.T3IE = 1;
    T3CONbits.TON = 1;
}

void wavegen_offset_stop(void) {
    T3CONbits.TON = 0;
    IEC0bits.T3IE = 0;
    set_offset(offset_val);
}

uint16_t wavegen_offset_get_samples_left(void) {
    return wavegen_offset_samples;
}
