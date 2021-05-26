/**
 * Project Stm32Project
 */


#ifndef _I2C_H
#define _I2C_H

#include "ADXL345.h"                // for ADXL345.h. 

#include "i2c1registers.hpp"        // for I2C registers. 


/**
 * I2C implementation
 */

template<typename Port>
class I2C 
{
public: 
    /**
     * @return void
     */
    void Write(char device, char reg)
    {
        // Assert that master wants to write register address for ADXL345. 
        I2C1::CR1::STOP::Disable::Set();            // Disable stop bit.
        I2C1::CR1::START::Enable::Set();            // Send start bit. 
        
        // Wait until stop bit is sent. 
        while(I2C1::SR1::SB::Value0::IsSet()); 
        I2C1::SR1::Get();
        I2C1::SR2::Get();
        
        // Set address of ADXL345 and that master writes (first bit is 0).  
        I2C1::DR::Write((ADXL345_ADDRESS << 1)); 
        while(I2C1::SR1::ADDR::Value0::IsSet()); 
        I2C1::SR1::Get();
        I2C1::SR2::Get();
        
        // Write register address of ADXL345 (for example, DATAX0).
        I2C1::DR::Write(reg);
        while(!I2C1::SR1::TxE::Value1::IsSet());    // Wait until DR is empty 

        I2C1::CR1::START::Disable::Set();           // Disable start bit. 
    }

    /**
     * @return void
     */
    void Read(char device, std::uint16_t *var)
    {
        // Assert that master wants to write register address for ADXL345. 
        I2C1::CR1::STOP::Disable::Set();            // Disable stop bit.
        I2C1::CR1::START::Enable::Set();            // Send start bit. 
        
        // Wait until stop bit is sent. 
        while(I2C1::SR1::SB::Value0::IsSet());    
        
        // Set address of ADXL345 and that master reads (first bit is 1).  
        I2C1::DR::Write( (ADXL345_ADDRESS << 1) | 0x01 ); 
        while(I2C1::SR1::ADDR::Value0::IsSet()); 
        
        // Set ACK to low and POS to high 
        I2C1::CR1::ACK::NoAcknowledge::Set();
        I2C1::CR1::POS::NextByte::Set(); 
        
        // Clear ADDR 
        I2C1::SR1::Get();
        I2C1::SR2::Get();
        
        // wait until BTF=1
        while(I2C1::SR1::BTF::Value0::IsSet());
        
        I2C1::CR1::START::Disable::Set();           // Disable start bit. 
        I2C1::CR1::STOP::Enable::Set();             // Send stop bit. 
        
        // Read data from DATAX0 and DATAX1 of ADXL345. 
        *var = (std::uint16_t)I2C1::DR::Get(); 
        *var += (I2C1::DR::Get() << 8);
    }
};

#endif //_I2C_H