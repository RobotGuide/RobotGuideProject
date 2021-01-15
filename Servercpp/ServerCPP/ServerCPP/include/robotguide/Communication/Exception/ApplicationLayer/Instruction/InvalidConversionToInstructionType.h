#ifndef ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_INSTRUCTION_INVALIDCONVERSIONTOINSTRUCTIONTYPE_H
#define ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_INSTRUCTION_INVALIDCONVERSIONTOINSTRUCTIONTYPE_H

#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/LexerException.h"

namespace robotguide::com::exception::applicationlayer
{
	class InvalidConversionToInstructionType : public LexerException
	{
	public:
		InvalidConversionToInstructionType(const char* text);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_EXCEPTION_APPLICATIONLAYER_INSTRUCTION_INVALIDCONVERSIONTOINSTRUCTIONTYPE_H