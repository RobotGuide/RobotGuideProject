#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXERCHARACTERTYPE_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXERCHARACTERTYPE_H

namespace robotguide { namespace com { namespace al 
{
	enum class LexerCharacterType
	{
		Unknown,
		Text,
		Number,
		Point,
		Negative_sign,
		Comma,
		Stringdeclaration,
		Space,
		Ignore,
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_LEXER_LEXERCHARACTERTYPE_H
