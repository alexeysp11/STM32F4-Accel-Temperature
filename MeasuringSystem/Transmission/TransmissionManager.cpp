/**
 * Project Stm32Project
 */


/*****************************************************
 * Application level includes. 
 *****************************************************/

#include "TransmissionManager.h"
#include "dtregisters.h"            // for DT registers (for packets encoding). 

/*****************************************************
 * Additional includes. 
 *****************************************************/

#include <cstdlib>              // for malloc. 
#include <math.h>               // for fmodf. 
#include <iostream>             // for std::cout. 

/**
 * TransmissionManager implementation
 */


/**
 * @param measuredData Array of measured data that passed by poiner and  
 * needs to be sent (0th index is temperature, 1st index is acceleration 
 * along X axis, 2nd index is acceleration along Y axis, 3rd index is
 * acceleration along Z axis).
 * @param overallSize Size of an array of data that need to be sent. 
 * @return void
 */
void TransmissionManager::ConvertToByte(float* measuredData, size_t overallSize) 
{
    for (int i = 0; i < overallSize; i++)
    {
        float value = *(measuredData + i);      // Get measured data. 
        
        if (i == 0)
        {
            // Configure data from temperature sensor. 
            DT_HEAD_TEMP &= DT_RESET_BYTE;      // Reset header byte for temperature sensor. 
            DT_HEAD_TEMP |= DT_SENSOR_TEMP;     // Encode temperature sensor. 
            DT_HEAD_TEMP |= DT_TEMP;            // Encode unit of temperature. 
            
            // Checksum for HEAD byte. 
            char checksum = DT_HEAD_TEMP % 64;  // This should vary from 0 to 3. 
            AddChecksumToHeader(DT_HEAD_TEMP, checksum);

            // Write measured data into DT_DATA register. 

            // Calculate CRC for measured data. 
            DT_CRC_TEMP = (DT_DATA0_TEMP + DT_DATA1_TEMP + 
                           DT_DATA2_TEMP + DT_DATA3_TEMP) / 4; 
        }
        else if (i == 1)
        {
            // Configure data from accelerometer (X axis). 
            DT_HEAD_ACCELX &= DT_RESET_BYTE;    // Reset header byte for accelerometer (X axis).
            DT_HEAD_ACCELX |= DT_SENSOR_ACCEL;  // Encode accelerometer. 
            DT_HEAD_ACCELX |= DT_ACCELX;        // Encode axis of accelerometer measurement. 
            
            // Checksum for HEAD byte. 
            char checksum = DT_HEAD_ACCELX % 64;  // This should vary from 0 to 3.
            AddChecksumToHeader(DT_HEAD_ACCELX, checksum);

            // Write measured data into DT_DATA register. 

            // Calculate CRC for measured data. 
            DT_CRC_ACCELX = (DT_DATA0_ACCELX + DT_DATA1_ACCELX + 
                            DT_DATA2_ACCELX + DT_DATA3_ACCELX) / 4; 
        }
        else if (i == 2)
        {
            // Configure data from accelerometer (Y axis). 
            DT_HEAD_ACCELY &= DT_RESET_BYTE;    // Reset header byte for accelerometer (Y axis).
            DT_HEAD_ACCELY |= DT_SENSOR_ACCEL;  // Encode accelerometer. 
            DT_HEAD_ACCELY |= DT_ACCELY;        // Encode axis of accelerometer measurement. 
            
            // Checksum for HEAD byte. 
            char checksum = DT_HEAD_ACCELY % 64;  // This should vary from 0 to 3.
            AddChecksumToHeader(DT_HEAD_ACCELY, checksum);

            // Write measured data into DT_DATA register. 

            // Calculate CRC for measured data. 
            DT_CRC_ACCELY = (DT_DATA0_ACCELY + DT_DATA1_ACCELY + 
                            DT_DATA2_ACCELY + DT_DATA3_ACCELY) / 4; 
        }
        else if (i == 3)
        {
            // Configure data from accelerometer (Z axis). 
            DT_HEAD_ACCELZ &= DT_RESET_BYTE;    // Reset header byte for accelerometer (Z axis).
            DT_HEAD_ACCELZ |= DT_SENSOR_ACCEL;  // Encode accelerometer. 
            DT_HEAD_ACCELZ |= DT_ACCELZ;        // Encode axis of accelerometer measurement. 
            
            // Checksum for HEAD byte. 
            char checksum = DT_HEAD_ACCELZ % 64;  // This should vary from 0 to 3.
            AddChecksumToHeader(DT_HEAD_ACCELZ, checksum);
            
            // Write measured data into DT_DATA register. 

            // Calculate CRC for measured data. 
            DT_CRC_ACCELZ = (DT_DATA0_ACCELZ + DT_DATA1_ACCELZ + 
                            DT_DATA2_ACCELZ + DT_DATA3_ACCELZ) / 4; 
        }
    }

    m_uartdriver.SendMessage(DT_BUFFER, sizeof(DT_BUFFER)); 
}

/**
 * @param reg
 * @param checksum 
 */
void TransmissionManager::AddChecksumToHeader(char reg, char checksum) 
{
    if (checksum == 0)  
    {
        reg |= DT_CHECKSUM_0; 
    }
    else if (checksum == 1)
    {
        reg |= DT_CHECKSUM_1; 
    }
    else if (checksum == 2)
    {
        reg |= DT_CHECKSUM_2; 
    }
    else if (checksum == 3)
    {
        reg |= DT_CHECKSUM_3; 
    }
}