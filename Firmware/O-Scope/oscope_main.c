#include "oscope.h"
#include "parser.h"
#include "usb.h"
#include "cdc.h"

void set_config_callback(void) {
    USB_setup_class_callback = cdc_setup_callback;

    BD[EP1IN].bytecount = 0;
    BD[EP1IN].address = EP1_IN_buffer;
    BD[EP1IN].status = UOWN | DTS | DTSEN;
    U1EP1 = ENDPT_IN_ONLY;

    BD[EP2OUT].bytecount = 64;
    BD[EP2OUT].address = EP2_OUT_buffer;
    BD[EP2OUT].status = UOWN | DTSEN;
    USB_out_callbacks[2] = cdc_rx_service;

    BD[EP2IN].bytecount = 0;
    BD[EP2IN].address = EP2_IN_buffer;
    BD[EP2IN].status = UOWN | DTS | DTSEN;
    U1EP2 = ENDPT_NON_CONTROL;
    USB_in_callbacks[2] = cdc_tx_service;
}

int16_t main(void) {
    init_oscope();
    init_parser();

    init_cdc();
    USB_set_config_callback = set_config_callback;
    init_usb();

    while (USB_USWSTAT != CONFIG_STATE) {
#ifndef USB_INTERRUPT
        usb_service();
#endif
    }
    while (1) {
        parser_state();
#ifndef USB_INTERRUPT
        usb_service();
#endif
    }
}

