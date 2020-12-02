#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ILISTENER_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ILISTENER_H


namespace robotguide::com::transportlayer
{
	/// <summary>
	/// Implement this interface for classes where you can listen for pending connections
	/// </summary>
	class IListener
	{
	public:
		/// <summary>
		/// Deconstruct the listener
		/// </summary>
		virtual ~IListener() = default;

		/// <summary>
		/// Start listening for connections
		/// </summary>
		/// <param name="maxConnections">The max amount of connections this socket will accept</param>
		virtual void Listen(unsigned maxConnections) = 0;

		/// <summary>
		/// Accept a pending connection
		/// </summary>
		/// <returns>It returns the socket handler</returns>
		virtual int Accept() = 0;

		/// <summary>
		/// Stop listening for connections
		/// </summary>
		virtual void Stop() = 0;
	};
}}}

#endif

