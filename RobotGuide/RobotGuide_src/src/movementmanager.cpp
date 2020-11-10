#include "movementManager.h"
//currently there is some innacuracy because of the momentum of the
//robot at stop, this might be fixed in a couple of ways:
//-gently scale motor power down as rotary encoders approach target count
//-calculate amount of rotary ticks that can be deducted by calculating drift
//lets keep motor usage between 75 and 90/100 for now

//todo: think about dynamically deciding motor power

#define ROTATION_SPEED 80
#define MOVEMENT_SPEED 90

MotorManager::MotorManager(
    int wheelDiameter,
    int platformDiameter,
    int rencCountsPerRev,
    RotaryEncoders* rotaryEncoders,
    MotorDriver* motorDriver)
{
    this->done = true;
    this->wheelCircumference = PI * wheelDiameter;
    this->platformCircumference = PI * platformDiameter;
    this->targetCount = 0;
    this->encLPrev = 0;
    this->encRPrev = 0;

    this->delayTime = 20;
    this->prevTime = 0;

    this->countsPerRev = rencCountsPerRev;
    this->rotaryEncoders = rotaryEncoders;
    this->motorDriver = motorDriver;
}

bool MotorManager::destinationReached()
{
    return done;
}

void MotorManager::move(float distance) //distance is in cm
{
    done = false;

    float revolutions = (fabs(distance) * 10) / wheelCircumference;

    targetCount = revolutions * countsPerRev;

    if(distance > 0)
    {
        motorDriver->setLeftWheel(HIGH, LOW, MOVEMENT_SPEED);
        motorDriver->setRightWheel(HIGH, LOW, MOVEMENT_SPEED);
    }
    else
    {
        motorDriver->setLeftWheel(LOW, HIGH, MOVEMENT_SPEED);
        motorDriver->setRightWheel(LOW, HIGH, MOVEMENT_SPEED);
    }

    powerL = MOVEMENT_SPEED;
    powerR = MOVEMENT_SPEED;

    rotaryEncoders->clearCounts();
    encLPrev = 0;
    encRPrev = 0;
}

void MotorManager::rotate(float degrees)
{
    done = false;

    float distance = (fabs(degrees) / 360.0) * platformCircumference;
    
    float revolutions = distance / wheelCircumference;

    targetCount = revolutions * countsPerRev;

    if(degrees > 0)
    {
        motorDriver->setLeftWheel(LOW, HIGH, ROTATION_SPEED);
        motorDriver->setRightWheel(HIGH, LOW, ROTATION_SPEED);
    }
    else
    {
        motorDriver->setLeftWheel(HIGH, LOW, ROTATION_SPEED);
        motorDriver->setRightWheel(LOW, HIGH, ROTATION_SPEED);
    }

    powerL = ROTATION_SPEED;
    powerR = ROTATION_SPEED;

    rotaryEncoders->clearCounts();
    encLPrev = 0;
    encRPrev = 0;
}

void MotorManager::loopTick()
{
    if(done)
    {
        return;
    }

    unsigned long time = millis();
    if(time < prevTime)
    {
        return;
    }

    prevTime = time + delayTime;

    uint32_t encoderL = rotaryEncoders->encoderCounterL;
    uint32_t encoderR = rotaryEncoders->encoderCounterR;

    if((encoderL > targetCount) && (encoderR > targetCount))
    {
        motorDriver->setLeftWheel(LOW, LOW, 255);
        motorDriver->setRightWheel(LOW, LOW, 255);
        done = true;
        return;
    }

    motorDriver->setLeftWheel(powerL);
    motorDriver->setRightWheel(powerR);

    uint32_t encoderLDiv = encoderL - encLPrev;
    uint32_t encoderRDiv = encoderR - encRPrev;

    encLPrev = encoderL;
    encRPrev = encoderR;

    //todo: add linear interpolation to power variables

    if(encoderLDiv > encoderRDiv)
    {
        powerL -= 5;
        powerR += 5;
    }

    if(encoderLDiv < encoderRDiv)
    {
        powerL += 5;
        powerR -= 5;
    }
}