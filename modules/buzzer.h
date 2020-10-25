/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/


#ifndef _MODULES_BUZZER_H
#define _MODULES_BUZZER_H

#include "../include.h"
#include "io.h"

typedef struct {
  volatile uint8_t *ddr, *port;
  uint8_t n;
} buzzer_t;

void buzzer_init(buzzer_t *buzz);
void buzzer_buzz(buzzer_t *buzz, uint16_t ps, uint16_t loops);

#endif
