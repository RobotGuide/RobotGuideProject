#ifndef ROBOTGUIDE_MOVEMENT_H
#define ROBOTGUIDE_MOVEMENT_H

#include "RotaryEncoders.h"
#include "L298NWheel.h"
#include "PIDcontroller.h"
#include "ILoopComponent.h"
#include <stdint.h>

class Movement : ILoopComponent
{
public:
    Movement(int wheelDiameter,
            int platformDiameter,
            int rencCountsPerRev,
            float controlSignalPercentile,
            float correctionPercentile,
            float integratorCutoffBound,
            uint8_t maxPower,
            uint8_t errorBound,
            RotaryEncoders& rotaryEncoders,
            L298NWheel& leftWheel,
            L298NWheel& rightWheel,
            PIDcontroller& leftPID,
            PIDcontroller& rightPID,
            PIDcontroller& deltaPID);
    Movement(const Movement& other) = delete;
    Movement& operator=(const Movement&) = delete;
    ~Movement() override = default;

    bool NeedsUpdate(unsigned long time) const override;
    void Update(unsigned long time) override;

    bool IsMoving();
    void Move(int millimeters);
    void Rotate(int degrees);
    void Brake();
    
private:
    RotaryEncoders& rotaryEncoders;
    L298NWheel& leftWheel;
    L298NWheel& rightWheel;
    PIDcontroller& leftPID;
    PIDcontroller& rightPID;
    PIDcontroller& deltaPID;
    
    const unsigned long countsPerRev;
    const float wheelCircumference;
    const float platformCircumference;
    const uint8_t maxPower;
    const uint8_t errorBound;

    const float controlSignalPercentile;
    const float correctionPercentile;
    const float integratorCutoffBound;

    bool moving;
    unsigned long targetCount;

    unsigned long prevTime;
    const int delay;

    float CalculateEncoderTicks(float millimeters) const;
    static float CalculateCircumference(float diameter);
};

#endif