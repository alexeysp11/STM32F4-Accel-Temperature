/**
 * Project Stm32Project
 */


#ifndef _ACCELDRIVER_H
#define _ACCELDRIVER_H

#include "I2CDriver.h"              // for I2CDriver. 
#include "IDataSource.h"            // for IDataSource. 

class AccelDriver 
{
public: 
    /**
     * @param i2cDriver
     */
    AccelDriver(I2CDriver& i2cDriver) : m_ds(i2cDriver)
    {
    }
        
    float* Get();
private: 
    IDataSource& m_ds;
};

#endif //_ACCELDRIVER_H