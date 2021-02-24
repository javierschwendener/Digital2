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
#include <stdio.h>
#include <pic16f887.h>
#include "LCD.h"
#include "Lib1.h"
#include "spi.h"

void setup(void) {
    //Configuracion de los puertos
    PORTA = 0;
    PORTB = 0b00000111;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0;
    TRISCbits.TRISC0 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC6 = 0;
    TRISD = 0;
    TRISE = 0;
    //Configuracion de la comunicacion EUSART
    INTCON = 0b11000000;
    SPBRGH = 0;
    SPBRG = 25;
    BAUDCTL = 0;
    TXSTA = 0b00100100;
    RCSTA = 0b10000000;
    PORTC = 0;
    PORTD = 0;
}

//Creacion de variables utiles
uint8_t S1;
uint8_t S2;
uint8_t S3;
uint8_t vasc;
uint8_t res1;
uint8_t res2;
uint8_t res3;
uint8_t res4;
uint8_t bin1;
uint8_t bin2;
uint8_t bin3;
uint8_t bin4;
uint8_t bin5;
uint8_t bin6;
char carac[16];

//Vector de interrupcion
void __interrupt() isr(void) {
    //Limpiar la bandera de la comunicacion SPI
    PIR1bits.SSPIF = 0;
}

void main(void) {
    setup();
    //Configuracion SPI
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    //Inicializacion de la LCD
    Lcd_Init();
    Lcd_Clear();
    while (1) { //LOOP principal
        //Intercambiar valores en SPI
        PORTBbits.RB0 = 0;
        spiWrite(0);
        S1 = spiRead();
        PORTBbits.RB0 = 1;
        PORTBbits.RB1 = 0;
        spiWrite(0);
        S2 = spiRead();
        PORTBbits.RB1 = 1;
        PORTBbits.RB2 = 0;
        spiWrite(0);
        S3 = spiRead();
        PORTBbits.RB2 = 1;

        //Mapeo de ADC

        while (S1 >= 50) {
            S1 = S1 - 50;
            res1++;
        }
        while (S1 >= 5) {
            S1 = S1 - 5;
            res2++;
        }

        //Escribir a la LCD

        Lcd_Set_Cursor(1, 1);
        Lcd_Write_String("POT   BIN   TEMP");
        Lcd_Set_Cursor(2, 1);
        sprintf(carac, "%1i.%1iV  %3i %3i.0C", res1, res2, S2, S3);
        Lcd_Write_String(carac);

        //Mapeo del contador binario

        while (S2 >= 100) {
            S2 = S2 - 100;
            bin1++;
        }
        while (S2 >= 10) {
            S2 = S2 - 10;
            bin2++;
        }
        while (S2 >= 1) {
            S2 = S2 - 1;
            bin3++;
        }
        
        //Mapeo de la temperatura

        while (S3 >= 100) {
            S3 = S3 - 100;
            bin4++;
        }
        while (S3 >= 10) {
            S3 = S3 - 10;
            bin5++;
        }
        while (S3 >= 1) {
            S3 = S3 - 1;
            bin6++;
        }
        
        //Escribir a la terminal

        if (TXSTAbits.TRMT == 1) {
            vasc = ascii(res1);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x2E;
            __delay_ms(5);
            vasc = ascii(res2);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x56;
            __delay_ms(5);
            TXREG = 0x20;
            __delay_ms(5);
            TXREG = 0x20;
            __delay_ms(5);
            vasc = ascii(bin1);
            TXREG = vasc;
            __delay_ms(5);
            vasc = ascii(bin2);
            TXREG = vasc;
            __delay_ms(5);
            vasc = ascii(bin3);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x20;
            __delay_ms(5);
            TXREG = 0x20;
            __delay_ms(5);
            vasc  = ascii(bin4);
            TXREG = vasc;
            __delay_ms(5);
            vasc  = ascii(bin5);
            TXREG = vasc;
            __delay_ms(5);
            vasc  = ascii(bin6);
            TXREG = vasc;
            __delay_ms(5);
            TXREG = 0x0D;
            __delay_ms(5);
        }
        
        //Limpiar variables usadas
        res1 = 0;
        res2 = 0;
        res3 = 0;
        bin1 = 0;
        bin2 = 0;
        bin3 = 0;
        bin4 = 0;
        bin5 = 0;
        bin6 = 0;

    }
}