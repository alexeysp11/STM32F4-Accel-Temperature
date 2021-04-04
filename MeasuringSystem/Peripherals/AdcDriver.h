/**
 * Project Stm32Project
 */


#ifndef _ADCDRIVER_H
#define _ADCDRIVER_H

#include "IDataSource.h"


class AdcDriver: public IDataSource 
{
public: 
    /**
     * @param adc
     */
    void AdcDriver(Adc& adc);
        
    float Get();
private: 
    Adc& m_adc;
};

#endif //_ADCDRIVER_H