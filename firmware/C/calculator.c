#include "calculator.h"
#include "lcd_i2c.h"
#include <stdlib.h>
#include <util/delay.h>

static long long num1 = 0;
static long long num2 = 0;
static char infix_operator = 0;
static char last_key = 0; 
static char flag = 0;

static void custom_lltoa(long long num, char* buffer) {
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    uint8_t is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    char temp_buf[32];
    uint8_t i = 0;
    while (num > 0) {
        temp_buf[i] = (num % 10) + '0'; 
        num = num / 10;
        i++;
    }
    if (is_negative) {
        temp_buf[i] = '-';
        i++;
    }
    uint8_t j = 0;
    while (i > 0) {
        i--;
        buffer[j] = temp_buf[i];
        j++;
    }
    buffer[j] = '\0';
}

void calc_process_key(char key) {
    if (key != 0 && key != last_key) {
        
        if (key >= '0' && key <= '9') {
            if (flag) {
                lcd_clear();
                num2 = 0; 
                flag = 0;
            }
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
                    infix_operator = key;
                    flag = 1;       
                    lcd_clear();
                    lcd_char(key);
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
                    char buffer[32];
                    custom_lltoa(num2, buffer); 
                    lcd_print(buffer);
                    num1 = 0;
                    infix_operator = 0;
                    flag = 1; 
                    break;
                case '.': 
                    num1 = 0;
                    num2 = 0;
                    infix_operator = 0;
                    flag = 0;
                    lcd_clear();
                    break;
            }
        }
    }
    last_key = key; 
}