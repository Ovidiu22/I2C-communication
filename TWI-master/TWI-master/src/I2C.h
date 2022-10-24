
#ifndef I2C_H_
#define I2C_H_

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

	#include <avr/io.h>

	/* Address of I2C device */
	#define I2C_DEVICE                  0x27    
	
	/* defines the data direction to read */
	#define I2C_READ    1

	/* defines the data direction to write */
	#define I2C_WRITE   0

	/* Functions */
	void write_i2c(unsigned char value);
	extern void i2c_init(void);
	extern void i2c_stop(void);
	extern unsigned char i2c_start(unsigned char addr);
	extern unsigned char i2c_rep_start(unsigned char addr);
	extern unsigned char i2c_write(unsigned char data);

#endif /* I2C_H_ */