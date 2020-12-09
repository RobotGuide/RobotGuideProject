#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionType.h"
#include <string>

namespace robotguide::com::applicationlayer
{
	struct Instruction;
	class InstructionStream;

	class InstructionPrinter
	{
	public:
		InstructionPrinter() = default;

		InstructionType GetInstructionType(const std::string& text) const;
		std::string InstructionTypeToString(const InstructionType type) const;

		std::string ConvertInstructionToASCII(const Instruction& instruction) const;
		std::string ConvertInstructionStreamToASCII(const InstructionStream& stream) const;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H