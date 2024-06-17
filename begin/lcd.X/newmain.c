/*
 * File:   newmain.c
 * Author: Admin
 *
 * Created on Ngày 29 tháng 4 n?m 2024, 15:36
 */
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)


#include "lcd_8bit.h"
//#define bt = PORTAbits.RA0;

void main(void) {
    TRISA = 0;
    TRISC = 0;
    TRISD = 0; // output
    PORTD = 0;

    TRISBbits.TRISB0 = 1; //input
    TRISAbits.TRISA1 = 0; //output
    PORTA = 0;
    int count = 0;
    lcd_init();
    lcd_setCursor(0, 0);
    lcd_string("count=");
    lcd_setCursor(6, 0);
    lcd_number(count);
    while (1) {
        //PORTBbits.RB0 = 0;
        if (PORTBbits.RB0 == 0) {
            count++;
            //PORTAbits.RA1 = ~PORTAbits.RA1;
            lcd_setCursor(6, 0);
            lcd_number(count);
            while(PORTBbits.RB0 == 0);
            if(count %2 ==0)
            {
                PORTAbits.RA1 = 1;
            }
            else
                PORTAbits.RA1 = 0;
        }

        //PORTAbits.RA1 = 1;
    }
}