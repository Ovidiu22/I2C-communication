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
	displayLCD_main(1, "Init complete", NONE, "NONE");

	/* MT */
	while (1)
	{
		write_i2c(i2c_res);
		_delay_ms(2000);
	}
#if 0
	/* SR */
	while (1)
	{
		//i2c_start_SR();				displayLCD_main(2, "End of start", NONE, "NONE");		
		i2c_res = i2c_readNak();	displayLCD_main(3, "Data = ", i2c_res, "NONE"); //displayLCD_main(3, "End of data read", NONE, "NONE");		
		//i2c_stop();				displayLCD_main(4, "End of sequence", NONE, "NONE");
		_delay_ms(2000);
	}
#endif
}
