#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWS_CONNECTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_WINDOWS_CONNECTION_H

#include "IConnection.h"
#include <WinSock2.h>
#include <string>

namespace robotguide::com::transportlayer
{

	class WindowsConnection final : public IConnection
	{
	private:
		SOCKET socket;
		Buffer receiveBuffer;

	public:
		/// <summary>
		/// Initialize a connection
		/// </summary>
		/// <param name="socketHandler">The socket handler</param>
		/// <param name="receiveBufferSize">The size of the receive buffer</param>
		WindowsConnection(const SOCKET& socketHandler, int receiveBufferSize);

		~WindowsConnection() override;

		/// <summary>
		/// Get the socket handler for this windows connection
		/// </summary>
		/// <returns>The socket handle</returns>
		int GetSocketHandle() const override;

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
		/// Get a reference to the buffer
		/// </summary>
		/// <returns>The buffer for this connection</returns>
		Buffer& GetReceiveBuffer() override;

		/// <summary>
		/// Add a received value to the buffer. This function should only be called when data is available.
		/// </summary>
		void HandleData() override;
	};
}
#endif
