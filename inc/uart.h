#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *s);
void uart_send_binary(const uint8_t *data, uint16_t len);

#endif // UART_H
