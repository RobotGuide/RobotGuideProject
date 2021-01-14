#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSLISTENER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSLISTENER_H

#include "IListener.h"
#include "Receiver.h"
#include <string>
#include <WinSock2.h>

namespace robotguide::com::transportlayer
{
	class WindowsListener : public IListener
	{
	private:
		addrinfo* address;
		unsigned int listenerSocket;

	public:
		/// <summary>
		/// Initialize a windows listener
		/// </summary>
		/// <param name="ipAddress">The ip address you want to listen on</param>
		/// <param name="port">The port you want to listen on</param>
		/// <param name="type">The address types. This includes the protocol and other things.</param>
		WindowsListener(const std::string& ipAddress, const std::string& port, const addrinfo& type);

		~WindowsListener() override;
		WindowsListener(const WindowsListener& listener);
		WindowsListener& operator=(const WindowsListener& listener);

		/// <summary>
		/// Start listening for connections
		/// </summary>
		/// <param name="maxConnections">The max amount of connections this socket will accept</param>
		void Listen(unsigned maxConnections) override;

		/// <summary>
		/// Check if the socket is currently listening for data
		/// </summary>
		/// <returns>Activity state</returns>
		bool IsConnected() const override;

		/// <summary>
		/// Accept a pending connection
		/// </summary>
		/// <returns>It returns the socket handler</returns>
		int Accept() override;

		/// <summary>
		/// Stop listening for connections
		/// </summary>
		void Disconnect() override;

		/// <summary>
		/// Get the socket handle for this listener
		/// </summary>
		/// <returns>The socket handle</returns>
		unsigned int GetSocketHandle() const override;

	private:
		/// <summary>
		/// Initialize the listener socket
		/// </summary>
		void InitializeListenerSocket();

		/// <summary>
		/// Bind a socket to your address
		/// </summary>
		void BindListenerSocket() const;

		/// <summary>
		/// Start listening for connections
		/// </summary>
		/// <param name="maxConnections">The maximum connections</param>
		void ListenOnSocket(unsigned maxConnections) const;

		/// <summary>
		/// Set the socket to non blocking mode
		/// </summary>
		void SetSocketToNonBlockingMode() const;
	};
}

#endif
