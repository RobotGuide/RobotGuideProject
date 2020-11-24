#include "robotguide/Communication/ApplicationLayer/Token/DecimalToken.h"

robotguide::com::al::DecimalToken::DecimalToken(const double data) : Token(TokenType::Decimal, InstructionData(data))
{
}
