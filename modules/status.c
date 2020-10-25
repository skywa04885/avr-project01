#include "status.h"

void status_init() {
  io_mode(&STATUS_DDR, &STATUS_PORT, STATUS_LED_BUS, IO_OUTPUT);
  io_mode(&STATUS_DDR, &STATUS_PORT, STATUS_LED_LOOP, IO_OUTPUT);
  io_mode(&STATUS_DDR, &STATUS_PORT, STATUS_LED_ERROR, IO_OUTPUT);

  io_mode(&STATUS_C_DDR, &STATUS_C_PORT, STATUS_C_RED, IO_OUTPUT);
  io_mode(&STATUS_C_DDR, &STATUS_C_PORT, STATUS_C_GREEN, IO_OUTPUT);
  io_mode(&STATUS_C_DDR, &STATUS_C_PORT, STATUS_C_BLUE, IO_OUTPUT);
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

// ===========================

void status_c_red_on() {
  io_low(&STATUS_C_PORT, STATUS_C_BLUE);
  io_low(&STATUS_C_PORT, STATUS_C_GREEN);

  io_high(&STATUS_C_PORT, STATUS_C_RED);
}

void status_c_blue_on() {
  io_low(&STATUS_C_PORT, STATUS_C_GREEN);
  io_low(&STATUS_C_PORT, STATUS_C_RED);

  io_high(&STATUS_C_PORT, STATUS_C_BLUE);
}

void status_c_green_on() {
  io_low(&STATUS_C_PORT, STATUS_C_BLUE);
  io_low(&STATUS_C_PORT, STATUS_C_RED);

  io_high(&STATUS_C_PORT, STATUS_C_GREEN);
}