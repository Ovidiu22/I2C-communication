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
	unsigned char i2c_res = 52;
	initLCD();		// LED initialization
	i2c_init();		// i2c initialization
	i2c_set_address();

	while (1)
	{
		displayLCD_main(1, "Hello there!", NONE, "NONE");
		//i2c_readNak();
		//i2c_res = i2c_readAck();
		displayLCD_main(2, "TWAR: ", TWAR, "NONE");
		
		i2c_start(I2C_DEVICE+I2C_WRITE);	// Send start condition and set transmission mode
		
		i2c_write(i2c_res);					// Send data
		
		i2c_stop();							// Stop command
						
		displayLCD_main(2, "End of sequence", NONE, "NONE");
		_delay_ms(2000);
	}
}
