/**
 * Project Stm32Project
 */


#ifndef _USARTBASE_H
#define _USARTBASE_H

/**
 * UsartBase implementation
 */


template<typename Port , auto& aTransmitter>
class UsartBase 
{
public: 
    /**
     * @param byteToSend
     * @return void
     */
    static void WriteByte(char byteToSend)
    {
        Port::DR::Write(byteToSend);
    }
    
    /**
     * @return void
     */
    static void InterruptHandler()
    {
        if(IsTransferRegisterEmpty() &&  IsInterruptEnabled())
        {
            aTransmitter.OnNextByteTransmit();
        }
    }
    
    /**
     * @return void
     */
    static void InterruptsEnable()
    {
        Port::CR1::TXEIE::InterruptWhenTXE::Set(); 
    }
    
    /**
     * @return void
     */
    static void InterruptsDisable()
    {
        Port::CR1::TXEIE::InterruptInhibited::Set();
    }
    
    /**
     * @return void
     */
    static void TransmitEnable()
    {
        Port::CR1::TE::Enable::Set();
    }
    
    /**
     * @return void
     */
    static void TransmitDisable()
    {
        Port::CR1::RE::Disable::Set();
    }
    
    /**
     * @return bool
     */    
    static bool IsTransferRegisterEmpty()
    {
        return Port::SR::TXE::DataRegisterEmpty::IsSet();  
    }
    
    /**
     * @return bool
     */    
    static bool IsInterruptEnabled()
    {
        return Port::CR1::TXEIE::InterruptWhenTXE::IsSet();
    }
};

#endif //_USARTBASE_H