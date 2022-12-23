#ifndef _CDC_H_
#define _CDC_H_

#include "usb.h"

#define TX_BUFFER_SIZE      256
#define RX_BUFFER_SIZE      256

// CDC Class requests
#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01
#define SET_COMM_FEATURE            0x02
#define GET_COMM_FEATURE            0x03
#define CLEAR_COMM_FEATURE          0x04
#define SET_AUX_LINE_STATE          0x10
#define SET_HOOK_STATE              0x11
#define PULSE_SETUP                 0x12
#define SEND_PULSE                  0x13
#define SET_PULSE_TIME              0x14
#define RING_AUX_JACK               0x15
#define SET_LINE_CODING             0x20
#define GET_LINE_CODING             0x21
#define SET_CONTROL_LINE_STATE      0x22
#define SEND_BREAK                  0x23
#define SET_RINGER_PARMS            0x30
#define GET_RINGER_PARMS            0x31
#define SET_OPERATION_PARMS         0x32
#define GET_OPERATION_PARMS         0x33
#define SET_LINE_PARMS              0x34
#define GET_LINE_PARMS              0x35
#define DIAL_DIGITS                 0x36
#define SET_UNIT_PARAMETER          0x37
#define GET_UNIT_PARAMETER          0x38
#define CLEAR_UNIT_PARAMETER        0x39
#define GET_PROFILE                 0x3A
#define SET_ETHERNET_MULTICAST_FILTERS  0x40
#define SET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER    0x41
#define GET_ETHERNET_POWER_MANAGEMENT_PATTERN_FILTER    0x42
#define SET_ETHERNET_PACKET_FILTER  0x43
#define GET_ETHERNET_STATISTIC      0x44
#define SET_ATM_DATA_FORMAT         0x50
#define GET_ATM_DEVICE_STATISTICS   0x51
#define SET_ATM_DEFAULT_VC          0x52
#define GET_ATM_VC_STATISTICS       0x53

// CDC Notification codes
#define NETWORK_CONNECTION          0x00
#define RESPONSE_AVAILABLE          0x01
#define AUX_JACK_HOOK_STATE         0x08
#define RING_DETECT                 0x09
#define SERIAL_STATE                0x20
#define CALL_STATE_CHANGE           0x28
#define LINE_STATE_CHANGE           0x29
#define CONNECTION_SPEED_CHANGE     0x2A

extern uint8_t EP1_IN_buffer[];
extern uint8_t EP2_OUT_buffer[];
extern uint8_t EP2_IN_buffer[];

void init_cdc(void);
uint16_t cdc_in_waiting(void);
uint16_t cdc_tx_buffer_space(void);
void cdc_putc(uint8_t ch);
uint8_t cdc_getc(void);
void cdc_puts(uint8_t *str);
void cdc_gets(uint8_t *str, uint16_t len);
void cdc_gets_term(uint8_t *str, uint16_t len);
void cdc_tx_service(void);
void cdc_rx_service(void);
void cdc_setup_callback(void);

#endif
