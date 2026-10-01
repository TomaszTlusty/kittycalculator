#include "lcd_i2c.h"
#include "i2c.h"
#include <util/delay.h>

#define LCD_ADDR (0x27 << 1) 
#define LCD_RS 0x01  
#define LCD_RW 0x02  
#define LCD_EN 0x04  
#define LCD_BL 0x08  

static void pcf8574_write(uint8_t data) {
    i2c_start();
    i2c_write(LCD_ADDR); 
    i2c_write(data);     
    i2c_stop();          
}

static void lcd_send_nibble(uint8_t nibble, uint8_t rs_flag) {
    uint8_t data = (nibble & 0xF0) | LCD_BL | rs_flag;
    pcf8574_write(data);
    pcf8574_write(data | LCD_EN);
    _delay_us(1);
    pcf8574_write(data & ~LCD_EN);
    _delay_us(50); 
}

static void lcd_send_byte(uint8_t data, uint8_t rs_flag) {
    lcd_send_nibble(data & 0xF0, rs_flag);
    lcd_send_nibble((data << 4) & 0xF0, rs_flag);
}

void lcd_cmd(uint8_t cmd) {
    lcd_send_byte(cmd, 0);
}

void lcd_char(uint8_t data) {
    lcd_send_byte(data, LCD_RS);
}

void lcd_print(const char* str) {
    while (*str) {
        lcd_char(*str++);
    }
}

void lcd_set_cursor(uint8_t col, uint8_t row) {
    uint8_t row_offsets[] = {0x00, 0x40};
    lcd_cmd(0x80 | (col + row_offsets[row]));
}

void lcd_init(void) {
    _delay_ms(50); 
    lcd_send_nibble(0x30, 0);
    _delay_ms(5);
    lcd_send_nibble(0x30, 0);
    _delay_us(150);
    lcd_send_nibble(0x30, 0);
    lcd_send_nibble(0x20, 0);
    lcd_cmd(0x28); 
    lcd_cmd(0x0C); 
    lcd_cmd(0x01);
    _delay_ms(2);  
    lcd_cmd(0x06);
}

void lcd_clear(void) {
    lcd_cmd(0x01); 
    _delay_ms(2);  
}