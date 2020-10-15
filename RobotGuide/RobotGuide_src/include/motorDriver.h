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
    void setLeftWheel(uint8_t speed);
    void setRightWheel(uint8_t speed);
    void setLeftWheel(uint8_t forward, uint8_t backward);
    void setRightWheel(uint8_t forward, uint8_t backward);
    void setLeftWheel(uint8_t forward, uint8_t backward, uint8_t speed);
    void setRightWheel(uint8_t forward, uint8_t backward, uint8_t speed);
    void reverseLeftWheel();
    void reverseRightWheel();
private:
    int pwmAPin;
    int pwmBPin;
    int in1Pin;
    int in2Pin;
    int in3Pin;
    int in4Pin;
    int pwmAValue;
    int pwmBValue;
    int in1Value;
    int in2Value;
    int in3Value;
    int in4Value;
};

#endif