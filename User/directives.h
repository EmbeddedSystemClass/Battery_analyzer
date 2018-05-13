#ifndef DIRECTIVES_H
#define DIRECTIVES_H

#define SW_VERSION  "0.01"

#define DEBUGGING
    #define DEBUG_INIT          SMART_DEBUG_OFF
    #define DEBUG_I2C           SMART_DEBUG_OFF
    #define DEBUG_BTN           SMART_DEBUG_OFF
    #define DEBUG_ADC           SMART_DEBUG_OFF
    #define DEBUG_SCPI          SMART_DEBUG_OFF
    #define DEBUG_POWER         SMART_DEBUG_ON


#define USE_WDT     (1)

#define COLOR_RED COLOR(30, 0, 0)
#define COLOR_GREEN COLOR(0, 30, 0)
#define COLOR_BLUE COLOR(0, 0, 30)
#define COLOR_PURPLE COLOR(255, 0, 216)
#define COLOR_ORANGE COLOR(132, 92, 0)
#define COLOR_YELLOW COLOR(10, 10, 0)

#define BTN_OK_MASK       0x1
#define BTN_LEFT_MASK     0x2
#define BTN_RIGHT_MASK    0x4
#define BTN_UP_MASK       0x8
#define BTN_DOWN_MASK     0x10
#define BTN_STOP_MASK     0x20

//#define DBG_PRINT_ADC_EVERY_SECOND

#endif /* DIRECTIVES_H */