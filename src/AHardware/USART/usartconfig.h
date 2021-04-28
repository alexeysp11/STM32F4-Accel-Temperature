/**
 * Project Stm32Project
 */


#ifndef _USARTCONFIG_H
#define _USARTCONFIG_H

#include "UsartBase.h"
#include "UartDriver.h"

#include "usart2registers.hpp"  // for USART2. 

class Usart2;

inline UartDriver<Usart2> usartDriver;

class Usart2: public UsartBase<USART2, usartDriver>
{
};

#endif  // _USARTCONFIG_H