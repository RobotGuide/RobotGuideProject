#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_INTEGERTOKEN_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_INTEGERTOKEN_H

#include "robotguide/Communication/ApplicationLayer/Token/Token.h"

namespace robotguide { namespace com { namespace al 
{
	class IntegerToken final : public Token
	{
	public:
		IntegerToken(const int data);
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_INTEGERTOKEN_H