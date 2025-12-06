#include "timer.h"
#include "scheduler.h"
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void timer_init_1ms_tick(void) {
    cli();
    /* Timer1 CTC mode, prescaler 64 -> 16MHz/64 = 250kHz -> OCR1A for 1ms = 250 */
    TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10); // CTC, prescale 64
    OCR1A = (uint16_t)((F_CPU_HZ / 64UL) / (1000UL) - 1UL);
    TIMSK1 |= (1<<OCIE1A);
    sei();
}

ISR(TIMER1_COMPA_vect) {
    scheduler_tick();
}
