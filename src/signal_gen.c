#include "signal_gen.h"
#include "scheduler.h"
#include <math.h>

static float freq;
static float amp;
static uint32_t sample_index = 0;

void signal_gen_init(float frequency, float amplitude) {
    freq = frequency;
    amp = amplitude;
    sample_index = 0;
}

float signal_gen_next_sample(void) {
    float t = (float)sample_index / SAMPLE_RATE;
    float sample = amp * sinf(2.0f * M_PI * freq * t);
    sample_index++;
    return sample;
}
