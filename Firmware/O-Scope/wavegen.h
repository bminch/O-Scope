
#ifndef _WAVEGEN_H_
#define _WAVEGEN_H_

#include "pic24fj.h"
#include "common.h"
#include <stdint.h>

// AD9837 DDS registers
#define AD9837_CONTROL      0x0000
#define AD9837_14FREQ0      0x4000
#define AD9837_14FREQ1      0x8000
#define AD9837_12PHASE0     0xC000
#define AD9837_12PHASE1     0xE000

// AD9837 DDS control register bit definitions
#define AD9837_B28          0x2000
#define AD9837_HLB          0x1000
#define AD9837_FSEL         0x0800
#define AD9837_PSEL         0x0400
#define AD9837_RESET        0x0100
#define AD9837_SLEEP1       0x0080
#define AD9837_SLEEP12      0x0040
#define AD9837_OPBITEN      0x0020
#define AD9837_DIV2         0x0008
#define AD9837_MODE         0x0002

// Wavegen wave shape definitions
#define DC                  0
#define SIN                 1
#define SQUARE              2
#define TRIANGLE            3

// Wavegen offset mode definitions
#define SINGLE              0
#define REPEAT              1

// Wavegen offset sample memory definitions
#define WAVEGEN_OFFSET_NUM_SAMPLES  0x10400
#define WAVEGEN_OFFSET_SAMPLE_MEM   0x10402

void init_wavegen(void);
void set_wg_gain(uint16_t value);
uint16_t get_wg_gain(void);
void set_nsq(uint16_t value);
uint16_t get_nsq(void);
void spi_out_dds(uint16_t value);
void spi_out_pot(uint8_t value);
void set_shape(uint16_t value);
uint16_t get_shape(void);
void set_freq(uint16_t value_l, uint16_t value_h);
uint16_t get_freq_l(void);
uint16_t get_freq_h(void);
void set_phase(uint16_t value);
uint16_t get_phase(void);
void set_amplitude(uint16_t value);
uint16_t get_amplitude(void);
void set_offset(uint16_t value);
uint16_t get_offset(void);
void set_sq_offset_adj(uint16_t value);
uint16_t get_sq_offset_adj(void);
void set_nsq_offset_adj(uint16_t value);
uint16_t get_nsq_offset_adj(void);

void wavegen_offset_set_interval(uint16_t value1, uint16_t value2);
void wavegen_offset_set_mode(uint16_t value);
uint16_t wavegen_offset_get_mode(void);
void wavegen_offset_start(void);
void wavegen_offset_stop(void);
uint16_t wavegen_offset_get_samples_left(void);
#endif

