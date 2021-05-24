/**
 * Project Stm32Project
 */


#include "Acceleration.h"

/**
 * Acceleration implementation
 */


/**
 * @return void
 */
void Acceleration::Measure() 
{
    float* measuredData = m_sensor.Get(); 
    for (int i = 0; i < 3; i++)
    {
        if (i == 0)
        {
            ADXL345_ACCELX = m_filter_x.Calculate( *(measuredData + i) ); 
        }
        else if (i == 1)
        {
            ADXL345_ACCELY = m_filter_y.Calculate( *(measuredData + i) ); 
        }
        else if (i == 2)
        {
            ADXL345_ACCELZ = m_filter_z.Calculate( *(measuredData + i) ); 
        }
    }
}

/**
 * @return float[]
 */
float Acceleration::GetValue() 
{
    if (index == 0)
    {
        index++; 
        return ADXL345_ACCELX; 
    }
    else if (index == 1)
    {
        index++; 
        return ADXL345_ACCELY; 
    }
    else if (index == 2)
    {
        index = 0; 
        return ADXL345_ACCELZ; 
    }
}