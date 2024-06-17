
#include <pic16f887.h>

/*
 * File:   newmain.c
 * Author: Admin
 *
 * Created on Ngày 29 tháng 4 n?m 2024, 15:36
 */
// CONFIG
#pragma config FOSC = HS// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON     // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF      // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF   
/*#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
*/
#include "lcd_8bit.h"
//#define bt = PORTAbits.RA0;

void main(void) {

    TRISC = 0;
    TRISB = 0;
    TRISD = 1; // input
    PORTD = 1;
    PORTB = 0;

    lcd_init();
    int count = 0;
    while (1) {
        setCursor(0, 0);
        lcd_string("count=");
        setCursor(6, 0);
        lcd_number(count);
        if (PORTDbits.RD0 == 0) {
            count++;
            while(PORTDbits.RD0 ==0);
        }

    }



}

/*      led 7 doan
unsigned char number_7seg[10] = {       // anode chung
    0xC0,
    0xF9,
    0xA4,
    0xB0,
    0x99,
    0x92,
    0x82,
    0xF8,
    0x80,
    0x90
};

void set_number(unsigned int num)
{// vd 1234
    int digit = num/1000; // hang ngin  -> 1
    PORTB = ~number_7seg[digit];
    PORTCbits.RC0 = 0;
    __delay_ms(2);
    PORTCbits.RC0 = 1;
    __delay_ms(2);
    
    num = num%1000; // 234
    digit = num/100; // 2
    PORTB = ~number_7seg[digit];
    PORTCbits.RC1 = 0;
    __delay_ms(2);
    PORTCbits.RC1 = 1;
    __delay_ms(2);
    
    num = num%100; // 34
    digit = num/10; // 3
    PORTB = ~number_7seg[digit];
    PORTCbits.RC2 = 0;
    __delay_ms(2);
    PORTCbits.RC2 = 1;
    __delay_ms(2);
    
    num = num%10; // 4
    digit = num/1; // 2
    PORTB = ~number_7seg[digit];
    PORTCbits.RC3 = 0;
    __delay_ms(2);
    PORTCbits.RC3 = 1;
    __delay_ms(2);
}

 */