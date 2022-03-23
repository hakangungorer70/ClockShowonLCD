#ifndef ZAMANLAYICI_H_
#define ZAMANLAYICI_H_


/* Fonksiyon Prototipleri */
int saniye,dakika,saat;
void initSaatVariables(int saniye,int dakika,int saat);
void initSettings();
void timerSettings();
void timerInterrupt();
void calculateSaatVariables();
void showSaatVariables(int saat1,int dakika1,int saniye1);


#endif /* ZAMANLAYICI_H_ */
