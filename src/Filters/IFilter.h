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
    virtual float Calculate(float value) = 0;
};

#endif //_IFILTER_H