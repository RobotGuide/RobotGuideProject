#include "L298NWheel.h"

#include <Arduino.h>

L298NWheel::L298NWheel(uint8_t directionPin1, uint8_t directionPin2, uint8_t pwmPin)
    :directionPin1_(directionPin1), directionPin2_(directionPin2), pwmPin_(pwmPin)
{
    pinMode(directionPin1_, OUTPUT);
    pinMode(directionPin2_, OUTPUT);
    pinMode(pwmPin_, OUTPUT);
}

void L298NWheel::setWheel(Direction direction, uint8_t power) const
{
    setWheelDirection(direction);
    setWheelPower(power);
}

void L298NWheel::setWheelDirection(Direction direction) const
{
    switch (direction)
    {
    case Direction::FORWARD:
        digitalWrite(directionPin1_, LOW);
        digitalWrite(directionPin2_, HIGH);
        break;

    case Direction::BACKWARD:
        digitalWrite(directionPin1_, HIGH);
        digitalWrite(directionPin2_, LOW);
        break;
    }  
}

void L298NWheel::setWheelPower(uint8_t power) const
{
    analogWrite(pwmPin_, power);
}

void L298NWheel::brake() const
{
    digitalWrite(directionPin1_, LOW);
    digitalWrite(directionPin2_, LOW);
    analogWrite(pwmPin_, 255);
}