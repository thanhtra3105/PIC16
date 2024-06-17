
// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

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
#pragma config BOR4V = BOR21V   // Brown-out Reset Selection bit (Brown-out Reset set to 2.1V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include "lcd_8bit_1.h"
#define _XTAL_FREQ 4000000


#define I2C_LCD_ADDR 0x4E

#define I2C_LCD_Delay_Ms(u16DelayMs) __delay_ms(u16DelayMs)

#define LCD_EN 2
#define LCD_RW 1
#define LCD_RS 0
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_BL 3
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t weekDay;
uint8_t day;
uint8_t month;
uint8_t year;

void I2C_LCD_Init(void);
void I2C_LCD_Puts(char *szStr);
void I2C_LCD_Clear(void);
void I2C_LCD_NewLine(void);
void I2C_LCD_BackLight(uint8_t u8BackLight);

void i2c_init(void) {
/*
    SSPCONbits.SSPM3 = 1;
    SSPADD = 0x09;
    SSPCONbits.SSPEN = 1;
 * */
    TRISC3 = 1;
    TRISC4 = 1;
    // setup thanh ghi 1
    SSPCON = 0b00101000;
    SSPADD = _XTAL_FREQ/(100000*4)-1;
}

void i2c_start(void) {

    SSPCON2bits.SEN = 1;
    while (SSPCON2bits.SEN) {

    }
}

void i2c_stop(void) {

    SSPCON2bits.PEN = 1;
    while (SSPCON2bits.PEN) {

    }
}

uint8_t i2c_write(uint8_t u8Data) {

    PIR1bits.SSPIF = 0;
    SSPBUF = u8Data;
    while (PIR1bits.SSPIF == 0) {

    }

    return SSPCON2bits.ACKSTAT;
}

uint8_t i2c_read(uint8_t u8Ack) {
    uint8_t tmp;

    SSPCON2bits.RCEN = 1;
    while (SSPCON2bits.RCEN) {

    }
    tmp = SSPBUF;
    SSPCON2bits.RCEN = 0;
    if (u8Ack) {
        SSPCON2bits.ACKDT = 1;
    } else {
        SSPCON2bits.ACKDT = 0;
    }

    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN) {

    }

    return tmp;
}

void i2c_repeat_start(void) {

    SSPCON2bits.RSEN = 1;
    while (SSPCON2bits.RSEN) {

    }
}

void My_I2C_Init(void) {

    i2c_init();
}

void I2C_Write(uint8_t u8Address, uint8_t *pu8Data, uint8_t u8Length) {
    uint8_t i;

    i2c_start();
    i2c_write(u8Address);
    for (i = 0; i < u8Length; ++i) {
        i2c_write(pu8Data[i]);
    }
    i2c_stop();
}

void I2C_Read(uint8_t u8Address, uint8_t *pu8Data, uint8_t u8Length) {
    uint8_t i;

    i2c_start();
    i2c_write(u8Address);
    for (i = 0; i < u8Length - 1; ++i) {
        pu8Data[i] = i2c_read(0);
    }
    pu8Data[i] = i2c_read(1);
    i2c_stop();
}

static uint8_t u8LCD_Buff[8]; //bo nho dem luu lai toan bo
static uint8_t u8LcdTmp;

#define	MODE_4_BIT		0x28
#define	CLR_SCR			0x01
#define	DISP_ON			0x0C
#define	CURSOR_ON		0x0E
#define	CURSOR_HOME		0x80

static void I2C_LCD_Write_4bit(uint8_t u8Data);
static void I2C_LCD_FlushVal(void);
static void I2C_LCD_WriteCmd(uint8_t u8Cmd);

static void I2C_LCD_FlushVal(void) {
    uint8_t i;

    for (i = 0; i < 8; ++i) {
        u8LcdTmp >>= 1;
        if (u8LCD_Buff[i]) {
            u8LcdTmp |= 0x80;
        }
    }
    I2C_Write(I2C_LCD_ADDR, &u8LcdTmp, 1);
}

void I2C_LCD_Init(void) {
    uint8_t i;

    I2C_LCD_Delay_Ms(50);

    My_I2C_Init();

    for (i = 0; i < 8; ++i) {
        u8LCD_Buff[i] = 0;
    }

    I2C_LCD_FlushVal();

    u8LCD_Buff[LCD_RS] = 0;
    I2C_LCD_FlushVal();

    u8LCD_Buff[LCD_RW] = 0;
    I2C_LCD_FlushVal();

    I2C_LCD_Write_4bit(0x03);
    I2C_LCD_Delay_Ms(5);

    I2C_LCD_Write_4bit(0x03);
    I2C_LCD_Delay_Ms(1);

    I2C_LCD_Write_4bit(0x03);
    I2C_LCD_Delay_Ms(1);

    I2C_LCD_Write_4bit(MODE_4_BIT >> 4);
    I2C_LCD_Delay_Ms(1);

    I2C_LCD_WriteCmd(MODE_4_BIT);
    I2C_LCD_WriteCmd(DISP_ON);
    I2C_LCD_WriteCmd(CURSOR_ON);
    I2C_LCD_WriteCmd(CLR_SCR);
}

static void I2C_LCD_Write_4bit(uint8_t u8Data) {
    //4 bit can ghi chinh la 4 5 6 7
    //dau tien gan LCD_E=1
    //ghi du lieu
    //sau do gan LCD_E=0

    if (u8Data & 0x08) {
        u8LCD_Buff[LCD_D7] = 1;
    } else {
        u8LCD_Buff[LCD_D7] = 0;
    }
    if (u8Data & 0x04) {
        u8LCD_Buff[LCD_D6] = 1;
    } else {
        u8LCD_Buff[LCD_D6] = 0;
    }
    if (u8Data & 0x02) {
        u8LCD_Buff[LCD_D5] = 1;
    } else {
        u8LCD_Buff[LCD_D5] = 0;
    }
    if (u8Data & 0x01) {
        u8LCD_Buff[LCD_D4] = 1;
    } else {
        u8LCD_Buff[LCD_D4] = 0;
    }

    u8LCD_Buff[LCD_EN] = 1;
    I2C_LCD_FlushVal();

    u8LCD_Buff[LCD_EN] = 0;
    I2C_LCD_FlushVal();

}

void LCD_WaitBusy(void) {
    char temp;

    //dau tien ghi tat ca 4 bit thap bang 1
    u8LCD_Buff[LCD_D4] = 1;
    u8LCD_Buff[LCD_D5] = 1;
    u8LCD_Buff[LCD_D6] = 1;
    u8LCD_Buff[LCD_D7] = 1;
    I2C_LCD_FlushVal();

    u8LCD_Buff[LCD_RS] = 0;
    I2C_LCD_FlushVal();

    u8LCD_Buff[LCD_RW] = 1;
    I2C_LCD_FlushVal();

    do {
        u8LCD_Buff[LCD_EN] = 1;
        I2C_LCD_FlushVal();
        I2C_Read(I2C_LCD_ADDR + 1, &temp, 1);

        u8LCD_Buff[LCD_EN] = 0;
        I2C_LCD_FlushVal();
        u8LCD_Buff[LCD_EN] = 1;
        I2C_LCD_FlushVal();
        u8LCD_Buff[LCD_EN] = 0;
        I2C_LCD_FlushVal();
    } while (temp & 0x08);
}

static void I2C_LCD_WriteCmd(uint8_t u8Cmd) {

    LCD_WaitBusy();

    u8LCD_Buff[LCD_RS] = 0;
    I2C_LCD_FlushVal();

    u8LCD_Buff[LCD_RW] = 0;
    I2C_LCD_FlushVal();

    I2C_LCD_Write_4bit(u8Cmd >> 4);
    I2C_LCD_Write_4bit(u8Cmd);
}

void LCD_Write_Chr(char chr) {

    LCD_WaitBusy();
    u8LCD_Buff[LCD_RS] = 1;
    I2C_LCD_FlushVal();
    u8LCD_Buff[LCD_RW] = 0;
    I2C_LCD_FlushVal();
    I2C_LCD_Write_4bit(chr >> 4);
    I2C_LCD_Write_4bit(chr);

}

void I2C_LCD_Puts(char *sz) {

    while (1) {
        if (*sz) {
            LCD_Write_Chr(*sz++);
        } else {
            break;
        }
    }
}

void I2C_LCD_Clear(void) {

    I2C_LCD_WriteCmd(CLR_SCR);
}

void I2C_LCD_NewLine(void) {

    I2C_LCD_WriteCmd(0xc0);
}

void I2C_LCD_BackLight(uint8_t u8BackLight) {

    if (u8BackLight) {
        u8LCD_Buff[LCD_BL] = 1;
    } else {
        u8LCD_Buff[LCD_BL] = 0;
    }
    I2C_LCD_FlushVal();
}
/*
void lcd_number(unsigned int num) {
    if (num < 10)
    {
        LCD_Write_Chr(48);
        LCD_Write_Chr(num+48);
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
            LCD_Write_Chr(a[count] + 48);
            count--;
        }
    }
}
*/
void ds1307_init() {
    i2c_init(); //100khz
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x07); // thanh ghi SQW/OUT
    i2c_write(0x00); // enable SQW/OUT
    i2c_stop();
}
uint8_t Decimal_To_BCD(uint8_t number)
{
    return(((number/10)<<4)+(number%10));
}

uint8_t BCD_To_Decimal(uint8_t number) 
{
  return((number >> 4)*10 +(number & 0x0F));
}
void ds1307_setTime()
{
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00);// thanh ghi second
    i2c_write(Decimal_To_BCD(0));    //0s
    i2c_write(Decimal_To_BCD(0));    //5p
    i2c_write(Decimal_To_BCD(13));    //10h
    i2c_write(Decimal_To_BCD(4));    //T3
    i2c_write(Decimal_To_BCD(12));    //ngay 11
    i2c_write(Decimal_To_BCD(6));    // thang 6
    i2c_write(Decimal_To_BCD(24));    //nam 24
    i2c_stop();
}
void i2c_readTime() {
    /*i2c_start();
    i2c_write(0xD0);
    i2c_write(0x01); // thanh ghi second
    i2c_repeat_start();
    i2c_write(0xD1);
    //second = BCD_To_Decimal(i2c_read(1));
    minute = BCD_To_Decimal(i2c_read(1));
    hour = BCD_To_Decimal(i2c_read(1));
    weekDay = BCD_To_Decimal(i2c_read(1));
    day = BCD_To_Decimal(i2c_read(1));
    month = BCD_To_Decimal(i2c_read(1));
    year = BCD_To_Decimal(i2c_read(0));
    i2c_stop();
    */
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00); // thanh ghi second
    i2c_repeat_start();
    i2c_write(0xD1);
    second = BCD_To_Decimal(i2c_read(1));
    i2c_stop();
    
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x01); // thanh ghi minute
    i2c_repeat_start();
    i2c_write(0xD1);
    minute = BCD_To_Decimal(i2c_read(1));
    i2c_stop();
    
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x02); // thanh ghi minute
    i2c_repeat_start();
    i2c_write(0xD1);
    hour = BCD_To_Decimal(i2c_read(1));
    i2c_stop();
    
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x03); // thanh ghi minute
    i2c_repeat_start();
    i2c_write(0xD1);
    weekDay = BCD_To_Decimal(i2c_read(1));
    i2c_stop();
    
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x04); // thanh ghi minute
    i2c_repeat_start();
    i2c_write(0xD1);
    day = BCD_To_Decimal(i2c_read(1));
    i2c_stop();
    
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x05); // thanh ghi minute
    i2c_repeat_start();
    i2c_write(0xD1);
    month = BCD_To_Decimal(i2c_read(1));
    i2c_stop();
    
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x06); // thanh ghi minute
    i2c_repeat_start();
    i2c_write(0xD1);
    year = BCD_To_Decimal(i2c_read(1));
    i2c_stop();
   
}

void main(void) {
    
/*
    I2C_LCD_Init();
    ds1307_init();
    I2C_LCD_Clear();
    I2C_LCD_BackLight(1);
    I2C_LCD_Puts("le thanh tra");
    I2C_LCD_NewLine();
    I2C_LCD_Puts("hiii");
    
    I2C_LCD_WriteCmd(0x01);
    ds1307_setTime();
    I2C_LCD_NewLine();
    I2C_LCD_Puts("da set");
    __delay_ms(1000);
    while(1)
    {
        i2c_readTime();
        I2C_LCD_WriteCmd(0x80);
        lcd_number(hour);
        I2C_LCD_Puts(":");
        lcd_number(minute);
        I2C_LCD_Puts(":");
        lcd_number(second);
        
        // hien ngay
        I2C_LCD_WriteCmd(0xC0);
        lcd_number(weekDay);
        I2C_LCD_Puts(" ");
        lcd_number(day);
        I2C_LCD_Puts("/");
        lcd_number(month);
        I2C_LCD_Puts("/");
        lcd_number(20);
        lcd_number(year);
    }
*/
    
    lcd_init();
    ds1307_init();
    lcd_setCursor(0,0);
    lcd_string("Start");
    __delay_ms(1000);
    lcd_command(0x01);
    while(1)
    {
        i2c_readTime();
        lcd_setCursor(0,0);
        lcd_number(second);
    }
}