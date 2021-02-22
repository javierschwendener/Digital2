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

uint8_t adc;

void setup(void) {
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    ANSEL = 0b00000001;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    ADCON0 = 0b00000001;
    INTCON = 0b11000000;
    PIE1 = 0b01000000;
}

void __interrupt() isr(void) {
    if (PIR1bits.ADIF == 1) {
        adc = ADRESH;
        PIR1bits.ADIF = 0;
    }
}

void main(void) {
    setup();
    while (1) {
        if (ADCON0bits.GO == 0) {
            __delay_ms(5);
            ADCON0bits.GO = 1;
        }
    }
}
