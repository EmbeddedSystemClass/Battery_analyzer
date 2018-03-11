#include "ws2812b.h"

void LEDS_init(void);

void LEDS_setColor(int id, uint8_t *color);

void LEDS_show(void);

extern const uint8_t C_RELAY_ON[];

extern const uint8_t C_RELAY_OFF[];
