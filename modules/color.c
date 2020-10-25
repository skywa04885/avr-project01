#include "color.h"

void color_sensor_init(color_sensor_t *sensor) {
  io_mode(sensor->ddr, sensor->port, sensor->out, IO_INPUT);

  io_mode(sensor->ddr, sensor->port, sensor->s0, IO_OUTPUT);
  io_mode(sensor->ddr, sensor->port, sensor->s1, IO_OUTPUT);
  io_mode(sensor->ddr, sensor->port, sensor->s2, IO_OUTPUT);
  io_mode(sensor->ddr, sensor->port, sensor->s3, IO_OUTPUT);
}

uint16_t color_sensor_measure(
  color_sensor_t *sensor, 
  color_sensor_measurement_t m
) {
  status_enable_loop();

  io_high(sensor->port, sensor->s0);
  io_low(sensor->port, sensor->s1);

  /*
    Tells the sensor which color we want to measure
  */

  if (m == MEASURE_RED) {
    io_low(sensor->port, sensor->s2);
    io_low(sensor->port, sensor->s3);
  } else if (m == MEASURE_GREEN) {
    io_high(sensor->port, sensor->s2);
    io_high(sensor->port, sensor->s3);
  } else if (m == MEASURE_BLUE) {
    io_low(sensor->port, sensor->s2);
    io_high(sensor->port, sensor->s3);
  }

  /*
    Measures the frequency of the sensor
  */

  // Waits until we've received an valid pulse from
  //  the sensor
  while(io_read(sensor->pin, sensor->out) == true);
  while(io_read(sensor->pin, sensor->out) == false);
  TCNT1 ^= TCNT1;
  TCCR1B = (1 << CS11);

  // Waits until the pulse is low again, and stops the timer
  //  which allows us to read the time the pulse took
  while(io_read(sensor->pin, sensor->out) == true);
  TCCR1B ^= TCCR1B;

  status_disable_loop();
  return TCNT1 / 2;
}

color_sensor_ret_t color_sensor_read(color_sensor_t *sensor) {
  color_sensor_ret_t ret = {0, 0, 0};
  
  ret.r = color_sensor_measure(sensor, MEASURE_RED);
  ret.g = color_sensor_measure(sensor, MEASURE_GREEN);
  ret.b = color_sensor_measure(sensor, MEASURE_BLUE);

  return ret;
}

color_sensor_cres_t color_sensor_make_sense(color_sensor_ret_t *idk) {
  if (idk->r < idk->b && idk->r < idk->g) return CRES_RED;
  if (idk->b < idk->r && idk->b < idk->g) return CRES_BLUE;
  else if (idk->g < idk->b && idk->g < idk->r) return CRES_GREEN;
}
