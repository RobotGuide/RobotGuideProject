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
	/// <summary>
	/// Initialize a connection
	/// </summary>
	/// <param name="socketHandler">The socket handler</param>
	WindowsConnection(const SOCKET socketHandler);

	~WindowsConnection() override;

	/// <summary>
	/// Get the socket handler for this windows connection
	/// </summary>
	/// <returns>The socket handle</returns>
	int GetSocketHandle() const override;

	/// <summary>
	/// Send data to the connected application
	/// </summary>
	/// <param name="message">The message you want to send</param>
	/// <param name="length">The length of the message</param>
	void Send(const char* message, const int length) override;

	/// <summary>
	/// Returns if the connection is still connected
	/// </summary>
	/// <returns>If the connection is active</returns>
	bool IsConnected() const override;

};

#endif
