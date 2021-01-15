#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include <memory>

using namespace robotguide;
using namespace com;
using namespace applicationlayer;

Instruction::Instruction(const InstructionType type_, const std::vector<InstructionData>& data_)
	: type(type_), data(data_)
{
}

std::string Instruction::ToString() const
{
	return InstructionPrinter().ConvertInstructionToASCII(*this);
}

std::string Instruction::ToFormattedString() const
{
	std::string completeString = "Head: " + InstructionPrinter().InstructionTypeToString(type) + '\n';

	for (const auto& singleData : data)
	{
		completeString += "\tData member: " + std::to_string(singleData.GetInteger()) + '\n';
	}

	return completeString;
}

InstructionType Instruction::GetType() const
{
	return type;
}

std::vector<InstructionData> Instruction::GetData() const
{
	return data;
}