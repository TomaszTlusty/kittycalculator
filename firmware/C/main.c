#include <avr/io.h>
#include <util/delay.h>
const char keypad_map[4][4] = {
  {'=','3','2','1'},
  {'B','6','5','4'},
  {'C','9','8','7'},
  {'D','#','0','*'}
};

char keypad_scan(void) {
    for (uint8_t row = 0; row < 4; row++) {
        PORTD &= ~(1 << (row + 2));
        _delay_us(5);
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

int main(void) {
    //rows
    DDRD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    PORTD |= (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    //cols
    DDRC &= ~((1 << 0) | (1 << 1) | (1 << 2) | (1 << 3));
    PORTC |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);

   
    DDRB |= (1 << 5);

    while (1) {
        char key = keypad_scan();

        if (key == '5') {
            PORTB |= (1 << 5); 
        } else {
            PORTB &= ~(1 << 5);
        }
    }
}

