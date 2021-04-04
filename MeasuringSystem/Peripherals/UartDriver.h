/**
 * Project Stm32Project
 */


#ifndef _UARTDRIVER_H
#define _UARTDRIVER_H

class UartDriver 
{
public: 
    /**
     * @param uart
     */
    void UartDriver(Uart& uart);
        
    /**
     * @param data
     */
    void SendMessage(uint8_t[] data);
        
    void OnNextByteTransmit();
        
    uint16_t FloatToByte();
private: 
    Uart& m_uart;
    uint8_t[] buffer;
    size_t size = 16;
};

#endif //_UARTDRIVER_H