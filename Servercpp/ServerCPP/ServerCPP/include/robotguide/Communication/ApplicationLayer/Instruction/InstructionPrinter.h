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
		InstructionPrinter() = delete;

		static InstructionType GetInstructionType(const std::string& text);
		static std::string InstructionTypeToString(const InstructionType type);

		static std::string ConvertInstructionToASCII(const Instruction& instruction);
		static std::string ConvertInstructionStreamToASCII(const InstructionStream& stream);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONPRINTER_H