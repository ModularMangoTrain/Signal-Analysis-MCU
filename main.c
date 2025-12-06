#include "config.h"
#include "scheduler.h"
#include "signal_gen.h"
#include "sampler.h"
#include "fft.h"
#include "uart.h"
#include "timer.h"

#include <avr/io.h>
#include <util/delay.h>

static int16_t sample_buffer[FFT_SIZE];

static void sample_task(void) {
    int16_t s = signal_gen_next_sample();
    sampler_add_sample(s);
}

static void blink_task(void) {
    PORTB ^= (1<<PB0);
}

int main(void) {
    uart_init();
    uart_puts("Mini-RTOS-DSP-FFT starting...\r\n");

    signal_gen_init();
    sampler_init(sample_buffer, FFT_SIZE);
    fft_task_init();
    scheduler_init();
    timer_init_1ms_tick();

    DDRB |= (1<<PB0);

    scheduler_add_task(sample_task, 1);        // 1ms = 1000 Hz sampling
    scheduler_add_task(fft_task_run, 50);      // FFT every 50ms
    scheduler_add_task(blink_task, 500);       // Blink every 500ms

    uart_puts("Entering main loop\r\n");
    while(1) {
        scheduler_dispatch();
        _delay_ms(1);
    }
    return 0;
}
