#include "robotguide/Communication/TransportLayer/WindowsRobotListener.h"

using namespace  robotguide::com::transportlayer;

WindowsRobotListener::WindowsRobotListener(IReceiver& receiver, IRobotInstructor& robotInstructor, const std::string& ipAddress, const std::string& port, const addrinfo& type)
	: WindowsListener(ipAddress, port, type), receiver(receiver), robotInstructor(robotInstructor)
{
}

void WindowsRobotListener::HandleAvailableData()
{
}
