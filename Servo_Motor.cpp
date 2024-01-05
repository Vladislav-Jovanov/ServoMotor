#include "Servo_Motor.h"
#include "Arduino.h"
#include "HardwareSerial.h"

Servo_Motor::Servo_Motor(int dir1_pin, int dir2_pin, int pwm_pin)
{   
    pin_dir1=dir1_pin;
    pin_dir2=dir2_pin;
    pin_pwm=pwm_pin;
    pwm=0;
    direction=true;

}

Servo_Motor::~Servo_Motor()
{
    //dtor
}

void Servo_Motor::stopMotor(){
    digitalWrite(pin_dir1, LOW);
    digitalWrite(pin_dir2, LOW);
    delay(250);
}

bool Servo_Motor::get_direction(){
    return direction;
}

void Servo_Motor::set_direction(bool direction_in){
    direction=direction_in;
}

int Servo_Motor::get_pwm(){
    return pwm;
}
void Servo_Motor::set_pwm(int pwm_in){
    pwm=pwm_in;
}

void Servo_Motor::setMotor(int pwm_in, bool direction_in){
    set_direction(direction_in);
    if (pwm_in<0){
        pwm_in=0;
    }else if (pwm_in>100){
        pwm_in=100;
    }
    set_pwm(pwm_in);
    float pwm_out=floatMap(pwm_in, 0,100,0,255);
    if (direction_in!=direction){
        stopMotor();
    }
    if(direction){
        digitalWrite(pin_dir1, HIGH);
        digitalWrite(pin_dir2, LOW);
        analogWrite(pin_pwm, pwm_out);
    }else{
        digitalWrite(pin_dir1, LOW);
        digitalWrite(pin_dir2, HIGH);
        analogWrite(pin_pwm, pwm_out);
    }
}

void Servo_Motor::setupMotor(){
    pinMode(pin_dir1, OUTPUT);
    pinMode(pin_dir2, OUTPUT);
    pinMode(pin_pwm, OUTPUT);
}

float Servo_Motor::floatMap(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void Servo_Motor::display_direction(HardwareSerial *Serial){
    if (direction){
     Serial->println("CW");
     //(*Serial).println("CW");
  }else{
     Serial->println("CCW");
  }

}