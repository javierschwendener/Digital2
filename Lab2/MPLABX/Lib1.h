/* 
 * File: Lib1
 * Author: Javier Schwendener
 * Comments: ADC
 * Revision history: v1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LIB1_H
#define	LIB1_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

uint8_t table(uint8_t index);
uint8_t adc(void);

#endif