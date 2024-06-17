/*
 * File:   newmain.c
 * Author: Admin
 *
 * Created on Ngày 30 tháng 4 n?m 2024, 16:18
 */

#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
unsigned char Value = 0x00;
void write_EEPROM(unsigned char adr, unsigned char Data)
{
    EEADR = adr;
    EEDATA = Data;
    //WR = 1;
    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;     // ngat
    EECON2 = 0x55;
    EECON2 = 0xAA;
    //INTCONbits.GIE = 1;     // bat interrupt
    EECON1bits.WR = 1;
    EECON1bits.WREN = 0;
    while(PIR2bits.EEIF == 0);
    PIR2bits.EEIF == 0;
}

unsigned char read_EEPROM(unsigned char adr)
{
    EEADR = adr;
    EECON1bits.EEPGD = 0x00;
    EECON1bits.RD = 1;
    return EEDATA;
}

void read_Flash(unsigned char adr)
{
    EEADRH = adr;
    EECON1bits.EEPGD = 0x00;
    EECON1bits.RD = 1;
    return EEDATH;
}

void write_Flash(unsigned char adr, unsigned char Data)
{
    
}

void main(void) {
    
    write_EEPROM(0xF0, 0x22);
    Value = read_EEPROM(0xF0);
}
