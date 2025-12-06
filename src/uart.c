#include "uart.h"
#include <avr/io.h>

void uart_init(void) {
    // Set pin directions: PD1 as output (TXD), PD0 as input (RXD)
    DDRD |= (1 << PD1);
    DDRD &= ~(1 << PD0);
    
    // Manual baud rate calculation for 12MHz, 9600 baud
    UBRR0H = 0;
    UBRR0L = 77;  // 12000000 / (16 * 9600) - 1 = 77.083 → 77
    
    // Enable transmitter and receiver, 8-bit data
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8N1
}

void uart_putc(char c) {
    while (!(UCSR0A & (1 << UDRE0))); // Wait for buffer empty
    UDR0 = (uint8_t)c;
}

void uart_puts(const char *s) {
    while (*s) {
        uart_putc(*s++);
    }
}

void uart_send_binary(const uint8_t *data, uint16_t len) {
    for(uint16_t i = 0; i < len; i++) {
        uart_putc((char)data[i]);
    }
}
