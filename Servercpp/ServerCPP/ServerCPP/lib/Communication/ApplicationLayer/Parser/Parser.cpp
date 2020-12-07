#include "robotguide/Communication/ApplicationLayer/Parser/Parser.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Parser/InvalidTokenSequenceException.h"

robotguide::com::applicationlayer::InstructionStream robotguide::com::applicationlayer::Parser::GetInstructionStream(
	TokenStream tokenStream)
{
	std::shared_ptr<Token> instructionHead;
	std::vector<std::shared_ptr<Token>> instructionData;
	instructionData.reserve(3);

	InstructionStream stream;

	bool instructionHeadSet = false;
	
	for (auto i = 0; i < tokenStream.size(); i++)
	{
		const std::shared_ptr<Token> currentToken = tokenStream[i];
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
				stream.AddInstruction(CreateInstruction(instructionHead, instructionData));
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
			throw exception::al::InvalidTokenSequenceException("Incorrect sequence encountered!");
			break;
		case ParserState::None:
			break;
		}
	}

	if (!instructionData.empty())
	{
		stream.AddInstruction(CreateInstruction(instructionHead, instructionData));
	}

	UpdateState(ParserState::None);
	
	return stream;
}

void robotguide::com::applicationlayer::Parser::UpdateState(const ParserState parserState)
{
	currentState = parserState;
}

bool robotguide::com::applicationlayer::Parser::CurrentStateIsInstructionType() const
{
	return currentState == ParserState::InstructionType;
}

bool robotguide::com::applicationlayer::Parser::CurrentStateIsInput() const
{
	return currentState == ParserState::InputType;
}

bool robotguide::com::applicationlayer::Parser::CurrentStateIsNone() const
{
	return currentState == ParserState::None;
}

bool robotguide::com::applicationlayer::Parser::CurrentStateIsError() const
{
	return currentState == ParserState::Error;
}

robotguide::com::applicationlayer::Instruction* robotguide::com::applicationlayer::Parser::CreateInstruction(const std::shared_ptr<Token>& token,
	const std::vector<std::shared_ptr<Token>>& vector) const
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
