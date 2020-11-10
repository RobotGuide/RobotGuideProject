#ifndef ROTARY_ENCODER_MANAGER
#define ROTARY_ENCODER_MANAGER

#include <Arduino.h>

class RotaryEncoders
{
public:
    volatile uint32_t encoderCounterL;
    volatile uint32_t encoderCounterR;
    static RotaryEncoders* getInstance();
    void setupInterrupts(int encoderPinL, int encoderPinR);
    void clearCounts();

private:
    RotaryEncoders();
    static void isr_renc_L();
    static void isr_renc_R();
    static RotaryEncoders* instance;
};

#endif