#include "movementManager.h"
//currently there is some innacuracy because of the momentum of the
//robot at stop, this might be fixed in a couple of ways:
//-play around with different gearboxes
//-gently scale motor power down as rotary encoders approach target count
//-calculate amount of rotary ticks that can be deducted by calculating drift
//-get better motors
//-reverse polarity of motors right before stopping (might be harmful): tried, but results are inconclusive
//lets keep motor usage between 75 and 90/100 for now

MotorManager::MotorManager(
    int wheelDiameter,
    int platformDiameter,
    int rencCountsPerRev,
    RotaryEncoderManager* rotaryEncoderManager,
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
    this->rotaryEncoderManager = rotaryEncoderManager;
    this->motorDriver = motorDriver;
}

bool MotorManager::destinationReached()
{
    return done;
}

void MotorManager::move(float distance) //distance is in cm
{
    done = false;

    float revolutions = (distance * 10) / wheelCircumference;

    targetCount = revolutions * countsPerRev;

    motorDriver->setLeftWheel(HIGH, LOW, 100);
    motorDriver->setRightWheel(HIGH, LOW, 100);

    powerL = 100;
    powerR = 100;

    rotaryEncoderManager->clearCounts();
    encLPrev = 0;
    encRPrev = 0;
}

void MotorManager::rotate(float degrees)
{
    done = false;

    float distance = (degrees / 360.0) * platformCircumference;
    
    float revolutions = distance / wheelCircumference;

    targetCount = revolutions * countsPerRev;
    
    motorDriver->setLeftWheel(LOW, HIGH, 90);
    motorDriver->setRightWheel(HIGH, LOW, 90);

    powerL = 90;
    powerR = 90;

    rotaryEncoderManager->clearCounts();
    encLPrev = 0;
    encRPrev = 0;
}

void MotorManager::loopTick()
{
    if(done)
    {
        return;
    }

    //add a delay?
    unsigned long time = millis();
    if(time < prevTime)
    {
        return;
    }

    prevTime = time + delayTime;
    Serial.println(prevTime);

    uint32_t encoderL = rotaryEncoderManager->encoderCounterL;
    uint32_t encoderR = rotaryEncoderManager->encoderCounterR;

    if((encoderL > targetCount) && (encoderR > targetCount))
    {
        // motorDriver->reverseLeftWheel();
        // motorDriver->reverseRightWheel();
        // delay(20);

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