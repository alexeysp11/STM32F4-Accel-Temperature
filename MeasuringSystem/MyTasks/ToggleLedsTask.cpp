/*******************************************************************************
* Filename  	: ToggleLedsTask.cpp
* 
* Details   	: Implementation of a task for toggling LEDs. 
*
*******************************************************************************/

#include "ToggleLedsTask.hpp"   // for ToggleLedsTask. 

/*
* Summary: executes a task `ToggleLedsTask`.
* Sleep some amount of time until an event occurs (when desired delay has 
* passed and mask is equal to 0) and then toggle required LEDs. 
* 
* Parameters: No. 
*/ 
void ToggleLedsTask::Execute()
{
  // Set mode `LedsModeInsideOutside` that implements toggling LEDs 2 and 3. 
  ledsCntr.SetMode(4U);         
  
  for(;;)
  {
    // Wait the end of event (mask will be equal to 0) and do nothing. 
    if (event.Wait() != 0); 
    
    /* Invoke `Update()` method of an instance of `LedsController` class
    that was passed to the constructor of this class as a parameter. */ 
    ledsCntr.Update();
  }
}

