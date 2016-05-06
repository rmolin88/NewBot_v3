#include "../include/atxmega.h"

// Change the configuration protecction for CLK.CTRL
void Clk32MhzInit()
{
	OSC.CTRL |= PIN1_bm;  // Select the 32Mhz Osc
	while(!(OSC.STATUS & PIN1_bm)); /*Wait for 32Mhz to be ready*/ 

	// Protected select no divisor of main clk
	CCP |= CCP_IOREG_gc;
	CLK.PSCTRL |= (CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc );

	// Protected switch to the 32Mhz Clk
	CCP |= CCP_IOREG_gc;
	CLK.CTRL |= CLK_SCLKSEL_RC32M_gc;

	// Disable 2Mhz Clk
	OSC.CTRL &= ~PIN0_bm;
}

void WDTDisble()
{
	// Protected Disable WDT
	CCP |= CCP_IOREG_gc;
	// Clear WEN and set WCEN
	WDT.CTRL |= ((WDT.CTRL & ~PIN1_bm) | PIN0_bm);
}
