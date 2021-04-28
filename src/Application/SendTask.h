/**
 * Project Stm32Project
 */


#ifndef _SENDTASK_H
#define _SENDTASK_H

#include "MeasureTask.h"            // for MeasureTask. 
#include "TransmissionManager.h"    // for TransmissionManager. 


class SendTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
public: 
    /**
     * @param measuring
     * @param tm
     */
    SendTask(MeasureTask& measuring, TransmissionManager& tm) : m_measuring(measuring), 
                                                                m_tm(tm)
    {
    }
        
    void Execute() override;
private: 
    MeasureTask& m_measuring;
    TransmissionManager& m_tm;
};

#endif //_SENDTASK_H