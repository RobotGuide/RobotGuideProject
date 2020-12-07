#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"

#include <memory>


#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"

robotguide::com::applicationlayer::Instruction::Instruction(const InstructionType type_, const std::vector<InstructionData>& data_)
	: type(type_), data(data_)
{
}

std::string robotguide::com::applicationlayer::Instruction::ToString() const
{
	std::string completeString = "Head: " + InstructionPrinter().InstructionTypeToString(type) + '\n';

	for(auto singleData : data)
	{
		completeString += "    Data: " "not implemented\n";
	}
	
	return completeString;
}