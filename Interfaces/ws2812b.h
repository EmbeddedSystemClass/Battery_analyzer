/*
 * light weight WS2812 lib - ARM Cortex M0/M0+ version
 *
 */

#ifndef WS2812B_H
#define WS2812B_H

#include "stm32f0xx.h"
#include "stm32f0xx_ll_gpio.h"

#define ws2812_port_set ((uint32_t*)&GPIOB->BSRR)  // Address of the data port register to set the pin
#define ws2812_port_clr ((uint32_t*)&GPIOB->BRR) // Address of the data port register to clear the pin

#define ws2812_mask_set  LL_GPIO_PIN_15   // Bitmask to set the data out pin
#define ws2812_mask_clr  LL_GPIO_PIN_15   // Bitmask to clear the data out pin
///////////////////////////////////////////////////////////////////////
// User defined area: Define CPU clock speed
//
// The current implementation of the sendarray routine uses cycle accurate
// active waiting. The routine is automatically adjusted according to
// the clockspeed defined below. Only values between 8 Mhz and 60 Mhz
// are allowable.
//
// Important: The timing calculation assumes that there are no waitstates
// for code memory access. If there are waitstates you may have to reduce
// the value below until you get acceptable timing. It is highly recommended
// to use this library only on devices without flash waitstates and
// predictable code execution timing.
//
///////////////////////////////////////////////////////////////////////

#define ws2812_cpuclk 24000000 /* 48000000 */

///////////////////////////////////////////////////////////////////////
// End user defined area
///////////////////////////////////////////////////////////////////////

#if (ws2812_cpuclk<8000000)
	#error "Minimum clockspeed for ARM ws2812 library is 8 Mhz!"
#endif

#if (ws2812_cpuclk>60000000)
	#error "Maximum clockspeed for ARM ws2812 library is 60 Mhz!"
#endif


///////////////////////////////////////////////////////////////////////
// Main function call
//
// Call with address to led color array (order is Green-Red-Blue)
// Numer of leds to be transmitted
///////////////////////////////////////////////////////////////////////

void ws2812b_sendArray(uint8_t *ledarray,int length);

///////////////////////////////////////////////////////////////////////
// GPIO & Port initialization
//
// Call to init GPIO Pin
///////////////////////////////////////////////////////////////////////

void ws2812b_initPort(void);

#define COLOR(R, G, B) {G, R, B}

#endif /* WS2812B_H */
