#include "RPM.h"
#include "HardwareSerial.h"
#include "Arduino.h"
#include "Optic_Interrupt.h"

RPM::RPM(bool * val):Optic_Interrupt(val)
{
    front_edge=false;
    back_edge=false;
    freq_meas=false;
}

RPM::~RPM()
{
    //dtor
}


void RPM::start_freq_meas(){
  if (!*led_on){
    start_OI();
  }
  frontSum=0;
  backSum=0;
  freqfrontCounter=0;
  freqbackCounter=0;
  freq_meas=true;
  frontTimenew=0;
  backTimenew=0;
}
void RPM::stop_freq_meas(bool val){
  if (!val){ 
    stop_OI();
  }
  freq_meas=false;
}




void RPM::main_freq(HardwareSerial * Serial){
  if (front_edge & freq_meas){
      freqfrontCounter++;
      if (!(freqfrontCounter % openings)){
         Serial->print("Front edgde frequency:");
         Serial->print(1e3/frontSum);
         Serial->println("Hz");
         frontfreq=1e3/frontSum;
         frontSum=0;
         freqfrontCounter=0;
      }
      frontTimeold=frontTimenew;
      frontTimenew=millis();
      frontSum+=frontTimenew-frontTimeold;
      front_edge=false;
  }
  if (back_edge & freq_meas){
      freqbackCounter++;
      if (!(freqbackCounter % openings)){
         Serial->print("Back edge frequency:");
         Serial->print(1e3/backSum);
         Serial->println("Hz");
         backfreq=1e3/backSum;
         backSum=0;
         freqbackCounter=0;
      }

      backTimeold=backTimenew;
      backTimenew=millis();
      backSum+=backTimenew-backTimeold;
      back_edge=false;
  }
}


void RPM::IRS_CHANGE(){
    if (freq_meas){
        if (digitalRead(Pin_OIntp)==HIGH){
            front_edge=true;
        }else{
            back_edge=true;
        }
    }

}
