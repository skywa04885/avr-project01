#include "vma306.h"

void vma306_init(vma306_t *vma) {
  io_mode(vma->ddr, vma->port, vma->trig, IO_OUTPUT);
  io_mode(vma->ddr, vma->port, vma->echo, IO_INPUT);
}

uint16_t vma306_read(vma306_t *vma) {
  status_enable_loop();

  // Sends the 10uS wide pulse to the VMA306, which will send the
  //  sound pulse
  io_high(vma->port, vma->trig);
  _delay_us(10);
  io_low(vma->port, vma->trig);

  // Starts the timer which will count until the echo has been
  //  recieved
  while (true) if (io_read(vma->pin, vma->echo) == true) break;
  TCNT1 ^= TCNT1;
  TCCR1B = (1 << CS11);

  // Waits until the echo has been received, after which we stop
  //  the timer
  while (true) if (io_read(vma->pin, vma->echo) == false) break;
  TCCR1B ^= TCCR1B;

  // Calculates the distance in cm, and returns it from the
  //  function
  status_disable_loop();
  return (TCNT1 / 2) * 0.034f / 2;
}
