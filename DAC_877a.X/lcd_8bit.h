

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_8BIT_H
#define	LCD_8BIT_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define RS PORTCbits.RC0
#define RW PORTCbits.RC1
#define E PORTCbits.RC2
unsigned int _XTAL_FREQ = 4000000;


void lcd_command(unsigned char cmd) {
    RS = 0x00; // che do cmd
    RW = 0x00;
    E = 0x01;
    PORTD = cmd;
    E = 0;
    __delay_ms(1);
}

void lcd_data(unsigned char Data) {
    RS = 1; // data mode
    RW = 0;
    E = 1;
    PORTD = Data;
    E = 0;
    __delay_ms(1);
}

void lcd_init() {
    lcd_command(0x0C);
    lcd_command(0x38);
    lcd_command(0x80); // set vi tri hang 1 cot 1

}

void lcd_string(char *string_data) {
    int i = 0;
    for (i = 0; string_data[i] != 0; i++) {
        lcd_data(string_data[i]);
    }
}

void lcd_number(unsigned int num) {
    if (num < 10)
    {
        lcd_data(num+48);
    }
    else {
        unsigned int temp;
        int a[16];
        int count = 0;
        while (num >= 10) { // vd 451
            temp = num % 10; //1     5
            a[count] = temp; //1     5
            num /= 10; //45    4
            count++; // 1    2
        }
        a[count] = num;
        while (count >= 0) {
            lcd_data(a[count] + 48);
            count--;
        }
    }
}

void lcd_setCursor(unsigned char x, unsigned char y) // x; cot, y: hang. hang 1(8x), hang 2 (Cx), x: 0->F(16)  
{
    if (x >= 0 && x < 16) {
        if (y == 0) // 8x
        {
            lcd_command(0x80 + x);

        } else if (y == 1) // Cx
        {
            lcd_command(0xC0 + x);
        }
    }
}


#endif	/* XC_HEADER_TEMPLATE_H */

