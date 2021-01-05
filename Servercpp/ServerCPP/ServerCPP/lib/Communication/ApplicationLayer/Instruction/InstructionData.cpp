#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionData.h"

using namespace robotguide::com::applicationlayer;

InstructionData::InstructionData(const char* text)
{
	Data = text;
}

InstructionData::InstructionData(const std::string& text)
{
	Data = text;
}

InstructionData::InstructionData(const int integer)
{
	Data = integer;
}

InstructionData::InstructionData(const double decimal)
{
	Data = decimal;
}

InstructionData::InstructionData(const InstructionType instructionType)
{
	Data = instructionType;
}

std::string InstructionData::GetString() const
{
	return std::get<std::string>(Data);
}

int InstructionData::GetInteger() const
{
	return std::get<int>(Data);
}

double InstructionData::GetDecimal() const
{
	return std::get<double>(Data);
}

InstructionType InstructionData::GetInstructionType() const
{
	return std::get<InstructionType>(Data);
}
