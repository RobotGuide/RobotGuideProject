#include "WindowsConnection.h"
#include <stdexcept>

#include "SocketException.h"

WindowsConnection::WindowsConnection(const SOCKET socketHandler)
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

void WindowsConnection::Send(const char* message, const int length)
{
	if (message == nullptr)
	{
		throw std::invalid_argument("Message can not be null");
	}

	const int result = send(socket, message, length, 0);
	if (result == SOCKET_ERROR)
	{
		socket = INVALID_SOCKET;
		throw SocketException("Socket disconnected");
	}
	if (result == WSAEWOULDBLOCK)
	{
		throw SocketException("Send timed out");
	}
}

bool WindowsConnection::IsConnected() const
{
	return socket != INVALID_SOCKET;
}

