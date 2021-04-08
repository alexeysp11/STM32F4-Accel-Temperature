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
    TempSensor(AdcDriver adcDriver) : m_ds(adcDriver)
    {
    }
        
    float Get();
private: 
    IDataSource& m_ds;
};

#endif //_TEMPSENSOR_H