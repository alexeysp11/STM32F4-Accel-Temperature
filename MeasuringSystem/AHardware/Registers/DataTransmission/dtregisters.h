/**
 * Project Stm32Project
 * 
 * DESCRIPTION: Registers for data encoding while transmission. 
 */


#ifndef _DTREGISTERS_H
#define _DTREGISTERS_H

/*****************************************************
 * Values for registers configuration. 
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

inline char DT_BUFFER[24] = {
    DT_HEAD_TEMP,
    DT_DATA0_TEMP, 
    DT_DATA1_TEMP, 
    DT_DATA2_TEMP, 
    DT_DATA3_TEMP, 
    DT_CRC_TEMP, 

    DT_HEAD_ACCELX, 
    DT_DATA0_ACCELX, 
    DT_DATA1_ACCELX, 
    DT_DATA2_ACCELX, 
    DT_DATA3_ACCELX, 
    DT_CRC_ACCELX, 

    DT_HEAD_ACCELY, 
    DT_DATA0_ACCELY, 
    DT_DATA1_ACCELY, 
    DT_DATA2_ACCELY, 
    DT_DATA3_ACCELY, 
    DT_CRC_ACCELY, 

    DT_HEAD_ACCELZ, 
    DT_DATA0_ACCELZ, 
    DT_DATA1_ACCELZ, 
    DT_DATA2_ACCELZ, 
    DT_DATA3_ACCELZ, 
    DT_CRC_ACCELZ
}; 

#endif  // _DTREGISTERS_H