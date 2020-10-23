/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#include "usart.h"

static FILE usart_stream = FDEV_SETUP_STREAM(&usart_write_stream, 
  &usart_read_stream, _FDEV_SETUP_RW);

void usart_init() {
  UBRR0L = UBRRL_VALUE;
  UBRR0H = UBRRH_VALUE;

  #if USE_2X
  UCSR0A |= (1 << U2X0);
  #else
  UCSR0A &= ~(1 << U2X0);
  #endif

  UCSR0B = (1 << TXEN0) | (1 << RXEN0);
  UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void usart_setup_streams() {
  stdin = stdout = stderr = &usart_stream;
}

// ===========================

void usart_write_char(char c) {
  if (c == '\n')
    usart_write_char('\r');
  while((UCSR0A & (1 << UDRE0)) == 0);
  UDR0 = c;
}

void usart_write(const char *str) {
  while (*str != '\0')
    usart_write_char(*str++);
}

char usart_read() {
  while((UCSR0A & (1 << RXC0)) == 0);
  return UDR0;
}

// ===========================

void usart_write_stream(char c, FILE *stream) {
  if (c == '\n')
    usart_write_stream('\r', stream);
  while((UCSR0A & (1 << UDRE0)) == 0);
  UDR0 = c;
}

char usart_read_stream(FILE *stream) {
  while((UCSR0A & (1 << RXC0)) == 0);
  return UDR0;
}