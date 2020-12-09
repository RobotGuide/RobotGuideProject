#include "robotguide/Communication/ApplicationLayer/Token/DecimalToken.h"

using namespace robotguide::com::applicationlayer;

DecimalToken::DecimalToken(const double data) : Token(TokenType::Decimal, InstructionData(data))
{
}
