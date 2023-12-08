#ifndef RPM_H
#define RPM_H

#include "HardwareSerial.h"
#include "Optic_Interrupt.h"

class RPM: public Optic_Interrupt
{
    public:
        RPM(bool * val);
        virtual ~RPM();

        unsigned int GetFreqMeas() { return freq_meas; }
        float getFrontFreq(){return frontfreq;};
        float getBackFreq(){return backfreq;};
        void start_freq_meas();
        void stop_freq_meas(bool val=false);
        void main_freq(HardwareSerial * Serial);
        void IRS_CHANGE();

    protected:

    private:
        float backfreq;
        float frontfreq;
        unsigned int freqfrontCounter;
        unsigned int freqbackCounter;
        bool front_edge;//freq and counter class
        bool back_edge;//freq and counter class
        bool freq_meas;//freq and counter class
        unsigned long frontTimenew;//freq and counter class
        unsigned long frontTimeold;//freq and counter class
        unsigned long backTimenew;//freq and counter class
        unsigned long backTimeold;//freq and counter class
        unsigned long frontSum;
        unsigned long backSum;
};

#endif // RPM_H
