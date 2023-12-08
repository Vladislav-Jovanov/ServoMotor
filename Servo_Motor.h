#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H
#include "HardwareSerial.h"


class Servo_Motor
{
    public:
        Servo_Motor(int dir1_pin, int dir2_pin, int pwm_pin);
        virtual ~Servo_Motor();
        void stopMotor();
        bool get_direction();
        int get_pwm();
        void setMotor(int pwm_in, bool direction_in);
        void setupMotor();
        void display_direction(HardwareSerial * Serial);

    protected:

    private:
        float floatMap(float x, float in_min, float in_max, float out_min, float out_max);
        void set_direction(bool direction_in);
        void set_pwm(int pwm);
        bool direction;
        int pwm;
        int pin_dir1;
        int pin_dir2;
        int pin_pwm;
};

#endif // SERVO_MOTOR_H
