#ifndef PINS_H
#define PINS_H

#define BTN_LEFT_PORT    GPIOB
#define BTN_LEFT_PIN     LL_GPIO_PIN_11
#define BTN_LEFT_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define BTN_RIGHT_PORT    GPIOB
#define BTN_RIGHT_PIN     LL_GPIO_PIN_2
#define BTN_RIGHT_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define BTN_UP_PORT    GPIOB
#define BTN_UP_PIN     LL_GPIO_PIN_1
#define BTN_UP_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define BTN_DOWN_PORT    GPIOB
#define BTN_DOWN_PIN     LL_GPIO_PIN_12
#define BTN_DOWN_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define BTN_OK_PORT    GPIOB
#define BTN_OK_PIN     LL_GPIO_PIN_10
#define BTN_OK_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define BTN_STOP_PORT    GPIOB
#define BTN_STOP_PIN     LL_GPIO_PIN_14
#define BTN_STOP_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define DISP_RST_PORT    GPIOA
#define DISP_RST_PIN     LL_GPIO_PIN_11
#define DISP_RST_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA

#define FAN_PORT    GPIOB
#define FAN_PIN     LL_GPIO_PIN_8
#define FAN_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define BUZZER_PORT    GPIOB
#define BUZZER_PIN     LL_GPIO_PIN_9
#define BUZZER_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define STEP_DOWN_P_DRIVE_PORT    GPIOA
#define STEP_DOWN_P_DRIVE_PIN     LL_GPIO_PIN_8
#define STEP_DOWN_P_DRIVE_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA

#define STEP_DOWN_N_DRIVE_PORT    GPIOB
#define STEP_DOWN_N_DRIVE_PIN     LL_GPIO_PIN_13
#define STEP_DOWN_N_DRIVE_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB

#define INTERNAL_THERMISTOR_PORT    GPIOA
#define INTERNAL_THERMISTOR_PIN     LL_GPIO_PIN_7
#define INTERNAL_THERMISTOR_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA
#define INTERNAL_THERMISTOR_ADC_CH  LL_ADC_CHANNEL_7

#define BATT_THERMISTOR_PORT    GPIOA
#define BATT_THERMISTOR_PIN     LL_GPIO_PIN_6
#define BATT_THERMISTOR_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA
#define BATT_THERMISTOR_ADC_CH  LL_ADC_CHANNEL_6

#define VCC_IN_ADC_PORT    GPIOA
#define VCC_IN_ADC_PIN     LL_GPIO_PIN_3
#define VCC_IN_ADC_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA
#define VCC_IN_ADC_ADC_CH  LL_ADC_CHANNEL_3

#define V_BUS_ADC_PORT    GPIOA
#define V_BUS_ADC_PIN     LL_GPIO_PIN_2
#define V_BUS_ADC_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA
#define V_BUS_ADC_CH      LL_ADC_CHANNEL_2

#define BATT_VTG_ADC_PORT    GPIOA
#define BATT_VTG_ADC_PIN     LL_GPIO_PIN_0
#define BATT_VTG_ADC_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA
#define BATT_VTG_ADC_CH      LL_ADC_CHANNEL_0

#define FB_ADC_PORT    GPIOB
#define FB_ADC_PIN     LL_GPIO_PIN_0
#define FB_ADC_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOB
#define FB_ADC_CH      LL_ADC_CHANNEL_8

#define CHARGE_CURR_ADC_PORT    GPIOA
#define CHARGE_CURR_ADC_PIN     LL_GPIO_PIN_5
#define CHARGE_CURR_ADC_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA
#define CHARGE_CURR_ADC_CH      LL_ADC_CHANNEL_5

#define DISCHARGE_CURR_CURR_ADC_PORT    GPIOA
#define DISCHARGE_CURR_CURR_ADC_PIN     LL_GPIO_PIN_4
#define DISCHARGE_CURR_CURR_ADC_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA
#define DISCHARGE_CURR_CURR_ADC_CH      LL_ADC_CHANNEL_4

#define UART_PINS_PORT  GPIOB
#define UART_RX_PIN LL_GPIO_PIN_7
#define UART_TX_PIN LL_GPIO_PIN_6
#define UART_PINS_CLOCK  LL_AHB1_GRP1_PERIPH_GPIOB
#define UART_UART_CLOCK LL_APB1_GRP2_PERIPH_USART1
#define UART_UART   USART1
#define UART_SPEED  57600
#define UART_AF     LL_GPIO_AF_0

#define I2C_PINS_PORT  GPIOF
#define I2C_SCL_PIN    LL_GPIO_PIN_6
#define I2C_SDA_PIN    LL_GPIO_PIN_7
#define I2C_PINS_CLOCK LL_AHB1_GRP1_PERIPH_GPIOF
#define I2C_CLOCK      LL_APB1_GRP1_PERIPH_I2C2
#define I2C_AF         LL_GPIO_AF_1
#define I2C            I2C2

#define EEPROM_ADDRESS  0x50
#define OLED_ADDRESS    0x78

#define OLED_RST_PORT    GPIOA
#define OLED_RST_PIN     LL_GPIO_PIN_11
#define OLED_RST_CLOCK   LL_AHB1_GRP1_PERIPH_GPIOA

#endif /* PINS_H */