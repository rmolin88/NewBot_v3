#include "../include/atxmega.h"

volatile char cDataWrite[256];
volatile char *pDataReceived = cDataWrite;

int main(void)
{
	cli(); // Disable global interrupts during initialization 

	Clk32MhzInit();
	WDTDisble();
	UARTInit();

	// Enable low level interrupts
	PMIC_CTRL |= PMIC_LOLVLEX_bm;
	sei();

	// On board LED = E1
	PORTE.DIRSET |= PIN1_bm;

	while(1)
	{
		_delay_ms(1000);
		// PORTE.OUTTGL |= PIN1_bm;
		// UARTTrans('8'); 
	}
	return 0;
}
