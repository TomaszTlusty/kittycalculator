#include <avr/io.h>
.section .text
.global main
main:
  ; ---- diode ----
  sbi _SFR_IO_ADDR(DDRB),5        

  ; ----rows R1-R4 = PD2..PD5 jako wyjścia ----
  sbi _SFR_IO_ADDR(DDRD),2
  sbi _SFR_IO_ADDR(DDRD),3
  sbi _SFR_IO_ADDR(DDRD),4
  sbi _SFR_IO_ADDR(DDRD),5

  ; ---- rows WYSOKIE (nieaktywne) ----
  sbi _SFR_IO_ADDR(PORTD),2
  sbi _SFR_IO_ADDR(PORTD),3
  sbi _SFR_IO_ADDR(PORTD),4
  sbi _SFR_IO_ADDR(PORTD),5

  ; ---- cools C1-C4 = PC0..PC3, pull-ups ----
  sbi _SFR_IO_ADDR(PORTC),0
  sbi _SFR_IO_ADDR(PORTC),1
  sbi _SFR_IO_ADDR(PORTC),2
  sbi _SFR_IO_ADDR(PORTC),3

loop:
  ; ===== ROW 1 (R1 = PD2) =====
  cbi _SFR_IO_ADDR(PORTD),2
  rcall settle
  sbis _SFR_IO_ADDR(PINC),0
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),1
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),2
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),3
  rjmp zapal
  sbi _SFR_IO_ADDR(PORTD),2

  ; ===== ROW 2 (R2 = PD3) =====
  cbi _SFR_IO_ADDR(PORTD),3
  rcall settle
  sbis _SFR_IO_ADDR(PINC),0
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),1
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),2
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),3
  rjmp zapal
  sbi _SFR_IO_ADDR(PORTD),3

  ; ===== ROW 3 (R3 = PD4) =====
  cbi _SFR_IO_ADDR(PORTD),4
  rcall settle
  sbis _SFR_IO_ADDR(PINC),0
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),1
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),2
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),3
  rjmp zapal
  sbi _SFR_IO_ADDR(PORTD),4

  ; ===== ROW 4 (R4 = PD5)=====  
  cbi _SFR_IO_ADDR(PORTD),5
  rcall settle
  sbis _SFR_IO_ADDR(PINC),0
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),1
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),2
  rjmp zapal
  sbis _SFR_IO_ADDR(PINC),3
  rjmp zapal
  sbi _SFR_IO_ADDR(PORTD),5

  ; ===== nothing clicked =====
  cbi _SFR_IO_ADDR(PORTB),5        
  rjmp loop

zapal:
  sbi _SFR_IO_ADDR(PORTB),5        
  sbi _SFR_IO_ADDR(PORTD),2
  sbi _SFR_IO_ADDR(PORTD),3
  sbi _SFR_IO_ADDR(PORTD),4
  sbi _SFR_IO_ADDR(PORTD),5
  rjmp loop

settle:
  ldi r18,20
s1:
  dec r18
  brne s1
  ret
  
;not making LCD display in asm ngl too hard
