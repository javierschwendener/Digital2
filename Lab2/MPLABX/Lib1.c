/*
 * File:   Lib1.c
 * Author: USUARIO
 *
 * Created on February 4, 2021, 10:18 AM
 */


#include <xc.h>
#include "Lib1.h"

uint8_t value;
uint8_t adc_value;

uint8_t table(uint8_t index) {
    switch (index) {
        case 0: //Dibujar el 0 
            value = 0b00111111;
            break;
        case 1: //Dibujar el 1
            value = 0b00000110;
            break;
        case 2: //Dibujar el 2
            value = 0b01011011;
            break;
        case 3: //Dibujar el 3
            value = 0b01001111;
            break;
        case 4: //Dibujar el 4
            value = 0b01100110;
            break;
        case 5: //Dibujar el 5
            value = 0b01101101;
            break;
        case 6: //Dibujar el 6
            value = 0b01111101;
            break;
        case 7: //Dibujar el 7
            value = 0b00000111;
            break;
        case 8: //Dibujar el 8
            value = 0b01111111;
            break;
        case 9: //Dibujar el 9
            value = 0b01100111;
            break;
        case 10: //Dibujar la A
            value = 0b01110111;
            break;
        case 11: //Dibujar la B
            value = 0b01111111;
            break;
        case 12: //Dibujar la C
            value = 0b00111001;
            break;
        case 13: //Dibujar la D
            value = 0b00111111;
            break;
        case 14: //Dibujar la E
            value = 0b01111001;
            break;
        case 15: //Dibujar la F
            value = 0b01110001;
            break;
    }
}

uint8_t adc(void) {
    if (PIR1bits.ADIF == 1) {
        adc_value = ADRESH;
        PIR1bits.ADIF = 0;
    }
}