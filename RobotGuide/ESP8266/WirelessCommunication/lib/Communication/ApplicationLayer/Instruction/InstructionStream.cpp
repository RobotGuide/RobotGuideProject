#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionStream.h"

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"

void robotguide::com::al::InstructionStream::AddInstruction(Instruction* instruction)
{
	instructions.push_back(std::shared_ptr<Instruction>(instruction));
}

std::string robotguide::com::al::InstructionStream::ToString() const
{
	std::string completeString;

	for (const auto& instruction : instructions)
	{
		completeString += instruction->ToString();
	}
	
	return completeString;
}

unsigned robotguide::com::al::InstructionStream::size() const
{
	return instructions.size();
}
