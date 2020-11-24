#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_PARSER_PARSER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_PARSER_PARSER_H

#include "robotguide/Communication/ApplicationLayer/Parser/ParserState.h"
#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionStream.h"

namespace robotguide::com::al
{
	class Parser
	{
	private:
		ParserState currentState = ParserState::None;

		void UpdateState(const ParserState parserState);
		bool CurrentStateIsInstructionType() const;
		bool CurrentStateIsInput() const;
		bool CurrentStateIsNone() const;
		bool CurrentStateIsError() const;

		[[nodiscard]] Instruction* CreateInstruction(const std::shared_ptr<Token>& token, const std::vector<std::shared_ptr<Token>>& vector) const;
	public:
		Parser() = default;

		InstructionStream GetInstructionStream(TokenStream tokenStream);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_PARSER_PARSER_H