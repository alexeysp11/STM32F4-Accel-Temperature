/**
 * Project Stm32Project
 */


#ifndef _ADCDRIVER_H
#define _ADCDRIVER_H

#include "IDataSource.h"        // for IDataSource. 
#include "Adc.h"                // for Adc. 

#include "adc1registers.hpp"    // for ADC registers. 


class AdcDriver: public IDataSource 
{
public: 
    /**
     * @param adc
     */
    AdcDriver(Adc<ADC1>& adc) : m_adc(adc)
    {
    }
        
    float Get();
private: 
    Adc<ADC1>& m_adc;
};

#endif //_ADCDRIVER_H