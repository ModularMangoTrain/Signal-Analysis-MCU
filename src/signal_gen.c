#include "signal_gen.h"
#include "config.h"
#include <avr/pgmspace.h>

/* 20-sample sine table for 50 Hz at 1000 Hz sampling rate */
static const int16_t sine_table[20] PROGMEM = {
    0, 9755, 18541, 25000, 28531, 28531, 25000, 18541, 9755, 0,
    -9755, -18541, -25000, -28531, -28531, -25000, -18541, -9755, 0, 0
};

static volatile uint8_t idx = 0;

void signal_gen_init(void) {
    idx = 0;
}

int16_t signal_gen_next_sample(void) {
    int16_t v = (int16_t)pgm_read_word(&sine_table[idx]);
    idx++;
    if (idx >= 20) idx = 0;
    return v;
}
