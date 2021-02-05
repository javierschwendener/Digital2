/*
 * *************************
 CONFIGURACION
 * *************************
 */

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
#include "Lib1.h"

//Configuracion general del PIC

void setup(void) {
    //Se limpian los puertos, ansel y triestados a utilizar
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    //AN8 como bit de entrada analogica
    ANSEL = 0;
    ANSELH = 0b00000001;
    //Se deja B0 y B1 como entradas para los push buttons
    TRISA = 0;
    TRISB = 0b00000111;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    //Se habilita el ADC
    IOCB = 0b00000011;
    ADCON0 = 0b01100001;
    INTCON = 0b11001000;
    PIE1 = 0b01000000;
    T2CON = 0b00000100;
}

//Se definen las variables que se usaran en el programa

uint8_t variable;
uint8_t multi;
uint8_t flags;
uint8_t flags2;
uint8_t adece;
uint8_t nib;

//Se define la funcion de interrupciones a usar

void __interrupt() isr(void) {
    //Se lee el valor del ADC
    adece = adc();
    //Se verifica la interrupcion del Timer2
    if (PIR1bits.TMR2IF == 1) {
        PIR1bits.TMR2IF = 0;
        if (multi == 0b00000000) {
            //Apagar el segundo display y encender el primero
            multi = 0b00000001;
            PORTEbits.RE1 = 0;
            PORTEbits.RE0 = 1;
        } else {
            //Apagar el primer display y encender el segundo
            multi = 0b00000000;
            PORTEbits.RE0 = 0;
            PORTEbits.RE1 = 1;
        }
    }
    //Se verifica el boton presionado
    //Boton de suma
    if (PORTBbits.RB0 == 1 && flags == 0b00000000) {
        //Realizar el incremento para el puerto requerido
        flags = 0b00000001;
        PORTC++;
    } else if (PORTBbits.RB0 == 0 && flags == 0b00000001) {
        flags = 0b00000000;
    }
    //Boton de resta
    if (PORTBbits.RB1 && flags2 == 0b00000000) {
        //Realizar el decremento para el puerto requerido
        flags2 = 0b00000001;
        PORTC--;
    } else if (PORTBbits.RB1 == 0 && flags2 == 0b00000001) {
        flags2 = 0b00000000;
    }
    INTCONbits.RBIF = 0;
}

void main(void) {
    setup();
    //LOOP principal
    while (1) {
        //Se verifica si el contador del ADC supera al contador binario
        if (adece > PORTC) {
            PORTEbits.RE2 = 1;
        } else {
            PORTEbits.RE2 = 0;
        }
        //Se hacen las modificaciones a los displays activos
        if (multi == 0b00000000) {
            nib = adece & 0b00001111;
            table(nib);
            PORTD = nib;
            PORTD = table(nib);
        } else {
            nib = adece & 0b11110000;
            nib = nib >> 4;
            table(nib);
            PORTD = nib;
            PORTD = table(nib);
        }
        //Iniciar conversion ADC
        if (ADCON0bits.GO == 0) {
            __delay_ms(5);
            ADCON0bits.GO = 1;
        }
    }
}
