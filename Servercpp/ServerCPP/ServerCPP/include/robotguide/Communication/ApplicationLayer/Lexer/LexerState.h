#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXERSTATE_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXERSTATE_H

namespace robotguide::com::applicationlayer
{
	enum class LexerState
	{
		Head,
		Int,
		Decimal,
		Text,
		None,
		Stringdeclaration,
		Error,
		EndToken,
		Ignore,
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXERSTATE_H
