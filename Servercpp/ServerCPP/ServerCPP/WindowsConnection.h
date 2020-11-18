#ifndef  WINDOWS_CONNECTION_H
#define WINDOWS_CONNECTION_H

#undef  UNICODE
#define WIN32_LEAN_AND_MEAN

#include "IConnection.h"
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

class WindowsConnection final : public IConnection
{
private:
	SOCKET socket;

public:
	WindowsConnection(const SOCKET socketHandler);
	~WindowsConnection() override;

	int GetSocketHandle() const override;
	void Send(const char* message, const int length) override;
	bool IsConnected() const override;

};

#endif
