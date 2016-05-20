#include "../include/atxmega.h"

volatile uint8_t bRxFlag;
volatile char cRxData;

int main(void)
{
	Clk32MhzInit();
	WDTDisble();
	UARTInit();

	cRxData = bRxFlag = 0; // Clearing globals 

	PMIC_CTRL |= PMIC_LOLVLEX_bm;  // Enable low level interrupts
	sei(); // Enable Global Interrupts

	PORTE.DIR |= PIN1_bm;  // On board LED = E1

	char cLocData[32] = {0}, *pData = cLocData;
	while(1)
	{
		if (bRxFlag)
		{
			*pData = cRxData; // Copy rx data
			bRxFlag = 0; // Reset Flag

			if (*pData == '\0') // Check for EOT flag
			{
				cli(); // Allow me time to process this data uninterrupted 

				pData = cLocData; // Reset pointer

				while (*pData != '\0') // use this data 
				{
					UARTTrans(*pData); // for now just send it back 
					pData++;
				}

				pData = cLocData; // Reset pointer
				*pData = 0; // Reset Data

				PORTE.OUT ^= PIN1_bm; // Signal full transmition rcvd

				sei(); // Get back to receiving data 
			}
			else // not EOT just point to next char 
				pData++;
		}
	}
	return 0;
}
