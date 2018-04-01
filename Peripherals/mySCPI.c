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

void mySCPI_processInput(void)
{
    if (EOL_detected) {
        EOL_detected = 0;
    }
    SCPI_Input(&scpi_context, RxBuffer, RxCount);
    uart_clearRxBuffer();
}