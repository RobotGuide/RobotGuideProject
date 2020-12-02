#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include "robotguide/Communication/TransportLayer/SocketException.h"
#include <vector>
#include <iostream>
#include <winsock2.h>
#include <windows.h>

using namespace  robotguide::com::transportlayer;

WindowsReceiver::WindowsReceiver()
{
}

WindowsReceiver::~WindowsReceiver()
{
}

void WindowsReceiver::ReceiveData(const std::vector<std::shared_ptr<IConnection>>& connections)
{
	FD_ZERO(&ReadSet);
	struct timeval tv
	{
		5, 0
	};

	//Initialize sockets
	for (const std::shared_ptr<IConnection> connection : connections)
	{
		FD_SET(connection->GetSocketHandle(), &ReadSet);
	}

	int activeSockets = connections.size();/*select(0, &ReadSet, nullptr, nullptr, nullptr);
	if (activeSockets == SOCKET_ERROR)
	{
		throw SocketException("Select failed to execute");
	}*/

	WSABUF buffer;
	DWORD bytesReceived;
	DWORD Flags = 0;


	for (int i = 0; activeSockets > 0 && i < connections.size(); i++)
	{
		/*if (FD_ISSET(connections[i]->GetSocketHandle(), &ReadSet))
		{*/
		buffer.buf = connections[i]->GetReceiveBuffer();
		buffer.len = connections[i]->GetReceiveBufferSize();
		activeSockets--;

		const int value = WSARecv(connections[i]->GetSocketHandle(), &buffer, 1, &bytesReceived, &Flags, nullptr, nullptr);
		if (value == SOCKET_ERROR)
		{
			//connections[i]->Disconnect();
		}
		else if (value != WSAEWOULDBLOCK)
		{
			connections[i]->SetBytesReceived(bytesReceived);
			if (bytesReceived <= 0)
			{
				connections[i]->Disconnect();
			}
			else
			{
				std::cout.write(connections[i]->GetReceiveBuffer(), bytesReceived);
				std::cout << std::endl;
			}
		}
		//}
	}
}
