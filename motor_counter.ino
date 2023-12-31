//here define pins if different
#define Pin_LED 4
#define Pin_OIntp 2
#define M1_dir1 8
#define M1_dir2 7
#define M1_pwm 9
#define openings 8

#define COMMANDS "Motor controls:\n'm<num>' - set motor to <num>% power\n'moff' - turn motor off, same as m0\n'm+' - set direction clockwise\n'm-' - set direction counterclockwise\n'mdir' - get direction\n'fmeas' - measure and display frequency\n'foff' - stop the frequency measurement\n'c<num>' - allow <num> motor turns\n'cstart' - start the counter\n'cstop' - stop the counter\n'cpause' - pause the counter\n'crestart' - start again\n'cstatus' - display status.\nAny other command will stop the motor and reset the counter."

#include "Servo_Motor.h"
#include "Optic_Interrupt.h"
#include "RPM.h"
#include "TurnCounter.h"

String computerdata;  // in the main
bool serial_event=false;//            in the main
bool restart=true;//first run         in the main
bool led_on;//here is stored if led is on or off

Servo_Motor my_motor(M1_dir1, M1_dir2, M1_pwm);
RPM my_rpm(&led_on);
TurnCounter my_counter(&led_on);


//I like this approach better
void Iterrupt_Action(){
    my_rpm.IRS_CHANGE();
    my_counter.IRS_CHANGE();
}

void counter_end(){
  my_motor.stopMotor();
  my_rpm.stop_freq_meas();
  my_counter.stop_counter();
}

/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-potentiometer
 */


//function serialEvent is recognizable by arduino in the main
void serialEvent() {
  computerdata=Serial.readString(); //this interrupt will trigger when the data coming from the serial monitor(pc/mac/other) is received.
  serial_event = true; //set the serial event flag only if command is in proper format
}

void ProcessCommand(String *computerdata){
    //switch ((*computerdata).charAt(0)) alternative
    switch (computerdata->charAt(0)){
       case 'm':
        //change of motor direction
        if (computerdata->charAt(1)=='+'){
            my_motor.setMotor(my_motor.get_pwm(),1);
         //change of motor direction
         }else if (computerdata->charAt(1)=='-'){
            my_motor.setMotor(my_motor.get_pwm(),0);
         }else if (computerdata->substring(computerdata->indexOf("m")+1,computerdata->indexOf("m")+4)=="off"){
            my_motor.stopMotor();
         }else if (computerdata->substring(computerdata->indexOf("m")+1,computerdata->indexOf("m")+4)=="dir"){
            my_motor.display_direction(&Serial);
         }else if ((computerdata->substring(computerdata->indexOf("m")+1).toInt()<=0) & (computerdata->substring(computerdata->indexOf("m")+1)!="0")){
          //unallowed command
            Serial.println("Command doesn't exist. Halting everyting.");
            counter_end();
            //set count at inf
         }else{
            my_motor.setMotor(computerdata->substring(computerdata->indexOf("m")+1).toInt(),my_motor.get_direction());
         }
         break;
       case 'f':
         if (computerdata->substring(computerdata->indexOf("f")+1,computerdata->indexOf("f")+5)=="meas"){
            my_rpm.start_freq_meas();
         }else if (computerdata->substring(computerdata->indexOf("f")+1,computerdata->indexOf("f")+4)=="off"){
            my_rpm.stop_freq_meas(my_counter.GetCounterStatus());
         }else{
           Serial.println("Command doesn't exist. Halting everyting.");
          counter_end();
         }

         break;
      case 'c':
         if (computerdata->substring(computerdata->indexOf("c")+1,computerdata->indexOf("c")+6)=="reset"){
            my_counter.SetCurrentCounter(0);
         }else if (computerdata->substring(computerdata->indexOf("c")+1,computerdata->indexOf("c")+8)=="restart"){
            my_counter.SetCurrentCounter(0);
            my_counter.start_counter(&counter_end);
            //my_counter.start_counter();
         }else if (computerdata->substring(computerdata->indexOf("c")+1,computerdata->indexOf("c")+5)=="stop"){
            my_counter.stop_counter(my_rpm.GetFreqMeas());
            my_counter.SetCurrentCounter(0);
         }else if (computerdata->substring(computerdata->indexOf("c")+1,computerdata->indexOf("c")+6)=="start"){
            my_counter.start_counter(&counter_end);
         }else if (computerdata->substring(computerdata->indexOf("c")+1,computerdata->indexOf("c")+6)=="pause"){
            my_counter.stop_counter(my_rpm.GetFreqMeas());
         }else if (computerdata->substring(computerdata->indexOf("c")+1,computerdata->indexOf("c")+7)=="status"){
            my_counter.display_status(&Serial);
         }else if ((computerdata->substring(computerdata->indexOf("c")+1).toInt()<=0) & (computerdata->substring(computerdata->indexOf("c")+1)!="0")){
            Serial.println("Command doesn't exist. Halting everyting.");
            counter_end();
         }else{
            my_counter.SetCounter(computerdata->substring(computerdata->indexOf("c")+1).toInt());
         }
         break;
      default:
         Serial.println("Command doesn't exist. Halting everyting.");
         counter_end();
         //set count ot inf
         Serial.println(COMMANDS);
         break;
    }

}

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  my_rpm.setup_OI();
  //my_counter.setup_OI();
  attachInterrupt(digitalPinToInterrupt(Pin_OIntp), Iterrupt_Action, CHANGE);//setup OI
  my_motor.setupMotor();
}

// the loop routine runs over and over again forever:
void loop() {
  if (restart){
    Serial.println(COMMANDS);
    restart=false;
  }
  if (serial_event){
    ProcessCommand(&computerdata);
    serial_event=false;
  }
  my_rpm.main_freq(&Serial);
  my_counter.main_counter(&Serial);
}

