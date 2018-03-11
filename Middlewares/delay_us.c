/*
 *Microsecond delay
 * initialize library with: delay_us_init();
 * for 8MHz or more	core frequency clock
 * This library doesn't generate precise us delay, so be careful - take a few us more/less
 */
#include "stm32f0xx_ll_rcc.h"
#include "delay_us.h"

static volatile uint32_t us_multiplier;

// init delay
void delay_us_init(void) {
  LL_RCC_ClocksTypeDef clocks;

  LL_RCC_GetSystemClocksFreq(&clocks);
  us_multiplier = clocks.SYSCLK_Frequency / 1000000; /* For 1 us delay, we need to divide with 1M */
}

// delay function: micros >= 1;
void delay_us(uint32_t micros){
    register uint32_t ms asm("r0") = micros * us_multiplier;

    //substitute 8 cycles for each call of asm code below == //micros /= 8;
    __asm(".syntax unified\n"
	"loop: subs r0, #8 \n"
	" bhi loop \n"
        ".syntax divided\n");
}
