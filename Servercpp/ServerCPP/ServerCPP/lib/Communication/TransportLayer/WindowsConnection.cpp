#include "robotguide/Communication/TransportLayer/WindowsConnection.h"
#include "robotguide/Communication/TransportLayer/SocketDisconnectException.h"
#include "robotguide/Communication/TransportLayer/SocketTimeOutException.h"
#include <stdexcept>

using namespace robotguide::com::transportlayer;

WindowsConnection::WindowsConnection(const SOCKET& socketHandler, const int receiveBufferSize)
	: socket(socketHandler), receiveBuffer(receiveBufferSize)
{
	u_long mode = 1;
	ioctlsocket(socketHandler, FIONBIO, &mode);
}

WindowsConnection::~WindowsConnection()
{
	Disconnect();
};

int WindowsConnection::GetSocketHandle() const
{
	return socket;
}

void WindowsConnection::Disconnect()
{
	closesocket(socket);
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

Buffer& WindowsConnection::GetReceiveBuffer()
{
	return receiveBuffer;
}

