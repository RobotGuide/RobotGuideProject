#include "movementManager.h"
//currently there is some innacuracy because of the momentum of the
//robot at stop, this might be fixed in a couple of ways:
//-gently scale motor power down as rotary encoders approach target count
//-calculate amount of rotary ticks that can be deducted by calculating drift
//lets keep motor usage between 75 and 90/100 for now

//todo: think about dynamically deciding motor power

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
        motorDriver->setLeftWheel(HIGH, LOW, baseMoveSpeed);
        motorDriver->setRightWheel(HIGH, LOW, baseMoveSpeed);
    }
    else
    {
        motorDriver->setLeftWheel(LOW, HIGH, baseMoveSpeed);
        motorDriver->setRightWheel(LOW, HIGH, baseMoveSpeed);
    }

    powerL = baseMoveSpeed;
    powerR = baseMoveSpeed;

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
        motorDriver->setLeftWheel(LOW, HIGH, baseTurnSpeed);
        motorDriver->setRightWheel(HIGH, LOW, baseTurnSpeed);
    }
    else
    {
        motorDriver->setLeftWheel(HIGH, LOW, baseTurnSpeed);
        motorDriver->setRightWheel(LOW, HIGH, baseTurnSpeed);
    }

    powerL = baseTurnSpeed;
    powerR = baseTurnSpeed;

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

    unsigned long encoderL = rotaryEncoders->getEncoderCountL();
    unsigned long encoderR = rotaryEncoders->getEncoderCountR();

    if((encoderL > targetCount) && (encoderR > targetCount))
    {
        brake();
        return;
    }

    setWheelPower();
    adjustWheelPower(encoderL, encoderR);
}

void MotorManager::brake()
{
    motorDriver->setLeftWheel(LOW, LOW, 255);
    motorDriver->setRightWheel(LOW, LOW, 255);
    done = true;
}

void MotorManager::adjustWheelPower(unsigned long encoderL, unsigned long encoderR)
{
    unsigned long encoderLDiv = encoderL - encLPrev;
    unsigned long encoderRDiv = encoderR - encRPrev;

    encLPrev = encoderL;
    encRPrev = encoderR;

    //todo: add linear interpolation to power variables?

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

void MotorManager::setWheelPower()
{
    motorDriver->setLeftWheel(powerL);
    motorDriver->setRightWheel(powerR);
}