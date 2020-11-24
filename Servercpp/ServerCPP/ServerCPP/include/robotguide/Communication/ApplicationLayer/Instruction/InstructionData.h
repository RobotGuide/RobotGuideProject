#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONDATA_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONDATA_H

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionType.h"
#include <variant>
#include <string>

namespace robotguide::com::al
{
	struct InstructionData final
	{
	public:
		std::variant<std::string, int, double, InstructionType> Data;
	public:
		InstructionData(const char* text);
		InstructionData(const std::string& text);
		InstructionData(const int integer);
		InstructionData(const double decimal);
		InstructionData(const InstructionType instructionType);

		std::string GetString() const;
		int GetInteger() const;
		double GetDecimal() const;
		InstructionType GetInstructionType() const;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONDATA_H