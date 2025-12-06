#include "signal_gen.h"
#include "config.h"
#include <avr/pgmspace.h>

/* Simple sine table, 64 samples, Q15-ish scaled to int16 range */
static const int16_t sine_table[FFT_SIZE] PROGMEM = {
    0, 3211, 6392, 9511, 12539, 15446, 18204, 20787,
    23170, 25329, 27245, 28898, 30273, 31356, 32137, 32610,
    32767, 32610, 32137, 31356, 30273, 28898, 27245, 25329,
    23170, 20787, 18204, 15446, 12539, 9511, 6392, 3211,
    0, -3211, -6392, -9511, -12539, -15446, -18204, -20787,
    -23170, -25329, -27245, -28898, -30273, -31356, -32137, -32610,
    -32767, -32610, -32137, -31356, -30273, -28898, -27245, -25329,
    -23170, -20787, -18204, -15446, -12539, -9511, -6392, -3211
};

static uint16_t idx = 0;

void signal_gen_init(void) {
    idx = 0;
}

int16_t signal_gen_next_sample(void) {
    int16_t v = (int16_t)pgm_read_word(&sine_table[idx]);
    idx = (idx + 1) % FFT_SIZE;
    return v;
}
