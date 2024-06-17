
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)


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
    lcd_command(0x01);
    while(1)
    {
        value = ADC_read();
        value = value/2;

        lcd_setCursor(0,0);
        lcd_number(value);
        
        lcd_string("    ");
        
    }
    
}
