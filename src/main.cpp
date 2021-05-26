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

#include "rccregisters.hpp"             // for RCC.
#include "nvicregisters.hpp"            // for NVIC. 
#include <gpioaregisters.hpp>           // for GPIOA (USART).
#include "gpiobregisters.hpp"           // for GPIOB (PB8 and PB9).
#include <gpiocregisters.hpp>           // for GPIOC.
#include "usart2registers.hpp"          // for USART2. 
#include "i2c1registers.hpp"            // for I2C1.
#include "adccommonregisters.hpp"       // for ADC1. 

#include "Application/Diagnostic/GlobalStatus.hpp"


/*****************************************************
 * Code. 
 *****************************************************/

// assign SystemCoreClock (from port.s file). 
std::uint32_t SystemCoreClock = 16'000'000U;    

constexpr std::uint32_t UartSpeed19200 = std::uint32_t(16'000'000U / 19'200U);

extern "C" {
  int __low_level_init(void)
  {
    //Switch on external 16 MHz oscillator.
    RCC::CR::HSION::On::Set();
    while (RCC::CR::HSIRDY::NotReady::IsSet());

    // Switch system clock on external oscillator. 
    RCC::CFGR::SW::Hsi::Set();
    while (!RCC::CFGR::SWS::Hsi::IsSet());

    /*****************************************************
     * USART2 configuration. 
     *****************************************************/
    
    // Switch on clock on PortA (for USART2). 
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
  
    USART2::BRR::Write(UartSpeed19200) ;
    USART2::CR1::UE::Enable::Set() ;
    
    NVIC::ISER1::Write(1<<6);

    /*****************************************************
     * ADC1 configuration. 
     *****************************************************/

    RCC::APB2ENR::ADC1EN::Enable::Set();
    ADC1::SQR3::SQ1::Channel18::Set();        // Select ADC1_IN16 or ADC1_IN18 input channel.
    ADC_Common::CCR::TSVREFE::Enable::Set();  // Set the TSVREFE bit in the ADC_CCR register to wake up the temperature sensor.
    ADC1::CR1::RES::Bits12::Set();
    ADC1::CR2::CONT::SingleConversion::Set();
    ADC1::CR2::EOCS::SingleConversion::Set();
    ADC1::SQR1::L::Conversions1::Set();
    ADC1::SMPR1::SMP18::Cycles84::Set();
    ADC1::CR2::ADON::Enable::Set();
    GPIOA::MODER::MODER0::Analog::Set();
    
    /******************************************
    * PB8 and PB9 configuration. 
    ******************************************/ 
    
    // Switch on clock on Port B. 
    RCC::AHB1ENR::GPIOBEN::Enable::Set();

    // Enable PB8 and PB9 for I2C1 as alternate. 
    GPIOB::MODERPack<
        GPIOB::MODER::MODER8::Alternate, 
        GPIOB::MODER::MODER9::Alternate  
        >::Set();
    
    // Set the alternate functions for pins 8 and 9. 
    GPIOB::AFRH::AFRH8::Af4::Set(); 
    GPIOB::AFRH::AFRH9::Af4::Set(); 

    // Type register open drain. 
    GPIOB::OTYPER::OT8::OutputOpenDrain::Set(); 
    GPIOB::OTYPER::OT9::OutputOpenDrain::Set(); 

    // Output speed register low. 
    GPIOB::OSPEEDR::OSPEEDR8::LowSpeed::Set(); 
    GPIOB::OSPEEDR::OSPEEDR9::LowSpeed::Set(); 

    // No internal pull up, pull down resistors. 
    GPIOB::PUPDR::PUPDR8::NoPullUpNoPullDown::Set(); 
    GPIOB::PUPDR::PUPDR9::NoPullUpNoPullDown::Set(); 
    
    /******************************************
    * I2C1 configuration. 
    ******************************************/ 
    
    // Peripheral clock enable register. 
    RCC::APB1ENR::I2C1EN::Enable::Set();    
    
    /* Program the peripheral input clock in I2C_CR2 Register in order 
    to generate correct timings. */
    I2C1::CR2::FREQ::Set(2U);                   // I2C1 clocking (2 MHz).
    
    /*  Configure the clock control registers. */
    I2C1::CCR::F_S::StandartMode::Set();        // Set Sm mode. 
    I2C1::CCR::CCRField::Set(100U);             // Set CCR in I2C_CCR (10 * T_SCLK). 
    
    /*  Configure the rise time register */ 
    // Maximum rise time in Fm/Sm mode (Master mode).
    I2C1::TRISE::TRISEField::Set(17U);
    
    /* Program the I2C_CR1 register to enable the peripheral. */ 
    I2C1::CR1::PE::Enable::Set();               // Enable peripheral. 
    
    // Set address of ADXL345. 
    I2C1::OAR1::ADD7::Set(ADXL345_ADDRESS);     // Set address of device ADXL345. 
    
    // Send stop bit. 
    I2C1::CR1::STOP::Enable::Set();  

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
