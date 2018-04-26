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

typedef enum  {
    NO_PROCESS = 0,
    CHARGING = 1,
    DISCHARGING = 2,
    ACM_CAPACITY_MEASUREMENT = 3,
}acm_process;

 typedef enum {
    NO_ACM = 0,
    NiMH = 1,
    NiCd = 2,
    Pb_Acid = 3,
    Li_Ion = 4,
    Li_Po = 5,
    Li_FePo4 = 6,           
}acm_list;

void show_acm_list(acm_list *acm, acm_process process);
void main_state_set(uint32_t state);
uint32_t main_state_get(void);
void UI_process(void);
void UI_TIMER_Init(void);

void show_main_window(acm_process *process);
void show_settings_window(uint32_t tlacitko);

#endif /*__UI_H */