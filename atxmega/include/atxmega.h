#ifndef ATXMEGA_H
#define ATXMEGA_H

// Eliminating clang warnings. All of the below are already defined
#ifndef __AVR_ATxmega128A4U__
#define __AVR_ATxmega128A4U__
#endif

#ifndef F_CPU
#define F_CPU 32000000UL
#endif

#ifndef __OPTIMIZE__
#define __OPTIMIZE__
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h> // for _NOP 
#include <util/delay.h> // for _delay_ms 
#include "uart.h"
#include "sys_clk.h"
#include "buffer.h"


#endif // ATXMEGA_H
