/**
 * Project Stm32Project
 */


#ifndef _TEMPSENSOR_H
#define _TEMPSENSOR_H

#include "AdcDriver.h"              // for AdcDriver. 
#include "IDataSource.h"            // for IDataSource. 


class TempSensor 
{
public: 
    /**
     * @param adcDriver
     */
    explicit TempSensor(AdcDriver& adcDriver) : m_ds(adcDriver)
    {
    }
        
    float Get() const;
private: 
    IDataSource& m_ds;
    float V25 = 0.76f;
    float AVG_Slope = 0.0025f;
};

#endif //_TEMPSENSOR_H