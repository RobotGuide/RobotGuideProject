#ifndef MOTOR_MANAGER
#define MOTOR_MANAGER

#include <Arduino.h>
#include "rotaryEncoders.h"
#include "motorDriver.h"

class Movement
{
public:
    Movement(
        int wheelDiameter,
        int platformDiameter,
        int rencCountsPerRev,
        RotaryEncoders* rotaryEncoders,
        MotorDriver* motorDriver);
    bool destinationReached();
    void move(float centimeters);
    void rotate(float degrees);
    void loopTick();
    void brake();
private:
    RotaryEncoders* rotaryEncoders;
    MotorDriver* motorDriver;
    bool done;
    int wheelCircumference;
    int platformCircumference;
    unsigned long countsPerRev;
    unsigned long targetCount;
    unsigned long encLPrev;
    unsigned long encRPrev;
    uint8_t powerL;
    uint8_t powerR;
    unsigned long delayTime;
    unsigned long prevTime;

    const int baseMoveSpeed = 90;
    const int baseTurnSpeed = 80;

    void adjustWheelPower(unsigned long encoderL, unsigned long encoderR);
    void setWheelPower();
    bool rotaryEncodersReachedCount(unsigned long encoderL, unsigned long encoderR);
    bool deltaTimeElapsed(unsigned long time);
};

#endif