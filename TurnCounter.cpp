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


void TurnCounter::start_counter(void (*func)()=NULL){
  counter_running=true;
  backCounter=0;
  init=true;
  //currentCount=0;
  if (func==NULL){
    counter_end_func=&pass;
  }else{
    counter_end_func=func;
  }
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

void TurnCounter::display_status(HardwareSerial *Serial){
    Serial->print("#Counter:");
    if (counter_running){
      Serial->print("on");
    }else{
      Serial->print("off");
    }
    Serial->print("#Round:");
    Serial->print(currentCount);
    Serial->print("/");
    Serial->println(totCount);

}

void TurnCounter::main_counter(HardwareSerial * Serial){
    if (backEdge & counter_running){
        if (init){
          init=false;
        }else{
            backCounter++;
            if (!(backCounter % openings)){
                currentCount++;
                Serial->print("#Round:");
                Serial->print(currentCount);
                Serial->print("/");
                Serial->println(totCount);
                backCounter=0;
            }
        }
        if (currentCount>=totCount){
          counter_end_func();
        }
        
        backEdge=false;
    }

}

void TurnCounter::IRS_CHANGE(){
    if (counter_running & (digitalRead(Pin_OIntp)==LOW)){
        backEdge=true;
    }
}