#include "io.h"

void io_mode(
  volatile uint8_t *ddr, volatile uint8_t *port, uint8_t n, 
  io_mode_t mode
) {
  if (mode == IO_INPUT || mode == IO_INPUT_PULLUP) *ddr &= ~(1 << n);
  else if (mode == IO_OUTPUT) {
    *ddr |= (1 << n);
    return;
  }

  if (mode == IO_INPUT_PULLUP) *port |= (1 << n);
  else *port &= ~(1 << n);
}

void io_high(volatile uint8_t *port, uint8_t n) {
  *port |= (1 << n);
}

void io_low(volatile uint8_t *port, uint8_t n) {
  *port &= ~(1 << n);
}

void io_toggle(volatile uint8_t *port, uint8_t n) {
  *port ^= (1 << n);
}

bool io_read(volatile uint8_t *pin, uint8_t n) {
  return *pin & (1 << n);
}