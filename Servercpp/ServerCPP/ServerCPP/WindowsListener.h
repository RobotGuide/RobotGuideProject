#ifndef WINDOWS_RECEIVER_H
#define WINDOWS_RECEIVER_H
#undef  UNICODE
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "Ws2_32.lib")


#include "IListener.h"
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

class WindowsListener final : public IListener
{
public:
	WindowsListener(const char* ipAddress, const char* port, addrinfo* type);
	~WindowsListener() override ;

	void Listen(unsigned int maxConnections) override;
	void Stop() override;

private:
	addrinfo* address;
	SOCKET listenerSocket;
};

#endif
