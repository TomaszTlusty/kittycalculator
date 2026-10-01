// #define F_CPU 16000000UL

#include <avr/io.h>
#include "i2c.h"
#include "lcd_i2c.h"
#include "keypad.h"
#include "calculator.h"
#include <util/delay.h>

int main(void) {
    i2c_init();    
    lcd_init();    
    keypad_init();
    lcd_set_cursor(0, 0);          
    
    while (1) {
        calc_process_key(keypad_scan());
        _delay_us(50); 
    }
    return 0;
}