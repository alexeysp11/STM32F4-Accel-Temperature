/**
 * Project Stm32Project
 */


/*****************************************************
 * Application level includes. 
 *****************************************************/

#include "TransmissionManager.h"

/*****************************************************
 * Additional includes. 
 *****************************************************/

#include <cstdlib>              // for malloc. 
#include <math.h>               // for fmodf. 

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
    char* buffer = (char*)std::malloc( sizeof(char) * overallSize * 4 ); 
    
    if( buffer == NULL )
    {
        // Do nothing. 
    }
    else
    {
        // Get data stored in `measuredData`. 
        for (int i = 0; i < overallSize; i++) 
        {
            // Get which sensor measured data. 
            if (i == 0)
            {
                buffer[0] = 'T';    // Encode letter 'T' (that stand for temperature sensor).
            }
            else if (i == 1)
            {
                buffer[0] = 'A';    // Encode letter 'A' (that stand for accelerometer).
            }
            else if (i == 2)
            {
                buffer[0] = 'A';    // Encode letter 'A' (that stand for accelerometer).
            }
            else if (i == 3)
            {
                buffer[0] = 'A';    // Encode letter 'A' (that stand for accelerometer).
            }
            
            float value = *(measuredData + i);          // Get measured data. 

            buffer[1] = (char)(value / 256);            // Store first byte of data.
            buffer[2] = (char)( fmodf(value, 256) );    // Store second byte of data.

            /*
            NOTE: you can recover float value from two bytes by using: 
            initialValue = (buffer[0] * 256US) + buffer[1]; 
            */
            
            // Calculate CRC. 
            buffer[3] = (buffer[0] + buffer[1] + buffer[2]) / 3; 
        }

        m_uartdriver.SendMessage(buffer, sizeof(buffer)); 

        free(buffer);                   // Clear buffer. 
    }
}