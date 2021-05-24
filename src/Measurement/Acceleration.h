/**
 * Project Stm32Project
 */


#ifndef _ACCELERATION_H
#define _ACCELERATION_H

#include "IVariableAccel.h"     // for IVariableAccel. 
#include "AccelDriver.h"        // for AccelDriver. 
#include "IFilter.h"            // for IFilter. 
#include "ADXL345.h"            // for ADXL345 registers. 


class Acceleration: public IVariableAccel 
{
public: 
    /**
     * @param sensor
     * @param filter
     */
    Acceleration(AccelDriver& sensor, IFilter& filter_x, IFilter& filter_y, 
                 IFilter& filter_z) : m_sensor(sensor), m_filter_x(filter_x), 
                             m_filter_y(filter_y), m_filter_z(filter_z)
    {
    }
    
    void Measure();
    
    float GetValue();
private: 
    float* values;
    int index = 0; 
    AccelDriver& m_sensor;
    IFilter& m_filter_x;
    IFilter& m_filter_y;
    IFilter& m_filter_z;
};

#endif //_ACCELERATION_H