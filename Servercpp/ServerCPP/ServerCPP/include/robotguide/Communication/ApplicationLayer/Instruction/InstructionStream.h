#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H
#include <memory>
#include <vector>

#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"

namespace robotguide::com::al
{
	class InstructionStream
	{
	private:
		using const_iterator = std::vector<std::shared_ptr<Instruction>>::const_iterator;
		using iterator = std::vector<std::shared_ptr<Instruction>>::iterator;
		
		std::vector<std::shared_ptr<Instruction>> instructions;
	public:
		InstructionStream() = default;

		void AddInstruction(Instruction* instruction);

		std::string ToString() const;

		Instruction& operator[](const unsigned index)
		{
			return *instructions[index];
		}

		const Instruction& operator[](const unsigned index) const
		{
			return *instructions[index];
		}

		unsigned size() const;

		const_iterator begin() const noexcept
		{
			return instructions.begin();
		}

		const_iterator end() const noexcept
		{
			return instructions.end();
		}
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H