
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
#include "eeprom.h"
#define _XTAL_FREQ 4000000


void main(void) {

    //setup pin
    TRISB = 0; // ouput
    TRISCbits.TRISC0 = 0; // output
    TRISCbits.TRISC1 = 0; // output
    TRISCbits.TRISC2 = 0; // output
    TRISCbits.TRISC3 = 0;
    PORTCbits.RC3 = 1;
    TRISCbits.TRISC7 = 1;
    TRISCbits.TRISC6 = 1; // input
    lcd_init();
    
    lcd_setCursor(0, 0);
    lcd_string("Start");
    __delay_ms(500);
    lcd_setCursor(0,0);
    lcd_string("1.Write EEPROM");
    lcd_setCursor(0,1);
    lcd_string("2.Read EEPROM");
    unsigned char value[16];
    while (1) {
        if (PORTCbits.RC7 == 0) {
            while (PORTCbits.RC7 == 0);
            lcd_setCursor(0, 0);
            lcd_string("WRITE EEPROM");
            EEPROM_write_string(0x00, "le thanh tra");
            __delay_ms(500);
            lcd_setCursor(0, 0);
            lcd_string("               ");
            lcd_clear();
            __delay_ms(100);
            lcd_setCursor(0, 0);
            lcd_string("DONE WRITE");
        }
        if (PORTCbits.RC6 == 0) {
            while (PORTCbits.RC6 == 0);
            int i = 0;
            lcd_setCursor(0, 0);
            lcd_string("Doc EEPROM");
            __delay_ms(500);
            lcd_setCursor(0, 0);
            lcd_string("               ");
            lcd_setCursor(0, 0);
            while (1) {
                value[i] = EEPROM_read(0x00 + i);
                if (value[i] == 255)
                    break;
                lcd_data(value[i]);
                i++;
            }
        }
    }
}
