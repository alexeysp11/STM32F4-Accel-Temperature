/*
* DESCRIPTION: This program toggles LEDs 2 and 3 every 1000 ms and handles 
* a button (checks every 100 ms if a button is pressed). 
* If a button is pressed, then toggle LED 1. 
* 
* Assign events and tasks for button handling and LEDs toggling. 
* Then in the main function create threads and start RTOS. 
*/ 

#include "HandleBtnTask.hpp"    // for HandleBtnTask.
#include "ToggleLedsTask.hpp"   // for ToggleLedsTask.

#include "rtos.hpp"             // for Rtos.
#include "mailbox.hpp"          // for Mailbox.
#include "event.hpp"            // for Event.

#include "rccregisters.hpp"     // for RCC.
#include <gpioaregisters.hpp>   // for GPIOA.
#include <gpiocregisters.hpp>   // for GPIOC.

#include "Application/Diagnostic/GlobalStatus.hpp"

std::uint32_t SystemCoreClock = 16'000'000U;

extern "C" {
  int __low_level_init(void)
  {
    //Switch on external 16 MHz oscillator.
    RCC::CR::HSION::On::Set();
    while (RCC::CR::HSIRDY::NotReady::IsSet());

    //Switch system clock on external oscillator. 
    RCC::CFGR::SW::Hsi::Set();
    while (!RCC::CFGR::SWS::Hsi::IsSet());
    
    //Switch on clock on PortA and PortC
    RCC::AHB1ENRPack<
        RCC::AHB1ENR::GPIOCEN::Enable,
        RCC::AHB1ENR::GPIOAEN::Enable
    >::Set();

    RCC::APB2ENR::SYSCFGEN::Enable::Set();

    //LED1 on PortA.5, set PortA.5 as output
    GPIOA::MODER::MODER5::Output::Set();

    /* LED2 on PortC.9, LED3 on PortC.8, LED4 on PortC.5 so set PortC.5,8,9 as output */
    GPIOC::MODERPack<
        GPIOC::MODER::MODER5::Output,
        GPIOC::MODER::MODER8::Output,
        GPIOC::MODER::MODER9::Output
    >::Set();

    return 1;
  }
}

// An event for button handling every 100 ms, mask equal to 1. 
OsWrapper::Event buttonEvent{100ms, 1};

// An event for toggling LEDs 2 and 3 every 1000 ms, mask equal to 1. 
OsWrapper::Event ledsEvent{1000ms, 1};

// A task for handling a button. 
HandleBtnTask btnTask(buttonEvent, UserButton::GetInstance(), LedsModeFirst::GetInstance());

// A task for toggling LEDs. 
ToggleLedsTask ledsTask(ledsEvent, LedsController::GetInstance());

/*
* In the main function create threads and start RTOS. 
*/ 
int main()
{
  // Create threads.
  using namespace OsWrapper;
  Rtos::CreateThread(btnTask, "btnTask", ThreadPriority::lowest);
  Rtos::CreateThread(ledsTask, "ledsTask");
  
  // Start RTOS. 
  Rtos::Start();

  return 0;
}
