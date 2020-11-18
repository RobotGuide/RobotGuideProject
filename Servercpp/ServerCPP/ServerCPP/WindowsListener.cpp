#include "WindowsListener.h"
#include "SocketException.h"
#include <iostream>
#include <stdexcept>

WindowsListener::WindowsListener(const char* ipAddress, const char* port, addrinfo* type)
{
	if (port == nullptr)
	{
		throw std::invalid_argument("Port can not be null");
	}
	if (type == nullptr)
	{
		throw std::invalid_argument("Type can not be null");
	}
	address = nullptr;
	listenerSocket = INVALID_SOCKET;

	const int outcome = getaddrinfo(ipAddress, port, type, &address);
	if (outcome != 0) {
		WSACleanup();
		throw SocketException("Could not get address for these specific parameter");
	}
}

WindowsListener::~WindowsListener()
{
	freeaddrinfo(address);
	Stop();
}

void WindowsListener::Listen(const unsigned int maxConnections)
{
	if (maxConnections > SOMAXCONN)
	{
		throw std::invalid_argument("You can not have more than the max amount of connections");
	}

	listenerSocket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (listenerSocket == INVALID_SOCKET)
	{
		HandleFailure("Initialization of the socket failed");
	}

	int result = bind(listenerSocket, address->ai_addr, static_cast<int>(address->ai_addrlen));
	if (result == SOCKET_ERROR)
	{
		HandleFailure("Bind failed");
	}

	result = listen(listenerSocket, static_cast<int>(maxConnections));
	if (result == SOCKET_ERROR)
	{
		HandleFailure("Could not listen for connections");
	}
	u_long mode = 1;
	ioctlsocket(listenerSocket, FIONBIO, &mode);
}

int WindowsListener::Accept()
{
	if (listenerSocket == INVALID_SOCKET)
	{
		throw std::logic_error("You can not accept calls when you are not listening for connections");
	}
	const SOCKET handle = accept(listenerSocket, nullptr, nullptr);
	if (handle == WSAEWOULDBLOCK || handle == INVALID_SOCKET)
	{
		throw SocketException("No connection available");
	}
	return  handle;
}

void WindowsListener::Stop()
{
	if (listenerSocket != INVALID_SOCKET)
	{
		closesocket(listenerSocket);
		listenerSocket = INVALID_SOCKET;
	}
}

void WindowsListener::HandleFailure(const char* message)
{
	freeaddrinfo(address);
	Stop();
	WSACleanup();
	throw SocketException(message);
}

