/**
 * @file fft.h
 * @brief FFT task interface for frequency analysis
 */

#ifndef FFT_H
#define FFT_H

#include <stdint.h>

/**
 * @brief Initialize FFT module
 */
void fft_task_init(void);

/**
 * @brief Run FFT analysis on sampled data
 * 
 * Performs 128-point FFT and outputs peak frequency via UART.
 * Must be called after sampler buffer is full.
 */
void fft_task_run(void);

#endif
