#ifndef FFT_H
#define FFT_H

#include <stdint.h>

typedef struct {
    float dominant_freq;
    float magnitude;
} fft_result_t;

void fft_task_init(void);
void fft_task_run(float *buffer_ptr);
fft_result_t fft_task_get_results(void);

#endif
