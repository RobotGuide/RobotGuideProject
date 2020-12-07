#include "robotguide/Communication/ApplicationLayer/Token/TextToken.h"

robotguide::com::applicationlayer::TextToken::TextToken(const char* data) : Token(TokenType::Text, InstructionData(data))
{
}

robotguide::com::applicationlayer::TextToken::TextToken(const std::string& data) : Token(TokenType::Text, InstructionData(data))
{
}
