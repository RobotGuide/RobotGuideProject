#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionType.h"
#include <string>

namespace robotguide::com::applicationlayer
{
	struct InstructionPrinter
	{
	public:
		InstructionPrinter() = default;

		InstructionType GetInstructionType(const std::string& text) const;
		std::string InstructionTypeToString(const InstructionType type) const;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H