/**
 * Project Stm32Project
 */


#ifndef _TEMPSENSOR_H
#define _TEMPSENSOR_H

class TempSensor 
{
public: 
    /**
     * @param adcDriver
     */
    void TempSensor(AdcDriver adcDriver);
        
    float Get();
private: 
    IDataSource& m_ds;
};

#endif //_TEMPSENSOR_H