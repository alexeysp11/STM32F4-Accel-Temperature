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
    Temperature(TempSensor& sensor, 
                             IFilter& filter) : m_sensor(sensor), m_filter(filter) 
    {
    }
        
    void Measure();
        
    float GetValue();
private: 
    TempSensor& m_sensor;
    IFilter& m_filter;
    float value = 0.0f; 
};

#endif //_TEMPERATURE_H