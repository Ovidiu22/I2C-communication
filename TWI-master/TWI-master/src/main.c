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

/*-------------- Main function ----------------*/
int main(void)
{
	uint8_t data = 12;
	i2c_init();				// Initialize I2C
	i2c_set_address();
	//i2c_start_wait(I2C_DEVICE+I2C_WRITE);		
	while (1)
	{
		//i2c_readNak();
		write_i2c(data);		// Send data over i2c
	}
}