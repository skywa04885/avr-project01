/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#ifndef _INCLUDE_H
#define _INCLUDE_H

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define BAUD 9600

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>
#include <util/setbaud.h>
#include <util/twi.h>

#endif
