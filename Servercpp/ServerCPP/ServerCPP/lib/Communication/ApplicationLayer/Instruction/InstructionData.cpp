#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionData.h"

robotguide::com::al::InstructionData::InstructionData(const char* text)
{
	Data = text;
}

robotguide::com::al::InstructionData::InstructionData(const std::string& text)
{
	Data = text;
}

robotguide::com::al::InstructionData::InstructionData(const int integer)
{
	Data = integer;
}

robotguide::com::al::InstructionData::InstructionData(const double decimal)
{
	Data = decimal;
}

robotguide::com::al::InstructionData::InstructionData(const InstructionType instructionType)
{
	Data = instructionType;
}

std::string robotguide::com::al::InstructionData::GetString() const
{
	return std::get<std::string>(Data);
}

int robotguide::com::al::InstructionData::GetInteger() const
{
	return std::get<int>(Data);
}

double robotguide::com::al::InstructionData::GetDecimal() const
{
	return std::get<double>(Data);
}

robotguide::com::al::InstructionType robotguide::com::al::InstructionData::GetInstructionType() const
{
	return std::get<InstructionType>(Data);
}
