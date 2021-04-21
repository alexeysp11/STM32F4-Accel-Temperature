/**
 * Project Stm32Project
 */


#ifndef _MEASURECONFIG_H
#define _MEASURECONFIG_H

/*****************************************************
 * Includes for application. 
 *****************************************************/

#include "Temperature.h"        // for Temperature. 
#include "TempSensor.h"         // for TempSensor.  
#include "AdcDriver.h"          // for AdcDriver. 
#include "Adc.h"                // for Adc. 
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
inline AdcDriver adcDriver(adc); 
inline TempSensor tempSensor(adcDriver); 
inline Temperature temperature(tempSensor, filter);

#endif  // _MEASURECONFIG_H