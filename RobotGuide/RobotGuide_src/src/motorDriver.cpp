#include "motorDriver.h"

MotorDriver::MotorDriver(
    int in1Pin,
    int in2Pin,
    int in3Pin,
    int in4Pin,
    int enAPin,
    int enBPin)
    :pwmAPin(enAPin),
    pwmBPin(enBPin),
    in1Pin(in1Pin),
    in2Pin(in2Pin),
    in3Pin(in3Pin),
    in4Pin(in4Pin)
{}

void MotorDriver::setLeftWheel(int forward, int backward, byte speed)
{
    digitalWrite(in3Pin, backward);
    digitalWrite(in4Pin, forward);

    analogWrite(pwmBPin, speed);
}

void MotorDriver::setRightWheel(int forward, int backward, byte speed)
{
    digitalWrite(in1Pin, backward);
    digitalWrite(in2Pin, forward);

    analogWrite(pwmAPin, speed);
}