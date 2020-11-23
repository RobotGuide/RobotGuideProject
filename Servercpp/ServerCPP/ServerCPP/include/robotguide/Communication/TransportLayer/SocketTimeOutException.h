#ifndef ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKETTIMEOUTEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_TRANSPORTLAYER_SOCKETTIMEOUTEXCEPTION_H

#include "robotguide/Communication/TransportLayer/SocketException.h"

namespace robotguide::com::transportlayer
{
	class SocketTimeOutException : public SocketException
	{
	public:
		explicit SocketTimeOutException(const std::string& errorMessage)
			: SocketException(errorMessage)
		{
		}
	};
}

#endif

