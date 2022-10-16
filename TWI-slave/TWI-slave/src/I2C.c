/*
 * I2C.c
 *
 * Created: 18.09.2022 11:18:35
 *  Author: lenovo
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/* I2C clock in Hz */
#define SCL_CLOCK  100000L

#include <inttypes.h>
#include <compat/twi.h>
#include "I2C.h"
#include "LCD.h"


void write_i2c(unsigned char value)
{
												displayLCD_main(2, "Inside write_i2c", NONE, "NONE");
	i2c_start_wait(I2C_DEVICE+I2C_WRITE);		displayLCD_main(2, "Start successful", NONE, "NONE");
	
	i2c_write(value);							displayLCD_main(2, "Write successful", NONE, "NONE");
	
	i2c_stop();									displayLCD_main(2, "stop successful", NONE, "NONE");
	
}


//-     Read data from i2c
unsigned char read_i2c(void)
{
	unsigned char lcddata = 0x00;
	i2c_start_wait(I2C_DEVICE+I2C_READ);
	lcddata = i2c_readNak();
	i2c_stop();
	return lcddata;
}




/*************************************************************************
 Initialization of the I2C bus interface. Need to be called only once
*************************************************************************/
void i2c_init(void)
{
  /* initialize TWI clock: 100 kHz clock, TWPS = 0 => prescaler = 1 */
  
  TWSR = 0;                         /* no prescaler */
  TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */


}/* i2c_init */

void i2c_set_address(void)
{
	TWAR = I2C_DEVICE;
}

/*************************************************************************	
  Issues a start condition and sends address and transfer direction.
  return 0 = device accessible, 1= failed to access device
*************************************************************************/
unsigned char i2c_start(unsigned char transmissionMode)
{
	displayLCD_main(1, "Inside i2c_start", NONE, "NONE");
	//displayLCD_main(2, "TWSR: ", TWSR, "NONE");
	
    uint8_t   twst = 0;

// 1. send START condition
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);


	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));

		displayLCD_main(3, "TWSR: ", TWSR, "NONE");		// Expected 0x08

	// check value of TWI Status Register. Mask prescaler bits.
	//twst = TW_STATUS & 0xF8;		// TWSR
	//if ( (twst != TW_START) && (twst != TW_REP_START)) return 1;

	//displayLCD_main(3, "TW_STATUS: ", TW_STATUS, "NONE");

// 2. send transmission mode SLA+W (MT) or SLA+R (MR)

	TWDR = transmissionMode;
	
	TWCR = (1<<TWINT) | (1<<TWEN);

//displayLCD_main(2, "TWDR: ", TWDR, "NONE");

//displayLCD_main(3, "TWCR SLA+W: ", TWCR, "NONE");

//displayLCD_main(4, "TWSR SLA+W: ", TWSR, "NONE");

	// wail until transmission completed and ACK/NACK has been received
	while(!(TWCR & (1<<TWINT)));

	// check value of TWI Status Register. Mask prescaler bits.
	//twst = TW_STATUS & 0xF8;
	if ( (twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
displayLCD_main(4, "TW_STATUS: ", TW_STATUS, "NONE");
	return 0;

}/* i2c_start */


/*************************************************************************
 Issues a start condition and sends address and transfer direction.
 If device is busy, use ack polling to wait until device is ready
 
 Input:   address and transfer direction of I2C device
*************************************************************************/
void i2c_start_wait(unsigned char address)
{
    uint8_t   twst;


    while ( 1 )
    {
	    // send START condition
	    TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);				displayLCD_main(1, "TWSR: ", TWSR, "NONE");

    	// wait until transmission completed
    	while(!(TWCR & (1<<TWINT)));
    
    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;								displayLCD_main(2, "TWSR: ", TWSR, "NONE");		// Expected 0x08
		
    	if ( (twst != TW_START) && (twst != TW_REP_START)) continue;
    
    	// send device address
    	TWDR = address;
    	TWCR = (1<<TWINT) | (1<<TWEN);
    
    	// wail until transmission completed
    	while(!(TWCR & (1<<TWINT)));
    
    	// check value of TWI Status Register. Mask prescaler bits.
    	twst = TW_STATUS & 0xF8;								displayLCD_main(3, "TWSR: ", TWSR, "NONE");		// Expected 0x08
    	if ( (twst == TW_MT_SLA_NACK )||(twst ==TW_MR_DATA_NACK) ) 
    	{    	    
    	    /* device busy, send stop condition to terminate write operation */
	        TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	        
	        // wait until stop condition is executed and bus released
	        while(TWCR & (1<<TWSTO));
	        
    	    continue;
    	}
    	//if( twst != TW_MT_SLA_ACK) return 1;
    	break;
     }

}/* i2c_start_wait */

void i2c_start_SR(void)
{
	while (1)
	{
		// send START condition
		TWCR = (1<<TWINT) | (1<<TWEN);

		// wait until transmission completed
		while(!(TWCR & (1<<TWINT)));
		
		break;
}

	}/* i2c_start */

void i2c_start_read(void)
{
	// send START condition
	TWCR = (1<<TWEA) | (1<<TWEN);
		
	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));
	
}/*  */



/*************************************************************************
 Issues a repeated start condition and sends address and transfer direction 

 Input:   address and transfer direction of I2C device
 
 Return:  0 device accessible
          1 failed to access device
*************************************************************************/
unsigned char i2c_rep_start(unsigned char address)
{
    return i2c_start( address );

}/* i2c_rep_start */


/*************************************************************************
 Terminates the data transfer and releases the I2C bus
*************************************************************************/
void i2c_stop(void)
{
    /* send stop condition */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
	
	// wait until stop condition is executed and bus released
	while(TWCR & (1<<TWSTO));

}/* i2c_stop */


/*************************************************************************
  Send one byte to I2C device
  
  Input:    byte to be transfered
  Return:   0 write successful 
            1 write failed
*************************************************************************/
unsigned char i2c_write( unsigned char data )
{	
    uint8_t   twst;
    
	// send data to the previously addressed device
	
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	
	// wait until transmission completed
	while(!(TWCR & (1<<TWINT)));
	
TWDR = data;

	// check value of TWI Status Register. Mask prescaler bits
	twst = TW_STATUS & 0xF8;
	if( twst != TW_MT_DATA_ACK) return 1;
	return 0;

}/* i2c_write */


/*************************************************************************
 Read one byte from the I2C device, request more data from device 
 
 Return:  byte read from I2C device
*************************************************************************/
unsigned char i2c_readAck(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while(!(TWCR & (1<<TWINT)));    

    return TWDR;

}/* i2c_readAck */


/*************************************************************************
 Read one byte from the I2C device, read is followed by a stop condition 
 
 Return:  byte read from I2C device
*************************************************************************/
unsigned char i2c_readNak(void)
{
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
    return TWDR;

}/* i2c_readNak */
