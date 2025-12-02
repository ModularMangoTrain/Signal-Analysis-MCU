#include "fft.h"
#include "scheduler.h"
#include <stdio.h>

static fft_result_t result;

void fft_task_init(void) {
    result.dominant_freq = 0.0f;
    result.magnitude = 0.0f;
}

void fft_task_run(float *buffer_ptr) {
    // FFT placeholder - stores mock result
    result.dominant_freq = 440.0f;
    result.magnitude = 1.0f;
    
    printf("FFT: Detected %.0f Hz\n", result.dominant_freq);
}

fft_result_t fft_task_get_results(void) {
    return result;
}
