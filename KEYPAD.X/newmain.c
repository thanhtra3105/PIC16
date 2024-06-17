
// => C[4] = {3.2.1.0}
// => R[4] = {7,6,5,4}
// CONFIG1
#pragma config FOSC = HS// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON     // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = ON         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = ON        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF      // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
#include <xc.h>
#include "lcd_8bit.h"
#include "keypad4x4.h"
#define _XTAL_FREQ 4000000


void main(void) {

    TRISB = 0;
    TRISC = 0;
    TRISD = 0xF0;      // cot input, hang ouput
    lcd_init();
    lcd_setCursor(0, 0);
    lcd_string("Nhan phim");
    __delay_ms(500);
    lcd_clear();

    while (1) {
        keypad_scan();
        lcd_setCursor(0,0);
        lcd_data(keypad[row - 1][col - 1]);
    }
}
