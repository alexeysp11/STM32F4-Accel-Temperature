/**
 * Project Stm32Project
 */


#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

#include "IVariableTemp.h"
#include "TempSensor.h"         // for TempSensor. 
#include "IFilter.h"            // for IFilter. 


class Temperature: public IVariableTemp 
{
public: 
    /**
     * @param sensor
     * @param filter
     */
    explicit Temperature(TempSensor& sensor, 
                             IFilter& filter) : m_sensor(sensor), m_filter(filter) 
    {
    }
        
    void Measure() override;
        
    float GetValue() override;
private: 
    TempSensor& m_sensor;
    IFilter& m_filter;
    float value = 0.0f; 
};

#endif //_TEMPERATURE_H