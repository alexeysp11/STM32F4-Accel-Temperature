/**
 * Project Stm32Project
 */


#include "AdcDriver.h"

/**
 * AdcDriver implementation
 */


/**
 * @return float
 */
float AdcDriver::Get() 
{
    m_adc.Convert();
    return m_adc.Get();
}