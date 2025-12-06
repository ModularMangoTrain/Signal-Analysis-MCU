#ifndef SAMPLER_H
#define SAMPLER_H

#include <stdint.h>
#include <stdbool.h>

void sampler_init(int16_t *buffer, uint16_t size);
void sampler_add_sample(int16_t s);
bool sampler_is_full(void);
int16_t *sampler_get_buffer(void);
void sampler_clear(void);

#endif
