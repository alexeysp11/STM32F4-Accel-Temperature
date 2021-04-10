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
    
    union {
        float float_variable;
        char byte_array[4];
    } value;

    /**
     * @param reg
     * @param checksum 
     */
    void AddChecksumToHeader(char reg, char checksum); 
};

#endif //_TRANSMISSIONMANAGER_H