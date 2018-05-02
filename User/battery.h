/** \addtogroup User
 * @{ */

/**
 * \defgroup Battery
 *
 * There is implemented battery charging and discharging process
 * @{
 */

#ifndef BATTERY_H
#define BATTERY_H

#include "stm32f0xx.h"

typedef enum {
    CHARGE,
    DISCHARGE,
    STOP,
} Battery_controll_state_e;

typedef struct {
    uint32_t Icharge;
    uint32_t Ucharge_cell;
    uint32_t Cells;
    uint32_t Icutoff;
    uint32_t Max_charging_time;
    uint32_t Udischarge_minimal;
    uint32_t Idischarge;
    uint32_t ReadOutTimeout;
} Battery_s;

typedef struct {
    Battery_controll_state_e controll_state;
} BatteryParam_s;

void battery_Uset(uint32_t voltage);
void battery_Iset(uint32_t current);
uint32_t battery_Uget(void);
uint32_t battery_Icharge_get(void);
uint32_t battery_Idischarge_get(void);
uint32_t battery_UccGet(void);
void Battery_setState(Battery_controll_state_e newstate);
Battery_controll_state_e Battery_getState(void);

extern Battery_s lead;

#endif /* BATTERY_H */
