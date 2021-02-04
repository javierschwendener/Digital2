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

//Configuracion general del PIC

void setup(void) {
    //Se limpian los puertos, ansel y triestados a utilizar
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    //AN8 como bit de entrada analogica
    ANSEL = 0b00000001;
    ANSELH = 0;
    //Se deja B0 y B1 como entradas para los push buttons
    TRISA = 0;
    TRISB = 0b00000011;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    return;
}

//Se definen las variables que se usaran en el programa

uint8_t variable;
uint8_t multi;
uint8_t adece;
uint8_t nib;

//Se define la funcion de interrupciones a usar

void __interrupt() isr(void) {
    //Placeholder de la interrupcion (aiuda)
}

//Definir una funcion para tomar un dato y colocarlo en los 7-segmentos
void tabla(uint8_t nib) {
    switch (nib) {
        case 0: //Dibujar el 0 
            variable = 0b00111111;
            break;
        case 1: //Dibujar el 1
            variable = 0b00000110;
            break;
        case 2: //Dibujar el 2
            variable = 0b01011011;
            break;
        case 3: //Dibujar el 3
            variable = 0b01001111;
            break;
        case 4: //Dibujar el 4
            variable = 0b01100110;
            break;
        case 5: //Dibujar el 5
            variable = 0b01101101;
            break;
        case 6: //Dibujar el 6
            variable = 0b01111101;
            break;
        case 7: //Dibujar el 7
            variable = 0b00000111;
            break;
        case 8: //Dibujar el 8
            variable = 0b01111111;
            break;
        case 9: //Dibujar el 9
            variable = 0b01100111;
            break;
        case 10: //Dibujar la A
            variable = 0b01110111;
            break;
        case 11: //Dibujar la B
            variable = 0b01111111;
            break;
        case 12: //Dibujar la C
            variable = 0b00111001;
            break;
        case 13: //Dibujar la D
            variable = 0b00111111;
            break;
        case 14: //Dibujar la E
            variable = 0b01111001;
            break;
        case 15: //Dibujar la F
            variable = 0b01110001;
            break;
    }
}

void main(void) {
    setup();
    //LOOP principal
    while (1) {
        //Se verifican los botones
        //Boton de suma
        if (PORTBbits.RB0 == 1) {
            //Realizar el incremento para el puerto requerido
            if (PORTC == 255) {
                PORTC = 0;
                __delay_ms(250);
            } else {
                PORTC = PORTC + 1;
                __delay_ms(250);
            }
        }
        //Boton de resta
        if (PORTBbits.RB1) {
            //Realizar el decremento para el puerto requerido
            if (PORTC == 0) {
                PORTC = 255;
                __delay_ms(250);
            } else {
                PORTC = PORTC - 1;
                __delay_ms(250);
            }
        }
        //Se realiza el multiplexado
        if (multi == 0b00000000) {
            //Apagar el segundo display y encender el primero
            PORTEbits.RE1 = 0;
            nib = PORTC & 0b00001111;
            tabla(nib);
            PORTD = variable;
            /*nib = adece & 0b00001111;
            tabla(nib);
            PORTD = nib;*/
            PORTEbits.RE0 = 1;
            multi = 0b00000001;
        } else {
            //Apagar el primer display y encender el segundo
            PORTEbits.RE0 = 0;
            nib = PORTC & 0b11110000;
            nib = nib >> 4;
            tabla(nib);
            PORTD = variable;
            /*nib = adece & 0b11110000;
            nib = nib >> 4;
            tabla(nib);
            PORTD = nib;*/
            PORTEbits.RE1 = 1;
            multi = 0b00000000;
        }
        //Iniciar conversion ADC
        __delay_ms(5);
        ADCON0bits.GO = 1;
        __delay_ms(5);
        adece = ADRESH;
    }
}
