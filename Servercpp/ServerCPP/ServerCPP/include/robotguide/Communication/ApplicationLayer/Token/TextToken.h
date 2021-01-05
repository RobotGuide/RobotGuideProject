#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TEXTTOKEN_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TEXTTOKEN_H

#include "robotguide/Communication/ApplicationLayer/Token/Token.h"

namespace robotguide::com::applicationlayer
{
	class TextToken final : public Token
	{
	public:
		TextToken(const char* data);
		TextToken(const std::string& data);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TEXTTOKEN_H