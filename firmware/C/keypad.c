#include "keypad.h"
#include <avr/io.h>
#include <util/delay.h>

const char keypad_map[4][4] = {
  {'%','3','2','1'},
  {'*','6','5','4'},
  {'-','9','8','7'},
  {'+','.','=','0'}
};

void keypad_init(void) {
    DDRD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    PORTD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    DDRC &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
    PORTC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
}

char keypad_scan(void) {
    for (uint8_t row = 0; row < 4; row++) {
        PORTD &= ~(1 << (row + 2));
        _delay_ms(20);
        for (uint8_t col = 0; col < 4; col++) {
            if (!(PINC & (1 << col))) {
                PORTD |= (1 << (row + 2));
                return keypad_map[row][col];
            }
        }
        PORTD |= (1 << (row + 2));
    }
    return '\0'; 
}