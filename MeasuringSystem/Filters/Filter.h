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
    float Filter(float values) override;
};

#endif //_FILTER_H