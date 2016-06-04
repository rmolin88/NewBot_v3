#include "../include/atxmega.h"

#define BUFFER_SIZE 64
#define MSG_LENGTH 14 // S100010001000 + EOT

volatile uint8_t bRxFlag;

int main(void)
{
	Clk32MhzInit();
	WDTDisble();
	UARTInit();

	bRxFlag = 0; // Clearing globals 

	char buffer[BUFFER_SIZE] = {0};
	rb_attr_t attr = 
	{
		sizeof(char),
		BUFFER_SIZE,
		buffer
	};

	if (ring_buffer_init(&attr) != 0)
		while(1); // LED would not light if cant start buffer

	PMIC_CTRL |= PMIC_LOLVLEX_bm;  // Enable low level interrupts
	sei(); // Enable Global Interrupts

	PORTE.DIR |= PIN1_bm;  // On board LED = E1
	PORTE.OUT |= PIN1_bm;  


	char cLocData[32] = {0}, *pData = cLocData;

	while(1)
	{
		// Read buffer for msg length
		// copy it somewhere
		// transmit it back
		// reset flag
		int k;
		if (bRxFlag == MSG_LENGTH) // Account for \0
		{
			// cli(); 
			for (pData = cLocData,k=0; k<MSG_LENGTH; k++) // Initialize pointer
				ring_buffer_get(pData++); // read all data

			for (k=0; k<MSG_LENGTH; k++)
				UARTTrans(cLocData[k]); // transmit all data back

			bRxFlag = 0;
			// sei();
		}
	}
	return 0;
}
