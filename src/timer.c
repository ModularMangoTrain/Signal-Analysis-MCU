#include "timer.h"
#include "scheduler.h"
#include "signal_gen.h"
#include "sampler.h"
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void timer_init_1ms_tick(void) {
    cli();
    /* Timer1 CTC mode, prescaler 64 -> 12MHz/64 = 187.5kHz -> OCR1A for 1ms = 186 */
    TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10); // CTC, prescale 64
    OCR1A = 186;  // (12000000 / 64 / 1000) - 1 = 186.5
    TIMSK1 |= (1<<OCIE1A);
    sei();
}

ISR(TIMER1_COMPA_vect) {
    scheduler_tick();
    
    // Sample at exactly 1000 Hz from ISR
    int16_t s = signal_gen_next_sample();
    sampler_add_sample(s);
}
