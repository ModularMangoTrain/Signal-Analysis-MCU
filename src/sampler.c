#include "sampler.h"
#include "scheduler.h"

static float *buffer;
static uint32_t index = 0;

void sampler_init(float *buffer_ptr) {
    buffer = buffer_ptr;
    index = 0;
}

void sampler_add_sample(float sample) {
    if (index < BUFFER_SIZE) {
        buffer[index++] = sample;
    }
}

uint8_t sampler_buffer_full(void) {
    return (index >= BUFFER_SIZE);
}

void sampler_reset(void) {
    index = 0;
}
