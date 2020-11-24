#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"

robotguide::com::al::Instruction::Instruction(const InstructionType type_, const std::vector<InstructionData>& data_)
	: type(type_), data(data_)
{
}

std::string robotguide::com::al::Instruction::ToString() const
{
	std::string completeString = "Head: " + InstructionPrinter().InstructionTypeToString(type) + '\n';

	for(auto singleData : data)
	{
		completeString += "    Data: " "not implemented\n";
	}
	
	return completeString;
}
