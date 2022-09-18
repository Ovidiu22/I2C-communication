/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	18 September 2022	 ***/
/*******************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/*----------------- Include -------------------*/
#include <avr/io.h>
#include "LCD.h"
#include "I2C.h"



/*-------------- Main function ----------------*/
int main (void)
{
	unsigned char i2c_res = 0;
	initLCD();		// LED initialization
	i2c_init();		// i2c initialization
	i2c_set_address();

	while (1)
	{
		displayLCD_main(1, "Hello there!", NONE, "NONE");
		i2c_start_read();
		i2c_res = i2c_readAck();
				
		displayLCD_main(2, "Data: ", i2c_res, "NONE");
		displayLCD_main(3, "Status register", TWSR, "NONE");
		
		displayLCD_main(4, "End of sequence", NONE, "NONE");
	}
}
