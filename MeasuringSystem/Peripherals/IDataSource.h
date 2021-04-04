/**
 * Project Stm32Project
 */


#ifndef _IDATASOURCE_H
#define _IDATASOURCE_H

class IDataSource 
{
public: 
    virtual float Get() = 0;
};

#endif //_IDATASOURCE_H