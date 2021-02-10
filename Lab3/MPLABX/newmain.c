/*
 * *********************************
 * CONFIGUIRACION
 * *********************************
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
#include <stdio.h>
#include "Lib1.h"
#include "lcd.h"

void setup(void) { //Se limpian los puertos, ansel y triestados a utilizar
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    PORTC = 0;
    ANSEL = 0b00000011; //RA0 y RA1 de lectura analogica
    ANSELH = 0;
    TRISA = 0b00000011; //RA0 y RA1 como entradas
    TRISB = 0;
    TRISD = 0;
    TRISC = 0;
    ADCON0 = 0b00000001; //Se habilita el ADC para el RA0
    ADCON1 = 0x00;
    INTCON = 0b11000000; //Interrupciones globales
    PIE1 = 0b01100000; //Permitir interrupcion del ADC
    SPBRGH = 0;
    SPBRG = 25;
    BAUDCTL = 0b00000000; //Se configura el baudrate
    TXSTA = 0b00100100;
    RCSTA = 0b10010000;
}

/*
 * *********************************
 * VARIABLES
 * *********************************
 */

uint8_t adece1;
uint8_t adece2;
uint8_t res1;
uint8_t res2;
uint8_t res3;
uint8_t res4;
uint8_t multi;
uint8_t coms;
uint8_t dato = 0;
uint8_t vasc;
char carac[16];

//Vector de interrupciones

void __interrupt() isr(void) {
    //Se lee el valor del ADC
    if (multi == 0) {
        adece1 = adc();
        multi = 1;
        res1 = 0;
        res2 = 0;
        ADCON0 = 0b00000101; //Se habilita el pin RA1 como entrada de ADC
    } else {
        adece2 = adc();
        multi = 0;
        res3 = 0;
        res4 = 0;
        ADCON0 = 0b00000001; //Se habilita el pin RA0 como entrada de ADC
    }
    if (PIR1bits.RCIF == 1) {
        coms = RCREG;
        PIR1bits.RCIF = 0;
        if (coms == 0x2B) {
            dato++;
        } else if (coms == 0x2D) {
            dato--;
        }
    }
}

//Se definan las variables a usar en el programa

void main(void) {
    setup();
    Lcd_Init();
    Lcd_Clear();
    while (1) { //LOOP principal
        //Se inicia la lectura del ADC
        if (ADCON0bits.GO == 0) {
            __delay_ms(5);
            ADCON0bits.GO = 1;
            __delay_ms(5);
        }
        Lcd_Set_Cursor(1, 1);
        //Linea de titulos
        Lcd_Write_String(" S1    S2    S3 ");
        //Linea de resultados
        Lcd_Set_Cursor(2, 1);
        //Se realiza el mapeo de valores para poder mostrar el voltaje
        //equivalente para ambos valores de ADC
        //Se envian datos por el TX
        while (adece1 >= 50) {
            adece1 = adece1 - 50;
            res1++;
        }
        while (adece1 >= 5) {
            adece1 = adece1 - 5;
            res2++;
        }
        while (adece2 >= 50) {
            adece2 = adece2 - 50;
            res3++;
        }
        while (adece2 >= 5) {
            adece2 = adece2 - 5;
            res4++;
        }
        //Se reciben datos en el RC
        if (TXSTAbits.TRMT == 1) {
            vasc = ascii(res1);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x2E;
            __delay_ms(5);
            vasc = ascii(res2);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x20;
            __delay_ms(5);
            vasc = ascii(res3);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x2E;
            __delay_ms(5);
            vasc = ascii(res4);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x0D;
            __delay_ms(5);
        }
        //Se realiza una traduccion para mostrar los resultados en la LCD
        sprintf(carac, "%1i.%1iV  %1i.%1iV   %3i", res1, res2, res3, res4, dato);
        //Se envia el dato a la LCD
        Lcd_Write_String(carac);
    }
}
