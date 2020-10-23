/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#include "a1602.h"

void a1602_init() {
  io_mode(&A1602_REST_DDR, &A1602_REST_PORT, A1602_REST_RS, IO_OUTPUT);
  io_mode(&A1602_REST_DDR, &A1602_REST_PORT, A1602_REST_E, IO_OUTPUT);
  io_mode(&A1602_REST_DDR, &A1602_REST_PORT, A1602_REST_RW, IO_OUTPUT);

  io_low(&A1602_REST_PORT, A1602_REST_RS);
}

void a1602_bus_mode(io_mode_t mode) {
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D0, mode);
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D1, mode);
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D2, mode);
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D3, mode);
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D4, mode);
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D5, mode);
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D6, mode);
  io_mode(&A1602_BUS_DDR, &A1602_BUS_PORT, A1602_BUS_D7, mode);
}

void a1602_instruction_write(uint8_t byte) {
  // Enables the BUS led, and sets the bus mode to output
  status_enable_bus();
  a1602_bus_mode(IO_OUTPUT);

  // Sets the mode to write, after which we wait for the address
  //  setup time
  io_high(&A1602_REST_PORT, A1602_REST_RW);       // Goes to read mode
  io_low(&A1602_REST_PORT, A1602_REST_RW);        // Goes to write mode
  _delay_us(A1602_WRM_AST);

  // Sets the enable pin high, and writes the byte to the bus
  io_high(&A1602_REST_PORT, A1602_REST_E);        // Sets the enable pin
  A1602_BUS_PORT = byte;                          // Writes the byte to bus
  _delay_us(A1602_WRM_EPW);                       // Waits for enable finish
  io_low(&A1602_REST_PORT, A1602_REST_E);         // Enable pi nlow

  // Sets the enable pin low and waits some time for the data to be 
  //  processed, after which we go back to read mode
  _delay_us(A1602_WRM_DHT);                       // Waits the hold time
  io_high(&A1602_REST_PORT, A1602_REST_RW);       // Sets mode to read

  // Sets the bus mode to input, and disables the LED
  a1602_bus_mode(IO_INPUT);
  status_disable_bus();
}

void a1602_write_char(char c) {
  io_high(&A1602_REST_PORT, A1602_REST_RS);
  a1602_instruction_write(c);
  io_low(&A1602_REST_PORT, A1602_REST_RS);
}

void a1602_write_string(const char *str) {
  uint8_t line_len = 0;
  while (*str != '\0') {
    if (++line_len > 16) break;

    a1602_write_char(*str++);
    _delay_us(A1602_DLY_SCG);
  }
}
