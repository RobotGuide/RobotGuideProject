#include "Movement.h"

#include <Arduino.h>
#include <math.h>

//TODO:
//clean up this file. create helper functions and add object variables whenever needed
//TULN 90 and TURN 90 kinda get stuck at the moment, i assume not enough power?
//check if problem also exists in ES version

Movement::Movement(int wheelDiameter,
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
                  PIDcontroller& deltaPID)
    : rotaryEncoders(rotaryEncoders)
    , leftWheel(leftWheel)
    , rightWheel(rightWheel)
    , leftPID(leftPID)
    , rightPID(rightPID)
    , deltaPID(deltaPID)
    , countsPerRev(rencCountsPerRev)
    , wheelCircumference(CalculateCircumference((float)wheelDiameter))
    , platformCircumference(CalculateCircumference((float)platformDiameter))
    , maxPower(maxPower)
    , errorBound(errorBound)
    , controlSignalPercentile(controlSignalPercentile)
    , correctionPercentile(correctionPercentile)
    , integratorCutoffBound(integratorCutoffBound)
    , moving(false)
    , targetCount(0)
    , prevTime(0)
    , delay(10)
{

}

bool Movement::NeedsUpdate(unsigned long time) const
{
    return (moving && time >= prevTime + delay);
}

void Movement::Update(unsigned long time)
{
    const unsigned long encoderL = rotaryEncoders.getEncoderCountL();
    const unsigned long encoderR = rotaryEncoders.getEncoderCountR();

    const long errorL = targetCount - encoderL;
    const long errorR = targetCount - encoderR;
    const long errorDelta = errorL - errorR;

    const long deltaTime = time - prevTime;

    prevTime = time;

    //make a general function that handles the left and right motors?
    if(errorL <= 0)
    {
        leftPID.resetController();
        leftWheel.brake();
    }

    if(errorR <= 0)
    {
        rightPID.resetController();
        rightWheel.brake();
    }

    if(errorL <= 0 && errorR <= 0)
    {
        Brake();
        return;
    }

    float controlSignalL = leftPID.calculateControlSignal(errorL, deltaTime);
    float controlSignalR = rightPID.calculateControlSignal(errorR, deltaTime);

    //good oportunity for a clamp function?
    float clampedControlSignalL = constrain(controlSignalL, 0, controlSignalPercentile * maxPower);
    float clampedControlSignalR = constrain(controlSignalR, 0, controlSignalPercentile * maxPower);

    //good oportunity for a helper function?
    leftPID.integratorEnabled(fabs(controlSignalL - clampedControlSignalL) < integratorCutoffBound);
    rightPID.integratorEnabled(fabs(controlSignalR - clampedControlSignalR) < integratorCutoffBound);

    float controlSignalDelta = deltaPID.calculateControlSignal(errorDelta, deltaTime);

    float clampedControlSignalDelta = constrain(controlSignalDelta, -(correctionPercentile * maxPower), correctionPercentile * maxPower);

    uint8_t clampedFinalSignalL = constrain(clampedControlSignalL + clampedControlSignalDelta, 0, maxPower);
    uint8_t clampedFinalSignalR = constrain(clampedControlSignalR - clampedControlSignalDelta, 0, maxPower);

    leftWheel.setWheelPower(clampedFinalSignalL);
    rightWheel.setWheelPower(clampedFinalSignalR);
}


bool Movement::IsMoving()
{
    return moving;
}

void Movement::Move(int millimeters)
{
    moving = true;

    targetCount = CalculateEncoderTicks(labs(millimeters));

    if(millimeters > 0)
    {
        leftWheel.setWheel(Direction::FORWARD, 0);
        rightWheel.setWheel(Direction::FORWARD, 0);
    }
    else
    {
        leftWheel.setWheel(Direction::BACKWARD, 0);
        rightWheel.setWheel(Direction::BACKWARD, 0);
    }

    rotaryEncoders.clearCounts();
}

void Movement::Rotate(int degrees)
{
    moving = true;

    const float millimeters = ((float)labs(degrees) * platformCircumference) / 360.0f;
    
    targetCount = CalculateEncoderTicks(millimeters);

    if(degrees > 0)
    {
        leftWheel.setWheel(Direction::BACKWARD, 0);
        rightWheel.setWheel(Direction::FORWARD, 0);
    }
    else
    {
        leftWheel.setWheel(Direction::FORWARD, 0);
        rightWheel.setWheel(Direction::BACKWARD, 0);
    }

    rotaryEncoders.clearCounts();
}

void Movement::Brake()
{
    leftPID.resetController();
    rightPID.resetController();

    leftWheel.brake();
    rightWheel.brake();
    moving = false;
}

float Movement::CalculateEncoderTicks(float millimeters) const
{
    float revolutions = millimeters / wheelCircumference;
    return revolutions * countsPerRev;
}

float Movement::CalculateCircumference(float diameter)
{
    return PI * diameter;
}