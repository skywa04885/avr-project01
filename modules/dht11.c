#include "dht11.h"

void dht11_init(dht11_t *dht) {
  io_mode(dht->ddr, dht->port, dht->n, IO_OUTPUT);
  io_high(dht->port, dht->n);
}

void dht11_start_signal(dht11_t *dht) {
  io_low(dht->port, dht->n);
  _delay_us(DHT11_DEL_STA);
}

void dht11_stop_signal(dht11_t *dht) {
  io_mode(dht->ddr, dht->port, dht->n, IO_OUTPUT);
  io_high(dht->port, dht->n);
}

bool dht11_await_response(dht11_t *dht) {
  status_enable_loop();

  io_mode(dht->ddr, dht->port, dht->n, IO_INPUT);
  while (io_read(dht->pin, dht->n) == true);    // Wait for pull down
  while (io_read(dht->pin, dht->n) == false);   // Wait for pull up
  while (io_read(dht->pin, dht->n) == true);    // Wait for pull down

  status_disable_loop();
}

bool dht11_read_bytes(dht11_t *dht, uint8_t *bytes) {
  // Reads all the five bytes into memory, after which
  //  we can process them further
  for (uint8_t i = 0; i < 5; ++i)
    bytes[i] = dht11_read_byte(dht);
}

uint8_t dht11_read_byte(dht11_t *dht) {
  uint8_t result = 0;

  for (uint8_t i = 0; i < 8; ++i) {
    while(io_read(dht->pin, dht->n) == false);
    _delay_us(30);

    result <<= 1;

    if (io_read(dht->pin, dht->n) == true) result |= 1;
    while(io_read(dht->pin, dht->n) == true);
  }

  return result;
}

uint8_t dht11_calculate_checksum(uint8_t *bytes) {
  // Sums the data of all the bytes, in order to generate the 
  //  checksum, and later validate the data
  return bytes[0] + bytes[1] + bytes[2] + bytes[3];
}

dht11_ret_t dht11_read(dht11_t *dht) {
  uint8_t bytes[5];
  dht11_ret_t ret;
  ret.success = true;

  // Sensd the start signal, after which we wait for the
  //  client to generate the data, and send it over to us
  dht11_start_signal(dht);
  dht11_await_response(dht);

  // Reads the bytes from the sensor
  dht11_read_bytes(dht, bytes);
  ret.h_dec = bytes[1];
  ret.h_int = bytes[0];
  ret.t_dec = bytes[3];
  ret.t_int = bytes[2];
  ret.sum   = bytes[4];

  // Calculats the checksum to later validate if the data
  //  transmission was successfull
  ret.csum = dht11_calculate_checksum(bytes);

  // Sends the stop signal, and returns the result measurement
  dht11_stop_signal(dht);

  return ret;
}
