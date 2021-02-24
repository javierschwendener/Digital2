#pragma config FOSC     =   INTRC_NOCLKOUT
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

#define _XTAL_FREQ 4000000

#include <xc.h>
#include <stdint.h>
#include "spi.h"

void setup(void) {
    //Configuracion de los puertos
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0b00100000;
    TRISB = 0b00000011;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    //Configuracion de la interrupcion del puerto B
    IOCB = 0b00000011;
    PIE1 = 0b00001000;
    INTCON = 0b11001000;
}

uint8_t flags;
uint8_t flags2;
uint8_t temp;

void __interrupt() isr(void) {
    //Interrupcion por puerto B
    if (PORTBbits.RB0 == 1 && flags == 0b00000000) {
        flags = 0b00000001;
        PORTD++;
    } else if (PORTBbits.RB0 == 0 && flags == 0b00000001) {
        flags = 0b00000000;
    }
    if (PORTBbits.RB1 && flags2 == 0b00000000) {
        flags2 = 0b00000001;
        PORTD--;
    } else if (PORTBbits.RB1 == 0 && flags2 == 0b00000001) {
        flags2 = 0b00000000;
    }
    //Limpiar la bandera de interrupcion de puerto B
    INTCONbits.RBIF = 0;
    //Interrupcion por SPI
    if (PIR1bits.SSPIF == 1) {
        PIR1bits.SSPIF = 0;
        temp = spiRead();
        spiWrite(PORTD);
    }
}

void main(void) {
    setup();
    //Configuracion SPI
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while (1) { //LOOP principal
        __delay_ms(1);
    }
}
