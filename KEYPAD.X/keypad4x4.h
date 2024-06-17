#ifndef KEY_PAD_4x4_H
#define KEY_PAD_4x4_H

int row, col;
char keypad[4][4] = {
    {'7', '8', '9', '/'},
    {'4', '5', '6', 'x'},
    {'1', '2', '3', '-'},
    {'*', '0', '=', '+'}
};

void keypad_scan() {
    int i = 0;
    while (1) {
        PORTD = 0x01 << i;
        col = 4-i;
        if (PORTDbits.RD4 == 1) {
            row = 4;
            break;
        }
        if (PORTDbits.RD5 == 1) {
            row = 3;
            break;
        }
        if (PORTDbits.RD6 == 1) {
            row = 2;
            break;
        }
        if (PORTDbits.RD7 == 1) {
            row = 1;
            break;
        }
        i++;
        if(i==4)
            i=0;
    }
    
}

#endif