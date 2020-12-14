#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKETDISCONNECTEDEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKETDISCONNECTEDEXCEPTION_H

#include "robotguide/Communication/TransportLayer/SocketException.h"

namespace robotguide::com::transportlayer
{
	class SocketDisconnectedException : public SocketException
	{
	public:
		SocketDisconnectedException(const std::string& errorMessage)
			: SocketException(errorMessage)
		{
		}
	};
}

#endif

