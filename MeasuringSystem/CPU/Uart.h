/**
 * Project Stm32Project
 */


#ifndef _UART_H
#define _UART_H

/**
 * Uart implementation
 */


template<typename Port>
class Uart 
{
public: 
    /**
     * @param byte
     * @return void
     */
    void WriteByte(uint8_t byte)
    {
        return; 
    }
    
    /**
     * @return void
     */
    void InterruptsEnable()
    {
        return; 
    }
    
    /**
     * @return void
     */
    void InterruptsDisable()
    {
        return; 
    }
    
    /**
     * @return void
     */
    void TransmitEnable()
    {
        return; 
    }
    
    /**
     * @return void
     */
    void TransmitDisable()
    {
        return; 
    }
    
    /**
     * @return bool
     */    
    bool IsTransferRegisterEmpty()
    {
        return false; 
    }
    
    /**
     * @return bool
     */    
    bool IsInterruptEnabled()
    {
        return false; 
    }
};

#endif //_UART_H