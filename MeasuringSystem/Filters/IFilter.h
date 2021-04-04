/**
 * Project Stm32Project
 */


#ifndef _IFILTER_H
#define _IFILTER_H

class IFilter 
{
public: 
    /**
     * @param value
     */
    virtual float Filter(float value) = 0;
private: 
    float oldValue;
};

#endif //_IFILTER_H