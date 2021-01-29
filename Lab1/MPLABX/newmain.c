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

#include <xc.h>

//Se definen variables a usar
int flag;

//Configuracion general del PIC
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
    flag = 0;
    return;
}

//Se define una funcion que encendera distintos leds en secuencia, simulando el semaforo de salida
void semaforo(void) {
    PORTDbits.RD0 = 1;
    __delay_ms(1000);
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 1;
    __delay_ms(1000);
    PORTDbits.RD1 = 0;
    PORTDbits.RD2 = 1;
    __delay_ms(1000);
    PORTD = 0;
    return;
}

//Se define la funcion principal del programa
void main(void) {
    setup();
    //Equivalente a un LOOP
    while (1) {
        if (PORTAbits.RA0 == 1 && flag == 0) {
            semaforo();
            flag = 1;
            PORTB = 0;
            PORTC = 0;
            PORTD = 0;
        }
        while (flag == 1) {
            //Leer los botones de los jugadores (A1 y A2))
            if (PORTAbits.RA1 == 1) {
                if(PORTB != 0){
                    if(PORTBbits.RB7 == 1){
                        PORTB = 0;
                        PORTDbits.RD4 = 1;
                        flag = 0;
                    }
                    PORTB = 2 * PORTB;
                    __delay_ms(500);
                }
                else{
                    PORTB = 1;
                    __delay_ms(500);
                }
            }
            if (PORTAbits.RA2 == 1) {
                if(PORTC != 0){
                    if(PORTCbits.RC7 == 1){
                        PORTC = 0;
                        PORTDbits.RD3 = 1;
                        flag = 0;
                    }
                    PORTC = 2 * PORTC;
                    __delay_ms(500);
                }
                else{
                    PORTC = 1;
                    __delay_ms(500);
                }
            }
        }

    }
}