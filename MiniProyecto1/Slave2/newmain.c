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

void setup(void) {
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0b0000011;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    IOCB = 0b00000011;
    INTCON = 0b11001000;
}

uint8_t cont8bits;
uint8_t flags;
uint8_t flags2;

void __interrupt() isr(void) {
    if (PORTBbits.RB0 == 1 && flags == 0b00000000) {
        flags = 0b00000001;
        cont8bits++;
    } else if (PORTBbits.RB0 == 0 && flags == 0b00000001) {
        flags = 0b00000000;
    }
    if (PORTBbits.RB1 && flags2 == 0b00000000) {
        flags2 = 0b00000001;
        cont8bits--;
    } else if (PORTBbits.RB1 == 0 && flags2 == 0b00000001) {
        flags2 = 0b00000000;
    }
    INTCONbits.RBIF = 0;
}

void main(void) {
    setup();
    while (1) {
        PORTD = cont8bits;
    }
}
