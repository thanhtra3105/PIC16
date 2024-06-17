#ifndef UART_H
#define	UART_H

#define _XTAL_FREQ 4000000
void UART_init(int baud) {
    TRISCbits.TRISC6 = 0; // Configure Rx pin as input and Tx as output  
    TRISCbits.TRISC7 = 1;
    // setup TXSTA 
    TXSTAbits.SYNC = 0;     // che do ko dong bo/Asynchronous mode
    //RCSTAbits.SPEN = 1;
    TXSTAbits.TXEN = 1;
    if(baud < 9600)
    {
        SPBRG = (_XTAL_FREQ / (long) (64UL * baud)) - 1; // baud rate @4Mhz Clock
        TXSTAbits.BRGH = 0; // o che do thap thi set = 0; muc low speed
    }
    else if(baud <=19200)
    {
        SPBRG = (_XTAL_FREQ / (long) (16UL * baud)) - 1; // baud rate @4Mhz Clock
        TXSTAbits.BRGH = 1; // o toc do cao thi set muc 1, muc high speed
    }
    else
    {
        SPBRG = (_XTAL_FREQ / (long) (4UL * baud)) - 1; // baud rate @4Mhz Clock
        TXSTAbits.BRGH = 1; // o toc do cao thi set muc 1, muc high speed
        BAUDCTLbits.BRG16 = 1;
        TXSTAbits.SYNC = 1; 
    }
    
    // setup RX
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;
    
}


void UART_write(char ch) {
    while (TXIF == 0); // Wait till the transmitter register becomes empty
    TXIF = 0; // Clear transmitter flag
    TXREG = ch; // load the char to be transmitted into transmit reg
}

char UART_read() {
    while (RCIF == 0); // Wait till the data is received 
    RCIF = 0; // Clear receiver flag
    return (RCREG); // Return the received data to calling function
}

#endif