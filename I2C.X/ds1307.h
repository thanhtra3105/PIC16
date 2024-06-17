
#ifndef DS1307_H
#define DS1307_H
#include "i2c.h"
#define DATA_WRITE_ADD 0xD0
#define DATA_READ_ADD 0xD1


uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t weekDay;
uint8_t day;
uint8_t month;
uint8_t year;


//struct Time time;

uint8_t Decimal_To_BCD(uint8_t number) {
    return (((number / 10) << 4)+(number % 10));
}

uint8_t BCD_To_Decimal(uint8_t number) {
    return ((number >> 4)*10 + (number & 0x0F));
}

void ds1307_init() {
    i2c_init(); //100khz
    i2c_start();
    i2c_write(DATA_WRITE_ADD);
    i2c_write(0x07); // thanh ghi SQW/OUT
    i2c_write(0x00); // enable SQW/OUT
    i2c_stop();
}

void ds1307_setTime(int dow, int date, int mo, int yr, int hr, int mi, int se) {
    i2c_start();
    i2c_write(0xD0);
    i2c_write(0x00);// thanh ghi second
    i2c_write(Decimal_To_BCD(se));    //0s
    i2c_write(Decimal_To_BCD(mi));    //5p
    i2c_write(Decimal_To_BCD(hr));    //10h
    i2c_write(Decimal_To_BCD(dow));    //T3
    i2c_write(Decimal_To_BCD(date));    //ngay 11
    i2c_write(Decimal_To_BCD(mo));    // thang 6
    i2c_write(Decimal_To_BCD(yr));    //nam 24
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
#endif
