/**
 * Project Stm32Project
 */


#ifndef _ACCELERATION_H
#define _ACCELERATION_H

#include "IVariableAccel.h"     // for IVariableAccel. 
#include "AccelDriver.h"        // for AccelDriver. 
#include "IFilter.h"            // for IFilter. 


class Acceleration: public IVariableAccel 
{
public: 
    /**
     * @param sensor
     * @param filter
     */
    Acceleration(AccelDriver& sensor, 
                              IFilter& filter) : m_sensor(sensor), m_filter(filter)
    {
    }
    
    void Measure();
    
    float* GetValue();
private: 
    float* value;
    AccelDriver& m_sensor;
    IFilter& m_filter;
};

#endif //_ACCELERATION_H