#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionStream.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"

using namespace robotguide::com::applicationlayer;

InstructionStream::~InstructionStream()
{
	for (auto* instruction : instructions)
	{
		delete instruction;
		instruction = nullptr;
	}
}

void InstructionStream::AddInstruction(Instruction* instruction)
{
	instructions.push_back(instruction);
}

std::string InstructionStream::ToString() const
{
	std::string completeString;

	for (const auto& instruction : instructions)
	{
		completeString += instruction->ToString();
	}
	
	return completeString;
}

unsigned InstructionStream::size() const
{
	return instructions.size();
}
