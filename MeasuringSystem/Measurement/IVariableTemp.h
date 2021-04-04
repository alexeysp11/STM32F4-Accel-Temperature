/**
 * Project Stm32Project
 */


#ifndef _IVARIABLETEMP_H
#define _IVARIABLETEMP_H

class IVariableTemp 
{
public: 
    virtual void Measure() = 0;
    virtual float GetValue() = 0;
private: 
    float value;
};

#endif //_IVARIABLETEMP_H