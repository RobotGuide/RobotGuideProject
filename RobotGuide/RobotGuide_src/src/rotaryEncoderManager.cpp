#include "rotaryEncoderManager.h"

RotaryEncoderManager* RotaryEncoderManager::instance = NULL;

RotaryEncoderManager* RotaryEncoderManager::getInstance()
{
    if(instance == NULL)
    {
      instance = new RotaryEncoderManager();
    }

    return instance;
}

RotaryEncoderManager::RotaryEncoderManager()
{
    clearCounts();
}

void RotaryEncoderManager::clearCounts()
{
    encoderCounterL = 0;
    encoderCounterR = 0;
}

void RotaryEncoderManager::setupInterrupts(int encoderPinL, int encoderPinR)
{
    // void (* arr [1])();
    // arr[0] = &isr_renc_R;

    pinMode(encoderPinL, INPUT);
    pinMode(encoderPinR, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderPinL), &isr_renc_L, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinR), &isr_renc_R, CHANGE);
}

void RotaryEncoderManager::isr_renc_L()
{
    instance->encoderCounterL++;
}

void RotaryEncoderManager::isr_renc_R()
{
    instance->encoderCounterR++;
}

