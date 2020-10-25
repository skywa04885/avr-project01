/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#ifndef _MODULES_COLOR_H
#define _MODULES_COLOR_H

#include "../include.h"
#include "io.h"
#include "status.h"

typedef enum {
  MEASURE_RED, MEASURE_GREEN, MEASURE_BLUE
} color_sensor_measurement_t;

typedef enum {
  CRES_RED, CRES_BLUE, CRES_GREEN, CRES_YELLOW, CRES_WHITE
} color_sensor_cres_t;

typedef struct {
  volatile uint8_t *port, *ddr, *pin;
  uint8_t out, s0, s1, s2, s3;
} color_sensor_t;

typedef struct {
  uint16_t r, g, b;
} color_sensor_ret_t;

void color_sensor_init(color_sensor_t *sensor);
color_sensor_cres_t color_sensor_make_sense(color_sensor_ret_t *idk);

uint16_t color_sensor_measure(
  color_sensor_t *sensor, 
  color_sensor_measurement_t m
);

color_sensor_ret_t color_sensor_read(color_sensor_t *sensor);

#endif
