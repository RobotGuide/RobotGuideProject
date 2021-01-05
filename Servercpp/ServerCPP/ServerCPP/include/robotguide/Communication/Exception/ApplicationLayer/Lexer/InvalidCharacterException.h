#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_INVALIDCHARACTEREXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_INVALIDCHARACTEREXCEPTION_H

#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"

namespace robotguide::com::exception::applicationlayer
{
	class InvalidCharacterException final : public LexerException
	{
	public:
		InvalidCharacterException(const char* text);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_INVALIDCHARACTEREXCEPTION_H