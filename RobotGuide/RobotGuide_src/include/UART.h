#ifndef ROBOTGUIDE_UART_H
#define ROBOTGUIDE_UART_H

#include "ILoopComponent.h"
#include "INavigatorCallback.h"
#include "Navigator.h"

enum class Commands
{
    FORN,
    BACN,
    TULN,
    TURN,
    NOT_A_COMMAND
};

class UART : ILoopComponent, INavigatorCallback
{
public:
    UART(Navigator& navigator);
    UART(const UART& other) = delete;
    UART& operator=(const UART&) = delete;
    ~UART() override = default;

    void OnNavigationFinished(NavigatorStatus status) override;

    bool NeedsUpdate(unsigned long time) const override;
    void Update(unsigned long time) override;

private:
    Navigator& navigator;
    unsigned long nextUpdateTime;
    const int delay;

    Commands ParseStringToCommand(char* data);
    void ExecuteCommand(Commands command, int arg);
    void SendSerialResponse(const char* rsp) const;
};

#endif