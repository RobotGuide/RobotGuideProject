#ifndef ROBOTGUIDE_MOVEMENT_H
#define ROBOTGUIDE_MOVEMENT_H

#include "rotaryEncoders.h"
#include "L298NWheel.h"
#include <stdint.h>

class Movement
{
public:
    Movement(int wheelDiameter, int platformDiameter, int rencCountsPerRev,
        RotaryEncoders* rotaryEncoders, L298NWheel* leftWheel, L298NWheel* rightWheel);
    bool destinationReached();
    void move(int millimeters);
    void rotate(int degrees);
    void loopTick();
    void brake();
    
private:
    RotaryEncoders* rotaryEncoders_;
    L298NWheel* leftWheel_;
    L298NWheel* rightWheel_;
    const int wheelCircumference_;
    const int platformCircumference_;
    const unsigned long countsPerRev_;
    bool done_ = true;
    unsigned long targetCount_ = 0;
    unsigned long encLPrev_ = 0;
    unsigned long encRPrev_ = 0;
    uint8_t powerL_ = 0;
    uint8_t powerR_ = 0;
    unsigned long prevTime_ = 0;

    const unsigned long delayTime_ = 20;
    const uint8_t baseMovePower_ = 90;
    const uint8_t baseTurnPower_ = 80;

    void adjustWheelPower(unsigned long encoderL, unsigned long encoderR);
    void setWheelPower();
    bool rotaryEncodersReachedCount(unsigned long encoderL, unsigned long encoderR) const;
    bool deltaTimeElapsed(unsigned long time) const;
    unsigned long calculateEncoderTicks(unsigned long millimeters) const;
};

#endif