/**
 * Project Stm32Project
 */


#ifndef _TRANSMISSIONMANAGER_H
#define _TRANSMISSIONMANAGER_H

#include "UartDriver.h"         // for UartDriver. 
#include "usartconfig.h"        // for Usart2. 

class TransmissionManager 
{
public: 
    /**
     * @param uartdriver Reference to UartDriver object. 
     */
    TransmissionManager(UartDriver<Usart2>& uartdriver) : m_uartdriver(uartdriver)
    {
    }
        
    /**
     * @param measuredData
     * @param overallSize 
     */
    void ConvertToByte(float* measuredData, size_t overallSize);
private: 
    UartDriver<Usart2>& m_uartdriver;
};

#endif //_TRANSMISSIONMANAGER_H