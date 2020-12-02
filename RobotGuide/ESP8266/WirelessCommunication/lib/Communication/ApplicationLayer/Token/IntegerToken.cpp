#include "robotguide/Communication/ApplicationLayer/Token/IntegerToken.h"

robotguide::com::al::IntegerToken::IntegerToken(const int data) : Token(TokenType::Integer, InstructionData(data))
{
}
