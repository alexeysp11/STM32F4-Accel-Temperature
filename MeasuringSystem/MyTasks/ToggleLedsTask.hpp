/*******************************************************************************
* Filename  	: ToggleLedsTask.hpp
* 
* Details   	: Declaration of a task for toggling LEDs. 
*
*******************************************************************************/

#ifndef _TOGGLELEDSTASK_HPP_
#define _TOGGLELEDSTASK_HPP_

#include "userbutton.hpp"       // for Button.
#include "event.hpp"            // for Event. 
#include "ledscontroller.hpp"   // for LedsController.
#include "thread.hpp"           // for OsWrapper::Thread.

#include <array>

/*
* Toggles LEDs 2 and 3. 
* 
* Constructor of `ToggleLedsTask` gets created event for LEDs toggling and 
* a reference to the instance of `LedsController` as parameters. 
*/ 
class ToggleLedsTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
public:
  virtual void Execute() override;

  ToggleLedsTask(OsWrapper::Event& event, LedsController& controller) : event(event), ledsCntr(controller)
  {
  }
  
private:
  OsWrapper::Event& event;
  LedsController& ledsCntr;
};

#endif // _TOGGLELEDSTASK_HPP_
