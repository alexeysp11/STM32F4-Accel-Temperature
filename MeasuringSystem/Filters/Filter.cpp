/**
 * Project Stm32Project
 */


#include "Filter.h"

/**
 * Filter implementation
 */


/**
 * @param values
 * @return float
 */
float Filter::Calculate(float values) 
{
    oldValue = (values + oldValue) / 2;
    return oldValue;
}