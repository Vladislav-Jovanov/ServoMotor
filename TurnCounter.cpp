#include "TurnCounter.h"
#include "Optic_Interrupt.h"
#include "Arduino.h"

TurnCounter::TurnCounter(bool * led_on, unsigned int val):Optic_Interrupt(led_on)
{
    if (!val){
        totCount=10;
    }else{
        totCount = val;
    }
    counter_running=false;
    backEdge=false;
}

TurnCounter::~TurnCounter()
{
    //dtor
}


void TurnCounter::start_counter(){
  counter_running=true;
  backCounter=0;
  currentCount=0;
  if (!*led_on){
    start_OI();
  }
}

void TurnCounter::stop_counter(bool val){
  if (!val){
    stop_OI();
  }
  counter_running=false;
}

void TurnCounter::main_counter(HardwareSerial * Serial){
    if (backEdge & counter_running){
        backCounter++;
        if (!(backCounter % openings)){
            currentCount++;
            Serial->print("We are at round ");
            Serial->print(currentCount);
            Serial->print("/");
            Serial->println(totCount);
            backCounter=0;
        }
        backEdge=false;
    }

}

void TurnCounter::IRS_CHANGE(){
    if (counter_running & (digitalRead(Pin_OIntp)==LOW)){
        backEdge=true;
    }
}