#include "UART.h"
#include "Constants.h"
#include <Arduino.h>

static const char* FORN = "FORN";
static const char* BACN = "BACN";
static const char* TULN = "TULN";
static const char* TURN = "TURN";

static const char* NAVS = "NAVS";
static const char* NAVF = "NAVF";

UART::UART(Navigator& navigator)
    : navigator(navigator)
    , nextUpdateTime(0)
    , delay(50)
{
    // do not call serial.begin from here
    // calling serial.begin from outside the Setup() function
    // will cause a crash
}

void UART::OnNavigationFinished(NavigatorStatus status)
{
    switch (status)
    {
    case NavigatorStatus::ARRIVED:
        SendSerialResponse(NAVS);
        break;

    case NavigatorStatus::BLOCKED:
        SendSerialResponse(NAVF);
        break;
    
    default:
        break;
    }
}

bool UART::NeedsUpdate(unsigned long time) const
{
    return (Serial.available() && time >= nextUpdateTime);
}

void UART::Update(unsigned long time)
{
    nextUpdateTime = time + delay;

    char msg[20];
    memset(msg, ' ', 20);

    size_t msgLength = Serial.readBytesUntil('\n', msg, 20);

    if(msgLength == 0)
    {
        SendSerialResponse(NAVF);
        return;
    }

    char* cmd = strtok(msg, " ");
    char* argc = strtok(NULL, " ");
    int arg = atoi(argc);

    Commands command = ParseStringToCommand(cmd);

    if(command == Commands::NOT_A_COMMAND || argc == NULL || arg == 0)
    {
        SendSerialResponse(NAVF);
        return;
    }

    ExecuteCommand(command, arg);
}

Commands UART::ParseStringToCommand(char* data)
{
    if(strcmp(data, FORN) == 0)
    {
        return Commands::FORN;
    }
    else if(strcmp(data, BACN) == 0)
    {
        return Commands::BACN;
    }
    else if(strcmp(data, TURN) == 0)
    {
        return Commands::TURN;
    }
    else if(strcmp(data, TULN) == 0)
    {
        return Commands::TULN;
    }
    else
    {
        return Commands::NOT_A_COMMAND;
    }
}

void UART::ExecuteCommand(Commands command, int arg)
{
    switch (command)
    {
    case Commands::FORN:
        navigator.MoveForward(arg, this);
        break;

    case Commands::BACN:
        navigator.MoveBackward(arg, this);
        break;

    case Commands::TULN:
        navigator.RotateLeft(arg, this);
        break;

    case Commands::TURN:
        navigator.RotateRight(arg, this);
        break;
    
    default:
        break;
    }
}

void UART::SendSerialResponse(const char* rsp) const
{
    char data[strlen(rsp) + 2];
    strcpy(data, rsp);
    strcat(data, "\n");

    Serial.print(data);
}