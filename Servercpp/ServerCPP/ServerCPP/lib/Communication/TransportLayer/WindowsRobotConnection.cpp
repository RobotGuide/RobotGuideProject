#include "robotguide/Communication/TransportLayer/WindowsRobotConnection.h"
#include <iostream>
#include <ostream>

using namespace robotguide::com::transportlayer;

#define INVALID_ID -1

WindowsRobotConnection::WindowsRobotConnection(IRobotInstructor& robotInstructor, const SOCKET& socketHandler, const unsigned int receiveBufferSize)
	: WindowsConnection(socketHandler, receiveBufferSize), robotInstructor(robotInstructor), robotID(INVALID_ID)
{
}

void WindowsRobotConnection::HandleAvailableData()
{
	WindowsConnection::HandleAvailableData();

	std::string message(GetReceiveBuffer().GetBuffer());

	if (robotID == INVALID_ID)
	{
		//Use Parser
	}
	else
	{
		// Pass message to robot
	}

	std::cout.write(GetReceiveBuffer().GetBuffer(), GetReceiveBuffer().GetLength());
	std::cout << std::endl;
}

ISelectable* WindowsRobotConnection::Copy() const
{
	return new WindowsRobotConnection(*this);
}
