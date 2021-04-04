/**
 * Project Stm32Project
 */


#ifndef _ACCELERATION_H
#define _ACCELERATION_H

#include "IVariableAccel.h"


class Acceleration: public IVariableAccel 
{
public: 
    /**
     * @param sensor
     * @param filter
     */
    void AccelerationX(AccelDriver& sensor, IFilter& filter);
    
    void Measure();
    
    float[] GetValue();
private: 
    float[] value;
    AccelDriver& m_sensor;
    IFilter& m_filter;
};

#endif //_ACCELERATION_H