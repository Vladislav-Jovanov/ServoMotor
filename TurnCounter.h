#ifndef TURNCOUNTER_H
#define TURNCOUNTER_H
#include "Optic_Interrupt.h"
#include "HardwareSerial.h"

class TurnCounter: public Optic_Interrupt
{
    public:
        TurnCounter(bool * led_on, unsigned int val=10);
        virtual ~TurnCounter();
        
        
        unsigned int GetCounterStatus() { return counter_running; }
        unsigned int GetTotCounter() { return totCount; }
        unsigned int GetCurentCounter() { return currentCount; }
        void SetCounter(unsigned int val) { totCount = val; }
        void start_counter();
        void stop_counter(bool val);
        void main_counter(HardwareSerial * Serial);
        void IRS_CHANGE();

    protected:

    private:
        unsigned int totCount;
        unsigned int currentCount;
        unsigned int backCounter;
        bool backEdge;
        bool counter_running;//freq and counter class
};

#endif // TURNCOUNTER_H
