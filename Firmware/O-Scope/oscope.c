#include "oscope.h"
#include "scope.h"
#include "wavegen.h"

void init_oscope(void) {
    uint8_t *RPOR, *RPINR;
    uint16_t *ADTBL;
    uint16_t i;

    CLKDIV = 0x0100;        // RCDIV = 001 (4MHz, div2), 
                            // CPDIV = 00 (FOSC = 32MHz, FCY = 16MHz)

    OSCTUN = 0x9000;        // enable FRC self tuning with USB host clock

    // Configure digital pins to be outputs
    D0_DIR = OUT; D0 = 0;
    D1_DIR = OUT; D1 = 0;
    D2_DIR = OUT; D2 = 0;
    D3_DIR = OUT; D3 = 0;

    // Make all pins digital I/Os
    ANSB = 0;
    ANSC = 0;
    ANSD = 0;
    ANSF = 0;
    ANSG = 0;

    ANSBbits.ANSB0 = 1;         // configure RB0 (AN0) for analog function
    TRISBbits.TRISB0 = 1;       // tristate RB0's output driver

    ANSBbits.ANSB1 = 1;         // configure RB1 (AN1) for analog function
    TRISBbits.TRISB1 = 1;       // tristate RB0's output driver

    ANSBbits.ANSB2 = 1;         // configure RB2 (AN2) for analog function
    TRISBbits.TRISB2 = 1;       // tristate RB2's output driver

    ANSBbits.ANSB3 = 1;         // configure RB3 (AN3) for analog function
    TRISBbits.TRISB3 = 1;       // tristate RB3's output driver

    ANSGbits.ANSG9 = 1;         // configure RG9 (DAC1) for analog function
    TRISGbits.TRISG9 = 1;       // tristate RG9's output driver
    DAC1CON = 0x8081;           // enable DAC1, no trigger, and reference is DREF+

    ANSBbits.ANSB13 = 1;        // configure RB13 (DAC2) for analog function
    TRISBbits.TRISB13 = 1;      // tristate RB13's output driver
    DAC2CON = 0x8081;           // enable DAC2, no trigger, and reference is DREF+

    // Configure LED pins as outputs, set to low (off)
    LED1_DIR = OUT; LED1 = OFF;
    LED2_DIR = OUT; LED2 = OFF;
    LED3_DIR = OUT; LED3 = OFF;

    // Configure SW pins as inputs
    SW1_DIR = IN;

    // Configure channel gain pins
    CH1_GAIN_DIR = OUT; CH1_GAIN = 0;
    CH2_GAIN_DIR = OUT; CH2_GAIN = 0;

    set_sweep_in_progress(FALSE);
    set_samples_left(SCOPE_BUFFER_SIZE / 2);
    clear_scope_buffer();

    // Configure DMA module
    DMACON = 0x8000;            // enable DMA peripheral with fixed priority scheme
    DMAL = 0x0000;
    DMAH = 0x2000;

    DMASRC0 = (uint16_t)&ADRES0;
    DMADST0 = (uint16_t)&scope_buffer[0];
    DMACNT0 = SCOPE_BUFFER_SIZE / 2;
    DMAINT0 = 0x2F00;           // set DMA0 trigger to pipeline ADC:
                                //   CHSEL = 0b101111 (pipeline ADC)
    DMACH0 = 0x0215;            // enable DMA CH0 with 
                                //   RELOAD = 1, 
                                //   SAMODE = 0b00 (fixed), 
                                //   DAMODE = 0b01 (increment), 
                                //   TRMODE = 0b01 (repeated one-shot), and 
                                //   SIZE = 0 (word)

    DMASRC1 = (uint16_t)&ADRES1;
    DMADST1 = (uint16_t)&scope_buffer[SCOPE_BUFFER_SIZE / 2];
    DMACNT1 = SCOPE_BUFFER_SIZE / 2;
    DMAINT1 = 0x2F00;           // set DMA1 trigger to pipeline ADC:
                                //   CHSEL = 0b101111 (pipeline ADC)
    DMACH1 = 0x0215;            // enable DMA CH1 with 
                                //   RELOAD = 1, 
                                //   SAMODE = 0b00 (fixed), 
                                //   DAMODE = 0b01 (increment), 
                                //   TRMODE = 0b01 (repeated one-shot), and 
                                //   SIZE = 0 (word)

    IFS0bits.DMA1IF = 0;
    IEC0bits.DMA1IE = 1;

    set_max_avg(4);
    set_num_avg(0);

    // Configure pipelined ADC module
    ADCON1 = 0x0001;                // configure pipelined ADC module with
                                    //     FORM = 0000 (integer, raw data), 
                                    //     PUMPEN = 0 (charge pump disabled), 
                                    //     PWRLVL = 1 (full power, 1-10MHz clk)
    ADCON2 = 0x4700;                //     PVCFG = 01 (ADREF+ is ext VREF+),
                                    //     NVCFG = 0 (ADREF- is AVSS),
                                    //     BUFORG = 1 (buffer is indexed),
                                    //     ADPWR = 11 (ADC is always powered),
                                    //     BUFINT = 00 (no buffer interrupt),
                                    //     REFPUMP = 0 (ref chg pump disabled)
    ADCON3 = 0x0001;                //     ADRC = 0 (ADC clock from sys clock), 
                                    //     ADCS = 00000001 (TAD = 2*TSYS, 8MHz)

    ADL0CONH = 0xA040;              // configure sample list 0 with
                                    //     ASEN = 1 (auto-scan enabled),
                                    //     SLINT = 01 (int after auto-scan done),
                                    //     WM = 00 (all conversion results saved),
                                    //     CM = 000 (threshold matching disabled), 
                                    //     CTMEN = 0 (CTMU not used as Isrc),
                                    //     PINTRIS = 1 (IO pin high-Z during samp),
                                    //     MULCHEN = 0 (only one channel selected),
                                    //     SAMC = 00000 (TSAMP = 0.5*TAD)

    ADL0CONL = 0x0581;              //     SLENCLR = 0 (SLEN cleared by software), 
                                    //     SLTSRC = 00101 (trigger on Timer2), 
                                    //     THSRC = 1 (thresh comp from samp list thresh reg),
                                    //     SLSIZE = 00001 (samp list size = 2)

    ADL0PTR = 0;                    // sample list starts from first entry

    ADTBL = (uint16_t *)&ADTBL0;
    for (i = 0; i < 32; i++) {      // create sample list to alternate between AN1 (A1) and AN2 (A2)
        ADTBL[i++] = 1;
        ADTBL[i] = 2;
    }

    ADCON1bits.ADON = 1;            // enable ADC module
    while (ADSTATHbits.ADREADY == 0) {}     // wait until ADC module is ready

    ADCON1bits.ADCAL = 1;           // start ADC module calibration
    while (ADSTATHbits.ADREADY == 0) {}     // wait until ADC module is ready

    ADL0CONLbits.SAMP = 1;          // close sampling switch

    ADCON3bits.SLEN0 = 1;           // enable sample list 0 in ADCON3
    ADL0CONLbits.SLEN = 1;          // enable sample list 0

    set_period(15, 0);              // set Timer2 frequency to 1 MHz
//    set_period(159, 0);             // set Timer2 frequency to 100 kHz

    // Initialize the waveform generator
    init_wavegen();

    // Configure initial PWM frequencies to 1 kHz and duty cycles to 50%
    OC1RS = 15999;
    OC1R = 7999;
    OC1TMR = 0;

    OC2RS = 15999;
    OC2R = 7999;
    OC2TMR = 0;

    OC3RS = 15999;
    OC3R = 7999;
    OC3TMR = 0;

    OC4RS = 15999;
    OC4R = 7999;
    OC4TMR = 0;

    // Configure Timer1 to have a period of 20 ms
    T1CON = 0x0010;
    PR1 = 0x9C3F;

    TMR1 = 0;
    T1CONbits.TON = 1;
}

