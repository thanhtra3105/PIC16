/*
 * File:   newmain.c
 * Author: Admin
 *
 * Created on Ngày 01 tháng 5 n?m 2024, 12:10
 */
// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ  4000000
// Qua bo chia 4 -> 1M       chia 32 = 
// 1T = 1/31250 s
// 31.25T = 1ms
// 256-31 = 225

int count = 0;
int count2 = 0;
void Timer0_cfg() { // co ngat
    INTCONbits.GIE = 1; // enable interupt global   
    INTCONbits.TMR0IE = 1; // enable interrupt 
    INTCONbits.TMR0IF = 0; // clear interrupt flag

    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 0;
    TMR0 = 225;
}

void Timer1_cfg() {
    GIE = 1; // enable interupt global   
    PEIE = 0;
    TMR1IE = 1; // enable interrupt 
    TMR1IF = 0; // clear interrupt flag
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.T1CKPS0 = 1;
    T1CONbits.T1OSCEN = 1;
    T1CONbits.T1SYNC = 0; // khi  TMR1CS = 0; focs/4
    T1CONbits.TMR1CS = 0;
    TMR1ON = 1;
    TMR1H = 254;
    TMR1L = 12;
    //while (!TMR1IF);

}

void Timer2_cfg()
{
    GIE = 0; // enable interupt global   
    //PEIE = 0;
    TMR2IE = 0; // enable interrupt 
    TMR2IF = 0; // clear interrupt flag
    
    TOUTPS3 = 0;
    TOUTPS2 = 0;
    TOUTPS1 = 0;
    TOUTPS0 = 0;
    TMR2ON = 1;
    T2CKPS1 = 0;
    T2CKPS0 = 1;
}

void delay_ms_TMR0(int time) {
    while (time--) {
        INTCONbits.TMR0IF = 0; // clear 
        TMR0 = 225;
        while (!INTCONbits.TMR0IF); // chay cho den khi falg len 1
    }
}

void delay_ms_TMR1(int time) {
    while (time--) {
        // 4M/4 = 1M        // muon delay 1ms thi T = 2k -> T/2 = 1k
        // 1ms -> theo ct qua bo chia 2 -> TMR1 = 65286 -> TMR1H = TMR1/256 = 255, TMR1L = 6
        TMR1H = 254;
        TMR1L = 12;
        TMR1IF = 0;
        while (!TMR1IF);
    }
}

void delay_ms_TMR2(int time) {
    while (time--) {
        TMR2 = 6;
        TMR2IF = 0;
        while (!TMR2IF);
    }
}

void __interrupt(high_priority) IRS(void) {

    if ((INTCONbits.TMR0IF == 1) && (INTCONbits.TMR0IE == 1)) {
        count++;
        TMR0 = 225;
        INTCONbits.TMR0IF = 0; // clear flag
    }
    
    if ((TMR1IF == 1) && (TMR0IE == 1)) {
        count2++;
        TMR1H = 254;
        TMR1L = 12;
        TMR1IF = 0;
    }
    if(count == 1)
    {
        PORTBbits.RB0 = ~PORTBbits.RB0;
        count = 0;
    }
    if(count2 == 2)
    {
        PORTBbits.RB1 = ~PORTBbits.RB1;
        count2 =0;
    }
}

void main(void) {
    TRISB = 0; // output
    PORTB = 0;
    //Timer0_cfg();
    //Timer1_cfg();
    Timer2_cfg();
    while (1) {
        delay_ms_TMR2(1);
        PORTB = ~PORTB;
    }

}
