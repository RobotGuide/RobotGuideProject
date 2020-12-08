#include "movement.h"

#include <Arduino.h>

Movement::Movement(int wheelDiameter, int platformDiameter, int rencCountsPerRev,
    RotaryEncoders* rotaryEncoders, L298NWheel* leftWheel, L298NWheel* rightWheel)
    :countsPerRev_(rencCountsPerRev), rotaryEncoders_(rotaryEncoders),
    leftWheel_(leftWheel), rightWheel_(rightWheel),
    wheelCircumference_((PI * wheelDiameter) + 0.5),
    platformCircumference_((PI * platformDiameter) + 0.5)
{}

bool Movement::destinationReached()
{
    return done_;
}

void Movement::move(int millimeters)
{
    done_ = false;

    targetCount_ = calculateEncoderTicks(labs(millimeters));

    if(millimeters > 0)
    {
        leftWheel_->setWheel(Direction::FORWARD, baseMovePower_);
        rightWheel_->setWheel(Direction::FORWARD, baseMovePower_);
    }
    else
    {
        leftWheel_->setWheel(Direction::BACKWARD, baseMovePower_);
        rightWheel_->setWheel(Direction::BACKWARD, baseMovePower_);
    }

    powerL_ = baseMovePower_;
    powerR_ = baseMovePower_;

    rotaryEncoders_->clearCounts();
    encLPrev_ = 0;
    encRPrev_ = 0;
}

void Movement::rotate(int degrees)
{
    done_ = false;

    const unsigned long millimeters = (labs(degrees) * platformCircumference_) / 360;
    
    targetCount_ = calculateEncoderTicks(millimeters);

    targetCount_ -= 4;

    if(degrees > 0)
    {
        leftWheel_->setWheel(Direction::BACKWARD, baseTurnPower_);
        rightWheel_->setWheel(Direction::FORWARD, baseTurnPower_);
    }
    else
    {
        leftWheel_->setWheel(Direction::FORWARD, baseTurnPower_);
        rightWheel_->setWheel(Direction::BACKWARD, baseTurnPower_);
    }

    powerL_ = baseTurnPower_;
    powerR_ = baseTurnPower_;

    rotaryEncoders_->clearCounts();
    encLPrev_ = 0;
    encRPrev_ = 0;
}

void Movement::loopTick()
{
    if(done_)
    {
        return;
    }

    const unsigned long time = millis();
    if(deltaTimeElapsed(time))
    {
        return;
    }

    prevTime_ = time + delayTime_;

    const unsigned long encoderL = rotaryEncoders_->getEncoderCountL();
    const unsigned long encoderR = rotaryEncoders_->getEncoderCountR();

    if(rotaryEncodersReachedCount(encoderL, encoderR))
    {
        brake();
        return;
    }

    setWheelPower();
    adjustWheelPower(encoderL, encoderR);
}

void Movement::brake()
{
    leftWheel_->brake();
    rightWheel_->brake();
    done_ = true;
}

void Movement::adjustWheelPower(unsigned long encoderL, unsigned long encoderR)
{
    const unsigned long encoderLDiv = encoderL - encLPrev_;
    const unsigned long encoderRDiv = encoderR - encRPrev_;

    encLPrev_ = encoderL;
    encRPrev_ = encoderR;

    if(encoderLDiv > encoderRDiv)
    {
        powerL_ -= 5;
        powerR_ += 5;
    }

    if(encoderLDiv < encoderRDiv)
    {
        powerL_ += 5;
        powerR_ -= 5;
    }
}

void Movement::setWheelPower()
{
    leftWheel_->setWheelPower(powerL_);
    rightWheel_->setWheelPower(powerR_);
}

bool Movement::rotaryEncodersReachedCount(unsigned long encoderL, unsigned long encoderR) const
{
    return (encoderL > targetCount_) && (encoderR > targetCount_);
}

bool Movement::deltaTimeElapsed(unsigned long time) const
{
    return time < prevTime_;
}

unsigned long Movement::calculateEncoderTicks(unsigned long millimeters) const
{
    unsigned long revolutions = (millimeters * 1000L) / wheelCircumference_;
    return ((revolutions * countsPerRev_) + 500L) / 1000L;
}