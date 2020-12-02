#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKENTYPE_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKENTYPE_H

/*
 * Defines the different input data types, used by the lexer.
 */

namespace robotguide { namespace com { namespace al 
{
	enum class TokenType
	{
		Head,
		Integer,
		Decimal,
		Text,
	};
}}}


#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKENTYPE_H