#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ISOCKET_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ISOCKET_H

namespace robotguide::com::transportlayer
{
	class ISocket
	{
	private:
	public:
		/// <summary>
		/// Destruct a socket
		/// </summary>
		virtual ~ISocket() = default;

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
		/// Get the socket handle of this socket
		/// </summary>
		/// <returns>The socket handle for this connection</returns>
		virtual unsigned int GetSocketHandle() const = 0;
	};
}


#endif
