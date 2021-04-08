/*
* DESCRIPTION: . 
*/ 

/*****************************************************
 * Members for application level. 
 *****************************************************/

#include "MeasureTask.h"                // for MeasureTask. 
#include "SendTask.h"                   // for SendTask. 
#include "TransmissionManager.h"        // for TransmissionManager. 

/*****************************************************
 * Configuration files. 
 *****************************************************/

#include "usartconfig.h"        // for Usart2 and usartDriver. 
#include "measureconfig.h"      // for temperature and acceleration. 

/*****************************************************
 * RTOS members. 
 *****************************************************/

#include "rtos.hpp"             // for Rtos.
#include "mailbox.hpp"          // for Mailbox.
#include "event.hpp"            // for Event.

/*****************************************************
 * CPU registers. 
 *****************************************************/

#include "rccregisters.hpp"     // for RCC.
#include "extiregisters.hpp"    // for EXTI. 
#include <gpioaregisters.hpp>   // for GPIOA.
#include <gpiocregisters.hpp>   // for GPIOC.
#include "usart2registers.hpp"  // for USART2. 

#include "Application/Diagnostic/GlobalStatus.hpp"


/*****************************************************
 * Code. 
 *****************************************************/

// assign SystemCoreClock (from port.s file). 
std::uint32_t SystemCoreClock = 16'000'000U;    

constexpr std::uint32_t UartSpeed9600 = std::uint32_t(16'000'000U / 9'600U) ;

extern "C" {
  int __low_level_init(void)
  {
    //Switch on external 16 MHz oscillator.
    RCC::CR::HSION::On::Set();
    while (RCC::CR::HSIRDY::NotReady::IsSet());

    //Switch system clock on external oscillator. 
    RCC::CFGR::SW::Hsi::Set();
    while (!RCC::CFGR::SWS::Hsi::IsSet());
    
    //Switch on clock on PortA a
    RCC::AHB1ENR::GPIOAEN::Enable::Set() ;
    
    RCC::APB1ENRPack<
      RCC::APB1ENR::TIM2EN::Enable, 
      RCC::APB1ENR::USART2EN::Enable
      >::Set() ;
    
    GPIOA::MODERPack<
      GPIOA::MODER::MODER2::Alternate,    // Uart2 TX.
      GPIOA::MODER::MODER3::Alternate     // Uart2 RX.
      >::Set() ;
    
    GPIOA::AFRLPack <
      GPIOA::AFRL::AFRL2::Af7,            // Uart2 TX.
      GPIOA::AFRL::AFRL3::Af7             // Uart2 RX.
      >::Set() ;
  
    USART2::BRR::Write(UartSpeed9600) ;
    USART2::CR1::UE::Enable::Set() ;
    
    //NVIC::ISER1::Write(1<<6);

    return 1;
  }
}

// An event for sending measured data every 100 ms; mask equal to 1. 
//OsWrapper::Event sendEvent{100ms, 1};

// A task for measuring data. 
MeasureTask measureTask(temperature, acceleration);

// An object that provides functionality for data transmission. 
TransmissionManager tm(usartDriver);

// A task for for sending measured data. 
SendTask sendTask(measureTask, tm);

/*
* In the main function create threads and start RTOS. 
*/ 
int main()
{
  // Create threads.
  using namespace OsWrapper;
  Rtos::CreateThread(measureTask, "measureTask", ThreadPriority::lowest);
  Rtos::CreateThread(sendTask, "sendTask");
  
  // Start RTOS. 
  Rtos::Start();

  return 0;
}
