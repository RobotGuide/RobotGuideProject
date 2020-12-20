#include "robotguide/Communication/TransportLayer/WindowsRobotConnection.h"
#include <iostream>
#include <ostream>

using namespace robotguide::com::transportlayer;

WindowsRobotConnection::WindowsRobotConnection(IRobotInstructor& robotInstructor, const SOCKET& socketHandler, const unsigned int receiveBufferSize)
	: WindowsConnection(socketHandler, receiveBufferSize), robotInstructor(robotInstructor)
{
}

void WindowsRobotConnection::HandleAvailableData()
{
	WindowsConnection::HandleAvailableData();

	std::cout.write(GetReceiveBuffer().GetBuffer(), GetReceiveBuffer().GetLength());
	std::cout << std::endl;
}

ISelectable* WindowsRobotConnection::Copy() const
{
	return new WindowsRobotConnection(*this);
}
