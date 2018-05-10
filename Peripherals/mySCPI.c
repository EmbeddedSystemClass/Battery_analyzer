#include "mySCPI.h"
#include <stdio.h>
#include <stdlib.h>
#include "systick.h"
#include "stm32f0xx.h"
#include "pins.h"
#include "queue.h"
#include "debug.h"
#include "uart.h"
#include "scpi/parser.h"
#include "scpi-def.h"

static uint8_t EOL_detected = 0;

void mySCPI_setEOL_detected(void)
{
    EOL_detected = 1;
}

uint8_t mySCPI_isEOL_detected(void)
{
    return EOL_detected;
}

void mySCPI_processInput(void)
{
    scpi_bool_t result;
    result = SCPI_Input(&scpi_context, RxBuffer, RxCount);
    uart_clearRxBuffer();
    EOL_detected = 0;
}