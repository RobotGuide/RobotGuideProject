#include "movement.h"
//currently there is some innacuracy because of the momentum of the
//robot at stop, this might be fixed in a couple of ways:
//-gently scale motor power down as rotary encoders approach target count
//-calculate amount of rotary ticks that can be deducted by calculating drift
//lets keep motor usage between 75 and 90/100 for now
//todo: think about dynamically deciding motor power using the gyroscope

Movement::Movement(int wheelDiameter, int platformDiameter, int rencCountsPerRev,
    RotaryEncoders* rotaryEncoders, L298NWheel* leftWheel, L298NWheel* rightWheel)
    :done_(true), targetCount_(0), encLPrev_(0), encRPrev_(0), prevTime_(0),
    countsPerRev_(rencCountsPerRev), rotaryEncoders_(rotaryEncoders),
    leftWheel_(leftWheel), rightWheel_(rightWheel),
    wheelCircumference_((PI * wheelDiameter) + 0.5),
    platformCircumference_((PI * platformDiameter) + 0.5)
{
    // Serial.println(wheelCircumference_);
    // Serial.println(platformCircumference_);
}

bool Movement::destinationReached()
{
    return done_;
}

void Movement::move(int millimeters)
{
    done_ = false;

    targetCount_ = calculateEncoderTicks(labs(millimeters));
    // unsigned long revolutions = (abs(millimeters) * 1000L) / wheelCircumference_;
    // targetCount_ = ((revolutions * countsPerRev_) + 500L) / 1000L; //helper function

    // Serial.println(targetCount_);

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

    unsigned long millimeters = (labs(degrees) * platformCircumference_) / 360;
    
    targetCount_ = calculateEncoderTicks(millimeters);
    // unsigned long revolutions = (millimeters * 1000L) / wheelCircumference_;
    // targetCount_ = ((revolutions * countsPerRev_) + 500L) / 1000L;

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

    unsigned long time = millis();
    if(deltaTimeElapsed(time))
    {
        return;
    }

    prevTime_ = time + delayTime_;

    unsigned long encoderL = rotaryEncoders_->getEncoderCountL();
    unsigned long encoderR = rotaryEncoders_->getEncoderCountR();

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
    unsigned long encoderLDiv = encoderL - encLPrev_;
    unsigned long encoderRDiv = encoderR - encRPrev_;

    encLPrev_ = encoderL;
    encRPrev_ = encoderR;

    //todo: add linear interpolation to power variables?

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

unsigned long Movement::calculateEncoderTicks(unsigned long millimeters)
{
    unsigned long revolutions = (millimeters * 1000L) / wheelCircumference_;
    return ((revolutions * countsPerRev_) + 500L) / 1000L;
}