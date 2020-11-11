#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKENTYPE_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKENTYPE_H

/*
 * Defines the different input datatypes, used by the lexer.
 */

namespace robotguide::com::applicationlayer
{
	enum class TokenType
	{
		Head,
		Integer,
		Decimal,
		Text,
	};
}


#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKENTYPE_H