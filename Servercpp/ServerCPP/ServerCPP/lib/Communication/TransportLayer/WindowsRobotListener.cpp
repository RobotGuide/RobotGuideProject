#include "robotguide/Communication/TransportLayer/WindowsRobotListener.h"
#include "robotguide/Communication/TransportLayer/WindowsRobotConnection.h"
#include <stdexcept>
#include <iostream>

using namespace  robotguide::com::transportlayer;

WindowsRobotListener::WindowsRobotListener(Receiver& receiver, IRobotInstructor& robotInstructor, const std::string& ipAddress, const std::string& port, const addrinfo& type)
	: WindowsListener(ipAddress, port, type), receiver(receiver), robotInstructor(robotInstructor)
{
}

void WindowsRobotListener::HandleAvailableData()
{
	const SOCKET socketHandle = Accept();
	std::cout << "New robot connected: " << socketHandle << std::endl;
	WindowsRobotConnection robot(robotInstructor, socketHandle, 80);
	receiver.AddSelectable(robot);
	robot.Send("FORN 10");
}

ISelectable* WindowsRobotListener::Copy() const
{
	return new WindowsRobotListener(*this);
}
