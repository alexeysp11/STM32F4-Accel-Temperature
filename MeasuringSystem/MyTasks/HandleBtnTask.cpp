/*******************************************************************************
* Filename  	: HandleBtnTask.cpp
* 
* Details   	: Implementation of Execute() of `HandleBtnTask` class. 
*
*******************************************************************************/

#include "HandleBtnTask.hpp"
#include <chrono>             // for std::chrono::milliseconds.

/*
* Summary: in an infinite `while` loop every 300 ms check if a button is pressed. 
* If a button was pressed, just invoke `Do()` method of an instance of 
* `LedsModeFirst` class and toggle required LED. 
* 
* TODO: try to toggle LED by notifying an instance of `OsWrapper::Event` 
* about that a button was pressed. 
*/
void HandleBtnTask::Execute()
{
  using namespace OsWrapper; 
  while(true) 
  {
    if (button.IsPressed())
    {
      /* Invoke `Do()` method of an instance of `LedsModeFirst` class
      that was passed to the constructor of this class as a parameter,
      and toggle LED 1. */ 
      ledsMode.Do(); 
    }

    /* Invoke `OsWrapper::IThread::Sleep()` that makes a delay that is 
    equal to a value of timeout between events. */
    Sleep( std::chrono::milliseconds( event.GetTimeout() ) );
  }
}