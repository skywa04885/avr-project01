/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#ifndef _MODULES_DHT11_H
#define _MODULES_DHT11_H

#define DHT11_DEL_STA     18000   /* The start signal delay */
#define DHT11_DEL_RSP     40      /* The response delay */
#define DHT11_DEL_DPT     80      /* Data prepare time */
#define DHT11_DEL_STT     50      /* Start to transmit */

#include "../include.h"
#include "io.h"
#include "status.h"

typedef struct {
  uint8_t h_int, h_dec;
  uint8_t t_int, t_dec;
  bool success;
  uint8_t sum, csum;
} dht11_ret_t;

typedef struct {
  volatile uint8_t *port, *ddr, *pin;
  uint8_t n;
} dht11_t;

void dht11_init(dht11_t *dht);
void dht11_start_signal(dht11_t *dht);
void dht11_stop_signal(dht11_t *dht);
bool dht11_await_response(dht11_t *dht);
bool dht11_read_bytes(dht11_t *dht, uint8_t *bytes);
uint8_t dht11_read_byte(dht11_t *dht);
uint8_t dht11_calculate_checksum(uint8_t *bytes);
dht11_ret_t dht11_read(dht11_t *dht);

#endif
