#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H
#define Pin_IN1 8
#define Pin_IN2 7
#define Pin_PWM 9


class Servo_Motor
{
    public:
        Servo_Motor();
        virtual ~Servo_Motor();
        void stopMotor();
        bool get_direction();
        int get_pwm();
        void setMotor(int pwm_in, bool direction_in);
        void setupMotor();

    protected:

    private:
        float floatMap(float x, float in_min, float in_max, float out_min, float out_max);
        void set_direction(bool direction_in);
        void set_pwm(int pwm);
        bool direction;
        int pwm;
};

#endif // SERVO_MOTOR_H
