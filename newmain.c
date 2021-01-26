#include <xc.h>

/*
///////////////////////////////////
 * CONFIG
///////////////////////////////////
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

/*
//////////////////////////////////
 * VARIABLES
//////////////////////////////////
 */

int flag;

void setup(void) {
    //Se limpian los puertos, ansel y triestados a utilizar
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0b00000111;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;
    flag = 0b00000000;
    return;
}

void semaforo(void) {
    //Se define una funcion que encendera distintos leds en secuencia, simulando el semaforo de salida
    PORTDbits.RD0 = 1;
    __delay_ms(1000);
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 1;
    __delay_ms(1000);
    PORTDbits.RD1 = 0;
    PORTDbits.RD2 = 1;
    __delay_ms(1000);
    PORTDbits.RD0 = 0;
}

void main(void) {
    setup();
    while (1) { //Equivalente a un loop
        while (PORTAbits.RA0 == 1 && flag == 0b00000000) {
            semaforo();
            flag = 0b00000001;
        }
        while (flag == 0b00000001) {
            //Leer los botones de los jugadores (A1 y A2)
            while (PORTAbits.RA1 == 1) {
                if (PORTB == 0){
                    PORTB = 1;
                }
                else {
                    PORTB = PORTB + PORTB;
                }
            }
            while (PORTAbits.RA2 == 2) {
                if (PORTC == 0){
                    PORTC = 1;
                }
                else {
                    PORTC = PORTC + PORTC;
                }
            }
        }
    }
}