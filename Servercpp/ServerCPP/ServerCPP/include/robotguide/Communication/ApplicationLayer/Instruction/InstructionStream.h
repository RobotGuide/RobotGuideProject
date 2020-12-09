#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H

#include "robotguide/Communication/ApplicationLayer/Instruction/Instruction.h"
#include <vector>
#include <memory>

namespace robotguide::com::applicationlayer
{
	/*
	 * InstructionStreams take ownership of the content they receive.
	 */
	class InstructionStream
	{
	private:
		std::vector<Instruction*> instructions;
	public:
		InstructionStream() = default;
		InstructionStream(const InstructionStream& instructionStream) = delete;

		~InstructionStream();

		void AddInstruction(Instruction* instruction);

		std::string ToString() const;

		const Instruction* operator[](const unsigned index)
		{
			return instructions[index];
		}

		const Instruction* operator[](const unsigned index) const
		{
			return instructions[index];
		}

		unsigned size() const;

		InstructionStream& operator=(const InstructionStream& instructionStream) = delete;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTIONSTREAM_H