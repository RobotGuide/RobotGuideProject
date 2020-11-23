#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKEINITIALIZATIONEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKEINITIALIZATIONEXCEPTION_H

#include "robotguide/Communication/TransportLayer/SocketException.h"

namespace robotguide::com::transportlayer
{
	class SocketInitializationException : public SocketException
	{
	public:
		explicit SocketInitializationException(const std::string& errorMessage)
			: SocketException(errorMessage)
		{
		}
	};
}

#endif

