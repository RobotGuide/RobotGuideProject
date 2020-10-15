#ifndef MOTOR_MANAGER
#define MOTOR_MANAGER

#include <Arduino.h>
#include "rotaryEncoderManager.h"
#include "motorDriver.h"

class MotorManager
{
public:
    MotorManager(
        int wheelDiameter,
        int platformDiameter,
        int rencCountsPerRev,
        RotaryEncoderManager* rotaryEncoderManager,
        MotorDriver* motorDriver);
    bool destinationReached();
    void move(float distance);
    void rotate(float degrees);
    void loopTick();
private:
    RotaryEncoderManager* rotaryEncoderManager;
    MotorDriver* motorDriver;
    bool done;
    float wheelCircumference; //mm
    float platformCircumference; //mm
    uint16_t countsPerRev;
    uint32_t targetCount;
    uint32_t encLPrev;
    uint32_t encRPrev;
    byte powerL;
    byte powerR;
    unsigned long delayTime;
    unsigned long prevTime;
};

#endif