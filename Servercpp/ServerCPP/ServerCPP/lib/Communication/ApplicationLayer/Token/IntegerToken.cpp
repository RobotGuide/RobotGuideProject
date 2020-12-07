#include "robotguide/Communication/ApplicationLayer/Token/IntegerToken.h"

robotguide::com::applicationlayer::IntegerToken::IntegerToken(const int data) : Token(TokenType::Integer, InstructionData(data))
{
}
