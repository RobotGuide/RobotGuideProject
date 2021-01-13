#include "robotguide/Communication/TransportLayer/WindowsUserConnection.h"

#include <iostream>

using namespace robotguide::com::transportlayer;

WindowsUserConnection::WindowsUserConnection(IRouteRequester& routeRequester,
	const SOCKET& socketHandler,
	const unsigned int receiveBufferSize)
	: WindowsConnection(socketHandler, receiveBufferSize)
	, routeRequester(routeRequester)
{
}

void WindowsUserConnection::HandleAvailableData()
{
	WindowsConnection::HandleAvailableData();
	routeRequester.HandleMessage(std::string(GetReceiveBuffer().GetBuffer()));
}

ISelectable* WindowsUserConnection::Copy() const
{
	return new WindowsUserConnection(*this);
}
