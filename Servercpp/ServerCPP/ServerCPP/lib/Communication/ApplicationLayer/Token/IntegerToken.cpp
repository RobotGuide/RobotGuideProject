#include "robotguide/Communication/ApplicationLayer/Token/IntegerToken.h"

using namespace robotguide::com::applicationlayer;

IntegerToken::IntegerToken(const int data) : Token(TokenType::Integer, InstructionData(data))
{
}
