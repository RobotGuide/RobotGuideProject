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

void MotorDriver::setLeftWheel(uint8_t speed)
{
    setLeftWheel(in4Value, in3Value, speed);
}

void MotorDriver::setRightWheel(uint8_t speed)
{
    setRightWheel(in2Value, in1Value, speed);
}

void MotorDriver::setLeftWheel(uint8_t forward, uint8_t backward)
{
    setLeftWheel(forward, backward, pwmBValue);
}

void MotorDriver::setRightWheel(uint8_t forward, uint8_t backward)
{
    setRightWheel(forward, backward, pwmAValue);
}

void MotorDriver::setLeftWheel(uint8_t forward, uint8_t backward, uint8_t speed)
{
    in3Value = backward;
    in4Value = forward;
    pwmBValue = speed;

    digitalWrite(in3Pin, backward);
    digitalWrite(in4Pin, forward);

    analogWrite(pwmBPin, speed);
}

void MotorDriver::setRightWheel(uint8_t forward, uint8_t backward, uint8_t speed)
{
    in1Value = backward;
    in2Value = forward;
    pwmAValue = speed;

    digitalWrite(in1Pin, backward);
    digitalWrite(in2Pin, forward);

    analogWrite(pwmAPin, speed);
}

void MotorDriver::reverseLeftWheel()
{
    digitalWrite(in3Pin, in4Value);
    digitalWrite(in4Pin, in3Value);
}

void MotorDriver::reverseRightWheel()
{
    digitalWrite(in1Pin, in2Value);
    digitalWrite(in2Pin, in1Value);
}