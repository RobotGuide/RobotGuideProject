#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTION_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTION_H

#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionData.h"
#include <vector>

namespace robotguide::com::al
{
	struct Instruction
	{
	private:
		const InstructionType type;
		const std::vector<InstructionData> data;
	public:
		Instruction(const InstructionType type_, const std::vector<InstructionData>& data_);

		std::string ToString() const;
		InstructionType GetType() const;
		std::vector<InstructionData> GetData() const;
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_INSTRUCTION_INSTRUCTION_H