#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_INVALIDSEQUENCEEXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_INVALIDSEQUENCEEXCEPTION_H

#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"

namespace robotguide { namespace com { namespace al
{
	class InvalidSequenceException final : public LexerException
	{
	public:
		InvalidSequenceException(const char* text);
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_INVALIDSEQUENCEEXCEPTION_H