#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ISOCKET_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_ISOCKET_H

namespace robotguide::com::transportlayer
{
	class ISocket
	{
	public:
		/// <summary>
		/// Destruct a socket
		/// </summary>
		virtual ~ISocket() = default;

		/// <summary>
		/// Handle the data. This should only be called when the socket has data available.
		/// </summary>
		virtual void HandleAvailableData() = 0;
	};
}


#endif
