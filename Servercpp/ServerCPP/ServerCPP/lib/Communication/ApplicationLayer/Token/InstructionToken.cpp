#include "robotguide/Communication/ApplicationLayer/Token/InstructionToken.h"

robotguide::com::applicationlayer::InstructionToken::InstructionToken(const InstructionType data) : Token(TokenType::Head, InstructionData(data))
{
}
