#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <WinSock2.h>

using namespace  robotguide::com::transportlayer;

WindowsReceiver::WindowsReceiver()
{
}

WindowsReceiver::~WindowsReceiver()
{
}

void WindowsReceiver::ReceiveData(const std::vector<std::shared_ptr<IConnection>>& connections)
{
	int activeSockets = GetAvailableSocketsCount(connections);
	for (int i = 0; activeSockets > 0 && i < connections.size(); i++)
	{
		if (FD_ISSET(connections[i]->GetSocketHandle(), &ReadSet))
		{
			activeSockets--;
			ReceiveDataFromConnection(connections[i]);
		}
	}
}

int WindowsReceiver::GetAvailableSocketsCount(const std::vector<std::shared_ptr<IConnection>>& connections)
{
	FD_ZERO(&ReadSet);
	struct timeval tv
	{
		0, 50
	};

	for (const std::shared_ptr<IConnection>& connection : connections)
	{
		FD_SET(connection->GetSocketHandle(), &ReadSet);
	}

	return select(0, &ReadSet, nullptr, nullptr, &tv);
}

void WindowsReceiver::ReceiveDataFromConnection(const std::shared_ptr<IConnection>& connection)
{
	WSABUF buffer;
	DWORD bytesReceived;
	DWORD Flags = 0;

	Buffer& receiveBuffer = connection->GetReceiveBuffer();
	receiveBuffer.Clear();

	buffer.buf = receiveBuffer.GetBuffer();
	buffer.len = receiveBuffer.GetMaxLength();

	const int value = WSARecv(connection->GetSocketHandle(), &buffer, 1, &bytesReceived, &Flags, nullptr, nullptr);
	if (value == SOCKET_ERROR || bytesReceived <= 0)
	{
		connection->Disconnect();
		return;
	}
	receiveBuffer.SetLength(bytesReceived);
}

