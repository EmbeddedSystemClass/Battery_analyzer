#include "UI.h"
#include "stm32f0xx_ll_tim.h"
#include "iprintf.h"

uint32_t main_state = MAIN_STATE_INITIALISATION;

enum WINDOWS_STATES_t {
    MEASURE_WINDOW,
    MAIN_WINDOW,
    SETTINGS_WINDOW,
    SETTINGS_WIFI_WINDOW,
    SETTINGS_BRIGHTNESS_WINDOW,
    SETTINGS_BRIGHTNESS_DISPLAY_WINDOW,
    SETTINGS_BRIGHTNESS_LEDS_WINDOW,
};
uint32_t windows_state = MAIN_WINDOW;


volatile uint32_t aktualizovat_cas;
volatile uint32_t save_wifi;
volatile uint32_t save_brightness = 0;
volatile uint32_t load_brightness; //upravit - udelano narychlo
volatile uint8_t jas;
volatile uint32_t vystup;
volatile uint32_t wifi_connect;

#define BRIGHTNESS_DISPLAY_MAX 200
#define BRIGHTNESS_DISPLAY_MIN 0
#define BRIGHTNESS_LEDS_MAX 100
#define BRIGHTNESS_LEDS_MIN 0

static volatile uint8_t brightness_display = 100; //pozdeji bude brat z EEPROM
static volatile uint8_t brightness_leds = 50;


void show_idle_window(void);
void show_main_window(uint32_t tlacitko);
void show_settings_window(uint32_t tlacitko);
void show_settings_brightness_window(uint32_t tlacitko);
void show_settings_brightness_display_window(uint32_t tlacitko);
void show_settings_brightness_leds_window(uint32_t tlacitko);
void show_settings_wifi_window(uint32_t tlacitko);

void main_state_set(uint32_t state)
{
    main_state = state;
}

uint32_t main_state_get(void)
{
    return main_state;
}

void UI_process(void) //User Interface process
{
    uint32_t tlacitko = 0;


    switch (windows_state) {
    case MEASURE_WINDOW:
        if (tlacitko > 3) {
            windows_state = MAIN_WINDOW;
            break;
        }
        show_idle_window();
        break;

    case MAIN_WINDOW:
        if (tlacitko == 4) {
            windows_state = MEASURE_WINDOW;
        } //pusteno tlacitko 1 = navrat na MEASURE
        if (tlacitko == 5) {
            if (vystup) {
                vystup = 0;
                //                RELAY(0);
            } else {
                vystup = 1;
                //                RELAY(1);
            }
        } //pusteno tlacitko 2 = vypnout/zapnout vystup
        if (tlacitko == 6) {
            windows_state = SETTINGS_WINDOW;
        } //pusteno tlacitko 3 = nastaveni
        show_main_window(tlacitko); //zadny stisk nebo drzeni tlacitka 1, 2 nebo 3
        break;

    case SETTINGS_WINDOW:
        if (tlacitko == 4) {
            windows_state = MAIN_WINDOW;
        } //pusteno tlacitko 1 = navrat na MAIN
        if (tlacitko == 5) {
            windows_state = SETTINGS_WIFI_WINDOW;
            main_state = MAIN_STATE_WIFISET;
            //            LEDS_ColorRing();
        } //pusteno tlacitko 2 = nastaveni wifi
        if (tlacitko == 6) {
            windows_state = SETTINGS_BRIGHTNESS_WINDOW;
        } //pusteno tlacitko 3 = nastaveni jasu
        show_settings_window(tlacitko); //zadny stisk nebo drzeni tlacitka 1, 2 nebo 3
        break;

    case SETTINGS_WIFI_WINDOW:
        if (tlacitko == 4 || main_state_get() == MAIN_STATE_WIFISETOK) {
            windows_state = SETTINGS_WINDOW;
            main_state = MAIN_STATE_NORMAL;
        } //pusteno tlacitko 1 = navrat do SETTINGS
        //	if(tlacitko==5) {if(vystup){vystup=0;RELAY(0);}else {vystup=1;RELAY(1);}}	//pusteno tlacitko 2 = nastaveni wifi
        //	if(tlacitko==6) {windows_state=SETTINGS_WINDOW;}							//pusteno tlacitko 3 = nastaveni jasu
        show_settings_wifi_window(tlacitko); //zadny stisk nebo drzeni tlacitka 1, 2 nebo 3
        break;

    case SETTINGS_BRIGHTNESS_WINDOW:
        if (tlacitko == 4) {
            windows_state = SETTINGS_WINDOW;
        } //pusteno tlacitko 1 = navrat do SETTINGS
        if (tlacitko == 5) {
            windows_state = SETTINGS_BRIGHTNESS_DISPLAY_WINDOW;
        } //pusteno tlacitko 2 = nastaveni jasu displeje
        if (tlacitko == 6) {
            windows_state = SETTINGS_BRIGHTNESS_LEDS_WINDOW;
        } //pusteno tlacitko 3 = nastaveni jasu LED
        show_settings_brightness_window(tlacitko); //zadny stisk nebo drzeni tlacitka 1, 2 nebo 3
        break;

    case SETTINGS_BRIGHTNESS_DISPLAY_WINDOW:
        if (tlacitko == 4) {
            windows_state = SETTINGS_BRIGHTNESS_WINDOW;
        } //pusteno tlacitko 1 = navrat do SETTINGS_BRIGHTNESS
        if (tlacitko == 5) {
            if (brightness_display > BRIGHTNESS_DISPLAY_MIN + 19)brightness_display -= 20;
            save_brightness = 1;
        } //pusteno tlacitko 2 = nastaveni jasu displeje
        if (tlacitko == 6) {
            if (brightness_display < BRIGHTNESS_DISPLAY_MAX - 19)brightness_display += 20;
            save_brightness = 1;
        } //pusteno tlacitko 3 = nastaveni jasu LED
        show_settings_brightness_display_window(tlacitko); //zadny stisk nebo drzeni tlacitka 1, 2 nebo 3
        OLED_SetContrast(brightness_display);
        break;

    case SETTINGS_BRIGHTNESS_LEDS_WINDOW:
        if (tlacitko == 4) {
            windows_state = SETTINGS_BRIGHTNESS_WINDOW;
        } //pusteno tlacitko 1 = navrat do SETTINGS_BRIGHTNESS
        if (tlacitko == 5) {
            if (brightness_leds > BRIGHTNESS_LEDS_MIN + 9)brightness_leds -= 10;
            save_brightness = 1;
        } //pusteno tlacitko 2 = nastaveni jasu displeje
        if (tlacitko == 6) {
            if (brightness_leds < BRIGHTNESS_LEDS_MAX - 9)brightness_leds += 10;
            save_brightness = 1;
        } //pusteno tlacitko 3 = nastaveni jasu LED
        show_settings_brightness_leds_window(tlacitko); //zadny stisk nebo drzeni tlacitka 1, 2 nebo 3
        //        LEDS_SetPWM(brightness_leds);
        break;


    default: break;
    }

    ssd1306_Update_display();
}

void show_idle_window(void)
{
    uint8_t textbuff[200];
    UG_FontSelect(&FONT_6X8_CZECH);
    UG_FillScreen(0);

    //    uint8_t ucinik_buff[10];
    //    if (ucinik == 10000)smart_iprintf(ucinik_buff, "+1,000");
    //    else if (ucinik == -10000)smart_iprintf(ucinik_buff, "-1,000");
    //    else if (ucinik < 0) {
    //        ucinik = abs(ucinik);
    //        moba_siprintf(ucinik_buff, "-0,%03d", (int32_t) ucinik / 10);
    //    } else {
    //        moba_siprintf(ucinik_buff, "+0,%03d", (int32_t) ucinik / 10);
    //    }



    smart_siprintf(textbuff, "Proud: %d.%03dA\r\nNapětí: %d.%1dV\r\nPříkon: %d.%03dW\r\nPF: %s\r\nSpotřeba:", 1, 2, 2, 3, 5, 4, 8, 5, 5);
    UG_PutString(0, 0, textbuff);
    UG_FontSelect(&FONT_10X16);
    smart_siprintf(textbuff, "%d.%03dWh\r\n", 1, 2);
    UG_PutString(2, 48, textbuff);
}

void show_main_window(uint32_t tlacitko)
{
    static uint32_t obr1 = 0;
    static uint32_t obr2 = 0;
    static uint32_t obr3 = 0;
    uint8_t textbuff[40];

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    smart_siprintf(textbuff, "%02d.%02d.%04d", 1, 2, 3 + 2000);
    UG_PutString(0, 0, textbuff);

    if (wifi_connect == 1)add_picture_wifi(picture_wifi_on);
    else add_picture_wifi(picture_wifi_off);

    smart_siprintf(textbuff, "%02d:%02d:%02d", 44, 45, 64);
    UG_PutString(80, 0, textbuff);

    UG_FontSelect(&FONT_10X16);
    if (vystup)UG_PutString(26, 13, "ZAPNUTO");
    else UG_PutString(26, 13, "VYPNUTO");

    if (tlacitko == 1) {
        obr1 = 1;
        obr2 = 0;
        obr3 = 0;
    }
    if (tlacitko == 2) {
        obr1 = 0;
        obr2 = 1;
        obr3 = 0;
    }
    if (tlacitko == 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 1;
    }
    if (tlacitko > 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 0;
    }

    if (obr1) add_picture(1, picture_measuring_i);
    else add_picture(1, picture_measuring);
    if (obr2) add_picture(2, picture_output_i);
    else add_picture(2, picture_output);
    if (obr3) add_picture(3, picture_settings_i);
    else add_picture(3, picture_settings);
}

void show_settings_window(uint32_t tlacitko)
{
    static uint32_t obr1 = 0;
    static uint32_t obr2 = 0;
    static uint32_t obr3 = 0;
    uint8_t textbuff[40];

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    smart_siprintf(textbuff, "%02d.%02d.%04d", 8, 9, 10 + 2000);
    UG_PutString(0, 0, textbuff);

    if (wifi_connect == 1)add_picture_wifi(picture_wifi_on);
    else add_picture_wifi(picture_wifi_off);

    smart_siprintf(textbuff, "%02d:%02d:%02d", 5, 4, 3);
    UG_PutString(80, 0, textbuff);

    UG_FontSelect(&FONT_10X16);
    UG_PutString(16, 13, "NASTAVENI");


    if (tlacitko == 1) {
        obr1 = 1;
        obr2 = 0;
        obr3 = 0;
    }
    if (tlacitko == 2) {
        obr1 = 0;
        obr2 = 1;
        obr3 = 0;
    }
    if (tlacitko == 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 1;
    }
    if (tlacitko > 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 0;
    }

    if (obr1) add_picture(1, picture_backarrow_i);
    else add_picture(1, picture_backarrow);
    if (obr2) add_picture(2, picture_wifi_i);
    else add_picture(2, picture_wifi);
    if (obr3) add_picture(3, picture_brightness_i);
    else add_picture(3, picture_brightness);
}

void show_settings_wifi_window(uint32_t tlacitko)
{
    static uint32_t obr1 = 0;
    static uint32_t obr2 = 0;
    static uint32_t obr3 = 0;
    uint8_t textbuff[40];

    UG_FillScreen(0);

    UG_FontSelect(&FONT_6X8_CZECH);

    UG_PutString(0, 0, "Připojte se k wifi");
    UG_FontSelect(&FONT_10X16);
    UG_PutString(15, 12, "SmartPlug");
    UG_FontSelect(&FONT_6X8_CZECH);
    UG_PutString(45, 30, "a zadejte");
    UG_PutString(45, 39, "adresu");
    UG_FontSelect(&FONT_10X16);
    UG_PutString(45, 48, "1.1.1.1");




    if (tlacitko == 1) {
        obr1 = 1;
    }
    //if(tlacitko==2) {obr1=0; obr2=1; obr3=0;}
    //if(tlacitko==3) {obr1=0; obr2=0; obr3=1;}
    if (tlacitko > 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 0;
    }

    if (obr1) add_picture(1, picture_backarrow_i);
    else add_picture(1, picture_backarrow);
    //if(obr2) add_picture(2,picture_wifi_i); else add_picture(2,picture_wifi);
    //if(obr3) add_picture(3,picture_brightness_i); else add_picture(3,picture_brightness);
}

void show_settings_brightness_window(uint32_t tlacitko)
{
    static uint32_t obr1 = 0;
    static uint32_t obr2 = 0;
    static uint32_t obr3 = 0;
    uint8_t textbuff[40];

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    smart_siprintf(textbuff, "%02d.%02d.%04d", 4, 5, 6 + 2000);
    UG_PutString(0, 0, textbuff);

    if (wifi_connect == 1)add_picture_wifi(picture_wifi_on);
    else add_picture_wifi(picture_wifi_off);

    smart_siprintf(textbuff, "%02d:%02d:%02d", 1, 2, 3);
    UG_PutString(80, 0, textbuff);

    UG_FontSelect(&FONT_6X8_CZECH);
    UG_PutString(15, 18, "NASTAVENI JASU");


    if (tlacitko == 1) {
        obr1 = 1;
        obr2 = 0;
        obr3 = 0;
    }
    if (tlacitko == 2) {
        obr1 = 0;
        obr2 = 1;
        obr3 = 0;
    }
    if (tlacitko == 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 1;
    }
    if (tlacitko > 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 0;
    }

    if (obr1) add_picture(1, picture_backarrow_i);
    else add_picture(1, picture_backarrow);
    if (obr2) add_picture(2, picture_display_i);
    else add_picture(2, picture_display);
    if (obr3) add_picture(3, picture_leds_i);
    else add_picture(3, picture_leds);
}

void show_settings_brightness_display_window(uint32_t tlacitko)
{
    static uint32_t obr1 = 0;
    static uint32_t obr2 = 0;
    static uint32_t obr3 = 0;
    uint8_t textbuff[40];

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    smart_siprintf(textbuff, "%02d.%02d.%04d", 8, 9, 1 + 2000);
    UG_PutString(0, 0, textbuff);

    if (wifi_connect == 1)add_picture_wifi(picture_wifi_on);
    else add_picture_wifi(picture_wifi_off);

    smart_siprintf(textbuff, "%02d:%02d:%02d", 3, 4, 5);
    UG_PutString(80, 0, textbuff);

    UG_DrawFrame(14, 15, 114, 27, 1);
    UG_FillFrame(14, 15, 14 + (brightness_display / 2), 27, 1);


    if (tlacitko == 1) {
        obr1 = 1;
        obr2 = 0;
        obr3 = 0;
    }
    if (tlacitko == 2) {
        obr1 = 0;
        obr2 = 1;
        obr3 = 0;
    }
    if (tlacitko == 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 1;
    }
    if (tlacitko > 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 0;
    }

    if (obr1) add_picture(1, picture_backarrow_i);
    else add_picture(1, picture_backarrow);
    if (obr2) add_picture(2, picture_minus_i);
    else add_picture(2, picture_minus);
    if (obr3) add_picture(3, picture_plus_i);
    else add_picture(3, picture_plus);
}

void show_settings_brightness_leds_window(uint32_t tlacitko)
{
    static uint32_t obr1 = 0;
    static uint32_t obr2 = 0;
    static uint32_t obr3 = 0;
    uint8_t textbuff[40];

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    smart_siprintf(textbuff, "%02d.%02d.%04d", 1, 4, 7 + 2000);
    UG_PutString(0, 0, textbuff);

    if (wifi_connect == 1)add_picture_wifi(picture_wifi_on);
    else add_picture_wifi(picture_wifi_off);

    smart_siprintf(textbuff, "%02d:%02d:%02d", 9, 6, 3);
    UG_PutString(80, 0, textbuff);

    UG_DrawFrame(14, 15, 114, 27, 1);
    UG_FillFrame(14, 15, 14 + brightness_leds, 27, 1);


    if (tlacitko == 1) {
        obr1 = 1;
        obr2 = 0;
        obr3 = 0;
    }
    if (tlacitko == 2) {
        obr1 = 0;
        obr2 = 1;
        obr3 = 0;
    }
    if (tlacitko == 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 1;
    }
    if (tlacitko > 3) {
        obr1 = 0;
        obr2 = 0;
        obr3 = 0;
    }

    if (obr1) add_picture(1, picture_backarrow_i);
    else add_picture(1, picture_backarrow);
    if (obr2) add_picture(2, picture_minus_i);
    else add_picture(2, picture_minus);
    if (obr3) add_picture(3, picture_plus_i);
    else add_picture(3, picture_plus);
}

void UI_TIMER_Init(void)
{
#define UI_TIMER_PERIOD ((48000000 / 1000 ) - 1)
    LL_TIM_InitTypeDef TIM_InitStruct;

    /* Peripheral clock enable */
    LL_APB1_GRP2_EnableClock(LL_APB1_GRP2_PERIPH_TIM15);

    /* TIM15 interrupt Init */

    TIM_InitStruct.Prescaler = 80;
    TIM_InitStruct.CounterMode = LL_TIM_COUNTERMODE_UP;
    TIM_InitStruct.Autoreload = UI_TIMER_PERIOD;
    TIM_InitStruct.ClockDivision = LL_TIM_CLOCKDIVISION_DIV1;
    TIM_InitStruct.RepetitionCounter = 0;
    LL_TIM_Init(TIM15, &TIM_InitStruct);

    LL_TIM_DisableARRPreload(TIM15);

    LL_TIM_SetClockSource(TIM15, LL_TIM_CLOCKSOURCE_INTERNAL);

    LL_TIM_SetTriggerOutput(TIM15, LL_TIM_TRGO_RESET);

    LL_TIM_DisableMasterSlaveMode(TIM15);
    LL_TIM_EnableIT_UPDATE(TIM15);
    LL_TIM_EnableCounter(TIM15);

    NVIC_SetPriority(TIM15_IRQn, 1);
    NVIC_EnableIRQ(TIM15_IRQn);
}

void TIM15_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM15) != RESET) {
        LL_TIM_ClearFlag_UPDATE(TIM15);
        UI_process();
    }
}



















