/**
 * Project Stm32Project
 */


#include "SendTask.h"

/**
 * SendTask implementation
 * 
 * Sends measured data to computer using USART. 
 * Is a task that executes every 100 ms.
 */


/**
 * @param measuring
 * @param uartdriver
 */
void SendTask::SendTask(MeasureTask& measuring, UartDriver& uartdriver) 
{

}

/**
 * @return void
 */
void SendTask::Execute() 
{
    while (true)
    {
        /* Invoke `OsWrapper::IThread::Sleep()` that makes a delay that is 
        equal to a value of timeout between events. */
        Sleep( std::chrono::milliseconds(100ms) );
    }
}