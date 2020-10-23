#include "vma306.h"

void vma306_init(vma306_t *vma) {
  io_mode(vma->ddr, vma->port, vma->trig, IO_OUTPUT);
  io_mode(vma->ddr, vma->port, vma->echo, IO_INPUT);
}

uint16_t vma306_read(vma306_t *vma) {

}
