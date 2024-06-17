
// PIC16F877A Configuration Bit Settings
/*
#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>

#define _XTAL_FREQ 1000000
unsigned char number_7seg[10] = {
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


void display_number(unsigned int port, unsigned int num)  // 2 so, vd so: 45
{
    
    unsigned char temp = 0;
    temp = number_7seg[num];
    if((temp & 0x01) == 0x01)
    {
        PORTBbits.RB0 = 1;
    }
    else 
        PORTBbits.RB0 = 0;
    
    
    temp = temp>>1;
    if((temp & 0x01) == 0x01)
    {
        PORTBbits.RB1 = 1;
    }
    else 
        PORTBbits.RB1 = 0;
    
    
    temp = temp>>1;
    if((temp & 0x01) == 0x01)
    {
        PORTBbits.RB2 = 1;
    }
    else 
        PORTBbits.RB2 = 0;
    
    temp = temp>>1;
    if((temp & 0x01) == 0x01)
    {
        PORTBbits.RB3 = 1;
    }
    else 
        PORTBbits.RB3 = 0;
    
    temp = temp>>1;
    if((temp & 0x01) == 0x01)
    {
        PORTBbits.RB4 = 1;
    }
    else 
        PORTBbits.RB4 = 0;
    
    temp = temp>>1;
    if((temp & 0x01) == 0x01)
    {
        PORTBbits.RB5 = 1;
    }
    else 
        PORTBbits.RB5 = 0;
    
    temp = temp>>1;
    if((temp & 0x01) == 0x01)
    {
        PORTBbits.RB6 = 1;
    }
    else 
        PORTBbits.RB6 = 0;
    
    if(port == 1)
    {
        PORTCbits.RC0 = 1;
    }
    else if(port == 2)
    {
        PORTCbits.RC1 = 1;
    }
    else
    {
        PORTCbits.RC0 = 1;
        PORTCbits.RC1 = 1;
    }
    __delay_ms(1);
}

void set_number(unsigned char num) {
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    int digit = num/10;
    display_number(1,digit);
    
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    num = num%10;
    digit = num/1;
    display_number(2,digit);
}

void main(void) {
    TRISB = 0; // output(0), input(1)
    TRISC = 0;
   
    PORTC = 0;
    PORTB = 0;
    while (1) {
        int i = 0;
        int j = 0;
        //set_number(54);
        for (i=0; i < 100; i++) {
            set_number(i);
            __delay_ms(100);
        }
        
    }

}
*/

#pragma config FOSC = HS        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#include <xc.h>

#define _XTAL_FREQ 1000000
unsigned char number_7seg[10] = {
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
{
    int digit = num/10; // hang chuc
    PORTB = number_7seg[digit];
    PORTCbits.RC0 = 1;
    __delay_ms(1);
    PORTCbits.RC0 = 0;
    
    num = num%10;
    PORTB = number_7seg[num];
    PORTCbits.RC1 = 1;
    __delay_ms(1);
    //PORTCbits.RC1 = 0;
    
}

void main()
{
    TRISB = 0;
    TRISC = 0;
    int i;
    while(1)
        for(i=0;i<100;i++)
        {
            set_number(i);
            __delay_ms(1000);
        }
}
