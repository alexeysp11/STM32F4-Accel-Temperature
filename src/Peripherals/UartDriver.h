/**
 * Project Stm32Project
 */


#ifndef _UARTDRIVER_H
#define _UARTDRIVER_H

#include <cstdint>              // for uint8_t. 
#include <cstddef>              // for std::size_t. 
#include <cassert>              // for assert. 
#include <array>                // for array (for storing data in buffer). 

/**
 * UartDriver implementation
 */


template<typename TUsart>
class UartDriver 
{
public: 
    /**
     * @param data
     * @return void
     */
    void SendMessage(char* data, std::size_t overallSize)
    {
        assert(overallSize <= size); 
        std::memcpy(buffer.data(), data, size);
        size = overallSize;
        i = 0U;
        
        TUsart::WriteByte(buffer[i++]); 
        TUsart::TransmitEnable();
        TUsart::InterruptsEnable(); 
    }
    
    /**
     * @return void
     */
    void OnNextByteTransmit()
    {
        TUsart::WriteByte(buffer[i++]);    
        if (i >= size)
        {
            TUsart::TransmitDisable();
            TUsart::InterruptsDisable();
            i = 0U;
        }
    }
private: 
    std::size_t i = 0U;
    std::size_t size = 24U; 
    std::array<char, 24U> buffer;
};

#endif //_UARTDRIVER_H