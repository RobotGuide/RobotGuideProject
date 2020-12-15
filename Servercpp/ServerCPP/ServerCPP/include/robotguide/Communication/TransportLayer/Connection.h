#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_CONNECTION_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_CONNECTION_H

#include "Buffer.h"
#include "ISocket.h"
#include <string>

namespace robotguide::com::transportlayer
{
	class Connection : public ISocket
	{
	private:
		Buffer receiveBuffer;
	public:

		/// <summary>
		/// Initialize the connection
		/// </summary>
		/// <param name="receiveBufferSize"></param>
		Connection(unsigned int receiveBufferSize);

		/// <summary>
		/// Destruct a connection
		/// </summary>
		virtual ~Connection() = default;

		/// <summary>
		/// Returns the socket handler for this connection
		/// </summary>
		/// <returns>The socket handle for this connection</returns>
		virtual int GetSocketHandle() const = 0;

		/// <summary>
		/// Send data to the connected application. This is a blocking function!
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
		/// Get a reference to the buffer
		/// </summary>
		/// <returns>The buffer for this connection</returns>
		Buffer& GetReceiveBuffer();
	};
}

#endif
