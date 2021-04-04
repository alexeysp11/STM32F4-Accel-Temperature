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
 * @param temp
 * @param accel
 */
void MeasureTask::MeasureTask(IVariableTemp& temp, IVariableAccel& accel) 
{

}

/**
 * @return void
 */
void MeasureTask::Execute() 
{
    while (true)
    {
        /* Invoke `OsWrapper::IThread::Sleep()` that makes a delay that is 
        equal to a value of timeout between events. */
        Sleep( std::chrono::milliseconds(50ms) );
    }
}

/**
 * @return float[]
 */
float[] MeasureTask::GetData() 
{
    return null;
}