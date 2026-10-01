#include "calculator.h"
#include "lcd_i2c.h"
#include <stdlib.h>
#include <util/delay.h>


static int num1 = 0;
static int num2 = 0;
static char infix_operator = 0;
static char last_key = 0; 

void calc_process_key(char key) {
    if (key != 0 && key != last_key) {
        
        if (key >= '0' && key <= '9') {
            num2 = (num2 * 10) + (key - '0');
            lcd_char(key);
        } 
        else {
            switch (key) {
                case '+': 
                case '-': 
                case '*': 
                case '%': 
                    num1 = num2;         
                    num2 = 0;            
                    infix_operator = key;       
                    break;
                    
                case '=':
                    if (infix_operator == '+') num2 = num1 + num2;
                    else if (infix_operator == '-') num2 = num1 - num2;
                    else if (infix_operator == '*') num2 = num1 * num2;
                    else if (infix_operator == '%') { 
                        if (num2 != 0) {
                            num2 = num1 / num2;
                        } else {
                            lcd_clear();
                            lcd_print("Div by 0");
                            _delay_ms(2000);
                            lcd_clear();
                            num1 = 0; 
                            num2 = 0; 
                            infix_operator = 0;
                            break; 
                        }
                    }
                    lcd_clear();
                    char buffer[16];
                    itoa(num2, buffer, 10); 
                    lcd_print(buffer);
                    
                    num1 = 0;
                    infix_operator = 0;
                    break;
                    
                case '.': 
                    num1 = 0;
                    num2 = 0;
                    infix_operator = 0;
                    lcd_clear();
                    break;
            }
        }
    }
    last_key = key; 
}