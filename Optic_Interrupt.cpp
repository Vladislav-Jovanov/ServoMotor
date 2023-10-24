#include "Optic_Interrupt.h"
#include "Arduino.h"


Optic_Interrupt::~Optic_Interrupt()
{
    //dtor
}

void Optic_Interrupt::start_OI(){
  digitalWrite(Pin_LED, HIGH);
  *led_on=true;
}
void Optic_Interrupt::stop_OI(){
  digitalWrite(Pin_LED, LOW);
  *led_on=false;
}

void Optic_Interrupt::setup_OI(){
    pinMode(Pin_LED, OUTPUT);//setup OI
    pinMode(Pin_OIntp, INPUT);//setup OI
}
