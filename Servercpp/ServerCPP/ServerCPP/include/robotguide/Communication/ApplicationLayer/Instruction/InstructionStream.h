#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H
#include <memory>
#include <vector>

#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"

namespace robotguide::com::applicationlayer
{
	class InstructionStream
	{
	private:
		std::vector<std::shared_ptr<Instruction>> instructions;
	public:
		InstructionStream() = default;

		void AddInstruction(Instruction* instruction);

		std::string ToString() const;

		std::shared_ptr<Instruction>& operator[](const unsigned index)
		{
			return instructions[index];
		}

		const std::shared_ptr<Instruction>& operator[](const unsigned index) const
		{
			return instructions[index];
		}

		unsigned size() const;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H