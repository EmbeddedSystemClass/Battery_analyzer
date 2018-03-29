#include "systick.h"
#include "debug.h"
#include "inputs.h"

volatile uint32_t millis_cnt = 0;
volatile uint32_t CLK1MS = 0;
volatile uint32_t CLK1S = 0;
volatile uint32_t delay_time = 0;
uint8_t state = 0;

extern void WDG_restart(void);

void SysTick_Handler(void)
{
    millis_cnt++;
    CLK1MS++;
    WDG_restart();
    if (delay_time)
        delay_time--;
    if (!(CLK1MS % 1000)) {
        CLK1S++;
        Inputs_ADC_printValues();
    }
}

uint32_t millis(void)
{
    return millis_cnt;
}

void delay(uint32_t milliseconds)
{
    delay_time = milliseconds;
    while (delay_time)
        ;
}

uint32_t SysTick_getSeconds(void)
{
    return CLK1S;
}