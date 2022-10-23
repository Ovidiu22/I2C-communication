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
	unsigned char i2c_res = 99;
	uint8_t i = 0;
	i2c_init();		// i2c initialization
	i2c_set_address();
displayLCD_main(1, "Init complete", NONE, "NONE");

	while (1)
	{	
		i += 1;
		i2c_start_SR();
#if LCD_AVAIL
		displayLCD_main(1, "Iteration: ", i, "NONE");
		displayLCD_main(2, "TWSR: ", TWSR, "NONE");
		displayLCD_main(3, "TWDR: ", TWDR, "NONE");
		displayLCD_main(4, "TWCR: ", TWCR, "NONE");
		_delay_ms(5000);
#endif
	}
}
