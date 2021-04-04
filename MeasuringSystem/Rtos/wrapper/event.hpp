/*******************************************************************************
* Filename  	: event.hpp
* 
* Details   	: Event class is used to enable one or multiple tasks to wait 
*                 for a particular event to occur. 
* 
* The tasks can be kept suspended until the event is set by another task, 
* a software timer, or an interrupt handler.  
* 
* An event can be, for example, the change of an input signal, the expiration  
* of a timer, a key press, the reception of a character, or a complete command. 
* 
* Typical usage of event is activate a task from interrupt by an event object. 
*
*******************************************************************************/

#ifndef EVENT_HPP
#define EVENT_HPP

// For tEvent
#include "rtosdefs.hpp"       // for tTime. 
#include "rtoswrapper.hpp"    // for RtosWrapper. 
#include "eventmode.hpp"      // for EventMode. 


namespace OsWrapper
{
  constexpr tTime waitForEver = 0;
  constexpr tEventBits defaultMask = {0b11111111};
  
  /*
  * Implements waiting for an event or timout and notifying tasks about
  * that an event has been occured. 
  */
  class Event
  {
  public:
    __forceinline explicit Event(const std::chrono::milliseconds delay, const tEventBits maskBits) :
        timeOut{(std::chrono::duration_cast<TicksPerSecond>(delay)).count()},
        mask{maskBits}
    {
      handle = RtosWrapper::wCreateEvent(event);
    }

    __forceinline ~Event()
    {
      RtosWrapper::wDeleteEvent(handle);
    }

    /*
    * Summary: resumes tasks which are waiting at the event object. 
    */
    __forceinline void Signal()
    {
      RtosWrapper::wSignalEvent(handle, mask);
    }

    /*
    * Summary: invokes the function `RtosWrapper::wWaitEvent()` that waits for 
    * an event and suspends the task for a specified time or until the event 
    * has been signaled. 
    * 
    * Returns: set of bits. 
    * 
    * By default time delay is equal to 1000 ms (as a private variable of 
    * `Event` class). 
    */
    __forceinline tEventBits Wait(const EventMode mode = EventMode::waitAnyBits,
                                  const tEventBits maskBits = defaultMask) const
    {
      // By default time delay is equal to 1000 ms (as `timeOut` variable). 
      return RtosWrapper::wWaitEvent(handle, maskBits, timeOut, mode);
    }

    /*
    * Sets a value of delay. 
    */
    __forceinline void SetTimeout(std::chrono::milliseconds delay)
    {     
      timeOut = (std::chrono::duration_cast<TicksPerSecond>(delay)).count();
    }

    /*
    * Gets a value of delay. 
    */
    __forceinline tTime GetTimeout()
    {     
      return timeOut;
    }

    __forceinline void SetMaskBits(tEventBits maskBits)
    {
      mask = maskBits;
    }

  private:
    tEventHandle handle{0};
    tEvent event;
    tTime timeOut = 1000;
    tEventBits mask{defaultMask};
  };
};

#endif // EVENT_HPP
