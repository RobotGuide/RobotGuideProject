#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_DOUBLETOKEN_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_DOUBLETOKEN_H

#include "robotguide/Communication/ApplicationLayer/Token/Token.h"

namespace robotguide::com::al
{
	class DecimalToken final : public Token
	{
	public:
		DecimalToken(const double data);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_DOUBLETOKEN_H