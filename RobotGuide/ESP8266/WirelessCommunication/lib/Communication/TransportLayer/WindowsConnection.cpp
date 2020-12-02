#include "robotguide/Communication/TransportLayer/WindowsConnection.h"
#include "robotguide/Communication/TransportLayer/SocketDisconnectException.h"
#include "robotguide/Communication/TransportLayer/SocketTimeOutException.h"
#include <stdexcept>

using namespace robotguide::com::transportlayer;

WindowsConnection::WindowsConnection(const SOCKET& socketHandler)
{
	socket = socketHandler;
}

WindowsConnection::~WindowsConnection()
{
	closesocket(socket);
};

int WindowsConnection::GetSocketHandle() const
{
	return socket;
}

void WindowsConnection::Send(const std::string& message)
{
	const int result = send(socket, message.c_str(), message.length(), 0);
	if (result == SOCKET_ERROR)
	{
		socket = INVALID_SOCKET;
		throw SocketDisconnectException("Socket disconnected");
	}
	if (result == WSAEWOULDBLOCK)
	{
		throw SocketTimeOutException("Sent timed out");
	}
}

bool WindowsConnection::IsConnected() const
{
	return socket != INVALID_SOCKET;
}

