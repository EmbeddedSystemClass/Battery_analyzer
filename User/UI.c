#include "UI.h"
#include "stm32f0xx_ll_tim.h"
#include "iprintf.h"
#include "inputs.h"
#include "directives.h"
#include "debug.h"
#include "internal_timer.h"

uint32_t main_state = MAIN_STATE_INITIALISATION;

enum WINDOWS_STATES_t {
    CHARGING_SETUP_WINDOW,
    MAIN_WINDOW,
    SETTINGS_WINDOW,
    DISCHARGING_WINDOW,
    CHOOSE_ACM,
    CHARGING_WINDOW,

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


static const uint32_t Umin[] = {0 ,900,900,2000,0,0,1000};
static const uint32_t Unom[] = {0 ,900,900,2000,0,0,1000}; //opravit
static const uint32_t Umax[] = {0 ,900,900,2000,0,0,1000};//opravit


static  acm_process process = NO_PROCESS;
static  uint8_t acm = NO_ACM;

static uint32_t param_pass[7];

void init_param_pass (uint8_t acm)
{
        param_pass[0] = acm;
        param_pass[1] = 1; //pocet akumulatoru
        param_pass[2] = Umax[acm];
        param_pass[3] = Unom[acm];
        param_pass[4] = Umin[acm];
        param_pass[5] = 100; //proud 100mA
        param_pass[6] = 100; //kapacita 100mAh
}


void show_charging_window(uint32_t t0);
void charging_setup_window(void);
void show_acm_list(acm_list *acm, acm_process process);
void show_main_window(acm_process *process);
void show_settings_window(uint32_t tlacitko);
void show_settings_brightness_window(uint32_t tlacitko);
void show_settings_brightness_display_window(uint32_t tlacitko);
void show_settings_brightness_leds_window(uint32_t tlacitko);
void show_settings_wifi_window(uint32_t tlacitko);

void main_state_set(uint32_t state) {
    main_state = state;
}

uint32_t main_state_get(void) {
    return main_state;
}

void UI_process(void) //User Interface process
{
    static uint32_t charging_sec_t0;
    switch (windows_state) {
        case MAIN_WINDOW:
            show_main_window(&process);
            break;
        case CHOOSE_ACM:
            show_acm_list(&acm, process);
            init_param_pass(acm);
            break;

        case CHARGING_SETUP_WINDOW:
            charging_setup_window();
            charging_sec_t0 = TIM16_getSeconds();
            break;
        case CHARGING_WINDOW:
            
            show_charging_window(charging_sec_t0);
            break; 
            
        case DISCHARGING_WINDOW:

            //show_acm_list(&acm);
            break;
            
        case SETTINGS_WINDOW:
            show_settings_window(1);
            break;

        default: break;
    }

    ssd1306_Update_display();
}

void show_charging_window(uint32_t t0){
    const uint8_t MenuCount = 4;
    uint8_t textbuff[40];
    uint8_t MenuShift = 0;
    uint8_t ArrowPos = 0;
    uint8_t MenuPos[MenuCount];
    static uint8_t BtnCount = 0;
    uint8_t t = TIM16_getSeconds() - t0;

    if (Inputs_BTN_isBtnPressed(BTN_DOWN_MASK)) {
        BtnCount++;
        Inputs_BTN_clearBtnBuffer();
    }
    if (Inputs_BTN_isBtnPressed(BTN_UP_MASK)) {
        if (BtnCount)
            BtnCount--;
        Inputs_BTN_clearBtnBuffer();
    }

//    if (Inputs_BTN_isBtnPressed(BTN_RIGHT_MASK)) {
//        windows_state = CHOOSE_ACM;
//
//        if (BtnCount == 0)
//            *process = CHARGING;
//        if (BtnCount == 1)
//            *process = DISCHARGING;
//        if (BtnCount == 2)
//            *process = ACM_CAPACITY_MEASUREMENT;
//
//        Inputs_BTN_clearBtnBuffer();
//        }
    if (BtnCount > MenuCount - 1)
        BtnCount = MenuCount - 1;

    if (BtnCount)
        MenuShift = BtnCount - 1;
    if (BtnCount >= MenuCount - 1)
        MenuShift -= 1;

    for (int i = 0; i <= MenuCount; ++i)
        MenuPos[i] = 100;
    for (int i = MenuShift; i < MenuShift + 3; ++i) {
        MenuPos[i] = 12 * (i - MenuShift + 1);
    }

    UG_FillScreen(0);
    UG_FontSelect(&FONT_5X12);
    
    smart_siprintf(textbuff, "Cas: %02d:%02d:%02ds",t/3600,(t/60)%60,t%60);
    UG_PutString(10, MenuPos[0], textbuff);
    smart_siprintf(textbuff, "Inab: %d.%02dA", 1,10);
    UG_PutString(10, MenuPos[1], textbuff);
    smart_siprintf(textbuff, "Unab: %d.%02dA",2,20);
    UG_PutString(10, MenuPos[2], textbuff);
    smart_siprintf(textbuff, "Nabita kapacita: %d.%03dAh", 3,30);
    UG_PutString(10, MenuPos[3], textbuff);


    UG_PutString(85, 0, "Ucc=5V");
    if (MenuShift) {
        smart_siprintf(textbuff, "%c", 30); //v
        UG_PutString(40, 00, textbuff);
    }
    if (MenuShift + 3 - MenuCount) {
        smart_siprintf(textbuff, "%c", 31); //^
        UG_PutString(40, 48, textbuff);
    }
    if (BtnCount)
        ArrowPos = 1;
    if (BtnCount == MenuCount - 1)
        ArrowPos = 2;


    smart_siprintf(textbuff, "%c", 16); //>
    UG_PutString(00, 12 * (ArrowPos + 1), textbuff);


    }

void show_acm_list(acm_list *acm, acm_process process) {
    const uint8_t MenuCount = 6;
    uint8_t MenuPos[MenuCount];
    uint8_t textbuff[40];
    uint8_t MenuShift = 0;
    uint8_t ArrowPos = 0;
    static uint8_t BtnCount = 0;

    if (Inputs_BTN_isBtnPressed(BTN_LEFT_MASK)) {
        windows_state = MAIN_WINDOW;
        Inputs_BTN_clearBtnBuffer();
    }

    if (Inputs_BTN_isBtnPressed(BTN_DOWN_MASK)) {
        BtnCount++;
        Inputs_BTN_clearBtnBuffer();
    }
    if (Inputs_BTN_isBtnPressed(BTN_UP_MASK)) {
        if (BtnCount)
            BtnCount--;
        Inputs_BTN_clearBtnBuffer();
    }

    if (BtnCount > MenuCount - 1)
        BtnCount = MenuCount - 1;
    if (BtnCount)
        MenuShift = BtnCount - 1;
    if (BtnCount >= MenuCount - 1)
        MenuShift -= 1;

    if (Inputs_BTN_isBtnPressed(BTN_RIGHT_MASK)) {
        *acm = BtnCount + 1;
        if (process == CHARGING)
            windows_state = CHARGING_SETUP_WINDOW;
        if (process == DISCHARGING)
            windows_state = MAIN_WINDOW;
        Inputs_BTN_clearBtnBuffer();
    }


    for (int i = 0; i <= MenuCount; ++i)
        MenuPos[i] = 100;
    for (int i = MenuShift; i < MenuShift + 3; ++i) {
        MenuPos[i] = 12 * (i - MenuShift + 1);
    }

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    UG_PutString(10, MenuPos[0], "NiMH");
    UG_PutString(10, MenuPos[1], "NiCd");
    UG_PutString(10, MenuPos[2], "Pb-Acid");
    UG_PutString(10, MenuPos[3], "Li-Ion");
    UG_PutString(10, MenuPos[4], "Li-Po");
    UG_PutString(10, MenuPos[5], "Li-FePO4");


    UG_PutString(85, 0, "Ucc=5V");
    if (MenuShift) {
        smart_siprintf(textbuff, "%c", 30); //v
        UG_PutString(40, 00, textbuff);
    }
    if (MenuShift + 3 - MenuCount) {
        smart_siprintf(textbuff, "%c", 31); //^
        UG_PutString(40, 48, textbuff);
    }
    if (BtnCount)
        ArrowPos = 1;
    if (BtnCount == MenuCount - 1)
        ArrowPos = 2;

    smart_siprintf(textbuff, "%c", 16); //>
    UG_PutString(00, 12 * (ArrowPos + 1), textbuff);

    //windows_state = SETTINGS_WINDOW;

}

void show_main_window(acm_process *process) {
    const uint8_t MenuCount = 4;
    uint8_t textbuff[40];
    uint8_t MenuShift = 0;
    uint8_t ArrowPos = 0;
    uint8_t MenuPos[MenuCount];
    static uint8_t BtnCount = 0;

    if (Inputs_BTN_isBtnPressed(BTN_DOWN_MASK)) {
        BtnCount++;
        Inputs_BTN_clearBtnBuffer();
    }
    if (Inputs_BTN_isBtnPressed(BTN_UP_MASK)) {
        if (BtnCount)
            BtnCount--;
        Inputs_BTN_clearBtnBuffer();
    }

    if (Inputs_BTN_isBtnPressed(BTN_RIGHT_MASK)) {
        windows_state = CHOOSE_ACM;

        if (BtnCount == 0)
            *process = CHARGING;
        if (BtnCount == 1)
            *process = DISCHARGING;
        if (BtnCount == 2)
            *process = ACM_CAPACITY_MEASUREMENT;

        Inputs_BTN_clearBtnBuffer();
    }
    if (BtnCount > MenuCount - 1)
        BtnCount = MenuCount - 1;

    if (BtnCount)
        MenuShift = BtnCount - 1;
    if (BtnCount >= MenuCount - 1)
        MenuShift -= 1;

    for (int i = 0; i <= MenuCount; ++i)
        MenuPos[i] = 100;
    for (int i = MenuShift; i < MenuShift + 3; ++i) {
        MenuPos[i] = 12 * (i - MenuShift + 1);
    }

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    UG_PutString(10, MenuPos[0], "Nabijeni");
    UG_PutString(10, MenuPos[1], "Vybijeni");
    UG_PutString(10, MenuPos[2], "Mereni kapacity");
    UG_PutString(10, MenuPos[3], "Nastaveni");


    UG_PutString(85, 0, "Ucc=5V");
    if (MenuShift) {
        smart_siprintf(textbuff, "%c", 30); //v
        UG_PutString(40, 00, textbuff);
    }
    if (MenuShift + 3 - MenuCount) {
        smart_siprintf(textbuff, "%c", 31); //^
        UG_PutString(40, 48, textbuff);
    }
    if (BtnCount)
        ArrowPos = 1;
    if (BtnCount == MenuCount - 1)
        ArrowPos = 2;


    smart_siprintf(textbuff, "%c", 16); //>
    UG_PutString(00, 12 * (ArrowPos + 1), textbuff);
}

void charging_setup_window(void) {
    const uint8_t MenuCount = 4;
    uint8_t textbuff[40];
    uint8_t MenuShift = 0;
    uint8_t ArrowPos = 0;
    uint8_t MenuPos[MenuCount];
    static uint8_t BtnCount = 0;
    static MulSet = 1000;

    static uint8_t SetBit = 0;

    if (Inputs_BTN_isBtnPressed(BTN_DOWN_MASK)) {
        if (!SetBit)BtnCount++;
        else {
            switch (BtnCount) {
                case 0: if (param_pass[1] > 1) --param_pass[1];
                    break;
                case 1: param_pass[2] -= MulSet;
                    break;
                case 2: param_pass[5] -= MulSet;
                    break;
                case 3: param_pass[6] -= MulSet;
                    break;
            }
        }
        Inputs_BTN_clearBtnBuffer();
    }
    if (Inputs_BTN_isBtnPressed(BTN_UP_MASK)) {
        if (!SetBit) {
            if (BtnCount)
                BtnCount--;
        } else {
            switch (BtnCount) {
                case 0: if ((param_pass[1] + 1)*(param_pass[2]) < 14000) ++param_pass[1];
                    break; //14V
                case 1: param_pass[2] += MulSet;
                    break;
                case 2: param_pass[5] += MulSet;
                    break;
                case 3: param_pass[6] += MulSet;
                    break;
            }
        }

        Inputs_BTN_clearBtnBuffer();
    }
    if (Inputs_BTN_isBtnPressed(BTN_LEFT_MASK)) {
        if (!SetBit)
            windows_state = CHOOSE_ACM;
        if (SetBit){
            
            if (MulSet<1000) MulSet *= 10;
        }
            
        Inputs_BTN_clearBtnBuffer();
    }
    
    if (Inputs_BTN_isBtnPressed(BTN_RIGHT_MASK)) {
        if (!SetBit)
            windows_state = CHARGING_WINDOW;
        if (SetBit){
            if (MulSet>10) MulSet /= 10;
        }
            
        Inputs_BTN_clearBtnBuffer();
    }

    if (Inputs_BTN_isBtnPressed(BTN_OK_MASK)) {
        SetBit = !SetBit; //povoleni zapisovani
        Inputs_BTN_clearBtnBuffer();
    }

    if (BtnCount > MenuCount - 1)
        BtnCount = MenuCount - 1;

    if (BtnCount)
        MenuShift = BtnCount - 1;
    if (BtnCount >= MenuCount - 1)
        MenuShift -= 1;


    for (int i = 0; i <= MenuCount; ++i)
        MenuPos[i] = 100;
    for (int i = MenuShift; i < MenuShift + 3; ++i) {
        MenuPos[i] = 12 * (i - MenuShift + 1);
    }
    

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    smart_siprintf(textbuff, "Clanku: %d (%d.%dV)", param_pass[1], (param_pass[1]*(param_pass[3])) / 1000, ((param_pass[1]*(param_pass[3])) % 1000) / 100);
    UG_PutString(10, MenuPos[0], textbuff);
    smart_siprintf(textbuff, "Umax: %d.%02dV", (param_pass[2]) / 1000, (param_pass[2]) % 1000/10);
    UG_PutString(10, MenuPos[1], textbuff);
    smart_siprintf(textbuff, "Inab: %d.%02dA", param_pass[5] / 1000, param_pass[5] % 1000 / 10);
    UG_PutString(10, MenuPos[2], textbuff);
    smart_siprintf(textbuff, "Kapacita: %d.%03dAh", param_pass[6]/1000),param_pass[6] % 1000;
    UG_PutString(10, MenuPos[3], textbuff);
    
    if (SetBit && BtnCount){
    smart_siprintf(textbuff, "%d.%02d", MulSet/1000,MulSet%1000/10);
    UG_PutString(50, 00, textbuff);
    }


    UG_PutString(85, 0, "Ucc=5V");
    if (MenuShift) {
        smart_siprintf(textbuff, "%c", 30); //v
        UG_PutString(40, 00, textbuff);
    }
    if (MenuShift + 3 - MenuCount) {
        smart_siprintf(textbuff, "%c", 31); //^
        UG_PutString(40, 48, textbuff);
    }
    if (BtnCount)
        ArrowPos = 1;
    if (BtnCount == MenuCount - 1)
        ArrowPos = 2;

    smart_siprintf(textbuff, "%c", 16); //>
    UG_PutString(00, 12 * (ArrowPos + 1), textbuff);    
    
    if (SetBit) {
        if (millis()%500 > 250){
        smart_siprintf(textbuff, "%c", ' '); //>
        UG_PutString(00, 12 * (ArrowPos + 1), textbuff);
        }
    }
}

void show_settings_window(uint32_t tlacitko) {
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

void show_settings_wifi_window(uint32_t tlacitko) {
    static uint32_t obr1 = 0;
    static uint32_t obr2 = 0;
    static uint32_t obr3 = 0;
    uint8_t textbuff[40];

    UG_FillScreen(0);

    UG_FontSelect(&FONT_6X8_CZECH);

    UG_PutString(0, 0, "PÄąâ„˘ipojte se k wifi");
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

void show_settings_brightness_window(uint32_t tlacitko) {
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

void show_settings_brightness_display_window(uint32_t tlacitko) {
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

void show_settings_brightness_leds_window(uint32_t tlacitko) {
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

void UI_TIMER_Init(void) {
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
    init_param_pass(NO_ACM);
}

void TIM15_IRQHandler(void) {
    if (LL_TIM_IsActiveFlag_UPDATE(TIM15) != RESET) {
        LL_TIM_ClearFlag_UPDATE(TIM15);
        UI_process();
    }
}