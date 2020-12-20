#include "robotguide/Communication/TransportLayer/WindowsRobotListener.h"
#include <stdexcept>

using namespace  robotguide::com::transportlayer;

WindowsRobotListener::WindowsRobotListener(Receiver& receiver, IRobotInstructor& robotInstructor, const std::string& ipAddress, const std::string& port, const addrinfo& type)
	: WindowsListener(ipAddress, port, type), receiver(receiver), robotInstructor(robotInstructor)
{
}

void WindowsRobotListener::HandleAvailableData()
{

}
