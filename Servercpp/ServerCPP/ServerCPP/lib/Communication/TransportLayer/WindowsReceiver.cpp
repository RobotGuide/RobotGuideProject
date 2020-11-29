#include "robotguide/Communication/TransportLayer/WindowsReceiver.h"
#include "robotguide/Communication/TransportLayer/SocketException.h"
#include <vector>

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

	//Initialize sockets
	for (const std::shared_ptr<IConnection> connection : connections)
	{
		FD_SET(connection->GetSocketHandle(), &ReadSet);
	}

	int activeSockets = select(0, &ReadSet, nullptr, nullptr, nullptr);
	if (activeSockets == SOCKET_ERROR)
	{
		throw SocketException("Select failed to execute");
	}

	WSABUF buffer;
	DWORD bytesReceived;
	DWORD Flags;

	for (int i = 0; activeSockets > 0 && i < connections.size(); i++)
	{
		if (FD_ISSET(connections[i]->GetSocketHandle(), &ReadSet))
		{
			buffer.buf = connections[i]->GetReceiveBuffer();
			buffer.len = connections[i]->GetReceiveBufferSize();
			activeSockets--;
			Flags = 0;

			if (WSARecv(connections[i]->GetSocketHandle(), &buffer, 1, &bytesReceived, &Flags, nullptr, nullptr) == SOCKET_ERROR)
			{


			}
		}
	}
}
