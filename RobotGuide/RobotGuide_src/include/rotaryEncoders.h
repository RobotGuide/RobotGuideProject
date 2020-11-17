#ifndef ROBOTGUIDE_ROTARYENCODERS_H
#define ROBOTGUIDE_ROTARYENCODERS_H

class RotaryEncoders
{
public:
    static RotaryEncoders* getInstance();
    void setupInterrupts(int encoderPinL, int encoderPinR);
    void clearCounts();
    unsigned long getEncoderCountL() const;
    unsigned long getEncoderCountR() const; 

private:
    RotaryEncoders();
    static RotaryEncoders* instance;
    static void isr_renc_L();
    static void isr_renc_R();
    volatile unsigned long encoderCounterL;
    volatile unsigned long encoderCounterR;
};

#endif