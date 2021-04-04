/**
 * Project Stm32Project
 */


#ifndef _I2CDRIVER_H
#define _I2CDRIVER_H

#include "IDataSource.h"


class I2CDriver: public IDataSource 
{
public: 
    /**
     * @param i2c
     */
    void I2CDriver(I2C& i2c);
        
    float Get();
private: 
    I2C& m_i2c;
};

#endif //_I2CDRIVER_H