/**
 * Project Stm32Project
 */


#ifndef _SENDTASK_H
#define _SENDTASK_H

class SendTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
    friend class Singleton<LedsModeFirst>;
public: 
    /**
     * @param measuring
     * @param uartdriver
     */
    void SendTask(MeasureTask& measuring, UartDriver& uartdriver);
        
    void Execute() override;
private: 
    MeasureTask& m_measuring;
    UartDriver& m_uartdriver;
};

#endif //_SENDTASK_H