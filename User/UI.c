#include "UI.h"
#include "stm32f0xx_ll_tim.h"
#include "iprintf.h"
#include "inputs.h"
#include "directives.h"
#include "debug.h"
#include "internal_timer.h"
#include "battery.h"
#include "LEDS.h"

uint32_t main_state = MAIN_STATE_INITIALISATION;
extern volatile uint32_t remote_control;
extern volatile uint64_t capacity;

enum WINDOWS_STATES_t {
    CHARGING_SETUP_WINDOW,
    DISCHARGING_SETUP_WINDOW,
    MAIN_WINDOW,
    //    SETTINGS_WINDOW,
    DISCHARGING_WINDOW,
    CHOOSE_ACM,
    CHARGING_WINDOW,
    REMOTE_ACCESS_WINDOW,
};

uint32_t windows_state = MAIN_WINDOW;

static const uint32_t Umin[] = {1950, 2500, 0, 0, 0, 0, 0};
static const uint32_t Unom[] = {2000, 3600, 0, 00, 0, 0, 0}; //opravit
static const uint32_t Umax[] = {2400, 4100, 0, 0, 0, 0, 00}; //opravit

static volatile uint32_t OldSeconds = 0;
static volatile uint32_t t0_NiMH = 0;

//static  acm_process process = NO_PROCESS;
//static  uint8_t acm = NO_ACM;
//static  uint8_t wh_ah = 0; //pridat do nastaveni
//static  uint32_t timer_NiMH = 0;

//static uint32_t param_pass[7];

//#define NVD_ARRAY_NUM 10
//static int32_t negative_voltage_detection_array[NVD_ARRAY_NUM] = {0,};
//static uint8_t nvd_point = 1;


void show_discharging_window(uint32_t t0);
void show_charging_window(uint32_t t0);
void show_charging_setup_window(void);
void show_acm_list(acm_list *acm, acm_process process);
void show_main_window(acm_process *process);
//void show_settings_window(uint32_t tlacitko);
void show_discharging_setup_window(void);
void show_remote_access(void);

//void show_settings_brightness_window(uint32_t tlacitko);
//void show_settings_brightness_display_window(uint32_t tlacitko);
//void show_settings_brightness_leds_window(uint32_t tlacitko);
//void show_settings_wifi_window(uint32_t tlacitko);




//static const uint32_t Umin[] = {0 ,900,900,1900,0,0,1000};
//static const uint32_t Unom[] = {0 ,1200,1200,2000,0,0,1000}; //opravit
//static const uint32_t Umax[] = {0 ,1500,1450,2400,0,0,1000};//opravit

//static volatile uint32_t OldSeconds = 0;
//static volatile uint32_t t0_NiMH = 0;

static acm_process process = NO_PROCESS;
static uint8_t acm = NO_ACM;
static uint8_t wh_ah = 0; //pridat do nastaveni
static uint32_t timer_NiMH = 0;

static uint32_t param_pass[7];

void init_param_pass(uint8_t acm)
{
    param_pass[0] = acm;
    param_pass[1] = 1; //pocet clanku
    param_pass[2] = Umax[acm];
    param_pass[3] = Unom[acm];
    param_pass[4] = Umin[acm];
    param_pass[5] = 100; //proud 100mA
    param_pass[6] = 100; //kapacita 100mAh
}

//uint8_t negative_voltage_detection(void)  //overit fci, diferencni detekce, upravit:najit maximum a hledat zda jsou vsechny hodnoty mensi nez minule
//{
//    uint8_t nvd_point_start = nvd_point;
//    negative_voltage_detection_array[nvd_point] = (int32_t)battery_Uget();
//    nvd_point++;
//    nvd_point %= NVD_ARRAY_NUM;
//    //uint8_t i = 0;
//    
//    for(;nvd_point++%NVD_ARRAY_NUM != nvd_point_start;++nvd_point)
//    {
//        if (negative_voltage_detection_array[nvd_point_start] > negative_voltage_detection_array[nvd_point]) 
//        {
//            nvd_point = nvd_point_start; //nasla se vetsi nez aktualni
//            return 0;
//        }
//    }
//    return 1;//vsechny hodnoty musi byt mensi nez aktualni               
//}




//uint64_t charge_NiMH (uint32_t t, uint64_t cappacity) //in progress
//{
//    uint8_t textbuff[40];
//    lead.
//    uint32_t exceed_time =0;
//    if(wh_ah)
//        exceed_time = param_pass[6]/param_pass[5]*3600;
//    if(!wh_ah)
//        exceed_time = param_pass[6]/param_pass[5]*3600000/param_pass[3];
//    
//    if((battery_UccGet()) < param_pass[2]*param_pass[1]){ //napajeci napeti - Umax nab
//        charging_state = CHARGING_STATE_STOP;//udelej chybu nap. napeti je mensi nez maximalni napeti batery pri ;
//        smart_siprintf(textbuff, "!Ucc < Unab!");
//        
//    }
//    if(!param_pass[6]){
//        charging_state = CHARGING_STATE_STOP;//udelej chybu nulova nabijena kapacita
//        smart_siprintf(textbuff, "!Kapacita = 0!");
//    }
//    cappacity = measure_cappacity(cappacity,  t);
//    switch (charging_state){
//        case CHARGING_STATE_CC:
//            if (battery_Uget()/param_pass[1] < 1000 )//1V
//            { 
//                t = 0;
//                if(wh_ah)
//                     battery_Iset(param_pass[6]/10);
//                if(!wh_ah)
//                     battery_Iset(param_pass[6]/param_pass[3]/10);
//            }
//            else
//            {
//                battery_Iset(param_pass[5]);
//                if (t > exceed_time )
//                {
//                    charging_state = CHARGING_STATE_CHARGED;
//                }
//                if (negative_voltage_detection())
//                {
//                    charging_state = CHARGING_STATE_TRICKLE;
//                    t0_NiMH = t;
//                }
//            }
//            break;
//            
//        case CHARGING_STATE_TRICKLE:
//            if(wh_ah)
//                 battery_Iset(param_pass[6]/20);
//            if(!wh_ah)
//                 battery_Iset(param_pass[6]/param_pass[3]/20);
//            if ( (t-t0_NiMH) >= 15*60 )
//                charging_state = CHARGING_STATE_CHARGED;
//            break;
//            
//        case CHARGING_STATE_CHARGED:
//            battery_Iset(0);
////            LEDS_setColor(COLOR_GREEN);
//            smart_siprintf(textbuff, "!Nabito!");
//            UG_PutString(0,20, textbuff);
//            break;
//            
//        case CHARGING_STATE_STOP:
//            battery_Iset(0);
////          LEDS_setColor(COLOR_RED);
//            smart_siprintf(textbuff, "!Zastaveno!");
//            UG_PutString(0,20, textbuff);
//            break;       
//            
//        default:
//            charging_state = CHARGING_STATE_CHARGED;
//            break;
//    } 
//}
//uint64_t charge_Pb_Acid (uint32_t t, uint64_t cappacity){
//    uint8_t textbuff[40];
//    if((battery_UccGet()) < param_pass[2]*param_pass[1]){ //napajeci napeti - Umax nab
//        charging_state = CHARGING_STATE_STOP;//udelej chybu nap. napeti je mensi nez maximalni napeti batery pri ;
//        smart_siprintf(textbuff, "!Ucc < Unab!");
//        
//    }
//    if(!param_pass[6]){
//        charging_state = CHARGING_STATE_STOP;//udelej chybu nulova nabijena kapacita
//        smart_siprintf(textbuff, "!Kapacita = 0!");
//    }
//    if (cappacity > param_pass[6]*CHARGING_CAPACITY_MULTIPLIER){
//        charging_state = CHARGING_STATE_STOP;        //prekrocena maximalni povolena nabijeci kapacita
//        smart_siprintf(textbuff, "!Kapacita = 0!");
//    }
//    switch (charging_state){
//        case CHARGING_STATE_CC: 
//            battery_Iset(param_pass[5]);
//            cappacity = measure_cappacity(cappacity,  t);
//            if(battery_Uget() >= param_pass[1] * param_pass[2])
//                charging_state = CHARGING_STATE_CV;
////          LEDS_setColor(COLOR_RED);
//            break;
//        case CHARGING_STATE_CV: 
//            if(battery_Icharge_get() == 0);
//                //odpojeny acm
//            battery_Uset(param_pass[2]);
//            cappacity = measure_cappacity(cappacity,  t);
////            LEDS_setColor(COLOR_ORANGE);
//            if(battery_Icharge_get() <= param_pass[6]/20)
//                charging_state = CHARGING_STATE_CV_LOW;
//            
//            break;
//        case CHARGING_STATE_CV_LOW: 
//            battery_Uset(param_pass[1]*2275);
//            cappacity = measure_cappacity(cappacity,t);
//            if(battery_Icharge_get() <= param_pass[6]/34)
//                charging_state = CHARGING_STATE_CHARGED;
////            LEDS_setColor(COLOR_YELLOW);
//            break;
//        case CHARGING_STATE_CHARGED: 
//            battery_Iset(0);
////            LEDS_setColor(COLOR_GREEN);
//            break;
//        case CHARGING_STATE_STOP:
//            battery_Iset(0);
////            LEDS_setColor(COLOR_RED);
//            break;
//            
//    }
//    UG_PutString(0,20, textbuff);
//    return (cappacity);
//}

void main_state_set(uint32_t state)
{
    main_state = state;
}

uint32_t main_state_get(void)
{
    return main_state;
}



void show_remote_access(void)
{
    uint8_t textbuff[40];
    uint32_t temp_U, temp_I;

    UG_FillScreen(0);
    UG_FontSelect(&FONT_5X12);

    if (Inputs_BTN_isBtnPressed(BTN_STOP_MASK)) {
        Battery_setState(BATTERY_STOP);
        Inputs_BTN_clearBtnBuffer();
    }
    temp_U = battery_Uget();
    switch (Battery_getState()) {
    case BATTERY_STOP:
        UG_FillScreen(0);
        UG_PutString(0, 0, "  Vzdalene ovladani");
        UG_PutString(0, 30, "     Pripraveno");
        break;
    case BATTERY_CHARGE:
        temp_I = battery_Icharge_get();
        UG_PutString(0, 0, "  Vzdalene ovladani");
        UG_PutString(0, 12, "      Nabijeni");
        smart_siprintf(textbuff, "Napeti: %02ld.%02ldV", temp_U / 1000, temp_U % 1000 / 10);
        UG_PutString(0, 24, textbuff);
        smart_siprintf(textbuff, "Proud: %03ldmA", temp_I);
        UG_PutString(0, 36, textbuff);
        smart_siprintf(textbuff, "Nabito: %ld.%02ldmAh", (uint32_t)capacity/3600,(uint32_t)map(capacity%3600,0,3600,0,100));
        UG_PutString(0, 48, textbuff);
        break;
    case BATTERY_DISCHARGE:
        temp_I = battery_Idischarge_get();
        UG_PutString(0, 0, "  Vzdalene ovladani");
        UG_PutString(0, 12, "      Vybijeni");
        smart_siprintf(textbuff, "Napeti: %02ld.%02ldV", temp_U / 1000, temp_U % 1000 / 10);
        UG_PutString(0, 24, textbuff);
        smart_siprintf(textbuff, "Proud: %03ldmA", temp_I);
        UG_PutString(0, 36, textbuff);
        smart_siprintf(textbuff, "Vybito: %ld.%02ldmAh", (uint32_t)capacity/3600,(uint32_t)map(capacity%3600,0,3600,0,100));
        UG_PutString(0, 48, textbuff);
        break;
    }

}

void UI_process(void) //User Interface process
{

    /*
    
    uint8_t textbuff[40];
    uint32_t temp_U, temp_I;
    
    UG_FillScreen(0);
    UG_FontSelect(&FONT_5X12);
    
    if (Inputs_BTN_isBtnPressed(BTN_STOP_MASK)) {
        Battery_setState(STOP);
        Inputs_BTN_clearBtnBuffer();
    }
    temp_U = battery_Uget();
    switch (Battery_getState())
    {
        case STOP: 
            UG_FillScreen(0);
            UG_PutString(20, 30, "Nabijeni zastaveno!!!"); 
            break;
        case CHARGE: 
            temp_I = battery_Icharge_get();
             UG_PutString(10, 0, "Vzdalene rizeni"); 
             smart_siprintf(textbuff, "Napeti: %d.%02dV",12,36);//temp_U/1000,temp_U%1000/10);
             UG_PutString(10, 12, textbuff);
             smart_siprintf(textbuff, "Nab. proud: %d.%02dA",temp_I/1000,temp_I%1000/10);
             UG_PutString(10, 24, textbuff);
             smart_siprintf(textbuff, "Nabijeta C: %d.%02dAh",0,0);
             UG_PutString(10, 36, textbuff);
            break;
        case DISCHARGE: 
             temp_I = battery_Idischarge_get();
             UG_PutString(10, 0, "Vzdalene rizeni"); 
             smart_siprintf(textbuff, "Napeti: %d.%02dV",temp_U/1000,temp_U%1000);
             UG_PutString(10, 12, textbuff);
             smart_siprintf(textbuff, "Vybijeci proud: %d.%02dA",temp_I/1000,temp_I%1000);
             UG_PutString(10, 24, textbuff);
             smart_siprintf(textbuff, "Vybita C: %d.%02dAh",0,0);
             UG_PutString(10, 36, textbuff);
            break;
    }
     */
    if (remote_control)
        windows_state = REMOTE_ACCESS_WINDOW;
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
        show_charging_setup_window();
        charging_sec_t0 = TIM16_getSeconds();
        break;
    case CHARGING_WINDOW:

        show_charging_window(charging_sec_t0);
        break;
    case DISCHARGING_SETUP_WINDOW:
        show_discharging_setup_window();
        break;

    case DISCHARGING_WINDOW:
        show_discharging_window(charging_sec_t0);
        //show_acm_list(&acm);
        break;

    case REMOTE_ACCESS_WINDOW:
        show_remote_access();
        break;

    default: break;
    }

    ssd1306_Update_display();
}

void show_discharging_window(uint32_t t0)
{
    const uint8_t MenuCount = 4;
    uint8_t textbuff[40];
    uint8_t MenuShift = 0;
    uint8_t ArrowPos = 0;
    uint8_t MenuPos[MenuCount];
    static uint8_t BtnCount = 0;
    uint8_t t = TIM16_getSeconds() - t0;
    uint64_t cappacity = 0;

    if (Inputs_BTN_isBtnPressed(BTN_DOWN_MASK)) {
        BtnCount++;
        Inputs_BTN_clearBtnBuffer();
    }
    if (Inputs_BTN_isBtnPressed(BTN_UP_MASK)) {
        if (BtnCount)
            BtnCount--;
        Inputs_BTN_clearBtnBuffer();
    }


    if (Inputs_BTN_isBtnPressed(BTN_STOP_MASK)) {
        windows_state = MAIN_WINDOW;
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

    //    switch (acm) {
    //        case '1': smart_siprintf(textbuff, "!!!!!!!!!BLBOST!!!!!");
    //            UG_PutString(10, 0, textbuff);
    ////            cappacity = charge_NiMH (t, cappacity);break;        //NiMh
    //        case '2': break;                                    //NiCd
    //        case '3': cappacity = charge_Pb_Acid (t, cappacity); break;                                    //Pb_Acid
    //        case '4': break;                                    //Li_Ion
    //        case '5': break;                                    //Li_Po
    //        case '6': break;                                    //Li_FePo4
    //        default:  break;                                     //else
    //    }

    UG_FillScreen(0);
    UG_FontSelect(&FONT_5X12);

    smart_siprintf(textbuff, "Cas: %02d:%02d:%02ds", t / 3600, (t / 60) % 60, t % 60);
    UG_PutString(10, MenuPos[0], textbuff);
    smart_siprintf(textbuff, "Ivyb: %d.%02dA", 1, 01);
    UG_PutString(10, MenuPos[1], textbuff);
    smart_siprintf(textbuff, "Uvyb: %d.%02dV", 12, 14);
    UG_PutString(10, MenuPos[2], textbuff);
    if (wh_ah)
        smart_siprintf(textbuff, "Nabita kapacita: %d.%03dAh", cappacity / 3600000, cappacity % 3600000);
    if (!wh_ah)
        smart_siprintf(textbuff, "Nabita kapacita: %d.%03dWh", cappacity / 3600000000, cappacity % 3600000000);
    UG_PutString(10, MenuPos[3], textbuff);


    smart_siprintf(textbuff, "Ucc=%d.%01dV", battery_UccGet() / 1000, battery_UccGet() % 1000 / 100);
    UG_PutString(70, 0, textbuff);

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

void show_charging_window(uint32_t t0)
{
    const uint8_t MenuCount = 4;
    uint8_t textbuff[40];
    uint8_t MenuShift = 0;
    uint8_t ArrowPos = 0;
    uint8_t MenuPos[MenuCount];
    static uint8_t BtnCount = 0;
    uint8_t t = TIM16_getSeconds() - t0;
    uint64_t cappacity = 0;
    static uint32_t temp;
    if (Inputs_BTN_isBtnPressed(BTN_DOWN_MASK)) {
        BtnCount++;
        Inputs_BTN_clearBtnBuffer();
    }
    if (Inputs_BTN_isBtnPressed(BTN_UP_MASK)) {
        if (BtnCount)
            BtnCount--;
        Inputs_BTN_clearBtnBuffer();
    }


    if (Inputs_BTN_isBtnPressed(BTN_STOP_MASK)) {
        windows_state = CHARGING_SETUP_WINDOW;
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

    switch (acm) {
    case '1': smart_siprintf(textbuff, "!!!!!!!!!BLBOST!!!!!");
        UG_PutString(10, 0, textbuff);
        //            cappacity = charge_NiMH (t, cappacity);break;        //NiMh
    case '2': break; //NiCd
    case '3': cappacity = charge_Pb_Acid(t, cappacity);
        break; //Pb_Acid
    case '4': break; //Li_Ion
    case '5': break; //Li_Po
    case '6': break; //Li_FePo4
    default: break; //else
    }

    UG_FillScreen(0);
    UG_FontSelect(&FONT_5X12);

    smart_siprintf(textbuff, "Cas: %02d:%02d:%02ds", t / 3600, (t / 60) % 60, t % 60);
    UG_PutString(10, MenuPos[0], textbuff);
    temp = battery_Icharge_get();
    smart_siprintf(textbuff, "Inab: %d.%02dA", temp / 1000, temp % 1000 / 10);
    UG_PutString(10, MenuPos[1], textbuff);
    temp = battery_Uget();
    smart_siprintf(textbuff, "Unab: %d.%02dV", temp / 1000, temp % 1000 / 10);
    UG_PutString(10, MenuPos[2], textbuff);
    smart_siprintf(textbuff, "Nabita kapacita: %d.%03dAh", cappacity / 3600000, cappacity % 3600000);
    UG_PutString(10, MenuPos[3], textbuff);

    temp = battery_UccGet();
    smart_siprintf(textbuff, "Ucc=%d.%01dV", temp / 1000, temp % 1000 / 100);
    UG_PutString(70, 0, textbuff);

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

void show_acm_list(acm_list *acm, acm_process process)
{
    const uint8_t MenuCount = 2;
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
        *acm = BtnCount; // + 1;
        if (process == CHARGING)
            windows_state = CHARGING_SETUP_WINDOW;
        if (process == DISCHARGING)
            windows_state = DISCHARGING_SETUP_WINDOW;
        Inputs_BTN_clearBtnBuffer();
    }


    //    for (int i = 0; i <= MenuCount; ++i)
    //        MenuPos[i] = 100;
    //    for (int i = MenuShift; i < MenuShift + 3; ++i) {
    //        MenuPos[i] = 12 * (i - MenuShift + 1);
    //    }

    UG_FillScreen(0);

    UG_FontSelect(&FONT_5X12);
    //    UG_PutString(10, MenuPos[0], "NiMH");
    //    UG_PutString(10, MenuPos[1], "NiCd");
    UG_PutString(10, 12, "Pb-Acid"); // MenuPos[0]
    UG_PutString(10, 24, "Li-Ion"); //MenuPos[1]
    //    UG_PutString(10, MenuPos[4], "Li-Po");
    //    UG_PutString(10, MenuPos[5], "Li-FePO4");


    smart_siprintf(textbuff, "Ucc=%d.%01dV", battery_UccGet() / 1000, battery_UccGet() % 1000 / 100);
    UG_PutString(70, 0, textbuff);
    //    if (MenuShift) {
    //        smart_siprintf(textbuff, "%c", 30); //v
    //        UG_PutString(40, 00, textbuff);
    //    }
    //    if (MenuShift + 3 - MenuCount) {
    //        smart_siprintf(textbuff, "%c", 31); //^
    //        UG_PutString(40, 48, textbuff);
    //    }
    if (BtnCount)
        ArrowPos = 1;
    //    if (BtnCount == MenuCount - 1)
    //        ArrowPos = 2;

    smart_siprintf(textbuff, "%c", 16); //>
    UG_PutString(00, 12 * (ArrowPos + 1), textbuff);

    //windows_state = SETTINGS_WINDOW;

}

void show_main_window(acm_process *process)
{
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

    if (Inputs_BTN_isBtnPressed(BTN_OK_MASK) || Inputs_BTN_isBtnPressed(BTN_STOP_MASK))
        Inputs_BTN_clearBtnBuffer();

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


    smart_siprintf(textbuff, "Ucc=%d.%01dV", battery_UccGet() / 1000, battery_UccGet() % 1000 / 100);
    UG_PutString(70, 0, textbuff);
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

void show_discharging_setup_window(void)
{
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
            case 0:
                if (param_pass[1] > 1)
                    --param_pass[1];
                break;
            case 1:
                if ((param_pass[4]) >= MulSet)
                    param_pass[4] -= MulSet;
                break;
            case 2:
                if ((param_pass[5]) >= MulSet)
                    param_pass[5] -= MulSet;
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
            case 0:
                if ((param_pass[1] + 1)*(param_pass[2]) < battery_UccGet())
                    ++param_pass[1];
                break; //Ucc
            case 1:
                //if ((param_pass[2] ) < (battery_UccGet()))
                param_pass[4] += MulSet;
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
        if (SetBit) {

            if (MulSet < 1000) MulSet *= 10;
        }

        Inputs_BTN_clearBtnBuffer();
    }

    if (Inputs_BTN_isBtnPressed(BTN_RIGHT_MASK)) {
        if (!SetBit) {
            param_pass[0] = BtnCount++;
            BtnCount--;
            windows_state = CHARGING_WINDOW;
        }
        if (SetBit) {
            if (MulSet > 10) MulSet /= 10;
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
    smart_siprintf(textbuff, "Umin: %d.%02dV", (param_pass[4]) / 1000, (param_pass[4]) % 1000 / 10);
    UG_PutString(10, MenuPos[1], textbuff);
    smart_siprintf(textbuff, "Ivyb: %d.%02dA", param_pass[5] / 1000, param_pass[5] % 1000 / 10);
    UG_PutString(10, MenuPos[2], textbuff);
    smart_siprintf(textbuff, "Kapacita: %d.%02dAh", param_pass[6] / 1000), param_pass[6] % 1000;



    UG_PutString(10, MenuPos[3], textbuff);

    if (SetBit && BtnCount) {
        smart_siprintf(textbuff, "%d.%02d", MulSet / 1000, MulSet % 1000 / 10);
        UG_PutString(10, 00, textbuff);
    }


    smart_siprintf(textbuff, "Ucc=%d.%01dV", battery_UccGet() / 1000, battery_UccGet() % 1000 / 100);
    UG_PutString(70, 0, textbuff);
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
        if (millis() % 500 > 250) {
            smart_siprintf(textbuff, "%c", ' '); //>
            UG_PutString(00, 12 * (ArrowPos + 1), textbuff);
        }
    }
}

void show_charging_setup_window(void)
{
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
            case 0:
                if (param_pass[1] > 1)
                    --param_pass[1];
                break;
            case 1:
                if ((param_pass[2]) >= MulSet)
                    param_pass[2] -= MulSet;
                break;
            case 2:
                if ((param_pass[5]) >= MulSet)
                    param_pass[5] -= MulSet;
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
            case 0:
                if ((param_pass[1] + 1)*(param_pass[2]) < battery_UccGet())
                    ++param_pass[1];
                break; //Ucc
            case 1:
                if ((param_pass[2]) < (battery_UccGet()))
                    param_pass[2] += MulSet;
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
        if (SetBit) {

            if (MulSet < 1000) MulSet *= 10;
        }

        Inputs_BTN_clearBtnBuffer();
    }

    if (Inputs_BTN_isBtnPressed(BTN_RIGHT_MASK)) {
        if (!SetBit) {
            param_pass[0] = BtnCount++;
            BtnCount--;
            windows_state = CHARGING_WINDOW;
        }
        if (SetBit) {
            if (MulSet > 10) MulSet /= 10;
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
    smart_siprintf(textbuff, "Umax: %d.%02dV", (param_pass[2]) / 1000, (param_pass[2]) % 1000 / 10);
    UG_PutString(10, MenuPos[1], textbuff);
    smart_siprintf(textbuff, "Inab: %d.%02dA", param_pass[5] / 1000, param_pass[5] % 1000 / 10);
    UG_PutString(10, MenuPos[2], textbuff);
    smart_siprintf(textbuff, "Kapacita: %d.%02dAh", param_pass[6] / 1000), param_pass[6] % 1000;
    UG_PutString(10, MenuPos[3], textbuff);


    UG_PutString(10, MenuPos[3], textbuff);

    if (SetBit && BtnCount) {
        smart_siprintf(textbuff, "%d.%02d", MulSet / 1000, MulSet % 1000 / 10);
        UG_PutString(10, 00, textbuff);
    }


    smart_siprintf(textbuff, "Ucc=%d.%01dV", battery_UccGet() / 1000, battery_UccGet() % 1000 / 100);
    UG_PutString(70, 0, textbuff);
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
        if (millis() % 500 > 250) {
            smart_siprintf(textbuff, "%c", ' '); //>
            UG_PutString(00, 12 * (ArrowPos + 1), textbuff);
        }
    }
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
    init_param_pass(NO_ACM);
}

void TIM15_IRQHandler(void)
{
    if (LL_TIM_IsActiveFlag_UPDATE(TIM15) != RESET) {
        LL_TIM_ClearFlag_UPDATE(TIM15);
        UI_process();
    }
}