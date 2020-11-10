#include "rotaryEncoders.h"

RotaryEncoders* RotaryEncoders::instance = NULL;

RotaryEncoders* RotaryEncoders::getInstance()
{
    if(instance == NULL)
    {
      instance = new RotaryEncoders();
    }

    return instance;
}

RotaryEncoders::RotaryEncoders()
{
    clearCounts();
}

void RotaryEncoders::clearCounts()
{
    encoderCounterL = 0;
    encoderCounterR = 0;
}

void RotaryEncoders::setupInterrupts(int encoderPinL, int encoderPinR)
{
    // void (* arr [1])();
    // arr[0] = &isr_renc_R;

    pinMode(encoderPinL, INPUT);
    pinMode(encoderPinR, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderPinL), &isr_renc_L, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinR), &isr_renc_R, CHANGE);
}

void RotaryEncoders::isr_renc_L()
{
    instance->encoderCounterL++;
}

void RotaryEncoders::isr_renc_R()
{
    instance->encoderCounterR++;
}

