/*
 * ************************************************
 * Autor: Electrosome
 * Link: https://electrosome.com/lcd-pic-mplab-xc8/
 * Modificado para usos de laboratorio
 * ************************************************
*/

#ifndef LCD_H
#define LCD_H

void Lcd_Port(char a);
void Lcd_Cmd(char a);
void Lcd_Clear();
void Lcd_Set_Cursor(char a, char b);
void Lcd_Init();
void Lcd_Write_Char(char a);
void Lcd_Write_String(char *a);
void Lcd_Shift_Right();
void Lcd_Shift_Left();

#endif