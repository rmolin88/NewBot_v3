#include "../include/atxmega.h"

// Change the configuration protecction for CLK.CTRL
void Clk32MhzInit()
{
	OSC.CTRL |= OSC_RC32MEN_bm;  // Select the 32Mhz Osc
	while(!(OSC.STATUS & OSC_RC32MRDY_bm)); // Wait for 32Mhz to be ready

	CCP |= CCP_IOREG_gc;  // Protected select no divisor of main clk
	CLK.PSCTRL |= (CLK_PSADIV_1_gc | CLK_PSBCDIV_1_1_gc );

	CCP |= CCP_IOREG_gc;  // Protected switch to the 32Mhz Clk
	CLK.CTRL |= CLK_SCLKSEL_RC32M_gc;

	OSC.CTRL &= ~OSC_RC2MEN_bm;  // Disable 2Mhz Clk
}

void WDTDisble()
{
	CCP |= CCP_IOREG_gc;  // Protected Disable WDT
	WDT.CTRL |= ((WDT.CTRL & ~WDT_ENABLE_bm) | WDT_CEN_bm);  // Clear WEN and set WCEN
}
