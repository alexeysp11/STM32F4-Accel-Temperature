/**
 * Project Stm32Project
 */


#ifndef _TEMPERATURE_H
#define _TEMPERATURE_H

#include "IVariableTemp.h"


class Temperature: public IVariableTemp 
{
public: 
    /**
     * @param sensor
     * @param filter
     */
    void Temperature(TempSensor& sensor, IFilter& filter);
        
    void Measure();
        
    float GetValue();
private: 
    TempSensor& m_sensor;
    IFilter& m_filter;
};

#endif //_TEMPERATURE_H