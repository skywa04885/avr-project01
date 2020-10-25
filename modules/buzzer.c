#include "buzzer.h"

void buzzer_init(buzzer_t *buzz) {
  io_mode(buzz->ddr, buzz->port, buzz->n, IO_OUTPUT);
  io_low(buzz->port, buzz->n);
}

void buzzer_buzz(buzzer_t *buzz, uint16_t ps, uint16_t loops) {
  uint32_t delay = (1000000 / ps) / 2;
  for (uint16_t i = 0; i < loops / 2; ++i) {
    io_high(buzz->port, buzz->n);
    for(uint32_t j = 0; j < delay; ++j) _delay_us(1);
    io_low(buzz->port, buzz->n);
    for(uint32_t j = 0; j < delay; ++j) _delay_us(1);
  }
}