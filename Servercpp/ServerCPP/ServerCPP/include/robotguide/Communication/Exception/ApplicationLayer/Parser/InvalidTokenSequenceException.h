#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PARSER_INVALIDTOKENSEQUENCEEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PARSER_INVALIDTOKENSEQUENCEEXCEPTION_H

#include "robotguide/Communication/Exception/ApplicationLayer/Parser/ParserException.h"

namespace robotguide::com::exception::al
{
	class InvalidTokenSequenceException final : public ParserException
	{
	public:
		InvalidTokenSequenceException(const char* text);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_PARSER_INVALIDTOKENSEQUENCEEXCEPTION_H