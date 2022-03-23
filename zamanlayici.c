#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "zamanlayici.h"
#include "lcd.h"

/* PROJEDE KULLANILAN FONKSÝYONLAR*/
void initSaatVariables(int saniye,int dakika,int saat)
{
    saniye=saniye;
    dakika=dakika;
    saat=saat;
}
void initSettings()
{
    SYSCTL_RCGCGPIO_R|=(1<<5); //GPIO PORTF is enabled
    GPIO_PORTF_LOCK_R|=GPIO_LOCK_KEY; //GPIO LOCK is disabled
    GPIO_PORTF_CR_R|=(1<<0);
    GPIO_PORTF_DIR_R|=(1<<1)|(1<<2)|(1<<3); //portf 1-2-3 is output
    GPIO_PORTF_DIR_R&=~(1<<4)|~(1<<0); //portf 0-4 is input
    GPIO_PORTF_DEN_R|=(1<<4)|(1<<3)|(1<<2)|(1<<1)|(1<<0); //all portf is digital enable
    GPIO_PORTF_PUR_R|=(1<<4)|(1<<0); //pf0-pf4 is pull up resistor
}
void timerSettings()
{
    SYSCTL_RCGCTIMER_R|=(1<<0); //timer0 is active
    TIMER0_CTL_R&=~(1<<0);   //timer0_ctl_r&=0xFFFE;
    TIMER0_CFG_R=0x00;
    TIMER0_TAMR_R|=(1<<1);   //periodic timer
    TIMER0_TAMR_R&=~(1<<4);  //count down mode
    TIMER0_TAILR_R=16000000-1; //frequency is 16mhz
    TIMER0_CTL_R|=(1<<0);    //timerA is active
}
void timerInterrupt()
{
    if((TIMER0_RIS_R &=0x01)==1)
    {
        /*Bu kýsýma girildiyse Gerçek zamanda 1 saniye geçmiþtir */
        TIMER0_ICR_R|=0x01;     //timer flag is cleared
        calculateSaatVariables();
        showSaatVariables(saat,dakika,saniye);

    }
}
void calculateSaatVariables()
{
    saniye=saniye+1;
    if(saniye==60)
    {
        dakika=dakika+1;
        saniye=0;
        if(dakika==60)
        {
            saat=saat+1;
            dakika=0;
            if(saat==24)
            {
                saat=0;
                dakika=0;
                saniye=0;
            }
        }
    }
}

void showSaatVariables(int saat,int dakika,int saniye)
{
    int saatonlar,saatbirler,dakikaonlar,dakikabirler,saniyeonlar,saniyebirler;

    saatbirler=saat%10;
    saatonlar=(saat-saatbirler)/10;

    dakikabirler=dakika % 10;
    dakikaonlar=(dakika-dakikabirler)/10;

    saniyebirler=(saniye)%10;
    saniyeonlar=(saniye-saniyebirler)/10;

    char saatchonlar,saatchbirler,dakikachonlar,dakikachbirler,saniyechonlar,saniyechbirler;

    saatchonlar=saatonlar+48;
    saatchbirler=saatbirler+48;
    Lcd_Tek_Karakter_Yaz(saatchonlar);
    Lcd_Tek_Karakter_Yaz(saatchbirler);
    Lcd_Tek_Karakter_Yaz(0x3A);

    dakikachonlar=dakikaonlar+48;
    dakikachbirler=dakikabirler+48;
    Lcd_Tek_Karakter_Yaz(dakikachonlar);
    Lcd_Tek_Karakter_Yaz(dakikachbirler);
    Lcd_Tek_Karakter_Yaz(0x3A);

    saniyechonlar=saniyeonlar+48;
    saniyechbirler=saniyebirler+48;
    Lcd_Tek_Karakter_Yaz(saniyechonlar);
    Lcd_Tek_Karakter_Yaz(saniyechbirler);
}



