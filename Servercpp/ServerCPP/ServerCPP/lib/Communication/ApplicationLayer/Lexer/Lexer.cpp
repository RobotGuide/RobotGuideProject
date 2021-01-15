#include "robotguide/Communication/ApplicationLayer/Lexer/Lexer.h"
#include "robotguide/Communication/ApplicationLayer/Token/IntegerToken.h"
#include "robotguide/Communication/ApplicationLayer/Token/DecimalToken.h"
#include "robotguide/Communication/ApplicationLayer/Token/InstructionToken.h"
#include "robotguide/Communication/ApplicationLayer/Token/TextToken.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/InvalidCharacterException.h"
#include "robotguide/Communication/Exception/ApplicationLayer/Lexer/InvalidSequenceException.h"

using namespace robotguide::com;
using namespace applicationlayer;

void Lexer::GetTokenStream(const char& text, TokenStream& stream) const
{
	GetTokenStream(text, stream);
}

void Lexer::ResetLexer()
{
	UpdateCurrentState(LexerState::None);
	buffer.clear();
}

void Lexer::AddCharacterToBufferAndRetrieveToken(TokenStream& stream, const char character)
{
	const LexerState newState = LexCharacter(character);
	if (newState == LexerState::EndToken && !buffer.empty())
	{
		Token* newToken = GetToken();
		stream.AddToken(newToken);
		ResetLexer();
	}
	else if (newState == LexerState::Error)
	{
		throw exception::applicationlayer::InvalidSequenceException("Invalid sequence encountered!");
	}
	else if (newState == LexerState::Ignore)
	{
		return;
	}
	else if (newState != LexerState::Stringdeclaration)
	{
		buffer += character;
	}

	if (newState != LexerState::Ignore &&
		newState != LexerState::EndToken)
	{
		UpdateCurrentState(newState);
	}
}

void Lexer::GetTokenStream(const std::string& text, TokenStream& stream)
{
	for (auto character : text)
	{
		AddCharacterToBufferAndRetrieveToken(stream, character);
	}
	AddCharacterToBufferAndRetrieveToken(stream, ' '); // Is needed to fully clear the buffer, not forgetting some final text.
	ResetLexer();
}

LexerState Lexer::CurrentState() const
{
	return currentState;
}

LexerState Lexer::LexCharacter(const char character) const
{
	const LexerCharacterType type = GetCharacterType(character);
	if (type == LexerCharacterType::Unknown)
	{
		throw exception::applicationlayer::InvalidCharacterException("Unknown character encountered");
	}

	if (type == LexerCharacterType::Ignore)
	{
		return LexerState::Ignore;
	}

	switch (type)
	{
	case LexerCharacterType::Negative_sign:
		if (CurrentStateIsNone())
		{
			return LexerState::Int;
		}
		if (CurrentStateIsText())
		{
			return LexerState::Text;
		}

		return LexerState::Error;
		
	case LexerCharacterType::Text:
		if (CurrentStateIsNone() || CurrentStateIsHead())
		{
			return LexerState::Head;
		}
		if (CurrentStateIsStringDeclaration() || CurrentStateIsText())
		{
			return LexerState::Text;
		}

		return LexerState::Error;
		
	case LexerCharacterType::Comma:
		if (CurrentStateIsInteger())
		{
			return LexerState::Decimal;
		}
		if (CurrentStateIsText())
		{
			return LexerState::Text;
		}

		return LexerState::Error;

	case LexerCharacterType::Number:
		if (CurrentStateIsNone() || CurrentStateIsInteger())
		{
			return LexerState::Int;
		}
		if (CurrentStateIsDecimal())
		{
			return LexerState::Decimal;
		}
		if (CurrentStateIsText())
		{
			return LexerState::Text;
		}
		
		return LexerState::Error;

	case LexerCharacterType::Point:
		if (CurrentStateIsInteger())
		{
			return LexerState::Decimal;
		}
		if (CurrentStateIsText())
		{
			return LexerState::Text;
		}

		return LexerState::Error;

	case LexerCharacterType::Space:
		if (CurrentStateIsText())
		{
			return LexerState::Text;
		}
		
		return LexerState::EndToken;

	case LexerCharacterType::Stringdeclaration:
		if (CurrentStateIsNone() || CurrentStateIsText())
		{
			return LexerState::Stringdeclaration;
		}

		return LexerState::Error;

	default:
		return LexerState::Error;
	}
}

Token* Lexer::GetToken() const
{
	Token* token = nullptr;
	switch(currentState)
	{
	case LexerState::Head:
		token = GetInstructionToken();
		break;
	case LexerState::Int:
		token = GetIntToken();
		break;
	case LexerState::Decimal:
		token = GetDecimalToken();
		break;
	case LexerState::Stringdeclaration:
		token = GetTextToken();
		break;
	default:
		break;
	}

	if (token == nullptr)
	{
		throw exception::applicationlayer::InvalidSequenceException("Token couldn't be retrieved");
	}
	
	return token;
}

Token* Lexer::GetTextToken() const
{
	return new TextToken(buffer);
}

Token* Lexer::GetDecimalToken() const
{
	return new DecimalToken(std::stod(buffer));
}

Token* Lexer::GetIntToken() const
{
	return new IntegerToken(std::stoi(buffer));
}

Token* Lexer::GetInstructionToken() const
{
	const InstructionType type = InstructionPrinter().GetInstructionType(buffer);
	return new InstructionToken(type);
}

bool Lexer::CurrentStateIsStringDeclaration() const
{
	return currentState == LexerState::Stringdeclaration;
}

bool Lexer::CurrentStateIsHead() const
{
	return currentState == LexerState::Head;
}

bool Lexer::CurrentStateIsInteger() const
{
	return currentState == LexerState::Int;
}

bool Lexer::CurrentStateIsDecimal() const
{
	return currentState == LexerState::Decimal;
}

bool Lexer::CurrentStateIsText() const
{
	return currentState == LexerState::Text;
}

bool Lexer::CurrentStateIsNone() const
{
	return currentState == LexerState::None;
}

LexerCharacterType Lexer::GetCharacterType(const char character) const
{
	if (isdigit(character))
	{
		return LexerCharacterType::Number;
	}
	if (isalpha(character))
	{
		return LexerCharacterType::Text;
	}

	switch(character)
	{
	case '-':
		return LexerCharacterType::Negative_sign;
	case '.':
		return LexerCharacterType::Point;
	case ',':
		return LexerCharacterType::Comma;
	case '"':
		return LexerCharacterType::Stringdeclaration;
	case ' ':
		return LexerCharacterType::Space;
	case '\n': /* FALL THROUGH */
	case '\t': /* FALL THROUGH */
	case '\b': /* FALL THROUGH */
	case '\f': /* FALL THROUGH */
		return LexerCharacterType::Ignore;
	default:
		return LexerCharacterType::Unknown;
	}
}

void Lexer::UpdateCurrentState(const LexerState newState)
{
	if (newState == LexerState::EndToken)
	{
		currentState = LexerState::None;
	}
	else
	{
		currentState = newState;
	}
}
