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
			
	while (1)
	{
		write_i2c(data);		// Send data over i2c
	}
}