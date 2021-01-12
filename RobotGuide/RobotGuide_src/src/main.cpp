#include "RotaryEncoders.h"
#include "Movement.h"
#include "L298NWheel.h"
#include "UART.h"
#include "Navigator.h"
#include "Constants.h"
#include <Arduino.h>

L298NWheel leftWheel(DRIVER_IN3_PIN, DRIVER_IN4_PIN, DRIVER_ENB_PIN);
L298NWheel rightWheel(DRIVER_IN1_PIN, DRIVER_IN2_PIN, DRIVER_ENA_PIN);

PIDcontroller leftPID(2.0f, 0.01f, 0.5f);
PIDcontroller rightPID(2.0f, 0.01f, 0.5f);
PIDcontroller deltaPID(4.0f, 0.0f, 0.1f);

Movement movement(WHEEL_DIAMETER,
                 PLATFORM_DIAMETER,
                 ENCODER_DISK_TICS,
                 CONTROL_SIGNAL_PERCENTILE,
                 SIGNAL_CORRECTION_PERCENTILE,
                 INTEGRATOR_CUTOFF_BOUND,
                 MAX_MOTOR_POWER,
                 TARGET_ERROR_BOUND,
                 RotaryEncoders::getInstance(), 
                 leftWheel,
                 rightWheel,
                 leftPID,
                 rightPID,
                 deltaPID);

ObstacleDetection obstacles;

Navigator navigator(movement, obstacles);

UART uart(navigator);

void setup()
{
  Serial.setTimeout(10);
  Serial.begin(BAUDRATE);
  deltaPID.integratorEnabled(false);
};

void loop()
{
  unsigned long time = millis();

  if(uart.NeedsUpdate(time))
  {
    uart.Update(time);
  }

  if(navigator.NeedsUpdate(time))
  {
    navigator.Update(time);
  }

  if(movement.NeedsUpdate(time))
  {
    movement.Update(time);
  }
};