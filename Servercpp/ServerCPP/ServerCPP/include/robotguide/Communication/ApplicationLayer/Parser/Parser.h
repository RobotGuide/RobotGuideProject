#ifndef ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_PARSER_PARSER_H
#define ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_PARSER_PARSER_H

#include "robotguide/Communication/ApplicationLayer/Parser/ParserState.h"
#include "robotguide/Communication/ApplicationLayer/Token/TokenStream.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionStream.h"

namespace robotguide::com::applicationlayer
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

		[[nodiscard]] Instruction* CreateInstruction(const Token* token, const std::vector<Token*>& vector) const;
	public:
		Parser() = default;
		void ResetParser();

		void GetInstructionStream(TokenStream& tokenStream, InstructionStream& instructionStream);
	};
}

#endif //ROBOTGUIDE_COMMUNICATION_APPLICATIONLAYER_PARSER_PARSER_H