#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionData.h"

robotguide::com::applicationlayer::InstructionData::InstructionData(const char* text)
{
	Data = text;
}

robotguide::com::applicationlayer::InstructionData::InstructionData(const std::string& text)
{
	Data = text;
}

robotguide::com::applicationlayer::InstructionData::InstructionData(const int integer)
{
	Data = integer;
}

robotguide::com::applicationlayer::InstructionData::InstructionData(const double decimal)
{
	Data = decimal;
}

robotguide::com::applicationlayer::InstructionData::InstructionData(const InstructionType instructionType)
{
	Data = instructionType;
}

std::string robotguide::com::applicationlayer::InstructionData::GetString() const
{
	return std::get<std::string>(Data);
}

int robotguide::com::applicationlayer::InstructionData::GetInteger() const
{
	return std::get<int>(Data);
}

double robotguide::com::applicationlayer::InstructionData::GetDecimal() const
{
	return std::get<double>(Data);
}

robotguide::com::applicationlayer::InstructionType robotguide::com::applicationlayer::InstructionData::GetInstructionType() const
{
	return std::get<InstructionType>(Data);
}
