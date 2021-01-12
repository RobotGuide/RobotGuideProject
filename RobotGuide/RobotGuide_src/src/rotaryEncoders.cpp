#include "RotaryEncoders.h"
#include "Constants.h"

#include <Arduino.h>

RotaryEncoders RotaryEncoders::instance;

RotaryEncoders& RotaryEncoders::getInstance()
{
    return instance;
}

RotaryEncoders::RotaryEncoders()
{
    clearCounts();
    setupInterrupts(RENC_PIN_L, RENC_PIN_R);
}

void RotaryEncoders::clearCounts()
{
    encoderCounterL = 0;
    encoderCounterR = 0;
}

unsigned long RotaryEncoders::getEncoderCountL() const
{
    return encoderCounterL;
}

unsigned long RotaryEncoders::getEncoderCountR() const
{
    return encoderCounterR;
}

void RotaryEncoders::setupInterrupts(int encoderPinL, int encoderPinR)
{
    pinMode(encoderPinL, INPUT);
    pinMode(encoderPinR, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderPinL), &isr_renc_L, CHANGE);
    attachInterrupt(digitalPinToInterrupt(encoderPinR), &isr_renc_R, CHANGE);
}

void RotaryEncoders::isr_renc_L()
{
    instance.encoderCounterL++;
}

void RotaryEncoders::isr_renc_R()
{
    instance.encoderCounterR++;
}

