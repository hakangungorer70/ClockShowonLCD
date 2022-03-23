#include "stdbool.h"
#include "stdint.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "lcd.h"

void otuzHexgonder()
{
    GPIOPinWrite(LCDPORT, RS,  0x00 );

    GPIOPinWrite(LCDPORT, D4 | D5 | D6 | D7,  0x30 );
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(2000);
}

void enableAckapa()
{
    GPIOPinWrite(LCDPORT, E, 0x02);
    SysCtlDelay(10);
    GPIOPinWrite(LCDPORT, E, 0x00);

    SysCtlDelay(2000);
}

void Lcd_ilk_ayarlar() {

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(LCDPORT, 0xFF);

    SysCtlDelay(2000);

    otuzHexgonder();
    otuzHexgonder();
    otuzHexgonder();
//    Lcd_Satir_Sutuna_Git(1,7);
    Lcd_Komut_Gonder(0x0F); //ekran, kursör,blink acýk
    Lcd_Komut_Gonder(0x01); //ekran sil
    Lcd_Komut_Gonder(0x06); //kursor artar, karakterler kaymaz
    Lcd_Komut_Gonder(0x20); // 4 bit 5x7 1 satýr


    enableAckapa();

    Lcd_Temizle();

}
void Lcd_Komut_Gonder(unsigned char c) {
    GPIOPinWrite(LCDPORT,RS,0);
    GPIOPinWrite(LCDPORT,D4|D5|D6|D7,(c & 0xF0));
    enableAckapa();
    GPIOPinWrite(LCDPORT,RS,0);
    GPIOPinWrite(LCDPORT,D4|D5|D6|D7,(c & 0x0F)<<4);
    enableAckapa();
}
void Lcd_Tek_Karakter_Yaz(unsigned char d) {
    GPIOPinWrite(LCDPORT,RS,1);
    GPIOPinWrite(LCDPORT,D4|D5|D6|D7,(d & 0xF0));
    enableAckapa();

    SysCtlDelay(2000);

    GPIOPinWrite(LCDPORT,RS,1);
    GPIOPinWrite(LCDPORT,D4|D5|D6|D7,(d & 0x0F)<<4);
    enableAckapa();
}
void Lcd_Satir_Sutuna_Git(char x, char y){
    if (x==0) {
        Lcd_Komut_Gonder(0x80 + (y % 16));
           return;
       }
    Lcd_Komut_Gonder(0xBF + (y % 16));
}
void Lcd_Temizle(void){

    Lcd_Komut_Gonder(0x01);
    SysCtlDelay(10);
}
void Lcd_Cok_Karakter_Yaz(unsigned char dizi[], int dizisayisi){

    int i;
    for (i=0; i<dizisayisi; i++)
    {
        Lcd_Tek_Karakter_Yaz(dizi[i]);
    }
    SysCtlDelay(2000);
}


