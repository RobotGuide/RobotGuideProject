#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include <memory>

using namespace robotguide::com::applicationlayer;

Instruction::Instruction(const InstructionType type_, const std::vector<InstructionData>& data_)
	: type(type_), data(data_)
{
}

std::string Instruction::ToString() const
{
	std::string completeString = "Head: " + InstructionPrinter().InstructionTypeToString(type) + '\n';

	for(auto singleData : data)
	{
		completeString += "    Data: " "not implemented\n";
	}
	
	return completeString;
}

InstructionType Instruction::GetType() const
{
	return type;
}

std::vector<InstructionData> Instruction::
GetData() const
{
	return data;
}