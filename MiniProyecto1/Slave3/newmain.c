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

uint8_t adc;
uint8_t temp;

void setup(void) {
    //Configuracion de los puertos
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    ANSEL = 0b00000001;
    ANSELH = 0;
    TRISA = 0b00101001;
    TRISB = 0;
    TRISD = 0;
    TRISE = 0;
    //Configuracion de la interrupcion de ADC
    ADCON0 = 0b00000001;
    ADCON1 = 0b00010000;
    INTCON = 0b11000000;
    PIE1 = 0b01000000;
}

void __interrupt() isr(void) {
    //Interrupcion por ADC
    if (PIR1bits.ADIF == 1) {
        adc = ADRESH;
        PIR1bits.ADIF = 0;
    }
    //Interrupcion por SPI
    if (PIR1bits.SSPIF == 1) {
        PIR1bits.SSPIF = 0;
        temp = spiRead();
        spiWrite(adc);
    }
}

void main(void) {
    setup();
    //Configuracion de SPI
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    while (1) { //LOOP principal
        //Inicializacion de la lectura ADC
        if (ADCON0bits.GO == 0) {
            __delay_ms(5);
            ADCON0bits.GO = 1;
        }
        //Configuracion del semaforo
        if (adc < 13) { //13 = 25°C
            PORTD = 0b00000100;
        } else if (adc >= 13 && adc < 29) { //29 = 36°C
            PORTD = 0b00000010;
        } else {
            PORTD = 0b00000001;
        }
    }
}
