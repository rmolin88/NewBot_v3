#include "../include/uart.h"

extern volatile uint8_t bRxFlag;
extern volatile char cRxData;

void UARTInit()
{
#define BSEL 131
#define BSCALE -3

	// USART initialization should use the following sequence:
	// 1. Set the TxD pin value high, and optionally set the XCK pin low.
	// 2. Set the TxD and optionally the XCK pin as output.
	PORTC_DIR |= PIN7_bm;
	// PORTC_OUTSET |= PIN7_bm;					
	// PORTC_DIRCLR |= PIN6_bm; // Set RxD pin as input 

	// 3. Set the baud rate and frame format.
	// Setting baud rate 230.4k for CLK2X=0
	// Bsel = 123 = 0x7b, Bscale = -4 = 0xfc;
	// Setting baud rate 2M for CLK2X=0
	// Bsel = 0, Bscale = 0;
	// Setting baud rate 115.2k for CLK2X=0
	// Bsel = 131, Bscale = -3;
	USARTC1_BAUDCTRLA |= (USART_BSEL_gm & BSEL);
	USARTC1_BAUDCTRLB |= ((BSCALE << 4) | ((BSEL & 0xf00) >> 8));

	// 4. Set the mode of operation (enables XCK pin output in synchronous mode).
	USARTC1_CTRLC |= (USART_CMODE_ASYNCHRONOUS_gc | USART_PMODE_DISABLED_gc | USART_CHSIZE_8BIT_gc);		//ASYNCHRONOUS MODE

	USARTC1_CTRLA |= USART_RXCINTLVL0_bm;	//RECEIVED INTERRUPT ENABLE
	// 5. Enable the transmitter or the receiver, depending on the usage.
	USARTC1_CTRLB |= (USART_RXEN_bm | USART_TXEN_bm);// 0x18;	//receiver and transmitter enabled
}				


ISR(USARTC1_RXC_vect)
{
	while(!(USARTC1_STATUS & USART_RXCIF_bm))  // Wait for the Receive Complete Interrupt Flag
		_NOP(); 								// to be set 
	cRxData = USARTC1_DATA; 				// Load the data  
	bRxFlag = 1;
}


void UARTTrans(char cData)
{
	while(!(USARTC1_STATUS & USART_DREIF_bm))  // Wait for the Data Register Empty 
		_NOP();							// Flag to be set
	USARTC1_DATA = cData; 				// Copy data
}
