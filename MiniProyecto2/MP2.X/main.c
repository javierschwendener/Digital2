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
    INTCON = 0b11000000;
    PIE1 = 0b00100000;
    SPBRGH = 0;
    SPBRG = 25;
    BAUDCTL = 0;
    TXSTA = 0b00100100;
    RCSTA = 0b10010000;
}

//Se crean las variables a utilizar en el programa
uint8_t uread;
uint8_t iread;

void __interrupt() isr(void) {
    if (PIR1bits.RCIF == 1) {
        uread = RCREG;
        PIR1bits.RCIF = 0;
    }
}

void main(void) {
    setup();
    I2C_Master_Init(100000);
    while (1) {
        
        I2C_Master_Start();
        I2C_Master_Write(0x29);
        I2C_Master_Wait();
        if (ACKSTAT == 0){
            iread = I2C_Master_Read(0);
            I2C_Master_Stop();
        }
        else{
            I2C_Master_Stop();
        }
        __delay_ms(200);
        
        switch (uread){
            case 0:
                //Ninguna LED Piloto
                PORTB = 0;
                break;
            case 1:
                //Primera LED Piloto encendida
                PORTB = 1;
                break;
            case 2:
                //Segunda LED Piloto encendida
                PORTB = 2;
                break;
            case 3:
                //Ambas LEDs Piloto encendidas
                PORTB = 3;
                break;
            default:
                //Ninguna LED Piloto encendida
                PORTB = 0;
                break;
        }
        
        if (TXSTAbits.TRMT == 1){
            TXREG = 44;
            __delay_ms(5);
        }
    }
}
