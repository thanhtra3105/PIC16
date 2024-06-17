

// CONFIG1
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
#define _XTAL_FREQ 20000000
/*
 1T = 1M/16s
 250   0.1ms
 */
int count=0;
void TM0_setup()
{
    T0IE = 1; // enable interrupt
    GIE = 1;    // global interrupt
    T0CS = 0;
    T0SE = 0;
    PSA = 0;
    PS2 = 0;
    PS1 = 1;
    PS0 = 1;  // bo chia 16 prescale
    TMR0 = 251;
 
}

void __interrupt(high_priority) IRS(void){
    if(T0IF == 1)// sau 1ms thi T0 flag se set len 1
    {
        count++;
        TMR0 =251;
        T0IF = 0;// clear
    }

}
int map(int value)
{
    // count == 19 <=> toggle = 180
        //         10              0   
        //  x = [value_convert/(in_max - in_min)](out_max - out_min) + out_min
        // vd: x = [90/(180-0)]*(19-10)+ 10 = 14.5
        
    return (value*10)/180.0 + 10;
}
void SERVO_write(int tog)
{
    
    if(count >=0 && count < tog)
        {
            PORTD = 1;
        }
        else if(count < 190)
        {
            PORTD = 0;
            
        }
        else if(count == 190)
            count =0;
}

void main(void) {
    TRISD = 0;
    PORTD = 0;
    TM0_setup();
    int t;
    t = map(90);
    while(1)
    {
        SERVO_write(t);
    }
}

