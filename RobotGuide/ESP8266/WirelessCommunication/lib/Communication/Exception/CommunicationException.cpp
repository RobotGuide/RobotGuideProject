#include "robotguide/Communication/Exception/CommunicationException.h"

robotguide::com::exception::CommunicationException::CommunicationException(const char* text_) : text(text_)
{
}

char const* robotguide::com::exception::CommunicationException::what() const
{
	return text;
}
