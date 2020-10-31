#ifndef ROTARY_ENCODER_MANAGER
#define ROTARY_ENCODER_MANAGER

#include <Arduino.h>

class RotaryEncoderManager
{
public:
    volatile uint32_t encoderCounterL;
    volatile uint32_t encoderCounterR;
    static RotaryEncoderManager* getInstance();
    void setupInterrupts(int encoderPinL, int encoderPinR);
    void clearCounts();

private:
    RotaryEncoderManager();
    static void isr_renc_L();
    static void isr_renc_R();
    static RotaryEncoderManager* instance;
};

#endif