#ifndef UART_H
#define UART_H

#include "atxmega.h" // Because I need shared volatile vars

void UARTTrans(char cData);
void UARTInit(void);

#endif // UART_H
