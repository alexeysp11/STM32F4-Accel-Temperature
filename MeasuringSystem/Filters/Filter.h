/**
 * Project Stm32Project
 */


#ifndef _FILTER_H
#define _FILTER_H

#include "IFilter.h"


class Filter: public IFilter 
{
public: 
    /**
     * @param values
     */
    float Calculate(float values) override;
private:
    float oldValue = 0.0f;
};

#endif //_FILTER_H