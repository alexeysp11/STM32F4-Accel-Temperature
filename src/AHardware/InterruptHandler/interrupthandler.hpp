//
// Created by Sergey on 21.11.2019.
//

#ifndef REGISTERS_INTERRUPTHANDLER_HPP
#define REGISTERS_INTERRUPTHANDLER_HPP

class InterruptHandler {
  public:
    static void DummyHandler() { for(;;) {} }
    static void Timer2Handler()
    {
    }
};

#endif //REGISTERS_INTERRUPTHANDLER_HPP
