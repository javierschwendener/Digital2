/*
 * ************************************************
 * Autor: Electrosome
 * Link: https://electrosome.com
 * Modificado para usos de laboratorio
 * ************************************************
 */

#ifndef I2C_H
#define I2C_H

char UART_Init(const long int baudrate);
char UART_TX_Empty();
void UART_Write(char data);
void UART_Write_Text(char *text);
void I2C_Master_Init(const unsigned long c);
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_RepeatedStart();
void I2C_Master_Stop();
void I2C_Master_Write(unsigned d);
unsigned short I2C_Master_Read(unsigned short a);

#endif