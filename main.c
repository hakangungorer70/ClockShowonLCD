#include "stdint.h"
#include "stdbool.h"
#include "math.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/gpio.h"
#include "lcd.h"
#include "zamanlayici.h"



void main()
 {
    initSettings();
    timerSettings();
    initSaatVariables(0,0,0);
    Lcd_ilk_ayarlar();
    Lcd_Satir_Sutuna_Git(0,7);
    unsigned char metin[]={'O','D','E','V','2',':','T','I','M','E','R'};

    while(1){

        SysCtlDelay(5000000);
        //Lcd_ilk_ayarlar();
        Lcd_Satir_Sutuna_Git(0,7);
        timerInterrupt();
//        SysCtlDelay(10000);
        Lcd_Satir_Sutuna_Git(2,5);
//        SysCtlDelay(10000);
       Lcd_Cok_Karakter_Yaz(metin, 11);
    }
}


