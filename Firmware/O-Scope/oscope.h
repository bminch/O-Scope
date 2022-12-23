
#ifndef _OSCOPE_H_
#define _OSCOPE_H_

#include "pic24fj.h"
#include "common.h"
#include <stdint.h>

// LED pin definitions
#define LED1                LATEbits.LATE3
#define LED2                LATEbits.LATE4
#define LED3                LATEbits.LATE5

#define LED1_DIR            TRISEbits.TRISE3
#define LED2_DIR            TRISEbits.TRISE4
#define LED3_DIR            TRISEbits.TRISE5

// Tactile switch pin definitions
#define SW1                 PORTCbits.RC15

#define SW1_DIR             TRISCbits.TRISC15

// Digital header pin definitions
#define D0                  PORTFbits.RF4
#define D1                  PORTFbits.RF5
#define D2                  PORTDbits.RD9
#define D3                  PORTDbits.RD10

#define D0_DIR              TRISFbits.TRISF4
#define D1_DIR              TRISFbits.TRISF5
#define D2_DIR              TRISDbits.TRISD9
#define D3_DIR              TRISDbits.TRISD10

#define D0_LAT              LATFbits.LATF4
#define D1_LAT              LATFbits.LATF5
#define D2_LAT              LATDbits.LATD9
#define D3_LAT              LATDbits.LATD10

#define D0_RP               10
#define D1_RP               17
#define D2_RP               4
#define D3_RP               3

#define D0_OD               ODCFbits.ODF4
#define D1_OD               ODCFbits.ODF5
#define D2_OD               ODCDbits.ODD9
#define D3_OD               ODCDbits.ODD10

#define D0_PU               CNPU2bits.CN17PUE
#define D1_PU               CNPU2bits.CN18PUE
#define D2_PU               CNPU4bits.CN54PUE
#define D3_PU               CNPU4bits.CN55PUE

#define D0_PD               CNPD2bits.CN17PDE
#define D1_PD               CNPD2bits.CN18PDE
#define D2_PD               CNPD4bits.CN54PDE
#define D3_PD               CNPD4bits.CN55PDE

// AD9837 DDS interface pin defintions
#define nCS_DDS             LATBbits.LATB12
#define SCK_DDS             PORTBbits.RB14
#define MOSI_DDS            PORTBbits.RB15
#define MISO_DDS            PORTBbits.RB4
#define MCLK_DDS            PORTFbits.RF3

#define nCS_DDS_DIR         TRISBbits.TRISB12
#define SCK_DDS_DIR         TRISBbits.TRISB14
#define MOSI_DDS_DIR        TRISBbits.TRISB15
#define MISO_DDS_DIR        TRISBbits.TRISB4
#define MCLK_DDS_DIR        TRISFbits.TRISF3

#define SCK_DDS_RP          14
#define MOSI_DDS_RP         29
#define MISO_DDS_RP         28
#define MCLK_DDS_RP         16

// AD5160 digital potentiometer interface pin definitions
#define nCS_POT             LATCbits.LATC12
#define SCK_POT             PORTDbits.RD11
#define MOSI_POT            PORTDbits.RD8
#define MISO_POT            PORTBbits.RB5

#define nCS_POT_DIR         TRISCbits.TRISC12
#define SCK_POT_DIR         TRISDbits.TRISD11
#define MOSI_POT_DIR        TRISDbits.TRISD8
#define MISO_POT_DIR        TRISBbits.TRISB5

#define SCK_POT_RP          12
#define MOSI_POT_RP         2
#define MISO_POT_RP         18

// Wavegen mode pin defitions
#define nSQUARE             LATDbits.LATD6
#define WG_GAIN             LATEbits.LATE2

#define nSQUARE_DIR         TRISDbits.TRISD6
#define WG_GAIN_DIR         TRISEbits.TRISE2

// Scope channel gain pin definitions
#define CH1_GAIN            LATEbits.LATE1
#define CH2_GAIN            LATEbits.LATE0

#define CH1_GAIN_DIR        TRISEbits.TRISE1
#define CH2_GAIN_DIR        TRISEbits.TRISE0

// Peripheral remappable pin definitions
#define INT1_RP             1
#define INT2_RP             2
#define INT3_RP             3
#define INT4_RP             4

#define MOSI1_RP            7
#define SCK1OUT_RP          8
#define MOSI2_RP            10
#define SCK2OUT_RP          11

#define MISO1_RP            40
#define SCK1IN_RP           41
#define MISO2_RP            44
#define SCK2IN_RP           45

#define OC1_RP              18
#define OC2_RP              19
#define OC3_RP              20
#define OC4_RP              21
#define OC5_RP              22
#define OC6_RP              23
#define OC7_RP              24
#define OC8_RP              25
#define OC9_RP              35

#define U1TX_RP             3
#define U1RTS_RP            4
#define U2TX_RP             5
#define U2RTS_RP            6
#define U3TX_RP             28
#define U3RTS_RP            29
#define U4TX_RP             30
#define U4RTS_RP            31

#define U1RX_RP             36
#define U1CTS_RP            37
#define U2RX_RP             38
#define U2CTS_RP            39
#define U3RX_RP             35
#define U3CTS_RP            43
#define U4RX_RP             54
#define U4CTS_RP            55

// Convenience boolean values definitions
#define FALSE               0
#define TRUE                1

#define OFF                 0
#define ON                  1

#define OUT                 0
#define IN                  1

// Vendor request definitions
#define TOGGLE_LED1         0
#define TOGGLE_LED2         1
#define TOGGLE_LED3         2
#define READ_SW1            3
#define SET_DAC1            5
#define GET_DAC1            6
#define SET_DAC2            7
#define GET_DAC2            8
#define SET_DACS            9
#define GET_DACS            10
#define PULSE_MCP6N11_EN    11
#define TRIGGER             12
#define SET_PERIOD          13
#define GET_PERIOD          14
#define GET_SCOPE_BUFFER    15
#define GET_SWEEP_PROGRESS  16
#define SET_CH1_RANGE       17
#define GET_CH1_RANGE       18
#define SET_CH2_RANGE       19
#define GET_CH2_RANGE       20
#define SET_MAX_AVG         21
#define GET_MAX_AVG         22
#define GET_NUM_AVG         23
#define SET_WG_RANGE        24
#define GET_WG_RANGE        25
#define SET_NSQUARE         26
#define GET_NSQUARE         27
#define SPI_OUT_DDS         28
#define SPI_OUT_POT         29
#define SET_SHAPE_VAL       30
#define GET_SHAPE_VAL       31
#define SET_FREQ_VALS       32
#define GET_FREQ_VALS       33
#define SET_PHASE_VAL       34
#define GET_PHASE_VAL       35
#define SET_AMPLITUDE_VAL   36
#define GET_AMPLITUDE_VAL   37
#define SET_SQ_OFFSET_ADJ   38
#define GET_SQ_OFFSET_ADJ   39
#define SET_NSQ_OFFSET_ADJ  40
#define GET_NSQ_OFFSET_ADJ  41
#define READ_FLASH          42
#define WRITE_FLASH         43
#define ERASE_FLASH         44

void init_oscope(void);

#endif
