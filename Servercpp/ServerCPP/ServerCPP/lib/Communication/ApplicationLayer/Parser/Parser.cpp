#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/InvalidTokenSequenceException.h"
#include <exception>

using namespace robotguide::com::applicationlayer;

void Parser::ResetParser()
{
	currentState = ParserState::None;
}

void Parser::GetInstructionStream(
	TokenStream& tokenStream, InstructionStream& instructionStream)
{
	Token* instructionHead = nullptr;
	std::vector<Token*> instructionData;
	instructionData.reserve(3);

	bool instructionHeadSet = false;
	
	for (auto i = 0; i < tokenStream.size(); i++)
	{
		Token* currentToken = tokenStream[i];
		switch (currentToken->Type)
		{
		case TokenType::Head:
			if (CurrentStateIsNone())
			{
				instructionHeadSet = false;
				UpdateState(ParserState::InstructionType);
			}
			else if (CurrentStateIsInstructionType())
			{
				instructionStream.AddInstruction(CreateInstruction(instructionHead, instructionData));
				instructionData.clear();
				instructionHeadSet = false;
				UpdateState(ParserState::InstructionType);
			}
			else
			{
				UpdateState(ParserState::Error);
			}
			break;
		case TokenType::Integer: /* FALL THROUGH */
		case TokenType::Decimal: /* FALL THROUGH */
		case TokenType::Text:    /* FALL THROUGH */
			if ((CurrentStateIsInstructionType() || CurrentStateIsInput())
				&& instructionData.size() < 3)
			{
				UpdateState(ParserState::InputType);
			}
			else
			{
				UpdateState(ParserState::Error);
			}
			break;
		}

		switch(currentState)
		{
		case ParserState::InputType:
			instructionData.push_back(currentToken);
			break;
		case ParserState::InstructionType:
			instructionHead = currentToken;
			instructionHeadSet = true;
			break;
		case ParserState::Error:
			throw exception::applicationlayer::InvalidTokenSequenceException("Incorrect sequence encountered!");
			break;
		case ParserState::None:
			break;
		}
	}

	if (!instructionData.empty())
	{
		instructionStream.AddInstruction(CreateInstruction(instructionHead, instructionData));
	}

	UpdateState(ParserState::None);
}

void Parser::UpdateState(const ParserState parserState)
{
	currentState = parserState;
}

bool Parser::CurrentStateIsInstructionType() const
{
	return currentState == ParserState::InstructionType;
}

bool Parser::CurrentStateIsInput() const
{
	return currentState == ParserState::InputType;
}

bool Parser::CurrentStateIsNone() const
{
	return currentState == ParserState::None;
}

bool Parser::CurrentStateIsError() const
{
	return currentState == ParserState::Error;
}

Instruction* Parser::CreateInstruction(const Token* token,
                                       const std::vector<Token*>& vector) const
{
	const InstructionType type = token->Data.GetInstructionType();
	std::vector<InstructionData> data;
	data.reserve(3);

	for (const auto& i : vector)
	{
		data.push_back(i->Data);
	}
	return new Instruction(type, data);
}
