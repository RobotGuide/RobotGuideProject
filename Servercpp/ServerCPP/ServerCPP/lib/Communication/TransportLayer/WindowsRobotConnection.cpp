#include "robotguide/Communication/TransportLayer/WindowsRobotConnection.h"


#include <iostream>
#include <ostream>

using namespace robotguide::com::transportlayer;

WindowsRobotConnection::WindowsRobotConnection(IRobotInstructor& robotInstructor, const SOCKET& socketHandler, unsigned int receiveBufferSize)
	: robotInstructor(robotInstructor), WindowsConnection(socketHandler, receiveBufferSize)
{
}

void WindowsRobotConnection::HandleAvailableData()
{
	WindowsConnection::HandleAvailableData();

	std::cout.write(GetReceiveBuffer().GetBuffer(), GetReceiveBuffer().GetLength());
	std::cout << std::endl;
}
