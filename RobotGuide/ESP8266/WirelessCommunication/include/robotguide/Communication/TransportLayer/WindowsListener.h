#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWS_RECEIVER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWS_RECEIVER_H

#include "IListener.h"
#include <string>
#include <WinSock2.h>

namespace robotguide::com::transportlayer
{
	class WindowsListener final : public IListener
	{
	public:
		/// <summary>
		/// Initialize a windows listener
		/// </summary>
		/// <param name="ipAddress">The ip address you want to listen on</param>
		/// <param name="port">The port you want to listen on</param>
		/// <param name="type">The address types. This includes the protocol and other things.</param>
		WindowsListener(const std::string& ipAddress, const std::string& port, const addrinfo& type);

		~WindowsListener() override;

		/// <summary>
		/// Start listening for connections
		/// </summary>
		/// <param name="maxConnections">The max amount of connections this socket will accept</param>
		void Listen(unsigned maxConnections) override;

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
}}}

#endif
