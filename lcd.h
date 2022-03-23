#ifndef LCD_H_
#define LCD_H_

    #define LCDPORT                          GPIO_PORTB_BASE
    #define RS                               GPIO_PIN_0
    #define E                                GPIO_PIN_1

    // 4 bit olacaksa sadece bunlar.
    #define D4                               GPIO_PIN_4
    #define D5                               GPIO_PIN_5
    #define D6                               GPIO_PIN_6
    #define D7                               GPIO_PIN_7

    // 8 bit olacaksa asagidaki baglantilari da ekle.
    #define D0                               GPIO_PIN_0
    #define D1                               GPIO_PIN_1
    #define D2                               GPIO_PIN_2
    #define D3                               GPIO_PIN_3


    // fonksiyon prototipleri
    void Lcd_ilk_ayarlar();
    void Lcd_Komut_Gonder(unsigned char c) ;
    void Lcd_Tek_Karakter_Yaz(unsigned char d) ;
    void Lcd_Satir_Sutuna_Git(char x, char y);
    void Lcd_Temizle(void);
    void Lcd_Cok_Karakter_Yaz(unsigned char  dizi[], int dizisayisi);

#endif /* LCD_H_ */
