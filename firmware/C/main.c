#include <avr/io.h>
#include <util/delay.h>
#include "i2c.h"
#include "lcd_i2c.h"
#include "keypad.h"

int main(void) {
    i2c_init();    
    lcd_init();    
    keypad_init();
    lcd_set_cursor(0, 0);          
    lcd_print("Czyste C99!");
    lcd_set_cursor(0, 1);           
    lcd_print("C99 > .ino");    
    DDRB |= (1 << 5);

    while (1) {
        char key = keypad_scan();
        if (key == '5') {
            PORTB |= (1 << 5);
        } else {
            PORTB &= ~(1 << 5); 
        }
    }

    return 0;
}
