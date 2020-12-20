#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSCONNECTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWSCONNECTION_H

#include "Connection.h"
#include <WinSock2.h>
#include <string>

namespace robotguide::com::transportlayer
{

	class WindowsConnection : public Connection
	{
	public:
		/// <summary>
		/// Initialize a connection
		/// </summary>
		/// <param name="socketHandler">The socket handler</param>
		/// <param name="receiveBufferSize">The size of the receive buffer</param>
		WindowsConnection(const SOCKET& socketHandler, unsigned int receiveBufferSize);
		~WindowsConnection() override = default;

		/// <summary>
		/// Disconnect from this connection
		/// </summary>
		void Disconnect() override;

		/// <summary>
		/// Send data to the connected application
		/// </summary>
		/// <param name="message">The message you want to send</param>
		void Send(const std::string& message) override;

		/// <summary>
		/// Returns if the connection is still connected
		/// </summary>
		/// <returns>If the connection is active</returns>
		bool IsConnected() const override;

		/// <summary>
		/// Add a received value to the buffer. This function should only be called when data is available.
		/// </summary>
		virtual void HandleAvailableData() override;
	};
}
#endif
