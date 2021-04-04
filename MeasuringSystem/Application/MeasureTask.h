/**
 * Project Stm32Project
 */


#ifndef _MEASURETASK_H
#define _MEASURETASK_H

class MeasureTask : public OsWrapper::Thread<static_cast<std::size_t>(OsWrapper::StackDepth::minimal)>
{
    friend class Singleton<LedsModeFirst>;
public: 
    void m_measuring;
    
    /**
     * @param temp
     * @param accel
     */
    void MeasureTask(IVariableTemp& temp, IVariableAccel& accel);
        
    void Execute() override;
        
    float[] GetData();
private: 
    IVariableTemp& m_temp;
    IVariable&[] variables;
};

#endif //_MEASURETASK_H