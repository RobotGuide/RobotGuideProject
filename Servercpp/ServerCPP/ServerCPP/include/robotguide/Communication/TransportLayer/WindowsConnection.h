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
		char* receiveBuffer;
		const int receiveBufferLength;
		int bytesReceived;

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
		/// Get the buffer length
		/// </summary>
		/// <returns>The length of the buffer</returns>
		int GetReceiveBufferSize() const override;

		/// <summary>
		/// Get a pointer to the buffer
		/// </summary>
		/// <returns>The buffer for this connection</returns>
		char* GetReceiveBuffer() const override;

		/// <summary>
		/// Set the last package received bytes;
		/// </summary>
		void SetBytesReceived(const int bytesReceived) override;

	};
}
#endif
