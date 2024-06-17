// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 20000000
#define TMR2_PRESCALE 4
int temp_freq;

void PWM_start() {
    CCP2M3 = 1;
    CCP2M2 = 1;
#if TMR2_PRESCALE == 1
    T2CKPS1 = 0;
    T2CKPS0 = 0;
#elif TMR2_PRESCALE == 4
    T2CKPS1 = 0;
    T2CKPS0 = 0;
#elif TMR2_PRESCALE == 16
    T2CKPS1 = 1;
    T2CKPS0 = 1;
#endif
    TMR2ON = 1;
    TRISC1 = 0;
}

void PWM_setup(long freq) {
    PR2 = _XTAL_FREQ / (4 * freq * TMR2_PRESCALE) - 1;
    temp_freq = freq;
}

void PWM(unsigned int duty) {
    
    if (duty < 1024) {
        duty = (duty / 1023.0)*(_XTAL_FREQ / (temp_freq * TMR2_PRESCALE));
        CCP2X = duty & 2;
        CCP2Y = duty & 1;
        CCPR2L = duty >> 2;
    }
}

void main(void) {
    PWM_setup(5000); //250
    PWM(1023);
    PWM_start();
    while (1) {

    }
}

