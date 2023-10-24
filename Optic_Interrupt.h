#ifndef OPTIC_INTERRUPT_H
#define OPTIC_INTERRUPT_H
#define Pin_LED 4
#define Pin_OIntp 2
#define openings 8


class Optic_Interrupt
{
    public:
        Optic_Interrupt(bool * val){ led_on=val; };
        virtual ~Optic_Interrupt();
        void setup_OI();

    protected:
        void start_OI();
        void stop_OI();
        bool * led_on;//freq and counter class
        
    private:
        
};

#endif // OPTIC_INTERRUPT_H
