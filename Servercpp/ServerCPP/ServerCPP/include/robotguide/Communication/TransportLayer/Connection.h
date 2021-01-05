#ifndef  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_CONNECTION_H
#define  ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_CONNECTION_H

#include "Buffer.h"
#include "ISelectable.h"
#include <string>

namespace robotguide::com::transportlayer
{
	class Connection : public ISelectable
	{
	private:
		Buffer receiveBuffer;

	protected:
		unsigned int socketHandle;

	public:

		/// <summary>
		/// Initialize the connection
		/// </summary>
		/// <param name="socketHandle">The socket handle for this connection</param>
		/// <param name="receiveBufferSize">The size of the receive buffer</param>
		Connection(unsigned int socketHandle, unsigned int receiveBufferSize);

		/// <summary>
		/// Destruct a connection
		/// </summary>
		~Connection() override = default;

		/// <summary>
		/// Returns the socket handler for this connection
		/// </summary>
		/// <returns>The socket handle for this connection</returns>
		unsigned int GetSocketHandle() const override;

		/// <summary>
		/// Send data to the connected application. This is a blocking function!
		/// </summary>
		/// <param name="message">The message you want to send</param>
		virtual void Send(const std::string& message) = 0;

		/// <summary>
		/// Get a reference to the buffer
		/// </summary>
		/// <returns>The buffer for this connection</returns>
		Buffer& GetReceiveBuffer();
	};
}

#endif
