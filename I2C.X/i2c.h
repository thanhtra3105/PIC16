
#ifndef I2C_H
#define I2C_H

#define _XTAL_FREQ 4000000
#define SDA TRISCbits.TRISC4
#define SCL TRISCbits.TRISC3

void i2c_init()
{
    SDA = 1;
    SCL = 1;
    // setup thanh ghi 1
    SSPCON = 0b00101000;
    SSPADD = _XTAL_FREQ/(100000*4)-1;
}
void i2c_start()
{
    SEN = 1;
    while(SEN);
}
void i2c_repeat_start()
{
    RSEN = 1;
    while(RSEN);
}
void i2c_stop()
{
    PEN = 1;
    while(PEN);
}
void i2c_write(char Data)
{
    SSPBUF = Data;
    while(BF); // doi cho transit 
}

uint8_t i2c_read(uint8_t u8Ack) {
    uint8_t tmp;

    SSPCON2bits.RCEN = 1;       // enable Receive
    while(BF == 0);     // doi SSPBUF data
    tmp = SSPBUF;       // lay data tu thanh ghi SSPBUF
    SSPCON2bits.RCEN = 0;
    if (u8Ack) {    // set ACK hay k
        SSPCON2bits.ACKDT = 1;
    } else {
        SSPCON2bits.ACKDT = 0;
    }

    SSPCON2bits.ACKEN = 1;
    //while (SSPCON2bits.ACKEN);

    return tmp;
}

#endif
