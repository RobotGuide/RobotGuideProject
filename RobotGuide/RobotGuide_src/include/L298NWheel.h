#ifndef ROBOTGUIDE_L298NWHEEL_H
#define ROBOTGUIDE_L298NWHEEL_H

#include <stdint.h>

enum class Direction
{
    FORWARD,
    BACKWARD
};

class L298NWheel
{
public:
    L298NWheel(
        uint8_t directionPin1,
        uint8_t directionPin2,
        uint8_t pwmPin);
    void setWheel(Direction direction, uint8_t power) const;
    void setWheelPower(uint8_t power) const;
    void setWheelDirection(Direction direction) const;
    void brake() const;
private:
    const uint8_t directionPin1_;
    const uint8_t directionPin2_;
    const uint8_t pwmPin_;
};

#endif