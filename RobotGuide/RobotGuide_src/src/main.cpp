#include "rotaryEncoders.h"
#include "movement.h"
#include "L298NWheel.h"
#include <Arduino.h>

#define DRIVER_ENA_PIN 10
#define DRIVER_ENB_PIN 11
#define DRIVER_IN1_PIN 9
#define DRIVER_IN2_PIN 8
#define DRIVER_IN3_PIN 12
#define DRIVER_IN4_PIN 13

#define MOTOR_SPEED 90

#define WHEEL_DIAMETER 70     //mm
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

L298NWheel* leftWheel = NULL;
L298NWheel* rightWheel = NULL;
RotaryEncoders* rotaryEncoders = NULL;
Movement* movement = NULL;

bool responseSend = false;

void setup() {
  Serial.begin(9600);

  leftWheel = new L298NWheel(DRIVER_IN3_PIN, DRIVER_IN4_PIN, DRIVER_ENB_PIN);
  rightWheel = new L298NWheel(DRIVER_IN1_PIN, DRIVER_IN2_PIN, DRIVER_ENA_PIN);

  rotaryEncoders = rotaryEncoders->getInstance();
  rotaryEncoders->setupInterrupts(RENC_PIN_L, RENC_PIN_R);

  movement = new Movement(WHEEL_DIAMETER, PLATFORM_DIAMETER,
    ENCODER_DISK_TICS, rotaryEncoders, leftWheel, rightWheel);

  movement->move(1000);
};

void loop() {

  movement->loopTick();

  if(!movement->destinationReached())
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

    char* cmd = strtok(msg, " ");
    char* argc = strtok(NULL, " ");

    float arg = atof(argc);

    if(strcmp(cmd, FORN) == 0)
    {
      movement->move(arg);
      responseSend = false;
    }
    else if(strcmp(cmd, BACN) == 0)
    {
      movement->move(-arg);
      responseSend = false;
    }
    else if(strcmp(cmd, TURN) == 0)
    {
      movement->rotate(-arg);
      responseSend = false;
    }
    else if(strcmp(cmd, TULN) == 0)
    {
      movement->rotate(arg);
      responseSend = false;
    }
    else
    {
      Serial.print(NAVF);
    }     
  }
};