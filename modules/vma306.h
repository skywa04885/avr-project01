/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#ifndef _MODULES_VMA306_H
#define _MODULES_VMA306_H

#include "../include.h"
#include "io.h"

typedef struct {
  volatile uint8_t *ddr, *port, *pin;
  uint8_t trig, echo;
} vma306_t;

void vma306_init(vma306_t *vma);
uint16_t vma306_read(vma306_t *vma);

#endif
