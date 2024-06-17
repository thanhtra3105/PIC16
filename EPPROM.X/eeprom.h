#ifndef EEPROM_H
#define EEPROM_H


void EEPROM_write(unsigned char ADR, unsigned char Data) {
    EEADR = ADR;
    EEDAT = Data;
    //EEPGD = 0;
    WREN = 1;
    GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    WR = 1;
    WREN = 0;
    while (!EEIF);
    EEIF = 0;
}

void EEPROM_write_string(unsigned char ADR, unsigned char *Data) {
    int i = 0;
    for (i = 0; Data[i] != 0; i++) {
        EEPROM_write(ADR + i, Data[i]);
    }
}

unsigned char EEPROM_read(unsigned char ADR) {
    unsigned char Data;
    EEADR = ADR;
    EEPGD = 0;
    RD = 1;
    Data = EEDAT;
    return Data;
}
#endif