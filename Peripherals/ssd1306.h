/** \addtogroup Peripherals
 * @{ */

/**
 * \defgroup SSD1306
 *
 * This module contains OLED display SSD1306 routine
 * @{
 */
#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stm32f0xx_ll_pwr.h"
#include "stm32f0xx_ll_bus.h"

extern const uint32_t picture_wifi[40];
extern const uint32_t picture_wifi_i[40];

extern const uint32_t picture_settings[40];
extern const uint32_t picture_settings_i[40];

extern const uint32_t picture_output[40];
extern const uint32_t picture_output_i[40];

extern const uint32_t picture_backarrow[40];
extern const uint32_t picture_backarrow_i[40];

extern const uint32_t picture_measuring[40];
extern const uint32_t picture_measuring_i[40];
extern const uint32_t picture_brightness[40];
extern const uint32_t picture_brightness_i[40];

extern const uint32_t picture_minus[40];
extern const uint32_t picture_minus_i[40];

extern const uint32_t picture_plus[40];
extern const uint32_t picture_plus_i[40];

extern const uint32_t picture_display[40];
extern const uint32_t picture_display_i[40];

extern const uint32_t picture_leds[40];
extern const uint32_t picture_leds_i[40];

extern const uint32_t picture_wifi_on[13];
extern const uint32_t picture_wifi_off[13];

void ssd1306_rst_init(void);
void ssd1306_rst(void);

void ssd1306_init(void);
void OLED_send_cmd(uint8_t cmd);
void ssd1306_Update_display(void);
void OLED_SetContrast(uint8_t contrast);
void add_picture_wifi(uint32_t picture[]);
void add_picture(uint32_t position, uint32_t picture[]);

#endif /* SSD1306_H */
