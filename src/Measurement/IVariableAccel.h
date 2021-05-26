/**
 * Project Stm32Project
 */


#ifndef _IVARIABLEACCEL_H
#define _IVARIABLEACCEL_H

class IVariableAccel 
{
public: 
    virtual void Measure() = 0;
    virtual float GetValue() = 0;
private: 
    float* value;
};

#endif //_IVARIABLEACCEL_H