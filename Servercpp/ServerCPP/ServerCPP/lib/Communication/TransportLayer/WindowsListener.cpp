#include "robotguide/Communication/TransportLayer/WindowsListener.h"
#include "robotguide/Communication/TransportLayer/SocketInitializationException.h"
#include "robotguide/Communication/TransportLayer/SocketException.h"
#include <iostream>
#include <stdexcept>
#include <WS2tcpip.h>

using namespace robotguide::com::transportlayer;

WindowsListener::WindowsListener(const std::string& ipAddress, const std::string& port, const addrinfo& type)
{
	address = nullptr;
	listenerSocket = INVALID_SOCKET;

	const int outcome = getaddrinfo(ipAddress.c_str(), port.c_str(), &type, &address);
	if (outcome != 0) {
		WSACleanup();
		throw SocketInitializationException("Could not get address for these specific parameter");
	}
}

WindowsListener::~WindowsListener()
{
	freeaddrinfo(address);
	Stop();
}

void WindowsListener::Listen(const unsigned maxConnections)
{
	if (maxConnections > SOMAXCONN)
	{
		throw std::invalid_argument("You can not have more than the max amount of connections");
	}

	try
	{
		InitializeListenerSocket();
		BindListenerSocket();
		ListenOnSocket(maxConnections);
		SetSocketToNonBlockingMode();
	}
	catch (SocketException&)
	{
		freeaddrinfo(address);
		Stop();
		WSACleanup();
		throw;
	}
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
		throw SocketInitializationException("No connection available");
	}
	return handle;
}

void WindowsListener::Stop()
{
	if (listenerSocket != INVALID_SOCKET)
	{
		closesocket(listenerSocket);
		listenerSocket = INVALID_SOCKET;
	}
}


void WindowsListener::InitializeListenerSocket()
{
	listenerSocket = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (listenerSocket == INVALID_SOCKET)
	{
		throw SocketInitializationException("Initialization of the socket failed");
	}
}

void WindowsListener::BindListenerSocket() const
{
	const int result = bind(listenerSocket, address->ai_addr, address->ai_addrlen);
	if (result == SOCKET_ERROR)
	{
		throw SocketInitializationException("Bind address on socket failed");
	}
}

void WindowsListener::ListenOnSocket(const unsigned maxConnections) const
{
	const int result = listen(listenerSocket, maxConnections);
	if (result == SOCKET_ERROR)
	{
		throw SocketInitializationException("Could not listen for connections");
	}
}

void WindowsListener::SetSocketToNonBlockingMode() const
{
	u_long mode = 1;
	ioctlsocket(listenerSocket, FIONBIO, &mode);
}

