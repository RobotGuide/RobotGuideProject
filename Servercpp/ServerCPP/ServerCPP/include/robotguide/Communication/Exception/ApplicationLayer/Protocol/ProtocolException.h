#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PROTOCOL_PROTOCOLEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PROTOCOL_PROTOCOLEXCEPTION_H

#include "robotguide/Communication/Exception/ApplicationLayer/ApplicationLayerException.h"

namespace robotguide::com::exception::applicationlayer
{
	class ProtocolException : public ApplicationLayerException
	{
	public:
		ProtocolException(const char* text);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PROTOCOL_PROTOCOLEXCEPTION_H