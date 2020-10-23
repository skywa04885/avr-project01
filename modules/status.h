/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#include "../include.h"
#include "io.h"

#ifndef _MODULES_STATUS_H
#define _MODULES_STATUS_H

#define STATUS_PORT       PORTH
#define STATUS_DDR        DDRH
#define STATUS_LED_ERROR  PH4
#define STATUS_LED_LOOP   PH5
#define STATUS_LED_BUS    PH3

void status_init();

void status_enable_error();
void status_disable_error();

void status_enable_loop();
void status_disable_loop();

void status_enable_bus();
void status_disable_bus();

#endif
