#include "robotguide/Communication/ApplicationLayer/Token/InstructionToken.h"

using namespace robotguide::com::applicationlayer;

InstructionToken::InstructionToken(const InstructionType data) : Token(TokenType::Head, InstructionData(data))
{
}
