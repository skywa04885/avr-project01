/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#ifndef _MODULES_LOGGER_H
#define _MODULES_LOGGER_H

#include "../include.h"
#include "io.h"
#include "status.h"
#include "usart.h"

#ifdef LOGGER_ERRORS_ENABLE
#define LOGE(FMT, LABEL, ...) \
  fprintf(stderr, "[ERR(\"%s\",%d)@%s]: " FMT "\n", __FILE__, __LINE__, LABEL, ##__VA_ARGS__); \
  status_enable_error()
#else
#define LOGE(FMT, LABEL, ...)
#endif

#ifdef LOGGER_INFO_ENABLE
#define LOGI(FMT, LABEL, ...) \
  fprintf(stdout, "[INF@%s]: " FMT "\n", LABEL, ##__VA_ARGS__)
#else
#define LOGI(FMT, LABEL, ...)
#endif

#ifdef LOGGER_DEBUG_ENABLE
#define LOGD(FMT, LABEL, ...) \
  fprintf(stdout, "[DBG@%s]: " FMT "\n", LABEL, ##__VA_ARGS__)
#else
#define LOGD(FMT, LABEL, ...)
#endif


#endif
