#include "robotguide/Communication/ApplicationLayer/Token/TextToken.h"

using namespace robotguide::com::applicationlayer;

TextToken::TextToken(const char* data) : Token(TokenType::Text, InstructionData(data))
{
}

TextToken::TextToken(const std::string& data) : Token(TokenType::Text, InstructionData(data))
{
}
