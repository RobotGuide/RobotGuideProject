#include "robotguide/Communication/TransportLayer/WindowsConnection.h"
#include "robotguide/Communication/TransportLayer/SocketDisconnectedException.h"
#include "robotguide/Communication/TransportLayer/SocketTimeOutException.h"
#include <stdexcept>

using namespace robotguide::com::transportlayer;

WindowsConnection::WindowsConnection(const SOCKET& socketHandler, const unsigned int receiveBufferSize)
	: socket(socketHandler), Connection(receiveBufferSize)
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
	socket = INVALID_SOCKET;
}

void WindowsConnection::Send(const std::string& message)
{
	const int result = send(socket, message.c_str(), message.length(), 0);
	if (result == SOCKET_ERROR)
	{
		socket = INVALID_SOCKET;
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			throw SocketTimeOutException("Sent timed out");
		}
		throw SocketDisconnectedException("Socket disconnected");
	}
}

bool WindowsConnection::IsConnected() const
{
	return socket != INVALID_SOCKET;
}

void WindowsConnection::HandleAvailableData()
{
	WSABUF wsaBuffer;
	DWORD bytesReceived;
	DWORD Flags = 0;

	GetReceiveBuffer().Clear();

	wsaBuffer.buf = GetReceiveBuffer().GetBuffer();
	wsaBuffer.len = GetReceiveBuffer().GetMaxLength();

	const int value = WSARecv(GetSocketHandle(), &wsaBuffer, 1, &bytesReceived, &Flags, nullptr, nullptr);
	if (value == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAEWOULDBLOCK)
		{
			throw SocketTimeOutException("Socked would have timed out");
		}
		GetReceiveBuffer().Clear();
		return;
	}
	else if (bytesReceived <= 0)
	{
		Disconnect();
		GetReceiveBuffer().Clear();
		return;
	}
	GetReceiveBuffer().SetLength(bytesReceived);
}

