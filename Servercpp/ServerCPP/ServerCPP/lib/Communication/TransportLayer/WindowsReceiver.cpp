#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <WinSock2.h>

using namespace  robotguide::com::transportlayer;

void WindowsReceiver::ReceiveData(const std::vector<IConnection*>& connections)
{
	int activeSockets = GetAvailableSocketsCount(connections);
	for (IConnection* connection : connections)
	{
		if (FD_ISSET(connection->GetSocketHandle(), &ReadSet))
		{
			activeSockets--;
			ReceiveDataFromConnection(*connection);
		}
	}
}

int WindowsReceiver::GetAvailableSocketsCount(const std::vector<IConnection*>& connections)
{
	FD_ZERO(&ReadSet);
	struct timeval tv
	{
		0, 50
	};

	for (IConnection* connection : connections)
	{
		if (connection == nullptr)
		{
			throw std::invalid_argument("Connections can not be nullptr");
		}
		FD_SET(connection->GetSocketHandle(), &ReadSet);
	}

	return select(0, &ReadSet, nullptr, nullptr, &tv);
}

void WindowsReceiver::ReceiveDataFromConnection(IConnection& connection)
{
	WSABUF buffer;
	DWORD bytesReceived;
	DWORD Flags = 0;

	Buffer& receiveBuffer = connection.GetReceiveBuffer();
	receiveBuffer.Clear();

	buffer.buf = receiveBuffer.GetBuffer();
	buffer.len = receiveBuffer.GetMaxLength();

	const int value = WSARecv(connection.GetSocketHandle(), &buffer, 1, &bytesReceived, &Flags, nullptr, nullptr);
	if (value == SOCKET_ERROR || bytesReceived <= 0)
	{
		connection.Disconnect();
		return;
	}
	receiveBuffer.SetLength(bytesReceived);
	std::cout.write(receiveBuffer.GetBuffer(), receiveBuffer.GetLength());
	std::cout << std::endl;
}

