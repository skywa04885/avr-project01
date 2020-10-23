/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#include "../include.h"

#ifndef _MODULES_IO_H
#define _MODULES_IO_H

typedef enum {
  IO_INPUT, IO_OUTPUT, IO_INPUT_PULLUP
} io_mode_t;

void io_mode(
  volatile uint8_t *ddr, volatile uint8_t *port, uint8_t n, 
  io_mode_t mode
);

void io_high(volatile uint8_t *port, uint8_t n);
void io_low(volatile uint8_t *port, uint8_t n);
void io_toggle(volatile uint8_t *port, uint8_t n);

bool io_read(volatile uint8_t *pin, uint8_t n);

#endif
