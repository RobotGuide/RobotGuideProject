#include "robotguide/Communication/ApplicationLayer/Token/InstructionToken.h"

robotguide::com::al::InstructionToken::InstructionToken(const InstructionType data) : Token(TokenType::Head, InstructionData(data))
{
}
