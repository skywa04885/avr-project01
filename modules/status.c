#include "status.h"

void status_init() {
  io_mode(&STATUS_DDR, &STATUS_PORT, STATUS_LED_BUS, IO_OUTPUT);
  io_mode(&STATUS_DDR, &STATUS_PORT, STATUS_LED_LOOP, IO_OUTPUT);
  io_mode(&STATUS_DDR, &STATUS_PORT, STATUS_LED_ERROR, IO_OUTPUT);
}

void status_enable_error() {
  io_high(&STATUS_PORT, STATUS_LED_ERROR);
}

void status_disable_error() {
  io_low(&STATUS_PORT, STATUS_LED_ERROR);
}

// ===========================

void status_enable_loop() {
  io_high(&STATUS_PORT, STATUS_LED_LOOP);
}

void status_disable_loop() {
  io_low(&STATUS_PORT, STATUS_LED_LOOP);
}

// ===========================

void status_enable_bus() {
  io_high(&STATUS_PORT, STATUS_LED_BUS);
}

void status_disable_bus() {
  io_low(&STATUS_PORT, STATUS_LED_BUS);
}