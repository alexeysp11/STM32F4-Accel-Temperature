/**
 * Project Stm32Project
 */


#ifndef _ACCELDRIVER_H
#define _ACCELDRIVER_H

class AccelDriver {
public: 
    /**
     * @param m_i2cDriver
     */
    void AccelDriver(I2CDriver& m_i2cDriver);
        
    float[] Get();
private: 
    IDataSource& m_ds;
};

#endif //_ACCELDRIVER_H