/**
 * Project Stm32Project
 */


#include "AccelDriver.h"

/**
 * AccelDriver implementation
 */


/**
 * @return float[]
 */
float* AccelDriver::Get() 
{
    ADXL345_ACCELX = m_ds.Get(ADXL345_ADDRESS, ADXL345_DATAX0, &ADXL345_ACCELX_UINT16); 
    ADXL345_ACCELY = m_ds.Get(ADXL345_ADDRESS, ADXL345_DATAY0, &ADXL345_ACCELY_UINT16); 
    ADXL345_ACCELZ = m_ds.Get(ADXL345_ADDRESS, ADXL345_DATAZ0, &ADXL345_ACCELZ_UINT16); 
    return *ADXL345_ACCEL_DATA;
}