// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include "lcd_8bit.h"
#include "ds1307.h"
#define _XTAL_FREQ 4000000
void main()
{
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    TRISD = 0;
    lcd_init();
    ds1307_init();
    //ds1307_setTime(7,15,06,24,12,16,0);
    lcd_setCursor(0,0);
    lcd_string("da set tgian");
    __delay_ms(1000);
    lcd_command(0x01);
    while(1)
    {
       
        i2c_readTime();
        lcd_setCursor(0,0);
        // time
        lcd_number(hour);
        lcd_string(":");
        lcd_number(minute);
        lcd_string(":");
        lcd_number(second);
        //Date
        lcd_setCursor(0,1);
        if(weekDay > 1)
        {    
            lcd_string("T");
            lcd_number(weekDay);
        }
        else
            lcd_string("CN");
        lcd_string(" ");
        lcd_number(day);
        lcd_string("/");
        lcd_number(month);
        lcd_string("/");
        lcd_number(year);
      
    }
}