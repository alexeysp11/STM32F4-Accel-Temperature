/**
 * Project Stm32Project
 */


#ifndef _MEASURETASK_H
#define _MEASURETASK_H

/*****************************************************
 * Members for application level. 
 *****************************************************/

#include "IVariableTemp.h"      // for IVariableTemp. 
#include "IVariableAccel.h"     // for IVariableAccel. 

/*****************************************************
 * RTOS members. 
 *****************************************************/

#include "thread.hpp"           // for OsWrapper::Thread.
#include "event.hpp"
#include "rtosdefs.hpp"

/*****************************************************
 * Additional includes. 
 *****************************************************/

#include <cstdint>              // for uint8_t. 
#include <cstddef>              // for std::size_t. 
#include <array>                // for array (for storing data in buffer). 


/*****************************************************
 * MeasureTask declaration. 
 *****************************************************/

class MeasureTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
public: 
    /**
     * @param temp
     * @param accel
     */
    MeasureTask(IVariableTemp& temp, IVariableAccel& accel) : m_temp(temp), 
                                                              m_accel(accel)
    {
    }
        
    void Execute() override;
        
    float* GetData();
private: 
    IVariableTemp& m_temp;
    IVariableAccel& m_accel; 
    std::size_t size = 4U; 
    float buffer[4];
};

#endif //_MEASURETASK_H