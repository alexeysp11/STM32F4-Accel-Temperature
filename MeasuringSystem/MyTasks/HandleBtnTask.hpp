/*******************************************************************************
* Filename  	: HandleBtnTask.hpp
* 
* Details   	: Declaration of a task `HandleBtnTask` for getting if a button  
*                 was pressed. 
* 
* The class `HandleBtnTask` inherits `Thread` class from a file `thread.hpp`. 
*  
*******************************************************************************/

#ifndef _HANDLEBTNTASK_HPP_
#define _HANDLEBTNTASK_HPP_

#include "thread.hpp"
#include "userbutton.hpp"       // for UserButton. 
#include "event.hpp"
#include "rtosdefs.hpp"
#include "ledsmodes.hpp"        // for LedsModeFirst. 

#include <array>

/*
* Overrides `Execute()` method and inherits `Thread` class (file "thread.hpp"). 
*
* Size of a stack is minimal (128 bytes). 
*/
class HandleBtnTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
  friend class Singleton<LedsModeFirst>;
public:
  virtual void Execute() override;
  HandleBtnTask(OsWrapper::Event& event, UserButton& button, 
                LedsModeFirst& mode) : event(event), button(button), ledsMode(mode)
  {
  }
private:
  OsWrapper::Event& event;
  UserButton& button;
  LedsModeFirst& ledsMode; 
};

#endif // _HANDLEBTNTASK_HPP_
