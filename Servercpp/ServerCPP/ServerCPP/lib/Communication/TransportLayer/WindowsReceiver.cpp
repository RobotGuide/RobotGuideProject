#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <WinSock2.h>

using namespace  robotguide::com::transportlayer;


void WindowsReceiver::ReceiveDataFromConnection(Connection& connection)
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

void WindowsReceiver::CheckForData()
{
	SetFDSet();
	for (ISelectable* selectable : selectables)
	{
		if (FD_ISSET(selectable->GetSocketHandle(), &ReadSet))
		{
			selectable->HandleAvailableData();
		}
	}
}

void WindowsReceiver::AddSelectable(ISelectable* socket)
{
	selectables.push_back(new ISelectable(socket));
}

void WindowsReceiver::Clean()
{
	auto iterator = selectables.begin();
	while (iterator != selectables.end())
	{
		if (!(*iterator)->IsConnected())
		{
			ISelectable* temp = *iterator;
			iterator = selectables.erase(iterator);
			delete temp;
			temp = nullptr;
		}
	}
}

int WindowsReceiver::SetFDSet()
{
	FD_ZERO(&ReadSet);
	struct timeval tv
	{
		0, 50
	};

	for (ISelectable* selectable : selectables)
	{
		FD_SET(selectable->GetSocketHandle(), &ReadSet);
	}

	return select(0, &ReadSet, nullptr, nullptr, &tv);
}
