#ifndef MOTOR_DRIVER
#define MOTOR_DRIVER

#include <Arduino.h>


class MotorDriver
{
public:
    MotorDriver(
    int in1Pin,
    int in2Pin,
    int in3Pin,
    int in4Pin,
    int enAPin,
    int enBPin);
    void setLeftWheel(int forward, int backward, byte speed);
    void setRightWheel(int forward, int backward, byte speed);
private:
    int pwmAPin;
    int pwmBPin;
    int in1Pin;
    int in2Pin;
    int in3Pin;
    int in4Pin;
};

#endif