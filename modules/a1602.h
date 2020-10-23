/*
  Copyright Luke A.C.A. Rieff 2020 - Fannst Software
*/

#include "../include.h"
#include "io.h"
#include "status.h"

#ifndef _MODULES_A1602_H
#define _MODULES_A1602_H

#define A1602_BUS_PORT  PORTK
#define A1602_BUS_DDR   DDRK
#define A1602_BUS_D0    PK0
#define A1602_BUS_D1    PK1
#define A1602_BUS_D2    PK2
#define A1602_BUS_D3    PK3
#define A1602_BUS_D4    PK4
#define A1602_BUS_D5    PK5
#define A1602_BUS_D6    PK6
#define A1602_BUS_D7    PK7

#define A1602_REST_PORT PORTE
#define A1602_REST_DDR  DDRE
#define A1602_REST_RS   PE4
#define A1602_REST_RW   PE5
#define A1602_REST_E    PE3

#define A1602_MAX_ROWS  2
#define A1602_MAX_COLS  16

// =====================================

/* Operation delay */
#define A1602_DLY_CLD   15200     /* Clear display */
#define A1602_DLY_RH    15200     /* Return Home */
#define A1602_DLY_EMS   37        /* Entry Mode Set */
#define A1602_DLY_DOF   37        /* Display On orOff */
#define A1602_DLY_COS   37        /* Cursor or display shift */
#define A1602_DLY_FNS   37        /* Function Set */
#define A1602_DLY_SCG   37        /* Set CGRam address */
#define A1602_DLY_SDR   37        /* Set DDRam address */
#define A1602_DLY_WDR   37        /* Write data to ram */
#define A1602_DLY_RDR   37        /* Read data from RAM */

/* Special chars */
#define A1602_CDEG      0b01101111
#define A1602_CARR      0b01111110
#define A1602_CARL      0b01111111
#define A1602_CDEG      0b11011111

/* Clear Display */
#define A1602_CLD_DEF   0x1       /* Base */

/* Return Home */
#define A1602_REH_DEF   0x2       /* Base */

/* Entry Mode Set */
#define A1602_EMS_DEF   0x4       /* Base */
#define A1602_EMS_INC   0x2       /* If the position should increment */
#define A1602_EMS_DSF   0x1       /* Display shift */

/* Display ON/OFF */
#define A1602_DOO_DEF   0x8       /* Base */
#define A1602_DOO_ENA   0x1       /* Entire display on */
#define A1602_DOO_ENC   0x2       /* Cursor on */
#define A1602_DOO_ECP   0x4       /* Cursor position on */

/* Cursor or Display Shift */
#define A1602_CDS_DEF   0x16      /* Base */
#define A1602_CDS_CMM   0x8       /* Set cursor moving */
#define A1602_CDS_MLR   0x4       /* Set cursor move right */

/* Function Set */
#define A1602_FNS_DEF   0x32      /* Base */
#define A1602_FNS_U8B   0x16      /* Use 8 bits */
#define A1602_FNS_UL2   0x8       /* Use the second line */
#define A1602_FNS_ULF   0x4       /* Use 5x11 font */

/* Write Mode timing */
#define A1602_WRM_ECT   1200      /* Enable Cycle Time */
#define A1602_WRM_EPW   140       /* Enable Pulse Width */
#define A1602_WRM_AHT   10        /* Address hold time */
#define A1602_WRM_DST   40        /* Data Setup Time */
#define A1602_WRM_DHT   10        /* Data hold time */
#define A1602_WRM_AST   10        /* Address Setup Time */

/* Read mode timing */
#define A1602_RDM_ECT   1200      /* Enable Cycle Time */
#define A1602_RDM_EPW   140       /* Enable Pulse WIdth */
#define A1602_RDM_AHT   10        /* Address hold time */
#define A1602_RDM_DHT   10        /* Data hold time */
#define A1602_RDM_AST   10        /* Address Setup Time */

/* Easy function access */
#define a1602_clear() a1602_instruction_write(A1602_CLD_DEF); \
_delay_us(A1602_DLY_CLD)
#define a1602_return_home() a1602_instruction_write(A1602_REH_DEF); \
_delay_us(A1602_DLY_RH)
#define a1602_write(c) a1602_write_string(c); \
_delay_us(A1602_DLY_SCG)
#define a1602_instruct(c) a1602_instruction_write(c); \
_delay_us(A1602_DLY_SCG)

// =====================================

void a1602_init();

void a1602_bus_mode(io_mode_t mode);
void a1602_instruction_write(uint8_t byte);
void a1602_write_char(char c);
void a1602_write_string(const char *str);

#endif
