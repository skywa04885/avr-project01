#ifndef _MAIN_H
#define _MAIN_H

#define MAIN_LABEL "MAIN"

#include "include.h"
#include "modules/status.h"
#include "modules/usart.h"
#include "modules/logger.h"
#include "modules/a1602.h"
#include "modules/dht11.h"
#include "modules/vma306.h"
#include "modules/buzzer.h"
#include "modules/color.h"

void __attribute__ (( noreturn )) main();

#endif
