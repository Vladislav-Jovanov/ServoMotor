#include "Servo_Motor.h"
#include "Arduino.h"

Servo_Motor::Servo_Motor()
{
    pwm=0;
    direction=true;

}

Servo_Motor::~Servo_Motor()
{
    //dtor
}

void Servo_Motor::stopMotor(){
    digitalWrite(Pin_IN1, LOW);
    digitalWrite(Pin_IN2, LOW);
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
        digitalWrite(Pin_IN1, HIGH);
        digitalWrite(Pin_IN2, LOW);
        analogWrite(Pin_PWM, pwm_out);
    }else{
        digitalWrite(Pin_IN1, LOW);
        digitalWrite(Pin_IN2, HIGH);
        analogWrite(Pin_PWM, pwm_out);
    }
}

void Servo_Motor::setupMotor(){
    pinMode(Pin_IN1, OUTPUT);
    pinMode(Pin_IN2, OUTPUT);
    pinMode(Pin_PWM, OUTPUT);
}

float Servo_Motor::floatMap(float x, float in_min, float in_max, float out_min, float out_max){
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
