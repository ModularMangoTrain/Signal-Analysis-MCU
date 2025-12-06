#include "sampler.h"
#include "config.h"
#include <string.h>
#include <stdbool.h>

static int16_t *buf_ptr = 0;
static uint16_t buf_size = 0;
static uint16_t write_idx = 0;
static uint8_t full_flag = 0;

void sampler_init(int16_t *buffer, uint16_t size) {
    buf_ptr = buffer;
    buf_size = size;
    write_idx = 0;
    full_flag = 0;
    memset(buf_ptr, 0, sizeof(int16_t) * buf_size);
}

void sampler_add_sample(int16_t s) {
    if(!buf_ptr) return;
    buf_ptr[write_idx++] = s;
    if(write_idx >= buf_size) {
        write_idx = 0;
        full_flag = 1;
    }
}

bool sampler_is_full(void) {
    return full_flag != 0;
}

int16_t *sampler_get_buffer(void) {
    return buf_ptr;
}

void sampler_clear(void) {
    full_flag = 0;
}
