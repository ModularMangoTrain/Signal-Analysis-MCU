#include "fft.h"
#include "sampler.h"
#include "signal_gen.h"
#include "uart.h"
#include "config.h"

#include <stdio.h>

/* Simple blocking FFT implementation (complex, radix-2 iterative) */

static float real[FFT_SIZE];
static float imag[FFT_SIZE];

/* Pre-computed trig table for 128-point FFT */
static const float cos_table[7] = {-1.0f, -0.707107f, -0.382683f, -0.195090f, -0.098017f, -0.049068f, -0.024541f};
static const float sin_table[7] = {0.0f, -0.707107f, -0.923880f, -0.980785f, -0.995185f, -0.998795f, -0.999699f};

static void fft_compute(float *re, float *im, uint16_t n) {
    /* bit-reverse reorder */
    uint16_t i, j, k;
    for(i = 1, j = 0; i < n; ++i) {
        k = n >> 1;
        for(; j & k; k >>= 1) j ^= k;
        j ^= k;
        if(i < j) {
            float tr = re[i]; re[i] = re[j]; re[j] = tr;
            float ti = im[i]; im[i] = im[j]; im[j] = ti;
        }
    }

    uint8_t stage = 0;
    for(uint16_t len = 2; len <= n; len <<= 1, stage++) {
        float wlen_r = cos_table[stage];
        float wlen_i = sin_table[stage];
        for(i = 0; i < n; i += len) {
            float wr = 1.0f;
            float wi = 0.0f;
            for(uint16_t m = 0; m < (len>>1); ++m) {
                uint16_t u = i + m;
                uint16_t v = i + m + (len>>1);
                float xr = re[u];
                float xi = im[u];
                float yr = re[v] * wr - im[v] * wi;
                float yi = re[v] * wi + im[v] * wr;

                re[u] = xr + yr;
                im[u] = xi + yi;
                re[v] = xr - yr;
                im[v] = xi - yi;

                float nwr = wr * wlen_r - wi * wlen_i;
                float nwi = wr * wlen_i + wi * wlen_r;
                wr = nwr; wi = nwi;
            }
        }
    }
}

void fft_task_init(void) {
    /* nothing for now */
}

void fft_task_run(void) {
    if(!sampler_is_full()) return;

    int16_t *buf = sampler_get_buffer();
    /* copy into float arrays */
    for(uint16_t i = 0; i < FFT_SIZE; ++i) {
        real[i] = (float)buf[i];
        imag[i] = 0.0f;
    }

    fft_compute(real, imag, FFT_SIZE);

    /* find peak bin by magnitude squared (avoid sqrt) */
    float peak = 0.0f;
    uint16_t peak_bin = 0;
    for(uint16_t i = 1; i < FFT_SIZE/2; ++i) {
        float mag_sq = real[i]*real[i] + imag[i]*imag[i];
        if(mag_sq > peak) { peak = mag_sq; peak_bin = i; }
    }

    float freq_res = (float)SAMPLE_RATE / (float)FFT_SIZE;
    float peak_freq = peak_bin * freq_res;

    /* Print peak frequency */
    char bufstr[64];
    int len = snprintf(bufstr, sizeof(bufstr), "FFT peak: bin=%u freq=%u Hz\r\n", (unsigned)peak_bin, (unsigned)peak_freq);
    uart_send_binary((uint8_t*)bufstr, len);

    /* clear sampler to collect next block */
    sampler_clear();
}
