#include "robotguide/Communication/TransportLayer/WindowsUserListener.h"
#include "robotguide/Communication/TransportLayer/WindowsUserConnection.h"
#include <stdexcept>
#include <iostream>

using namespace  robotguide::com::transportlayer;

WindowsUserListener::WindowsUserListener(Receiver& receiver,
	IRouteRequester& routeRequester,
	const std::string& ipAddress,
	const std::string& port,
	const addrinfo& type)
	: WindowsListener(ipAddress, port, type)
	, receiver(receiver)
	, routeRequester(routeRequester)
{
}

void WindowsUserListener::HandleAvailableData()
{
	const SOCKET socketHandle = Accept();
	std::cout << "New user connected: " << socketHandle << std::endl;
	receiver.AddSelectable(WindowsUserConnection(routeRequester, socketHandle, 200));
}

ISelectable* WindowsUserListener::Copy() const
{
	return new WindowsUserListener(*this);
}
