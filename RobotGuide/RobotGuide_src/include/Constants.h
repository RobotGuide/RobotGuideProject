#ifndef ROBOTGUIDE_CONSTANTS_H
#define ROBOTGUIDE_CONSTANTS_H

#include <stdint.h>

//these pins enable pwm input to the L298N motor driver
const int DRIVER_ENA_PIN = 10;
const int DRIVER_ENB_PIN = 11;

//these pins control the direction and mode of the
//L298N-controlled motors
const int DRIVER_IN1_PIN = 9;
const int DRIVER_IN2_PIN = 8;
const int DRIVER_IN3_PIN = 12;
const int DRIVER_IN4_PIN = 13;

//units are in millimeters
const int WHEEL_DIAMETER = 70;
const int PLATFORM_DIAMETER = 125;

const int ENCODER_DISK_TICS = 40;

const uint8_t MAX_MOTOR_POWER = 90;
const uint8_t TARGET_ERROR_BOUND = 0;

const float CONTROL_SIGNAL_PERCENTILE = 0.8f;
const float SIGNAL_CORRECTION_PERCENTILE = 0.2f;

const float INTEGRATOR_CUTOFF_BOUND = 0.5f;

//interrupt pins for rotary encoders
const int RENC_PIN_L = 2;
const int RENC_PIN_R = 3;

const int BAUDRATE = 9600;

#endif