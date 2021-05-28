// Inclusion de librerias a usar
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
// Declaracion de las variables
bool S1 = false;
bool S2 = false;
bool S3 = false;
bool S4 = false;
int32_t B1;
int32_t B2;
int32_t B3;
int32_t B4;
int P1;
int P2;
int P3;
int P4;
uint32_t parking;
int main(void){
    // Configuracion principal
    SysCtlClockSet(SYSCTL_SYSDIV_6|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    // Se preparan los puertos A y B
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    // Se declaran los pines del puerto B como salidas
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    // Se declaran los pines del puerto A como entradas
    GPIOPinTypeGPIOInput(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
    GPIOPadConfigSet(GPIO_PORTA_BASE, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);
    // Se habilitan las interrupciones
    IntMasterEnable();
    // Se habilida el modulo UART1
    IntEnable(INT_UART1);
    // Se configura el modulo UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    // Se establecen los pines 4 y 5 del puerto C como los pines UART
    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);
    GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1));
    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));
    UARTFIFOEnable(UART1_BASE);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX7_8, UART_FIFO_RX1_8);
    // Loop principal
    while(1){
        // Se leen cada uno de los pines establecidos del puerto A
        B1 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
        // Se verifica que el boton este presionado
        if((B1 & 0x04)==4){
            // Se cambia de estado a la variable de estado
            S1 = !S1;
            // Se impide el seguimiento del programa hasta que se deje de presionar el boton
            while((B1 & 0x04)==4){
                // Se mantiene la lectura del pin hasta que se rompa la condicion
                B1 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_2);
            }
        }
        B2 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3);
        if((B2 & 0x08)==8){
            S2 = !S2;
            while((B2 & 0x08)==8){
                B2 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_3);
            }
        }
        B3 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
        if((B3 & 0x10)==16){
            S3 = !S3;
            while((B3 & 0x10)==16){
                B3 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_4);
            }
        }
        B4 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
        if((B4 & 0x20)==32){
            S4 = !S4;
            while((B4 & 0x20)==32){
                B4 = GPIOPinRead(GPIO_PORTA_BASE, GPIO_PIN_5);
            }
        }
        // Segun las variables de estado se configuran las LEDs
        if(S1 == true){
            // Se enciende la LED roja de cada parqueo
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1, 0x01); //0000 0001
            // Se establece un valor binario correspondiente a este parqueo
            P1 = 0b00000001;
        }
        else{
            // Se enciende la LED verde de cada parqueo
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0|GPIO_PIN_1, 0x02); //0000 0000
            P1 = 0b00000000;
        }
        if(S2 == true){
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3, 0x04); //0000 0010
            P2 = 0b00000010;
        }
        else{
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2|GPIO_PIN_3, 0x08); //0000 0000
            P2 = 0b00000000;
        }
        if(S3 == true){
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_5, 0x10); //0000 0100
            P3 = 0b00000100;
        }
        else{
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_4|GPIO_PIN_5, 0x20); //0000 0000
            P3 = 0b00000000;
        }
        if(S4 == true){
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6|GPIO_PIN_7, 0x40); //0000 1000
            P4 = 0b00001000;
        }
        else{
            GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_6|GPIO_PIN_7, 0x80); //0000 0000
            P4 = 0b00000000;
        }
        // Se obtiene un numerio binario de estado del parqueo completo
        parking = P1 + P2 + P3 + P4;
        // Se envia el estado del parqueo por UART
        UARTCharPut(UART1_BASE,parking);
    }
}
// Se define la interrupcion UART
void UARTIntHandler(void){
    // Se verifica el estado del modulo
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART1_BASE, true);
    // Se limpian los estados
    UARTIntClear(UART1_BASE, ui32Status);
    while(UARTCharsAvail(UART1_BASE)){
        UARTCharPutNonBlocking(UART1_BASE, parking);
    }
}
