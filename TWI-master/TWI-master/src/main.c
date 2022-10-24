/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	18 September 2022	***/
/*******************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/*----------------- Include -------------------*/
#include <avr/io.h>
#include "I2C.h"
#include "Btn.h"

/*-------------- Main function ----------------*/
int main(void)
{
	init_Btn();				// Initialize button
	i2c_init();				// Initialize I2C
	uint8_t btn_state = 0;	// Variable for button state (pressed / released)
	
	while (1)
	{
		btn_state = Btn_pin & (1<<Btn_bit);		// check button state
		write_i2c(btn_state);
 	}
}