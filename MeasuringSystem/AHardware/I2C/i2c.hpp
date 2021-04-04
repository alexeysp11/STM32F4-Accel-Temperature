/*
 * i2c.h
 *
 *  Created on: 5 Mar 2017
 *      Author: rafpe
 *  
 *  Modified by: alexeysp11 in 2021 
 */

/*
* This file contains declaration of a class I2CBase. 
*/ 

#ifndef INC_I2C_H_
#define INC_I2C_H_

class I2CBase
{
public:
    void i2c_setup_gpio(void);
    void rcc_init(void);
    void i2c_init(void);
    uint8_t i2c_read(uint8_t address, uint8_t registry);
    void i2c_read_many(uint8_t address, uint8_t registry, uint8_t * result, uint8_t length);
    void i2c_write_many(uint8_t address, uint8_t registry, uint8_t* buf, uint32_t length) ;
    void i2c_write(uint8_t address, uint8_t registry, uint8_t data) ;
}

#endif  /* INC_I2C_H_ */
