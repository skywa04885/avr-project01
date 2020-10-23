/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#ifndef _MODULES_USART_H
#define _MODULES_USART_H

#include "../include.h"

void usart_init();
void usart_setup_streams();

void usart_write_char(char c);
void usart_write(const char *str);
char usart_read();

void usart_write_stream(char c, FILE *stream);
char usart_read_stream(FILE *stream);

#endif
