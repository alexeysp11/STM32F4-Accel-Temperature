/**
 * Project Stm32Project
 */


#include "MeasureTask.h"

/**
 * MeasureTask implementation
 * 
 * Measures temperature and acceleration vector with respect to each of 3 axis. 
 * Invokes every 50 ms.
 * After measured parameters were received, these measured parameters should be 
 * written into fields of some static class or structure that represents circuit 
 * board states.
 */


/**
 * @return void
 */
void MeasureTask::Execute() 
{
    while (true)
    {
        // Measure temperature. 
        m_temp.Measure(); 

        // Measure acceleration. 
        m_accel.Measure(); 
        
        /* Invoke `OsWrapper::IThread::Sleep()` that makes a delay that is 
        equal to a value of timeout between events. */
        Sleep( std::chrono::milliseconds(50ms) );
    }
}

/**
 * @return float*
 */
float* MeasureTask::GetData() 
{
    // Get measured data data. 
    buffer[0] = m_temp.GetValue();       // Get data from temperature sensor. 
    buffer[1] = m_accel.GetValue(); 
    buffer[2] = m_accel.GetValue(); 
    buffer[3] = m_accel.GetValue(); 
    
    return &buffer[0];
}