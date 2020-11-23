#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKEDISCONNECTEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKEDISCONNECTEXCEPTION_H

#include "robotguide/Communication/TransportLayer/SocketException.h"

namespace robotguide::com::transportlayer
{
	class SocketDisconnectException : public SocketException
	{
	public:
		explicit SocketDisconnectException(const std::string& errorMessage)
			: SocketException(errorMessage)
		{
		}
	};
}

#endif

