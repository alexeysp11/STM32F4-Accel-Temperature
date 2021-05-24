/**
 * Project Stm32Project
 */


#include "I2CDriver.h"

/**
 * I2CDriver implementation
 */


/**
 * @return float
 */
float I2CDriver::Get(char device, char reg, std::uint16_t *var) 
{
    // Get value from I2C_DR 
    m_i2c.Write(device, reg);
    m_i2c.Read(device, var);

    return (float)(*var);
}