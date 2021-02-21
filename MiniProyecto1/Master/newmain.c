#pragma config FOSC     =   XT
#pragma config WDTE     =   OFF
#pragma config PWRTE    =   OFF
#pragma config MCLRE    =   OFF
#pragma config CP       =   OFF
#pragma config CPD      =   OFF
#pragma config BOREN    =   OFF
#pragma config IESO     =   OFF
#pragma config FCMEN    =   OFF
#pragma config LVP      =   OFF
#pragma config BOR4V    =   BOR40V
#pragma config WRT      =   OFF

#define _XTAL_FREQ 8000000

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "LCD.h"

void setup(void) {
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
}

uint8_t S1;
uint8_t S2;
uint8_t S3;
char carac[16];

void __interrupt() isr(void) {
    
}

void main(void) {
    setup();
    Lcd_Init();
    Lcd_Clear();
    while (1) {
        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("POT   BIN   TEMP");
        Lcd_Set_Cursor(2, 1);
        sprintf(carac, "%3i   %3i    %4i", S1, S2, S3);
        Lcd_Write_String(carac);
    }
}
