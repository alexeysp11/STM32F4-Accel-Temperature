/**
 * Project Stm32Project
 */


#ifndef _ADC_H
#define _ADC_H

#include "adc1registers.hpp"    // for ADC1 registers. 

/**
 * Adc implementation
 */

template<typename Port>
class Adc 
{
public: 
    /**
     * @return float
     */
    float Get()
    {
        return Port::DR::DATA::Get();
    }
    
    void Convert()
    {
        Port::CR2::SWSTART::On::Set();
        while(!Port::SR::EOC::ConversionComplete::IsSet());
    }
};

#endif //_ADC_H