/*
 * I2C.h
 *
 * Created: 18.09.2022 11:18:20
 *  Author: lenovo
 */ 


#ifndef I2C_H_
#define I2C_H_

#if (__GNUC__ * 100 + __GNUC_MINOR__) < 304
#error "This library requires AVR-GCC 3.4 or later, update to newer AVR-GCC compiler !"
#endif

	#include <avr/io.h>
// 	#include <util/delay.h>
// 	#include <stdbool.h>
// 	#include <stdint.h>
	//#include "i2cmaster.h"


	#define I2C_DEVICE                  0x27    
	
	/* Functions */

	void write_i2c(unsigned char value);                //-     Write data to i2c
	unsigned char read_i2c(void);                       //-     Read data from i2c
	void i2c_set_address(void);
	void i2c_start_read(void);
	void i2c_stop(void);

/** defines the data direction (reading from I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_READ    1

/** defines the data direction (writing to I2C device) in i2c_start(),i2c_rep_start() */
#define I2C_WRITE   0


/**
 @brief initialize the I2C master interace. Need to be called only once 
 @param  void
 @return none
 */
extern void i2c_init(void);


/** 
 @brief Terminates the data transfer and releases the I2C bus 
 @param void
 @return none
 */
extern void i2c_stop(void);


/** 
 @brief Issues a start condition and sends address and transfer direction 
  
 @param    addr address and transfer direction of I2C device
 @retval   0   device accessible 
 @retval   1   failed to access device 
 */
extern unsigned char i2c_start(unsigned char addr);


/**
 @brief Issues a repeated start condition and sends address and transfer direction 

 @param   addr address and transfer direction of I2C device
 @retval  0 device accessible
 @retval  1 failed to access device
 */
extern unsigned char i2c_rep_start(unsigned char addr);


/**
 @brief Issues a start condition and sends address and transfer direction 
   
 If device is busy, use ack polling to wait until device ready 
 @param    addr address and transfer direction of I2C device
 @return   none
 */
 extern void i2c_start_wait(unsigned char addr);

 
/**
 @brief Send one byte to I2C device
 @param    data  byte to be transfered
 @retval   0 write successful
 @retval   1 write failed
 */
extern unsigned char i2c_write(unsigned char data);


/**
 @brief    read one byte from the I2C device, request more data from device 
 @return   byte read from I2C device
 */
extern unsigned char i2c_readAck(void);

/**
 @brief    read one byte from the I2C device, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char i2c_readNak(void);

/** 
 @brief    read one byte from the I2C device
 
 Implemented as a macro, which calls either i2c_readAck or i2c_readNak
 
 @param    ack 1 send ack, request more data from device<br>
               0 send nak, read is followed by a stop condition 
 @return   byte read from I2C device
 */
extern unsigned char i2c_read(unsigned char ack);
#define i2c_read(ack)  (ack) ? i2c_readAck() : i2c_readNak(); 

void i2c_start_SR(void);
	
#endif /* I2C_H_ */