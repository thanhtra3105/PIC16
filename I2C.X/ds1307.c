/*
#include "ds1307.h"
#include "i2c.h"
struct Time time;

void ds1307_init()
{
    i2c_init(100000);//100khz
    i2c_start();
    i2c_write(DATA_WRITE_ADD);
    i2c_write(0x07);    // thanh ghi SQW/OUT
    i2c_write(0x00);    // enable SQW/OUT
    i2c_stop();
}
void ds1307_setTime()
{
    i2c_start();
    i2c_write(DATA_WRITE_ADD);
    i2c_write(0x00);// thanh ghi second
    i2c_write(0x00);    //0s
    i2c_write(0x05);    //5p
    i2c_write(0x0A);    //10h
    i2c_write(0x03);    //T3
    i2c_write(0x0B);    //ngay 11
    i2c_write(0x06);    // thang 6
    i2c_write(0x18);    //nam 24
    i2c_stop();
}
void i2c_readTime()
{
    i2c_start();
    i2c_write(DATA_WRITE_ADD);
    i2c_write(0x00);// thanh ghi second
    i2c_repeat_st();
    i2c_write(DATA_READ_ADD);
    time.second = i2c_read(1);
    time.minute = i2c_read(1);
    time.hour = i2c_read(1);
    time.weekDay = i2c_read(1);
    time.day = i2c_read(1);
    time.month = i2c_read(1);
    time.year = i2c_read(0);
    i2c_stop();
}
 * */