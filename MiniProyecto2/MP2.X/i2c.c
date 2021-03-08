/*
 * ************************************************
 * Autor: Electrosome
 * Link: https://electrosome.com
 * Modificado para usos de laboratorio
 * ************************************************
 */

#include <xc.h>

#define _XTAL_FREQ 4000000

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

char UART_Init(const long int baudrate) {
    unsigned int x;
    x = (_XTAL_FREQ - baudrate * 64) / (baudrate * 64); //SPBRG for Low Baud Rate
    if (x > 255) //If High Baud Rage Required
    {
        x = (_XTAL_FREQ - baudrate * 16) / (baudrate * 16); //SPBRG for High Baud Rate
        BRGH = 1; //Setting High Baud Rate
    }
    if (x < 256) {
        SPBRG = x; //Writing SPBRG Register
        SYNC = 0; //Setting Asynchronous Mode, ie UART
        SPEN = 1; //Enables Serial Port
        TRISC7 = 1; //As Prescribed in Datasheet
        TRISC6 = 1; //As Prescribed in Datasheet
        CREN = 1; //Enables Continuous Reception
        TXEN = 1; //Enables Transmission
        return 1; //Returns 1 to indicate Successful Completion
    }
    return 0; //Returns 0 to indicate UART initialization failed
}

char UART_TX_Empty() {
    return TRMT;
}

void UART_Write(char data) {
    while (!TRMT);
    TXREG = data;
}

void UART_Write_Text(char *text) {
    int i;
    for (i = 0; text[i] != '\0'; i++)
        UART_Write(text[i]);
}

void I2C_Master_Init(const unsigned long c) {
    SSPCON = 0b00101000;
    SSPCON2 = 0;
    SSPADD = (_XTAL_FREQ / (4 * c)) - 1;
    SSPSTAT = 0;
    TRISC3 = 1;
    TRISC4 = 1;
}

void I2C_Master_Wait() {
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start() {
    I2C_Master_Wait();
    SEN = 1;
}

void I2C_Master_RepeatedStart() {
    I2C_Master_Wait();
    RSEN = 1;
}

void I2C_Master_Stop() {
    I2C_Master_Wait();
    PEN = 1;
}

void I2C_Master_Write(unsigned d) {
    I2C_Master_Wait();
    SSPBUF = d;
}

unsigned short I2C_Master_Read(unsigned short a) {
    unsigned short temp;
    I2C_Master_Wait();
    RCEN = 1;
    I2C_Master_Wait();
    temp = SSPBUF;
    I2C_Master_Wait();
    ACKDT = (a) ? 1 : 0;
    ACKEN = 1;
    return temp;
}