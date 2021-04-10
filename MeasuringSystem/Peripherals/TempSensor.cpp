/**
 * Project Stm32Project
 */


#include "TempSensor.h"

/**
 * TempSensor implementation
 */


/**
 * @return float
 */
float TempSensor::Get() const 
{
    return ( ((m_ds.Get() * 3.3) / 4096 - V25) / AVG_Slope ) + 25.0;
}