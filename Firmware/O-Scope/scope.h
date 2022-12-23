
#ifndef _SCOPE_H_
#define _SCOPE_H_

#include "pic24fj.h"
#include "common.h"
#include <stdint.h>

#define SCOPE_BUFFER_SIZE   3000

typedef void (*TRIGGER_SWEEP_T)(void);

extern TRIGGER_SWEEP_T trigger_sweep;
extern uint16_t scope_buffer[SCOPE_BUFFER_SIZE];

void cancel_sweep(void);
void clear_scope_buffer(void);
void set_period(uint16_t value1, uint16_t value2);
void set_sweep_in_progress(uint16_t value);
uint16_t get_sweep_in_progress(void);
void set_samples_left(uint16_t value);
uint16_t get_samples_left(void);
void set_max_avg(uint16_t value);
uint16_t get_max_avg(void);
void set_num_avg(uint16_t value);
uint16_t get_num_avg(void);

#endif
