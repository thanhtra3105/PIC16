
// CONFIG1
// CONFIG
/*
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
*/
#include <xc.h>
#include "lcd_8bit.h"
void ADC_init()
{
    ADCON0 = 0b00000001;
    ADCON1 = 0b10000000;
}

unsigned int ADC_read()
{
    /*if(channel >7)
        return;
    ADCON0 = (1<<1) | (channel < 3);*/
    GO_nDONE = 1;
    while(GO_nDONE);
    return ((ADRESH << 8)+ ADRESL);
}


void main(void) {
    TRISC = 0;
    TRISD = 0;
    PORTD = 0;
    unsigned int value = 0;
    lcd_init();
    ADC_init();
    while(1)
    {
        value = ADC_read();
        value = value/(1.0*62/30);
        lcd_setCursor(0,0);
        lcd_number(value);
        __delay_ms(10);
        lcd_string("       ");
        lcd_setCursor(0,1);
        lcd_string("tra");
    }
    
}
