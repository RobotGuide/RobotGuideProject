#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKEN_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKEN_H

#include "robotguide/Communication/ApplicationLayer/Token/TokenType.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionData.h"

namespace robotguide::com::al
{
	class Token
	{
	public:
		const TokenType Type;
		const InstructionData Data;
	public:
		Token(const TokenType type, const InstructionData data);
		std::string ToString() const;
		std::string DataToString() const;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_TOKEN_TOKEN_H