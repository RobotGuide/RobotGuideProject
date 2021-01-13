#ifndef ROBOTGUIDE_UARTCOMMANDPARSER_H
#define ROBOTGUIDE_UARTCOMMANDPARSER_H

#include "ILoopComponent.h"
#include "INavigatorCallback.h"
#include "Navigator.h"
#include "Commands.h"

class UARTCommandParser : ILoopComponent, INavigatorCallback
{
public:
    UARTCommandParser(Navigator& navigator, unsigned int delay);
    UARTCommandParser(const UARTCommandParser& other) = delete;
    UARTCommandParser& operator=(const UARTCommandParser&) = delete;
    ~UARTCommandParser() override = default;

    void OnNavigationFinished(NavigatorStatus status) override;

    bool NeedsUpdate(unsigned long time) const override;
    void Update(unsigned long time) override;

private:
    Navigator& navigator;
    unsigned long nextUpdateTime;
    const unsigned int delay;

    Commands ParseStringToCommand(char* data);
    void ExecuteCommand(Commands command, int arg);
    void SendSerialResponse(const char* rsp) const;
};

#endif