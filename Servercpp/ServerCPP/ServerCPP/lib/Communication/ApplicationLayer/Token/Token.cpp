#include "robotguide/Communication/ApplicationLayer/Token/Token.h"
#include "robotguide/Communication/ApplicationLayer/Instruction/InstructionPrinter.h"

using namespace robotguide;
using namespace com;
using namespace applicationlayer;

Token::Token(const TokenType type, const InstructionData data) : Type(type), Data(data)
{
}

std::string Token::ToString() const
{
	switch (Type)
	{
	case TokenType::Head:
		return "Head";
	case TokenType::Integer:
		return "Integer";
	case TokenType::Decimal:
		return "Decimal";
	case TokenType::Text:
		return "Text";
	}
}

std::string Token::DataToString() const
{
	switch (Type)
	{
	case TokenType::Head:
		return InstructionPrinter::InstructionTypeToString(Data.GetInstructionType());
	case TokenType::Integer:
		return std::to_string(Data.GetInteger());
	case TokenType::Decimal:
		return std::to_string(Data.GetDecimal());
	case TokenType::Text:
		return Data.GetString();
	}
	return "";
}
