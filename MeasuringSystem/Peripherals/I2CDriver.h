/**
 * Project Stm32Project
 */


#ifndef _I2CDRIVER_H
#define _I2CDRIVER_H

#include "IDataSource.h"        // for IDataSource. 
#include "I2C.h"                // for I2C. 

#include "i2c1registers.hpp"    // for I2C registers. 


class I2CDriver: public IDataSource 
{
public: 
    /**
     * @param i2c
     */
    I2CDriver(I2C<I2C1>& i2c) : m_i2c(i2c)
    {
    }
        
    float Get();
private: 
    I2C<I2C1>& m_i2c;
};

#endif //_I2CDRIVER_H