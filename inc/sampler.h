#ifndef SAMPLER_H
#define SAMPLER_H

#include <stdint.h>

void sampler_init(float *buffer_ptr);
void sampler_add_sample(float sample);
uint8_t sampler_buffer_full(void);
void sampler_reset(void);

#endif
