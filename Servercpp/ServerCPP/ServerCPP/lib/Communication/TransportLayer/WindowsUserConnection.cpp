#include "robotguide/Communication/TransportLayer/WindowsUserConnection.h"

using namespace robotguide::com::transportlayer;

WindowsUserConnection::WindowsUserConnection(IRouteRequester& routeRequester, const SOCKET& socketHandler, unsigned int receiveBufferSize)
	: routeRequester(routeRequester), WindowsConnection(socketHandler, receiveBufferSize)
{
}

void WindowsUserConnection::HandleAvailableData()
{
}
