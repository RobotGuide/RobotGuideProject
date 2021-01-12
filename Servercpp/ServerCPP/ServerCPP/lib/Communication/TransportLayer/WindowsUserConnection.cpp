#include "robotguide/Communication/TransportLayer/WindowsUserConnection.h"

using namespace robotguide::com::transportlayer;

WindowsUserConnection::WindowsUserConnection(IRouteRequester& routeRequester,
	const SOCKET& socketHandler,
	unsigned int receiveBufferSize)
	: WindowsConnection(socketHandler, receiveBufferSize)
	, routeRequester(routeRequester)
{
}

void WindowsUserConnection::HandleAvailableData()
{
	WindowsConnection::HandleAvailableData();
	routeRequester.HandleMessage(std::string(GetReceiveBuffer().GetBuffer()));
}
