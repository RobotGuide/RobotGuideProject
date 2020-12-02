#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_CONNECTION_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_CONNECTION_H

#include <string>

namespace robotguide::com::transportlayer
{
	class IConnection
	{
	public:

		/// <summary>
		/// Destruct a connection
		/// </summary>
		virtual ~IConnection() = default;

		/// <summary>
		/// Returns the socket handler for this connection
		/// </summary>
		/// <returns>The socket handle for this connection</returns>
		virtual int GetSocketHandle() const = 0;

		/// <summary>
		/// Send data to the connected application
		/// </summary>
		/// <param name="message">The message you want to send</param>
		virtual void Send(const std::string& message) = 0;

		/// <summary>
		/// Disconnect from this connection
		/// </summary>
		virtual void Disconnect() = 0;

		/// <summary>
		/// Returns if the connection is still connected
		/// </summary>
		/// <returns>If the connection is active</returns>
		virtual bool IsConnected() const = 0;


		/// <summary>
		/// Get the buffer length
		/// </summary>
		/// <returns>The length of the buffer</returns>
		virtual int GetReceiveBufferSize() const = 0;

		/// <summary>
		/// Get a pointer to the buffer
		/// </summary>
		/// <returns>The buffer for this connection</returns>
		virtual char* GetReceiveBuffer() const = 0;


		/// <summary>
		/// Set the last package received bytes;
		/// </summary>
		virtual void SetBytesReceived(const int bytesReceived) = 0;

	};
}

#endif
