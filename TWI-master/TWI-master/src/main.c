/*******************************/
/*** Created by Ovidiu Sabau ***/
/***	18 September 2022	 ***/
/*******************************/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#define LCD_AVAIL 0
/*----------------- Include -------------------*/
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"
#include "LCD.h"
#include "Btn.h"

/*-------------- Main function ----------------*/
int main(void)
{
#if LCD_AVAIL
	initLCD();		// LED initialization
#endif
	unsigned char data = 99;
	uint8_t i = 0;
	init_Btn();				// Initialize button
	i2c_init();				// Initialize I2C
	uint8_t btn_state = 0;	// Variable for button state (pressed / released)
	while (1)
	{
		i += 1;
		btn_state = Btn_pin & (1<<Btn_bit);		// check button state
		//btn_state = 0;
		write_i2c(btn_state);
		_delay_ms(1000);
	#if LCD_AVAIL
		displayLCD_main(1, "Iteration: ", i, "NONE");
		displayLCD_main(2, "TWSR: ", TWSR, "NONE");
		displayLCD_main(3, "TWDR: ", TWDR, "NONE");
		displayLCD_main(4, "TWCR: ", TWCR, "NONE");
		_delay_ms(5000);
	#endif
 	}
}