#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_NOCONNECTIONEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_NOCONNECTIONEXCEPTION_H

#include "robotguide/Communication/TransportLayer/SocketException.h"

namespace robotguide::com::transportlayer
{
	class SocketNoConnectionException : public SocketException
	{
	public:
		SocketNoConnectionException(const std::string& errorMessage)
			: SocketException(errorMessage)
		{
		}
	};
}

#endif

