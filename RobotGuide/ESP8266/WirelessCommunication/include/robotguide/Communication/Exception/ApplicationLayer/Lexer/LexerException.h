#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_LEXEREXCEPTION_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_LEXEREXCEPTION_H

#include "robotguide/Communication/Exception/ApplicationLayer/ApplicationLayerException.h"

namespace robotguide { namespace com { namespace al
{
	class LexerException : public ApplicationLayerException
	{
	public:
		LexerException(const char* text);
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_LEXER_LEXEREXCEPTION_H