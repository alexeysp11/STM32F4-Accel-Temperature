/**
 * Project Stm32Project
 */


#ifndef _MEASURECONFIG_H
#define _MEASURECONFIG_H

/*****************************************************
 * Includes for application. 
 *****************************************************/

#include "Temperature.h"        // for Temperature. 
#include "Acceleration.h"       // for Acceleration. 

#include "TempSensor.h"         // for TempSensor. 
#include "AccelDriver.h"        // for AccelDriver (aka sensor for acceleration). 

#include "AdcDriver.h"          // for AdcDriver. 
#include "I2CDriver.h"          // for I2CDriver. 

#include "Adc.h"                // for Adc. 
#include "I2C.h"                // for I2C. 

#include "filterconfig.h"       // for filter. 

/*****************************************************
 * CPU registers. 
 *****************************************************/

#include "adc1registers.hpp"    // for ADC registers. 
#include "i2c1registers.hpp"    // for I2C registers. 

/*****************************************************
 * Members definition. 
 *****************************************************/

inline Adc<ADC1> adc; 
inline I2C<I2C1> i2c; 

inline AdcDriver adcDriver(adc); 
inline I2CDriver i2cDriver(i2c); 

inline TempSensor tempSensor(adcDriver); 
inline AccelDriver accelDriver(i2cDriver); 

inline Temperature temperature(tempSensor, TemperatureFilter);
inline Acceleration acceleration(accelDriver, AccelXFilter, AccelYFilter, AccelZFilter); 


#endif  // _MEASURECONFIG_H