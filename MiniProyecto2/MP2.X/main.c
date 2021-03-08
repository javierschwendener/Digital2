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
#include "i2c.h"

void setup(void) {
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0b00011000;
    TRISD = 0;
    TRISE = 0;
    ANSEL = 0;
    ANSELH = 0;
    SPBRGH = 0;
    SPBRG = 25;
    BAUDCTL = 0;
    TXSTA = 0b00100100;
    RCSTA = 0b10000000;
}

//Se crean las variables a utilizar en el programa

void main(void) {
    setup();
    I2C_Master_Init(100000);
    while (1) {
        I2C_Master_Start();
        I2C_Master_Write(0x29);
        I2C_Master_Wait();
        if (ACKSTAT == 0){
            PORTB = I2C_Master_Read(0);
            I2C_Master_Stop();
        }
        else{
            I2C_Master_Stop();
        }
        __delay_ms(200);
    }
}
