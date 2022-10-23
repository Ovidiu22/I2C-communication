
#include <avr/io.h>
#include "Btn.h"


/* *****************************************************************
Name:		init_Btn()
Inputs:		none
Outputs:	none
Description:initializes PIN D3 as an output with initial state low
******************************************************************** */
void init_Btn(void)
{
	DDRD |= (1<<Btn_bit);
	PORTD &= ~(1<<Btn_bit);
}
