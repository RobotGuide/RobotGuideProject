#ifndef MOTOR_MANAGER
#define MOTOR_MANAGER

#include <Arduino.h>
#include "rotaryEncoders.h"
#include "motorDriver.h"

class MotorManager
{
public:
    MotorManager(
        int wheelDiameter,
        int platformDiameter,
        int rencCountsPerRev,
        RotaryEncoders* rotaryEncoders,
        MotorDriver* motorDriver);
    bool destinationReached();
    void move(float distance);
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
};

#endif