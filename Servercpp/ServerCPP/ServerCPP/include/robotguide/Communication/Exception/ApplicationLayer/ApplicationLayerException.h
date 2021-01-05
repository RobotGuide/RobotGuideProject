#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_APPLICATIONLAYEREXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_APPLICATIONLAYEREXCEPTION_H

#include "robotguide/Communication/Exception/CommunicationException.h"

namespace robotguide::com::exception::applicationlayer
{
	class ApplicationLayerException : public CommunicationException
	{
	public:
		ApplicationLayerException(const char* text);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_APPLICATIONLAYEREXCEPTION_H