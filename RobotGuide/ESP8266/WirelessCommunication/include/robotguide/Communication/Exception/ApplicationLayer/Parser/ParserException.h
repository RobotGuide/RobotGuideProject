#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PARSER_PARSEREXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PARSER_PARSEREXCEPTION_H

#include "robotguide/Communication/Exception/ApplicationLayer/ApplicationLayerException.h"

namespace robotguide { namespace com { namespace al
{
	class ParserException : public ApplicationLayerException
	{
	public:
		ParserException(const char* text);
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PARSER_PARSEREXCEPTION_H