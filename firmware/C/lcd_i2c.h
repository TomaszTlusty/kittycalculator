#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdint.h>

void lcd_init(void);
void lcd_cmd(uint8_t cmd);
void lcd_char(uint8_t data);
void lcd_print(const char* str);
void lcd_set_cursor(uint8_t col, uint8_t row);

#endif 