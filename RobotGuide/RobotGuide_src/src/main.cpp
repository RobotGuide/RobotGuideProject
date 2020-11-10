#include <Arduino.h>
#include "rotaryEncoders.h"
#include "movementManager.h"
#include "motorDriver.h"

//todo: see if you can make a universal interrupt dispatcher
//which would handle incoming interrupts, for example for rotary
//encoders
//class for bare motor driver?

//todo:
//-reorganise using class/sequence diagrams
//-make a base class for objects that need access to loop
//-make uart communications class that sends instructions
//-make header file for defines
//-add a timeout of executing instructions?

//TODO:
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

#define FORN "FORN"
#define BACN "BACN"
#define TULN "TULN"
#define TURN "TURN"

#define NAVS "NAVS\n"
#define NAVF "NAVF\n"

MotorDriver* motorDriver = NULL;
RotaryEncoders* rotaryEncoders = NULL;
MotorManager* motorManager = NULL;

bool responseSend = false;

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
  rotaryEncoders = rotaryEncoders->getInstance();
  rotaryEncoders->setupInterrupts(RENC_PIN_L, RENC_PIN_R);

  motorManager = new MotorManager(
    WHEEL_DIAMETER,
    PLATFORM_DIAMETER,
    ENCODER_DISK_TICS,
    rotaryEncoders,
    motorDriver);
};

void loop() {

  motorManager->loopTick();

  if(!motorManager->destinationReached())
  {
    return;
  }

  if(!responseSend)
  {
    Serial.print(NAVS);
    responseSend = true;
  }

  else if (Serial.available())
  {
    char msg[20];
    memset(msg, ' ', 20);

    size_t msgLength = Serial.readBytesUntil('\n', msg, 20);

    if(msgLength == 0)
    {
      Serial.print(NAVF);
      return;
    }

    //todo: move tokenization of instructions to separate class
    //also todo: actually tokenize instructions

    char* cmd = strtok(msg, " ");
    char* argc = strtok(NULL, " ");

    float arg = atof(argc);

    if(strcmp(cmd, FORN) == 0)
    {
      motorManager->move(arg);
      responseSend = false;
    }
    else if(strcmp(cmd, BACN) == 0)
    {
      motorManager->move(-arg);
      responseSend = false;
    }
    else if(strcmp(cmd, TURN) == 0)
    {
      motorManager->rotate(-arg);
      responseSend = false;
    }
    else if(strcmp(cmd, TULN) == 0)
    {
      motorManager->rotate(arg);
      responseSend = false;
    }
    else
    {
      Serial.print(NAVF);
    }     
  }
};