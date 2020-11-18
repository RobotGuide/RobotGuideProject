#ifndef WINDOWS_RECEIVER_H
#define WINDOWS_RECEIVER_H

#include "IListener.h"
#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>

/// <summary>
/// A listener for Windows
/// </summary>
class WindowsListener final : public IListener
{
public:
	/// <summary>
	/// Initialize a windows listener
	/// </summary>
	/// <param name="ipAddress">The ip address you want to listen on</param>
	/// <param name="port">The port you want to listen on</param>
	/// <param name="type">The address types. This includes the protocol and other things.</param>
	WindowsListener(const char* ipAddress, const char* port, addrinfo* type);

	~WindowsListener() override;

	/// <summary>
	/// Start listening for connections
	/// </summary>
	/// <param name="maxConnections">The max amount of connections this socket will accept</param>
	void Listen(unsigned int maxConnections) override;

	/// <summary>
	/// Accept a pending connection
	/// </summary>
	/// <returns>It returns the socket handler</returns>
	int Accept() override;

	/// <summary>
	/// Stop listening for connections
	/// </summary>
	void Stop() override;

private:
	addrinfo* address;
	SOCKET listenerSocket;

	/// <summary>
	/// Handle errors of the server
	/// </summary>
	/// <param name="message">The error message</param>
	void HandleFailure(const char* message);
};

#endif
