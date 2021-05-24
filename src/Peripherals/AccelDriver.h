/**
 * Project Stm32Project
 */


#ifndef _ACCELDRIVER_H
#define _ACCELDRIVER_H

#include "I2CDriver.h"              // for I2CDriver. 
#include "IDataSource.h"            // for IDataSource. 
#include "ADXL345.h"                // for ADXL345.h. 

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
    I2CDriver& m_ds;
};

#endif //_ACCELDRIVER_H