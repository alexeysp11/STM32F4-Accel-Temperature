# Data Transmission 

This file contains description of that how to configure registers in `TransmissionManager` class for creating packets for data sending via **USART** (in **MeasuringSystem**) and how to decode received bytes (in **Simulation3d**). 

Read [here](UartPacket.md) to get information on how packets for data transmission look like (header byte **DT_HEAD**, 4 data bytes **DT_DATA[0:3]**, and CRC byte **DT_CRC** for *3-axis accelerometer* and *temperature sensor*). 

## MeasuringSystem

In the file `dtregisters.h` (relative path: `MeasuringSystem/AHardware/Registers/DataTransmission`) you can assign values for setting required bits into data transmission registers **DT**: 
```C
/*****************************************************
 * Values for registers configuration (HEAD register). 
 *****************************************************/        

#define DT_RESET_BYTE       0x00

#define DT_SENSOR_TEMP      0b00000000
#define DT_SENSOR_ACCEL     0b10000000

#define DT_ACCELX           0b00100000
#define DT_ACCELY           0b00010000
#define DT_ACCELZ           0b00001000
#define DT_TEMP             0b00000100

#define DT_CHECKSUM_0       0b00000000
#define DT_CHECKSUM_1       0b00000001
#define DT_CHECKSUM_2       0b00000010
#define DT_CHECKSUM_3       0b00000011

/*****************************************************
 * Registers for storing values. 
 *****************************************************/   

inline char DT_HEAD_TEMP; 
inline char DT_DATA0_TEMP; 
inline char DT_DATA1_TEMP; 
inline char DT_DATA2_TEMP; 
inline char DT_DATA3_TEMP; 
inline char DT_CRC_TEMP;

inline char DT_HEAD_ACCELX; 
inline char DT_DATA0_ACCELX; 
inline char DT_DATA1_ACCELX; 
inline char DT_DATA2_ACCELX; 
inline char DT_DATA3_ACCELX; 
inline char DT_CRC_ACCELX;

inline char DT_HEAD_ACCELY; 
inline char DT_DATA0_ACCELY; 
inline char DT_DATA1_ACCELY; 
inline char DT_DATA2_ACCELY; 
inline char DT_DATA3_ACCELY; 
inline char DT_CRC_ACCELY;

inline char DT_HEAD_ACCELZ; 
inline char DT_DATA0_ACCELZ; 
inline char DT_DATA1_ACCELZ; 
inline char DT_DATA2_ACCELZ; 
inline char DT_DATA3_ACCELZ; 
inline char DT_CRC_ACCELZ;

inline char* DT_BUFFER[24] = {
    &DT_HEAD_TEMP,
    &DT_DATA0_TEMP, 
    &DT_DATA1_TEMP, 
    &DT_DATA2_TEMP, 
    &DT_DATA3_TEMP, 
    &DT_CRC_TEMP, 

    &DT_HEAD_ACCELX, 
    &DT_DATA0_ACCELX, 
    &DT_DATA1_ACCELX, 
    &DT_DATA2_ACCELX, 
    &DT_DATA3_ACCELX, 
    &DT_CRC_ACCELX, 

    &DT_HEAD_ACCELY, 
    &DT_DATA0_ACCELY, 
    &DT_DATA1_ACCELY, 
    &DT_DATA2_ACCELY, 
    &DT_DATA3_ACCELY, 
    &DT_CRC_ACCELY, 

    &DT_HEAD_ACCELZ, 
    &DT_DATA0_ACCELZ, 
    &DT_DATA1_ACCELZ, 
    &DT_DATA2_ACCELZ, 
    &DT_DATA3_ACCELZ, 
    &DT_CRC_ACCELZ
}; 
```

Suppose you need to get 4 floating values (by taking pointer on first element of the array of 4 floating values and size of the array as parameters) and pass them via **USART**. 

Because of that `DT_BUFFER` is an array of pointers to **DT_HEAD**, **DT_DATA[0:3]** and **DT_CRC**, you can simply put values into these register and then just pass **DT_BUFFER** as shown below. 
```C++
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
        value.float_variable = *(measuredData + i);      // Get measured data. 
        
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
            DT_DATA0_TEMP = value.byte_array[0];
            DT_DATA1_TEMP = value.byte_array[1];
            DT_DATA2_TEMP = value.byte_array[2];
            DT_DATA3_TEMP = value.byte_array[3];

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
            DT_DATA0_ACCELX = value.byte_array[0];
            DT_DATA1_ACCELX = value.byte_array[1];
            DT_DATA2_ACCELX = value.byte_array[2];
            DT_DATA3_ACCELX = value.byte_array[3];

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
            DT_DATA0_ACCELY = value.byte_array[0];
            DT_DATA1_ACCELY = value.byte_array[1];
            DT_DATA2_ACCELY = value.byte_array[2];
            DT_DATA3_ACCELY = value.byte_array[3];

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
            DT_DATA0_ACCELZ = value.byte_array[0];
            DT_DATA1_ACCELZ = value.byte_array[1];
            DT_DATA2_ACCELZ = value.byte_array[2];
            DT_DATA3_ACCELZ = value.byte_array[3];

            // Calculate CRC for measured data. 
            DT_CRC_ACCELZ = (DT_DATA0_ACCELZ + DT_DATA1_ACCELZ + 
                            DT_DATA2_ACCELZ + DT_DATA3_ACCELZ) / 4; 
        }
    }
    
    /* Pass a size of DT_BUFFER as a parameter explicitly (in this case it's 
    equal to 24) because if you try to pass it using sizeof(DT_BUFFER) or 
    something else, the progam will stuck in DummyModule::handler() in an 
    infinite for(;;) loop.  */
    m_uartdriver.SendMessage(*DT_BUFFER, 24); 
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
```

You can invoke `TransmissionManager::ConvertToByte()` the following way: 
```C++
void SendTask::Execute() 
{
    while (true)
    {
        /* Invoke `OsWrapper::IThread::Sleep()` that makes a delay that is 
        equal to a value of timeout between events. */
        Sleep( std::chrono::milliseconds(100ms) );
          
        // Get measured values from MeasureTask. 
        float* data = m_measuring.GetData();
        
        // Invoke UartDriver class and pass references to measured data.
        m_tm.ConvertToByte(data, sizeof(*data));
    }
}
```

## Simulation3d

<!--
For Simulation3d (**WPF**): 
```C#

```

For MeasuringSystem (): 
```C#

```
-->
