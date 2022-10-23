/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	18 September 2022	 ***/
/*******************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define LCD_AVAIL 1
/*----------------- Include -------------------*/
#include <avr/io.h>
#include "LCD.h"
#include "I2C.h"



/*-------------- Main function ----------------*/
int main (void)
{
#if LCD_AVAIL
	initLCD();		// LED initialization
#endif
	uint8_t i2c_res = 0;
	uint8_t i = 0;
	i2c_init();		// i2c initialization


	while (1)
	{	
		i += 1;
		i2c_res = i2c_readAck();
		displayLCD_main(4, "Iteration: ", i, "NONE");
		displayLCD_main(3, "Data: ", i2c_res, "NONE");
		
		displayLCD_main(2, "btn: ", i2c_res, "NONE");
		if (i2c_res > 0)
		{
			displayLCD_main(1, "Btn. is pressed", NONE, "NONE");
		}
		else
		{
			displayLCD_main(1, "Btn. is not pressed", NONE, "NONE");
		}
#if LCD_AVAIL
// 		displayLCD_main(1, "Iteration: ", i, "NONE");
// 		displayLCD_main(2, "TWSR: ", TWSR, "NONE");
// 		displayLCD_main(3, "i2c_res: ", i2c_res, "NONE");
// 		_delay_ms(5000);
#endif
	}
}
