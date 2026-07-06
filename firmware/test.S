#include <avr/io.h>
.section .text
.global main
main:
	sbi _SFR_IO_ADDR(DDRB),5
loop:
	sbi _SFR_IO_ADDR(PORTB),5
	rcall delay
	cbi _SFR_IO_ADDR(PORTB),5
	rcall delay
	rjmp loop
delay:
    ldi r18, 20        ; licznik zewnętrzny = 20
d1: ldi r19, 255       ; licznik środkowy = 255
d2: ldi r20, 255       ; licznik wewnętrzny = 255
d3: dec r20            ; r20 = r20 - 1
    brne d3            ; jeśli r20 != 0, wróć do d3
    dec r19            ; r19 = r19 - 1
    brne d2            ; jeśli r19 != 0, wróć do d2 (i znów ustaw r20=255)
    dec r18            ; r18 = r18 - 1
    brne d1            ; jeśli r18 != 0, wróć do d1
    ret                ; wróć tam, skąd wywołano rcall
