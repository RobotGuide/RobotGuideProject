#include <Arduino.h>
#include "rotaryEncoderManager.h"
#include "movementManager.h"
#include "motorDriver.h"

//todo: see if you can make a universal interrupt dispatcher
//which would handle incoming interrupts, for example for rotary
//encoders
//class for bare motor driver?

//TODO:
//make function for setting left and right motors
//measure motor voltage with 8 batteries

//robot diameter:
//14.5cm -> 145mm
//robot circumference:
//455.53 ~> 456mm

#define DRIVER_ENA_PIN 10
#define DRIVER_ENB_PIN 11
#define DRIVER_IN1_PIN 9
#define DRIVER_IN2_PIN 8
#define DRIVER_IN3_PIN 12
#define DRIVER_IN4_PIN 13

#define MOTOR_SPEED 90

#define WHEEL_DIAMETER 70 //mm
#define PLATFORM_DIAMETER 125 //mm
#define ENCODER_DISK_TICS 40

#define RENC_PIN_L 2
#define RENC_PIN_R 3

MotorDriver* motorDriver = NULL;
RotaryEncoderManager* rencManager = NULL;
MotorManager* motorManager = NULL;

void setup() {
  Serial.begin(9600);

  motorDriver = new MotorDriver(
    DRIVER_IN1_PIN,
    DRIVER_IN2_PIN,
    DRIVER_IN3_PIN,
    DRIVER_IN4_PIN,
    DRIVER_ENA_PIN,
    DRIVER_ENB_PIN);

  //ugly! but necessary to get global interrupts to work
  //to be changed later
  rencManager = rencManager->getInstance();
  rencManager->setupInterrupts(RENC_PIN_L, RENC_PIN_R);

  motorManager = new MotorManager(
    WHEEL_DIAMETER,
    PLATFORM_DIAMETER,
    ENCODER_DISK_TICS,
    rencManager,
    motorDriver);

  // motorManager->move(200.0f);
  motorManager->rotate(90);
};

void loop() {
  motorManager->loopTick();

  if(motorManager->destinationReached())
  {
    delay(2000);
    motorManager->rotate(90);
  }
};