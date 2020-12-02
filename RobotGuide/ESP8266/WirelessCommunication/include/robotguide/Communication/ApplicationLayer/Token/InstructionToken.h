#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_INSTRUCTIONTOKEN_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_INSTRUCTIONTOKEN_H

#include "robotguide/Communication/ApplicationLayer/Token/Token.h"

namespace robotguide { namespace com { namespace al 
{
	class InstructionToken final : public Token
	{
	public:
		InstructionToken(const InstructionType data);
	};
}}}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_INSTRUCTIONTOKEN_H