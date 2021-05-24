// ADXL345.h

#ifndef _ADXL345_H
#define _ADXL345_H

#include <cstdint>                      // for int types such as uint16_t.

/* ------- Register names ------- */

/* TWI instance ID. */
#define TWI_INSTANCE_ID     	0

#define ADXL345_ADDRESS         0x53

/******************************************
* ADXL345 registers adresses. 
******************************************/ 

#define ADXL345_DEVID           0x00
#define ADXL345_RESERVED1       0x01
#define ADXL345_THRESH_TAP      0x1d
#define ADXL345_OFSX            0x1e
#define ADXL345_OFSY            0x1f
#define ADXL345_OFSZ            0x20
#define ADXL345_DUR             0x21
#define ADXL345_LATENT          0x22
#define ADXL345_WINDOW          0x23
#define ADXL345_THRESH_ACT      0x24
#define ADXL345_THRESH_INACT    0x25
#define ADXL345_TIME_INACT      0x26
#define ADXL345_ACT_INACT_CTL   0x27
#define ADXL345_THRESH_FF       0x28
#define ADXL345_TIME_FF         0x29
#define ADXL345_TAP_AXES        0x2a
#define ADXL345_ACT_TAP_STATUS  0x2b
#define ADXL345_BW_RATE         0x2c
#define ADXL345_POWER_CTL       0x2d
#define ADXL345_INT_ENABLE      0x2e
#define ADXL345_INT_MAP         0x2f
#define ADXL345_INT_SOURCE      0x30
#define ADXL345_DATA_FORMAT     0x31
#define ADXL345_DATAX0          0x32
#define ADXL345_DATAX1          0x33
#define ADXL345_DATAY0          0x34
#define ADXL345_DATAY1          0x35
#define ADXL345_DATAZ0          0x36
#define ADXL345_DATAZ1          0x37
#define ADXL345_FIFO_CTL        0x38
#define ADXL345_FIFO_STATUS     0x39

/******************************************
* ADXL345 data rates (bandwidth, Hz). 
******************************************/ 

#define ADXL345_BW_1600 0xF // 1111
#define ADXL345_BW_800  0xE // 1110
#define ADXL345_BW_400  0xD // 1101  
#define ADXL345_BW_200  0xC // 1100
#define ADXL345_BW_100  0xB // 1011  
#define ADXL345_BW_50   0xA // 1010 
#define ADXL345_BW_25   0x9 // 1001 
#define ADXL345_BW_12   0x8 // 1000 
#define ADXL345_BW_6    0x7 // 0111
#define ADXL345_BW_3    0x6 // 0110

/* ------- ADXL345 data ------- */

inline std::uint16_t ADXL345_ACCELX_UINT16; 
inline std::uint16_t ADXL345_ACCELY_UINT16; 
inline std::uint16_t ADXL345_ACCELZ_UINT16; 

inline float ADXL345_ACCELX;  
inline float ADXL345_ACCELY;  
inline float ADXL345_ACCELZ;  

inline float* ADXL345_ACCEL_DATA[3] = {
    &ADXL345_ACCELX,
    &ADXL345_ACCELY,
    &ADXL345_ACCELZ
}; 

#endif //_ADXL345_H
