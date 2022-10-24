/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	18 September 2022	 ***/
/*******************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/*----------------- Include -------------------*/
#include <avr/io.h>
#include "I2C.h"
#include "LCD.h"

/*-------------- Main function ----------------*/
int main (void)
{
	uint8_t i2c_res = 0;
	i2c_init();		// i2c initialization
	initLCD();		// LED initialization
	while (1)
	{	
		i2c_res = i2c_readAck();
		
		if (i2c_res > 0)
		{
			displayLCD_main(1, "Btn. is pressed", NONE, "NONE");
		}
		else
		{
			displayLCD_main(1, "Btn. is not pressed", NONE, "NONE");
		}
	}
}
