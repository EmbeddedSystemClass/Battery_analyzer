#ifndef __UI_H
#define __UI_H
#include "stm32f0xx.h"
#include "ugui.h"
#include "stdio.h"
#include "stdlib.h"
#include "strings.h"
#include "string.h"
#include "iprintf.h"
#include "LEDS.h"
#include "SysTick.h"
#include "EEPROM.h"

enum MAIN_STATES_t {
    MAIN_STATE_INITIALISATION,
    MAIN_STATE_NEW,
    MAIN_STATE_NORMAL,
    MAIN_STATE_ERROR,
    MAIN_STATE_NOTIFICATION,
    MAIN_STATE_WIFISET,
    MAIN_STATE_WIFISETOK,
};

void main_state_set(uint32_t state);
uint32_t main_state_get(void);
void UI_process(void);
void UI_TIMER_Init(void);
void show_idle_window(void);

void show_main_window(uint32_t tlacitko);
void show_settings_window(uint32_t tlacitko);

#endif /*__UI_H */
